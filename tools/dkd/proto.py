"""dkd wire protocol shared by tools/dkd/client.py (host, Python 3.9) and server.py (container).

Frame: struct "!BI" header (type, payload length) followed by the payload. JSON payloads are
UTF-8 objects; STDOUT/STDERR payloads are raw bytes. See the type constants below.
"""
import hashlib
import json
import os
import struct

PORT = 7564
INTERNAL_SOCK = "/run/dkd/internal.sock"
HEADER = struct.Struct("!BI")
MAX_PAYLOAD = 64 * 1024 * 1024
DKD_ERROR = 125

# client -> server
HELLO = 0x01
RUN = 0x02
SIGNAL = 0x03
HOLD = 0x04
RETIRE = 0x05
STATUS = 0x06
UPGRADE = 0x07
STANDALONE = 0x08

# server -> client
HELLO_OK = 0x81
STDOUT = 0x82
STDERR = 0x83
EXIT = 0x84
WAITING = 0x85
GRANTED = 0x86
LEASE = 0x87
ERROR = 0x88
RETIRED = 0x89
STATUS_REPLY = 0x8A

JSON_TYPES = frozenset(
    {HELLO, RUN, SIGNAL, HOLD, RETIRE, STATUS, UPGRADE, STANDALONE,
     HELLO_OK, EXIT, WAITING, GRANTED, LEASE, ERROR, RETIRED, STATUS_REPLY}
)
BYTES_TYPES = frozenset({STDOUT, STDERR})

# Files whose content defines the server's behaviour; a running server whose hash differs
# from the client's is retired and restarted.
CODE_FILES = ("tools/dkd/proto.py", "tools/dkd/server.py", "tools/dkd/locks.py",
              "tools/dkd/classify.py", "tools/dkd/shims/make")


class ProtocolError(Exception):
    pass


def encode(ftype, payload):
    """Build one frame. payload: dict for JSON types, bytes for STDOUT/STDERR."""
    if ftype in BYTES_TYPES:
        data = bytes(payload)
    elif ftype in JSON_TYPES:
        data = json.dumps(payload, separators=(",", ":")).encode("utf-8")
    else:
        raise ProtocolError("unknown frame type 0x%02x" % ftype)
    if len(data) > MAX_PAYLOAD:
        raise ProtocolError("payload too large")
    return HEADER.pack(ftype, len(data)) + data


def decode_payload(ftype, data):
    if ftype in BYTES_TYPES:
        return data
    if ftype in JSON_TYPES:
        try:
            obj = json.loads(data.decode("utf-8"))
        except ValueError as e:
            raise ProtocolError("bad JSON payload: %s" % e)
        if not isinstance(obj, dict):
            raise ProtocolError("JSON payload is not an object")
        return obj
    raise ProtocolError("unknown frame type 0x%02x" % ftype)


def recv_exact(sock, n):
    """Blocking socket read of exactly n bytes; returns None on clean EOF before any byte."""
    buf = bytearray()
    while len(buf) < n:
        chunk = sock.recv(n - len(buf))
        if not chunk:
            if not buf:
                return None
            raise ProtocolError("connection closed mid-frame")
        buf += chunk
    return bytes(buf)


def recv_frame(sock):
    """Blocking read of one frame -> (type, payload) or None on EOF at a frame boundary."""
    head = recv_exact(sock, HEADER.size)
    if head is None:
        return None
    ftype, length = HEADER.unpack(head)
    if length > MAX_PAYLOAD:
        raise ProtocolError("payload too large")
    data = recv_exact(sock, length) if length else b""
    if data is None:
        raise ProtocolError("connection closed mid-frame")
    return ftype, decode_payload(ftype, data)


async def read_frame(reader):
    """asyncio StreamReader variant -> (type, payload) or None on EOF at a frame boundary."""
    import asyncio
    try:
        head = await reader.readexactly(HEADER.size)
    except asyncio.IncompleteReadError as e:
        if not e.partial:
            return None
        raise ProtocolError("connection closed mid-frame")
    ftype, length = HEADER.unpack(head)
    if length > MAX_PAYLOAD:
        raise ProtocolError("payload too large")
    try:
        data = await reader.readexactly(length) if length else b""
    except asyncio.IncompleteReadError:
        raise ProtocolError("connection closed mid-frame")
    return ftype, decode_payload(ftype, data)


def code_hash(root):
    """sha256 over CODE_FILES (path + content) under repo root; missing files hash as absent."""
    h = hashlib.sha256()
    for rel in CODE_FILES:
        h.update(rel.encode() + b"\0")
        try:
            with open(os.path.join(root, rel), "rb") as f:
                h.update(f.read())
        except FileNotFoundError:
            h.update(b"<absent>")
        h.update(b"\0")
    return h.hexdigest()
