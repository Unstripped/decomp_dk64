import os
import sys
from pathlib import Path
import pytest

# Ensure repository root is on sys.path so tools.objdiff can be imported
REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

import tools.objdiff as objdiff

RODATA_VRAM = 0x80758000
RODATA_SIZE = 0x1000
DATA_VRAM = 0x80759000
DATA_SIZE = 0x1000
BSS_VRAM = 0x8075A000
BSS_SIZE = 0x1000
FAKE_OBJ_PATH = "fake_object.o"


@pytest.fixture(autouse=True)
def mock_sections(monkeypatch):
    """Supply real section sizes and vrams for fake object paths without requiring ELF binaries."""
    sec_sizes = {".rodata": RODATA_SIZE, ".data": DATA_SIZE, ".bss": BSS_SIZE}
    vrams = {".rodata": RODATA_VRAM, ".data": DATA_VRAM, ".bss": BSS_VRAM}
    monkeypatch.setattr(objdiff, "get_section_sizes", lambda obj_path: sec_sizes)
    monkeypatch.setattr(objdiff, "object_section_vrams", lambda obj_path, absolute: vrams)
    return {"sec_sizes": sec_sizes, "vrams": vrams}


def test_paired_hi16_lo16_to_own_rodata():
    """Case 1: Paired HI16/LO16 to an absolute symbol inside own .rodata.

    The reloc target becomes '.rodata' and the immediates encode the section offset;
    the same address expressed as '.rodata'+addend in the 'built' style normalises
    to identical text+relocs.
    """
    offset = 0x0040
    sym_name = "D_80758040"
    absolute = {sym_name: RODATA_VRAM + offset}

    # Expected style (asm): relocations target absolute symbol D_80758040 with 0 immediates:
    # lui $at, 0x0000; lw $v0, 0x0000($at)
    text_exp = (0x3C010000).to_bytes(4, "big") + (0x8C220000).to_bytes(4, "big")
    relocs_exp = [
        (0, "R_MIPS_HI16", sym_name),
        (4, "R_MIPS_LO16", sym_name),
    ]

    # Built style (C / IDO output): relocations target .rodata directly,
    # instructions already encode section offset 0x0040:
    # lui $at, 0x0000; lw $v0, 0x0040($at)
    text_built = (0x3C010000).to_bytes(4, "big") + (0x8C220040).to_bytes(4, "big")
    relocs_built = [
        (0, "R_MIPS_HI16", ".rodata"),
        (4, "R_MIPS_LO16", ".rodata"),
    ]

    # Normalise expected style
    norm_text_exp, norm_relocs_exp = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, text_exp, relocs_exp, absolute
    )

    # Reloc targets become .rodata
    assert norm_relocs_exp == [(0, "R_MIPS_HI16", ".rodata"), (4, "R_MIPS_LO16", ".rodata")]
    # Immediates encode the section offset (HI16: 0x0000, LO16: 0x0040)
    assert norm_text_exp == text_built

    # Normalise built style
    norm_text_built, norm_relocs_built = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, text_built, relocs_built, absolute
    )

    # Both styles normalise to identical text bytes and relocs
    assert norm_text_exp == norm_text_built
    assert norm_relocs_exp == norm_relocs_built


