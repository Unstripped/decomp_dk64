import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import ringfifo as rf  # noqa: E402


def _ins(*lines):
    return [d for d in (rf.decode(line) for line in lines) if d]


def test_ring_hands_out_t0_t2_after_t9():
    # 136820 faultDrawRegs (2026-11-18c M28): $8/$9/$10 after $25 and before $11
    ins = _ins("lw $14, 0($4)", "lw $15, 4($4)", "lw $24, 8($4)", "lw $25, 12($4)", "lw $8, 16($4)",
               "addu $9, $14, $15", "addu $10, $24, $25", "addu $11, $9, $10", "addu $12, $11, $8",
               "sw $12, 0($5)")
    ring, ex, inferred = rf.ring_for(ins)
    assert ring == [14, 15, 24, 25, 8, 9, 10, 11, 12, 13] and not ex and not inferred
    assert rf.simulate(ins, ring)[1] == []
    # a t0 the target allocates out of FIFO order: inferred uopt-coloured, not silently ignored
    assert rf.ring_for(_ins("lw $14, 0($4)", "lw $15, 4($4)", "lw $24, 8($4)", "lw $25, 12($4)",
                            "lw $9, 16($4)", "sw $9, 0($5)"))[2] == [(8, 4, "skipped")]


def test_single_block_t0_t2_web_is_inferred():
    ins = _ins("li $10, 683", "lw $14, 0($4)", "div $15, $14, $10", "sw $15, 0($5)")
    ring, ex, inferred = rf.ring_for(ins)
    assert 10 not in ring and inferred == [(10, 0, "allocated out of FIFO order")]
    assert rf.simulate(ins, ring)[1] == []


def test_t3_t5_mismatches_stay_reported():
    ins = _ins("lw $11, 0($4)", "sw $11, 0($5)")
    ring, _, inferred = rf.ring_for(ins)
    assert inferred == [] and rf.simulate(ins, ring)[1] == [(0, 11, 14)]
