import json
import os
import re
import sys
from pathlib import Path

import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools import quality as q  # noqa: E402

REAL_COLLECT = q.cwarn.collect  # the autouse no_compile fixture stubs it

FP = ("1111111111111111", "2222222222222222")
SITE = dict(key="global:80600000:dead-if:abc123", kind="dead-if", name="f", line=3, lines=[2], tagged=True,
            code="if (x) {} // FAKE")
FN = dict(name="f", seg="global", vram=0x80600000, fp_local=FP[0], fp_hdr=FP[1], sites=[])
REVIEW = "fake=0/0 goto=0 casts=0 views=ok protos=ok temps=ok names=0 uninit=0 warn=0"


def ev(site, method, outcome, fp=FP, note=None, **kw):
    e = dict(type="quality", t="2026-01-01T00:00:00Z", unit="u", agent="a", seg="global", vram="80600000",
             name="f", file="src/global/x.c", site=site["key"] if site else None,
             kind=site["kind"] if site else None, method=method, outcome=outcome, fp_local=fp[0], fp_hdr=fp[1],
             fp_hdr2=None, quirks=[], seconds=None, base=None, best=None, commit=None, note=note, model=None,
             new=None)
    e.update(kw)
    return e


@pytest.fixture(autouse=True)
def no_new_knowledge(monkeypatch):
    monkeypatch.setattr(q, "knowledge_after", lambda name, t, unit=None: False)


@pytest.fixture(autouse=True)
def no_compile(monkeypatch):
    """analyze() would compile through tools/dk; tests see no cfe warnings unless they patch them in."""
    monkeypatch.setattr(q.cwarn, "collect", lambda items, rev=None: [[] for _ in items])


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


def test_class2_site_needs_recipe_then_diagnose():
    evs = [ev(SITE, "remove", "nohit"), ev(SITE, "cond", "nohit"), ev(SITE, "classify", "nohit", note="class 2")]
    assert q.exhausted(SITE, evs, FP)[:2] == (False, "recipe")
    evs += [ev(SITE, "recipe", "nohit"), ev(SITE, "diagnose", "nohit", quirks=["Q0001"])]
    assert q.exhausted(SITE, evs, FP)[:2] == (True, None)


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
    ledger_path = tmp_path / "quality"
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
    ledger_path = tmp_path / "quality"
    monkeypatch.setattr(q, "LEDGER", str(ledger_path))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), SITE))
    batch = tmp_path / "batch.txt"
    batch.write_text(f'{SITE["key"]} diagnose nohit quirks=Q0001,Q0002 note="regalloc"\n')
    q.main(["record", "--unit", "u1", "--agent", "a", "--batch", str(batch)])
    unit, e = q.load_events()
    assert unit["type"] == "unit" and unit["unit"] == "u1" and unit["commit"]
    assert set(e) == set(ev(SITE, "diagnose", "nohit"))
    assert (e["site"], e["kind"], e["quirks"], e["fp_local"]) == (SITE["key"], "dead-if", ["Q0001", "Q0002"], FP[0])


@pytest.mark.parametrize("agent,ok", [("Clean12E800.SnXxx", True), ("a.b.c", True), ("a b", False),
                                      ("a/b", False), ("a.", False), (".a", False)])
def test_record_agent_ids(tmp_path, monkeypatch, agent, ok):
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), SITE))
    batch = tmp_path / "batch.txt"
    batch.write_text(f'{SITE["key"]} diagnose nohit quirks=Q0001\n')
    if ok:
        q.main(["record", "--unit", "u1", "--agent", agent, "--batch", str(batch)])
        assert q.load_events()[-1]["agent"] == agent
    else:
        with pytest.raises(SystemExit):
            q.main(["record", "--unit", "u1", "--agent", agent, "--batch", str(batch)])


def test_record_accepts_permute_stopped_on_zero(tmp_path, monkeypatch):
    ledger_path = tmp_path / "quality"
    monkeypatch.setattr(q, "LEDGER", str(ledger_path))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), SITE))
    batch = tmp_path / "batch.txt"
    batch.write_text(f'{SITE["key"]} permute nohit seconds=145 base=90 best=0 note="zero only via a hack"\n')
    q.main(["record", "--unit", "u1", "--agent", "a", "--batch", str(batch)])
    assert q.load_events()[-1]["seconds"] == 145


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
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
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
    ledger_path = tmp_path / "quality"
    ledger_path.mkdir()
    (ledger_path / "units.jsonl").write_text('{"type": "unit", "unit": "u0"}\n')
    before = sorted((p, p.read_bytes()) for p in ledger_path.rglob("*.jsonl"))
    monkeypatch.setattr(q, "LEDGER", str(ledger_path))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), SITE))
    good = tmp_path / "good.txt"
    good.write_text(f'{SITE["key"]} diagnose nohit quirks=Q0001\n')
    q.main(["record", "--unit", "u1", "--agent", "a", "--batch", str(good), "--dry-run"])
    assert "would record 1 events" in capsys.readouterr().out
    assert sorted((p, p.read_bytes()) for p in ledger_path.rglob("*.jsonl")) == before
    bad = tmp_path / "bad.txt"
    bad.write_text(f"{SITE['key']} remove kept\n")
    errs = []
    for extra in (["--dry-run"], []):
        with pytest.raises(SystemExit) as ex:
            q.main(["record", "--unit", "u1", "--agent", "a", "--batch", str(bad), *extra])
        assert ex.value.code == 1
        errs.append(capsys.readouterr().err)
    assert errs[0] == errs[1] and "kept is only for classify" in errs[0]
    assert sorted((p, p.read_bytes()) for p in ledger_path.rglob("*.jsonl")) == before