def test_differing_hi16_immediate():
    """Case 2: Two inputs differing ONLY in the HI16 immediate (addend differs by 0x10000).

    Normalised outputs must differ. (This tests the bug fixed in commit 0e86b1cc;
    pre-fix code 7e40c10c ignored the HI16 immediate and collapsed both to identical output).
    """
    offset = 0x0040
    sym_name = "D_80758040"
    absolute = {sym_name: RODATA_VRAM + offset}

    # Input A: HI16 immediate 0x0000, LO16 immediate 0x0000 (addend = 0x0)
    # lui $at, 0x0000; lw $v0, 0x0000($at)
    text_a = (0x3C010000).to_bytes(4, "big") + (0x8C220000).to_bytes(4, "big")
    relocs_a = [
        (0, "R_MIPS_HI16", sym_name),
        (4, "R_MIPS_LO16", sym_name),
    ]

    # Input B: HI16 immediate 0x0001, LO16 immediate 0x0000 (addend = 0x10000)
    # lui $at, 0x0001; lw $v0, 0x0000($at)
    text_b = (0x3C010001).to_bytes(4, "big") + (0x8C220000).to_bytes(4, "big")
    relocs_b = [
        (0, "R_MIPS_HI16", sym_name),
        (4, "R_MIPS_LO16", sym_name),
    ]

    norm_text_a, norm_relocs_a = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, text_a, relocs_a, absolute
    )
    norm_text_b, norm_relocs_b = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, text_b, relocs_b, absolute
    )

    # Reloc targets both become .rodata
    assert norm_relocs_a == [(0, "R_MIPS_HI16", ".rodata"), (4, "R_MIPS_LO16", ".rodata")]
    assert norm_relocs_b == [(0, "R_MIPS_HI16", ".rodata"), (4, "R_MIPS_LO16", ".rodata")]

    # Normalised outputs must differ
    assert norm_text_a != norm_text_b

    # Verify exact returned text bytes:
    # Input A value = offset + 0x0 = 0x0040 -> HI16 field = 0x0000, LO16 field = 0x0040
    assert norm_text_a == (0x3C010000).to_bytes(4, "big") + (0x8C220040).to_bytes(4, "big")
    # Input B value = offset + 0x10000 = 0x10040 -> HI16 field = 0x0001, LO16 field = 0x0040
    assert norm_text_b == (0x3C010001).to_bytes(4, "big") + (0x8C220040).to_bytes(4, "big")


def test_unpaired_hi16_preserves_immediate():
    """Case 3: Unpaired HI16 (no matching LO16).

    Its own immediate is preserved in the computed value (output differs when HI16
    immediate differs).
    """
    offset = 0x0040
    sym_name = "D_80758040"
    absolute = {sym_name: RODATA_VRAM + offset}

    # Input 1: HI16 immediate = 0x0000
    text_1 = (0x3C010000).to_bytes(4, "big")
    relocs_1 = [(0, "R_MIPS_HI16", sym_name)]

    # Input 2: HI16 immediate = 0x0007
    text_2 = (0x3C010007).to_bytes(4, "big")
    relocs_2 = [(0, "R_MIPS_HI16", sym_name)]

    norm_text_1, norm_relocs_1 = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, text_1, relocs_1, absolute
    )
    norm_text_2, norm_relocs_2 = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, text_2, relocs_2, absolute
    )

    # Relocs target .rodata
    assert norm_relocs_1 == [(0, "R_MIPS_HI16", ".rodata")]
    assert norm_relocs_2 == [(0, "R_MIPS_HI16", ".rodata")]

    # Outputs differ because HI16 immediate is preserved
    assert norm_text_1 != norm_text_2

    # Verify exact returned text bytes:
    # Input 1: value = offset + 0x0 = 0x0040 -> field = 0x0000
    assert norm_text_1 == (0x3C010000).to_bytes(4, "big")
    # Input 2: value = offset + (7 << 16) = 0x70040 -> field = ((0x70040 + 0x8000) >> 16) & 0xFFFF = 0x0007
    assert norm_text_2 == (0x3C010007).to_bytes(4, "big")


def test_extern_target_left_untouched():
    """Case 4: A target outside own sections (an extern) is left untouched."""
    # Target address outside .rodata and .data
    extern_addr = 0x80001000
    sym_name = "D_80001000"
    absolute = {sym_name: extern_addr}

    input_text = (0x3C010002).to_bytes(4, "big") + (0x8C220003).to_bytes(4, "big")
    input_relocs = [
        (0, "R_MIPS_HI16", sym_name),
        (4, "R_MIPS_LO16", sym_name),
    ]

    norm_text, norm_relocs = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, input_text, input_relocs, absolute
    )

    # Returned text bytes and relocs are completely untouched
    assert norm_text == input_text
    assert norm_relocs == input_relocs

    # Also verify with a named extern symbol not present in absolute map
    named_extern_relocs = [
        (0, "R_MIPS_HI16", "some_extern_symbol"),
        (4, "R_MIPS_LO16", "some_extern_symbol"),
    ]
    norm_text_named, norm_relocs_named = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, input_text, named_extern_relocs, absolute
    )
    assert norm_text_named == input_text
    assert norm_relocs_named == named_extern_relocs


