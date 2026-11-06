import sys
from pathlib import Path

import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from tools.quirks import add_entry, check, function_aliases, load, search


def _guide(root: Path, slug: str, body: str, title: str = "Guide") -> None:
    gdir = root / "guides"
    gdir.mkdir(parents=True, exist_ok=True)
    (gdir / f"{slug}.md").write_text(f'---\ntitle: "{title}"\n---\n{body}\n', encoding="utf-8")


def test_add_load_roundtrip(tmp_path):
    src = [{"path": "src/a.c", "commit": "abc", "note": "n"}]
    eid = add_entry(
        tmp_path, "Ünïcode “loops”", "cfe", ["loop", "branch-shape"], "body `x`\n\nmore",
        functions=["b", "a"], sources=src,
    )
    eid2 = add_entry(tmp_path, "other", "uopt", ["regalloc"], "b", see_also=[eid])
    e = load(tmp_path).entries[eid]
    assert (e.title, e.phase, e.symptoms) == ("Ünïcode “loops”", "cfe", ["loop", "branch-shape"])
    assert e.functions == ["a", "b"]
    assert e.sources == src
    assert e.body == "body `x`\n\nmore"
    assert load(tmp_path).entries[eid2].see_also == [eid]


def test_title_outranks_body_and_symptom_filter(tmp_path):
    a = add_entry(tmp_path, "unrolled loop priority", "uopt", ["loop"], "about something")
    b = add_entry(tmp_path, "something else", "uopt", ["regalloc"], "mentions unrolled once here")
    _guide(tmp_path, "g", "## Unrolled\nunrolled loop text")
    corpus = load(tmp_path)
    ids = [h.id for h in search(corpus, "unrolled")]
    assert ids.index(a) < ids.index(b)
    assert "g#1" in ids
    filtered = [h.id for h in search(corpus, "unrolled", symptoms=["loop"])]
    assert filtered == [a]


def test_function_aliases(tmp_path):
    (tmp_path / "symbol_addrs.bonus.us.txt").write_text(
        "fooBar = 0x80024000; // type:func\nD_1 = 0x80024010; // type:s32\n"
    )
    assert "func_80024000" in function_aliases("fooBar", tmp_path)
    assert "fooBar" in function_aliases("func_80024000", tmp_path)
    assert function_aliases("D_1", tmp_path) == {"D_1"}


def test_next_id_and_validation(tmp_path):
    edir = tmp_path / "entries"
    edir.mkdir()
    for n in ("Q0001", "Q0006"):
        (edir / f"{n}.md").write_text('---\ntitle: "t"\n---\nb\n')
    assert add_entry(tmp_path, "t", "cfe", ["loop"], "b") == "Q0007"
    with pytest.raises(ValueError, match="unknown symptom"):
        add_entry(tmp_path, "t", "cfe", ["nope"], "b")


def test_check_reports_dangling_and_phase(tmp_path):
    eid = add_entry(tmp_path, "t", "cfe", ["loop"], "b", see_also=["Q0999"])
    p = tmp_path / "entries" / f"{eid}.md"
    p.write_text(p.read_text().replace('"cfe"', '"bogus"'))
    probs = check(load(tmp_path))
    assert any("Q0999" in x for x in probs)
    assert any("bogus" in x for x in probs)
    assert check(load(tmp_path / "missing")) == []


def test_guide_chunking(tmp_path):
    para = ("word " * 199).strip()  # 994 chars
    long_section = "\n\n".join([para] * 7)  # ~7000 chars
    _guide(tmp_path, "g", f"intro text\n\n## A\naaa\n### B\n{long_section}\n## Sources\n[^x]: y")
    chunks = load(tmp_path).guides["g"].chunks
    assert chunks[0].heading == "intro" and chunks[1].heading == "A"
    b = [c for c in chunks if c.heading == "B"]
    assert len(b) >= 3 and all(len(c.text) <= 3000 for c in b)
    assert not any(c.heading == "Sources" for c in chunks)
    assert [c.id for c in chunks] == [f"g#{i}" for i in range(1, len(chunks) + 1)]
