#include "common.h"
#include "compiler/ido/memory.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/112080.h"
#include "proto/global/117190.h"
#include "proto/global/119370.h"
#include "proto/global/11BC10.h"
#include "proto/global/127B00.h"
#include "proto/global/133A90.h"
#include "proto/global/136820.h"
#include "proto/global/15050.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/2F550.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/79890.h"
#include "proto/global/7A510.h"
#include "proto/global/7BBD0.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8CA50.h"
#include "proto/global/8D3E0.h"
#include "proto/global/90D80.h"
#include "proto/global/CEAE0.h"
#include "proto/global/EFDC0.h"

// This TU's .data (0x8074DA30-0x8074E7A0), in address order.
s32 (*gActorInitFuncs[10])(s32 *) = {
    (s32 (*)(s32 *))func_8067B2B0,
    (s32 (*)(s32 *))actorInitFloorAttachment,
    (s32 (*)(s32 *))actorInitAnimAndCollision,
    (s32 (*)(s32 *))actorInitStaticMeshFlag,
    (s32 (*)(s32 *))actorInitCollisionFromModel,
    (s32 (*)(s32 *))func_8067B2B8,
    (s32 (*)(s32 *))func_8067B290,
    (s32 (*)(s32 *))func_8067B298,
    (s32 (*)(s32 *))func_8067B2A0,
    (s32 (*)(s32 *))func_8067B2A8,
};
// Component data sizes, indexed by the component ids of the gActorTypeComponents lists.
u16 gActorComponentSizes[117] = {
    0, 624, 32, 40, 256, 64, 32, 16, 8, 8, 16, 24,
    192, 40, 8, 16, 32, 16, 8, 8, 48, 16, 16, 8,
    8, 8, 32, 24, 2112, 24, 16, 64, 48, 16, 8, 8,
    8, 16, 32, 32, 64, 8, 8, 8, 8, 8, 72, 64,
    8, 8, 16, 8, 32, 216, 40, 16, 48, 16, 152, 8,
    40, 48, 40, 16, 24, 24, 56, 24, 24, 32, 16, 88,
    632, 8, 24, 32, 16, 40, 8, 16, 8, 24, 24, 64,
    16, 8, 120, 16, 16, 24, 16, 8, 8, 8, 56, 8,
    16, 48, 16, 16, 8, 8, 8, 16, 8, 16, 16, 64,
    24, 8, 16, 16, 24, 8, 48, 32, 32,
};
// Per-actor-type component lists (ending with 0), gActorTypeComponents[type].
u16 D_8074DB44[1] = { 0 };
u16 D_8074DB48[1] = { 0 };
u16 D_8074DB4C[3] = { 1, 72, 0 };
u16 D_8074DB54[3] = { 1, 72, 0 };
u16 D_8074DB5C[3] = { 1, 72, 0 };
u16 D_8074DB64[3] = { 1, 72, 0 };
u16 D_8074DB6C[3] = { 1, 72, 0 };
u16 D_8074DB74[3] = { 1, 72, 0 };
u16 D_8074DB7C[3] = { 1, 72, 0 };
u16 D_8074DB84[3] = { 1, 72, 0 };
u16 D_8074DB8C[1] = { 0 };
u16 D_8074DB90[1] = { 0 };
u16 D_8074DB94[2] = { 3, 0 };
u16 D_8074DB98[1] = { 0 };
u16 D_8074DB9C[1] = { 0 };
u16 D_8074DBA0[1] = { 0 };
u16 D_8074DBA4[1] = { 0 };
u16 D_8074DBA8[2] = { 6, 0 };
u16 D_8074DBAC[2] = { 16, 0 };
u16 D_8074DBB0[2] = { 5, 0 };
u16 D_8074DBB4[1] = { 0 };
u16 D_8074DBB8[2] = { 7, 0 };
u16 D_8074DBBC[2] = { 8, 0 };
u16 D_8074DBC0[2] = { 11, 0 };
u16 D_8074DBC4[2] = { 13, 0 };
u16 D_8074DBC8[2] = { 16, 0 };
u16 D_8074DBCC[2] = { 5, 0 };
u16 D_8074DBD0[2] = { 9, 0 };
u16 D_8074DBD4[2] = { 10, 0 };
u16 D_8074DBD8[2] = { 46, 0 };
u16 D_8074DBDC[2] = { 13, 0 };
u16 D_8074DBE0[2] = { 12, 0 };
u16 D_8074DBE4[2] = { 14, 0 };
u16 D_8074DBE8[2] = { 56, 0 };
u16 D_8074DBEC[3] = { 60, 61, 0 };
u16 D_8074DBF4[2] = { 13, 0 };
u16 D_8074DBF8[2] = { 13, 0 };
u16 D_8074DBFC[2] = { 15, 0 };
u16 D_8074DC00[2] = { 13, 0 };
u16 D_8074DC04[2] = { 12, 0 };
u16 D_8074DC08[2] = { 16, 0 };
u16 D_8074DC0C[2] = { 13, 0 };
u16 D_8074DC10[2] = { 13, 0 };
u16 D_8074DC14[2] = { 13, 0 };
u16 D_8074DC18[2] = { 13, 0 };
u16 D_8074DC1C[2] = { 17, 0 };
u16 D_8074DC20[3] = { 60, 62, 0 };
u16 D_8074DC28[2] = { 17, 0 };
u16 D_8074DC2C[2] = { 13, 0 };
u16 D_8074DC30[2] = { 18, 0 };
u16 D_8074DC34[2] = { 13, 0 };
u16 D_8074DC38[2] = { 17, 0 };
u16 D_8074DC3C[2] = { 17, 0 };
u16 D_8074DC40[2] = { 17, 0 };
u16 D_8074DC44[2] = { 17, 0 };
u16 D_8074DC48[2] = { 13, 0 };
u16 D_8074DC4C[2] = { 16, 0 };
u16 D_8074DC50[2] = { 16, 0 };
u16 D_8074DC54[2] = { 14, 0 };
u16 D_8074DC58[2] = { 13, 0 };
u16 D_8074DC5C[2] = { 19, 0 };
u16 D_8074DC60[2] = { 20, 0 };
u16 D_8074DC64[2] = { 46, 0 };
u16 D_8074DC68[2] = { 20, 0 };
u16 D_8074DC6C[2] = { 20, 0 };
u16 D_8074DC70[2] = { 20, 0 };
u16 D_8074DC74[2] = { 20, 0 };
u16 D_8074DC78[2] = { 20, 0 };
u16 D_8074DC7C[2] = { 56, 0 };
u16 D_8074DC80[2] = { 56, 0 };
u16 D_8074DC84[2] = { 57, 0 };
u16 D_8074DC88[1] = { 0 };
u16 D_8074DC8C[2] = { 17, 0 };
u16 D_8074DC90[2] = { 21, 0 };
u16 D_8074DC94[2] = { 13, 0 };
u16 D_8074DC98[2] = { 17, 0 };
u16 D_8074DC9C[2] = { 17, 0 };
u16 D_8074DCA0[2] = { 17, 0 };
u16 D_8074DCA4[2] = { 17, 0 };
u16 D_8074DCA8[2] = { 17, 0 };
u16 D_8074DCAC[2] = { 46, 0 };
u16 D_8074DCB0[2] = { 13, 0 };
u16 D_8074DCB4[2] = { 13, 0 };
u16 D_8074DCB8[2] = { 22, 0 };
u16 D_8074DCBC[1] = { 0 };
u16 D_8074DCC0[2] = { 5, 0 };
u16 D_8074DCC4[2] = { 17, 0 };
u16 D_8074DCC8[2] = { 46, 0 };
u16 D_8074DCCC[2] = { 57, 0 };
u16 D_8074DCD0[2] = { 13, 0 };
u16 D_8074DCD4[2] = { 23, 0 };
u16 D_8074DCD8[2] = { 24, 0 };
u16 D_8074DCDC[1] = { 0 };
u16 D_8074DCE0[2] = { 23, 0 };
u16 D_8074DCE4[1] = { 0 };
u16 D_8074DCE8[2] = { 26, 0 };
u16 D_8074DCEC[2] = { 16, 0 };
u16 D_8074DCF0[2] = { 9, 0 };
u16 D_8074DCF4[2] = { 83, 0 };
u16 D_8074DCF8[2] = { 13, 0 };
u16 D_8074DCFC[1] = { 0 };
u16 D_8074DD00[1] = { 0 };
u16 D_8074DD04[1] = { 0 };
u16 D_8074DD08[1] = { 0 };
u16 D_8074DD0C[1] = { 0 };
u16 D_8074DD10[1] = { 0 };
u16 D_8074DD14[2] = { 87, 0 };
u16 D_8074DD18[2] = { 10, 0 };
u16 D_8074DD1C[2] = { 13, 0 };
u16 D_8074DD20[1] = { 0 };
u16 D_8074DD24[2] = { 17, 0 };
u16 D_8074DD28[2] = { 24, 0 };
u16 D_8074DD2C[2] = { 24, 0 };
u16 D_8074DD30[2] = { 24, 0 };
u16 D_8074DD34[2] = { 24, 0 };
u16 D_8074DD38[1] = { 0 };
u16 D_8074DD3C[2] = { 56, 0 };
u16 D_8074DD40[1] = { 0 };
u16 D_8074DD44[2] = { 17, 0 };
u16 D_8074DD48[2] = { 17, 0 };
u16 D_8074DD4C[2] = { 17, 0 };
u16 D_8074DD50[2] = { 17, 0 };
u16 D_8074DD54[2] = { 17, 0 };
u16 D_8074DD58[2] = { 88, 0 };
u16 D_8074DD5C[3] = { 60, 90, 0 };
u16 D_8074DD64[3] = { 60, 89, 0 };
u16 D_8074DD6C[2] = { 94, 0 };
u16 D_8074DD70[2] = { 97, 0 };
u16 D_8074DD74[1] = { 0 };
u16 D_8074DD78[2] = { 16, 0 };
u16 D_8074DD7C[2] = { 20, 0 };
u16 D_8074DD80[1] = { 0 };
u16 D_8074DD84[2] = { 16, 0 };
u16 D_8074DD88[2] = { 5, 0 };
u16 D_8074DD8C[2] = { 10, 0 };
u16 D_8074DD90[1] = { 0 };
u16 D_8074DD94[2] = { 83, 0 };
u16 D_8074DD98[2] = { 83, 0 };
u16 D_8074DD9C[2] = { 104, 0 };
u16 D_8074DDA0[2] = { 105, 0 };
u16 D_8074DDA4[2] = { 17, 0 };
u16 D_8074DDA8[1] = { 0 };
u16 D_8074DDAC[1] = { 0 };
u16 D_8074DDB0[1] = { 0 };
u16 D_8074DDB4[1] = { 0 };
u16 D_8074DDB8[1] = { 0 };
u16 D_8074DDBC[1] = { 0 };
u16 D_8074DDC0[2] = { 24, 0 };
u16 D_8074DDC4[2] = { 25, 0 };
u16 D_8074DDC8[2] = { 5, 0 };
u16 D_8074DDCC[1] = { 0 };
u16 D_8074DDD0[1] = { 0 };
u16 D_8074DDD4[1] = { 0 };
u16 D_8074DDD8[1] = { 0 };
u16 D_8074DDDC[1] = { 0 };
u16 D_8074DDE0[1] = { 0 };
u16 D_8074DDE4[1] = { 0 };
u16 D_8074DDE8[1] = { 0 };
u16 D_8074DDEC[1] = { 0 };
u16 D_8074DDF0[1] = { 0 };
u16 D_8074DDF4[1] = { 0 };
u16 D_8074DDF8[1] = { 0 };
u16 D_8074DDFC[1] = { 0 };
u16 D_8074DE00[2] = { 31, 0 };
u16 D_8074DE04[3] = { 31, 107, 0 };
u16 D_8074DE0C[2] = { 108, 0 };
u16 D_8074DE10[2] = { 109, 0 };
u16 D_8074DE14[2] = { 11, 0 };
u16 D_8074DE18[2] = { 114, 0 };
u16 D_8074DE1C[2] = { 13, 0 };
u16 D_8074DE20[2] = { 110, 0 };
u16 D_8074DE24[2] = { 13, 0 };
u16 D_8074DE28[1] = { 0 };
u16 D_8074DE2C[1] = { 0 };
u16 D_8074DE30[3] = { 1, 72, 0 };
u16 D_8074DE38[3] = { 31, 34, 0 };
u16 D_8074DE40[2] = { 64, 0 };
u16 D_8074DE44[1] = { 0 };
u16 D_8074DE48[2] = { 31, 0 };
u16 D_8074DE4C[1] = { 0 };
u16 D_8074DE50[3] = { 31, 46, 0 };
u16 D_8074DE58[2] = { 31, 0 };
u16 D_8074DE5C[2] = { 31, 0 };
u16 D_8074DE60[3] = { 31, 33, 0 };
u16 D_8074DE68[5] = { 31, 65, 66, 115, 0 };
u16 D_8074DE74[4] = { 31, 39, 40, 0 };
u16 D_8074DE7C[2] = { 63, 0 };
u16 D_8074DE80[3] = { 31, 42, 0 };
u16 D_8074DE88[2] = { 4, 0 };
u16 D_8074DE8C[4] = { 31, 65, 66, 0 };
u16 D_8074DE94[4] = { 31, 65, 66, 0 };
u16 D_8074DE9C[4] = { 31, 65, 66, 0 };
u16 D_8074DEA4[4] = { 31, 53, 52, 0 };
u16 D_8074DEAC[4] = { 31, 73, 66, 0 };
u16 D_8074DEB4[4] = { 31, 33, 66, 0 };
u16 D_8074DEBC[3] = { 31, 33, 0 };
u16 D_8074DEC4[4] = { 31, 72, 66, 0 };
u16 D_8074DECC[4] = { 31, 72, 66, 0 };
u16 D_8074DED4[4] = { 31, 72, 66, 0 };
u16 D_8074DEDC[4] = { 31, 72, 66, 0 };
u16 D_8074DEE4[4] = { 31, 72, 66, 0 };
u16 D_8074DEEC[4] = { 31, 73, 66, 0 };
u16 D_8074DEF4[2] = { 74, 0 };
u16 D_8074DEF8[2] = { 31, 0 };
u16 D_8074DEFC[4] = { 31, 39, 41, 0 };
u16 D_8074DF04[3] = { 31, 43, 0 };
u16 D_8074DF0C[3] = { 31, 33, 0 };
u16 D_8074DF14[5] = { 31, 33, 66, 34, 0 };
u16 D_8074DF20[3] = { 31, 43, 0 };
u16 D_8074DF28[3] = { 31, 43, 0 };
u16 D_8074DF30[3] = { 31, 38, 0 };
u16 D_8074DF38[2] = { 31, 0 };
u16 D_8074DF3C[2] = { 31, 0 };
u16 D_8074DF40[2] = { 31, 0 };
u16 D_8074DF44[3] = { 31, 46, 0 };
u16 D_8074DF4C[3] = { 31, 46, 0 };
u16 D_8074DF54[3] = { 31, 39, 0 };
u16 D_8074DF5C[2] = { 74, 0 };
u16 D_8074DF60[2] = { 77, 0 };
u16 D_8074DF64[2] = { 78, 0 };
u16 D_8074DF68[4] = { 31, 34, 34, 0 };
u16 D_8074DF70[1] = { 0 };
u16 D_8074DF74[1] = { 0 };
u16 D_8074DF78[4] = { 31, 34, 34, 0 };
u16 D_8074DF80[2] = { 31, 0 };
u16 D_8074DF84[1] = { 0 };
u16 D_8074DF88[2] = { 31, 0 };
u16 D_8074DF8C[4] = { 31, 39, 30, 0 };
u16 D_8074DF94[2] = { 31, 0 };
u16 D_8074DF98[3] = { 31, 39, 0 };
u16 D_8074DFA0[3] = { 31, 37, 0 };
u16 D_8074DFA8[2] = { 31, 0 };
u16 D_8074DFAC[2] = { 79, 0 };
u16 D_8074DFB0[3] = { 31, 33, 0 };
u16 D_8074DFB8[2] = { 31, 0 };
u16 D_8074DFBC[3] = { 31, 34, 0 };
u16 D_8074DFC4[4] = { 31, 39, 33, 0 };
u16 D_8074DFCC[1] = { 0 };
u16 D_8074DFD0[2] = { 31, 0 };
u16 D_8074DFD4[1] = { 0 };
u16 D_8074DFD8[3] = { 31, 44, 0 };
u16 D_8074DFE0[2] = { 31, 0 };
u16 D_8074DFE4[2] = { 31, 0 };
u16 D_8074DFE8[2] = { 31, 0 };
u16 D_8074DFEC[2] = { 31, 0 };
u16 D_8074DFF0[2] = { 31, 0 };
u16 D_8074DFF4[2] = { 31, 0 };
u16 D_8074DFF8[4] = { 31, 73, 66, 0 };
u16 D_8074E000[2] = { 31, 0 };
u16 D_8074E004[3] = { 31, 44, 0 };
u16 D_8074E00C[5] = { 31, 33, 66, 34, 0 };
u16 D_8074E018[3] = { 31, 45, 0 };
u16 D_8074E020[2] = { 31, 0 };
u16 D_8074E024[3] = { 31, 81, 0 };
u16 D_8074E02C[4] = { 31, 72, 66, 0 };
u16 D_8074E034[2] = { 67, 0 };
u16 D_8074E038[3] = { 31, 70, 0 };
u16 D_8074E040[2] = { 31, 0 };
u16 D_8074E044[1] = { 0 };
u16 D_8074E048[2] = { 31, 0 };
u16 D_8074E04C[1] = { 0 };
u16 D_8074E050[3] = { 31, 33, 0 };
u16 D_8074E058[3] = { 31, 32, 0 };
u16 D_8074E060[2] = { 29, 0 };
u16 D_8074E064[1] = { 0 };
u16 D_8074E068[1] = { 0 };
u16 D_8074E06C[2] = { 28, 0 };
u16 D_8074E070[2] = { 31, 0 };
u16 D_8074E074[2] = { 31, 0 };
u16 D_8074E078[3] = { 31, 37, 0 };
u16 D_8074E080[3] = { 31, 37, 0 };
u16 D_8074E088[3] = { 31, 37, 0 };
u16 D_8074E090[2] = { 31, 0 };
u16 D_8074E094[2] = { 31, 0 };
u16 D_8074E098[2] = { 13, 0 };
u16 D_8074E09C[3] = { 31, 100, 0 };
u16 D_8074E0A4[2] = { 31, 0 };
u16 D_8074E0A8[5] = { 31, 33, 66, 34, 0 };
u16 D_8074E0B4[2] = { 13, 0 };
u16 D_8074E0B8[1] = { 0 };
u16 D_8074E0BC[1] = { 0 };
u16 D_8074E0C0[4] = { 31, 39, 68, 0 };
u16 D_8074E0C8[3] = { 73, 43, 0 };
u16 D_8074E0D0[2] = { 31, 0 };
u16 D_8074E0D4[2] = { 31, 0 };
u16 D_8074E0D8[3] = { 31, 33, 0 };
u16 D_8074E0E0[2] = { 31, 0 };
u16 D_8074E0E4[1] = { 0 };
u16 D_8074E0E8[2] = { 31, 0 };
u16 D_8074E0EC[2] = { 31, 0 };
u16 D_8074E0F0[2] = { 31, 0 };
u16 D_8074E0F4[2] = { 31, 0 };
u16 D_8074E0F8[4] = { 31, 39, 68, 0 };
u16 D_8074E100[4] = { 31, 39, 68, 0 };
u16 D_8074E108[4] = { 31, 39, 68, 0 };
u16 D_8074E110[4] = { 31, 39, 68, 0 };
u16 D_8074E118[1] = { 0 };
u16 D_8074E11C[3] = { 31, 69, 0 };
u16 D_8074E124[1] = { 0 };
u16 D_8074E128[2] = { 71, 0 };
u16 D_8074E12C[2] = { 75, 0 };
u16 D_8074E130[2] = { 76, 0 };
u16 D_8074E134[3] = { 53, 47, 0 };
u16 D_8074E13C[6] = { 31, 53, 47, 48, 52, 0 };
u16 D_8074E148[4] = { 53, 47, 49, 0 };
u16 D_8074E150[4] = { 53, 47, 50, 0 };
u16 D_8074E158[2] = { 54, 0 };
u16 D_8074E15C[3] = { 53, 51, 0 };
u16 D_8074E164[5] = { 31, 53, 51, 52, 0 };
u16 D_8074E170[2] = { 80, 0 };
u16 D_8074E174[1] = { 0 };
u16 D_8074E178[2] = { 55, 0 };
u16 D_8074E17C[4] = { 31, 53, 47, 0 };
u16 D_8074E184[2] = { 82, 0 };
u16 D_8074E188[2] = { 31, 0 };
u16 D_8074E18C[2] = { 53, 0 };
u16 D_8074E190[3] = { 84, 72, 0 };
u16 D_8074E198[2] = { 85, 0 };
u16 D_8074E19C[2] = { 86, 0 };
u16 D_8074E1A0[3] = { 53, 51, 0 };
u16 D_8074E1A8[2] = { 58, 0 };
u16 D_8074E1AC[2] = { 116, 0 };
u16 D_8074E1B0[2] = { 53, 0 };
u16 D_8074E1B4[4] = { 31, 53, 52, 0 };
u16 D_8074E1BC[2] = { 58, 0 };
u16 D_8074E1C0[2] = { 59, 0 };
u16 D_8074E1C4[2] = { 27, 0 };
u16 D_8074E1C8[4] = { 91, 72, 66, 0 };
u16 D_8074E1D0[2] = { 92, 0 };
u16 D_8074E1D4[2] = { 93, 0 };
u16 D_8074E1D8[2] = { 96, 0 };
u16 D_8074E1DC[2] = { 98, 0 };
u16 D_8074E1E0[2] = { 95, 0 };
u16 D_8074E1E4[2] = { 99, 0 };
u16 D_8074E1E8[2] = { 101, 0 };
u16 D_8074E1EC[2] = { 102, 0 };
u16 D_8074E1F0[2] = { 103, 0 };
u16 D_8074E1F4[4] = { 106, 72, 66, 0 };
u16 D_8074E1FC[1] = { 0 };
u16 D_8074E200[2] = { 111, 0 };
u16 D_8074E204[3] = { 31, 112, 0 };
u16 D_8074E20C[2] = { 113, 0 };
u16 D_8074E210[1] = { 0 };
u16 D_8074E214[1] = { 0 };
u16 *gActorTypeComponents[344] = {
    D_8074DB44, D_8074DB48, D_8074DB4C, D_8074DB54, D_8074DB5C, D_8074DB64,
    D_8074DB6C, D_8074DB74, D_8074DB7C, D_8074DB84, D_8074DB8C, D_8074DB90,
    D_8074DB94, D_8074DB98, D_8074DB9C, D_8074DBA0, D_8074DBA4, D_8074DBA8,
    D_8074DBAC, D_8074DBB0, D_8074DBB4, D_8074DBB8, D_8074DBBC, D_8074DBC0,
    D_8074DBC4, D_8074DBC8, D_8074DBCC, D_8074DBD0, D_8074DBD4, D_8074DBD8,
    D_8074DBDC, D_8074DBE0, D_8074DBE4, D_8074DBE8, D_8074DBEC, D_8074DBF4,
    D_8074DBF8, D_8074DBFC, D_8074DC00, D_8074DC04, D_8074DC08, D_8074DC0C,
    D_8074DC10, D_8074DC14, D_8074DC18, D_8074DC1C, D_8074DC20, D_8074DC28,
    D_8074DC2C, D_8074DC30, D_8074DC34, D_8074DC38, D_8074DC3C, D_8074DC40,
    D_8074DC44, D_8074DC48, D_8074DC4C, D_8074DC50, D_8074DC54, D_8074DC58,
    D_8074DC5C, D_8074DC60, D_8074DC64, D_8074DC68, D_8074DC6C, D_8074DC70,
    D_8074DC74, D_8074DC78, D_8074DC7C, D_8074DC80, D_8074DC84, D_8074DC88,
    D_8074DC8C, D_8074DC90, D_8074DC94, D_8074DC98, D_8074DC9C, D_8074DCA0,
    D_8074DCA4, D_8074DCA8, D_8074DCAC, D_8074DCB0, D_8074DCB4, D_8074DCB8,
    D_8074DCBC, D_8074DCC0, D_8074DCC4, D_8074DCC8, D_8074DCCC, D_8074DCD0,
    D_8074DCD4, D_8074DCD8, D_8074DCDC, D_8074DCE0, D_8074DCE4, D_8074DCE8,
    D_8074DCEC, D_8074DCF0, D_8074DCF4, D_8074DCF8, D_8074DCFC, D_8074DD00,
    D_8074DD04, D_8074DD08, D_8074DD0C, D_8074DD10, D_8074DD14, D_8074DD18,
    D_8074DD1C, D_8074DD20, D_8074DD24, D_8074DD28, D_8074DD2C, D_8074DD30,
    D_8074DD34, D_8074DD38, D_8074DD3C, D_8074DD40, D_8074DD44, D_8074DD48,
    D_8074DD4C, D_8074DD50, D_8074DD54, D_8074DD58, D_8074DD5C, D_8074DD64,
    D_8074DD6C, D_8074DD70, D_8074DD74, D_8074DD78, D_8074DD7C, D_8074DD80,
    D_8074DD84, D_8074DD88, D_8074DD8C, D_8074DD90, D_8074DD94, D_8074DD98,
    D_8074DD9C, D_8074DDA0, D_8074DDA4, D_8074DDA8, D_8074DDAC, D_8074DDB0,
    D_8074DDB4, D_8074DDB8, D_8074DDBC, D_8074DDC0, D_8074DDC4, D_8074DDC8,
    D_8074DDCC, D_8074DDD0, D_8074DDD4, D_8074DDD8, D_8074DDDC, D_8074DDE0,
    D_8074DDE4, D_8074DDE8, D_8074DDEC, D_8074DDF0, D_8074DDF4, D_8074DDF8,
    D_8074DDFC, D_8074DE00, D_8074DE04, D_8074DE0C, D_8074DE10, D_8074DE14,
    D_8074DE18, D_8074DE1C, D_8074DE20, D_8074DE24, D_8074DE28, D_8074DE2C,
    D_8074DE30, D_8074DE38, D_8074DE40, D_8074DE44, D_8074DE48, D_8074DE4C,
    D_8074DE50, D_8074DE58, D_8074DE5C, D_8074DE60, D_8074DE68, D_8074DE74,
    D_8074DE7C, D_8074DE80, D_8074DE88, D_8074DE8C, D_8074DE94, D_8074DE9C,
    D_8074DEA4, D_8074DEAC, D_8074DEB4, D_8074DEBC, D_8074DEC4, D_8074DECC,
    D_8074DED4, D_8074DEDC, D_8074DEE4, D_8074DEEC, D_8074DEF4, D_8074DEF8,
    D_8074DEFC, D_8074DF04, D_8074DF0C, D_8074DF14, D_8074DF20, D_8074DF28,
    D_8074DF30, D_8074DF38, D_8074DF3C, D_8074DF40, D_8074DF44, D_8074DF4C,
    D_8074DF54, D_8074DF5C, D_8074DF60, D_8074DF64, D_8074DF68, D_8074DF70,
    D_8074DF74, D_8074DF78, D_8074DF80, D_8074DF84, D_8074DF88, D_8074DF8C,
    D_8074DF94, D_8074DF98, D_8074DFA0, D_8074DFA8, D_8074DFAC, D_8074DFB0,
    D_8074DFB8, D_8074DFBC, D_8074DFC4, D_8074DFCC, D_8074DFD0, D_8074DFD4,
    D_8074DFD8, D_8074DFE0, D_8074DFE4, D_8074DFE8, D_8074DFEC, D_8074DFF0,
    D_8074DFF4, D_8074DFF8, D_8074E000, D_8074E004, D_8074E00C, D_8074E018,
    D_8074E020, D_8074E024, D_8074E02C, D_8074E034, D_8074E038, D_8074E040,
    D_8074E044, D_8074E048, D_8074E04C, D_8074E050, D_8074E058, D_8074E060,
    D_8074E064, D_8074E068, D_8074E06C, D_8074E070, D_8074E074, D_8074E078,
    D_8074E080, D_8074E088, D_8074E090, D_8074E094, D_8074E098, D_8074E09C,
    D_8074E0A4, D_8074E0A8, D_8074E0B4, D_8074E0B8, D_8074E0BC, D_8074E0C0,
    D_8074E0C8, D_8074E0D0, D_8074E0D4, D_8074E0D8, D_8074E0E0, D_8074E0E4,
    D_8074E0E8, D_8074E0EC, D_8074E0F0, D_8074E0F4, D_8074E0F8, D_8074E100,
    D_8074E108, D_8074E110, D_8074E118, D_8074E11C, D_8074E124, D_8074E128,
    D_8074E12C, D_8074E130, D_8074E134, D_8074E13C, D_8074E148, D_8074E150,
    D_8074E158, D_8074E15C, D_8074E164, D_8074E170, D_8074E174, D_8074E178,
    D_8074E17C, D_8074E184, D_8074E188, D_8074E18C, D_8074E190, D_8074E198,
    D_8074E19C, D_8074E1A0, D_8074E1A8, D_8074E1AC, D_8074E1B0, D_8074E1B4,
    D_8074E1BC, D_8074E1C0, D_8074E1C4, D_8074E1C8, D_8074E1D0, D_8074E1D4,
    D_8074E1D8, D_8074E1DC, D_8074E1E0, D_8074E1E4, D_8074E1E8, D_8074E1EC,
    D_8074E1F0, D_8074E1F4, D_8074E1FC, D_8074E200, D_8074E204, D_8074E20C,
    D_8074E210, D_8074E214,
};
// 112080 indexes the name table through this word by actorType (2..9).
s32 D_8074E778 = 0;
u8 gPlayerCharacterId[4] = { 0, 0, 2, 3 };
extern const char D_80759260[];
extern const char D_80759268[];
extern const char D_80759270[];
extern const char D_80759278[];
extern const char D_80759280[];
extern const char D_80759288[];
extern const char D_80759290[];
extern const char D_80759298[];
const char *gCharacterNames[8] = {
    D_80759260, D_80759268, D_80759270, D_80759278,
    D_80759280, D_80759288, D_80759290, D_80759298,
};