def test_carry_across_unrelated_file_scope_changes(tmp_path, monkeypatch, capsys):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
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


def test_carry_renames_with_unrelated_file_scope_changes(tmp_path, monkeypatch, capsys):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    vrams = {"f": 0x80600000, "h": 0x80600100, "k": 0x80600200}
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: vrams[name])
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    src = repo / "src" / "global" / "x.c"
    fns_text = ("int f(ViewA *%s) {\n    if (%s->a) {} // FAKE: steers\n    return %s->a;\n}\n"
                "int h(ViewB *%s) {\n    return %s->b;\n}\n"
                "int k(%s %s) {\n    return %s;\n}\n")
    old = "typedef struct { int a; } ViewA;\ntypedef struct { int b; } ViewB;\ntypedef struct { int c; } ViewC;\n"
    src.write_text(old + fns_text % ("arg0", "arg0", "arg0", "arg0", "arg0", "int", "arg0", "arg0"))
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "a")
    rev_a = _git(repo, "rev-parse", "HEAD")
    fns = {fn["name"]: dict(fn, file="src/global/x.c") for fn in q.analyze("src/global/x.c", "global")["functions"]}
    q.append_events([q.event("u1", "a", fns[n], None, "review", "nohit", note="fake=0/0") for n in vrams])

    # ViewC (reached by nobody) deleted, ViewB (reached by h) changed; every parameter renamed, k's retyped
    src.write_text("typedef struct { int a; } ViewA;\ntypedef struct { int pad; int b; } ViewB;\n"
                   + fns_text % ("view", "view", "view", "p", "p", "unsigned", "n", "n"))
    _git(repo, "commit", "-qam", "b")
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--dry-run"])
    out = capsys.readouterr().out
    assert "would carry src/global/x.c: f: review (renames; unrelated file-scope changes only)" in out
    assert "h: not a pure rename" in out and "k: not a pure rename" in out
    assert not [e for e in q.load_events() if e.get("agent") == "carry"]


_real_knowledge_after = q.knowledge_after


def test_knowledge_search_is_name_only(monkeypatch):
    calls = []

    def related(corpus, name, note):
        calls.append(note)
        return {"knowledge/ido/entries/Q9002.md"} if name == "named" else set()

    times = {"knowledge/ido/entries/Q9002.md": "2026-02-01T00:00:00Z"}
    monkeypatch.setattr(q, "_know", {"times": times, "newest": max(times.values()), "corpus": []})
    monkeypatch.setattr(q.ledger, "related_knowledge", related)
    t = "2026-01-01T00:00:00Z"
    assert not _real_knowledge_after("f", t)
    assert _real_knowledge_after("named", t)  # a file naming the function stales it
    assert calls == [None, None]  # never searched by note text


def test_note_hits_never_stale(monkeypatch):
    # rounds 18-36: top-8 note hits re-ran the same diagnose/permute attempts; a retry must name
    # what is new (record's new= gate) instead
    monkeypatch.setattr(q, "knowledge_after", _real_knowledge_after)
    monkeypatch.setattr(q.ledger, "related_knowledge", lambda corpus, name, note: (
        {"knowledge/ido/entries/Q9001.md"} if note else set()) | (
        {"knowledge/ido/entries/Q9002.md"} if name == "named" else set()))
    times = {"knowledge/ido/entries/Q9001.md": "2026-02-01T00:00:00Z",
             "knowledge/ido/entries/Q9002.md": "2026-02-01T00:00:00Z"}
    monkeypatch.setattr(q, "_know", {"times": times, "newest": max(times.values()),
                                     "corpus": q.quirks.Corpus(Path("."))})
    note = "re-read after the steer fix " + REVIEW
    for m in ("review", "goto-hand", "permute", "diagnose", "reconstruct", "retype"):
        assert q.fresh(ev(None, m, "nohit", note=note), FP, "f")  # note hit alone: still fresh
        assert not q.fresh(ev(None, m, "nohit", note=note, name="named"), FP, "named")  # name hit


def test_entry_naming_function_stales_every_method(tmp_path, monkeypatch):
    repo, kroot = _knowledge_repo(tmp_path, monkeypatch)
    (repo / "symbol_addrs.us.txt").write_text("fooBar = 0x80600000; // type:func\n")
    hit = q.quirks.add_entry(kroot, "spill across the jal", "uopt", ["regalloc"], "sp+0x34 spill across the jal")
    named = q.quirks.add_entry(kroot, "dead store kept", "uopt", ["dead-code"], "a dead store", functions=["fooBar"])
    note, t = "spill across the jal", "2026-01-20T00:00:00Z"

    def fresh(method, times):
        monkeypatch.setattr(q, "_know", {"times": times, "newest": max(times.values()),
                                         "corpus": q.quirks.load(kroot)})
        return q.fresh(ev(SITE, method, "nohit", note=note, name="fooBar", t=t), FP, "fooBar")

    newer_hit = {f"knowledge/ido/entries/{hit}.md": "2026-02-01T00:00:00Z",
                 f"knowledge/ido/entries/{named}.md": "2026-01-01T00:00:00Z"}
    newer_named = {f"knowledge/ido/entries/{hit}.md": "2026-01-01T00:00:00Z",
                   f"knowledge/ido/entries/{named}.md": "2026-02-01T00:00:00Z"}
    for m in ("permute", "diagnose", "reconstruct"):
        assert fresh(m, newer_hit)  # a newer top-8 hit for the note alone
        assert not fresh(m, newer_named)  # a newer entry naming the function


