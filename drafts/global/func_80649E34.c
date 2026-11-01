// func_80649E34 (src/global/478F0.c): stage 5 (frame 0x30, all 76 insns match except 2-insn delay slot swap: target move a2,0; jal; sw v1,0x1c(sp) vs built sw v1,0x1c(sp); jal; move a2,0). Diagnosed via as1probe: as1 refuses to put sw into jal slot when move a2,0 is on the same .loc line as the call; inserting .loc record between move and sw produces full=0 text=0 reloc=0 (exact byte match).
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
    if (((u32) p) < (new_var = (u32) D_80748212))
    {
      if (1)
      {
        new_var2 = p[1];
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