typedef struct ActorMovePayload2D {
    f32 x;
    f32 z;
    u8 priority;
    u8 skipArcCheck;
} ActorMovePayload2D;

typedef struct ActorMovePayload3D {
    f32 x;
    f32 y;
    f32 z;
    u8 priority;
    u8 skipArcCheck;
} ActorMovePayload3D;

typedef struct ActorStatePayload {
    s16 yaw;
    f32 speedY;
    s16 speedXZ;
} ActorStatePayload;

typedef struct ActorRiderPayload {
    f32 x;
    f32 y;
    f32 z;
    s32 pointIndex;
    u8 spansNodes;
} ActorRiderPayload;

typedef struct ActorEventPayload {
    f32 x;
    f32 y;
    f32 z;
    s16 value0;
    s16 value1;
} ActorEventPayload;

extern u16 D_8074D624[];
extern u8 D_807F94B4;
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern ActorGlobalState gActorGlobalState;
extern PlayerState *gActivePlayerState;
extern u8 D_807FBE08;
extern u8 D_807FBE09;
extern Actor *D_807FBE10[];
extern s16 D_807FBF10;
extern ActorQueueEntry gActorDelayedCallbackQueue[16];
extern s16 gActorDelayedCallbackCount;
extern ActorCallbackNode *D_807FBFE0[];
extern s32 D_807FBFF0[];
extern s16 D_807FC3F0;