R34 = "2026-11-13: cleanup round 34"


def _knowledge_repo(tmp_path, monkeypatch):
    """(repo, its knowledge/ido root): ledger.ROOT at REPO, the real knowledge_after."""
    repo = tmp_path.resolve() / "repo"
    kroot = repo / "knowledge" / "ido"
    kroot.mkdir(parents=True)
    monkeypatch.setattr(q.ledger, "ROOT", str(repo))
    monkeypatch.setattr(q, "knowledge_after", _real_knowledge_after)
    return repo, kroot


def test_own_unit_entry_naming_function_does_not_stale(tmp_path, monkeypatch):
    # round 34: Q0704-Q0719, derived from the round's own runs, staled those very runs (circular)
    repo, kroot = _knowledge_repo(tmp_path, monkeypatch)
    (repo / "symbol_addrs.us.txt").write_text("fooBar = 0x80600000; // type:func\n")
    own = q.quirks.add_entry(kroot, "spill across the jal", "uopt", ["regalloc"], "sp+0x34 spill across the jal",
                             functions=["func_80600000"], unit=R34)  # names fooBar by its address
    older = q.quirks.add_entry(kroot, "dead store kept", "uopt", ["dead-code"], "a dead store", functions=["fooBar"])
    times = {f"knowledge/ido/entries/{own}.md": "2026-02-01T00:00:00Z",
             f"knowledge/ido/entries/{older}.md": "2026-01-15T00:00:00Z"}
    monkeypatch.setattr(q, "_know", {"times": times, "newest": max(times.values()), "corpus": q.quirks.load(kroot)})

    def fresh(name, method, unit, t="2026-01-20T00:00:00Z"):
        note = "spill across the jal" if method in ("diagnose", "reconstruct") else REVIEW
        return q.fresh(ev(None, method, "nohit", note=note, name=name, unit=unit, t=t), FP, name)

    for m in ("review", "goto-hand", "retype", "diagnose", "permute", "reconstruct"):
        assert fresh("fooBar", m, R34)  # same unit, named (also a note hit): its agents had the finding
        assert not fresh("fooBar", m, "2026-11-12: cleanup round 33")  # earlier unit: staled
        assert not fresh("fooBar", m, R34, t="2026-01-10T00:00:00Z")  # another newer entry names it
    for m in ("diagnose", "permute", "reconstruct", "review"):
        assert fresh("otherFn", m, R34)  # not in `functions`: a note hit alone never stales
    # a carried event holds an earlier agent's result under the carrying unit: the copied event's unit counts
    t = "2026-01-20T00:00:00Z"
    for orig_unit, ok in ((R34, True), ("2026-11-12: cleanup round 22", False)):
        orig = ev(SITE, "diagnose", "nohit", note="spill across the jal", name="fooBar", unit=orig_unit, t=t)
        carried = dict(orig, unit=R34, agent="carry", note="carried from abc (renames) spill across the jal")
        assert q.mark([orig, carried], "diagnose", FP, "fooBar")[2] is ok
    assert not q.mark([carried], "diagnose", FP, "fooBar")[2]  # its original not among them: unknown


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
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
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
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
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


def test_record_requires_new_for_retry(tmp_path, monkeypatch, capsys):
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (dict(FN, file="src/global/x.c"), SITE))
    batch = tmp_path / "batch.txt"
    line = f'{SITE["key"]} diagnose nohit quirks=Q0001 note="regalloc"'
    batch.write_text(line + "\n")
    q.main(["record", "--unit", "u0", "--agent", "Old", "--batch", str(batch)])
    with pytest.raises(SystemExit) as ex:
        q.main(["record", "--unit", "u1", "--agent", "New", "--batch", str(batch)])
    assert ex.value.code == 1 and "tried before (1 earlier events)" in capsys.readouterr().err
    batch.write_text(line + ' new="swap"\n')
    q.main(["record", "--unit", "u1", "--agent", "New", "--batch", str(batch)])
    assert q.load_events()[-1]["new"] == "swap"
    batch.write_text(line + "\n")
    q.main(["record", "--unit", "u0", "--agent", "Old", "--batch", str(batch)])  # its own re-record
    assert [e["agent"] for e in q.load_events() if e["type"] == "quality"] == ["Old", "New", "Old"]


def test_record_model_and_skip_missing(tmp_path, monkeypatch, capsys):
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
    gone = "global:80600000:dead-if:ffffff"
    monkeypatch.setattr(q.Resolver, "find", lambda self, key: (
        f"no site {key} at HEAD" if key == gone else (dict(FN, file="src/global/x.c"), SITE)))
    batch = tmp_path / "batch.txt"
    batch.write_text(f"{gone} remove nohit\n{SITE['key']} remove nohit\n")
    with pytest.raises(SystemExit):
        q.main(["record", "--unit", "u", "--agent", "a", "--batch", str(batch)])
    with pytest.raises(SystemExit):
        q.main(["record", "--unit", "u", "--agent", "a", "--model", "opus", "--batch", str(batch)])
    q.main(["record", "--unit", "u", "--agent", "a", "--model", "anthropic/claude-opus-5-5:xhigh",
            "--skip-missing", "--batch", str(batch)])
    assert "skipped line 1" in capsys.readouterr().err
    e, = [e for e in q.load_events() if e["type"] == "quality"]
    assert (e["site"], e["model"]) == (SITE["key"], "anthropic/claude-opus-5-5:xhigh")


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


