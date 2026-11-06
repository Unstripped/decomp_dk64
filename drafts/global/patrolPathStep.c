// patrolPathStep (src/global/12E800.c): stage 5: full=168 text=171 reloc=0 shape=33; retained exact-count 374/374 insn park (frame 0x38, no saved s/FPRs); tested unchaining idx/dir loads and bitops (regressed to 412 insns, full 201). Traced uopt (-l5/-l6) and ran as1probe scan on records 0-50 (4 single-record mutations improved full 168->167, e.g. delete 38 move $12,$24 from dir & 0x80; confirming allocator ra/dir assignment and early temp allocation drive the diff). Left parked with whole-file fdiff OK. | Prior: patrolPathStep (src/global/12E800.c): Matcher7 revisit: stage 5 retained, whole-TU full=168 text=171 shape=33, 374/374 instructions, frame 0x38, no saved s/FPRs; fdiff CURRENT (3265). Base 405a7498e5b7a23c3a79d8de873b11f10abaf56c. No exact-count improvement. Caller asm from B7490/C2A90 supplies only a0/a1 (including immediately after actorMoveWithinZone); unused third/fourth formals add unwanted parameter-home stores. Reusing incoming arg0/arg1 for key/type/idx/dir/moved did not improve. register qualifiers, named object/global-address pointers, float coordinate/delta temporaries, named radius, byte-array pair addressing, return widths, split/reused angle/index temps, and corrected mathAngleBetweenPoints2D s32 return prototype did not improve exact-count candidate. s16 idx reaches full146/text142 but 376 instructions (stage3); clean u16 v reaches full163/text162 but 377 instructions (stage3), so neither replaces exact-count park. Two FAKEs still each affect score. Bounded 600s -j2 permuter best2700 only added an actor-pointer dead test; not ported. Main blocker remains a3 exclusion/caller-saved cascade. Final parked fdiff OK and NON_MATCHING compilation succeeds. Draft refreshes obsolete func_8072D08C call to current patrolGetTargetAngle name.
typedef struct MiscBPatrolState {
    /* 0x00 */ u8 pad0[0xA];
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 pad10[0xA];
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 pad21[4];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[6];
    /* 0x2C */ s16 unk2C;
} MiscBPatrolState;

typedef struct MiscBPatrolWaypoint {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u8 pad6;
    /* 0x07 */ u8 r;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 pad9;
} MiscBPatrolWaypoint; // size = 0xA

typedef struct MiscBPatrolPathData {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u8 *unk14;
} MiscBPatrolPathData;

typedef struct MiscBPatrolActorView {
    /* 0x00 */ u8 pad0[0x58];
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x20];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ u8 pad8C[4];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 pad94[0x52];
    /* 0xE6 */ s16 unkE6;
    /* 0xE8 */ u8 padE8[6];
    /* 0xEE */ s16 unkEE;
    /* 0xF0 */ u8 padF0[0x64];
    /* 0x154 */ u8 unk154;
    /* 0x155 */ u8 unk155;
} MiscBPatrolActorView;

#define MISCB_PATROL_STATE ((MiscBPatrolState *)D_807FDC90)
#define MISCB_PATROL_PATH_DATA ((MiscBPatrolPathData *)D_807FDCA0)
#define MISCB_PATROL_ACTOR ((MiscBPatrolActorView *)D_807FBB40)
#define MISCB_PATROL_WAYPOINT(off) ((MiscBPatrolWaypoint *)(MISCB_PATROL_PATH_DATA->unk14 + (off)))

