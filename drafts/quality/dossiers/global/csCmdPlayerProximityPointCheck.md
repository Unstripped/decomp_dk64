# csCmdPlayerProximityPointCheck (global, src/global/478F0.c)
## Sites
global:80646770:other:81ca70 other: `v = *p + gMinecartTrackPoints[0];` (index-first pointer sum, first in the loop head) kept the track base in t1/t2 and the *p * 12 mflo in t3 (0x3c54-0x3c70); base-first or `&gMinecartTrackPoints[0][*p]` gave mflo t1, base t2/t3. FIXED 2026-11-17 (element reads, no v).
global:80646770:other:81ca70#2 other: the second `v = *p + gMinecartTrackPoints[0];` (hit arm, before effectCreateAtPosition) kept *p in t6, the base in t4/t5 and mflo t7 (0x3ce8-0x3d00); base-first or `&[0][*p]` gave *p t4, base t6/t7, mflo t5. FIXED 2026-11-17 (element reads, no v).
## Attempts
2026-11-09..11-14 rounds (Clean478F0, OwnerMinecartTrackPoints; opus-5-5 low/high): untagged do{}while(0), copy temp, re-read removed; CsState *cs with cs->data; file-local CsPoint3f retired for TargetVec3f / gMinecartTrackPoints from common.h. The index-first sums stayed untagged.
2026-11-17 cleanup CleancsCmdHubWorldItemsAdjust (opus-5-5 xhigh): diagnose nohit on both sites, tagged FAKE (pre-existing): every typed spelling of the v pointer (base-first sum, `&gMinecartTrackPoints[0][*p]`) swapped the base/product registers.
2026-11-17 cleanup CleancsCmdPlayerProximityPointCheck (opus-5-5): the element-read lever. Dropped the v local; dz/dx/dy read `gMinecartTrackPoints[0][*p].z/.x/.y` and the effectCreateAtPosition arguments `gMinecartTrackPoints[0][*p].x/.y/.z` -> fdiff 0 (whole object), both FAKE tags removed. Measured spellings (fdiff on the function):
- element reads in both blocks: OK; `(*gMinecartTrackPoints)[*p]` in both blocks: OK (same tree).
- element reads in the distance block, index-first v in the effect block: 0x3d04 addu v0,t5,t7 (target v1), 0x3d08-0x3d10 off v0.
- index-first v in the distance block, element reads in the effect block: same v0 difference at 0x3d04.
- element reads in the distance block, `v = &gMinecartTrackPoints[0][*p]` in the effect block: same v0 difference at 0x3d04.
- `v = &gMinecartTrackPoints[0][*p]` in the distance block, element reads in the effect block: mflo t1 / base t2,t3 at 0x3c54-0x3c70 (uadd tree, product first) plus the 0x3d04 v0 difference.
- element reads with the distance block in x/y/z statement order instead of z/x/y: camX/camY/camZ and point loads reorder (0x3c64-0x3c98 r/i rows).
## Untried ideas
none open (function has no hack site).
## Evidence
- 0x3c54-0x3c70: lw t1,0(s4) (gMinecartTrackPoints), lw t2,0(t1) ([0]), mflo t3 (*p * 12), addu v1,t2,t3: base numbered first = the element-read uixa{base}{umpy} tree (Q0781; extends the 2026-11-17f element-read lever: 36880 0685a368, 70FD0 53766941/cce4c004, 10D2D0 0eed63ec, E4090 d77f03ef).
- 0x3ce8-0x3d04: lw t6,0(s0) (*p), lw t4,0(s4), lw t5,0(t4), multu t6,s2, mflo t7, addu v1,t5,t7; reads 0/4/8(v1) into a2/a3/$f18 (stack arg at 16(sp)).
- The two sites are coupled through the 0x3d04 address register: it is v1 only when both blocks use the same spelling (one v local for both, or element reads in both); any mixed pair puts it in v0.
- `cnt = gMinecartTrackPoints[1] - gMinecartTrackPoints[0]` (0x3bec-0x3c10, subu/div by 12) kept as is.
