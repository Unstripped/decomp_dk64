import os
import re
import sys
from pathlib import Path, PurePosixPath, PureWindowsPath

import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent.parent
EMU_DIR = REPO_ROOT / "tools" / "emu"
if str(EMU_DIR) not in sys.path:
    sys.path.insert(0, str(EMU_DIR))

import emu  # noqa: E402


def test_container_path_uses_forward_slashes_for_a_windows_host_path():
    root = PureWindowsPath("C:/Users/x/decomp_dk64")
    p = root / "emu" / "maps" / "map_0x07.png"
    assert emu.container_path(p, root) == "/dk64/emu/maps/map_0x07.png"
    assert emu.container_path(root / ".scratch" / "EmuNames27" / "qcb.gdb", root) == "/dk64/.scratch/EmuNames27/qcb.gdb"


def test_container_path_posix_and_outside_the_repo():
    root = PurePosixPath("/home/x/decomp_dk64")
    assert emu.container_path(root / "build" / "dk64.us.elf", root) == "/dk64/build/dk64.us.elf"
    assert emu.container_path(PurePosixPath("/tmp/a.png"), root) is None
    assert emu.container_path(PureWindowsPath("D:/elsewhere/a.png"), PureWindowsPath("C:/repo")) is None


def test_container_path_defaults_to_the_repo_root():
    assert emu.container_path(emu.REPO_ROOT / "emu" / "maps" / "a.png") == "/dk64/emu/maps/a.png"


def test_no_container_path_is_built_from_str_of_a_relative_host_path():
    # `f"/dk64/{rel}"` / `"/dk64/" + str(rel)` put backslashes into the container command on Windows
    bad = re.compile(r'"/dk64/"\s*\+\s*str\(|f"/dk64/\{(rel|path|p)[}.]')
    for f in sorted(EMU_DIR.glob("*.py")):
        for n, line in enumerate(f.read_text(encoding="utf-8").splitlines(), 1):
            assert not bad.search(line), f"{f.name}:{n}: {line.strip()}"


def test_link_present_tolerates_an_unreadable_container_made_link(tmp_path, monkeypatch):
    assert emu._link_present(tmp_path / "missing") is False
    (tmp_path / "there").write_bytes(b"")
    assert emu._link_present(tmp_path / "there") is True

    def lstat(p):
        raise OSError(1920, "The file cannot be accessed by the system")  # WinError 1920

    monkeypatch.setattr(os, "lstat", lstat)
    assert emu._link_present(tmp_path / "Nintendo 64") is True  # present, never raises


def test_states_link_is_not_made_by_a_windows_host(tmp_path, monkeypatch):
    calls = []
    monkeypatch.setattr(Path, "symlink_to", lambda self, target, *a, **k: calls.append((self.name, target)))
    emu.ensure_states_link(tmp_path, windows=True)
    assert calls == []  # the container's entrypoint.sh makes it
    emu.ensure_states_link(tmp_path, windows=False)
    assert calls == [("Nintendo 64", ".")]


def test_states_link_not_recreated_when_the_link_is_unreadable(tmp_path, monkeypatch):
    calls = []
    monkeypatch.setattr(Path, "symlink_to", lambda self, target, *a, **k: calls.append(self.name))

    def lstat(p):
        raise OSError(1920, "The file cannot be accessed by the system")

    monkeypatch.setattr(os, "lstat", lstat)
    emu.ensure_states_link(tmp_path, windows=False)
    assert calls == []


def test_get_session_states_dir_survives_an_existing_link(tmp_path, monkeypatch):
    monkeypatch.setattr(emu, "REPO_ROOT", tmp_path)
    d = emu.get_session_states_dir("s")
    assert d == tmp_path / "emu" / "sessions" / "s" / "states" and d.is_dir()
    assert emu.get_session_states_dir("s") == d  # second start of the same session
