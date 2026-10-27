"""Property and unit tests for ``locks.LockManager`` (grant policy and atomic upgrades).

The centrepiece is a hypothesis ``RuleBasedStateMachine`` that drives a
``LockManager`` with random request/release/cancel/upgrade/cancel_upgrade
sequences next to an independent reference model.

Reference policy (model).  The queue is: pending upgrade entries first (an
ATOMIC entry, whose holder keeps its current grant, is always first; VICTIM
entries, whose holder holds nothing, follow in insertion order), then ordinary
waiters in request order.  Scanning in order, an entry is granted iff its
target is compatible with every granted holder other than the entry's own
holder AND with every earlier entry still waiting.  Granting an atomic entry
replaces the holder's grant with the target.  ``upgrade`` of a covered target
is a no-op ``(True, [])``; otherwise the holder gets an ATOMIC entry when no
atomic entry exists, or releases its grant and becomes a VICTIM entry.

After every step the machine checks:

  (a) safety          granted holders are pairwise compatible; an atomic
                      upgrader never loses (or changes) its grant while it waits;
  (b) model parity    granted dict, ordinary waiters, pending upgrades (and
                      their order) equal the model;
  (c) return values   request/release/cancel/cancel_upgrade/upgrade results equal
                      the model's, including holders whose upgrade completed, in
                      grant order; covered upgrades are no-ops returning (True, []);
  (d) no starvation   nothing that requested after a waiting EXCLUSIVE is ever
                      granted; ordinary grants never overtake an incompatible
                      earlier ordinary waiter or any pending upgrade; an upgrade
                      grant never overtakes an incompatible earlier upgrade; only
                      pending upgrades may pass ordinary waiters;
  (e) liveness        granted empty implies no waiting holders and no pending
                      upgrades; the state is stable (no entry is grantable
                      without a release);
  (f) structure       at most one ATOMIC entry, always first; victims in
                      insertion order; atomic holders are granted, victims are
                      not; ordinary waiters in request order;
  (g) deadlock-free   from every reachable state, repeatedly releasing granted
                      holders that have no pending upgrade drains the manager
                      completely, within one step per live holder;
  plus: rejected calls leave state untouched.
"""

import copy
from typing import Dict, FrozenSet, List, Optional, Tuple

import pytest
from hypothesis import given, settings
from hypothesis import strategies as st
from hypothesis.stateful import (
    RuleBasedStateMachine,
    invariant,
    precondition,
    rule,
)

import locks
from locks import LockManager, Mode

KEY_UNIVERSE = ["a", "b", "c", "d"]
HOLDERS = ["h%d" % i for i in range(8)]

Spec = Tuple[Mode, FrozenSet[str]]
Entry = Tuple[str, Mode, FrozenSet[str], bool]  # (holder, target mode, keys, atomic)


def compatible(x: Spec, y: Spec) -> bool:
    """Independent statement of the compatibility matrix from the contract."""
    (mx, kx), (my, ky) = x, y
    if mx is Mode.EXCLUSIVE or my is Mode.EXCLUSIVE:
        return False
    if mx is Mode.KEYED and my is Mode.KEYED:
        return not (kx & ky)
    return True


def combined(cur: Spec, mode: Mode, keys: FrozenSet[str]) -> Spec:
    """Upgrade target: EXCLUSIVE if either is; SHARED+SHARED = SHARED; else KEYED with union of keys."""
    cm, ck = cur
    if cm is Mode.EXCLUSIVE or mode is Mode.EXCLUSIVE:
        return (Mode.EXCLUSIVE, frozenset())
    if cm is Mode.SHARED and mode is Mode.SHARED:
        return (Mode.SHARED, frozenset())
    return (Mode.KEYED, ck | keys)


def covers(cur: Spec, mode: Mode, keys: FrozenSet[str]) -> bool:
    """True iff the current grant already covers the requested one (upgrade is a no-op)."""
    cm, ck = cur
    if cm is Mode.EXCLUSIVE:
        return True
    if cm is Mode.KEYED:
        return mode is Mode.SHARED or (mode is Mode.KEYED and keys <= ck)
    return mode is Mode.SHARED


