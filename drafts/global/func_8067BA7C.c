// func_8067BA7C (src/global/80150.c): stage 3: frame 0x30 matches, &D_807FBB40 hoisted into v1 via dead use if (D_807FBB40){}, needs s1 priority
void func_8067BA7C(s32 arg0)
{
  if ((!(D_807FBB40->unk60 & 0x10)) && (arg0 == 0x13))
  {
    animSetSpeed(D_807FBB40, 0, 0.5f);
    animSetLoopMode(D_807FBB40, 0, 0);
    animSetDirection(D_807FBB40, 0, 0);
    animSetLoopLimit(D_807FBB40, 0, -1);
  }
  switch (D_807FBB40->unk154)
  {
    case 0:

    case 1:

    case 2:

    case 3:

    case 4:

    case 5:

    case 6:

    case 7:

    case 8:

    case 9:

    case 12:

    case 13:

    case 14:

    case 15:

    case 16:

    case 17:

    case 18:

    case 19:
      break;

    case 10:
      sfxPlayFromActorWithAltitudeCheck(D_807FBB40, 0x31, 0xFF, 0x7F, 1);
      func_807149B8(0);
      func_807149FC(1);
      func_80714CC0(&D_8071FE08, 0.5f, D_807FBB40->unk7C, D_807FBB40->unk80 + 7.0f, D_807FBB40->unk84);
      func_80689114(arg0, D_807FBB40->unk7C, (f32) (((f64) D_807FBB40->unk80) + 8.3), D_807FBB40->unk84, 0, 1.0f, D_807FBB40);
      D_807FBB40->unk154++;
      break;

    case 11:
      if (D_807FBBA8 != 0)
    {
      D_807FBB40->unk154 = 0x14;
    }
      break;

    case 20:
      if (arg0 == 0x95)
    {
      D_807FBB40->unk168 = 0x1E;
      D_807FBB40->unk154 = 0x15;
    }
      break;

    case 21:
      if (D_807FBB40->unk168 != 0)
    {
      D_807FBB40->unk168--;
    }
    else
    {
      D_807FBB40->unk154 = 0xA;
    }
      if (D_807FBB40)
    {
    }
      break;

  }

  if (arg0 == 0x13)
  {
    actorUpdateModelMatrix(D_807FBB40, 0);
  }
}