extern u16 gModelCacheCount;
extern void *gActorScriptIndexTable;
extern void *gActorScriptAnimTable;
extern void *gActorScriptSoundTable;
extern s32 gActorNextInstanceId;

void actorInit(void) {
    u16 i;

    for (i = 0; i < 32; i++) {
        gModelCache[i].assetId = 0;
        gModelCache[i].refCount = 0;
        gModelCache[i].asset = NULL;
    }
    gModelCacheCount = 0;

    for (i = 0; i < 32; i++) {
        gAnimClipCache[i].id = 0xFFFF;
        gAnimClipCache[i].refCount = 0;
        gAnimClipCache[i].asset = NULL;
    }
    gAnimClipCacheCount = 0;

    gActorScriptAsset = assetLoad(0xD, 0, 1, 1);
    gActorScriptIndexTable = (void *)(gActorScriptAsset->indexTableOffset + (s32)gActorScriptAsset);
    gActorScriptAnimTable = (void *)(gActorScriptAsset->animTableOffset + (s32)gActorScriptAsset);
    gActorScriptSoundTable = (void *)(gActorScriptAsset->soundTableOffset + (s32)gActorScriptAsset);

    for (i = 0; i < 64; i++) {
        gActiveActors[i].actor = NULL;
        gActiveActors[i].unk4 = 0;
    }
    gActiveActorCount = 0;

    actorTableClear();

    gActorNextInstanceId = 0;
    D_807FBE09 = 0;
    gActorDelayedCallbackCount = 0;
    gActivePlayerActor = NULL;
}