class Model:
    """Reference implementation of the FIFO + upgrade grant policy."""

    def __init__(self) -> None:
        self.granted: Dict[str, Spec] = {}
        self.upgrades: List[Entry] = []
        self.waiting: List[Tuple[str, Mode, FrozenSet[str]]] = []
        self.last_noop = False

    def has_pending(self, holder: str) -> bool:
        return any(u[0] == holder for u in self.upgrades)

    def atomic_pending(self) -> bool:
        return any(u[3] for u in self.upgrades)

    def live(self) -> List[str]:
        victims = [u[0] for u in self.upgrades if u[0] not in self.granted]
        return list(self.granted) + victims + [w[0] for w in self.waiting]

    def _scan(self) -> List[str]:
        newly: List[str] = []
        still: List[Spec] = []  # targets of earlier entries that are still waiting
        left: List[Entry] = []
        for holder, mode, keys, atomic in self.upgrades:
            spec = (mode, keys)
            others = [g for h, g in self.granted.items() if h != holder]
            if all(compatible(spec, g) for g in others) and all(compatible(spec, s) for s in still):
                self.granted[holder] = spec
                newly.append(holder)
            else:
                left.append((holder, mode, keys, atomic))
                still.append(spec)
        self.upgrades = left
        rest: List[Tuple[str, Mode, FrozenSet[str]]] = []
        for holder, mode, keys in self.waiting:
            spec = (mode, keys)
            if all(compatible(spec, g) for g in self.granted.values()) and all(
                compatible(spec, s) for s in still
            ):
                self.granted[holder] = spec
                newly.append(holder)
            else:
                rest.append((holder, mode, keys))
                still.append(spec)
        self.waiting = rest
        return newly

    def request(self, holder: str, mode: Mode, keys: FrozenSet[str]) -> List[str]:
        self.waiting.append((holder, mode, keys))
        return self._scan()

    def _drop_entries(self, holder: str) -> None:
        self.upgrades = [u for u in self.upgrades if u[0] != holder]

    def release(self, holder: str) -> List[str]:
        del self.granted[holder]
        self._drop_entries(holder)
        return self._scan()

    def cancel(self, holder: str) -> List[str]:
        if holder in self.granted:
            del self.granted[holder]
        else:
            self.waiting = [w for w in self.waiting if w[0] != holder]
        self._drop_entries(holder)
        return self._scan()

    def cancel_upgrade(self, holder: str) -> List[str]:
        self._drop_entries(holder)
        return self._scan()

    def upgrade(self, holder: str, mode: Mode, keys: FrozenSet[str]) -> Tuple[bool, List[str]]:
        cur = self.granted[holder]
        self.last_noop = covers(cur, mode, keys)
        if self.last_noop:
            return (True, [])
        tmode, tkeys = combined(cur, mode, keys)
        if self.atomic_pending():  # victim: give up the grant, queue behind existing upgrades
            del self.granted[holder]
            self.upgrades.append((holder, tmode, tkeys, False))
        else:  # atomic: keep the grant, go to the very front
            self.upgrades.insert(0, (holder, tmode, tkeys, True))
        newly = self._scan()
        return (holder in newly, [n for n in newly if n != holder])


def norm_granted(lm: LockManager) -> Dict[str, Spec]:
    return {h: (m, frozenset(k)) for h, (m, k) in lm.granted().items()}


def norm_waiting(lm: LockManager) -> List[Tuple[str, Mode, FrozenSet[str]]]:
    return [(h, m, frozenset(k)) for h, m, k in lm.waiting()]


def norm_pending(lm: LockManager) -> List[Entry]:
    return [(h, m, frozenset(k), bool(a)) for h, m, k, a in lm.pending_upgrades()]


def snapshot(lm: LockManager):
    return norm_granted(lm), norm_waiting(lm), norm_pending(lm)


def live_of(lm: LockManager) -> List[str]:
    pending_victims = [h for h, _, _, a in lm.pending_upgrades() if not a]
    return sorted(lm.granted()) + pending_victims + [w[0] for w in lm.waiting()]


def runners_of(lm: LockManager) -> List[str]:
    """Granted holders that are not waiting for an upgrade ("running")."""
    pending = {h for h, _, _, _ in lm.pending_upgrades()}
    return sorted(h for h in lm.granted() if h not in pending)


def assert_drains_by_releasing_runners(lm: LockManager) -> None:
    """Deadlock freedom: releasing only running holders (repeatedly) drains everything."""
    live = len(live_of(lm))
    steps = 0
    while lm.granted():
        runners = runners_of(lm)
        assert runners, ("deadlock: granted holders all wait for upgrades", snapshot(lm))
        lm.release(runners[0])
        steps += 1
        assert steps <= live
        if not lm.granted():
            assert not lm.waiting() and not lm.pending_upgrades()
    assert lm.waiting() == [] and lm.pending_upgrades() == []


SPECS = st.one_of(
    st.just((Mode.SHARED, frozenset())),
    st.just((Mode.EXCLUSIVE, frozenset())),
    st.tuples(
        st.just(Mode.KEYED),
        st.frozensets(st.sampled_from(KEY_UNIVERSE), min_size=1, max_size=4),
    ),
)