class _NoHit:
    def result(self):
        return False


class _NoHitPool:
    """plan_file's pool, every check a miss (nothing compiles)."""

    def submit(self, fn, *args):
        return _NoHit()


SWEEP_C = ("typedef int s32;\ns32 g;\nvoid f(s32 x) {\n"
           "    do {} while (0); // FAKE: one-line block split\n"
           "    x = g; if (x) {} g = x; // FAKE: dead test sharing its line\n"
           "    if (g) {} // FAKE: steers\n"
           "    x = g; do { // FAKE: do sharing its line\n"
           "        g++;\n"
           "    } while (0);\n}\n")


def test_sweep_records_every_sweep_rung(tmp_path, monkeypatch):
    """A site whose shape the sweep cannot edit (a dead test or `do {` sharing its line) still gets a
    sweep event for every sweep method of its ladder: otherwise its hand-recorded rungs went stale on
    a header change and `sweep --record` never refreshed them (2690, 42630, 7BBD0 rounds 23-26)."""
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    c = tmp_path / "x.c"
    c.write_text(SWEEP_C)
    path = q.rel(str(c))
    an = q.analyze(path, "global")
    plan = q.plan_file(an, path, path, _NoHitPool())
    out, hits, _ = q.finish(plan)
    assert not hits
    fn, = an["functions"]
    site = {s["line"]: s for s in fn["sites"]}
    by_key = {s["key"]: s for s in fn["sites"]}
    assert {ln: s["kind"] for ln, s in site.items()} == {4: "do-while0", 5: "dead-if", 6: "dead-if", 7: "do-while0"}
    sweep = ("remove", "plain", "cond", "classify")
    assert {(s["key"], m) for s in fn["sites"] for m in q.LADDER[s["kind"]] if m in sweep} <= set(out)
    alone = [text for method, keys, _, text in plan["jobs"] if method == "remove" and keys == [site[4]["key"]]]
    assert len(alone) == 1 and "do {} while (0);" not in alone[0]  # a one-line wrapper is deleted, like a pair
    assert out[(site[5]["key"], "remove")] == out[(site[5]["key"], "cond")] == ["nohit", "no removal"]
    assert out[(site[5]["key"], "classify")] == ["nohit", "no guard"]
    assert out[(site[7]["key"], "remove")] == out[(site[7]["key"], "cond")] == ["nohit", "no removal"]
    # hand-recorded rungs at older fingerprints (a header changed since) are refreshed by the sweep
    old = ("0" * 16, "0" * 16)
    hand = [ev(s, m, "nohit", fp=old) for s in fn["sites"] for m in q.LADDER[s["kind"]] if m in sweep]
    swept = [dict(q.event("u", "sweep", dict(fn, file=path), by_key[k], m, o, note=n), t="2026-01-02T00:00:00Z")
             for (k, m), (o, n) in out.items()]
    by_site, by_func = q.index_events(hand + swept)
    st = q.function_state(fn, by_site, by_func)
    assert {v for _, r in st["sites"] for m, v in r["marks"].items() if m in sweep} == {"✓"}


def test_carry_takes_newest_event_by_time(tmp_path, monkeypatch):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
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


def _carve_repo(tmp_path, monkeypatch, new_header, ret="p->b", edit=None, old_header=CARVE_H):
    """Repo whose f (returning RET) reaches S (and g) through include/s.h, with automatic and agent
    results for f recorded under OLD_HEADER; then the header becomes NEW_HEADER (f's body untouched,
    unless EDIT rewrites the .c text in the same commit). Returns (repo, rev before the header edit)."""
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    (repo / "include").mkdir()
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "_htext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: {"f": 0x80600000, "h": 0x80600100}[name])
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    (repo / "include" / "s.h").write_text(old_header)
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
    if edit:
        x = repo / "src" / "global" / "x.c"
        x.write_text(edit(x.read_text()))
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


@pytest.mark.parametrize("old,new,reason", [
    (None, None, None),
    ("    int b;\n", "    unsigned int b;\n", ""),  # a field the body uses changed type
    ("    char pad4[4];\n", "    unsigned char pad4[4];\n", " (layout changed: S pad4 type"),  # one it does not
])
def test_carry_header_field_rename(tmp_path, monkeypatch, capsys, old, new, reason):
    # MpSettings unk4 -> gameMode (b99abd19): the body follows a field rename of a shared include/
    # record keeping its layout; with a field's type changed too the record no longer matches
    hdr = CARVE_H.replace("    int a;\n", "    int mode;\n")
    if old:
        hdr = hdr.replace(old, new)
    _, rev_a = _carve_repo(tmp_path, monkeypatch, hdr, edit=lambda s: s.replace("p->a", "p->mode"))
    before = q.load_events()
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--dry-run"])
    out = capsys.readouterr().out
    if reason is not None:
        assert f"skipped src/global/x.c: f: not a pure rename; body or a declaration it uses changed{reason}" in out
        assert "would carry 0 events" in out
        return
    assert "would carry src/global/x.c: f: remove, review, views (renames; record field renames: S)" in out
    assert "would carry 3 events" in out and "skipped" not in out and q.load_events() == before
    q.main(["carry", "--rev", rev_a, "--unit", "u2"])
    st = _carve_state()
    assert st["f"] == {"views": "✓", "review": "✓", "remove": "✓"}


