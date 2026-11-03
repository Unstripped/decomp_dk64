// patrolPathStep (src/global/12E800.c): UNPARKED 2026-11-02 count-inexact; leftovers revisit 6 (Patrol): stage 5, deadsweep full 165 (was 180/168 park), 375 insns vs target 374 (was 376): case 2/0x26/0x60 rewritten as if (moved) {type==6 ... else-if idx+1 ...} else {x,y,z stores} (drops 1 nop+store-order diff: shape 30 / full 215 w/o FAKEs; 3 FAKEs hill-climb -> 165). Remaining extra insn: as1 fills beqz moved delay slot with the else-arm 'lh x,50(sp)' instead of fall-through 'lbu type,52(sp)', so bne type,6 gets lui+nop. Regalloc: dir t3 vs ra (dir must colour last; target idx t3 key t2 a3 unused, cand18 uixa t0 not a3), end epilogue lw ra/lbu v0 order follows dir=ra. Tried: 18 prologue spellings of idx/dir (P1 idx=(dir=U) best), decl perms of idx/v/dir/off + types, split v/idx locals (v2/idx2), .a local in case 0x49, line-join grid (1-2 joins), 3 hill-climbs ~100k compiles with count penalty, deadsweep sweep (155 but 419 insns)
typedef struct PatrolState {
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
} PatrolState;

typedef struct PatrolWaypoint {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u8 pad6;
    /* 0x07 */ u8 r;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 pad9;
} PatrolWaypoint; // size = 0xA

typedef struct PatrolPathData {
    /* 0x00 */ u8 pad0[0x14];
    /* 0x14 */ u8 *unk14;
} PatrolPathData;

typedef struct PatrolActorView {
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
} PatrolActorView;

