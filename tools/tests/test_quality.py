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
REVIEW = "fake=0/0 goto=0 casts=0 views=ok protos=ok temps=ok names=0 uninit=0 warn=0"


def ev(site, method, outcome, fp=FP, note=None, **kw):
    e = dict(type="quality", t="2026-01-01T00:00:00Z", unit="u", agent="a", seg="global", vram="80600000",
             name="f", file="src/global/x.c", site=site["key"] if site else None,
             kind=site["kind"] if site else None, method=method, outcome=outcome, fp_local=fp[0], fp_hdr=fp[1],
             fp_hdr2=None, quirks=[], seconds=None, base=None, best=None, commit=None, note=note)
    e.update(kw)
    return e


@pytest.fixture(autouse=True)
def no_new_knowledge(monkeypatch):
    monkeypatch.setattr(q, "knowledge_after", lambda name, note, t: False)


@pytest.fixture(autouse=True)
def no_compile(monkeypatch):
    """analyze() would compile through tools/dk; tests see no cfe warnings unless they patch them in."""
    monkeypatch.setattr(q.cwarn, "collect", lambda items: [[] for _ in items])


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


@pytest.mark.parametrize("agent,ok", [("Clean12E800.SnXxx", True), ("a.b.c", True), ("a b", False),
                                      ("a/b", False), ("a.", False), (".a", False)])
def test_record_agent_ids(tmp_path, monkeypatch, agent, ok):
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality.jsonl"))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), SITE))
    batch = tmp_path / "batch.txt"
    batch.write_text(f'{SITE["key"]} diagnose nohit quirks=Q0001\n')
    if ok:
        q.main(["record", "--unit", "u1", "--agent", agent, "--batch", str(batch)])
        assert json.loads((tmp_path / "quality.jsonl").read_text().splitlines()[-1])["agent"] == agent
    else:
        with pytest.raises(SystemExit):
            q.main(["record", "--unit", "u1", "--agent", agent, "--batch", str(batch)])


def test_record_accepts_permute_stopped_on_zero(tmp_path, monkeypatch):
    ledger_path = tmp_path / "quality.jsonl"
    monkeypatch.setattr(q, "LEDGER", str(ledger_path))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), SITE))
    batch = tmp_path / "batch.txt"
    batch.write_text(f'{SITE["key"]} permute nohit seconds=145 base=90 best=0 note="zero only via a hack"\n')
    q.main(["record", "--unit", "u1", "--agent", "a", "--batch", str(batch)])
    assert json.loads(ledger_path.read_text().splitlines()[-1])["seconds"] == 145


def _toks(tmp_path, name, text):
    p = tmp_path / name
    p.write_text(text)
    return q.file_tokens(q.clint.parse(str(p)), str(p))


def _equiv(tmp_path, old, new, addr_new=lambda n: None):
    return q.rename_equivalent(_toks(tmp_path, "old.c", old), _toks(tmp_path, "new.c", new),
                               lambda n: q.sym_addr("global", n, None) if n.startswith("D_") else None, addr_new)


def test_rename_equivalent_accepts_declared_name_renames(tmp_path):
    assert _equiv(tmp_path, "int f(int x) { return x; /* a */ }", "int f(int count) { return count; // b\n}")
    s = "struct S { int a; int b; };\nint f(struct S *p) { return p->%s; }\n"
    assert _equiv(tmp_path, s % "a", s.replace("int a;", "int count;") % "count")
    g = "extern int %s;\nint f(void) { return %s; }\n"
    assert _equiv(tmp_path, g % ("D_80001000", "D_80001000"), g % ("menuFade", "menuFade"),
                  addr_new={"menuFade": 0x80001000}.get)


@pytest.mark.parametrize("old,new", [
    ("int f(int x) { return x; }", "unsigned f(unsigned x) { return x; }"),  # keyword type change
    ("typedef int s32;\ntypedef unsigned u32;\ns32 f(s32 x) { return x; }",
     "typedef int s32;\ntypedef unsigned u32;\nu32 f(u32 x) { return x; }"),  # typedef name change
    ("int f(int x) { if (x) return 1; return 0; }", "int f(int x) { while (x) return 1; return 0; }"),
    ("struct S { int a; int b; };\nint f(struct S *p) { return p->a; }",
     "struct S { int a; int b; };\nint f(struct S *p) { return p->b; }"),  # another field, same type
    ("int f(int a, int b) { return a + b; }", "int f(int a, int b) { return b + b; }"),
    ("int f(short x) { return x; }", "int f(short y) { return y + 0; }"),
])
def test_rename_equivalent_rejects_semantic_changes(tmp_path, old, new):
    assert not _equiv(tmp_path, old, new)


def test_rename_equivalent_checks_global_addresses(tmp_path):
    g = "extern int %s;\nint f(void) { return %s; }\n"
    assert not _equiv(tmp_path, g % ("D_80001000", "D_80001000"), g % ("menuFade", "menuFade"),
                      addr_new={"menuFade": 0x80002000}.get)
    assert not _equiv(tmp_path, g % ("D_80001000", "D_80001000"), g % ("menuFade", "menuFade"))


def _git(repo, *args):
    import subprocess
    return subprocess.run(["git", *args], cwd=repo, capture_output=True, text=True, check=True).stdout.strip()


def test_carry_end_to_end(tmp_path, monkeypatch, capsys):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality.jsonl"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    src = repo / "src" / "global" / "x.c"
    body = "int g;\nint f(int x) {\n    int %s;\n    %s = x + g;\n    if (%s) {} // FAKE: steers\n    return %s;\n}\n"
    src.write_text(body % (("y",) * 4))
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "a")
    rev_a = _git(repo, "rev-parse", "HEAD")
    fn = dict(q.analyze("src/global/x.c", "global")["functions"][0], file="src/global/x.c")
    site = fn["sites"][0]
    q.append_events([q.event("u1", "a", fn, None, "review", "nohit", note="fake=1/0"),
                     q.event("u1", "a", fn, site, "diagnose", "nohit", quirks=["Q0001"])])

    src.write_text(body % (("total",) * 4))  # pure local rename
    _git(repo, "commit", "-qam", "b")
    rev_b = _git(repo, "rev-parse", "HEAD")
    q.main(["carry", "--rev", rev_a, "--unit", "u2"])
    new = q.analyze("src/global/x.c", "global")["functions"][0]
    carried = [e for e in q.load_events() if e.get("agent") == "carry"]
    assert {(e["method"], e["site"]) for e in carried} == {("review", None), ("diagnose", new["sites"][0]["key"])}
    assert new["sites"][0]["key"] != site["key"] and all(e["fp_local"] == new["fp_local"] for e in carried)
    by_site, by_func = q.index_events(q.load_events())
    assert q.function_state(dict(new, file="src/global/x.c"), by_site, by_func)["review"] == "✓"

    src.write_text((body % (("total",) * 4)).replace("int total;", "unsigned total;"))  # type change
    _git(repo, "commit", "-qam", "c")
    before = len(q.load_events())
    capsys.readouterr()
    q.main(["carry", "--rev", rev_b, "--unit", "u3"])
    assert "f: not a pure rename" in capsys.readouterr().out
    assert len(q.load_events()) == before


def test_record_dry_run_validates_without_writing(tmp_path, monkeypatch, capsys):
    ledger_path = tmp_path / "quality.jsonl"
    ledger_path.write_text('{"type": "unit", "unit": "u0"}\n')
    before = ledger_path.read_bytes()
    monkeypatch.setattr(q, "LEDGER", str(ledger_path))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), SITE))
    good = tmp_path / "good.txt"
    good.write_text(f'{SITE["key"]} diagnose nohit quirks=Q0001\n')
    q.main(["record", "--unit", "u1", "--agent", "a", "--batch", str(good), "--dry-run"])
    assert "would record 1 events" in capsys.readouterr().out
    assert ledger_path.read_bytes() == before
    bad = tmp_path / "bad.txt"
    bad.write_text(f"{SITE['key']} remove kept\n")
    errs = []
    for extra in (["--dry-run"], []):
        with pytest.raises(SystemExit) as ex:
            q.main(["record", "--unit", "u1", "--agent", "a", "--batch", str(bad), *extra])
        assert ex.value.code == 1
        errs.append(capsys.readouterr().err)
    assert errs[0] == errs[1] and "kept is only for classify" in errs[0]
    assert ledger_path.read_bytes() == before