void func_80677EC8(s32 unused) {
}

extern u8 gActorTypeInitIndex[];

s32 actorSpawnFromInfo(ActorSpawnInfo *info) {
    u8 initIndex;
    if (actorAllocate((u16)info->type)) {
        initIndex = gActorTypeInitIndex[info->type];
        if (gActorInitFuncs[initIndex](&info->spawnArg)) {
            gSpawnedActor->x = info->x;
            gSpawnedActor->y = info->y;
            gSpawnedActor->z = info->z;
            gSpawnedActor->spawnData = info->spawnData;
            gSpawnedActor->yaw = info->yaw;
            gSpawnedActor->spawnTimer = info->spawnTimer;
            if (info->scriptId != 0) {
                actorScriptStart(gSpawnedActor, info->scriptId);
            }
            return 1;
        }
    }
    return 0;
}

s32 actorSpawn(s32 type, s32 spawnArg) {
    u8 initIndex;
    if (actorAllocate((u16)type)) {
        initIndex = gActorTypeInitIndex[type];
        if (gActorInitFuncs[initIndex](&spawnArg)) {
            return 1;
        }
    }
    return 0;
}

s32 func_80678014(s32 type) {
    if (actorAllocate(type & 0xFFFF) != 0) {
        actorInitFloorAttachment(0);
        return 1;
    }
    return 0;
}

extern u16 D_80748D4A;
extern u16 gSpawnedActorActiveIndex;

s32 actorAllocate(type)
u16 type;
{
    Actor *actor;
    u16 *types;
    void **ptrArray;
    u8 *dataPtr;
    u16 headerSize;
    u16 totalDataSize;

    types = gActorTypeComponents[type];
    headerSize = 0x174;
    totalDataSize = 0;
    if (*types != 0) {
        do {
            if (headerSize) {}  // FAKE: raises headerSize priority so it gets a1 (tds a2)
            totalDataSize += gActorComponentSizes[*types];
            headerSize += 4;
            types++;
        } while (*types != 0);
    }
    totalDataSize += (u16)((headerSize + 7) & 0xFFF8);
    actor = heapAlloc(totalDataSize);
    if (actor != NULL) {
        heapClearBlock(actor);
        types = gActorTypeComponents[type];
        ptrArray = &actor->customState;
        dataPtr = (u8 *)actor + ((u16)((headerSize + 7) & 0xFFF8));
        if (*types != 0) {
            do {
                *ptrArray++ = dataPtr;
                dataPtr += gActorComponentSizes[*types++];
            } while (*types != 0);
        }
        actor->callbacks = NULL;
        actor->callbackMask = -1;
        actor->unk144 = 2;
        actor->attachMode = 0;
        actor->unkF8 = 0x50;
        actor->flags = 0x58144;
        actor->renderFlags = 0;
        actor->alpha = 0xFF;
        actor->actorType = type;
        if (gGlobalOverlayFlags & 0x100) {
            actor->drawDistance = 0x7D0;
        } else {
            actor->drawDistance = 0x1F4;
        }
        actor->flags2 = 0;
        actor->unk156 = 0;
        actor->unk78[0] = 0;
        actor->contactFlags = actor->prevContactFlags = 1;
        actor->interactionType = 1;
        actor->riderList = NULL;
        actor->pathFollow = NULL;
        actor->parentActor = NULL;
        actor->soundSlots[0] = -1;
        actor->soundSlots[1] = -1;
        actor->floorTriangle = NULL;
        actor->chunkIndex = -1;
        actor->spawnData = NULL;
        actor->unk148[0] = NULL;
        actor->unk148[1] = NULL;
        actor->unkD4 = &D_80748D4A;
        actor->segmentFlags = -1;
        actor->collisionFlags = D_8074D624[type];
        actor->floorTiltPitch = 0x400;
        actor->floorNodeId = 0;
        actor->unkCD = 0;
        actor->cullMarginX = 0;
        actor->cullMarginY = 0;
        actor->tintA = 0xF;
        actor->boundingRadius = 0;
        actor->unkB0[0] = -1;
        actor->instanceId = gActorNextInstanceId;
        gActorNextInstanceId++;
        actorTableInsert(actor);
        actorInitHealth(actor);
        gActiveActors[gActiveActorCount].actor = actor;
        gActiveActors[gActiveActorCount].unk4 = 0;
        gSpawnedActorActiveIndex = gActiveActorCount;
        gActiveActorCount++;
        gSpawnedActor = actor;
        return 1;
    }
    return 0;
}

s32 actorDespawn(Actor *actor) {
    actorListRemoveByActor(actor);
    return actorQueueOrDespawn(actor);
}

s32 actorQueueOrDespawn(Actor *actor) {
    s32 i;

    if (D_807FBE09 != 0) {
        if (D_807FBF10 == 0x40) {
            faultSetMessage(0xC, 0, 0, 0);
        }
        if (actor == gCurrentActor) {
            D_807FBE08 = 1;
        }
        for (i = 0; i < D_807FBF10; i++) {
            if (actor == D_807FBE10[i]) {
                return 0;
            }
        }
        D_807FBE10[D_807FBF10] = actor;
        D_807FBF10++;
    } else {
        actorFreeImmediate(actor);
    }
    return 1;
}

void actorFlushDespawnQueue(void) {
    s32 i;
    for (i = 0; i < D_807FBF10; i++) {
        actorFreeImmediate(D_807FBE10[i]);
    }
    D_807FBF10 = 0;
}

void actorRegisterActive(Actor *actor) {
    gActiveActors[gActiveActorCount].actor = actor;
    gActiveActors[gActiveActorCount].unk4 = 0;
    gActiveActorCount++;
}

void actorDeregisterActive(Actor *actor) {
    s16 i;

    sfxStopSlotSound(actor, 0);
    sfxStopSlotSound(actor, 1);
    i = 0;
    if (actor != gActiveActors[0].actor && gActiveActorCount > 0) {
        do {
            i++;
            if (actor == gActiveActors[i].actor) {
                break;
            }
        } while (i < gActiveActorCount);
    }
    if (--gActiveActorCount != 0) {
        gActiveActors[i].actor = gActiveActors[gActiveActorCount].actor;
        gActiveActors[i].unk4 = gActiveActors[gActiveActorCount].unk4;
    }
    func_8062D26C(actor);
    actor->floorTriangle = NULL;
}

void actorDespawnByOwner(s32 owner) {
    s32 i;

    D_807FBE09 = 1;
    D_807FBF10 = 0;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (owner == (s32)actor->parentActor) {
            actorDespawn(actor);
            actor->parentActor = NULL;
        }
    }
    D_807FBE09 = 0;
    actorFlushDespawnQueue();
}

void actorFreeImmediate(Actor *actor) {
    s16 i;
    Actor *parent;

    if (actor->animState != NULL) {
        controllerAnimFree(actor);
    }
    parent = actor->parentActor;
    if (parent != NULL) {
        actorAppendCallback(parent, actor, 0x80000, 0, 0, NULL);
    }
    for (i = 0; i < gActiveActorCount; i++) {
        if (actor == gActiveActors[i].actor->parentActor) {
            gActiveActors[i].actor->parentActor = NULL;
        }
    }
    i = 0;
    effectFreeByResource(actor);
    pathPlaybackStopForActor(actor);
    sfxStopSlotSound(actor, 0);
    sfxStopSlotSound(actor, 1);
    if (gActiveActors[0].actor != actor) {
        if (gActiveActorCount > 0) {
            do {
                i++;
                if (gActiveActors[i].actor == actor) {
                    break;
                }
            } while (i < gActiveActorCount);
        }
    }
    if (i != gActiveActorCount) {
        if (--gActiveActorCount != 0) {
            gActiveActors[i].actor = gActiveActors[gActiveActorCount].actor;
            gActiveActors[i].unk4 = gActiveActors[gActiveActorCount].unk4;
        }
    }
    actorSub140Free(actor->collision);
    proxPathRemoveOwner((s32)actor);
    if (actor->pathFollow != NULL) {
        heapFree(actor->pathFollow);
    }
    if (actor->unk148[0] != NULL) {
        heapFree(actor->unk148[0]);
    }
    if (actor->unk148[1] != NULL) {
        heapFree(actor->unk148[1]);
    }
    func_8062D26C(actor);
    if (actor->actorType != 0x12B) {
        resQueueRemove(actor);
    }
    renderCallbacksDisableForActor(actor);
    actorTableRemove(actor);
    heapFree(actor);
}

void actorUpdateSpawnsWrapper(void) {
    actorListUpdateSpawns();
}

void actorStub7CA80_00(void) {}
void actorStub7CA80_01(void) {}
void actorStub7CA80_02(void) {}
void actorStub7CA80_03(void) {}
void actorStub7CA80_04(void) {}
void actorStub7CA80_05(void) {}
void actorStub7CA80_06(void) {}

ActorCallbackNode *D_807FBFE0[4];

