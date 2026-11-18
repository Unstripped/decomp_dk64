"""Tests for the data metric helpers of tools/progress.py."""

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from progress import asm_data_size, parse_map_data_sections  # noqa: E402


def test_asm_data_size_counts_every_directive(tmp_path):
    s = tmp_path / "D_80000000.s"
    s.write_text(
        ".section .rodata\n"
        "\n"
        "dlabel D_80000000\n"
        "    /* 0 80000000 00010203 */ .word 0x00010203, 0x04050607\n"
        "    /* 8 80000008 */ .asciz \"a\\\"b\\\\c\\n\\101\\0\"\n"
        "    /* 5741524E */\n"
        ".align 2\n"
        "    /* 14 80000014 */ .byte 0x01, 0x02, 0x03\n"
        "    /* 17 80000017 */ .space 0x5\n"
        "    /* 1C 8000001C */ .short 0x1234\n"
        "enddlabel D_80000000\n",
        encoding="utf-8",
    )
    # 8 words + "a\"b\\c\n\101\0" (8 bytes) + NUL = 17, aligned to 20,
    # then 3 bytes, 5 bytes of space and one short.
    assert asm_data_size(s) == 20 + 3 + 5 + 2


def test_asm_data_size_comma_in_string(tmp_path):
    s = tmp_path / "str.s"
    s.write_text('    .ascii "a,b", "cd"\n', encoding="utf-8")
    assert asm_data_size(s) == 5


def test_parse_map_data_sections_skips_discarded(tmp_path):
    m = tmp_path / "x.map"
    m.write_text(
        "Discarded input sections\n"
        "\n"
        " .data          0x00000000       0x40 build/src/bonus/0.o\n"
        " .rodata        0x00000000       0x10 build/src/bonus/0.o\n"
        "\n"
        "Memory Configuration\n"
        "\n"
        "Linker script and memory map\n"
        "\n"
        " .text          0x80024000      0x100 build/src/bonus/0.o\n"
        " .data          0x8002d860       0x60 build/asm/bonus/data/0.data.o\n"
        " .data          0x8002d8c0        0x0 build/src/bonus/0.o\n"
        " .rodata        0x8002d940      0x350 build/src/bonus/0.o\n",
        encoding="utf-8",
    )
    assert parse_map_data_sections(m) == [
        (".data", 0x8002D860, 0x60, "build/asm/bonus/data/0.data.o"),
        (".rodata", 0x8002D940, 0x350, "build/src/bonus/0.o"),
    ]