def test_carry_header_field_fold_is_no_rename(tmp_path, monkeypatch, capsys):
    # D_807552EC -> D_807552E4.matchPhase: a global replaced by a field access changes the body
    _, rev_a = _carve_repo(tmp_path, monkeypatch, CARVE_H + "extern S gS;\n", ret="gB",
                           edit=lambda s: s.replace("return gB;", "return gS.b;"),
                           old_header=CARVE_H + "extern int gB;\nextern S gS;\n")
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--dry-run"])
    out = capsys.readouterr().out
    assert "skipped src/global/x.c: f: not a pure rename" in out and "would carry 0 events" in out


def test_carry_func_limits_functions(tmp_path, monkeypatch, capsys):
    hdr = CARVE_H.replace("    int a;\n", "    int mode;\n")
    _, rev_a = _carve_repo(tmp_path, monkeypatch, hdr, edit=lambda s: s.replace("p->a", "p->mode").replace(
        "int h(int x) {\n    return x;", "int h(int y) {\n    return y;"))
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--dry-run"])
    out = capsys.readouterr().out
    assert "would carry src/global/x.c: f: " in out and "would carry src/global/x.c: h: views" in out
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--dry-run", "--func", "h"])
    out = capsys.readouterr().out
    assert "x.c: f:" not in out and "would carry src/global/x.c: h: views" in out
    assert "would carry 1 events" in out
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--header-carve", "--dry-run", "--func", "f"])
    out = capsys.readouterr().out
    assert "x.c: h:" not in out


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


MOVE_REC = "    int a;\n    char b;\n    short pad6;\n"
MOVE_FN = "extern Info gInfo[];\nint f(int i) {\n    if (gInfo[i].a) {} // FAKE: steers\n    return gInfo[i].b;\n}\n"


@pytest.mark.parametrize("direction,new_rec,reason", [
    ("to", MOVE_REC, None),  # anonymous typedef in x.c -> tagged typedef in include/info.h
    ("to", MOVE_REC.replace("pad6", "unk6"), "Info moved to include/info.h, changed: Info pad6 -> unk6"),
    ("to", MOVE_REC.replace("short pad6", "u16 pad6"), "Info moved to include/info.h, changed: "
                                                       "Info pad6 type short -> unsigned short"),
    ("from", MOVE_REC, None),  # include/info.h keeps other declarations, x.c gains Info
])
def test_carry_declaration_moved_between_file_and_header(tmp_path, monkeypatch, capsys, direction, new_rec, reason):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    (repo / "include").mkdir()
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "_htext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    src, hdr = repo / "src" / "global" / "x.c", repo / "include" / "info.h"
    local = "typedef struct {\n%s} Info;\n"
    shared = "typedef unsigned short u16;\n"
    tagged = shared + "typedef struct Info {\n%s} Info;\n"
    if direction == "to":
        hdr.write_text(shared)
        src.write_text('#include "info.h"\n' + local % MOVE_REC + MOVE_FN)
    else:
        hdr.write_text(tagged % MOVE_REC)
        src.write_text('#include "info.h"\n' + MOVE_FN)
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "a")
    rev_a = _git(repo, "rev-parse", "HEAD")
    fn = dict(q.analyze("src/global/x.c", "global")["functions"][0], file="src/global/x.c")
    site = fn["sites"][0]
    q.append_events([q.event("u1", "sweep", fn, site, "remove", "nohit"),
                     q.event("u1", "a", fn, None, "views", "nohit", note="no views left"),
                     q.event("u1", "a", fn, None, "review", "nohit", note=REVIEW),
                     q.event("u1", "a", fn, site, "diagnose", "nohit", quirks=["Q0001"])])
    if direction == "to":
        hdr.write_text(tagged % new_rec)
        src.write_text('#include "info.h"\n' + MOVE_FN)
    else:
        hdr.write_text(shared)
        src.write_text('#include "info.h"\n' + local % new_rec + MOVE_FN)
    _git(repo, "commit", "-qam", "b")
    monkeypatch.setattr(q, "_htext", {})
    new = dict(q.analyze("src/global/x.c", "global")["functions"][0], file="src/global/x.c")
    by_site, by_func = q.index_events(q.load_events())
    assert q.function_state(new, by_site, by_func)["review"] != "✓"  # x.c's file scope changed
    before = q.load_events()
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--dry-run"])
    out = capsys.readouterr().out
    assert q.load_events() == before
    if reason is not None:
        assert f"skipped src/global/x.c: f: not a pure rename; body or a declaration it uses changed ({reason})" in out
        assert "would carry 0 events" in out
        return
    how = f"moved {direction} include/info.h, identical"
    assert f"would carry src/global/x.c: f: diagnose, remove, review, views ({how})" in out
    assert "would carry 4 events" in out and "skipped" not in out
    q.main(["carry", "--rev", rev_a, "--unit", "u2"])
    carried = [e for e in q.load_events() if e.get("agent") == "carry"]
    assert all(e["note"].startswith(f"carried from {rev_a} ({how})") for e in carried)
    by_site, by_func = q.index_events(q.load_events())
    fp, fevs = (new["fp_local"], new["fp_hdr"], new["fp_hdr2"]), by_func[("global", "80600000")]
    assert {m: q.mark(fevs, m, fp, "f")[0] for m in ("views", "review")} == {"views": "✓", "review": "✓"}
    assert q.mark(by_site[new["sites"][0]["key"]], "remove", fp, "f")[0] == "✓"


