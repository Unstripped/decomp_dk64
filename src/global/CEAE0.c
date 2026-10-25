#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FC928;
extern u8 D_807FC929;
extern Struct807FD580 *D_807FD580;
extern s16 D_807FD584;
extern u16 D_807FD63C;

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806C9DE0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806C9E10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806C9E40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806C9E70.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806C9EA0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806C9ED0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806C9F00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806C9F44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806C9F74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806C9FD8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CA048.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CA0E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CA1B4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CA26C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CA2AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CA2E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CA540.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CA5F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CB53C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CBE44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CBE90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC10C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC14C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC190.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC284.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC364.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC5DC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC638.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC8A8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC8B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC8F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC920.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC948.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CC970.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CCB0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CCB94.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CCC10.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CCC54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CD424.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CD898.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CD8EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CD988.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CD9A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CDD24.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CE174.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CE4E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CE7A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CE928.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEB44.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEC04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEE64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEED8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CEFBC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF0D0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF138.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF2EC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF398.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF42C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF4B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF580.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF878.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF918.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CF9CC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFC90.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFD68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFDA8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFDEC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFE30.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFE7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFEA4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFECC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFEF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFF1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806CFF9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0150.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D01AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D024C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0378.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D03BC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0408.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0430.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0468.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D06A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0964.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D09E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0A54.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0A84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0DE4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D0EBC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D1080.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/CEAE0/func_806D10D0.s")
