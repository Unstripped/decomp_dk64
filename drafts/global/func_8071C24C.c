// func_8071C24C (src/global/11BC10.c): stage 6-in-progress: permuter best 672/1332 (output-672-1; earlier 997, 1312); frame 0x58 matches; remaining = sp48 memory-residency (lh-vs-li at lightAdd arg9) + register cascade; permuter text is 2-space prettified (formatting affects scheduling)
s32 collisionCheckGroundAtPoint(f32, f32, f32 *);
void func_80714944(s32);
void func_80714998(s32);
extern u8 D_8071FB54;
void func_8071C24C(TimedEffectActorView *arg0, u8 *arg1)
{
  f32 sp50;
  s16 sp4C;
  s16 sp4A;
  volatile short sp48;
  f32 *temp_v0;
  f32 *temp_v0_2;
  if (arg0->unk384 == 0)
  {
    temp_v0 = func_80610FE8(0xC);
    arg0->unk384 = temp_v0;
    *temp_v0 = 6.0f;
  }
  if (D_8076A0A8 == 0xAA)
  {
    sp4A = 0x46;
    sp48 = 0xFF;
    sp4C = 0;
  }
  else
  {
    sp4C = 0xFF;
    sp48 = 0xFF;
    arg0->unk340 = (f32) (arg0->unk340 + 1.0f);
    sp4A = 0xFF;
  }
  temp_v0_2 = arg0->unk384;
  arg0->unk344 = (f32) (arg0->unk344 + (*temp_v0_2));
  *temp_v0_2 = (f32) (((f64) (*temp_v0_2)) - 0.15);
  sp50 = arg0->unk344;
  if (collisionCheckGroundAtPoint(arg0->unk340, arg0->unk348, &sp50) == 0)
  {
    *arg1 = 1;
  }
  else
    if ((arg0->unk344 < sp50) && (((f64) (*((f32 *) arg0->unk384))) < 0.0))
  {
    *arg1 = 1;
  }
  if ((*arg1) != 0)
  {
    func_806086CC(arg0->unk340, arg0->unk344, arg0->unk348, 0xEA, 0xFF, 0x7F, 0x1E, 0x46, 9.0f, 0);
    func_80714998(2);
    func_807149B8(1);
    func_80714950(1);
    func_8071498C(func_8071C004);
    func_80714944(7);
    func_80714CC0((s32) (&D_8071FB54), 0.667f, arg0->unk340, sp50 + 10.0f, arg0->unk348);
  }
  lightAdd(arg0->unk340, arg0->unk344, arg0->unk348, 0.0f, 0.0f, 0.0f, 200.0f, 0, sp48, sp4A, sp4C);
}