RESPELL_FN = "int f(char *d, char *s) {\n    if (d) {} // FAKE: steers\n    memcpy(d, s, 4);\n    return d[0];\n}\n"


@pytest.mark.parametrize("hdr_decl,reason", [
    ("typedef unsigned int size_t;\nvoid *memcpy(void *, const void *, size_t);\n", None),
    ("typedef int size_t;\nvoid *memcpy(void *, const void *, size_t);\n",  # parameter type differs
     "memcpy moved to include/memory.h, changed"),
    ("void *memcpy();\n", "memcpy moved to include/memory.h, changed"),  # K&R vs prototyped
])
def test_carry_declaration_respelled_same_type(tmp_path, monkeypatch, capsys, hdr_decl, reason):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    (repo / "include").mkdir()
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "_htext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    src, hdr = repo / "src" / "global" / "x.c", repo / "include" / "memory.h"
    src.write_text("void *memcpy(void *, const void *, unsigned int);\n" + RESPELL_FN)
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "a")
    rev_a = _git(repo, "rev-parse", "HEAD")
    fn = dict(q.analyze("src/global/x.c", "global")["functions"][0], file="src/global/x.c")
    site = fn["sites"][0]
    q.append_events([q.event("u1", "sweep", fn, site, "remove", "nohit"),
                     q.event("u1", "a", fn, None, "views", "nohit", note="no views left"),
                     q.event("u1", "a", fn, None, "review", "nohit", note=REVIEW),
                     q.event("u1", "a", fn, site, "diagnose", "nohit", quirks=["Q0001"])])
    hdr.write_text(hdr_decl)
    src.write_text('#include "memory.h"\n' + RESPELL_FN)
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "b")
    monkeypatch.setattr(q, "_htext", {})
    new = dict(q.analyze("src/global/x.c", "global")["functions"][0], file="src/global/x.c")
    before = q.load_events()
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--dry-run"])
    out = capsys.readouterr().out
    assert q.load_events() == before
    if reason is not None:
        assert f"skipped src/global/x.c: f: not a pure rename; body or a declaration it uses changed ({reason})" in out
        assert "would carry 0 events" in out
        return
    how = "memcpy declaration moved to include/memory.h, same type"
    assert f"would carry src/global/x.c: f: diagnose, remove, review, views ({how})" in out
    assert "would carry 4 events" in out and "skipped" not in out
    q.main(["carry", "--rev", rev_a, "--unit", "u2"])
    by_site, by_func = q.index_events(q.load_events())
    fp, fevs = (new["fp_local"], new["fp_hdr"], new["fp_hdr2"]), by_func[("global", "80600000")]
    assert {m: q.mark(fevs, m, fp, "f")[0] for m in ("views", "review")} == {"views": "✓", "review": "✓"}
    assert q.mark(by_site[new["sites"][0]["key"]], "remove", fp, "f")[0] == "✓"


TYPE_FN = ("typedef struct %s {\n    char pad0[4];\n    %s a;\n} %s;\n\nextern %s *gSlots;\n\n"
           "int f(int i) {\n    %s *p = &gSlots[i];\n    if (p) {} // FAKE: steers\n"
           "    return p->a + sizeof(%s);\n}\n")


@pytest.mark.parametrize("field,reason", [("int", None), ("short", "")])  # field type changed: not identical
def test_carry_local_type_renamed(tmp_path, monkeypatch, capsys, field, reason):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    (repo / "include").mkdir()
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "_htext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    src = repo / "src" / "global" / "x.c"
    src.write_text(TYPE_FN % ("Slot", "int", "Slot", "Slot", "Slot", "Slot"))
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "a")
    rev_a = _git(repo, "rev-parse", "HEAD")
    fn = dict(q.analyze("src/global/x.c", "global")["functions"][0], file="src/global/x.c")
    q.append_events([q.event("u1", "a", fn, None, "views", "nohit", note="no views left"),
                     q.event("u1", "a", fn, None, "review", "nohit", note=REVIEW)])
    src.write_text(TYPE_FN % ("SlotView", field, "SlotView", "SlotView", "SlotView", "SlotView"))
    _git(repo, "commit", "-qam", "b")
    new = dict(q.analyze("src/global/x.c", "global")["functions"][0], file="src/global/x.c")
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--dry-run"])
    out = capsys.readouterr().out
    if reason is not None:
        assert "skipped src/global/x.c: f: not a pure rename; body or a declaration it uses changed" in out
        assert "would carry 0 events" in out
        return
    how = "type Slot renamed SlotView, identical"
    assert f"would carry src/global/x.c: f: review, views ({how})" in out
    assert "would carry 2 events" in out and "skipped" not in out
    q.main(["carry", "--rev", rev_a, "--unit", "u2"])
    by_site, by_func = q.index_events(q.load_events())
    fp, fevs = (new["fp_local"], new["fp_hdr"], new["fp_hdr2"]), by_func[("global", "80600000")]
    assert {m: q.mark(fevs, m, fp, "f")[0] for m in ("views", "review")} == {"views": "✓", "review": "✓"}


LOCAL_REC = ("typedef struct T {\n    int unk0;\n    short unk4;\n    short unk6;\n"
             "    struct {\n        short unk0;\n        short unk2;\n    } arr[2];\n} T;\n")
