// func_80649E34 (src/global/478F0.c): stage 5: 1 diff left, delay-slot swap (lh a0,2(v1) hoisted into beqz delay slot vs target li a1,0xa). permuter-found: if(1) wrapper, new_var2=p[1], (*st).unk4 compare; locals st,found,new_var2,new_var,p,d; parked NON_MATCHING in copy
typedef struct CsB8Slot {
    /* 0x00 */ u8 pad0[0x7C];
    /* 0x7C */ void *unk7C;
    /* 0x80 */ u8 pad80[0xA];
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ u8 pad8C[4];
} CsB8Slot; /* 0x90 */
s32 func_806418E8(s16, s16, s16);
void *func_80610FE8(s32);
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
