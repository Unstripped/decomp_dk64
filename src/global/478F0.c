#include "common.h"
#include "actor.h"
#include "cutscene.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB4C;
extern ActorGlobalState D_807FBB70;
extern u8 D_807FBD70;
extern f32 D_807F621C;
extern f32 D_807F6220;
extern f32 D_807F6224;
extern CsPlayer *D_807FC924;

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80642BF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80642C78.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80642E34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80642FC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80643274.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80643354.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80643440.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806436A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806436E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064384C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806438B8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80643B24.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80643C0C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80643F38.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064409C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064431C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806443E4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806449C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80644A18.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80644CC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80644D50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80644E2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80644EC8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806450C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645238.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645614.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645700.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806458C8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645A64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645B9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645C04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645D14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80645F40.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80646058.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80646770.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80646978.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80646DC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647108.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647170.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647218.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647508.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647610.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064774C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647834.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647A14.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647B74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647CF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80647D7C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80648000.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064826C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806485A0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806487C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80648C50.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80648C84.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064911C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806491F4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806493C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064954C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_806496B0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649BF0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649D74.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649E00.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649E34.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649F64.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_80649FC0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064A180.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064A194.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064A258.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064A804.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064AAC4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064AB1C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064AC28.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B118.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B150.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B190.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B204.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B260.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B2AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B370.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B3F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B4AC.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B514.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B574.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B5A4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B798.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B7C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B7D4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B7E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B828.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B868.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B900.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064B9E0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BAF4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BB4C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BB78.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BBD8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BCB0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BD2C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BE58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BE80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BF58.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064BFD0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C134.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C250.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C3E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C544.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C644.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C708.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C814.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064C9F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064CB3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064CC80.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064CD3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064D0C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064D1E8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064D418.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064D880.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064D978.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064DB98.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064DE04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064DF5C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E174.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E428.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E48C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E4F8.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E55C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E5C0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064E65C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EA48.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EAB4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EB3C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EB9C.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EC04.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EC60.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064ED68.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064EE08.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F028.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F1C4.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F210.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F2F0.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F308.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F358.s")

#pragma GLOBAL_ASM("asm/global/nonmatchings/478F0/func_8064F404.s")
