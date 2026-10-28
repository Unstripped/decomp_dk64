// func_80649E34 (src/global/478F0.c): CsNM7 stage 5: 2-line delay-slot swap only (full=2): target 'beqz at; li a1,0xa; lh a0,2(v1); move a2,zero; jal; sw v1,28(sp)' vs mine 'beqz; lh a0,2(v1); li a1,0xa; ...'. The 2nd call (bnez at; li a1,0x14; lh a0,-2(v1)) already matches, so as1 prefers li over lh as filler there. Tried (all no change): p[1]/*(p+1)/(p+1)[0]/s16-cast forms of arg0 x s16/long/u8/U casts of 0xA and 0 (~600 combos), (void)/d=/if() call wrappers, named d=0xA at 5 positions, hoisted vs inline new_var2 (inline gives sw before jal + move in jal slot = worse), joining 2-4 adjacent statements on one source line (all masks of lines 2183-2196), multi-line call splits, deadsweep sweep incl array forms, permuter 600s x2 (best output only moved new_var2 = p[1] before the compare, same 2 lines). NOT same-line-barrier fixable. as1 text-path (cc -c x.s) does not reproduce the real filler so ugen-order permutation tests are invalid.
extern s16 D_807F6240[];
extern s16 D_807481F4[];
extern s16 D_807481F6[];
extern u8 D_80748212[];
void func_8064199C(void *, s16, s16);

typedef struct CsB8E34State {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
} CsB8E34State;

void func_80649E34(CsState *cs, s16 csId, s16 b, s16 c)
{
  CsB8E34State *st;
  s32 found;
  s16 new_var2;
  long new_var;
  s16 *p;
  s32 d;
  if ((*((CsB8E34State **) cs)) == 0)
  {
    st = func_80610FE8(8);
    *((CsB8E34State **) cs) = st;
    st->unk0 = 0;
    st->unk4 = 0;
  }
  st = *((CsB8E34State **) cs);
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
        func_806418E8(new_var2, 0xA, 0);
        func_8064199C(((CsB8Slot *) D_807F6000)[hashTableLookup(D_807F6240[p[1]])].unk7C, 0, 0);
      }
    }
    if (((u32) p) >= ((u32) D_807481F6))
    {
      func_806418E8(p[-1], 0x14, 0);
    }
    st->unk4 = *(((u8 *) cs) + 0x49);
  }
}