LOCAL_FN = ('#include "g.h"\n%s%s'
            "int f(T *p) {\n    if (p) {} // FAKE: steers\n    return p->unk0 + gG.v + %s;\n}\n")


@pytest.mark.parametrize("rec,body,how", [
    # 80150.c TagBarrelActorState (23d222d5): unread fields renamed, body unchanged
    ((("unk4", "destMap"), ("unk6", "pad6"), ("unk2", "frame")), "0", "record field renames: T"),
    # ... and the body following the renames, a nested unnamed record's field too (ActorAnimLookup)
    ((("unk4", "destMap"), ("unk2", "frame")), "p->unk4 + p->arr[1].unk2", "renames; record field renames: T"),
    ((("short unk4", "int destMap"), ("short unk6;\n", "")), "0", None),  # layout changed
    ((("short unk4", "unsigned short destMap"),), "0", None),  # a field's type changed
    ((("short unk2", "unsigned short frame"),), "0", None),  # a nested field's type changed
])
def test_carry_local_record_field_rename(tmp_path, monkeypatch, capsys, rec, body, how):
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    (repo / "include").mkdir()
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "_htext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    (repo / "include" / "g.h").write_text("typedef struct G {\n    int v;\n} G;\nextern G gG;\n")
    src = repo / "src" / "global" / "x.c"
    # gActorGlobalState: a redundant extern, declared identically in an included header, removed
    src.write_text(LOCAL_FN % (LOCAL_REC, "extern G gG;\n", body))
    _git(repo, "add", "-A")
    _git(repo, "commit", "-qm", "a")
    rev_a = _git(repo, "rev-parse", "HEAD")
    fn = dict(q.analyze("src/global/x.c", "global")["functions"][0], file="src/global/x.c")
    q.append_events([q.event("u1", "sweep", fn, fn["sites"][0], "remove", "nohit"),
                     q.event("u1", "a", fn, None, "views", "nohit", note="no views left"),
                     q.event("u1", "a", fn, None, "review", "nohit", note=REVIEW)])
    new_rec, new_body = LOCAL_REC, body
    for old, new in rec:
        new_rec = new_rec.replace(old, new)
        new_body = new_body.replace(old.split()[-1], new.split()[-1] if new else "")
    src.write_text(LOCAL_FN % (new_rec, "", new_body))
    _git(repo, "commit", "-qam", "b")
    capsys.readouterr()
    q.main(["carry", "--rev", rev_a, "--unit", "u2", "--dry-run"])
    out = capsys.readouterr().out
    if how is None:
        assert "skipped src/global/x.c: f: not a pure rename; body or a declaration it uses changed (layout changed: T" \
            in out
        assert "would carry 0 events" in out
        return
    how += "; gG declaration respelled, same type"
    assert f"would carry src/global/x.c: f: remove, review, views ({how})" in out
    assert "would carry 3 events" in out and "skipped" not in out
    q.main(["carry", "--rev", rev_a, "--unit", "u2"])
    new = dict(q.analyze("src/global/x.c", "global")["functions"][0], file="src/global/x.c")
    by_site, by_func = q.index_events(q.load_events())
    fp, fevs = (new["fp_local"], new["fp_hdr"], new["fp_hdr2"]), by_func[("global", "80600000")]
    assert {m: q.mark(fevs, m, fp, "f")[0] for m in ("views", "review")} == {"views": "✓", "review": "✓"}
    assert q.mark(by_site[new["sites"][0]["key"]], "remove", fp, "f")[0] == "✓"


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
    ledger_path = tmp_path / "quality"
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
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
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
    monkeypatch.setattr(q.cwarn, "collect", lambda items, rev=None: [warns])
    an = q.analyze(str(c), "global")
    fn, = an["functions"]
    s, = fn["sites"]
    assert (s["kind"], s["line"], s["warning"]) == ("warning", 4, "712 illegal combination of pointer and integer")
    assert re.fullmatch(r"global:80600000:warning:[0-9a-f]{6}", s["key"])
    assert an["warnings"] == 2


def test_analyze_warning_site_from_subdirectory_cwd(tmp_path, monkeypatch):
    """ROOT-relative paths (from git grep, the ledger) are never re-resolved against the process cwd:
    run from a subdirectory, the cfe warning (path rel()'d by cwarn) still lands on the analysed file."""
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    c = tmp_path / "x.c"
    c.write_text("typedef int s32;\ns32 *g;\nvoid f(s32 x) {\n    g = x;\n}\n")
    path = q.rel(str(c))  # ROOT-relative, as Resolver.files() gets it from git grep
    monkeypatch.setattr(q.cwarn, "collect", lambda items, rev=None: [
        [dict(code=712, path=q.cwarn.rel(p), line=4, col=6, msg="illegal combination of pointer and integer")]
        for p, _, _ in items])
    monkeypatch.chdir(os.path.join(q.ROOT, "tools", "tests"))
    assert q.rel(path) == path and q.cwarn.rel(path) == path
    assert q.cli_path("test_quality.py") == os.path.join("tools", "tests", "test_quality.py")
    an = q.analyze(path, "global")
    fn, = an["functions"]
    s, = fn["sites"]
    assert (s["kind"], s["line"]) == ("warning", 4)


