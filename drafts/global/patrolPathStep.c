// patrolPathStep (src/global/12E800.c): MiscB 2026-11-03: stage 5, COUNT-EXACT 374 insns (413 lines), frame ok, deadsweep full 117 (was 150, count 375), shape ~46. New: 'dir = (idx = unk25)' (idx takes the lbu destination; dir the copy) is what makes the count exact (was 'idx = (dir = ..)' = +1 insn); anneal over dead tests + no-code defs (v = v ^ 0, v * 1, v + (v * 0)) from that base: 10 FAKEs. Remaining: dir not in ra (target: dir=ra copy of t3, idx=t3 direct, off spilled sw t9,24(sp)); ring phase: D_807FDC98 lui/lw lands before sw ra in ours (target after lbu t3) and every later t-reg is rotated; case-2 beqz delay slot (target: lbu type; ours: lh x) -> extra nop.
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
  dir = dir & 0x80;
  idx = idx & 0x7F;
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
        if (D_807FDC90) {}  // FAKE: dead/no-code statement steering uopt colouring and the ring (annealed)
      moved = 1;
      ((MiscBPatrolState *) D_807FDC90)->unk20 = 0;
    }
  }
  else
  {
    off = off ^ 0; // FAKE: dead/no-code statement steering uopt colouring and the ring (annealed)
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
        if (D_807FDC90 == 0) {}  // FAKE: dead/no-code statement steering uopt colouring and the ring (annealed)
      ((MiscBPatrolState *) D_807FDC90)->unkA = x;
      ((MiscBPatrolState *) D_807FDC90)->unkC = y;
      if (D_807FDC90) {}  // FAKE: dead/no-code statement steering uopt colouring and the ring (annealed)
      ((MiscBPatrolState *) D_807FDC90)->unkE = z;
      break;

    case 2:
    moved = moved * 1; // FAKE: dead/no-code statement steering uopt colouring and the ring (annealed)
    case 0x26:
    case 0x60:
    type = type ^ 0; // FAKE: dead/no-code statement steering uopt colouring and the ring (annealed)
      if (moved)
      {
        if (type == 6)
        {
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
    key = key ^ 0; // FAKE: dead/no-code statement steering uopt colouring and the ring (annealed)
        idx = (u8) (idx + 1);
      }
    if (dir) {} // FAKE: dead/no-code statement steering uopt colouring and the ring (annealed)
      else
    if (D_807FDCA0 && D_807FDCA0) {} // FAKE: dead/no-code statement steering uopt colouring and the ring (annealed)
      {
        idx = (u8) (idx - 1);
        dir = 0x80;
      }
      ((MiscBPatrolState *) D_807FDC90)->unk25 = dir | (idx & 0xFFFFFFFFFFFFFFFF);
    }
    else
    if (dir && dir) {} // FAKE: dead/no-code statement steering uopt colouring and the ring (annealed)
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
        v = func_8072D08C();
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