def test_alias_in_bss_vs_symbol_plus_addend():
    """Case 5: An alias inside .bss (absolute/splat) vs defined symbol + addend.

    When expected asm references an interior alias (e.g. D_8075A062 defined in
    undefined_syms) while C references a base symbol with an addend (e.g.
    D_8075A060 + 0x2), both resolve to the same VRAM address inside .bss and
    normalise to identical .bss-relative text bytes and relocs.
    """
    base_offset = 0x0060
    addend = 0x0002
    alias_offset = base_offset + addend  # 0x0062

    sym_base = f"D_{BSS_VRAM + base_offset:08X}"
    sym_alias = f"D_{BSS_VRAM + alias_offset:08X}"
    absolute = {sym_alias: BSS_VRAM + alias_offset}

    # Expected style: relocations target interior alias with 0 addend in instruction
    text_exp = (0x3C010000).to_bytes(4, "big") + (0xA02F0000).to_bytes(4, "big")
    relocs_exp = [
        (0, "R_MIPS_HI16", sym_base),
        (4, "R_MIPS_LO16", sym_alias),
    ]

    # Built style: relocations target base symbol, instruction encodes addend
    text_built = (0x3C010000).to_bytes(4, "big") + (0xA02F0000 | addend).to_bytes(4, "big")
    relocs_built = [
        (0, "R_MIPS_HI16", sym_base),
        (4, "R_MIPS_LO16", sym_base),
    ]

    norm_text_exp, norm_relocs_exp = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, text_exp, relocs_exp, absolute
    )
    norm_text_built, norm_relocs_built = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, text_built, relocs_built, absolute
    )

    # Both targets become .bss
    assert norm_relocs_exp == [(0, "R_MIPS_HI16", ".bss"), (4, "R_MIPS_LO16", ".bss")]
    assert norm_relocs_built == [(0, "R_MIPS_HI16", ".bss"), (4, "R_MIPS_LO16", ".bss")]

    # Both encode identical section offsets
    assert norm_text_exp == norm_text_built
    assert norm_relocs_exp == norm_relocs_built


def test_different_bss_addresses_differ():
    """Case 6: References to different addresses in .bss must remain different.

    Genuine differences in .bss targets (e.g. D_8075A062 vs D_8075A060 + 0x3)
    must produce different normalised text immediates.
    """
    base_offset = 0x0060
    sym_base = f"D_{BSS_VRAM + base_offset:08X}"
    alias_offset = base_offset + 0x0002
    sym_alias = f"D_{BSS_VRAM + alias_offset:08X}"
    absolute = {sym_alias: BSS_VRAM + alias_offset}

    # Input 1 targets alias at offset 0x0062
    text_1 = (0x3C010000).to_bytes(4, "big") + (0xA02F0000).to_bytes(4, "big")
    relocs_1 = [
        (0, "R_MIPS_HI16", sym_base),
        (4, "R_MIPS_LO16", sym_alias),
    ]

    # Input 2 targets base symbol + addend 0x0003 (offset 0x0063)
    text_2 = (0x3C010000).to_bytes(4, "big") + (0xA02F0003).to_bytes(4, "big")
    relocs_2 = [
        (0, "R_MIPS_HI16", sym_base),
        (4, "R_MIPS_LO16", sym_base),
    ]

    norm_text_1, norm_relocs_1 = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, text_1, relocs_1, absolute
    )
    norm_text_2, norm_relocs_2 = objdiff.normalise_own_section_relocs(
        FAKE_OBJ_PATH, text_2, relocs_2, absolute
    )

    # Both targets become .bss
    assert norm_relocs_1 == [(0, "R_MIPS_HI16", ".bss"), (4, "R_MIPS_LO16", ".bss")]
    assert norm_relocs_2 == [(0, "R_MIPS_HI16", ".bss"), (4, "R_MIPS_LO16", ".bss")]

    # But normalised text must differ due to differing offsets (0x0062 vs 0x0063)
    assert norm_text_1 != norm_text_2


