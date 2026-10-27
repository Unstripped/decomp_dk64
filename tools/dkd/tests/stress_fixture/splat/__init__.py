"""Fake `splat` package: shadows the real one via cwd so `python3 -m splat ...` is observable.

dkd classifies `python3 -m splat ...` as an EXCLUSIVE request by argv alone, which gives the
integration tests a directly-classified exclusive job that needs no make shim.
"""