def test_carry_across_unrelated_file_scope_changes(tmp_path, monkeypatch, capsys):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality.jsonl"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: {"f": 0x80600000, "h": 0x80600100}[name])
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    src = repo / "src" / "global" / "x.c"
    tail = ("int f(ViewA *p) {\n    if (p->a) {} // FAKE: steers\n    return p->a;\n}\n"
            "int h(ViewB *p) {\n    return p->b;\n}\n")
    src.write_text("typedef struct { int a; } ViewA;\ntypedef struct { int b; } ViewB;\n"
                   "typedef struct { int c; } ViewC;\n" + tail)
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "a")
    rev_a = _git(repo, "rev-parse", "HEAD")
    fns = {fn["name"]: dict(fn, file="src/global/x.c") for fn in q.analyze("src/global/x.c", "global")["functions"]}
    q.append_events([q.event("u1", "a", fns["f"], None, "review", "nohit", note="fake=1/0"),
                     q.event("u1", "a", fns["f"], fns["f"]["sites"][0], "diagnose", "nohit", quirks=["Q0001"]),
                     q.event("u1", "a", fns["h"], None, "review", "nohit", note="fake=0/0")])

    # ViewC (used by nobody) deleted, ViewB (used by h) changed layout; f's body and ViewA untouched
    src.write_text("typedef struct { int a; } ViewA;\ntypedef struct { int pad; int b; } ViewB;\n" + tail)
    _git(repo, "commit", "-qam", "b")
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2"])
    out = capsys.readouterr().out
    carried = [e for e in q.load_events() if e.get("agent") == "carry"]
    assert {(e["name"], e["method"]) for e in carried} == {("f", "review"), ("f", "diagnose")}
    assert all("unrelated file-scope changes only" in e["note"] for e in carried)
    assert "h: not a pure rename" in out
    new = {fn["name"]: dict(fn, file="src/global/x.c") for fn in q.analyze("src/global/x.c", "global")["functions"]}
    by_site, by_func = q.index_events(q.load_events())
    assert q.function_state(new["f"], by_site, by_func)["review"] == "✓"
    assert q.function_state(new["h"], by_site, by_func)["review"] != "✓"


_real_knowledge_after = q.knowledge_after


def test_review_freshness_ignores_checklist_tokens(monkeypatch):
    calls = []

    def related(corpus, name, note):
        calls.append(note)
        paths = {"knowledge/ido/entries/Q9001.md"} if note else set()  # broad entry: top-8 for any note
        if name == "named":
            paths.add("knowledge/ido/entries/Q9002.md")
        return paths

    times = {"knowledge/ido/entries/Q9001.md": "2026-02-01T00:00:00Z",
             "knowledge/ido/entries/Q9002.md": "2026-02-01T00:00:00Z"}
    monkeypatch.setattr(q, "_know", {"times": times, "newest": max(times.values()), "corpus": []})
    monkeypatch.setattr(q.ledger, "related_knowledge", related)
    t = "2026-01-01T00:00:00Z"
    assert q.note_text(REVIEW) is None
    assert not _real_knowledge_after("f", REVIEW, t)  # checklist only: name-based check only
    assert calls[-1] is None
    assert _real_knowledge_after("named", REVIEW, t)  # a file naming the function still stales it
    assert _real_knowledge_after("f", "regalloc swap " + REVIEW, t)  # free text still searched
    assert calls[-1] == "regalloc swap"


