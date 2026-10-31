// func_80649E34 (src/global/478F0.c): OlW stage 5: 2-line delay-slot choice only. NEW: inline arg 'csModelStateTrySetByte(p[1], 0xA, 0)' (no new_var2) gives target's beqz slot (li a1,0xa; lh a0 after) but then as1 puts 'move a2,zero' in the jal slot (mine: lh;sw v1,28(sp);jal;move) vs target lh;move;jal;sw. Hoisted new_var2=p[1] gives sw in jal slot but lh in the beqz slot. as1 picks the sw for the jal slot only when no v1-based load (lh a0,2(v1)/0(v1)) is in the block (arg0 const/b/found => sw in slot, as target). Tried since last note (fast container harness, 0.25s/variant, all >=2): d=0xA hoists x 4 anchors x types x arg forms, wrappers (0,x)/(1?x:0)/|0/*1/(s16) on all three args (~3000), K&R/void/s32 prototypes of csModelStateTrySetByte, drop-2nd-call/hash probes (as1 always picks move), hill-climb statement swaps/joins/decl swaps 1300 iters. Needs a source form where li is pulled to the beqz slot while lh a0 stays in the block and sw (not move) is the jal filler.
extern s16 gCsModelIds[];
extern s16 D_807481F4[];
extern s16 D_807481F6[];
extern u8 D_80748212[];
void func_8064199C(void *, s16, s16);

typedef struct CsPairState {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} CsPairState;

void func_80649E34(CsState *cs, s16 csId, s16 b, s16 c)
{
  CsPairState *st;
  s32 found;
  s16 new_var2;
  long new_var;
  s16 *p;
  s32 d;
  if ((*((CsPairState **) cs)) == 0)
  {
    st = heapAlloc(8);
    *((CsPairState **) cs) = st;
    st->unk0 = 0;
    st->unk4 = 0;
  }
  st = *((CsPairState **) cs);
  found = 0;
  if ((*(((u8 *) cs) + 0x49)) != (*st).unk4)
  {
    p = D_807481F4;
    do
    {
      if ((*p) == (*(((u8 *) cs) + 0x49)))
      {
        found = 1;
      }
      else
      {
        p++;
      }
    }
    while (found == 0);
    new_var2 = p[1];
    if (((u32) p) < (new_var = (u32) D_80748212))
    {
      if (1)
      {
        csModelStateTrySetByte(new_var2, 0xA, 0);
        func_8064199C(((CsModelSlotView *) D_807F6000)[hashTableLookup(gCsModelIds[p[1]])].unk7C, 0, 0);
      }
    }
    if (((u32) p) >= ((u32) D_807481F6))
    {
      csModelStateTrySetByte(p[-1], 0x14, 0);
    }
    st->unk4 = *(((u8 *) cs) + 0x49);
  }
}