void actorGlobalCallbacksReset(void) {
    s32 i;

    D_807FBE09 = 1;
    D_807FBF10 = 0;
    for (i = 0; i < 4; i++) {
        D_807FBFE0[i] = NULL;
    }
    actorUpdateActiveList(1);
    actorUpdateActiveList(2);
    actorGlobalCallbacksDispatchAndFree(1);
    actorUpdateLightingAndFog();
    D_807FBE09 = 0;
    actorFlushDespawnQueue();
    actorDelayedCallbacksTick();
}

extern void (*D_8074C0A0[])(void);

extern u16 D_807FBB3C;

void actorUpdateActiveList(u8 flags) {
    s32 i;

    for (i = D_807FBB3C = 0; i < gActiveActorCount; i = D_807FBB3C = i + 1) {
        D_807FBE08 = 0;
        gCurrentActor = gActiveActors[i].actor;
        if ((flags == 1 && !(gCurrentActor->flags & 0x100000)) || (flags == 2 && (gCurrentActor->flags & 0x100000))) {
            actorPreTick(gCurrentActor);
            D_8074C0A0[gCurrentActor->actorType]();
            actorPostTick(gCurrentActor);
        }
        i = D_807FBB3C;
    }
}

void actorUpdateWhilePaused(void) {
    s32 i;
    s32 j;

    for (j = 0; j < 4; j++) {
        D_807FBFE0[j] = NULL;
    }
    for (i = D_807FBB3C = 0; i < gActiveActorCount; i = ++D_807FBB3C) {
        gCurrentActor = gActiveActors[i].actor;
        if (gCurrentActor->renderFlags & 2) {
            actorPreTick(gCurrentActor);
            D_8074C0A0[gCurrentActor->actorType]();
            actorPostTick(gCurrentActor);
        }
        if (gCurrentActor->sub4 != NULL) {
            actorCheckWorldBounds(gCurrentActor);
        }
    }
    actorGlobalCallbacksDispatchAndFree(1);
    actorUpdateLightingAndFog();
}

void actorUpdateLightingAndFog(void) {
    s32 i;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (!(actor->flags & 0x08000000) && (actor->flags & 0x500) && (actor->flags & 0x4000)) {
            actorCheckWorldBounds(actor);
        }
        actor->flags &= ~0x100;
    }
}

void actorPreTick(Actor *actor) {
    collisionClearFlags();
    if (actor->collisionFlags & 1) {
        playerSetActiveGlobals(actor);
    }
    actor->prevX = actor->x;
    actor->prevY = actor->y;
    actor->prevZ = actor->z;
    actor->prevSpeedXZ = actor->speedXZ;
    D_807F94B4 = 0;
    if (actor->collision != NULL) {
        actor->collision->unk68 = 0;
    }
    actorRiderListFree(actor);
    if (actor == gActivePlayerActor) {
        actorCollisionCheckBoundingBoxes(actor);
    } else {
        actorInitDamage(actor);
    }
    actorDispatchCallbacks(actor);
    if (actor == gActivePlayerActor) {
        playerStateDispatchQueuedCallback();
    }
    if (actor->unk144 & 4) {
        actorUpdateMovementFlags(actor);
    } else if (actor->collision != NULL) {
        actor->collision->unk6C = 0;
    }
    if (actor->attachMode != 0) {
        actorUpdateSubnodeRotationAndMtx(actor);
    }
}

void actorPostTick(Actor *actor) {
    if ((s32 (*)(s32 *))actorInitCollisionFromModel == gActorInitFuncs[gActorTypeInitIndex[actor->actorType]]) {
        guTranslateF(actor->modelMtx, actor->x, actor->y, actor->z);
    }
    actorUpdatePositionAndSub140(actor);
    actorUpdateArcBounds(actor);
    if (!(actor->flags & 0x08000000)) {
        actor->flags &= ~0x200;
        if (actor->sub4 != NULL) {
            controllerStepMotionWindows(actor);
            if (((actor->flags & 0x500) || actor->unk156 != 0) && !(actor->flags & 0x4000)) {
                actorCheckWorldBounds(actor);
            }
        }
    }
    actorUpdatePeakHeight(actor);
    actorUpdateModelMatrices(actor);
    actorGlobalCallbacksDispatchAndFree(0);
    actorDispatchCollisionResults(actor);
    actorFreeCallbackList(actor);
    actorUpdateEffects(actor);
    animListUpdate(actor);
    actor->flags |= 0x10;
}

void actorCheckBoundsAndMotion(Actor *actor) {
    controllerStepMotionWindows(actor);
    if (actor->flags & 0x500) {
        actorCheckWorldBounds(actor);
    }
}

void actorUpdatePeakHeight(Actor *actor) {
    f32 y = actor->y;

    if (actor->prevY < y) {
        actor->peakY = y;
        return;
    }
    if (actor->contactFlags & 5) {
        if (actor->prevContactFlags & 5) {
            actor->peakY = y;
            return;
        }
        actor->prevPeakY = actor->peakY;
    }
}

extern u8 gCurrentPlayerIndex;

void actorUpdateArcBounds(Actor *actor) {
    u8 arcFlags;

    if ((actor->unk144 & 4) && (D_807FBE08 == 0)) {
        if (actor->flags & 0x10000) {
            actor->hasArcBounds = 0;
            actor->collisionHit = 0;
        }
        actor->hasArcBounds |= actorClearTargetAngle(actor, &actor->arcYawMin, &actor->arcYawMax, &arcFlags);
        arcFlags |= gActorGlobalState.unkE5;
        if (arcFlags != 0) {
            if (!(actor->contactFlags & 0x10)) {
                actor->contactFlags |= 0x10;
                if (actor == gActivePlayerActor) {
                    playerStateQueueCallback(4, 0, gCurrentPlayerIndex);
                }
            }
        }
        if (arcFlags == 0) {
            actor->contactFlags &= ~0x10;
        }
    } else {
        actor->hasArcBounds = 0;
        actor->collisionHit = 0;
        actor->contactFlags &= ~0x10;
    }
}

void actorRiderListFree(Actor *actor) {
    if (actor->riderList != NULL) {
        heapFree(actor->riderList);
        actor->riderList = NULL;
    }
}

void actorRiderListAdd(Actor *actor, Actor *item) {
    if (actor->riderList == NULL) {
        actor->riderList = heapAlloc(sizeof(ActorList));
        actor->riderList->count = 0;
    }
    if (actor->riderList->count != 4) {
        actor->riderList->items[actor->riderList->count] = item;
        actor->riderList->count++;
    }
}

s32 actorRiderListContains(Actor *actor, Actor *item) {
    ActorList *list = actor->riderList;
    s32 i;

    if (list == NULL) {
        return 0;
    }
    for (i = 0; i < list->count; i++) {
        if (list->items[i] == item) {
            return 1;
        }
    }
    return 0;
}

void actorRegisterGlobalCallback(ActorCallbackNode *node) {
    s32 i = 0;
    s32 found = 0;

    while ((i < 4) && (!found)) {
        if (D_807FBFE0[i] == NULL) {
            found = 1;
        } else {
            i++;
        }
    }
    if (!found) {
        faultSetMessage(0xE, 0, 0, 0);
    } else {
        D_807FBFE0[i] = node;
    }
}

void actorGlobalCallbacksDispatchAndFree(id)
u8 id;
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_807FBFE0[i] != NULL && D_807FBFE0[i]->unk4 == id) {
            ((void (*)(void *))D_807FBFE0[i]->callback)(&D_807FBFE0[i]->source);
            heapFree(D_807FBFE0[i]);
            D_807FBFE0[i] = NULL;
        }
    }
}

void actorFreeCallbackList(Actor *actor) {
    ActorCallbackNode *node = actor->callbacks;
    ActorCallbackNode *next;

    if (node != NULL) {
        actor->callbacks = NULL;
    }
    while (node != NULL) {
        next = node->next;
        if (node->unk10 != NULL) {
            heapFree(node->unk10);
        }
        heapFree(node);
        node = next;
    }
}

void actorCallbackMaskEnable(Actor *actor, s32 mask) {
    actor->callbackMask |= mask;
}

void actorCallbackMaskDisable(Actor *actor, s32 mask) {
    actor->callbackMask &= ~mask;
}

void actorAppendCallback(Actor *actor, Actor *source, s32 type, u8 subtype, s32 ownsPayload, void *payload) {
    s32 pad;
    ActorCallbackNode **link;
    ActorCallbackNode *prev;
    ActorCallbackNode *curr;
    ActorCallbackNode *node;

    prev = NULL;
    if (actorTableContains(actor)) {
        curr = actor->callbacks;
        link = &actor->callbacks;
        if (curr != NULL) {
            do {
                link = &curr->next;
                prev = curr;
                curr = curr->next;
            } while (curr != NULL);
        }
        node = actorAllocCallbackNode(source, type, subtype, ownsPayload, payload);
        *link = node;
        node->prev = prev;
    }
}

void actorQueueDelayedCallback(Actor *target, Actor *source, s32 type, u8 subtype, s32 ownsPayload, void *payload, s32 delay) {
    if (gActorDelayedCallbackCount == 16) {
        faultSetMessage(0xF, 0, 0, 0);
    }
    gActorDelayedCallbackQueue[gActorDelayedCallbackCount].node = actorAllocCallbackNode(source, type, subtype, ownsPayload, payload);
    gActorDelayedCallbackQueue[gActorDelayedCallbackCount].target = target;
    gActorDelayedCallbackQueue[gActorDelayedCallbackCount].delay = delay;
    gActorDelayedCallbackCount++;
}

void actorDelayedCallbacksTick(void) {
    s32 i;
    Actor *actor;
    ActorCallbackNode *node;
    ActorCallbackNode *curr;
    ActorCallbackNode **link;
    ActorCallbackNode *prev;
    s32 changed;

    for (i = 0; i < gActorDelayedCallbackCount; i++) {
        gActorDelayedCallbackQueue[i].delay--;
        if (gActorDelayedCallbackQueue[i].delay == 0) {
            actor = gActorDelayedCallbackQueue[i].target;
            if (actorTableContains(actor)) {
                curr = actor->callbacks;
                link = &actor->callbacks;
                prev = NULL;
                if (curr != NULL) {
                    do {
                        link = &curr->next;
                        prev = curr;
                        curr = curr->next;
                    } while (curr != NULL);
                }
                *link = gActorDelayedCallbackQueue[i].node;
                (*link)->prev = prev;
            } else {
                node = gActorDelayedCallbackQueue[i].node;
                if (node->unk10 != NULL) {
                    heapFree(node->unk10);
                }
                heapFree(node);
            }
        }
    }
    do {
        changed = 0;
        for (i = 0; i < gActorDelayedCallbackCount; i++) {
            if (gActorDelayedCallbackQueue[i].delay == 0) {
                gActorDelayedCallbackQueue[i].node = gActorDelayedCallbackQueue[gActorDelayedCallbackCount - 1].node;
                gActorDelayedCallbackQueue[i].target = gActorDelayedCallbackQueue[gActorDelayedCallbackCount - 1].target;
                gActorDelayedCallbackQueue[i].delay = gActorDelayedCallbackQueue[gActorDelayedCallbackCount - 1].delay;
                gActorDelayedCallbackCount--;
                changed = 1;
            }
        }
    } while (changed);
}

