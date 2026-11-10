import json
import sys
from pathlib import Path

import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import cwarn  # noqa: E402

OUT = """\
cfe: Warning 712: src/global/x.c, line 119: illegal combination of pointer and integer
                                 a = (s32)b;
 ------------------^
cfe: Warning 709: src/global/x.c, line 119: incompatible pointer type assignment
                                 a = (s32)b;
 --------------------------^
cc: Warning: -mips3 should not be used for ucode 32-bit compiles
cfe: Warning 712: src/global/x.c, line 120: illegal combination of pointer and integer
         c = d;
 ------------^
cfe: Warning 712: src/global/x.c, line 120: illegal combination of pointer and integer
         c = d;
 ------------^
cfe: Warning 709: include/actor.h, line 7: incompatible pointer type assignment
"""


def test_parse():
    w = lambda code, path, line, col, msg: dict(code=code, path=path, line=line, col=col, msg=msg)  # noqa: E731
    p712, p709 = "illegal combination of pointer and integer", "incompatible pointer type assignment"
    assert cwarn.parse(OUT) == [
        w(712, "src/global/x.c", 119, 19, p712),
        w(709, "src/global/x.c", 119, 27, p709),
        w(712, "src/global/x.c", 120, 13, p712),
        w(712, "src/global/x.c", 120, 13, p712),
        w(709, "include/actor.h", 7, -1, p709),
    ]


def _ratchet(tmp_path, before, after):
    b, a = tmp_path / "b.json", tmp_path / "a.json"
    b.write_text(json.dumps(before))
    a.write_text(json.dumps(after))
    cwarn.main(["ratchet", str(b), str(a)])


def test_ratchet_rise_fails(tmp_path, capsys):
    with pytest.raises(SystemExit) as ex:
        _ratchet(tmp_path, {"src/a.c": 2, "src/b.c": 1}, {"src/a.c": 3, "src/b.c": 0})
    assert ex.value.code == 1
    assert "ROSE src/a.c: 2 -> 3" in capsys.readouterr().out


def test_ratchet_new_file_passes(tmp_path, capsys):
    _ratchet(tmp_path, {"src/a.c": 2}, {"src/a.c": 1, "src/n.c": 4})
    out = capsys.readouterr().out
    assert "new src/n.c: 4" in out and "warnings OK (2 -> 5)" in out
