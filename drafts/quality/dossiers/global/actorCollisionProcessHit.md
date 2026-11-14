# actorCollisionProcessHit (global, src/global/7A510.c)

## Sites
- global:80675810:other:b8c7d3, now d9962d (keymap): the phase is re-read through `interactions` rather than `entry`, from a base-first address `interactions + i*12 + 8`. This keeps the entry induction in $s1 (Q0589). It was spelled as the punned byte `((u8 *)interactions)[i * 12 + 8]`; it is now the typed `(interactions + i)->phase`. The tag is kept.
- global:80675810:other:818f85 (Q0606, kept by Owner7A510FindTableEntry): `entry = &interactions[0] + i` keeps `addu s1,a0,t1` at 0x110.

## Attempts
- 2026-11-12/13 (rounds 29/32, :medium/:low): uopt_trace of hitPhase and entry->phase copies; a permuter best of 115 needs hacks.
- 2026-11-14 :high (interactions an s32, before typing): entry->phase 40, hitPhase 53, indexed 85, no locals 108.
- 2026-11-14 HackactorCollisionProcessHit :high (interactions typed `CollisionInteractionEntry *` by c828f7da):
  - Single-site spellings:
    - interactions[i].phase 85;
    - (interactions + i)->phase **0** (applied, tag kept);
    - (&interactions[0] + i)->phase 0;
    - entry->phase 40;
    - hitPhase 53.
  - Coupled with line 71 respelled (`&interactions[i]` or `interactions + i`):
    - (interactions + i)->phase 1 (the Q0606 addu at 0x110 only);
    - interactions[i].phase 85;
    - entry->phase 40.
  - `variants.py scan` of the interactions[i].phase copy: best 52 (`i` width).

## Untried ideas
- A natural form whose phase address is base-first without spelling `p + i`. In cfe, `p[i]` builds idx*size + base (as in Q0606 at line 71).

## Evidence
- The target re-reads phase with `lbu` from interactions + i*12 + 8 after the targetActor store; entry is held in $s1.