def test_note_hits_stale_only_diagnose_permute_reconstruct(monkeypatch):
    # Q0589/Q0118: a broad entry matching a review's prose (`re-read`, `steer`) staled reviews
    monkeypatch.setattr(q, "knowledge_after", _real_knowledge_after)
    monkeypatch.setattr(q.ledger, "related_knowledge", lambda corpus, name, note: (
        {"knowledge/ido/entries/Q9001.md"} if note else set()) | (
        {"knowledge/ido/entries/Q9002.md"} if name == "named" else set()))
    times = {"knowledge/ido/entries/Q9001.md": "2026-02-01T00:00:00Z",
             "knowledge/ido/entries/Q9002.md": "2026-02-01T00:00:00Z"}
    monkeypatch.setattr(q, "_know", {"times": times, "newest": max(times.values()), "corpus": []})
    note = "re-read after the steer fix " + REVIEW
    for m in ("review", "goto-hand"):
        assert q.fresh(ev(None, m, "nohit", note=note), FP, "f")  # note hit alone: still fresh
        assert not q.fresh(ev(None, m, "nohit", note=note, name="named"), FP, "named")  # name hit
    for m in ("diagnose", "permute", "reconstruct"):
        assert not q.fresh(ev(None, m, "nohit", note=note), FP, "f")


def test_newest_by_time_wins_over_carried_older_event():
    fresh = ev(SITE, "diagnose", "nohit", t="2026-01-02T00:00:00Z", quirks=["Q0001"])
    carried = ev(SITE, "diagnose", "blocked", t="2026-01-01T00:00:00Z", agent="carry")
    state, e, ok = q.mark([fresh, carried], "diagnose", FP, "f")
    assert e is fresh and (state, ok) == ("✓", True)


def test_per_function_header_fingerprint(tmp_path, monkeypatch):
    root = tmp_path.resolve()
    (root / "src" / "global").mkdir(parents=True)
    (root / "include" / "proto" / "global").mkdir(parents=True)
    monkeypatch.chdir(root)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(root))
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: {"f": 0x80600000, "h": 0x80600100}[name])
    s_h, p_h = root / "include" / "s.h", root / "include" / "proto" / "global" / "p.h"
    s_h.write_text("typedef struct S { int a; int b; } S;\n")
    p_h.write_text("void g(int);\nvoid k(int);\n")
    (root / "src" / "global" / "x.c").write_text(
        '#include "s.h"\n#include "proto/global/p.h"\n'
        "int f(S *p) {\n    return p->a;\n}\n"
        "int h(int x) {\n    g(x);\n    return x;\n}\n")

    def state():
        monkeypatch.setattr(q, "_htext", {})
        fns = {fn["name"]: dict(fn, file="src/global/x.c") for fn in q.analyze("src/global/x.c", "global")["functions"]}
        return fns, {n: (fn["fp_local"], fn["fp_hdr"], fn["fp_hdr2"]) for n, fn in fns.items()}

    fns, fp0 = state()
    plain = {n: q.event("u", "sweep", fn, None, "plain", "nohit") for n, fn in fns.items()}
    p_h.write_text("void g(int);\nvoid k(short);\n")  # regenerated proto: k is called by nobody
    _, fp1 = state()
    assert fp1["f"][1] != fp0["f"][1]  # whole-header fingerprint moved for everyone
    assert q.fresh(plain["f"], fp1["f"], "f") and q.fresh(plain["h"], fp1["h"], "h")
    s_h.write_text("typedef struct S { short a; int b; } S;\n")  # f's struct changed
    _, fp2 = state()
    assert not q.fresh(plain["f"], fp2["f"], "f")
    assert q.fresh(plain["h"], fp2["h"], "h")
    old = dict(plain["h"], fp_hdr2=None)  # an event from before fp_hdr2: whole-header rule
    assert not q.fresh(old, fp2["h"], "h")


def test_token_pasting_macro_falls_back_to_whole_header(tmp_path, monkeypatch):
    root = tmp_path.resolve()
    (root / "src" / "global").mkdir(parents=True)
    monkeypatch.chdir(root)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(root))
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: {"f": 0x80600000, "h": 0x80600100}[name])
    m_h = root / "include" / "m.h"
    m_h.parent.mkdir()
    m_h.write_text("#define PICK(n) VAL_##n\n#define VAL_1 10\n#define OTHER 3\n")
    (root / "src" / "global" / "x.c").write_text(
        '#include "m.h"\nint f(void) {\n    return PICK(1);\n}\nint h(void) {\n    return OTHER;\n}\n')

    def state():
        monkeypatch.setattr(q, "_htext", {})
        return {fn["name"]: fn["fp_hdr2"] for fn in q.analyze("src/global/x.c", "global")["functions"]}

    fp0 = state()
    m_h.write_text("#define PICK(n) VAL_##n\n#define VAL_1 11\n#define OTHER 3\n")
    fp1 = state()
    assert fp1["f"] != fp0["f"]  # VAL_1 only reached through VAL_##n
    assert fp1["h"] == fp0["h"]


@pytest.mark.parametrize("macros,new_macros,expect", [
    # bounded paste (gbi.h `GBL_c##clk`): every VAL_* is in reach, an unrelated deletion carries f
    ("#define PICK(n) VAL_##n\n#define VAL_1 10\n", None, "carried"),
    # ... and a changed VAL_* keeps it stale
    ("#define PICK(n) VAL_##n\n#define VAL_1 10\n", "#define PICK(n) VAL_##n\n#define VAL_1 11\n",
     "f: not a pure rename"),
    # two parameters pasted could form any name: not tracked
    ("#define CAT(a, b) a##b\n#define PICK(n) CAT(VAL_, n)\n#define VAL_1 10\n", None,
     "f: token-pasting macro CAT: dependencies not tracked"),
])
def test_carry_token_pasting_function(tmp_path, monkeypatch, capsys, macros, new_macros, expect):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality.jsonl"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: {"f": 0x80600000, "h": 0x80600100}[name])
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    src = repo / "src" / "global" / "x.c"
    tail = "int f(void) {\n    return PICK(1);\n}\nint h(void) {\n    return 2;\n}\n"
    src.write_text(macros + "typedef struct { int c; } ViewC;\n" + tail)
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "a")
    rev_a = _git(repo, "rev-parse", "HEAD")
    fns = {fn["name"]: dict(fn, file="src/global/x.c") for fn in q.analyze("src/global/x.c", "global")["functions"]}
    q.append_events([q.event("u1", "a", fns[n], None, "review", "nohit", note="fake=0/0") for n in ("f", "h")])
    src.write_text((new_macros or macros) + tail)  # unused ViewC deleted
    _git(repo, "commit", "-qam", "b")
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2"])
    out = capsys.readouterr().out
    carried = {e["name"] for e in q.load_events() if e.get("agent") == "carry"}
    if expect == "carried":
        assert carried == {"f", "h"}
    else:
        assert carried == {"h"} and expect in out


@pytest.mark.parametrize("old,new,kinds", [
    # D5E10 c9f9b289: `// PROTO:` -> `// FAKE: callee prototype steer` on the function's skip line
    ("#define PROTO_SKIP_g // PROTO: arity\nint g();\n", "#define PROTO_SKIP_g // FAKE: callee prototype steer\nint g();\n",
     ["dead-if", "proto-type"]),
    # round 4 tag batches: an untagged steering declaration gets its tag (a new file-scope site)
    ("int g();\n", "int g(); // FAKE: callee prototype steer\n", ["dead-if"]),
])
def test_carry_across_retagged_file_scope_site(tmp_path, monkeypatch, capsys, old, new, kinds):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality.jsonl"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    src = repo / "src" / "global" / "x.c"
    body = "int f(int x) {\n    if (x) {} // FAKE: steers\n    return g(x);\n}\n"
    src.write_text(old + body)
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "a")
    rev_a = _git(repo, "rev-parse", "HEAD")
    fn = dict(q.analyze("src/global/x.c", "global")["functions"][0], file="src/global/x.c")
    assert sorted(s["kind"] for s in fn["sites"]) == kinds
    dead = next(s for s in fn["sites"] if s["kind"] == "dead-if")
    q.append_events([q.event("u1", "a", fn, None, "review", "nohit", note="fake=1/0"),
                     q.event("u1", "a", fn, dead, "diagnose", "nohit", quirks=["Q0001"])])
    src.write_text(new + body)
    _git(repo, "commit", "-qam", "b")
    q.main(["carry", "--rev", rev_a, "--unit", "u2"])
    carried = [e for e in q.load_events() if e.get("agent") == "carry"]
    assert sorted(e["method"] for e in carried) == ["diagnose", "review"]
    assert all(e["site"] in (None, dead["key"]) for e in carried)


def test_note_text_strips_carry_prefixes():
    assert q.note_text("carried from abc^ (unrelated file-scope changes only): carried from def (identifier "
                       "renames only): " + REVIEW) is None
    assert q.note_text("carried from abc^ (identifier renames only): regalloc swap") == "regalloc swap"


@pytest.mark.parametrize("code, plain", [
    ("x = *(u16 *)&D_807FBB32;", "x = D_807FBB32;"),
    ("flags = ((u8 *)&anim->layerWeight)[1];", "flags = anim->layerWeight;"),
    ("v = ((s16 *)&gScore)[1] + 2;", "v = gScore + 2;"),
    ("v = *((u8 *)&state.count + 3);", "v = state.count;"),
])
def test_plain_rewrites_punned_low_part(code, plain):
    assert plain in {rx.sub(rep, code) for rx, rep in q.PLAIN}


def test_plain_rewrites_keep_high_part_puns():
    for code in ("v = ((u8 *)&gScore)[0];", "v = ((u8 *)&arr[i])[1];", "v = ((u8 *)&gScore)[i];"):
        assert {rx.sub(rep, code) for rx, rep in q.PLAIN} == {code}

def test_carry_takes_newest_event_by_time(tmp_path, monkeypatch):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality.jsonl"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    src = repo / "src" / "global" / "x.c"
    body = "int f(int x) {\n    return x + 1;\n}\n"
    src.write_text("typedef struct { int c; } ViewC;\n" + body)
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "a")
    rev_a = _git(repo, "rev-parse", "HEAD")
    fn = dict(q.analyze("src/global/x.c", "global")["functions"][0], file="src/global/x.c")
    agent = dict(q.event("u1", "a", fn, None, "review", "nohit", note=REVIEW), t="2026-01-02T00:00:00Z")
    older = dict(agent, agent="carry", t="2026-01-01T00:00:00Z")  # an older carried event, later in file
    q.append_events([agent, older])
    src.write_text(body)  # ViewC deleted
    _git(repo, "commit", "-qam", "b")
    q.main(["carry", "--rev", rev_a, "--unit", "u2"])
    carried = [e for e in q.load_events() if e.get("unit") == "u2" and e.get("type") == "quality"]
    assert [e["t"] for e in carried] == ["2026-01-02T00:00:00Z"]


CARVE_H = "void g(int);\ntypedef struct S {\n    int a;\n    char pad4[4];\n    int b;\n} S;\n"


def _carve_repo(tmp_path, monkeypatch, new_header, ret="p->b"):
    """Repo whose f (returning RET) reaches S (and g) through include/s.h, with automatic and agent
    results for f recorded under CARVE_H; then the header becomes NEW_HEADER (f's body untouched).
    Returns (repo, rev before the header edit)."""
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    (repo / "include").mkdir()
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality.jsonl"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "_htext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: {"f": 0x80600000, "h": 0x80600100}[name])
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    (repo / "include" / "s.h").write_text(CARVE_H)
    (repo / "src" / "global" / "x.c").write_text(
        ('#include "s.h"\nint f(S *p) {\n    if (p->a) {} // FAKE: steers\n    g(p->a);\n    return %s;\n}\n'
         "int h(int x) {\n    return x;\n}\n") % ret)
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "a")
    rev_a = _git(repo, "rev-parse", "HEAD")
    fns = {fn["name"]: dict(fn, file="src/global/x.c") for fn in q.analyze("src/global/x.c", "global")["functions"]}
    f, site = fns["f"], fns["f"]["sites"][0]
    q.append_events([q.event("u1", "sweep", f, site, "remove", "nohit"),
                     q.event("u1", "a", f, None, "views", "nohit", note="no views left"),
                     q.event("u1", "a", f, None, "review", "nohit", note=REVIEW),
                     q.event("u1", "a", fns["h"], None, "views", "nohit")])
    (repo / "include" / "s.h").write_text(new_header)
    _git(repo, "commit", "-qam", "b")
    monkeypatch.setattr(q, "_htext", {})
    return repo, rev_a


def _carve_state():
    """{function: {method: '✓' | 'stale' | '—'}} for views, review and (on f's site) remove."""
    fns = {fn["name"]: fn for fn in q.analyze("src/global/x.c", "global")["functions"]}
    by_site, by_func = q.index_events(q.load_events())
    out = {}
    for n, fn in fns.items():
        fp, fevs = (fn["fp_local"], fn["fp_hdr"], fn["fp_hdr2"]), by_func[("global", f"{fn['vram']:08X}")]
        out[n] = {m: q.mark(fevs, m, fp, n)[0] for m in ("views", "review")}
        if fn["sites"]:
            out[n]["remove"] = q.mark(by_site[fn["sites"][0]["key"]], "remove", fp, n)[0]
    return out


def test_carry_header_carve_keeping_layout(tmp_path, monkeypatch, capsys):
    _, rev_a = _carve_repo(tmp_path, monkeypatch, CARVE_H.replace(
        "    char pad4[4];\n", "    short unk4;\n    char pad6[2];\n"))
    st = _carve_state()
    assert (st["f"]["views"], st["f"]["remove"]) == ("stale", "stale")  # S changed: f's automatic results
    before = q.load_events()
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--header-carve", "--dry-run"])
    out = capsys.readouterr().out
    assert "would carry src/global/x.c: f: remove, views (header carve: S)" in out
    assert "would carry 2 events" in out and q.load_events() == before
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--header-carve"])
    carried = [e for e in q.load_events() if e.get("agent") == "carry"]
    assert sorted(e["method"] for e in carried) == ["remove", "views"]  # review needs fp_local only
    assert all(e["note"].startswith(f"carried from {rev_a} (header carve: S)") for e in carried)
    st = _carve_state()
    assert st["f"] == {"views": "✓", "review": "✓", "remove": "✓"} and st["h"]["views"] == "✓"
    n = len(q.load_events())
    q.main(["carry", "--rev", rev_a, "--unit", "u3", "--header-carve"])  # nothing left to carry
    assert len(q.load_events()) == n


def test_carry_header_carve_rejects_shifted_offset(tmp_path, monkeypatch, capsys):
    _, rev_a = _carve_repo(tmp_path, monkeypatch, CARVE_H.replace(
        "    char pad4[4];\n", "    short unk4;\n    char pad6[4];\n"))
    before = q.load_events()
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--header-carve"])
    out = capsys.readouterr().out
    assert "skipped src/global/x.c: f: layout changed: S size 0xC -> 0x10; S b offset 0x8 -> 0xC" in out
    assert "carried 0 events" in out and q.load_events() == before


def test_carry_header_carve_rejects_reached_prototype_change(tmp_path, monkeypatch, capsys):
    _, rev_a = _carve_repo(tmp_path, monkeypatch, CARVE_H.replace(
        "    char pad4[4];\n", "    short unk4;\n    char pad6[2];\n").replace("void g(int);", "void g(short);"))
    before = q.load_events()
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--header-carve"])
    out = capsys.readouterr().out
    assert "skipped src/global/x.c: f: prototype g changed" in out
    assert "carried 0 events" in out and q.load_events() == before


@pytest.mark.parametrize("ret,carried", [("p->b", True), ("p->b + sizeof(p->pad4)", False)])
def test_carry_header_carve_shrunk_padding_array(tmp_path, monkeypatch, capsys, ret, carried):
    # pad4 keeps its name and start, shrinks to make room (Actor.unk08[76] -> unk08[4] + modelMtx)
    _, rev_a = _carve_repo(tmp_path, monkeypatch, CARVE_H.replace(
        "    char pad4[4];\n", "    char pad4[2];\n    short unk6;\n"), ret)
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--header-carve"])
    out = capsys.readouterr().out
    assert ("carried 2 events" in out) == carried
    assert ("f: array S.pad4 resized and sizeof reached" in out) != carried