class LockMachine(RuleBasedStateMachine):
    def __init__(self) -> None:
        super().__init__()
        self.lm = LockManager()
        self.model = Model()
        self.seq: Dict[str, int] = {}  # request order of every live holder
        self.useq: Dict[str, int] = {}  # order in which holders got their latest upgrade entry
        self.spec: Dict[str, Spec] = {}  # the spec each holder originally requested
        self.upgraded = set()  # holders whose grant was ever changed by an upgrade
        self.counter = 0

    # ---- helpers ---------------------------------------------------------

    def _pre(self) -> dict:
        return {
            "granted": norm_granted(self.lm),
            "order": [h for h, _, _, _ in self.lm.pending_upgrades()],
            "atomic": {h for h, _, _, a in self.lm.pending_upgrades() if a},
        }

    def _after(self, newly: List[str], pre: dict, removed=(), fresh: Optional[str] = None) -> None:
        """(a)/(d) event checks after an operation that newly granted `newly`."""
        granted = norm_granted(self.lm)
        pending = {h: (m, k) for h, m, k, _ in norm_pending(self.lm)}
        waiting = [(h, (m, k)) for h, m, k in norm_waiting(self.lm)]
        upgrade_entries = set(pre["order"]) | ({fresh} if fresh else set())
        for g in newly:
            if g in upgrade_entries:
                # an upgrade grant may pass ordinary waiters, but not an incompatible EARLIER upgrade
                if g in pre["order"]:
                    for earlier in pre["order"][: pre["order"].index(g)]:
                        if earlier in pending:
                            assert compatible(granted[g], pending[earlier]), (g, "overtook upgrade", earlier)
            else:
                gspec = self.spec[g]
                for h, s in waiting:
                    if self.seq[h] < self.seq[g]:
                        assert compatible(gspec, s), (g, "overtook incompatible earlier waiter", h)
                for h, s in pending.items():
                    assert compatible(gspec, s), (g, "overtook incompatible pending upgrade", h)
        # an atomic upgrader keeps its grant while it waits, and loses it only via release/cancel
        for h in pre["atomic"]:
            if h not in removed:
                assert h in granted, (h, "atomic upgrader lost its grant")
        for h, _, _, atomic in norm_pending(self.lm):
            if atomic:
                assert h in granted and granted[h] == pre["granted"][h], (h, "atomic grant changed while waiting")

    # ---- rules -----------------------------------------------------------

    @rule(holder=st.sampled_from(HOLDERS), spec=SPECS)
    def request(self, holder, spec):
        mode, keys = spec
        if holder in self.model.live():
            before = snapshot(self.lm)
            with pytest.raises(ValueError):
                self.lm.request(holder, mode, keys)
            assert snapshot(self.lm) == before  # rejected call has no effect
            return
        pre = self._pre()
        self.counter += 1
        self.seq[holder] = self.counter
        self.spec[holder] = spec
        self.upgraded.discard(holder)
        expected = self.model.request(holder, mode, keys)
        result = self.lm.request(holder, mode, keys)
        assert result is (holder in expected)  # bool: granted immediately
        assert expected in ([], [holder])  # a tail append can only grant itself
        self._after(expected, pre)

    @precondition(lambda self: self.model.granted)
    @rule(data=st.data())
    def release(self, data):
        holder = data.draw(st.sampled_from(sorted(self.model.granted)))
        pre = self._pre()
        expected = self.model.release(holder)
        assert self.lm.release(holder) == expected
        self._after(expected, pre, removed=(holder,))

    @precondition(lambda self: self.model.live())
    @rule(data=st.data())
    def cancel(self, data):
        holder = data.draw(st.sampled_from(sorted(self.model.live())))
        pre = self._pre()
        expected = self.model.cancel(holder)
        assert self.lm.cancel(holder) == expected
        self._after(expected, pre, removed=(holder,))

    @precondition(lambda self: any(not self.model.has_pending(h) for h in self.model.granted))
    @rule(data=st.data(), spec=SPECS)
    def upgrade(self, data, spec):
        mode, keys = spec
        holder = data.draw(st.sampled_from(sorted(h for h in self.model.granted if not self.model.has_pending(h))))
        pre = self._pre()
        before = snapshot(self.lm)
        self.counter += 1
        self.useq[holder] = self.counter
        expected = self.model.upgrade(holder, mode, keys)
        result = self.lm.upgrade(holder, mode, keys)
        assert result == expected
        if self.model.last_noop:
            assert result == (True, [])
            assert snapshot(self.lm) == before  # covered upgrades change nothing
            return
        self.upgraded.add(holder)
        newly = ([holder] if expected[0] else []) + expected[1]
        self._after(newly, pre, fresh=holder)

    @precondition(lambda self: self.model.upgrades)
    @rule(data=st.data())
    def cancel_upgrade(self, data):
        holder = data.draw(st.sampled_from([u[0] for u in self.model.upgrades]))
        pre = self._pre()
        was_atomic = holder in pre["atomic"]
        before_grant = norm_granted(self.lm).get(holder)
        expected = self.model.cancel_upgrade(holder)
        assert self.lm.cancel_upgrade(holder) == expected
        if was_atomic:  # atomic upgrader keeps its current grant
            assert norm_granted(self.lm)[holder] == before_grant
        else:  # victim: the id is forgotten
            assert holder not in live_of(self.lm)
        self._after(expected, pre)

    @rule(holder=st.sampled_from(HOLDERS))
    def bad_release_cancel_and_cancel_upgrade(self, holder):
        """release needs a granted holder, cancel a live one, cancel_upgrade a pending upgrade."""
        before = snapshot(self.lm)
        if holder not in self.model.granted:
            with pytest.raises(KeyError):
                self.lm.release(holder)
        if holder not in self.model.live():
            with pytest.raises(KeyError):
                self.lm.cancel(holder)
        if not self.model.has_pending(holder):
            with pytest.raises(KeyError):
                self.lm.cancel_upgrade(holder)
        assert snapshot(self.lm) == before

    @rule(holder=st.sampled_from(HOLDERS), spec=SPECS)
    def bad_upgrade(self, holder, spec):
        """upgrade: KeyError unless granted; ValueError if an upgrade is already pending."""
        before = snapshot(self.lm)
        if holder not in self.model.granted:
            with pytest.raises(KeyError):
                self.lm.upgrade(holder, *spec)
        elif self.model.has_pending(holder):
            with pytest.raises(ValueError):
                self.lm.upgrade(holder, *spec)
        assert snapshot(self.lm) == before

    @rule(holder=st.sampled_from(HOLDERS), keys=st.frozensets(st.sampled_from(KEY_UNIVERSE), max_size=3))
    def bad_arguments(self, holder, keys):
        """Invalid mode/keys combinations are rejected without side effects."""
        before = snapshot(self.lm)
        with pytest.raises(ValueError):
            self.lm.request(holder, Mode.KEYED, frozenset())
        with pytest.raises(ValueError):
            self.lm.request(holder, Mode.SHARED, frozenset(["a"]) | keys)
        with pytest.raises(ValueError):
            self.lm.request(holder, Mode.EXCLUSIVE, frozenset(["a"]) | keys)
        free = [h for h in self.model.granted if not self.model.has_pending(h)]
        if free:
            target = sorted(free)[0]
            with pytest.raises(ValueError):
                self.lm.upgrade(target, Mode.KEYED, frozenset())
            with pytest.raises(ValueError):
                self.lm.upgrade(target, Mode.SHARED, frozenset(["a"]) | keys)
            with pytest.raises(ValueError):
                self.lm.upgrade(target, Mode.EXCLUSIVE, frozenset(["a"]) | keys)
        assert snapshot(self.lm) == before

    # ---- invariants ------------------------------------------------------

    @invariant()
    def safety(self):
        granted = list(norm_granted(self.lm).values())
        for i, x in enumerate(granted):
            for y in granted[i + 1 :]:
                assert compatible(x, y)

    @invariant()
    def matches_model(self):
        assert norm_granted(self.lm) == self.model.granted
        assert norm_waiting(self.lm) == self.model.waiting
        assert norm_pending(self.lm) == self.model.upgrades

    @invariant()
    def queue_is_in_request_order(self):
        seqs = [self.seq[h] for h, _, _ in self.lm.waiting()]
        assert seqs == sorted(seqs)

    @invariant()
    def no_starvation(self):
        granted = norm_granted(self.lm)
        for holder, mode, _ in norm_waiting(self.lm):
            if mode is Mode.EXCLUSIVE:  # nothing requested after a waiting EXCLUSIVE may hold a grant
                for granted_holder in granted:
                    assert self.seq[granted_holder] < self.seq[holder]
        for holder, mode, keys in norm_waiting(self.lm):
            for granted_holder, gspec in granted.items():
                # holders whose grant was changed by an upgrade may legitimately have passed waiters
                if self.seq[granted_holder] > self.seq[holder] and granted_holder not in self.upgraded:
                    assert compatible(gspec, (mode, keys))

    @invariant()
    def liveness_and_stability(self):
        if not self.lm.granted():
            assert not self.lm.waiting() and not self.lm.pending_upgrades()
        assert copy.deepcopy(self.model)._scan() == []  # nothing grantable without a release

    @invariant()
    def upgrade_queue_structure(self):
        pending = norm_pending(self.lm)
        granted = self.lm.granted()
        atomics = [i for i, e in enumerate(pending) if e[3]]
        assert len(atomics) <= 1  # at most one pending ATOMIC upgrade
        assert atomics in ([], [0])  # ... and it is always first
        victims = [e[0] for e in pending if not e[3]]
        assert [self.useq[h] for h in victims] == sorted(self.useq[h] for h in victims)
        for holder, _, _, atomic in pending:
            assert (holder in granted) == atomic
        assert not {h for h, _, _, _ in pending} & {w[0] for w in self.lm.waiting()}

    @invariant()
    def deadlock_free(self):
        assert_drains_by_releasing_runners(copy.deepcopy(self.lm))