def test_record_base_compiles_rev_text_against_rev_headers(tmp_path, monkeypatch):
    """A merge renamed S.b to S.c in include/s.h: the base text no longer compiles against the current
    include/. record --base compiles it against the base's include/ (exported, cwd of the compile) and
    resolves the base's warning site; a base that cannot compile names the file, rev and cfe error."""
    repo = tmp_path.resolve() / "repo"
    (repo / "src" / "global").mkdir(parents=True)
    (repo / "include").mkdir()
    monkeypatch.chdir(repo)
    for mod in (q, q.clint, q.ledger, q.cwarn):
        monkeypatch.setattr(mod, "ROOT", str(repo))
    monkeypatch.setattr(q.cwarn, "SCRATCH", str(repo / ".scratch" / "cwarn"))
    monkeypatch.setattr(q.cwarn, "_static", {"key": ("makefile", "include")})
    monkeypatch.setattr(q.cwarn, "collect", REAL_COLLECT)
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
    monkeypatch.setattr(q, "_know", {})
    monkeypatch.setattr(q, "_symtext", {})
    monkeypatch.setattr(q, "_htext", {})
    monkeypatch.setattr(q, "resolve_vram", lambda seg, name, src: 0x80600000)
    monkeypatch.setattr(q, "names_at", lambda seg, vram: ["f"])

    def run_jobs(jobs):  # IDO stand-in: `p->F` needs `int F;` in include/s.h of the compile's cwd
        out = []
        for job in jobs:
            cwd = repo / job.get("cwd", "")
            hdr = (cwd / "include" / "s.h").read_text()
            res = {"rc": 0, "out": ""}
            for n, line in enumerate((cwd / job["input"]).read_text().split("\n"), 1):
                for f in re.findall(r"p->(\w+)", line):
                    if f"int {f};" in hdr:
                        res["out"] += f"cfe: Warning 712: {job['input']}, line {n}: illegal combination\n"
                    else:
                        res = {"rc": 1, "out": f"cfe: Error: {job['input']}, line {n}: unknown field {f}\n"}
            out.append(res)
        return out

    monkeypatch.setattr(q.cwarn, "run_jobs", run_jobs)
    _git(repo, "init", "-q")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    hdr = "typedef struct S {\n    int a;\n    int %s;\n} S;\n"
    body = '#include "s.h"\nint f(S *p) {\n    return p->%s;\n}\n'
    revs = {}
    for name, field, used in (("broken", "b", "z"), ("base", "b", "b"), ("head", "c", "c")):
        (repo / "include" / "s.h").write_text(hdr % field)
        (repo / "src" / "global" / "x.c").write_text(body % used)
        _git(repo, "add", "-A", "include", "src")
        _git(repo, "commit", "-qm", name)
        revs[name] = _git(repo, "rev-parse", "HEAD")
    base_text = body % "b"
    with pytest.raises(q.cwarn.CompileError):  # the bug: base text, current headers
        q.analyze("src/global/x.c", "global", text=base_text)
    key = "global:80600000:warning:" + q.ledger.sha1("712\0" + q.norm(["    return p->b;"]))[:6]
    batch = tmp_path / "batch.txt"
    batch.write_text(f'{key} retype kept note="tried s32 *g; fdiff=3"\n')
    q.main(["record", "--unit", "u1", "--agent", "a", "--base", revs["base"], "--batch", str(batch)])
    e, = [e for e in q.load_events() if e.get("type") == "quality"]
    assert (e["site"], e["method"]) == (key, "retype")
    assert e["fp_hdr"] == q.fp_hdr(base_text, "src/global", {"include/s.h": hdr % "b"})

    with pytest.raises(SystemExit) as ex:
        q.main(["record", "--unit", "u1", "--agent", "a", "--base", revs["broken"], "--batch", str(batch)])
    msg = str(ex.value.code)
    assert msg.startswith(f"record: cannot compile src/global/x.c at {revs['broken']}: cfe: Error: ")
    assert msg.endswith("line 3: unknown field z")


def test_backfill_models_from_transcripts(tmp_path, monkeypatch, capsys):
    monkeypatch.setattr(q, "LEDGER", str(tmp_path / "quality"))
    sess = tmp_path / "S" / "2026-01-01T00-00-00-000Z_x"
    sess.mkdir(parents=True)
    rows = [{"type": "session", "timestamp": "2026-01-01T10:00:00.000Z"},
            {"type": "thinking_level_change", "timestamp": "2026-01-01T10:00:00.100Z", "thinkingLevel": "xhigh"},
            {"type": "message", "timestamp": "2026-01-01T10:00:01.000Z",
             "message": {"role": "assistant", "provider": "anthropic", "model": "claude-opus-5-5"}}]
    (sess / "CleanX.jsonl").write_text("".join(json.dumps(r) + "\n" for r in rows))
    q.append_events([ev(SITE, "diagnose", "nohit", unit="u", agent="CleanX", t="2026-01-01T11:00:00Z"),
                     ev(SITE, "remove", "nohit", unit="u", agent="sweep", t="2026-01-01T11:00:00Z"),
                     ev(SITE, "diagnose", "nohit", unit="u2", agent="Other", t="2026-01-01T11:00:00Z")])
    q.main(["backfill-models", str(tmp_path / "S")])
    assert "filled 1 of 2 agent units (1 without a transcript)" in capsys.readouterr().out
    assert q.load_models() == {("u", "CleanX"): "anthropic/claude-opus-5-5:xhigh"}
    q.main(["backfill-models", str(tmp_path / "S")])  # already filled: nothing appended
    assert len((tmp_path / "quality" / "models.jsonl").read_text().splitlines()) == 1
