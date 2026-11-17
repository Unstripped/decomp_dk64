# raceUpdateRacerMotion (race, src/race/6650.c)
## Sites
race:8002A7F8:other:bbe4db (other, REMOVED 2026-11-17): `factor` reused for brake drag (onGround branch), |steer| (brake > 0 block) and speed gain (yaw step); all three roles live only in $f0, never homed.
## Attempts
2026-11-14 RereviewRaceSeg claude-opus-5-5: three separate locals -> full=39 (frame grows); diagnose nohit (Q0331).
2026-11-17 HackraceUpdateRacerMotion claude-opus-5-5: variants.py try:
- V5 three locals + steerSign + tiltScale kept: full=39
- V1 steerSign inlined as ternary, tiltScale dropped, brakeDrag/absSteer/speedGain (all 6 orders): full=51
- V3 |steer| + steerSign inlined, tiltScale kept: full=51; V4 (extra word): full=51
- V6 factor kept, only tiltScale dropped: full=4; only steerSign inlined: full=8
- V2 |steer| inlined as ternary in the `> 0.1f` test, tiltScale dropped, brakeDrag in factor slot, speedGain last (either order): full=0 -> applied
- review: brake clamp as ternary max full=0 (applied); `if (brakeDrag <= 1.0f)` full=2; dropped (f32)steerSign full=0 (applied); both onGround tests bare full=0 (applied), both `!= 0` full=82.
Final: whole-file fdiff OK, clint uninit exit 0, cwarn total 0, sweep: no sites.
## Untried ideas
none open (function has no hack sites).
## Evidence
Frame 96: s0 24, ra 28, CSE spill 32(sp) = lowest home 44 - 12 (Q0331). Homes: velX 92, velZ 88, forwardAccel 84, onGround 83 (sb), thrustYaw 80, targetRoll 78, targetPitch 76, friction 68, steerAmount 64 (swc1 at 0x644), signedDist 54, pitchAngle 52, yawDelta 50, airPitch 48. Unhomed: brake ($f2), roles of old factor ($f0: 0x304-0x318, 0x5dc/0x5e4, 0x710/0x724), (f32)pitchAngle/airPitch spilled in CSE slot 32 (0x494/0x560). Word count of named locals must stay at the base count.
