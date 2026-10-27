"""Pure, synchronous reader/writer lock manager for dkd (no I/O, no asyncio, no clocks).

Three lock modes:

* ``SHARED``    - read-only users of the shared tree (fdiff, objdiff, compilers, ...).
* ``KEYED``     - writers of independent outputs, identified by a non-empty set of keys
                  (object-file paths).  Two KEYED requests conflict iff their key sets
                  intersect.
* ``EXCLUSIVE`` - rewrites shared outputs (``make``, ``make split``, ``make expected``, ...).

Compatibility matrix (symmetric)::

    SHARED    ~ SHARED     ok
    SHARED    ~ KEYED      ok
    KEYED     ~ KEYED      ok iff the key sets are disjoint
    EXCLUSIVE ~ anything   conflict (including another EXCLUSIVE)

Queue and grant policy
----------------------
The manager keeps two queues that are scanned as ONE sequence, in this order:

1. pending UPGRADE entries (see below), then
2. ordinary waiters (``request``) in arrival order.

A single scan walks the sequence and grants an entry E iff E is compatible with every currently
granted holder AND with every EARLIER entry that is still waiting (pending upgrade entries count
as earlier than every ordinary waiter and are compared by their TARGET mode/keys).  The one
exception to "every granted holder" is an atomic upgrade entry, which is compared with every
granted holder except its own holder.  Consequences:

* safety      - two incompatible holders are never granted at the same time;
* no barging  - once an EXCLUSIVE waits, nothing arriving after it is granted before it; a
                waiter can only be overtaken by later waiters that are compatible with it
                (and with everything ahead of them);
* liveness    - when nothing is granted, the head of the sequence is granted;
* determinism - the outcome depends only on the sequence of calls; newly granted holders are
                reported in scan order.

A single scan is a fixed point: granting an entry (or strengthening a grant by an upgrade) only
adds constraints to the granted set, which can only make earlier entries *less* grantable, so no
second pass is ever needed.

Atomic upgrades
---------------
A holder that already holds a grant and needs a stronger one calls ``upgrade``.  Releasing its
grant first and re-requesting would open a gap in which conflicting holders get in, so instead
the *target* grant ``combine(current, requested)`` (EXCLUSIVE if either side is; else KEYED with
the union of keys, SHARED counting as no keys; SHARED+SHARED = SHARED) is queued as a pending
upgrade entry:

* ATOMIC path - used when no other holder has a pending atomic upgrade.  The holder KEEPS its
  current grant while waiting (it still shows in ``granted()`` with the current grant) and the
  entry goes to the FRONT of the upgrade queue.  It is grantable iff the target is compatible
  with every granted holder other than itself and with every earlier entry still waiting.  On
  grant the holder's grant becomes the target, in place.
* VICTIM path - used when another holder already has a pending atomic upgrade.  The holder's
  grant is RELEASED (which may grant others, or complete the pending atomic upgrade) and the
  target is queued, holding nothing, at the END of the upgrade queue, i.e. behind the atomic
  entry and the earlier victims but ahead of all ordinary waiters.

Why at most one atomic upgrader is deadlock-free: an atomic upgrader keeps a grant while it
waits, so it must never wait (directly or transitively) for something that waits for it.  The
atomic entry is kept first in the sequence, so no earlier entry can block it; the only things it
waits for are granted holders other than itself.  With at most one atomic upgrader, every one of
those holders is *running* (it has no pending entry), so it will eventually release, and the
upgrader is then granted.  Every other waiting entry (victim or ordinary) holds nothing, so it
cannot be waited for by anyone; it waits only for running holders and for entries ahead of it,
which by induction make progress.  Two simultaneous atomic upgraders could each wait for the
other's current grant, hence the second one becomes a victim.  (A new atomic upgrade, when only
victim entries are pending, is inserted ahead of them for the same reason: a victim ahead of an
atomic upgrader could be blocked by the upgrader's current grant while the upgrader waits for
the victim.)

Holder ids are caller-chosen strings, unique among live requests (granted, waiting ordinary
requests, and victim upgrade entries).  The manager never blocks and never notifies: every
state-changing call returns the list of holders that became granted as a consequence, and the
caller (the server) wakes them.  That list includes holders whose pending upgrade just completed
(they were granted before; use ``pending_upgrades()`` before the call to tell the cases apart).

Python 3.9 compatible (imported by host-side tests); only ``typing`` generics are used.
"""
from enum import Enum
from typing import AbstractSet, Dict, FrozenSet, List, Optional, Tuple


class Mode(Enum):
    SHARED = "shared"
    KEYED = "keyed"
    EXCLUSIVE = "exclusive"


def compatible(mode_a: Mode, keys_a: AbstractSet, mode_b: Mode, keys_b: AbstractSet) -> bool:
    """True iff two requests may hold the lock at the same time."""
    if mode_a is Mode.EXCLUSIVE or mode_b is Mode.EXCLUSIVE:
        return False
    if mode_a is Mode.KEYED and mode_b is Mode.KEYED:
        return keys_a.isdisjoint(keys_b)
    return True


def combine(mode_a: Mode, keys_a: AbstractSet, mode_b: Mode, keys_b: AbstractSet) -> Tuple[Mode, FrozenSet]:
    """Weakest grant that covers both arguments (the target of an upgrade)."""
    if mode_a is Mode.EXCLUSIVE or mode_b is Mode.EXCLUSIVE:
        return Mode.EXCLUSIVE, frozenset()
    if mode_a is Mode.KEYED or mode_b is Mode.KEYED:
        return Mode.KEYED, frozenset(keys_a) | frozenset(keys_b)
    return Mode.SHARED, frozenset()


def covers(mode_a: Mode, keys_a: AbstractSet, mode_b: Mode, keys_b: AbstractSet) -> bool:
    """True iff holding (mode_a, keys_a) already satisfies a need for (mode_b, keys_b)."""
    if mode_a is Mode.EXCLUSIVE:
        return True
    if mode_b is Mode.EXCLUSIVE:
        return False
    if mode_b is Mode.SHARED:
        return True  # SHARED and KEYED both cover SHARED
    return mode_a is Mode.KEYED and frozenset(keys_b) <= frozenset(keys_a)


# (holder, target mode, target keys, atomic)
_Entry = Tuple[str, Mode, FrozenSet, bool]


class LockManager:
    """FIFO reader/writer lock table with atomic upgrades; see the module docstring."""

    def __init__(self) -> None:
        # dicts preserve insertion order: _granted is in grant order.
        self._granted = {}  # type: Dict[str, Tuple[Mode, FrozenSet]]
        self._upgrades = []  # type: List[_Entry]   # pending upgrades; an atomic one is first
        self._waiting = []  # type: List[Tuple[str, Mode, FrozenSet]]

    # -- public API ----------------------------------------------------------------------

    def request(self, holder: str, mode: Mode, keys: FrozenSet = frozenset()) -> bool:
        """Enqueue ``holder``; return True iff it was granted immediately.

        Raises ValueError for a holder id that is already live, for a KEYED request without
        keys, and for SHARED/EXCLUSIVE requests with keys; TypeError for arguments of the wrong
        type.  A rejected request leaves the manager unchanged.
        """
        keys = self._validate(holder, mode, keys)
        if self._is_live(holder):
            raise ValueError("duplicate holder %r" % (holder,))
        self._waiting.append((holder, mode, keys))
        return holder in self._schedule()

    def upgrade(self, holder: str, mode: Mode, keys: FrozenSet = frozenset()) -> Tuple[bool, List[str]]:
        """Strengthen ``holder``'s grant to ``combine(current, (mode, keys))`` atomically.

        Returns ``(granted_now, newly_granted_others)``: ``granted_now`` is True iff the holder
        holds the target grant on return (including the no-op case where its current grant
        already covers the need); ``newly_granted_others`` lists, in scan order, other holders
        that became granted (never ``holder`` itself) -- only non-empty on the VICTIM path,
        where the holder's old grant is released.

        Raises KeyError if ``holder`` is not currently granted, ValueError if it already has a
        pending upgrade, and the same ValueError/TypeError as ``request`` for bad arguments.
        A rejected call leaves the manager unchanged.
        """
        keys = self._validate(holder, mode, keys)
        if holder not in self._granted:
            raise KeyError(holder)
        if any(entry[0] == holder for entry in self._upgrades):
            raise ValueError("holder %r already has a pending upgrade" % (holder,))
        current_mode, current_keys = self._granted[holder]
        if covers(current_mode, current_keys, mode, keys):
            return True, []
        target_mode, target_keys = combine(current_mode, current_keys, mode, keys)
        if any(entry[3] for entry in self._upgrades):
            # VICTIM: another atomic upgrader is pending; give up the grant so it cannot
            # deadlock against us, and queue behind the existing upgrade entries.
            del self._granted[holder]
            self._upgrades.append((holder, target_mode, target_keys, False))
        else:
            # ATOMIC: keep the grant; go ahead of any (victim-only) pending upgrade entries.
            self._upgrades.insert(0, (holder, target_mode, target_keys, True))
        newly = self._schedule()
        return holder in newly, [h for h in newly if h != holder]

    def release(self, holder: str) -> List[str]:
        """Release a GRANTED holder; return the holders newly granted, in scan order.

        A pending atomic upgrade of the holder is dropped together with its grant.  Raises
        KeyError if ``holder`` is not currently granted (unknown, waiting, or a victim entry).
        """
        if holder not in self._granted:
            raise KeyError(holder)
        del self._granted[holder]
        self._upgrades = [entry for entry in self._upgrades if entry[0] != holder]
        return self._schedule()

    def cancel(self, holder: str) -> List[str]:
        """Remove a WAITING, GRANTED or victim-upgrading holder entirely (disconnect path).

        Drops the grant and any pending upgrade; returns newly granted holders (removing an
        entry can unblock entries queued behind it).  Raises KeyError if ``holder`` is unknown.
        """
        if holder in self._granted:
            del self._granted[holder]
            self._upgrades = [entry for entry in self._upgrades if entry[0] != holder]
        else:
            for index, entry in enumerate(self._upgrades):
                if entry[0] == holder:
                    del self._upgrades[index]
                    break
            else:
                for index, waiter in enumerate(self._waiting):
                    if waiter[0] == holder:
                        del self._waiting[index]
                        break
                else:
                    raise KeyError(holder)
        return self._schedule()

    def cancel_upgrade(self, holder: str) -> List[str]:
        """Drop only ``holder``'s pending upgrade; return newly granted holders.

        On the ATOMIC path the holder simply keeps its current grant.  On the VICTIM path the
        holder holds nothing, so the manager forgets it entirely (its id becomes reusable):
        servers should keep victim entries queued until granted or cancelled with ``cancel``.
        Raises KeyError if ``holder`` has no pending upgrade.
        """
        for index, entry in enumerate(self._upgrades):
            if entry[0] == holder:
                del self._upgrades[index]
                return self._schedule()
        raise KeyError(holder)

    def granted(self) -> Dict[str, Tuple[Mode, FrozenSet]]:
        """Snapshot of granted holders, in grant order (an atomic upgrader shows its CURRENT grant)."""
        return dict(self._granted)

    def waiting(self) -> List[Tuple[str, Mode, FrozenSet]]:
        """Snapshot of the ordinary wait queue, in queue order (pending upgrades excluded)."""
        return list(self._waiting)

    def pending_upgrades(self) -> List[Tuple[str, Mode, FrozenSet, bool]]:
        """Snapshot of pending upgrades ``(holder, target mode, target keys, atomic)`` in queue order."""
        return list(self._upgrades)

    # -- internals -----------------------------------------------------------------------

    @staticmethod
    def _validate(holder: str, mode: Mode, keys: FrozenSet) -> FrozenSet:
        if not isinstance(holder, str):
            raise TypeError("holder must be a str, got %r" % (type(holder).__name__,))
        if not isinstance(mode, Mode):
            raise TypeError("mode must be a Mode, got %r" % (type(mode).__name__,))
        if not isinstance(keys, (set, frozenset)):
            raise TypeError("keys must be a frozenset, got %r" % (type(keys).__name__,))
        keys = frozenset(keys)
        if mode is Mode.KEYED:
            if not keys:
                raise ValueError("KEYED request requires a non-empty key set")
        elif keys:
            raise ValueError("%s request must not carry keys" % (mode.name,))
        return keys

    def _is_live(self, holder: str) -> bool:
        return (
            holder in self._granted
            or any(entry[0] == holder for entry in self._upgrades)
            or any(waiter[0] == holder for waiter in self._waiting)
        )

    def _schedule(self) -> List[str]:
        """Grant every entry the policy allows (one scan); return their holders in scan order."""
        newly = []  # type: List[str]
        blocked = []  # type: List[Tuple[Mode, FrozenSet]]   # earlier entries still waiting
        upgrades = []  # type: List[_Entry]
        for entry in self._upgrades:
            holder, mode, keys, atomic = entry
            if self._grantable(holder if atomic else None, mode, keys, blocked):
                self._granted[holder] = (mode, keys)  # atomic: replaces in place
                newly.append(holder)
            else:
                upgrades.append(entry)
                blocked.append((mode, keys))
        waiting = []  # type: List[Tuple[str, Mode, FrozenSet]]
        for waiter in self._waiting:
            holder, mode, keys = waiter
            if self._grantable(None, mode, keys, blocked):
                self._granted[holder] = (mode, keys)
                newly.append(holder)
            else:
                waiting.append(waiter)
                blocked.append((mode, keys))
        self._upgrades = upgrades
        self._waiting = waiting
        return newly

    def _grantable(self, own: Optional[str], mode: Mode, keys: FrozenSet, blocked: List[Tuple[Mode, FrozenSet]]) -> bool:
        """Compatible with every granted holder (except ``own``) and every earlier waiting entry."""
        for other, (granted_mode, granted_keys) in self._granted.items():
            if other != own and not compatible(mode, keys, granted_mode, granted_keys):
                return False
        return all(compatible(mode, keys, m, k) for m, k in blocked)