ActorCallbackNode *actorAllocCallbackNode(Actor *source, s32 type, u8 subtype, s32 ownsPayload, void *payload) {
    ActorCallbackNode *node = heapAlloc(sizeof(ActorCallbackNode));

    node->callback = (void *)type;
    node->unk4 = subtype;
    node->source = source;
    node->unkC = ownsPayload;
    node->unk10 = payload;
    node->next = NULL;
    return node;
}

typedef struct ActorSurfacePayload {
    s16 yaw;
    s16 speed;
    u8 pos[0xC];
    u8 verts[0x24];
    s32 mtxIndex;
    s32 hitRadius;
    s32 maxClamp;
} ActorSurfacePayload;

typedef struct ActorHitPayload {
    u8 pos[0xC];
    u8 verts[0x24];
    s32 mtxIndex;
    s32 hitRadius;
    s32 maxClamp;
} ActorHitPayload;

void actorDispatchCallbacks(Actor *actor) {
    s16 pad[2];
    s32 mask;
    f32 targetX;
    f32 targetY;
    f32 targetZ;
    s32 bestType;
    u8 pad1;
    u8 skipArcCheck;
    s8 bestPriority;
    s32 priority2D;
    s32 priority3D;
    ActorRiderPayload *riderPayload;
    ActorHitPayload *hit;
    ActorSurfacePayload *surfacePayload;
    f32 *pointPair;
    ActorEventPayload *eventPayload;
    PlayerState *playerState;
    ActorMovePayload2D *move2D;
    ActorMovePayload3D *move3D;
    f32 *vecPayload;
    ActorStatePayload *launchPayload;
    ActorSub140 *collision;
    s32 *collisionValue;
    Actor *player;
    ActorCallbackNode *node;

    bestPriority = -1;
    actorGlobalStateClearEvents();
    node = actorCallbackListSort(actor->callbacks);
    actor->callbacks = node;
    mask = actor->callbackMask;
    while (node != NULL) {
        if ((s32)node->callback & mask) {
            switch ((s32)node->callback) {
            case 0x8000:
                actorCollisionProcessHit(actor, node);
                if (((gActorGlobalState.bossFightPhase == 9) || (gActorGlobalState.bossFightPhase == 0xA)) && (actor->collisionFlags & 1)) {
                    playerHandleDamageReaction(actor, gActorGlobalState.targetActor, (gActorGlobalState.bossFightPhase == 0xA));
                }
                break;
            case 0x2:
                switch (node->unk4) {
                case 0:
                    gActorGlobalState.unk16 = 1;
                    if (actor == gActivePlayerActor) {
                        playerStateQueueCallback(0x10, NULL, gCurrentPlayerIndex);
                    }
                    break;
                case 1:
                    gActorGlobalState.unk17 = 1;
                    if (actor == gActivePlayerActor) {
                        playerStateQueueCallback(0xE, node->source, gCurrentPlayerIndex);
                    }
                    break;
                case 2:
                    gActorGlobalState.unk18 = 1;
                    if (actor == gActivePlayerActor) {
                        playerStateQueueCallback(0x12, NULL, gCurrentPlayerIndex);
                    }
                    break;
                case 3:
                    gActorGlobalState.unk19 = 1;
                    if (actor == gActivePlayerActor) {
                        playerStateQueueCallback(0x13, NULL, gCurrentPlayerIndex);
                    }
                    break;
                case 6:
                    gActorGlobalState.unk1B = 1;
                    if (actor == gActivePlayerActor) {
                        playerStateQueueCallback(0x36, node->source, gCurrentPlayerIndex);
                    }
                    break;
                case 4:
                case 5:
                    if (actor == gActivePlayerActor) {
                        if (node->unk4 == 4) {
                            playerStateQueueCallback(0x2B, node->source, gCurrentPlayerIndex);
                        } else {
                            playerStateQueueCallback(0x32, node->source, gCurrentPlayerIndex);
                        }
                        player = node->source;
                        if ((player != NULL) && (player->collisionFlags & 2)) {
                            playerState = player->customState;
                            playerState->unk1A |= 0x100;
                        }
                    }
                    break;
                }
                break;
            case 0x8:
                playerHandleDamageReaction(actor, node->source, 0);
                break;
            case 0x4:
                playerHandleDamageReaction(actor, node->source, 1);
                break;
            case 0x800:
                actor->unk144 = node->unk4;
                gActorGlobalState.unk90 = 1;
                break;
            case 0x400:
                launchPayload = node->unk10;
                gActivePlayerState->launchYaw = launchPayload->yaw;
                gActivePlayerState->launchSpeedY = launchPayload->speedY;
                gActivePlayerState->launchSpeedXZ = launchPayload->speedXZ;
                gActorGlobalState.unk1A = 1;
                if (actor == gActivePlayerActor) {
                    playerStateQueueCallback(0x17, node->source, gCurrentPlayerIndex);
                }
                break;
            case 0x10:
                move2D = node->unk10;
                priority2D = move2D->priority;
                if (bestPriority < priority2D) {
                    bestPriority = priority2D;
                    targetX = move2D->x;
                    targetZ = move2D->z;
                    bestType = (s32)node->callback;
                    skipArcCheck = move2D->skipArcCheck;
                }
                break;
            case 0x20:
                move3D = node->unk10;
                priority3D = move3D->priority;
                if (bestPriority < priority3D) {
                    bestPriority = priority3D;
                    targetX = move3D->x;
                    targetY = move3D->y;
                    targetZ = move3D->z;
                    bestType = (s32)node->callback;
                    skipArcCheck = move3D->skipArcCheck;
                }
                break;
            case 0x100000:
                vecPayload = node->unk10;
                gActorGlobalState.unkD8 = vecPayload[0];
                gActorGlobalState.unkDC = vecPayload[1];
                gActorGlobalState.unkE0 = vecPayload[2];
                gActorGlobalState.unkE4 = 1;
                gActorGlobalState.unkEC = node->source;
                break;
            case 0x1000:
                gActorGlobalState.unk1C = 1;
                gActorGlobalState.unk20 = node->source;
                break;
            case 0x4000:
                launchPayload = node->unk10;
                gActorGlobalState.unk2C = 1;
                gActorGlobalState.unk30 = launchPayload->speedY;
                gActorGlobalState.unk34 = launchPayload->speedXZ;
                gActorGlobalState.unk36 = launchPayload->yaw;
                break;
            case 0x2000:
                if (node->unk4 != 0) {
                    gActorGlobalState.unk24 = 1;
                } else {
                    gActorGlobalState.unk25 = 1;
                }
                gActorGlobalState.unk28 = node->source;
                break;
            case 0x80:
                actor->flags |= 8;
                if (actor == gActivePlayerActor) {
                    playerStateQueueCallback(0x16, node->source, gCurrentPlayerIndex);
                }
                break;
            case 0x40:
                if (node->unk4 != 0) {
                    actor->flags |= 4;
                } else {
                    actor->flags &= ~4;
                }
                break;
            case 0x1:
                riderPayload = node->unk10;
                if (actorTableContains(node->source) != 0 && gActorGlobalState.unk39 != 4) {
                    gActorGlobalState.unk3C[gActorGlobalState.unk39][0] = riderPayload->x;
                    gActorGlobalState.unk3C[gActorGlobalState.unk39][1] = riderPayload->y;
                    gActorGlobalState.unk3C[gActorGlobalState.unk39][2] = riderPayload->z;
                    gActorGlobalState.unk6C[gActorGlobalState.unk39] = riderPayload->pointIndex;
                    gActorGlobalState.unk7C[gActorGlobalState.unk39] = node->source;
                    gActorGlobalState.unk8C[gActorGlobalState.unk39] = riderPayload->spansNodes;
                    gActorGlobalState.unk39++;
                    actorRiderListAdd(actor, node->source);
                }
                break;
            case 0x20000:
                hit = node->unk10;
                if (gActorGlobalState.unk1F8 != 4) {
                    memcpy(gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unk0, hit->pos, 0xC);
                    memcpy(gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unkC, hit->verts, 0x24);
                    gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unk30 = hit->mtxIndex;
                    gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unk34 = hit->hitRadius;
                    gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unk38 = hit->maxClamp;
                    gActorGlobalState.unkF8[gActorGlobalState.unk1F8].unk3C = node->source;
                    gActorGlobalState.unk1F8++;
                }
                break;
            case 0x10000:
                surfacePayload = node->unk10;
                gActorGlobalState.unk91 = 1;
                gActorGlobalState.unk92 = surfacePayload->yaw;
                gActorGlobalState.unk94 = surfacePayload->speed;
                memcpy(gActorGlobalState.unk98, surfacePayload->pos, 0xC);
                memcpy(gActorGlobalState.unkA4, surfacePayload->verts, 0x24);
                gActorGlobalState.unkC8 = surfacePayload->mtxIndex;
                gActorGlobalState.unkCC = node->source;
                gActorGlobalState.unkD0 = surfacePayload->hitRadius;
                gActorGlobalState.unkD4 = surfacePayload->maxClamp;
                break;
            case 0x40000:
                collisionValue = node->unk10;
                collision = actor->collision;
                if (collision != NULL) {
                    collision->unk68 = *collisionValue;
                }
                break;
            case 0x80000:
                gActorGlobalState.unk38 = 1;
                break;
            case 0x200000:
                pointPair = node->unk10;
                gActorGlobalState.unkF0 = pointPair[0];
                gActorGlobalState.unkF4 = pointPair[1];
                break;
            case 0x400000:
                gActorGlobalState.unkE8 = node->unk4;
                gActorGlobalState.unkE5 = 1;
                break;
            case 0x1000000:
                if (gActorGlobalState.volumeTriggerQueueCount < 8) {
                    gActorGlobalState.volumeTriggerQueueOp[gActorGlobalState.volumeTriggerQueueCount] = node->unk4;
                    gActorGlobalState.volumeTriggerQueueId[gActorGlobalState.volumeTriggerQueueCount] = node->unk10;
                    gActorGlobalState.volumeTriggerQueueCount++;
                }
                break;
            case 0x800000:
                eventPayload = node->unk10;
                gActorGlobalState.unk4 = eventPayload->x;
                gActorGlobalState.unk8 = eventPayload->y;
                gActorGlobalState.unkC = eventPayload->z;
                gActorGlobalState.unk10 = eventPayload->value0;
                gActorGlobalState.unk12 = eventPayload->value1;
                gActorGlobalState.unk2 = 1;
                gActorGlobalState.unk14 = node->unk4;
                break;
            case 0x2000000:
                gActorGlobalState.notifyReceived = 1;
                gActorGlobalState.notifyValue[0] = node->unk4;
                break;
            }
        }
        node = node->next;
    }
    if ((bestPriority != -1) && ((skipArcCheck == 1) || (actorCheckPointInAngleArc(actor, targetX, targetZ) != 0))) {
        switch (bestType) {
        case 0x10:
            actor->x = targetX;
            actor->z = targetZ;
            break;
        case 0x20:
            actor->x = targetX;
            actor->y = targetY;
            actor->z = targetZ;
            break;
        }
    }
}