TestLockMachine = LockMachine.TestCase
TestLockMachine.settings = settings(max_examples=300, stateful_step_count=60, deadline=None)


# ---- termination / drain properties -------------------------------------------------

OPS = st.lists(
    st.one_of(
        st.tuples(st.just("req"), SPECS),
        st.tuples(st.just("rel"), st.integers(min_value=0)),
        st.tuples(st.just("can"), st.integers(min_value=0)),
        st.tuples(st.just("upg"), st.tuples(st.integers(min_value=0), SPECS)),
        st.tuples(st.just("cu"), st.integers(min_value=0)),
    ),
    max_size=40,
)


def play(ops) -> LockManager:
    lm = LockManager()
    n = 0
    for kind, arg in ops:
        if kind == "req":
            lm.request("p%d" % n, arg[0], arg[1])
            n += 1
        elif kind == "rel":
            granted = sorted(lm.granted())
            if granted:
                lm.release(granted[arg % len(granted)])
        elif kind == "can":
            live = live_of(lm)
            if live:
                lm.cancel(live[arg % len(live)])
        elif kind == "upg":
            idx, spec = arg
            runners = runners_of(lm)
            if runners:
                lm.upgrade(runners[idx % len(runners)], spec[0], spec[1])
        else:
            pending = [h for h, _, _, _ in lm.pending_upgrades()]
            if pending:
                lm.cancel_upgrade(pending[arg % len(pending)])
    return lm


