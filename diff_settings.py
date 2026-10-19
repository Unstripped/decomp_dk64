import os
import sys

OVERLAYS = {
    "multiplayer": "ovl02",
    "minecart": "ovl03",
    "bonus": "ovl04",
    "race": "ovl05",
    "critter": "ovl06",
    "boss": "ovl07",
    "arcade": "ovl08",
    "jetpac": "ovl09",
    "menu": "ovl10",
}

SEGMENT_ALIASES = {
    "ovl02": "multiplayer",
    "ovl03": "minecart",
    "ovl04": "bonus",
    "ovl05": "race",
    "ovl06": "critter",
    "ovl07": "boss",
    "ovl08": "arcade",
    "ovl09": "jetpac",
    "ovl10": "menu",
}


def add_custom_arguments(parser):
    parser.add_argument(
        "--segment",
        default=None,
        help="Segment to diff: boot (default), global, or overlay name (multiplayer, minecart, bonus, race, critter, boss, arcade, jetpac, menu)",
    )
    parser.add_argument(
        "-n",
        "--no-make",
        action="store_true",
        help="Do not automatically run make before diffing",
    )


def apply(config, args):
    segment = None
    if args is not None:
        segment = getattr(args, "segment", None)
    if not segment:
        segment = os.environ.get("DIFF_SEGMENT") or "boot"

    segment = segment.lower()
    segment = SEGMENT_ALIASES.get(segment, segment)

    if segment == "boot":
        config["mapfile"] = "build/dk64.us.map"
        config["myimg"] = "build/boot.bin"
        config["baseimg"] = "baserom.us.z64"
    elif segment == "global":
        config["mapfile"] = "build/global.map"
        config["myimg"] = "build/global.bin"
        config["baseimg"] = "bin/segments/global.bin"
    elif segment in OVERLAYS:
        ovl_seg = OVERLAYS[segment]
        config["mapfile"] = f"build/{segment}.map"
        config["myimg"] = f"build/{segment}.bin"
        config["baseimg"] = f"bin/segments/{ovl_seg}.bin"
    else:
        valid = ["boot", "global"] + list(OVERLAYS.keys())
        sys.exit(
            f"diff_settings: unknown segment '{segment}'. Valid segments: {', '.join(valid)}"
        )
    if args is not None and hasattr(args, "no_pager"):
        import shutil
        if not sys.stdout.isatty() or shutil.which("less") is None:
            args.no_pager = True

    config["arch"] = "mips"
    config["objdump_executable"] = "mips-linux-gnu-objdump"
    config["source_directories"] = ["src", "include"]
    config["map_format"] = "gnu"
    config["build_dir"] = "build"
    config["make_command"] = ["make"]

    if args is not None and hasattr(args, "make"):
        args.make = not getattr(args, "no_make", False)


def map_build_target(make_target: str) -> str:
    return make_target


def watch_sources_for_target(make_target: str):
    return ["src", "include", "asm"]