extern PlayerStruct *gPlayerSlots;

extern s32 D_80720E2C;
void playerHandleDamageReaction(Actor *actor, Actor *attacker, u8 heavy) {
    s32 reaction;
    s32 queueReaction;
    void *pulseCallback;
    s32 pad;
    s32 damageLevel;

    gActorGlobalState.unk15 = 1;
    if (actor == gActivePlayerActor) {
        if (!(gPlayerSlots[gActivePlayerState->playerIndex].unk2C0 == 2 && attacker != NULL && (attacker->collisionFlags & 2))) {
            reaction = 0x2E;
            queueReaction = 1;
            if (heavy != 0) {
                reaction = 0x30;
            }
            if (attacker != NULL && attacker->actorType == 0x116) {
                effectSpawnBurstParticleCluster(actor);
                switch (attacker->unk155) {
                case 1:
                    queueReaction = 0;
                    gActivePlayerState->stateFlags ^= 0x80;
                    break;
                case 2:
                    reaction = 0x27;
                    break;
                case 3:
                    effectSetDuration(0xF0);
                    effectSetDepth(1);
                    pulseCallback = &effectPulseSpinUpdate;
                    effectSetCallback(pulseCallback);
                    effectCreateAtActorBone(&D_80720E2C, 0.4f, actor, 1, 2);
                    effectSetDuration(0xF0);
                    effectSetDepth(1);
                    effectSetCallback(pulseCallback);
                    effectCreateAtActorBone(&D_80720E2C, 0.38f, actor, 5, 2);
                    effectSetDuration(0xF0);
                    effectSetDepth(1);
                    effectSetCallback(pulseCallback);
                    effectCreateAtActorBone(&D_80720E2C, 0.3f, actor, 6, 2);
                    queueReaction = 0;
                    gActivePlayerState->stateFlags |= 0x08000000;
                    break;
                }
                gActivePlayerState->statusEffectTimer = 0xF0;
            } else if (attacker != NULL && ((attacker->collisionFlags & 1) || (attacker->collisionFlags & 4) || (attacker->collisionFlags & 2))) {
                if (mpIsMatchType(0) != 0) {
                    if (playerIsSmallerThanAttacker(actor, attacker) != 0) {
                        reaction = 0x31;
                    } else {
                        damageLevel = 1;
                        if (attacker->collisionFlags & 4) {
                            damageLevel = 3;
                        }
                        if (attacker->state != 0x28 && damageLevel < 3) {
                            reaction = 0x2B;
                        } else {
                            reaction = 0xE;
                        }
                    }
                }
            }
            if (queueReaction != 0) {
                playerStateQueueCallback(reaction, attacker, gCurrentPlayerIndex);
            }
        }
    }
}

ActorCallbackNode *actorCallbackListSort(ActorCallbackNode *head) {
    ActorCallbackNode *newHead = head;
    ActorCallbackNode *curr;
    ActorCallbackNode *scan;
    s32 inserted;
    ActorCallbackNode *next;

    if (head != NULL) {
        curr = head->next;
        if (curr != NULL) {
            do {
                scan = curr->prev;
                inserted = 0;
                if (scan != NULL) {
                    do {
                        if ((s32)curr->callback >= (s32)scan->callback) {
                            inserted = 1;
                            curr->prev->next = curr->next;
                            if (curr->next != NULL) {
                                curr->next->prev = curr->prev;
                            }
                            next = scan->next;
                            scan->next = curr;
                            curr->next = next;
                            if (curr->next != NULL) {
                                curr->next->prev = curr;
                            }
                            curr->prev = scan;
                        }
                        scan = scan->prev;
                    } while ((scan != NULL) && (!inserted));
                }
                if (!inserted) {
                    curr->prev->next = curr->next;
                    if (curr->next != NULL) {
                        curr->next->prev = curr->prev;
                    }
                    curr->prev = NULL;
                    curr->next = newHead;
                    newHead->prev = curr;
                    newHead = curr;
                }
                curr = curr->next;
            } while (curr != NULL);
        }
    }
    return newHead;
}

void actorCollisionEventsCancel(Actor *node, u8 event) {
    s32 i;

    for (i = 0; i < gActorGlobalState.unk201; i++) {
        if ((gActorGlobalState.unk244[i] == event) && (gActorGlobalState.unk204[i] == node)) {
            gActorGlobalState.unk244[i] = 0;
        }
    }
}

void actorDispatchCollisionResults(Actor *actor) {
    s32 i;
    f32 hitX;
    f32 hitZ;
    s32 pad60;
    f32 otherX;
    f32 otherZ;

    for (i = 0; i < gActorGlobalState.unk201; i++) {
        switch (gActorGlobalState.unk244[i]) {
        case 0:
            break;
        case 1:
            if (actorCollisionGetNodeHitPoint(actor, gActorGlobalState.unk204[i], &hitX, &hitZ) != 0) {
                actorAppendMoveTarget2D(actor, gActorGlobalState.unk204[i], hitX, hitZ, 0, 1);
            }
            break;
        case 2:
            actorCollisionGetNodeHitPoint(actor, gActorGlobalState.unk204[i], &otherX, &otherZ);
            break;
        case 4:
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 2, 1, 0, 0);
            break;
        case 3:
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 2, 0, 0, 0);
            break;
        case 8:
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 2, 2, 0, 0);
            break;
        case 10:
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 2, 3, 0, 0);
            break;
        case 13:
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 2, 6, 0, 0);
            break;
        case 11:
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 2, 4, 0, 0);
            break;
        case 12:
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 2, 5, 0, 0);
            break;
        case 6:
        case 7:
            if (gActorGlobalState.unk244[i] == 6) {
                actorAppendCallback(gActorGlobalState.unk204[i], actor, 0x40, 0, 0, 0);
            }
            actorAppendMoveTarget3D(actor, gActorGlobalState.unk204[i], actor->x, actor->y, actor->z, 2, 1);
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 0x80, 0, 0, 0);
            playerDropHeldActor(actor);
            break;
        case 5:
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 8, 0, 0, 0);
            break;
        case 15:
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 4, 0, 0, 0);
            break;
        case 9:
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 0x1000, 0, 0, 0);
            break;
        case 14:
            actorAppendCallback(gActorGlobalState.unk204[i], actor, 0x02000000, 0, 0, 0);
            break;
        }
    }

    if (gActorGlobalState.unk39) {
        for (i = 0; i < gActorGlobalState.unk39; i++) {
            if (gActorGlobalState.unk8C[i] == 0) {
                collisionTransformPointByActorMtx(actor, gActorGlobalState.unk6C[i], &gActorGlobalState.unk3C[i][0], gActorGlobalState.unk3C[i][1], &gActorGlobalState.unk3C[i][2]);
                actorAppendMoveTarget2D(actor, gActorGlobalState.unk7C[i], gActorGlobalState.unk3C[i][0], gActorGlobalState.unk3C[i][2], 1, 1);
            }
        }
    }

    if (gActorGlobalState.unk91 != 0) {
        actorCollisionResolveSurfaceHit(actor, gActorGlobalState.unkCC, gActorGlobalState.unk98, gActorGlobalState.unkA4, gActorGlobalState.unkC8, gActorGlobalState.unkD0, gActorGlobalState.unkD4, 1);
    }

    for (i = 0; i < gActorGlobalState.unk1F8; i++) {
        actorCollisionResolveSurfaceHit(actor, gActorGlobalState.unkF8[i].unk3C, gActorGlobalState.unkF8[i].unk0, gActorGlobalState.unkF8[i].unkC, gActorGlobalState.unkF8[i].unk30, gActorGlobalState.unkF8[i].unk34, gActorGlobalState.unkF8[i].unk38, 0);
    }
}

void actorAppendMoveTarget2D(Actor *source, Actor *target, f32 x, f32 z, u8 priority, u8 skipArcCheck) {
    ActorMovePayload2D *payload = heapAlloc(sizeof(ActorMovePayload2D));
    payload->x = x;
    payload->z = z;
    payload->priority = priority;
    payload->skipArcCheck = skipArcCheck;
    actorAppendCallback(target, source, 0x10, 0, 1, payload);
}

void actorAppendMoveTarget3D(Actor *source, Actor *target, f32 x, f32 y, f32 z, u8 priority, u8 skipArcCheck) {
    ActorMovePayload3D *payload = heapAlloc(sizeof(ActorMovePayload3D));
    payload->x = x;
    payload->y = y;
    payload->z = z;
    payload->priority = priority;
    payload->skipArcCheck = skipArcCheck;
    actorAppendCallback(target, source, 0x20, 0, 1, payload);
}

void actorAppendLaunch(Actor *source, Actor *target, s16 yaw, f32 speedY, s16 speedXZ) {
    ActorStatePayload *payload = heapAlloc(sizeof(ActorStatePayload));
    payload->yaw = yaw;
    payload->speedY = speedY;
    payload->speedXZ = speedXZ;
    actorAppendCallback(target, source, 0x4000, 0, 1, payload);
}

void actorAppendRiderPoint(Actor *source, Actor *target, f32 x, f32 y, f32 z, s32 pointIndex, u8 spansNodes) {
    ActorRiderPayload *payload = heapAlloc(sizeof(ActorRiderPayload));
    payload->x = x;
    payload->y = y;
    payload->z = z;
    payload->pointIndex = pointIndex;
    payload->spansNodes = spansNodes;
    actorAppendCallback(target, source, 0x1, 0, 1, payload);
}