@settings(max_examples=300, deadline=None)
@given(OPS)
def test_releasing_running_holders_drains_queue(ops):
    """Releasing only holders that are not waiting for an upgrade empties the manager (no deadlock)."""
    assert_drains_by_releasing_runners(play(ops))


@settings(max_examples=300, deadline=None)
@given(OPS)
def test_releasing_any_granted_holder_drains_queue(ops):
    """Releasing any granted holder (upgraders included) empties the manager in <= #live steps."""
    lm = play(ops)
    live = len(live_of(lm))
    steps = 0
    while lm.granted():
        lm.release(sorted(lm.granted())[0])
        steps += 1
        assert steps <= live
        if not lm.granted():
            assert not lm.waiting() and not lm.pending_upgrades()
    assert not lm.waiting() and not lm.pending_upgrades()
    assert lm.granted() == {}


@settings(max_examples=300, deadline=None)
@given(OPS, st.data())
def test_cancelling_arbitrary_holders_drains_queue(ops, data):
    """Cancelling holders (granted, waiting or victim) in any order drains the manager, keeping liveness."""
    lm = play(ops)
    live = live_of(lm)
    while live:
        victim = data.draw(st.sampled_from(live))
        lm.cancel(victim)
        live.remove(victim)
        assert sorted(live_of(lm)) == sorted(live)  # each cancel removes exactly that one holder
        if not lm.granted():
            assert not lm.waiting() and not lm.pending_upgrades()
    assert lm.granted() == {} and lm.waiting() == [] and lm.pending_upgrades() == []


# ---- explicit unit tests ------------------------------------------------------------

S, K, X = Mode.SHARED, Mode.KEYED, Mode.EXCLUSIVE
EMPTY = frozenset()


def test_modes_are_the_pinned_values():
    assert {m.name: m.value for m in Mode} == {
        "SHARED": "shared",
        "KEYED": "keyed",
        "EXCLUSIVE": "exclusive",
    }


def test_duplicate_holder_rejected_granted_and_waiting():
    lm = LockManager()
    assert lm.request("g", Mode.EXCLUSIVE) is True
    assert lm.request("w", Mode.SHARED) is False
    for holder in ("g", "w"):
        with pytest.raises(ValueError):
            lm.request(holder, Mode.SHARED)
    assert list(lm.granted()) == ["g"]
    assert [w[0] for w in lm.waiting()] == ["w"]


def test_holder_id_reusable_after_release_and_cancel():
    lm = LockManager()
    lm.request("x", Mode.EXCLUSIVE)
    lm.release("x")
    assert lm.request("x", Mode.EXCLUSIVE) is True
    lm.cancel("x")
    assert lm.request("x", Mode.SHARED) is True


def test_keyed_requires_nonempty_keys():
    lm = LockManager()
    with pytest.raises(ValueError):
        lm.request("k", Mode.KEYED)
    with pytest.raises(ValueError):
        lm.request("k", Mode.KEYED, frozenset())
    assert lm.granted() == {} and lm.waiting() == []


@pytest.mark.parametrize("mode", [Mode.SHARED, Mode.EXCLUSIVE])
def test_non_keyed_modes_reject_keys(mode):
    lm = LockManager()
    with pytest.raises(ValueError):
        lm.request("s", mode, frozenset({"a"}))
    assert lm.granted() == {} and lm.waiting() == []


def test_release_unknown_holder_is_keyerror():
    with pytest.raises(KeyError):
        LockManager().release("nobody")


def test_release_waiting_holder_is_keyerror_and_leaves_it_queued():
    lm = LockManager()
    lm.request("g", Mode.EXCLUSIVE)
    lm.request("w", Mode.SHARED)
    with pytest.raises(KeyError):
        lm.release("w")
    assert [w[0] for w in lm.waiting()] == ["w"]


def test_cancel_unknown_holder_is_keyerror():
    lm = LockManager()
    with pytest.raises(KeyError):
        lm.cancel("nobody")
    lm.request("a", Mode.SHARED)
    lm.release("a")
    with pytest.raises(KeyError):
        lm.cancel("a")  # already released


def test_double_release_is_keyerror():
    lm = LockManager()
    lm.request("a", Mode.SHARED)
    lm.release("a")
    with pytest.raises(KeyError):
        lm.release("a")


def test_compatibility_matrix():
    ab, bc, c = frozenset("ab"), frozenset("bc"), frozenset("c")

    def second_granted(m1, k1, m2, k2):
        lm = LockManager()
        assert lm.request("one", m1, k1) is True
        return lm.request("two", m2, k2)

    assert second_granted(S, EMPTY, S, EMPTY) is True
    assert second_granted(S, EMPTY, K, ab) is True
    assert second_granted(K, ab, S, EMPTY) is True
    assert second_granted(K, ab, K, c) is True
    assert second_granted(K, ab, K, bc) is False
    assert second_granted(X, EMPTY, S, EMPTY) is False
    assert second_granted(X, EMPTY, K, ab) is False
    assert second_granted(X, EMPTY, X, EMPTY) is False
    assert second_granted(S, EMPTY, X, EMPTY) is False
    assert second_granted(K, ab, X, EMPTY) is False


def test_exclusive_waiter_blocks_later_compatible_requests():
    lm = LockManager()
    assert lm.request("s1", Mode.SHARED) is True
    assert lm.request("x", Mode.EXCLUSIVE) is False
    assert lm.request("s2", Mode.SHARED) is False  # would be compatible with s1, but must not pass x
    assert lm.release("s1") == ["x"]
    assert lm.release("x") == ["s2"]


def test_compatible_later_request_may_overtake_unrelated_waiter():
    lm = LockManager()
    assert lm.request("k1", Mode.KEYED, frozenset({"a"})) is True
    assert lm.request("k2", Mode.KEYED, frozenset({"a"})) is False  # conflicts with k1
    assert lm.request("k3", Mode.KEYED, frozenset({"b"})) is True  # disjoint from k1 and from waiter k2
    assert lm.request("k4", Mode.KEYED, frozenset({"a", "b"})) is False  # conflicts with granted and with k2


def test_later_request_does_not_overtake_conflicting_waiter():
    lm = LockManager()
    lm.request("k1", Mode.KEYED, frozenset({"a"}))
    lm.request("k2", Mode.KEYED, frozenset({"a", "b"}))  # waits on k1
    assert lm.request("k3", Mode.KEYED, frozenset({"b"})) is False  # free of k1 but conflicts with waiter k2
    assert lm.release("k1") == ["k2"]
    assert lm.release("k2") == ["k3"]


def test_release_grants_in_queue_order_as_a_batch():
    lm = LockManager()
    lm.request("x", Mode.EXCLUSIVE)
    lm.request("s1", Mode.SHARED)
    lm.request("k1", Mode.KEYED, frozenset({"a"}))
    lm.request("k2", Mode.KEYED, frozenset({"a"}))
    lm.request("s2", Mode.SHARED)
    assert lm.release("x") == ["s1", "k1", "s2"]  # k2 conflicts with k1 and stays queued
    assert [w[0] for w in lm.waiting()] == ["k2"]


def test_cancelling_waiting_exclusive_unblocks_later_requests():
    lm = LockManager()
    lm.request("s1", Mode.SHARED)
    lm.request("x", Mode.EXCLUSIVE)
    lm.request("s2", Mode.SHARED)
    assert lm.cancel("x") == ["s2"]
    assert sorted(lm.granted()) == ["s1", "s2"]


def test_cancel_granted_acts_like_release():
    lm = LockManager()
    lm.request("x", Mode.EXCLUSIVE)
    lm.request("s", Mode.SHARED)
    assert lm.cancel("x") == ["s"]


def test_granted_and_waiting_report_modes_and_keys():
    lm = LockManager()
    lm.request("k", Mode.KEYED, frozenset({"a", "b"}))
    lm.request("x", Mode.EXCLUSIVE)
    lm.request("s", Mode.SHARED)
    assert lm.granted() == {"k": (Mode.KEYED, frozenset({"a", "b"}))}
    assert lm.waiting() == [
        ("x", Mode.EXCLUSIVE, frozenset()),
        ("s", Mode.SHARED, frozenset()),
    ]


def test_module_exports_contract_api():
    assert locks.LockManager is LockManager and locks.Mode is Mode


# ---- upgrade unit tests -------------------------------------------------------------


def shared_pair(*names):
    lm = LockManager()
    for name in names:
        assert lm.request(name, S) is True
    return lm


def test_upgrade_atomic_keeps_grant_while_waiting():
    lm = shared_pair("x", "y")
    assert lm.upgrade("x", X) == (False, [])
    assert lm.granted() == {"x": (S, EMPTY), "y": (S, EMPTY)}  # x still holds SHARED
    assert lm.pending_upgrades() == [("x", X, EMPTY, True)]
    assert lm.waiting() == []  # waiting() lists ordinary waiters only
    assert lm.release("y") == ["x"]  # completion is reported as a newly granted holder
    assert lm.granted() == {"x": (X, EMPTY)}
    assert lm.pending_upgrades() == []


