"""In-container GDB Python helper for memory inspection and modification.

Runs inside gdb-multiarch via:
  gdb-multiarch -batch -x /opt/emu/gdb_helper.py
Controlled by environment variables:
  GDB_PORT   - target remote port (default: 9123)
  GDB_ACTION - "read", "read32", "write"
  GDB_ADDR   - hex or decimal address (e.g. "0x805FF378")
  GDB_LEN    - length in bytes for read (e.g. "16")
  GDB_DATA   - hex string for write (e.g. "deadbeef")
"""

import os
import sys

try:
    import gdb
except ImportError:
    print("Error: must be run inside gdb-multiarch", file=sys.stderr)
    sys.exit(1)

def main():
    port = os.environ.get("GDB_PORT", "9123")
    action = os.environ.get("GDB_ACTION", "read32")
    addr_str = os.environ.get("GDB_ADDR", "0x80000000")
    addr = int(addr_str, 0)

    gdb.execute("set architecture mips:4000", to_string=True)
    gdb.execute(f"target remote 127.0.0.1:{port}", to_string=True)
    inf = gdb.selected_inferior()

    try:
        if action == "read32":
            data = inf.read_memory(addr, 4).tobytes()
            val = int.from_bytes(data, byteorder="big")
            print(f"0x{val:08X}")
        elif action == "read":
            length = int(os.environ.get("GDB_LEN", "16"), 0)
            data = inf.read_memory(addr, length).tobytes()
            # Format hex dump (16 bytes per line)
            for offset in range(0, len(data), 16):
                chunk = data[offset:offset + 16]
                hex_part = " ".join(f"{b:02x}" for b in chunk)
                ascii_part = "".join(chr(b) if 32 <= b < 127 else "." for b in chunk)
                print(f"0x{addr + offset:08x}:  {hex_part:<48}  |{ascii_part}|")
        elif action == "write":
            hex_data = os.environ.get("GDB_DATA", "")
            payload = bytes.fromhex(hex_data)
            inf.write_memory(addr, payload)
            print(f"Wrote {len(payload)} bytes to 0x{addr:08X}")
        else:
            print(f"Unknown action: {action}", file=sys.stderr)
    finally:
        try:
            gdb.execute("detach", to_string=True)
        except Exception:
            pass

main()