void actorAppendSurfaceHit(Actor *source, Actor *target, s16 yaw, s16 speed, void *pos, void *verts, s32 mtxIndex, s32 hitRadius, s32 maxClamp) {
    ActorSurfacePayload *payload = heapAlloc(sizeof(ActorSurfacePayload));
    payload->yaw = yaw;
    payload->speed = speed;
    memcpy(payload->pos, pos, 0xC);
    memcpy(payload->verts, verts, 0x24);
    payload->mtxIndex = mtxIndex;
    payload->hitRadius = hitRadius;
    payload->maxClamp = maxClamp;
    actorAppendCallback(target, source, 0x10000, 0, 1, payload);
}

void actorAppendCollisionHit(Actor *source, Actor *target, void *pos, void *verts, s32 mtxIndex, s32 hitRadius, s32 maxClamp) {
    ActorHitPayload *payload = heapAlloc(sizeof(ActorHitPayload));
    memcpy(payload->pos, pos, 0xC);
    memcpy(payload->verts, verts, 0x24);
    payload->mtxIndex = mtxIndex;
    payload->hitRadius = hitRadius;
    payload->maxClamp = maxClamp;
    actorAppendCallback(target, source, 0x20000, 0, 1, payload);
}

void actorAppendCallbackS32(Actor *source, Actor *target, s32 value) {
    s32 *payload = heapAlloc(sizeof(s32));
    *payload = value;
    actorAppendCallback(target, source, 0x40000, 0, 1, payload);
}

void actorAppendCallbackVec3f(Actor *source, Actor *target, f32 x, f32 y, f32 z) {
    f32 *payload = heapAlloc(3 * sizeof(f32));
    payload[0] = x;
    payload[1] = y;
    payload[2] = z;
    actorAppendCallback(target, source, 0x100000, 0, 1, payload);
}

void actorAppendCallbackVec2f(Actor *source, Actor *target, f32 x, f32 z) {
    f32 *payload = heapAlloc(2 * sizeof(f32));
    payload[0] = x;
    payload[1] = z;
    actorAppendCallback(target, source, 0x200000, 0, 1, payload);
}

void actorAppendPlayerLaunch(Actor *source, Actor *target, s16 yaw, f32 speedY, s16 speedXZ) {
    ActorStatePayload *payload = heapAlloc(sizeof(ActorStatePayload));
    payload->speedY = speedY;
    payload->speedXZ = speedXZ;
    payload->yaw = yaw;
    actorAppendCallback(target, source, 0x400, 0, 1, payload);
}

void actorAppendCallbackMemcpy8(Actor *source, Actor *target, s32 type, u8 subtype, void *data, u8 delayed) {
    void *payload = heapAlloc(8);
    memcpy(payload, data, 8);
    if (!delayed) {
        actorAppendCallback(target, source, type, subtype, 1, payload);
    } else {
        actorQueueDelayedCallback(target, source, type, subtype, 1, payload, 1);
    }
}

void actorAppendEvent(Actor *source, Actor *target, u8 subtype, s16 value0, s16 value1, f32 x, f32 y, f32 z) {
    ActorEventPayload *payload = heapAlloc(sizeof(ActorEventPayload));
    payload->x = x;
    payload->y = y;
    payload->z = z;
    payload->value0 = value0;
    payload->value1 = value1;
    actorAppendCallback(target, source, 0x800000, subtype, 1, payload);
}

void actorGlobalStateClearEvents(void) {
    gActorGlobalState.unkE5 = 0;
    gActorGlobalState.unk15 = 0;
    gActorGlobalState.unk16 = 0;
    gActorGlobalState.unk17 = 0;
    gActorGlobalState.unk18 = 0;
    gActorGlobalState.unk19 = 0;
    gActorGlobalState.unk1B = 0;
    gActorGlobalState.unk1A = 0;
    gActorGlobalState.unk1C = 0;
    gActorGlobalState.unk24 = 0;
    gActorGlobalState.unk25 = 0;
    gActorGlobalState.unk2C = 0;
    gActorGlobalState.unk38 = 0;
    gActorGlobalState.unkE4 = 0;
    gActorGlobalState.unk90 = 0;
    gActorGlobalState.unk39 = 0;
    gActorGlobalState.unk91 = 0;
    gActorGlobalState.unk1F8 = 0;
    gActorGlobalState.targetActor = 0;
    gActorGlobalState.bossFightPhase = 0;
    gActorGlobalState.unk201 = 0;
    gActorGlobalState.volumeTriggerQueueCount = 0;
    gActorGlobalState.unk2 = 0;
    gActorGlobalState.notifyReceived = 0;
    gActorGlobalState.unkE8 = 0.0f;
    gActorGlobalState.unkF0 = 0.0f;
    gActorGlobalState.unkF4 = 0.0f;
}

void actorUpdatePrevContactFlags(Actor *actor) {
    actor->prevContactFlags = actor->contactFlags;
}

u16 actorLookupClass(u16 type) {
    return D_8074D624[type];
}

s32 actorCountOwnedByClass(owner, actorClass, filter)
s32 owner;
u16 actorClass;
s32 (*filter)(Actor *);
{
    u16 count = 0;
    s32 i;

    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (owner == (s32)actor->parentActor && actor->collisionFlags == actorClass) {
            if (filter == NULL || filter(actor)) {
                count++;
            }
        }
    }
    return count;
}

extern u8 gPlayerCount;

Actor *actorFindByType(u16 type) {
    s32 i;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (actor->actorType == type) {
            return actor;
        }
    }
    return NULL;
}

s32 actorIsActive(Actor *target) {
    s32 i;
    for (i = 0; i < gActiveActorCount; i++) {
        Actor *actor = gActiveActors[i].actor;
        if (target == actor) {
            return 1;
        }
    }
    return 0;
}

void actorTableClear(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        D_807FBFF0[i] = -1;
    }
    D_807FC3F0 = 0;
}

void actorTableInsert(Actor *actor) {
    if (D_807FC3F0 < 256) {
        D_807FBFF0[D_807FC3F0++] = (s32)actor;
    } else {
        faultSetMessage(0x13, actor->actorType, 0, 0);
    }
    actorTableSort();
}

void actorTableRemove(Actor *actor) {
    u32 res = actorTableBinarySearch(actor);
    s16 idx = res;
    if (res != -1) {
        D_807FBFF0[idx] = -1;
        actorTableSort();
    }
}

s32 actorTableContains(Actor *actor) {
    if (actorTableBinarySearch(actor) != -1) {
        return 1;
    }
    return 0;
}

s32 actorTableBinarySearch(Actor *key) {
    s16 low = 0;
    s16 high = D_807FC3F0 - 1;

    if (D_807FC3F0 == 0) {
        return -1;
    }
    while (low <= high) {
        s16 mid = (low + high) >> 1;

        if (key == (Actor *)D_807FBFF0[mid]) {
            return mid;
        }
        if (key < (Actor *)D_807FBFF0[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

void actorTableSort(void) {
    s32 done = FALSE;
    s16 i;
    s16 j;

    for (i = 1; i < D_807FC3F0; i++) {
        u32 val = D_807FBFF0[i];

        j = i;
        if (val < (u32)D_807FBFF0[j - 1]) {
            do {
                D_807FBFF0[j] = D_807FBFF0[j - 1];
                j--;
            } while (val < (u32)D_807FBFF0[j - 1]);
        }
        D_807FBFF0[j] = val;
    }
    D_807FC3F0 = 0;
    do {
        if (D_807FBFF0[D_807FC3F0] == -1) {
            done = TRUE;
        } else {
            D_807FC3F0++;
        }
    } while (!done);
}

extern OSContPad *gCurrentContPad;
extern u16 gContPressedButtons;
extern s16 gCurrentCharacterIndex;

void playerSetActiveGlobals(Actor *actor) {
    u8 character;

    gActivePlayerState = actor->customState;
    gCurrentPlayerIndex = gActivePlayerState->playerIndex;
    character = gPlayerCharacterId[gCurrentPlayerIndex];
    gActivePlayerActor = gPlayerSlots[gCurrentPlayerIndex].actor;
    gCurrentKongInventory = &gPlayerInventoryTable[gCurrentPlayerIndex].kong[character];
    gCurrentContPad = gPlayerSlots[gCurrentPlayerIndex].contPad;
    gContPressedButtons = *gPlayerSlots[gCurrentPlayerIndex].heldButtonsPtr;
    gCurrentCharacterIndex = gKongCharacterTable[character].characterIndex;
    gPlayerSlots[gCurrentPlayerIndex].sizeModeDirty = 0;
}

u8 playerFindIndexByActor(Actor *actor) {
    s32 i;
    for (i = 0; i < gPlayerCount; i++) {
        if (gPlayerSlots[i].active != 0 && actor == gPlayerSlots[i].actor) {
            return (u8)i;
        }
    }
    return 0;
}

void actorCopyPoseAndScale(Actor *dest, Actor *src, f32 scale) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
    dest->yaw = src->yaw;
    if (dest->sub4 != NULL) {
        dest->sub4->scaleX = scale;
        dest->sub4->scaleY = scale;
        dest->sub4->scaleZ = scale;
    }
}

void func_8067B280(void) {}
void func_8067B288(void) {}
void func_8067B290(void) {}
void func_8067B298(void) {}
void func_8067B2A0(void) {}
void func_8067B2A8(void) {}

void func_8067B2B0(s32 unused) {
}

void func_8067B2B8(s32 unused) {
}

s32 actorInitFloorAttachment(s32 unused) {
    gSpawnedActor->unk144 = 1;
    return 1;
}

typedef struct ActorInitArg {
    u8 pad0[2];
    u16 animId;
} ActorInitArg;

s32 actorInitAnimAndCollision(ActorInitArg *init) {
    if (controllerAnimInit(gSpawnedActor, init->animId) != 0) {
        gSpawnedActor->collision = actorSub140CreateFromModel(gSpawnedActor);
        gSpawnedActor->eyeHeight = (u32)(((f64)gSpawnedActor->collision->scaledRadius * 0.15) * 0.5);
        return 1;
    }
    return 0;
}

s32 actorInitCollisionFromModel(s32 unused) {
    gSpawnedActor->collision = actorSub140CreateFromModel(gSpawnedActor);
    return 1;
}

s32 actorInitStaticMeshFlag(s32 unused) {
    gSpawnedActor->flags |= 0x2000;
    return 1;
}

const char D_80759260[7] = "DONKEY";
const char D_80759268[6] = "DIDDY";
const char D_80759270[6] = "LANKY";
const char D_80759278[5] = "TINY";
const char D_80759280[7] = "CHUNKY";
const char D_80759288[7] = "KRUSHA";
const char D_80759290[6] = "RAMBI";
const char D_80759298[9] = "ENGUARDE";