def test_upgrade_granted_immediately_when_alone():
    lm = shared_pair("x")
    assert lm.upgrade("x", X) == (True, [])
    assert lm.granted() == {"x": (X, EMPTY)}
    assert lm.pending_upgrades() == []


def test_upgrade_victim_when_another_atomic_upgrade_is_pending():
    lm = shared_pair("x", "y", "z")
    assert lm.upgrade("x", X) == (False, [])  # atomic: waits for y and z
    assert lm.upgrade("y", X) == (False, [])  # victim: y gives up its grant
    assert sorted(lm.granted()) == ["x", "z"]
    assert lm.pending_upgrades() == [("x", X, EMPTY, True), ("y", X, EMPTY, False)]
    assert lm.release("z") == ["x"]  # atomic completes first
    assert lm.pending_upgrades() == [("y", X, EMPTY, False)]
    assert lm.release("x") == ["y"]  # then the victim, now holding its target
    assert lm.granted() == {"y": (X, EMPTY)}


def test_victim_release_can_complete_the_atomic_upgrade():
    lm = shared_pair("x", "y")
    assert lm.upgrade("x", X) == (False, [])  # waits only for y
    assert lm.upgrade("y", X) == (False, ["x"])  # y's release lets x's upgrade complete
    assert lm.granted() == {"x": (X, EMPTY)}
    assert lm.pending_upgrades() == [("y", X, EMPTY, False)]
    assert lm.release("x") == ["y"]


def test_victim_target_combines_current_and_requested():
    lm = LockManager()
    lm.request("x", S)
    lm.request("k", K, frozenset({"a"}))
    lm.request("z", S)
    assert lm.upgrade("x", X) == (False, [])  # atomic, waits for k and z
    assert lm.upgrade("k", K, frozenset({"b"})) == (False, [])  # victim, target KEYED{a,b}; x still waits for z
    assert lm.pending_upgrades() == [
        ("x", X, EMPTY, True),
        ("k", K, frozenset({"a", "b"}), False),
    ]
    assert lm.release("z") == ["x"]
    assert lm.release("x") == ["k"]
    assert lm.granted() == {"k": (K, frozenset({"a", "b"}))}


def test_atomic_entry_goes_ahead_of_older_victim_entries():
    """The atomic entry is always first, so it never waits on a victim that waits on its own grant."""
    lm = LockManager()
    lm.request("a", S)
    lm.request("b", S)
    lm.request("c", K, frozenset({"a"}))
    lm.request("j", K, frozenset({"b"}))
    assert lm.upgrade("a", X) == (False, [])  # atomic, blocked by b, c and j
    assert lm.upgrade("b", K, frozenset({"a"})) == (False, [])  # victim, blocked by c
    assert lm.cancel_upgrade("a") == []  # a keeps its SHARED grant; the victim stays queued
    assert lm.pending_upgrades() == [("b", K, frozenset({"a"}), False)]
    assert lm.upgrade("c", K, frozenset({"b"})) == (False, [])  # blocked by j only
    assert lm.pending_upgrades() == [
        ("c", K, frozenset({"a", "b"}), True),  # atomic entry is first ...
        ("b", K, frozenset({"a"}), False),  # ... ahead of the older victim
    ]
    assert_drains_by_releasing_runners(copy.deepcopy(lm))
    assert lm.release("j") == ["c"]
    assert lm.release("c") == ["b"]


def test_atomic_upgrade_is_not_blocked_by_a_victim_that_waits_on_it():
    """Regression for the upgrade deadlock: victim waits for c's grant, c's upgrade must not wait for the victim."""
    lm = LockManager()
    lm.request("a", S)
    lm.request("b", S)
    lm.request("c", K, frozenset({"a"}))
    lm.upgrade("a", X)
    lm.upgrade("b", K, frozenset({"a"}))
    lm.cancel_upgrade("a")
    assert lm.upgrade("c", K, frozenset({"b"})) == (True, [])
    assert_drains_by_releasing_runners(lm)


def test_upgrade_keyed_extends_keys():
    lm = LockManager()
    lm.request("k", K, frozenset({"a"}))
    assert lm.upgrade("k", K, frozenset({"b"})) == (True, [])
    assert lm.granted() == {"k": (K, frozenset({"a", "b"}))}


def test_upgrade_keyed_waits_for_conflicting_holder():
    lm = LockManager()
    lm.request("k", K, frozenset({"a"}))
    lm.request("j", K, frozenset({"b"}))
    assert lm.upgrade("k", K, frozenset({"b"})) == (False, [])
    assert lm.granted()["k"] == (K, frozenset({"a"}))  # still the old grant
    assert lm.request("n", K, frozenset({"a"})) is False  # conflicts with k's grant anyway
    assert lm.release("j") == ["k"]
    assert lm.granted()["k"] == (K, frozenset({"a", "b"}))