@pytest.mark.parametrize("ret,reason", [
    ("p->b", None),
    ("p->b + sizeof(p->a)", "f: array S.pad4 resized and sizeof reached"),
    ("p->b + (int)p->pad4", "f: array S.pad4 became a scalar and is accessed"),
])
def test_carry_header_carve_padding_array_to_scalar(tmp_path, monkeypatch, capsys, ret, reason):
    # pad4 keeps its name and start as a scalar of its element type (7e4bbf00: u8 pad36[2] -> pad36 + unk37)
    _, rev_a = _carve_repo(tmp_path, monkeypatch, CARVE_H.replace(
        "    char pad4[4];\n", "    char pad4;\n    char unk5;\n    short unk6;\n"), ret)
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--header-carve"])
    out = capsys.readouterr().out
    if reason is None:
        assert "carried 2 events" in out and "skipped" not in out
        assert _carve_state()["f"] == {"views": "✓", "review": "✓", "remove": "✓"}
    else:
        assert reason in out and "carried 0 events" in out


WSITE = dict(key="global:80600000:warning:abc123", kind="warning", name="f", line=4, lines=[3], tagged=False,
             code="g = x;", warning="712 illegal combination of pointer and integer")


def test_warning_site_ladder():
    assert q.exhausted(WSITE, [], FP)[:2] == (False, "retype")
    assert q.exhausted(WSITE, [ev(WSITE, "retype", "kept", note="tried s32 *g; fdiff=1")], FP)[:2] == (True, None)
    assert q.exhausted(WSITE, [ev(WSITE, "retype", "blocked", note="needs Actor.unk0 typed")], FP)[:2] == (
        False, "retype")


def test_warning_sites_need_no_reconstruct():
    fn = dict(FN, sites=[dict(WSITE, key=WSITE["key"] + (f"#{n}" if n > 1 else "")) for n in (1, 2, 3)])
    st = q.function_state(fn, {}, {("global", "80600000"): [ev(None, "review", "nohit", note=REVIEW)]})
    assert (st["reconstruct"], st["next"]) == (None, "retype")


@pytest.mark.parametrize("line,msg", [
    (f"{WSITE['key']} retype nohit", "retype outcome is fixed, kept or blocked"),
    (f'{WSITE["key"]} retype kept note="tried s32 *g"', "retype kept needs note with fdiff=<1|3>"),
    (f"{SITE['key']} retype fixed", "retype needs a warning site key"),
    (f"{WSITE['key']} diagnose nohit quirks=Q0001", "warning sites take only retype"),
    (f"{WSITE['key']} retype blocked", "retype blocked needs a note"),
])
def test_record_rejects_bad_retype(tmp_path, monkeypatch, capsys, line, msg):
    ledger_path = tmp_path / "quality.jsonl"
    monkeypatch.setattr(q, "LEDGER", str(ledger_path))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), WSITE))
    batch = tmp_path / "batch.txt"
    batch.write_text(line + "\n")
    with pytest.raises(SystemExit) as ex:
        q.main(["record", "--unit", "u1", "--agent", "a", "--batch", str(batch), "--dry-run"])
    assert ex.value.code == 1
    assert msg in capsys.readouterr().err
    assert not ledger_path.exists()


def test_record_accepts_retype_kept_with_fdiff(tmp_path, monkeypatch, capsys):
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality.jsonl"))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), WSITE))
    batch = tmp_path / "batch.txt"
    batch.write_text(f'{WSITE["key"]} retype kept note="tried s32 *g; fdiff=3"\n')
    q.main(["record", "--unit", "u1", "--agent", "a", "--batch", str(batch), "--dry-run"])
    assert "would record 1 events" in capsys.readouterr().out


def test_analyze_warning_site(tmp_path, monkeypatch):
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    c = tmp_path / "x.c"
    c.write_text("typedef int s32;\ns32 *g;\nvoid f(s32 x) {\n    g = x;\n}\n")
    path = q.rel(str(c))
    warns = [dict(code=712, path=path, line=4, col=6, msg="illegal combination of pointer and integer"),
             dict(code=709, path="include/x.h", line=1, col=-1, msg="incompatible pointer type")]
    monkeypatch.setattr(q.cwarn, "collect", lambda items: [warns])
    an = q.analyze(str(c), "global")
    fn, = an["functions"]
    s, = fn["sites"]
    assert (s["kind"], s["line"], s["warning"]) == ("warning", 4, "712 illegal combination of pointer and integer")
    assert re.fullmatch(r"global:80600000:warning:[0-9a-f]{6}", s["key"])
    assert an["warnings"] == 2
