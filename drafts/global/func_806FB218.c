// func_806FB218 (src/global/FCCD0.c): matched TEXT OK via permuter: preserve same-line initialization and parenthesized byte access
void func_806FB218(void)
{
  s32 i;
  s32 offset;
  func_806FAFE4();
 i = 0; offset = 0; do {
    if ((*((((u8 *) D_80754280) + offset) + 6)) != 0)
    {
      func_806F8CFC(i, 0);
    }
    i++;
    offset += 0x30;
  }
  while (i != 0xF);
}
