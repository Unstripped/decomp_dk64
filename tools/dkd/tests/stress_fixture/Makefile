# Fixture Makefile for the dkd integration tests (the fake root's /dk64/Makefile).
#
#   make [ID=.. SLEEP=..]              default goal: whole-tree build -> dkd must treat it as EXCLUSIVE
#   make build/src/<key>.o [..]        object build -> KEYED on that object
#   make orphan HB=<file>              EXCLUSIVE job leaving a setsid'ed heartbeat writer behind
#
# Recipes only log START/END intervals (fx/ev.py) around a sleep so the tests can check overlap.

ID ?= x
SLEEP ?= 0.1
HB ?= .evlog/hb-default

.DEFAULT_GOAL := all
.PHONY: all orphan FORCE

all:
	@python3 fx/ev.py run exclusive $(ID) $(SLEEP)

orphan:
	@python3 fx/orphan.py $(HB) 120

build/src/%.o: FORCE
	@python3 fx/ev.py run keyed:$* $(ID) $(SLEEP)

FORCE:
