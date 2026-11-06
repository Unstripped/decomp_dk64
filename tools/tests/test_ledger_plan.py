import random
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
for p in (REPO_ROOT, REPO_ROOT / "tools"):
    if str(p) not in sys.path:
        sys.path.insert(0, str(p))

from tools import ledger  # noqa: E402

FLASH = ledger.ARMS["flash"]["model"].split(":")[0]
SONNET = ledger.ARMS["sonnet"]["model"]


def ev(outcome, model, day, approx=False):
    return dict(type="attempt", outcome=outcome, model=model, ts=f"2026-11-{day:02d}T00:00:00Z", approx=approx)


def test_cells_bucket_by_prior_tries_and_skip_non_trials():
    key = ("global", 1)
    events = [ev("attempted", FLASH, 1), ev("skipped", FLASH, 2), ev("attempted", None, 3),
              ev("attempted", SONNET, 4, approx=True), ev("parked", SONNET, 5), ev("matched", SONNET, 6)]
    cells, arm_tot, _ = ledger.bandit_cells({key: events}, {key: 100})
    # flash tried first (0 prior tries); the unknown-model attempt still counts as a try;
    # skipped and approximate events are neither trials nor tries
    assert cells[("flash", "0", "s")] == [0, 1]
    assert cells[("sonnet", "1-2", "s")] == [0, 1]
    assert cells[("sonnet", "3-5", "s")] == [1, 0]
    assert arm_tot == {"flash": [0, 1], "sonnet": [1, 1]}


def mean_theta(arm, fails, cells, arm_tot, bucket_tot, n=4000):
    rng = random.Random(0)
    b = ("6+", "m")
    return sum(ledger.sample_theta(rng, arm, b, fails, cells, arm_tot, bucket_tot) for _ in range(n)) / n


def test_own_failures_lower_that_arm_for_the_function():
    cells = {("sonnet", "6+", "m"): [3, 7]}
    arm_tot = {"sonnet": [30, 70]}
    bucket_tot = {("6+", "m"): [3, 7], ("0", "s"): [30, 70]}
    fresh = mean_theta("sonnet", 0, cells, arm_tot, bucket_tot)
    tried = mean_theta("sonnet", 15, cells, arm_tot, bucket_tot)
    assert tried < fresh * 0.75


def test_arm_without_data_uses_configured_prior():
    bucket_tot = {("6+", "m"): [1, 1]}
    assert abs(ledger.cell_prior("fable", ("6+", "m"), {}, bucket_tot) - ledger.ARMS["fable"]["prior"]) < 1e-9


def test_recorded_selectors_map_to_arms_regardless_of_level():
    assert ledger.arm_of("anthropic/claude-sonnet-5-5:medium") == "sonnet"
    assert ledger.arm_of("google-antigravity/gemini-3.8-flash") == "flash"
    assert ledger.arm_of("someone/else") is None



def test_soft_rule_makes_cheap_arms_dearer_only_on_heavily_tried_functions():
    hard = ledger.SINGLE_TRIES
    assert ledger.arm_cost("sonnet", hard) == ledger.ARMS["sonnet"]["cost"] * ledger.HARD_COST_MULT
    assert ledger.arm_cost("sonnet", hard - 1) == ledger.ARMS["sonnet"]["cost"]
    assert ledger.arm_cost("astra", hard) == ledger.ARMS["astra"]["cost"]


def test_thinking_level_selects_its_own_arm():
    assert ledger.arm_of("anthropic/claude-sonnet-5-5:xhigh") == "sonnet_xhigh"
    assert ledger.arm_of("anthropic/claude-sonnet-5-5:high") == "sonnet"
    assert ledger.arm_of("anthropic/claude-sonnet-5-5") == "sonnet"


def test_arm_without_data_borrows_its_sibling_rate():
    bucket_tot = {("6+", "m"): [1, 1]}
    arm_tot = {"sonnet": [9, 1]}
    assert ledger.cell_prior("sonnet_xhigh", ("6+", "m"), arm_tot, bucket_tot) == \
        ledger.cell_prior("sonnet", ("6+", "m"), arm_tot, bucket_tot)


def test_session_model_replays_model_and_level_changes():
    t = lambda h: ledger._when(f"2026-11-06T{h:02d}:00:00Z")
    changes = [(t(1), "anthropic/claude-opus-5-5", None), (t(1), None, "medium"),
               (t(2), None, "xhigh"), (t(3), "anthropic/claude-sonnet-5-5", None)]
    assert ledger.session_model(changes, t(2)) == "anthropic/claude-opus-5-5:xhigh"
    assert ledger.session_model(changes, t(4)) == "anthropic/claude-sonnet-5-5:xhigh"


def session(changes, msgs):
    t = lambda h, m=0: ledger._when(f"2026-11-06T{h:02d}:{m:02d}:00Z")
    return t, dict(changes=[(t(*c[0]), c[1], c[2]) for c in changes],
                   msgs=[(t(*x[0]), x[1], x[2], x[3]) for x in msgs])


SONNET_MSG = "anthropic/claude-sonnet-5-5"
RECORD = '{"command": "python3 tools/ledger.py record --unit U --agent orchestrator --seg global funcA"}'


def test_orchestrator_model_from_the_record_call_of_that_function():
    t, s = session([((1,), SONNET_MSG, None), ((1,), None, "xhigh")],
                   [((2,), SONNET_MSG, "working on funcA", []), ((3,), SONNET_MSG, "", [RECORD])])
    assert ledger.orchestrator_model(s, "funcA", t(3)) == "anthropic/claude-sonnet-5-5:xhigh"


def test_orchestrator_model_needs_a_record_call_naming_the_function():
    unrelated = '{"command": "python3 tools/ledger.py record --unit U --agent orchestrator --seg global funcB"}'
    t, s = session([((1,), SONNET_MSG, None), ((1,), None, "xhigh")],
                   [((2,), SONNET_MSG, "funcA looks hard", []), ((3,), SONNET_MSG, "", [unrelated])])
    assert ledger.orchestrator_model(s, "funcA", t(3)) is None


def test_orchestrator_model_unknown_when_model_changed_mid_work():
    t, s = session([((1,), "anthropic/claude-opus-5-5", None), ((2, 30), SONNET_MSG, None)],
                   [((2,), "anthropic/claude-opus-5-5", "funcA first look", []), ((3,), SONNET_MSG, "", [RECORD])])
    assert ledger.orchestrator_model(s, "funcA", t(3)) is None
