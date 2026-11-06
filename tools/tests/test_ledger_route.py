import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
for p in (REPO_ROOT, REPO_ROOT / "tools"):
    if str(p) not in sys.path:
        sys.path.insert(0, str(p))

from tools import ledger  # noqa: E402

quirks = ledger.quirks


def ev(outcome="attempted", day=1, fp=None, score=None, approx=False, stage=None):
    return dict(type="attempt", outcome=outcome, ts=f"2026-11-{day:02d}T00:00:00Z", agent="A",
                fp=fp, score=None if score is None else dict(full=score, text=0, reloc=0, shape=0),
                approx=approx, stage=stage)


def test_fresh_functions_go_to_finish():
    assert ledger.decide([], "x") == ("finish", "never attempted")
    assert ledger.decide([ev(day=1), ev(day=2)], "x")[0] == "finish"
    assert ledger.decide([ev(day=1), ev(day=2), ev(day=3)], "x")[0] == "strong"


def test_skipped_and_approx_neither_count_nor_become_last():
    events = [ev(day=1), ev(day=2), ev("skipped", day=3), ev(day=4, approx=True)]
    assert ledger.decide(events, "x") == ("finish", "2 tries")
    # a skipped event carrying the current fp must not block
    events = [ev(day=1, fp="y"), ev("skipped", day=2, fp="x")]
    assert ledger.decide(events, "x")[0] == "finish"


def test_same_evidence_blocks_unless_forced():
    events = [ev(day=1), ev(day=2), ev(day=3, fp="x")]
    tier, reason = ledger.decide(events, "x")
    assert tier == "blocked" and reason.startswith("no new evidence since 2026-11-03")
    tier, reason = ledger.decide(events, "x", force=True)
    assert tier == "strong" and reason.startswith("forced; ")
    assert ledger.decide(events, "z")[0] == "strong"


def test_parked_with_same_evidence_blocks():
    assert ledger.decide([ev("parked", fp="x")], "x")[0] == "blocked"


def test_missing_fingerprint_never_blocks():
    assert ledger.decide([ev(fp=None)], None)[0] == "finish"


def test_blocked_outcome_blocks():
    tier, reason = ledger.decide([ev(day=1), ev("blocked", day=2)], "x")
    assert tier == "blocked" and "split/data" in reason


def test_close_improvement_returns_to_finish():
    base = [ev(day=d) for d in (1, 2, 3)]
    assert ledger.decide(base + [ev(day=4, score=30), ev(day=5, score=6)], "x")[0] == "finish"
    assert ledger.decide(base + [ev(day=4, score=30), ev(day=5, score=12)], "x")[0] == "strong"
    assert ledger.decide(base + [ev(day=4, score=6), ev(day=5, score=6)], "x")[0] == "strong"
    # the improvement must be the last attempt's
    assert ledger.decide(base + [ev(day=4, score=30), ev(day=5, score=6), ev(day=6)], "x")[0] == "strong"


def _draft(root, header, body):
    d = root / "drafts" / "global"
    d.mkdir(parents=True, exist_ok=True)
    (d / "func_80000000.c").write_text(f"{header}\n{body}\n")


def test_fingerprint_tracks_evidence(tmp_path, monkeypatch):
    monkeypatch.setattr(ledger, "ROOT", str(tmp_path))
    ido = tmp_path / "ido"
    quirks.add_entry(ido, "unrelated", "cfe", ["loop"], "body", functions=["other"])
    corpus = quirks.load(ido)

    def fp(rest=""):
        return ledger.fingerprint("global", "func_80000000", rest, quirks.load(ido))

    _draft(tmp_path, "// func_80000000 (src/global/a.c): note one", "void f(void) {}")
    first = fp()
    _draft(tmp_path, "// func_80000000 (src/global/a.c): note two", "void f(void) {}")
    assert fp() == first
    _draft(tmp_path, "// func_80000000 (src/global/a.c): note two", "void f(void) { g(); }")
    assert fp() != first

    assert fp("next: a  b") == fp("next: a b")
    assert fp("next: x") != fp("next: y")

    before = ledger.fingerprint("global", "func_80000000", "", corpus)
    quirks.add_entry(ido, "about it", "cfe", ["loop"], "body", functions=["func_80000000"])
    assert fp() != before


def test_unrouted_respawn_hides_older_routed_spawn(tmp_path, monkeypatch):
    import json
    spawns = tmp_path / "spawns.jsonl"
    monkeypatch.setattr(ledger, "SPAWNS", str(spawns))
    routed = dict(agent="A", ts="2026-11-01T00:00:00Z", model="m", functions=[{"seg": "global", "vram": "0x1", "fp": "f"}])
    spawns.write_text(json.dumps(routed) + "\n")
    assert ledger.spawn_for("A", "2026-11-02T00:00:00Z")["model"] == "m"
    unrouted = dict(agent="A", ts="2026-11-03T00:00:00Z", model=None, functions=[])
    spawns.write_text(json.dumps(routed) + "\n" + json.dumps(unrouted) + "\n")
    assert ledger.spawn_for("A", "2026-11-04T00:00:00Z") is None
    # a record before the unrouted respawn still sees the routed one
    assert ledger.spawn_for("A", "2026-11-02T00:00:00Z")["model"] == "m"