def test_upgrade_shared_to_exclusive_waits_for_shared_holders_but_blocks_new_ones():
    lm = shared_pair("s1", "s2")
    assert lm.upgrade("s1", X) == (False, [])
    assert lm.request("s3", S) is False  # pending upgrade is ahead of every ordinary waiter
    assert lm.release("s2") == ["s1"]
    assert lm.granted() == {"s1": (X, EMPTY)}
    assert lm.release("s1") == ["s3"]


def test_upgrade_may_pass_ordinary_waiters():
    lm = shared_pair("s1", "s2")
    assert lm.request("x", X) is False  # ordinary EXCLUSIVE waiter, behind s1 and s2
    assert lm.upgrade("s1", K, frozenset({"a"})) == (True, [])  # passes x: target compatible with s2
    assert lm.granted()["s1"] == (K, frozenset({"a"}))
    assert [w[0] for w in lm.waiting()] == ["x"]


@pytest.mark.parametrize(
    "cur,req",
    [
        ((X, EMPTY), (S, EMPTY)),
        ((X, EMPTY), (K, frozenset({"a"}))),
        ((X, EMPTY), (X, EMPTY)),
        ((K, frozenset({"a", "b"})), (S, EMPTY)),
        ((K, frozenset({"a", "b"})), (K, frozenset({"b"}))),
        ((K, frozenset({"a", "b"})), (K, frozenset({"a", "b"}))),
        ((S, EMPTY), (S, EMPTY)),
    ],
)
def test_covered_upgrade_is_a_noop(cur, req):
    lm = LockManager()
    lm.request("h", cur[0], cur[1])
    lm.request("w", X)  # an ordinary waiter that must stay untouched
    before = snapshot(lm)
    assert lm.upgrade("h", req[0], req[1]) == (True, [])
    assert snapshot(lm) == before
    assert lm.pending_upgrades() == []


def test_upgrade_of_unknown_or_waiting_holder_is_keyerror():
    lm = LockManager()
    with pytest.raises(KeyError):
        lm.upgrade("nobody", X)
    lm.request("g", X)
    lm.request("w", S)
    with pytest.raises(KeyError):
        lm.upgrade("w", X)
    assert [w[0] for w in lm.waiting()] == ["w"]


def test_upgrade_of_victim_holder_is_keyerror():
    lm = shared_pair("x", "y")
    lm.upgrade("x", X)
    lm.upgrade("y", X)  # y is now a victim holding nothing
    with pytest.raises(KeyError):
        lm.upgrade("y", X)


def test_double_upgrade_is_valueerror():
    lm = shared_pair("x", "y")
    assert lm.upgrade("x", X) == (False, [])
    before = snapshot(lm)
    with pytest.raises(ValueError):
        lm.upgrade("x", X)
    with pytest.raises(ValueError):
        lm.upgrade("x", K, frozenset({"a"}))
    assert snapshot(lm) == before


def test_upgrade_argument_validation():
    lm = shared_pair("x", "y")
    with pytest.raises(ValueError):
        lm.upgrade("x", K)
    with pytest.raises(ValueError):
        lm.upgrade("x", S, frozenset({"a"}))
    with pytest.raises(ValueError):
        lm.upgrade("x", X, frozenset({"a"}))
    assert lm.pending_upgrades() == []


def test_release_and_cancel_of_atomic_upgrader_drop_grant_and_entry():
    for op in ("release", "cancel"):
        lm = shared_pair("x", "y")
        lm.request("w", S)  # granted: compatible with shared holders
        lm.upgrade("x", X)
        assert getattr(lm, op)("x") == []
        assert lm.pending_upgrades() == []
        assert sorted(lm.granted()) == ["w", "y"]
        assert lm.request("x", X) is False  # id is reusable


def test_cancel_upgrade_keeps_grant_and_unblocks_waiters():
    lm = shared_pair("x", "y")
    lm.upgrade("x", X)
    assert lm.request("w", S) is False  # blocked behind the pending upgrade
    assert lm.cancel_upgrade("x") == ["w"]
    assert sorted(lm.granted()) == ["w", "x", "y"]
    assert lm.granted()["x"] == (S, EMPTY)
    assert lm.pending_upgrades() == []


def test_cancel_upgrade_without_pending_upgrade_is_keyerror():
    lm = shared_pair("x")
    with pytest.raises(KeyError):
        lm.cancel_upgrade("x")
    with pytest.raises(KeyError):
        lm.cancel_upgrade("nobody")


def test_victim_entry_cancel_and_cancel_upgrade_forget_the_holder():
    for op in ("cancel", "cancel_upgrade"):
        lm = shared_pair("x", "y", "z")
        assert lm.upgrade("x", X) == (False, [])  # atomic, waits for y and z
        assert lm.upgrade("y", X) == (False, [])  # victim; x still waits for z
        with pytest.raises(KeyError):
            lm.release("y")  # a victim holds nothing
        assert getattr(lm, op)("y") == []
        assert lm.pending_upgrades() == [("x", X, EMPTY, True)]
        assert sorted(lm.granted()) == ["x", "z"]
        assert lm.request("y", S) is False  # id reusable (queued behind x's upgrade)
