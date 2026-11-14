import subprocess
import sys
from pathlib import Path

import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import merge_record as mr  # noqa: E402


def test_keymap_rewrites_first_token():
    mapping = mr.parse_keymap("# renamed by the merge\n\nglobal:80600000:dead-if:aaaaaa -> global:80600000:dead-if:bbbbbb\n")
    lines = ['global:80600000:dead-if:aaaaaa diagnose nohit quirks=Q0001 note="x aaaaaa"',
             "global:80600000:other:cccccc plain nohit", ""]
    assert mr.apply_keymap(lines, mapping) == [
        'global:80600000:dead-if:bbbbbb diagnose nohit quirks=Q0001 note="x aaaaaa"',
        "global:80600000:other:cccccc plain nohit", ""]


def test_keymap_rejects_malformed_line():
    with pytest.raises(ValueError, match="keymap line 2"):
        mr.parse_keymap("a -> b\na => b\n")


def test_dry_run_ledger_only(tmp_path, capsys):
    head = subprocess.run(["git", "show", "HEAD:src/global/0.c"], cwd=REPO_ROOT, capture_output=True, check=True).stdout
    (tmp_path / "0.c").write_bytes(head)
    assert mr.main(["--dry-run", "--agent", "X", "--unit", "u", "--base", "HEAD", "--model", "a/b:high",
                    "--ledger", "/dev/null", "--copy-dir", str(tmp_path), "src/global/0.c"]) == 0
    out = capsys.readouterr().out
    cmds = [line for line in out.splitlines() if line.startswith("$ ")]
    assert [c.split()[4] if "quality.py" in c else c.split()[1:3] for c in cmds] == [
        "record", "carry", ["git", "add"], ["git", "commit"]]
    assert "merge_gate" not in out and "MERGE_RECORD_OK merge=none" in out
