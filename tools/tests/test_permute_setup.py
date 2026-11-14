"""Regression tests for tools/permute.py: single-function target, same-line wrapping, K&R definitions, setup record."""

import re
import struct
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools.permute import (
    HACK_PASSES,
    function_asm_from_object,
    read_setup_record,
    run_record_problem,
    settings_toml,
    setup_conflict,
    strip_other_fns,
    wrap_multi_statement_lines,
    write_setup_record,
)


def build_object(text_words, symbols, relocs):
    """Minimal big-endian ELF32 MIPS relocatable: .text, .bss, .rel.text, .symtab, .strtab, .shstrtab.

    symbols: (name, value, size, type, shndx); type 3 = section symbol (name ignored).
    relocs: (offset, type, symbol index).
    """
    shnames = ["", ".text", ".bss", ".rel.text", ".symtab", ".strtab", ".shstrtab"]
    shstrtab = b"\0".join(n.encode() for n in shnames) + b"\0"
    sh_name_off = [shstrtab.index(n.encode() + b"\0") if n else 0 for n in shnames]

    strtab = b"\0"
    symtab = b"\0" * 16
    for name, value, size, typ, shndx in symbols:
        name_off = 0
        if typ != 3:
            name_off = len(strtab)
            strtab += name.encode() + b"\0"
        bind = 0 if typ == 3 else 1
        symtab += struct.pack(">IIIBBH", name_off, value, size, (bind << 4) | typ, 0, shndx)
    text = b"".join(struct.pack(">I", w) for w in text_words)
    rel = b"".join(struct.pack(">II", off, ((sym + 1) << 8) | typ) for off, typ, sym in relocs)

    body = b""
    offsets = {}
    for key, data in (("text", text), ("rel", rel), ("symtab", symtab), ("strtab", strtab), ("shstrtab", shstrtab)):
        offsets[key] = 0x34 + len(body)
        body += data
    shoff = 0x34 + len(body)
    headers = [
        (0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
        (sh_name_off[1], 1, 6, 0, offsets["text"], len(text), 0, 0, 4, 0),
        (sh_name_off[2], 8, 3, 0, offsets["text"], 0, 0, 0, 4, 0),
        (sh_name_off[3], 9, 0, 0, offsets["rel"], len(rel), 4, 1, 4, 8),
        (sh_name_off[4], 2, 0, 0, offsets["symtab"], len(symtab), 5, 1, 4, 16),
        (sh_name_off[5], 3, 0, 0, offsets["strtab"], len(strtab), 0, 0, 1, 0),
        (sh_name_off[6], 3, 0, 0, offsets["shstrtab"], len(shstrtab), 0, 0, 1, 0),
    ]
    ident = b"\x7fELF\x01\x02\x01" + b"\0" * 9
    ehdr = ident + struct.pack(">HHIIIIIHHHHHH", 1, 8, 1, 0, 0, shoff, 0, 0x34, 0, 0, 40, len(headers), 6)
    return ehdr + body + b"".join(struct.pack(">10I", *h) for h in headers)


def test_target_is_only_the_function_rebased_to_zero():
    # helper at 0x0 (2 words), target at 0x8: lui (HI16 .bss), j inside target, jal helper (.text), nop
    words = [0x03E00008, 0x00000000, 0x3C0F0000, 0x08000000 | (0x10 >> 2), 0x0C000000, 0x00000000]
    symbols = [
        (".text", 0, 0, 3, 1),
        (".bss", 0, 0, 3, 2),
        ("helper", 0x0, 8, 2, 1),
        ("target", 0x8, 16, 2, 1),
        ("gExtern", 0, 0, 0, 0),
    ]
    relocs = [(0x8, 5, 1), (0xC, 4, 0), (0x10, 4, 0)]
    asm = function_asm_from_object(build_object(words, symbols, relocs), "target")

    lines = asm.splitlines()
    assert "target:" in lines
    assert [l for l in lines if l.startswith(".word")] == [
        ".word 0x3C0F0000",
        ".word 0x08000002",  # in-function jump rebased from 0x10 to 0x8 - 0x8
        ".word 0x0C000000",  # section-relative call: field cleared, callee named
        ".word 0x00000000",
    ]
    assert [l for l in lines if l.startswith(".reloc")] == [
        ".reloc target+0x0, R_MIPS_HI16, .bss",
        ".reloc target+0x4, R_MIPS_26, .text",
        ".reloc target+0x8, R_MIPS_26, helper",
    ]
    assert "0x03E00008" not in asm  # other functions of the TU are not part of the target


def wrapped(body: str) -> str:
    src = "int g;\nvoid f(void) {\n" + body + "\n}\n"
    out = wrap_multi_statement_lines(src, "f")
    return out[out.index("{") + 2:out.rindex("}") - 1]


def test_statement_sharing_a_line_with_do_is_kept_together():
    assert wrapped("    i = 0; do {\n        g++;\n    } while (++i < 3);") == (
        "    PERM_FORCE_SAMELINE(i = 0; do {)\n        g++;\n    } while (++i < 3);"
    )


def test_braceless_if_body_on_its_line_is_kept_together():
    assert wrapped("    if (g) return;") == "    PERM_FORCE_SAMELINE(if (g) return;)"


def test_single_pieces_are_left_alone():
    body = "    for (i = 0; i < 3; i++) {\n        g++;\n    } while (g);\n    if (g) {\n    } else {\n    }"
    assert wrapped(body) == body


def test_no_pragma_between_if_and_else():
    body = "    if (g) g = 1;\n    else if (i) g = 2;"
    assert wrapped(body) == body


KNR_SOURCE = """\
short proto(short);
short late_proto();

short knr_new(a, b)
short a;
short *b;
{
    return a + *b;
}

short proto(a)
short a;
{
    return a;
}

short late_proto(a)
short a;
{
    return a;
}

short late_proto(short);

short proto_after_target(a)
short a;
{
    return a;
}

void knr_comment(a, b)
int *a;
volatile unsigned char b; // FAKE: comment inside the declaration list
{
    *a = b;
}

int knr_bare(a)
{
    return a;
}

int ansi(int a) // comment before the brace
{
    return a;
}

int target(a, b)
short a;
short b;
{
    return knr_new(a, &b) + proto(b) + late_proto(a) + proto_after_target(b);
}

short proto_after_target(short);

int knr_after(a)
short a;
{
    return a;
}
"""


def test_knr_definitions_keep_their_type_at_the_target():
    out = strip_other_fns(KNR_SOURCE, "target")
    # Never an identifier list outside a definition, never a new ANSI prototype (IDO
    # would convert arguments to the declared types instead of default-promoting them).
    assert "(a, b);" not in out and "(a);" not in out
    assert "return a + *b;" not in out and "*a = b;" not in out
    # No declaration before the target: the definition becomes `T f();`.
    assert "short knr_new();" in out
    assert "void knr_comment();" in out
    assert "int knr_bare();" in out
    # A prototype seen before the target is in force there (IDO uses it before or after
    # a K&R definition), and `T f();` beside a narrow prototype is a cfe error: only the
    # prototype stays.
    assert "short proto(short);" in out and len(re.findall(r"\bproto\(", out)) == 2
    assert "short late_proto(short);" in out and "late_proto()" not in out
    # Prototypes after the target do not affect it and would clash with `T f();`.
    assert "short proto_after_target();" in out and "proto_after_target(short)" not in out
    # K&R definitions after the target are dropped.
    assert "knr_after" not in out
    # ANSI definitions still become prototypes, also with a comment before the brace.
    assert "int ansi(int a);" in out
    # The kept K&R target is unchanged.
    assert (
        "int target(a, b)\nshort a;\nshort b;\n{\n"
        "    return knr_new(a, &b) + proto(b) + late_proto(a) + proto_after_target(b);\n}"
    ) in out


def test_wrapping_finds_a_knr_target_with_comments_in_its_declarations():
    src = "int g;\nvoid f(a)\nint a; // c\n{\n    g = a; g++;\n}\n"
    assert "    PERM_FORCE_SAMELINE(g = a; g++;)" in wrap_multi_statement_lines(src, "f")


def make_setup_dir(path: Path, baseline: int) -> dict:
    for name, data in (("base.c", "int f(void) { return 1; }\n"), ("target.o", "obj"), ("compile.sh", "#!/bin/bash\n")):
        (path / name).write_text(data)
    record = {"seg": "boss", "func": "f", "src": "src/boss/F0D0.c", "source": ".scratch/A/F0D0.c", "baseline_score": baseline}
    write_setup_record(path, record)
    return read_setup_record(path)


def test_run_refuses_a_directory_another_setup_rewrote(tmp_path):
    record = make_setup_dir(tmp_path, baseline=160)
    assert run_record_problem(tmp_path, record) is None
    # Another agent's setup from the matched src replaced base.c and target.o: the
    # permuter would start from base score 0 and report a "zero" at once.
    (tmp_path / "base.c").write_text("int f(void) { return 2; }\n")
    (tmp_path / "target.o").write_text("other obj")
    problem = run_record_problem(tmp_path, record)
    assert problem is not None and "base.c, target.o changed since setup of f from .scratch/A/F0D0.c" in problem


def test_run_refuses_a_zero_baseline(tmp_path):
    record = make_setup_dir(tmp_path, baseline=0)
    assert "already scores 0" in run_record_problem(tmp_path, record)


def test_setup_replaces_only_its_own_directory():
    previous = {"func": "f", "source": ".scratch/A/F0D0.c"}
    assert setup_conflict(None, {"func": "f", "source": "src/boss/F0D0.c"}) is None
    # Re-setup from the same (updated) copy is the normal workflow.
    assert setup_conflict(previous, {"func": "f", "source": ".scratch/A/F0D0.c"}) is None
    assert "from .scratch/A/F0D0.c, not f from src/boss/F0D0.c" in setup_conflict(
        previous, {"func": "f", "source": "src/boss/F0D0.c"}
    )
    assert setup_conflict(previous, {"func": "g", "source": ".scratch/A/F0D0.c"}) is not None


def test_settings_turn_hack_passes_off():
    import tomllib
    s = tomllib.loads(settings_toml("f"))
    assert (s["func_name"], s["compiler_type"]) == ("f", "ido")
    assert s["weight_overrides"] == {p: 0.0 for p in HACK_PASSES}
    assert all(isinstance(v, float) for v in s["weight_overrides"].values())  # permuter json_dict(..., float)


def test_run_never_stops_on_zero():
    assert "--stop-on-zero" not in (REPO_ROOT / "tools" / "permute.py").read_text()


def _batch_env(tmp_path, monkeypatch, run_rc, seconds=700):
    """A one-row list in TMP_PATH whose `setup` succeeds (baseline 50) and whose `run` exits RUN_RC
    after SECONDS of wall time; no permuter outputs."""
    import argparse
    import subprocess
    from tools import permute
    d = tmp_path / "001_global_f"
    (d / "perm").mkdir(parents=True)

    def run(cmd, **kw):
        if "setup" in cmd:
            write_setup_record(d / "perm", {"func": "f", "baseline_score": 50})
            return subprocess.CompletedProcess(cmd, 0, "", "")
        kw["stdout"].write("permuter: crashed\n" if run_rc else "Wall-clock limit reached\n")
        return subprocess.CompletedProcess(cmd, run_rc)

    clock = iter([0.0, float(seconds)])
    monkeypatch.setattr(permute.subprocess, "run", run)
    monkeypatch.setattr(permute.time, "monotonic", lambda: next(clock))
    row = [str(d), "global", "f", str(d / "x.c"), "src/global/x.c", "global:80600000:dead-if:abc123", "40"]
    (tmp_path / "list.tsv").write_text("\t".join(row) + "\n")
    return permute, d, row, argparse.Namespace(list=str(tmp_path / "list.tsv"), parallel=1, j=2, seconds=900)


def test_batch_row_failed_run_gets_no_ledger_credit(tmp_path, monkeypatch):
    import json
    import threading
    permute, d, row, args = _batch_env(tmp_path, monkeypatch, run_rc=1)
    assert permute.batch_row(row, tmp_path, args, threading.Lock()) is False
    res = json.loads((d / "result.json").read_text())
    assert res["key"] == row[5] and res["error"].startswith("run: exit 1 after 700s: permuter: crashed")
    assert not (tmp_path / "ledger.txt").exists()


def test_batch_row_completed_run_records_nohit(tmp_path, monkeypatch):
    import threading
    permute, d, row, args = _batch_env(tmp_path, monkeypatch, run_rc=0)
    assert permute.batch_row(row, tmp_path, args, threading.Lock()) is True
    line = (tmp_path / "ledger.txt").read_text()
    assert line.startswith(f"{row[5]} permute nohit seconds=700 base=50 best=50 ")


def test_batch_exits_nonzero_when_a_row_fails(tmp_path, monkeypatch, capsys):
    import pytest
    permute, d, row, args = _batch_env(tmp_path, monkeypatch, run_rc=0)

    def boom(*a):
        raise RuntimeError("disk full")

    monkeypatch.setattr(permute, "batch_row", boom)
    with pytest.raises(SystemExit) as ex:
        permute.cmd_batch(args)
    assert ex.value.code == 1
    out = capsys.readouterr().out
    assert f"FAIL {row[5]} exception: RuntimeError: disk full" in out and "1 failed" in out