u8 patrolPathStep(u8 arg0, u8 arg1)
{
  u8 q1;
  u8 p2;
  u8 key;
  u8 type;
  s16 x;
  s16 y;
  s16 z;
  u8 moved;
  u8 q2;
  u8 p3;
  u8 new_var;
  u8 p1;
  s32 idx;
  s32 v;
  s32 dir;
  s32 off;
  dir = (idx = ((MiscBPatrolState *) D_807FDC90)->unk25);
  idx = idx & 0x7F;
  dir = dir & 0x80;
  key = ((D1Pair *) ((D1Dc98ViewG *) D_807FDC98)->unk20)[idx].a;
  type = ((D1Pair *) ((D1Dc98ViewG *) D_807FDC98)->unk20)[idx].b;
  off = key * 10;
  x = ((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + off))->x;
  y = ((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + off))->y;
  z = ((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + off))->z;
  moved = (((((MiscBPatrolActorView *) D_807FBB40)->unk7C - x) * (((MiscBPatrolActorView *) D_807FBB40)->unk7C - x)) + ((((MiscBPatrolActorView *) D_807FBB40)->unk84 - z) * (((MiscBPatrolActorView *) D_807FBB40)->unk84 - z))) < ((f32) (((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + off))->r * ((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + off))->r));
  if (((arg1 & 1) && (((MiscBPatrolActorView *) D_807FBB40)->unk88 == ((MiscBPatrolActorView *) D_807FBB40)->unk7C)) && (((MiscBPatrolActorView *) D_807FBB40)->unk90 == ((MiscBPatrolActorView *) D_807FBB40)->unk84))
  {
    ((MiscBPatrolState *) D_807FDC90)->unk20++;
    if ((((MiscBPatrolState *) D_807FDC90)->unk20++) > 0x10)
    {
      moved = 1;
      ((MiscBPatrolState *) D_807FDC90)->unk20 = 0;
    }
  }
  else
  {
    ((MiscBPatrolState *) D_807FDC90)->unk20 = 0;
  }
  switch (arg0)
  {
    case 0x49:
      v = idx + 1;
      key = (v < ((D1Dc9cViewG *) D_807FDC9C)->unk11) ? (v) : (0);
      v = mathAngleBetweenPoints2D(((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + (((D1Pair *) ((D1Dc98ViewG *) D_807FDC98)->unk20)[key].a * 10)))->x, ((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + (((D1Pair *) ((D1Dc98ViewG *) D_807FDC98)->unk20)[key].a * 10)))->z, x, z);
      ((MiscBPatrolActorView *) D_807FBB40)->unkEE = v;
      ((MiscBPatrolActorView *) D_807FBB40)->unkE6 = v;

    case 0x42:

    case 0x5B:
      ((MiscBPatrolState *) D_807FDC90)->unkA = x;
      ((MiscBPatrolState *) D_807FDC90)->unkC = y;
      ((MiscBPatrolState *) D_807FDC90)->unkE = z;
      break;

    case 2:
    case 0x26:
  if (D_807FDC9C && D_807FDC9C) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    case 0x60:
      if (moved)
      {
        if (type == 6)
        {
  if (D_807FDCA0 != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
          ((MiscBPatrolState *) D_807FDC90)->unk25 = ((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + off))->unk8;
        }
        else if ((idx + 1) < ((D1Dc9cViewG *) D_807FDC9C)->unk11)
        {
          ((MiscBPatrolState *) D_807FDC90)->unk25 = idx + 1;
        }
        else
        {
          ((MiscBPatrolState *) D_807FDC90)->unk25 = 0;
        }
      }
      else
      {
        ((MiscBPatrolState *) D_807FDC90)->unkA = x;
        ((MiscBPatrolState *) D_807FDC90)->unkC = y;
        ((MiscBPatrolState *) D_807FDC90)->unkE = z;
      }
      break;

    case 3:
      if (moved)
    {
      if (dir != 0)
      {
        if (idx > 0)
        {
          idx = (u8) (idx - 1);
        }
        else
        {
          idx = (u8) (idx + 1);
          dir = 0;
        }
      }
      else
        if (idx < (((D1Dc9cViewG *) D_807FDC9C)->unk11 - 1))
      {
        idx = (u8) (idx + 1);
      }
      else
      {
        idx = (u8) (idx - 1);
        dir = 0x80;
      }
      ((MiscBPatrolState *) D_807FDC90)->unk25 = dir | (idx & 0xFFFFFFFFFFFFFFFF);
    }
    else
    {
      ((MiscBPatrolState *) D_807FDC90)->unkA = x;
      ((MiscBPatrolState *) D_807FDC90)->unkC = y;
      ((MiscBPatrolState *) D_807FDC90)->unkE = z;
    }
      break;

  }

  idx = ((MiscBPatrolState *) D_807FDC90)->unk25 & 0x7F;
  if (moved)
  {
    ((MiscBPatrolState *) D_807FDC90)->unk1A |= 4;
    switch (type)
    {
      case 1:
        new_var = ((D1Pair *) ((D1Dc98ViewG *) D_807FDC98)->unk20)[idx].a;
        key = new_var;
        v = patrolGetTargetAngle();
        ((MiscBPatrolActorView *) D_807FBB40)->unkEE = v;
        ((MiscBPatrolActorView *) D_807FBB40)->unkE6 = v;
        ((MiscBPatrolActorView *) D_807FBB40)->unk7C = ((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + (key * 10)))->x;
        ((MiscBPatrolActorView *) D_807FBB40)->unk80 = ((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + (key * 10)))->y;
        ((MiscBPatrolActorView *) D_807FBB40)->unk84 = ((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + (key * 10)))->z;
        break;

      case 2:
        ((MiscBPatrolActorView *) D_807FBB40)->unk154 = 0x26;
        ((MiscBPatrolActorView *) D_807FBB40)->unk155 = 0;
        break;

      case 4:
        ((MiscBPatrolActorView *) D_807FBB40)->unk154 = 0x19;
        ((MiscBPatrolActorView *) D_807FBB40)->unk155 = 0;
        ((MiscBPatrolState *) D_807FDC90)->unk2C = ((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + off))->unk8;
        break;

      case 5:
        actorSetTargetSpeed(D_807FBB40, ((MiscBPatrolWaypoint *) (((MiscBPatrolPathData *) D_807FDCA0)->unk14 + off))->unk8);
        return moved;

      case 7:
        ((MiscBPatrolActorView *) D_807FBB40)->unk154 = 0x3B;
        moved = 0;
        break;

      case 8:
        ((MiscBPatrolActorView *) D_807FBB40)->unk154 = 0x13;
        ((MiscBPatrolActorView *) D_807FBB40)->unk155 = 0;
        break;

      case 3:
        if (((MiscBPatrolActorView *) D_807FBB40)->unk58 == 0xAF)
      {
        ((MiscBPatrolActorView *) D_807FBB40)->unk154 = 0x37;
        ((MiscBPatrolActorView *) D_807FBB40)->unk155 = 0;
      }
        D_80744508++;
        ((MiscBPatrolActorView *) D_807FBB40)->unk154 = 0x40;
        break;

    }

  }
  else
  {
    ((MiscBPatrolState *) D_807FDC90)->unk1A &= 0xFFFB;
  }
  return moved;
}
