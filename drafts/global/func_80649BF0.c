// func_80649BF0 (src/global/478F0.c): from .scratch/CsB8/func_80649BF0_best.c
s32 func_806418E8(s16, s16, s16);
void *func_80610FE8(s32);
extern s16 D_80748180[][2];

typedef struct CsB8BF0State {
    /* 0x0 */ s32 cnt;
    /* 0x4 */ s32 prev;
} CsB8BF0State;

void func_80649BF0(CsState *cs, s16 csId, s16 b, s16 c) {
  CsB8BF0State *st;
  u8 found;
  int new_var;
  s32 ok;
  s32 i;
  s32 prev;
  s32 d;
  d = *(((u8 *) cs) + 0x48);
  if ((*((CsB8BF0State **) cs)) == 0)
  {
    st = func_80610FE8(8);
    *((CsB8BF0State **) cs) = st;
    st->cnt = 0;
    st->prev = -1;
  }
  st = *((CsB8BF0State **) cs);
  prev = st->prev;
  if (prev == (-1))
  {
    st->prev = *(((u8 *) cs) + 0x48);
  }
  else
  {
    ok = 0;
    if (st->prev & 1)
    {
      if (((*(((u8 *) cs) + 0x48)) + 1) == st->prev)
      {
        ok = 1;
      }
    }
    else
    {
      new_var = (*(((u8 *) cs) + 0x48)) == ((*st).prev + 1);
      if (new_var)
      {
        ok = 1;
      }
    }
    if (ok)
    {
      if ((++st->cnt) == 8)
      {
        *(((u8 *) cs) + 0x4B) = 100;
      }
    }
    else
    {
      i = (found = 0);
      while (!found)
      {
        if (D_80748180[i][0] == st->prev)
        {
          found = 1;
        }
        else
        {
          i++;
        }
      }

      func_806418E8(D_80748180[i][1], 0x28, 0);
      i = 0;
      found = 0;
      while (!found)
      {
        if (D_80748180[i][0] == (*(((u8 *) cs) + 0x48)))
        {
          found = 1;
        }
        else
        {
          i++;
        }
      }

      func_806418E8(D_80748180[i][1], 0x28, 0);
    }
    st->prev = -1;
  }
}
