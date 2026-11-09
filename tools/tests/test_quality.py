import json
import re
import sys
from pathlib import Path

import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import quality as q  # noqa: E402

FP = ("1111111111111111", "2222222222222222")
SITE = dict(key="global:80600000:dead-if:abc123", kind="dead-if", name="f", line=3, lines=[2], tagged=True,
            code="if (x) {} // FAKE")
FN = dict(name="f", seg="global", vram=0x80600000, fp_local=FP[0], fp_hdr=FP[1], sites=[])
REVIEW = "fake=0/0 goto=0 casts=0 views=ok protos=ok temps=ok names=0 uninit=0"


def ev(site, method, outcome, fp=FP, note=None, **kw):
    e = dict(type="quality", t="2026-01-01T00:00:00Z", unit="u", agent="a", seg="global", vram="80600000",
             name="f", file="src/global/x.c", site=site["key"] if site else None,
             kind=site["kind"] if site else None, method=method, outcome=outcome, fp_local=fp[0], fp_hdr=fp[1],
             quirks=[], seconds=None, base=None, best=None, commit=None, note=note)
    e.update(kw)
    return e


@pytest.fixture(autouse=True)
def no_new_knowledge(monkeypatch):
    monkeypatch.setattr(q, "knowledge_after", lambda name, note, t: False)


def class1_events():
    return [ev(SITE, "remove", "nohit"), ev(SITE, "cond", "nohit"), ev(SITE, "classify", "kept", note="class 1")]


def test_dead_if_class1_is_exhausted():
    done, nxt, marks = q.exhausted(SITE, class1_events(), FP)
    assert (done, nxt) == (True, None)
    assert [marks[m] for m in ("remove", "cond", "classify")] == ["✓"] * 3


def test_changed_header_fingerprint_is_stale():
    done, nxt, marks = q.exhausted(SITE, class1_events(), (FP[0], "changed"))
    assert (done, nxt) == (False, "remove")
    assert marks["remove"] == "stale"


def test_class2_site_needs_permute():
    evs = [ev(SITE, "remove", "nohit"), ev(SITE, "cond", "nohit"), ev(SITE, "classify", "nohit", note="class 2"),
           ev(SITE, "diagnose", "nohit", quirks=["Q0001"])]
    assert q.exhausted(SITE, evs, FP)[:2] == (False, "permute")


def test_function_without_sites_needs_review():
    st = q.function_state(FN, {}, {})
    assert (st["done"], st["next"]) == (False, "review")
    st = q.function_state(FN, {}, {("global", "80600000"): [ev(None, "review", "nohit", note=REVIEW)]})
    assert (st["done"], st["next"]) == (True, None)


def test_untagged_dead_if_site(tmp_path, monkeypatch):
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    c = tmp_path / "x.c"
    c.write_text("typedef int s32;\ns32 g;\nvoid f(s32 x) {\n    if (x) {}\n    g = x;\n"
                 "    if (g) {} // FAKE: steers\n}\n")
    fn, = q.analyze(str(c), "global")["functions"]
    untagged = [s for s in fn["sites"] if not s["tagged"]]
    tagged = [s for s in fn["sites"] if s["tagged"]]
    assert [(s["kind"], s["line"]) for s in untagged] == [("dead-if", 4)]
    assert re.fullmatch(r"global:80600000:dead-if:u[0-9a-f]{5}", untagged[0]["key"])
    assert [(s["kind"], s["line"]) for s in tagged] == [("dead-if", 6)]
    assert not tagged[0]["key"].split(":")[3].startswith("u")


def test_record_rejects_short_permute_and_kept_remove(tmp_path, monkeypatch, capsys):
    ledger_path = tmp_path / "quality.jsonl"
    monkeypatch.setattr(q, "LEDGER", str(ledger_path))
    batch = tmp_path / "batch.txt"
    batch.write_text(f"{SITE['key']} permute nohit seconds=300 base=10 best=8\n{SITE['key']} remove kept\n")
    with pytest.raises(SystemExit) as ex:
        q.main(["record", "--unit", "u", "--agent", "a", "--batch", str(batch)])
    assert ex.value.code == 1
    assert not ledger_path.exists()
    err = capsys.readouterr().err
    assert "line 1" in err and "seconds>=600" in err
    assert "line 2" in err and "kept is only for classify" in err


def test_record_writes_full_schema(tmp_path, monkeypatch):
    ledger_path = tmp_path / "quality.jsonl"
    monkeypatch.setattr(q, "LEDGER", str(ledger_path))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), SITE))
    batch = tmp_path / "batch.txt"
    batch.write_text(f'{SITE["key"]} diagnose nohit quirks=Q0001,Q0002 note="regalloc"\n')
    q.main(["record", "--unit", "u1", "--agent", "a", "--batch", str(batch)])
    unit, e = [json.loads(x) for x in ledger_path.read_text().splitlines()]
    assert unit["type"] == "unit" and unit["unit"] == "u1" and unit["commit"]
    assert set(e) == set(ev(SITE, "diagnose", "nohit"))
    assert (e["site"], e["kind"], e["quirks"], e["fp_local"]) == (SITE["key"], "dead-if", ["Q0001", "Q0002"], FP[0])


def test_record_accepts_permute_stopped_on_zero(tmp_path, monkeypatch):
    ledger_path = tmp_path / "quality.jsonl"
    monkeypatch.setattr(q, "LEDGER", str(ledger_path))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), SITE))
    batch = tmp_path / "batch.txt"
    batch.write_text(f'{SITE["key"]} permute nohit seconds=145 base=90 best=0 note="zero only via a hack"\n')
    q.main(["record", "--unit", "u1", "--agent", "a", "--batch", str(batch)])
    assert json.loads(ledger_path.read_text().splitlines()[-1])["seconds"] == 145