#define PATROL_STATE ((PatrolState *)D_807FDC90)
#define PATROL_PATH_DATA ((PatrolPathData *)D_807FDCA0)
#define PATROL_ACTOR ((PatrolActorView *)D_807FBB40)
#define PATROL_WAYPOINT(off) ((PatrolWaypoint *)(PATROL_PATH_DATA->unk14 + (off)))

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
  idx = (dir = ((PatrolState *) D_807FDC90)->unk25);
  dir = dir & 0x80;
  idx = idx & 0x7F;
  key = ((D1Pair *) ((D1Dc98ViewG *) D_807FDC98)->unk20)[idx].a;
  type = ((D1Pair *) ((D1Dc98ViewG *) D_807FDC98)->unk20)[idx].b;
  key = key ^ 0;  // FAKE
  off = key * 10;
  x = ((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + off))->x;
  y = ((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + off))->y;
  z = ((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + off))->z;
  moved = (((((PatrolActorView *) D_807FBB40)->unk7C - x) * (((PatrolActorView *) D_807FBB40)->unk7C - x)) + ((((PatrolActorView *) D_807FBB40)->unk84 - z) * (((PatrolActorView *) D_807FBB40)->unk84 - z))) < ((f32) (((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + off))->r * ((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + off))->r));
  if (D_807FDC90) {}  // FAKE
  if (((arg1 & 1) && (((PatrolActorView *) D_807FBB40)->unk88 == ((PatrolActorView *) D_807FBB40)->unk7C)) && (((PatrolActorView *) D_807FBB40)->unk90 == ((PatrolActorView *) D_807FBB40)->unk84))
  {
    ((PatrolState *) D_807FDC90)->unk20++;
    if ((((PatrolState *) D_807FDC90)->unk20++) > 0x10)
    {
      moved = 1;
      ((PatrolState *) D_807FDC90)->unk20 = 0;
    }
  }
  else
  {
    ((PatrolState *) D_807FDC90)->unk20 = 0;
  }
  switch (arg0)
  {
    case 0x49:
      v = idx + 1;
      key = (v < ((D1Dc9cViewG *) D_807FDC9C)->unk11) ? (v) : (0);
      if (D_807FDC90 == 0) {}  // FAKE
      v = mathAngleBetweenPoints2D(((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + (((D1Pair *) ((D1Dc98ViewG *) D_807FDC98)->unk20)[key].a * 10)))->x, ((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + (((D1Pair *) ((D1Dc98ViewG *) D_807FDC98)->unk20)[key].a * 10)))->z, x, z);
      ((PatrolActorView *) D_807FBB40)->unkEE = v;
      ((PatrolActorView *) D_807FBB40)->unkE6 = v;

    case 0x42:

    case 0x5B:
      ((PatrolState *) D_807FDC90)->unkA = x;
      ((PatrolState *) D_807FDC90)->unkC = y;
      ((PatrolState *) D_807FDC90)->unkE = z;
      break;

    case 2:
    case 0x26:
    case 0x60:
      if (moved)
      {
        if (type == 6)
        {
          ((PatrolState *) D_807FDC90)->unk25 = ((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + off))->unk8;
        }
        else if ((idx + 1) < ((D1Dc9cViewG *) D_807FDC9C)->unk11)
        {
          ((PatrolState *) D_807FDC90)->unk25 = idx + 1;
        }
        else
        {
          ((PatrolState *) D_807FDC90)->unk25 = 0;
        }
      }
      else
      {
        ((PatrolState *) D_807FDC90)->unkA = x;
        ((PatrolState *) D_807FDC90)->unkC = y;
        ((PatrolState *) D_807FDC90)->unkE = z;
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
      ((PatrolState *) D_807FDC90)->unk25 = dir | (idx & 0xFFFFFFFFFFFFFFFF);
    }
    else
    {
      ((PatrolState *) D_807FDC90)->unkA = x;
      ((PatrolState *) D_807FDC90)->unkC = y;
      ((PatrolState *) D_807FDC90)->unkE = z;
    }
      break;

  }

  idx = ((PatrolState *) D_807FDC90)->unk25 & 0x7F;
  if (moved)
  {
    ((PatrolState *) D_807FDC90)->unk1A |= 4;
    switch (type)
    {
      case 1:
        new_var = ((D1Pair *) ((D1Dc98ViewG *) D_807FDC98)->unk20)[idx].a;
        key = new_var;
        v = func_8072D08C();
        ((PatrolActorView *) D_807FBB40)->unkEE = v;
        ((PatrolActorView *) D_807FBB40)->unkE6 = v;
        ((PatrolActorView *) D_807FBB40)->unk7C = ((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + (key * 10)))->x;
        ((PatrolActorView *) D_807FBB40)->unk80 = ((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + (key * 10)))->y;
        ((PatrolActorView *) D_807FBB40)->unk84 = ((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + (key * 10)))->z;
        break;

      case 2:
        ((PatrolActorView *) D_807FBB40)->unk154 = 0x26;
        ((PatrolActorView *) D_807FBB40)->unk155 = 0;
        break;

      case 4:
        ((PatrolActorView *) D_807FBB40)->unk154 = 0x19;
        ((PatrolActorView *) D_807FBB40)->unk155 = 0;
        ((PatrolState *) D_807FDC90)->unk2C = ((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + off))->unk8;
        break;

      case 5:
        actorSetTargetSpeed(D_807FBB40, ((PatrolWaypoint *) (((PatrolPathData *) D_807FDCA0)->unk14 + off))->unk8);
        return moved;

      case 7:
        ((PatrolActorView *) D_807FBB40)->unk154 = 0x3B;
        moved = 0;
        break;

      case 8:
        ((PatrolActorView *) D_807FBB40)->unk154 = 0x13;
        ((PatrolActorView *) D_807FBB40)->unk155 = 0;
        break;

      case 3:
        if (((PatrolActorView *) D_807FBB40)->unk58 == 0xAF)
      {
        ((PatrolActorView *) D_807FBB40)->unk154 = 0x37;
        ((PatrolActorView *) D_807FBB40)->unk155 = 0;
      }
        D_80744508++;
        ((PatrolActorView *) D_807FBB40)->unk154 = 0x40;
        break;

    }

  }
  else
  {
    ((PatrolState *) D_807FDC90)->unk1A &= 0xFFFB;
  }
  return moved;
}
