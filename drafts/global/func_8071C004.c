// func_8071C004 (src/global/11BC10.c): stage 6-in-progress: permuter best 3463/4244 (output-3463-1); frame 0x40 vs target 0x58 — palette homes never touched in my build so uopt frees the whole homes region; theory: palette must be memory-anchored (array of s16 sp44[3] in C004 vs scalars in C24C); permuter text is 2-space prettified
typedef struct 
{
  u8 pad0[0x16];
  s16 unk16;
} Fx11BFTimer16;
typedef struct 
{
  u8 pad0[0x330];
  Fx11BFTimer16 *unk330;
  u8 pad334[0xC];
  f32 unk340;
  f32 unk344;
  f32 unk348;
  u8 pad34C[2];
  s16 unk34E;
  u8 pad350;
  u8 unk351;
  u8 pad352[0xA];
  u32 unk35C;
} Fx11BFFadeView;
void func_806086CC(f32, f32, f32, s32, s32, s32, s32, s32, f32, s32);
void func_807149FC(s32);
void func_8071C24C();
extern u8 D_807201D4;
void func_8071C004(Fx11BFFadeView *arg0, s8 *arg1)
{
  f64 ratio;
  f32 new_var;
  s32 temp_v0;
  s16 temp_v0_2;
  s16 sp48;
  s16 sp46;
  s16 sp44;
  f32 temp_fv0;
  float new_var2;
  if (D_8076A0A8 == 0xAA)
  {
    sp46 = 0x46;
    sp44 = 0xFF;
    sp48 = 0;
  }
  else
  {
    sp48 = 0xFF;
    sp46 = 0xFF;
    sp44 = 0xFF;
  }
  temp_v0 = arg0->unk35C;
  switch (temp_v0)
  {
    case 0:
      temp_v0_2 = arg0->unk34E;
      if ((temp_v0_2 == 0xA) && (arg0->unk351 == 0))
    {
      func_806086CC(arg0->unk340, arg0->unk344, arg0->unk348, 0xE4, 0xFF, 0x7F, 0x1E, 0x46, 9.0f, 0);
      func_807149FC(-1);
      func_807149B8(1);
      func_8071498C(func_8071C24C);
      func_80714CC0((s32) (&D_807201D4), 0.8f, arg0->unk340, arg0->unk344, arg0->unk348);
      return;
    }
      new_var = (f32) (arg0->unk330->unk16 * 2);
      temp_fv0 = new_var;
      ratio = (f64) ((temp_fv0 - ((f32) (arg0->unk351 + (temp_v0_2 * 2)))) / temp_fv0);
      lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 200.0f * ((f32) (1.0 - ratio)), 0, sp44, sp46, sp48);
      return;

    case 1:
      temp_fv0 = (f32) (arg0->unk330->unk16 * 2);
 new_var2 = (temp_fv0 - ((f32) (arg0->unk351 + (arg0->unk34E * 2)))) / temp_fv0; do { } while (0);
      lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 200.0f * new_var2, 0, sp44, sp46, sp48);
      return;

  }

}