def _reloc_objects(monkeypatch, built, expected, syms=None):
    """Fake objects: {path: (text, relocs)}; .data/.rodata empty in both."""
    objs = {"built.o": built, "expected/build/src/global/x.o": expected}
    monkeypatch.setattr(objdiff, "get_section_bytes",
                        lambda p, sec: objs[p][0] if sec == ".text" else b"")
    monkeypatch.setattr(objdiff, "get_text_relocs", lambda p: objs[p][1])
    monkeypatch.setattr(objdiff, "symbol_addresses", lambda p: dict(syms or {}))
    return "built.o", "expected/build/src/global/x.o"


def _hi_lo(hi, lo):
    # lui $at, hi; lbu $v0, lo($at)
    return (0x3C010000 | hi).to_bytes(4, "big") + (0x90220000 | (lo & 0xFFFF)).to_bytes(4, "big")


def test_reloc_equivalent_split_splat_label(monkeypatch):
    """`D_807506D0 + 5` (C indexes the array) vs expected's split label `D_807506D5`."""
    b, e = _reloc_objects(monkeypatch,
                          (_hi_lo(0, 5), [(0, "R_MIPS_HI16", "D_807506D0"), (4, "R_MIPS_LO16", "D_807506D0")]),
                          (_hi_lo(0, 0), [(0, "R_MIPS_HI16", "D_807506D5"), (4, "R_MIPS_LO16", "D_807506D5")]))
    assert objdiff.reloc_equivalent(b, e)


def test_reloc_equivalent_named_symbol(monkeypatch):
    b, e = _reloc_objects(monkeypatch,
                          (_hi_lo(0, 5), [(0, "R_MIPS_HI16", "gTable"), (4, "R_MIPS_LO16", "gTable")]),
                          (_hi_lo(0, 0), [(0, "R_MIPS_HI16", "D_807506D5"), (4, "R_MIPS_LO16", "D_807506D5")]),
                          {"gTable": 0x807506D0})
    assert objdiff.reloc_equivalent(b, e)


@pytest.mark.parametrize("built_lo, syms", [(4, {}), (5, None)])
def test_reloc_equivalent_rejects_other_address_or_unknown_symbol(monkeypatch, built_lo, syms):
    name = "D_807506D0" if syms is not None else "gUnknown"
    b, e = _reloc_objects(monkeypatch,
                          (_hi_lo(0, built_lo), [(0, "R_MIPS_HI16", name), (4, "R_MIPS_LO16", name)]),
                          (_hi_lo(0, 0), [(0, "R_MIPS_HI16", "D_807506D5"), (4, "R_MIPS_LO16", "D_807506D5")]),
                          syms)
    assert not objdiff.reloc_equivalent(b, e)


def test_reloc_equivalent_rejects_different_instruction(monkeypatch):
    text_b = (0x3C010000).to_bytes(4, "big") + (0x8C220005).to_bytes(4, "big")  # lw, not lbu
    b, e = _reloc_objects(monkeypatch,
                          (text_b, [(0, "R_MIPS_HI16", "D_807506D0"), (4, "R_MIPS_LO16", "D_807506D0")]),
                          (_hi_lo(0, 0), [(0, "R_MIPS_HI16", "D_807506D5"), (4, "R_MIPS_LO16", "D_807506D5")]))
    assert not objdiff.reloc_equivalent(b, e)
