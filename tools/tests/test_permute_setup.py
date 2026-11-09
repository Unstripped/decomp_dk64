"""Regression tests for tools/permute.py setup: single-function target and same-line wrapping."""

import struct
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools.permute import function_asm_from_object, wrap_multi_statement_lines


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
