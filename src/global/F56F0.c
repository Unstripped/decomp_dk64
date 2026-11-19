#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/117190.h"
#include "proto/global/15050.h"
#include "proto/global/166A0.h"
#include "proto/global/17B90.h"
#include "proto/global/19A00.h"
#include "proto/global/69E60.h"
#include "proto/global/6AD90.h"
#include "proto/global/70FD0.h"
#include "proto/global/7130.h"
#include "proto/global/7CA80.h"
#include "proto/global/89250.h"
#include "proto/global/8F050.h"
#include "proto/global/CC800.h"
#include "proto/global/CEAE0.h"
#include "proto/global/E4090.h"
#include "proto/global/EFDC0.h"
#include "proto/global/F56F0.h"
#include "proto/global/F9450.h"

struct WaypointNode;
extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern PlayerStruct *gPlayerSlots;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;
extern s32 gCurrentMap;

// This TU's .data (0x80752DF0-0x80753E94), in address order: IDO emits .data in definition order and
// starts every object on a 4-byte boundary. Between this TU's weapon tables and gWaypointPaths sit the
// per-kong tables (f32[7], or s16[8] with a zero pad entry) read by CEAE0, D5E10, E4090, EFDC0 and others.
// Target chain weight per player animation, indexed by animId - 0xA2 (kongChainUpdateDiddy);
// -0x80 rests the chain.
s8 gDiddyChainAnimWeights[0x130] = {
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,  0x00,  0x00,  0x00,  0x00,  0x00, -0x80, -0x80, -0x80,
     0x00, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,  0x00,  0x00, -0x80,  0x00, -0x80, -0x80,
    -0x80, -0x40, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80,  0x00,  0x00,  0x00, -0x80,  0x00, -0x80,  0x00, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,  0x00,  0x00, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,  0x00,  0x00, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,  0x00,  0x00, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80,  0x00, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80,  0x00, -0x80,  0x00, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80,  0x00,  0x00, -0x80, -0x80, -0x80, -0x80, -0x80,  0x00, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,  0x00,  0x00, -0x80,
     0x00, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,
    -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80, -0x80,  0x00,  0x00,  0x00,
};
u16 gWeaponRecoilAnglesDual[8] = { 0x0000, 0xF830, 0xF448, 0xEC78, 0xE890, 0xE890, 0xF448, 0x0000 };
u16 gWeaponRecoilAnglesBone4[4] = { 0xFA24, 0xF63C, 0xF448, 0xFA24 };
u16 gWeaponRecoilAnglesBone1[4] = { 0xFA24, 0xF63C, 0xF448, 0xFA24 };
u16 gWeaponRecoilAnglesBone1XY[6] = { 0x0000, 0xF448, 0xEC78, 0xE890, 0xF448, 0x0000 };
f32 D_80752F4C = 0.0f;
s16 D_80752F50[8] = { 100, 100, 100, 100, 100, 100, 100, 0 }; // unreferenced
f32 D_80752F60[7] = { 180.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f, 180.0f }; // unreferenced
f32 D_80752F7C[7] = { 20.0f, 20.0f, 20.0f, 20.0f, 20.0f, 20.0f, 20.0f };
f32 D_80752F98[7] = { 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f };
f32 D_80752FB4[7] = { 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f };
f32 D_80752FD0[7] = { 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f };
f32 D_80752FEC[7] = { 20.0f, 20.0f, 20.0f, 20.0f, 20.0f, 20.0f, 20.0f };
f32 D_80753008[7] = { 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f };
f32 gKongSwimStrokeSpeeds[7] = { -20.0f, -20.0f, -20.0f, -20.0f, -20.0f, -20.0f, -20.0f };
f32 D_80753040[7] = { 200.0f, 200.0f, 200.0f, 200.0f, 180.0f, 180.0f, 100.0f };
f32 gKongSwimTurnSpeeds[7] = { 140.0f, 140.0f, 140.0f, 140.0f, 100.0f, 100.0f, 140.0f };
f32 D_80753078[7] = { 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f };
f32 gKongSwimStrokeMaxSpeeds[7] = { 40.0f, 40.0f, 100.0f, 40.0f, 40.0f, 40.0f, 40.0f };
s16 D_807530B0[8] = { 100, 100, 100, 100, 100, 100, 100, 0 };
s16 D_807530C0[8] = { 5, 5, 5, 5, 5, 5, 5, 0 }; // unreferenced
s16 D_807530D0[8] = { 80, 80, 80, 80, 80, 80, 80, 0 };
s16 D_807530E0[8] = { 30, 30, 30, 30, 30, 30, 30, 0 };
f32 gKongSwimPaddleSpeeds[7] = { 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f };
f32 D_8075310C[7] = { -20.0f, -20.0f, -20.0f, -20.0f, -20.0f, -20.0f, -20.0f };
f32 D_80753128[7] = { 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f };
f32 gKongSwimSpeeds[7] = { 140.0f, 140.0f, 140.0f, 140.0f, 140.0f, 140.0f, 140.0f };
s16 D_80753160[8] = { 100, 100, 100, 100, 100, 100, 100, 0 };
f32 D_80753170[7] = { 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 10.0f };
f32 D_8075318C[7] = { 40.0f, 30.0f, 50.0f, 30.0f, 30.0f, 30.0f, 0.0f };
f32 D_807531A8[7] = { 35.0f, 25.0f, 45.0f, 25.0f, 25.0f, 25.0f, 35.0f };
f32 D_807531C4[7] = { 85.0f, 55.0f, 85.0f, 65.0f, 55.0f, 55.0f, 0.0f };
f32 D_807531E0[7] = { 80.0f, 50.0f, 80.0f, 60.0f, 50.0f, 50.0f, 10.0f };
f32 gKongTurnDecelRates[7] = { 140.0f, 140.0f, 140.0f, 140.0f, 140.0f, 140.0f, 300.0f };
f32 D_80753218[7] = { 220.0f, 230.0f, 300.0f, 230.0f, 200.0f, 200.0f, 230.0f };
f32 gKongAirAccel[7] = { 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 12.0f, 15.0f };
f32 gKongDecelRate[7] = { 8.0f, 10.0f, 10.0f, 10.0f, 8.0f, 8.0f, 15.0f };
s16 gKongTurnRate[8] = { 300, 400, 400, 400, 300, 300, 300, 0 };
f32 D_8075327C[7] = { 4.0f, 8.0f, 4.0f, 8.0f, 4.0f, 4.0f, 12.0f };
s16 D_80753298[8] = { 200, 400, 200, 400, 200, 200, 200, 0 };
s16 gKongPickupApproachRadius[8] = { 17, 10, 15, 10, 20, 20, 10, 0 };
f32 D_807532B8[7] = { 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f };
f32 D_807532D4[7] = { 90.0f, 60.0f, 60.0f, 60.0f, 100.0f, 100.0f, 60.0f };
f32 D_807532F0[7] = { 1.5f, 1.0f, 1.0f, 1.0f, 12.0f, 12.0f, 1.0f };
f32 D_8075330C[7] = { 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f };
s16 D_80753328[8] = { 300, 400, 400, 400, 300, 300, 200, 0 };
f32 D_80753338[7] = { 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f };
s16 D_80753354[8] = { 300, 400, 400, 400, 300, 300, 300, 0 };
f32 D_80753364[7] = { 0.0f, 30.0f, 30.0f, 30.0f, 30.0f, 30.0f, 30.0f };
f32 D_80753380[7] = { 2.5f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f };
f32 gKongHoldPutDownOffsets[7] = { 240.0f, 160.0f, 240.0f, 120.0f, 400.0f, 400.0f, 120.0f };
f32 gKongHoldPutDownAngles[7] = { 40.0f, 40.0f, 40.0f, 40.0f, 100.0f, 100.0f, 40.0f };
f32 gKongHoldThrowOffsets[7] = { 280.0f, 260.0f, 120.0f, 120.0f, 400.0f, 400.0f, 120.0f };
f32 gKongHoldThrowAngles[7] = { 0.0f, 80.0f, 40.0f, 40.0f, 100.0f, 100.0f, 40.0f };
f32 D_8075340C[7] = { 120.0f, 120.0f, 120.0f, 120.0f, 120.0f, 120.0f, 120.0f };
f32 D_80753428[7] = { 160.0f, 160.0f, 160.0f, 160.0f, 160.0f, 160.0f, 160.0f };
s16 D_80753444[8] = { 1000, 50, 1000, 1000, 50, 50, 1000, 0 };
f32 D_80753454[7] = { 70.0f, 70.0f, 70.0f, 70.0f, 70.0f, 70.0f, 70.0f };
f32 D_80753470[7] = { 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f };
f32 D_8075348C[7] = { 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f };
s16 D_807534A8[8] = { 300, 300, 300, 300, 300, 300, 300, 0 };
f32 D_807534B8[7] = { 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 20.0f };
s16 D_807534D4[8] = { 300, 300, 300, 300, 300, 300, 300, 0 };
f32 D_807534E4[7] = { 60.0f, 60.0f, 60.0f, 60.0f, 60.0f, 60.0f, 60.0f };
f32 D_80753500[7] = { 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f };
s16 D_8075351C[8] = { 128, 128, 128, 128, 128, 128, 128, 0 };
f32 D_8075352C[7] = { 30.0f, 80.0f, 30.0f, 30.0f, 30.0f, 30.0f, 80.0f };
s16 D_80753548[8] = { 6, 12, 6, 6, 6, 6, 20, 0 };
s16 D_80753558[8] = { 20, 7, 7, 7, 7, 7, 7, 0 };
s16 D_80753568[8] = { 250, 150, 150, 150, 150, 150, 150, 0 };
f32 gKongAccelY[7] = { -20.0f, -20.0f, -30.0f, -30.0f, -20.0f, -20.0f, -30.0f };
f32 D_80753594[7] = { -30.0f, -30.0f, -30.0f, -30.0f, -20.0f, -20.0f, -30.0f };
f32 D_807535B0[7] = { -17.0f, -17.0f, -17.0f, -17.0f, -10.0f, -10.0f, -17.0f };
f32 gKongJumpVelocityY[7] = { 200.0f, 200.0f, 200.0f, 200.0f, 170.0f, 170.0f, 200.0f };
f32 gKongTerminalSpeedY[7] = { -400.0f, -400.0f, -400.0f, -400.0f, -400.0f, -400.0f, -400.0f };
f32 D_80753604[7] = { 266.67f, 266.67f, 266.67f, 266.67f, 266.67f, 266.67f, 266.67f };
f32 D_80753620[7] = { 120.0f, 120.0f, 120.0f, 120.0f, 120.0f, 120.0f, 120.0f };
f32 D_8075363C[7] = { -17.78f, -17.78f, -17.78f, -17.78f, -17.78f, -17.78f, -17.78f };
f32 D_80753658[7] = { -25.0f, -25.0f, -25.0f, -25.0f, -25.0f, -25.0f, -25.0f };
f32 D_80753674[7] = { 20.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f };
f32 D_80753690[7] = { -33.33f, -33.33f, -33.33f, -33.33f, -33.33f, -33.33f, -33.33f };
f32 D_807536AC[7] = { 320.0f, 320.0f, 320.0f, 320.0f, 320.0f, 320.0f, 320.0f };
f32 D_807536C8[7] = { 70.0f, 70.0f, 70.0f, 70.0f, 70.0f, 70.0f, 70.0f };
f32 D_807536E4[7] = { -10.67f, -10.67f, -10.67f, -10.67f, -10.67f, -10.67f, -10.67f };
f32 D_80753700[7] = { -14.0f, -14.0f, -14.0f, -14.0f, -14.0f, -14.0f, -14.0f };
f32 D_8075371C[7] = { 260.0f, 300.0f, 260.0f, 300.0f, 260.0f, 260.0f, 260.0f };
f32 D_80753738[7] = { -14.0f, -14.0f, -14.0f, -14.0f, -14.0f, -14.0f, -14.0f };
f32 D_80753754[7] = { -14.0f, -14.0f, -14.0f, -14.0f, -14.0f, -14.0f, -14.0f };
f32 D_80753770[7] = { 150.0f, 150.0f, 150.0f, 150.0f, 150.0f, 150.0f, 150.0f };
f32 D_8075378C[7] = { 160.0f, 160.0f, 160.0f, 160.0f, 160.0f, 160.0f, 160.0f };
f32 D_807537A8[7] = { -10.66f, -10.66f, -10.66f, -10.66f, -10.66f, -10.66f, -10.66f };
f32 D_807537C4[7] = { 27.0f, 17.0f, 10.0f, 17.0f, 17.0f, 17.0f, 17.0f };
f32 D_807537E0[7] = { 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f };
s16 D_807537FC[8] = { 15, 15, 15, 15, 15, 15, 15, 0 };
s16 D_8075380C[8] = { 60, 120, 60, 60, 60, 60, 300, 0 };
s16 D_8075381C[8] = { 120, 120, 120, 120, 120, 120, 300, 0 };
s16 D_8075382C[8] = { 12, 12, 12, 12, 12, 12, 30, 0 };
s16 D_8075383C[8] = { 20, 20, 20, 20, 20, 20, 20, 0 };
s16 D_8075384C[8] = { 200, 200, 200, 200, 200, 200, 200, 0 };
s16 D_8075385C[8] = { 300, 300, 300, 300, 300, 300, 30, 0 };
s16 D_8075386C[8] = { 14, 8, 8, 8, 16, 16, 8, 0 };
s16 D_8075387C[8] = { 12, 6, 6, 6, 15, 15, 6, 0 };
s16 D_8075388C[8] = { 13, 10, 10, 10, 17, 14, 10, 0 };
f32 D_8075389C[7] = { 14.0f, 8.0f, 8.0f, 2.5f, 31.0f, 16.0f, 8.0f };
s16 D_807538B8[8] = { 12, 6, 6, 2, 30, 30, 6, 0 };
s16 D_807538C8[8] = { 10, 10, 10, 3, 33, 33, 10, 0 };
s16 D_807538D8[8] = { 100, 100, 100, 100, 100, 100, 100, 0 };
s16 D_807538E8[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
s16 D_807538F8[8] = { 75, 75, 75, 75, 75, 75, 75, 0 };
f32 D_80753908[7] = { 226.0f, 226.0f, 226.0f, 226.0f, 190.0f, 190.0f, 226.0f };
f32 D_80753924[7] = { 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f };
f32 D_80753940[7] = { 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f };
s16 D_8075395C[8] = { 20, 20, 20, 20, 18, 18, 18, 0 };
f32 D_8075396C[7] = { 30.0f, 30.0f, 30.0f, 30.0f, 30.0f, 30.0f, 30.0f };
f32 D_80753988[7] = { 90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f, 90.0f };
f32 D_807539A4[7] = { 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f };
f32 D_807539C0[7] = { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f };
s16 D_807539DC[8] = { 15, 15, 15, 15, 15, 15, 15, 0 };
s16 D_807539EC[8] = { 500, 500, 500, 500, 500, 500, 500, 0 };
s16 D_807539FC[8] = { 128, 128, 128, 128, 128, 128, 128, 0 };
// 89250 reads it as D_80753A0C[actor->actorType - 2]
s16 D_80753A0C[8] = { 18, 12, 12, 10, 18, 18, 8, 0 };
// 89250 reads it as D_80753A1C[actor->actorType - 2]
s16 D_80753A1C[8] = { 18, 12, 12, 2, 50, 18, 8, 0 };
s16 D_80753A2C[8] = { 20, 20, 20, 20, 20, 20, 20, 0 };
s16 D_80753A3C[8] = { 14, 7, 10, 8, 18, 18, 6, 0 };
s16 D_80753A4C[8] = { 6, 6, 6, 1, 35, 6, 6, 0 };
f32 D_80753A5C[7] = { 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f };
s16 D_80753A78[8] = { 20, 20, 20, 20, 20, 20, 20, 0 };
s16 D_80753A88[8] = { 16, 16, 16, 18, 20, 20, 16, 0 };
s16 D_80753A98[8] = { 10, 10, 10, 10, 10, 10, 10, 0 };
f32 D_80753AA8[7] = { 50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f };
f32 D_80753AC4[7] = { 80.0f, 80.0f, 80.0f, 80.0f, 80.0f, 80.0f, 80.0f };
f32 D_80753AE0[7] = { 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f };
f32 D_80753AFC[7] = { 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 4.0f };
f32 D_80753B18[7] = { 2.0f, 2.0f, 2.0f, 1.8f, 2.0f, 2.0f, 2.0f };
s16 gKongStickTurnRates[8] = { 341, 341, 341, 341, 341, 341, 341, 0 };
s16 D_80753B44[8] = { 853, 853, 853, 853, 853, 853, 853, 0 };
s16 D_80753B54[8] = { 113, 113, 113, 113, 113, 113, 113, 0 };
s16 D_80753B64[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
s16 D_80753B74[8] = { 400, 0, 0, 0, 50, 50, 0, 0 };
s16 D_80753B84[8] = { 14, 14, 14, 14, 14, 14, 14, 0 }; // unreferenced
s16 D_80753B94[8] = { 6, 6, 6, 6, 6, 6, 6, 0 }; // unreferenced
f32 D_80753BA4[7] = { 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f };
f32 D_80753BC0[7] = { 50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f };
f32 D_80753BDC[7] = { -5.0f, -5.0f, -5.0f, -5.0f, -5.0f, -5.0f, -5.0f };
f32 D_80753BF8[7] = { -50.0f, -50.0f, -50.0f, -50.0f, -50.0f, -50.0f, -50.0f };
f32 D_80753C14[7] = { -80.0f, -80.0f, -80.0f, -80.0f, -80.0f, -80.0f, -80.0f }; // unreferenced
f32 D_80753C30[7] = { 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f, 6.0f };
f32 D_80753C4C[7] = { 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f };
f32 D_80753C68[7] = { 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f };
s16 D_80753C84[8] = { 8, 8, 8, 8, 8, 8, 8, 0 };
s16 gKongCannonLaunchSpeeds[8] = { 20, 20, 20, 20, 20, 20, 20, 0 };
s16 D_80753CA4[8] = { 20, 20, 20, 20, 20, 20, 20, 0 };
f32 gKongKnockbackSpeeds[7] = { 140.0f, 140.0f, 140.0f, 140.0f, 140.0f, 140.0f, 140.0f };
f32 D_80753CD0[7] = { -20.0f, -20.0f, -20.0f, -20.0f, -20.0f, -20.0f, -20.0f };
f32 D_80753CEC[7] = { 130.0f, 130.0f, 130.0f, 130.0f, 130.0f, 130.0f, 130.0f }; // unreferenced
f32 gKongCannonLaunchTimers[7] = { 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f, 100.0f };
f32 D_80753D24[7] = { 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f }; // unreferenced
s16 D_80753D40[8] = { 24, 24, 24, 24, 24, 24, 24, 0 }; // unreferenced
s16 D_80753D50[8] = { 30, 20, 2, 8, 5, 5, 20, 0 };
s16 D_80753D60[8] = { 20, 20, 20, 2, 20, 20, 20, 0 };
f32 D_80753D70[7] = { 29.0f, 14.0f, 19.5f, 16.0f, 31.0f, 31.0f, 14.0f };
f32 D_80753D8C[7] = { 14.0f, 14.0f, 14.0f, 5.4f, 14.0f, 14.0f, 14.0f };
s16 D_80753DA8[8] = { 15, 15, 15, 15, 5, 5, 15, 0 };
s16 D_80753DB8[8] = { 15, 15, 15, 15, 0, 0, 15, 0 };
f32 D_80753DC8[7] = { 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f, 15.0f };
f32 D_80753DE4[7] = { 50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f, 50.0f };
s16 D_80753E00[8] = { 5, 0, 10, 0, 20, 20, 0, 0 };
f32 D_80753E10[7] = { 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f, 40.0f };
f32 gKongProjectileSpeed[7] = { 350.0f, 350.0f, 350.0f, 1100.0f, 350.0f, 350.0f, 350.0f };
f32 D_80753E48[7] = { 400.0f, 400.0f, 400.0f, 400.0f, 400.0f, 400.0f, 400.0f };
s16 gKongMaxActiveProjectiles[8] = { 4, 4, 4, 4, 4, 4, 4, 0 };
s16 D_80753E74[8] = { 0, 0, 0, 0, 500, 0, 0, 0 }; // unreferenced
// unreferenced zeros up to gWaypointPaths (16-aligned: possibly a hidden TU start)
s32 D_80753E84[3] = { 0 };
extern struct WaypointPathTable D_807FD700; // path table header in the asm .bss blob
struct WaypointPathTable *gWaypointPaths = &D_807FD700;

void playerKongStopAudioChannels(Actor *actor, u16 actorType) {
    switch (actorType) {
    case 0xC5:
    case 3:
        actorClearSegmentFlag(actor, 0);
        actorClearSegmentFlag(actor, 1);
        actorClearSegmentFlag(actor, 2);
        break;
    case 0xC8:
    case 6:
        actorSetSegmentFlag(actor, 0);
        actorClearSegmentFlag(actor, 1);
        break;
    case 0xC6:
    case 4:
        actorSetSegmentFlag(actor, 0);
        actorClearSegmentFlag(actor, 1);
        break;
    case 0xC7:
    case 5:
        actorSetSegmentFlag(actor, 0);
        actorClearSegmentFlag(actor, 1);
        break;
    case 0xC4:
    case 2:
        actorSetSegmentFlag(actor, 0);
        actorClearSegmentFlag(actor, 1);
        break;
    case 7:
        actorSetSegmentFlag(actor, 1);
        actorClearSegmentFlag(actor, 0);
        break;
    }
}


void playerKongPlayHolsterSfx(Actor *actor) {
    switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
    case 0:
        sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xFF, 0x7F, 0x19);
        break;
    case 1:
        sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xC8, 0xA0, 5);
        break;
    case 2:
        sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xFF, 0x7F, 5);
        break;
    case 3:
        sfxPlayFromActorWithAltitudeCheck(actor, 0x185, 0xFF, 0x7F, 0x19);
        break;
    default:
        sfxPlayFromActorWithAltitudeCheck(actor, 0x18F, 0xFF, 0x7F, 0x19);
        break;
    }
}

void playerKongHolsterGun(Actor *actor) {
    s32 pad;
    PlayerState *extra;

    switch (controllerLookupModelAssetId(actor)) {
    case 1:
    case 2:
    case 3:
        actorClearSegmentFlag(actor, 0);
        actorClearSegmentFlag(actor, 1);
        break;
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
        actorSetSegmentFlag(actor, 0);
        actorClearSegmentFlag(actor, 1);
        break;
    case 0xDB:
        actorSetSegmentFlag(actor, 1);
        actorClearSegmentFlag(actor, 0);
        break;
    case 6:
    case 7:
    case 8:
        actorSetSegmentFlag(actor, 0);
        actorClearSegmentFlag(actor, 1);
        break;
    case 9:
    case 0xA:
    case 0xB:
        actorSetSegmentFlag(actor, 0);
        actorClearSegmentFlag(actor, 1);
        break;
    case 4:
    case 5:
        actorSetSegmentFlag(actor, 0);
        actorClearSegmentFlag(actor, 1);
        break;
    }
    if (actor->collisionFlags & 1) {
        extra = actor->customState;
        if (extra->gunDrawn != 0) {
            playerKongPlayHolsterSfx(actor);
            extra->gunDrawn = 0;
        }
    }
}


void playerKongDrawGun(Actor *actor) {
    s32 pad;
    PlayerState *extra;

    switch (controllerLookupModelAssetId(actor)) {
    case 1:
    case 2:
        actorSetSegmentFlag(actor, 0);
        actorSetSegmentFlag(actor, 1);
        break;
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
        actorClearSegmentFlag(actor, 0);
        actorSetSegmentFlag(actor, 1);
        break;
    case 0xDB:
        actorClearSegmentFlag(actor, 1);
        actorSetSegmentFlag(actor, 0);
        break;
    case 6:
    case 7:
        actorClearSegmentFlag(actor, 0);
        actorSetSegmentFlag(actor, 1);
        break;
    case 9:
    case 0xA:
        actorClearSegmentFlag(actor, 0);
        actorSetSegmentFlag(actor, 1);
        break;
    case 4:
        actorClearSegmentFlag(actor, 0);
        actorSetSegmentFlag(actor, 1);
        break;
    }
    if (actor->collisionFlags & 1) {
        extra = actor->customState;
        if (extra->gunDrawn == 0) {
            switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
            case 0:
                sfxPlayFromActorWithAltitudeCheck(actor, 0x186, 0xFF, 0x64, 0x19);
                sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xFF, 0x64, 0x19);
                break;
            case 1:
                sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xC8, 0xBE, 5);
                break;
            case 2:
                sfxPlayFromActorWithAltitudeCheck(actor, 0x186, 0xFF, 0x7F, 0x19);
                sfxPlayFromActorWithAltitudeCheck(actor, 0x17C, 0xFF, 0xA0, 5);
                break;
            case 3:
                sfxPlayFromActorWithAltitudeCheck(actor, 0x185, 0xFF, 0x7F, 0x19);
                break;
            default:
                sfxPlayFromActorWithAltitudeCheck(actor, 0x18E, 0xFF, 0x7F, 0x19);
                break;
            }
            extra->gunDrawn = 1;
        }
        if (mpIsMatchType(0) != 0) {
            gPlayerInventoryTable[extra->playerIndex].kong[playerGetResolvedKongId(extra->playerIndex)].weaponFlags = 1;
            gridSpawnAmmoCrateItems(extra->playerIndex, 0, actor, 0x8F);
        }
    }
}


void playerKongClearFlagsByActorType(Actor *actor) {
    PlayerState *state = actor->customState;

    switch (actor->actorType) {
    case 4:
    case 0xC6:
        state->stateFlags &= ~0x100;
    case 3:
    case 5:
    case 6:
    case 0xC5:
    case 0xC7:
    case 0xC8:
        if (!(state->stateFlags & 0x40)) {
            controllerAnimFreeStateAsset(actor);
        }
        break;
    }
    actorSetInteractionTimer(gCurrentActor);
}

void playerKongSpawnTransformationSmoke(Actor *actor) {
    switch (actor->actorType) {
        case 2:
        case 0xC4:
            playerKongHolsterGun(actor);
            actorSpawn(0xEF, 0xA6);
            actorCopyPoseAndScale(gSpawnedActor, actor, actor->sub4->scaleY * 1.25);
            gSpawnedActor->pitch = actor->pitch;
            gSpawnedActor->roll = actor->roll;
            gSpawnedActor->flags |= 0x40000000;
            break;
        case 3:
        case 0xC5:
            playerKongHolsterGun(actor);
            controllerAnimLoadStateAsset(actor, 2);
            break;
        case 4:
        case 0xC6:
            playerKongHolsterGun(actor);
            controllerAnimLoadStateAsset(actor, 7);
            break;
        case 5:
        case 0xC7:
            playerKongHolsterGun(actor);
            controllerAnimLoadStateAsset(actor, 0xA);
            break;
        case 6:
        case 0xC8:
            playerKongHolsterGun(actor);
            controllerAnimLoadStateAsset(actor, 0xD);
            break;
    }
}

extern s32 gGlobalCutsceneFlags;

void playerTransformAnimalStartSfx(Actor *actor) {
    PlayerState *extra = actor->customState;

    if (actor->actorType == 6) {
        controllerAnimLoadStateAsset(actor, 0x10);
        sfxPlayAtPositionPooled(actor->x, actor->y, actor->z, 0x2E2, 0xFF, 0xA0, 0, 0x32, 0.0f, 0);
        if (!(gGlobalCutsceneFlags & 2)) {
            sfxAllocateChannel(0x6C, 1.0f);
        }
    }
    extra->stateFlags |= 0x40;
}

void playerTransformAnimalEndSfx(Actor *actor) {
    PlayerState *extra = actor->customState;

    if (actor->actorType == 6) {
        controllerAnimFreeStateAsset(actor);
        sfxStopChannel(0x6C, 0);
    }
    extra->stateFlags &= ~0x40;
}


void playerFireWeaponPrimary(Actor *actor) {
    playerFireWeapon(0, 1);
}

void playerScriptCmdNop(Actor *actor) {}

void scriptCmdCompareSpeedXZ(Actor *actor) {
    f32 temp;

    scriptReadU32(&temp);
    actor->sub4->scriptResult = (s32)(actor->speedXZ - temp);
}




void scriptCmdCompareMoveTier(Actor *actor) {
    u8 temp;

    scriptReadU8(&temp);
    actor->sub4->scriptResult =
        playerSelectMoveTier(actor, actor->speedXZ, actor->speedXZ, gActivePlayerState->unk4C, gCurrentCharacterIndex) - temp;
}

void playerResumeLocomotionDecel(Actor *actor) {
    f32 value;

    playerResumeLocomotion(actor);
    value = gCurrentActor->speedXZ;
    gCurrentActor->speedXZ =
        gPlayerPadState[gCurrentPlayerIndex].stickMagNorm * (value - (value / 2)) + (value / 2);
}


void playerD0150Wrapper(Actor *actor) {
    playerEnterBarrelTransition(actor);
}

void playerKongCalculateHealthScale(Actor *actor) {
    f32 limit;
    u8 amount;
    f64 den;
    f32 base;
    f32 value;
    f32 high;
    f32 ratio;
    s32 count;

    scriptReadU32(&limit);
    scriptReadU8(&amount);
    base = actor->sub4->model->frame;
    actor->sub4->scriptResult = 0;
    if ((actor->contactFlags & 2) && ((actor->waterY - actor->floorY) > 12.0f)) {
        high = (actor->waterY < actor->floorY) ? actor->floorY : actor->waterY;
        value = actor->y - high;
        if (value < 0.0f) {
            value = 0.0f;
        }
    } else {
        value = actor->distToFloor;
    }
    count = mathCalculateRatioClamped(value * 40.0f, actor->speedY, actor->terminalSpeedY, actor->accelY);
    if (count == 0) {
        actor->sub4->scriptResult = 1;
        return;
    }
    ratio = ((f32)(u32)amount - base) / count;
    if (ratio < 0.0f) {
        ratio = 0.01f;
    }
    den = (actor->sub4->model->speed < 0.01) ? 0.01 : actor->sub4->model->speed;
    ratio = ratio / den;
    if (limit < ratio) {
        ratio = limit;
    }
    scriptSetActorRampTarget(actor, ratio, 0.0f);
}


s32 mathCalculateRatioClamped(f32 distance, f32 speed, f32 maxSpeed, f32 accel) {
    f32 quot;
    f32 val;
    f32 res;

    if ((distance < 0.0f) || (0.0f < maxSpeed) || (0.0f <= accel)) {
        return 0;
    }
    quot = (maxSpeed - speed) / accel;
    val = distance;
    val += ((speed + maxSpeed) / 2) * quot;
    if (val > 0.0f) {
        res = quot - val / maxSpeed;
    } else {
        res = (-sqrtf((speed * speed) - (2 * accel * distance)) - speed) / accel;
    }
    return (s32)(res + 0.5);
}


void playerWeaponCalculateTrajectory7(Actor *actor, BoneRotation *slots, s32 *count) {
    s32 index;
    u16 angle;
    angle = 7U;  // FAKE: the bound shares angle with the table value (one register)
    index = gActivePlayerState->recoilTimer - 0x14;
    if ((index >= 0) && ((u32) index < angle)) {
        angle = gWeaponRecoilAnglesDual[index];
        slots[*count].weight = 0x7F;
        slots[*count].bone = gActivePlayerState->lastFireHand != 0 ? 9 : 8;
        slots[*count].rotX = 0;
        slots[*count].rotY = gActivePlayerState->lastFireHand != 0 ? angle : -angle;
        slots[*count].rotZ = 0;
        *count += 1;
    }
}

void playerWeaponCalculateTrajectory4(Actor *actor, BoneRotation *slots, s32 *count) {
    s32 index;
    u16 angle;
    angle = 4U;  // FAKE: the bound shares angle with the table value (one register)
    index = gActivePlayerState->recoilTimer - 0x14;
    if ((index >= 0) && ((u32) index < angle)) {
        angle = gWeaponRecoilAnglesBone4[index];
        slots[*count].weight = 0x7F;
        slots[*count].bone = 4;
        slots[*count].rotX = 0;
        slots[*count].rotY = angle;
        slots[*count].rotZ = 0;
        *count += 1;
    }
}



void playerWeaponCalculateTrajectory22(Actor *actor, BoneRotation *slots, s32 *count) {
    s32 tableIndex;
    u16 angle;

    angle = 0x16;  // FAKE: the base shares the angle register with the table value (Q0214)
    tableIndex = gActivePlayerState->recoilTimer - angle;
    if ((tableIndex >= 0) && ((u32)tableIndex < 4U)) {
        angle = gWeaponRecoilAnglesBone1[tableIndex];
        slots[*count].weight = 0x7F;
        slots[*count].bone = 1;
        slots[*count].rotX = 0;
        slots[*count].rotY = angle;
        slots[*count].rotZ = 0;
        *count += 1;
    }
}

void playerWeaponCalculateTrajectory23(Actor *actor, BoneRotation *slots, s32 *count) {
    u16 angle;

    angle = gWeaponRecoilAnglesBone1XY[gActivePlayerState->recoilTimer];
    slots[*count].weight = 0x7F;
    slots[*count].bone = 1;
    slots[*count].rotX = angle;
    slots[*count].rotY = angle;
    slots[*count].rotZ = 0;
    *count += 1;
}

void playerWeaponCalculateTrajectory24(f32 force, f32 damping, KongSpring *spring, f32 *angle) {
    s32 pad[1];
    f32 cosTilt;

    cosTilt = cosApprox(spring->angle);
    spring->velocity += force * cosApprox(*angle) * cosTilt;
    spring->velocity -= damping * sinApprox(spring->angle);
    spring->velocity *= 0.93;
    spring->angle += spring->velocity;
    *angle += spring->angle + spring->offset;
}

f32 playerWeaponCalculateTrajectory25(Actor *actor, KongChain *state, f32 scale) {
    f32 delta;
    f32 sway;

    sway = mathCosF((s16)(actor->yaw - actor->moveYaw)) * (actor->speedXZ * 0.0076923077f);
    delta = sway - state->sway;
    state->sway = sway;
    return (delta + sway) * scale;
}

s32 playerWeaponCalculateTrajectory26(Actor *actor, KongChain *state, s32 mode) {
    s32 ret = (actor->flags & 0x100) != 0;

    if (ret != 0) {
        ret = state->holdTimer == 0;
        if (ret != 0) {
            return mode == state->kind;
        }
    } // ORIG: no final return; the target falls through with ret in $v0 (0x1170 sltu v0 -> beqz v0, 0x1188 move v0,t8 in the beqz delay slot, then 0x1198 jr ra)
}

f32 mathAngleRadDeltaTurns(f32 *prevAngle, f32 angle) {
    f32 diff;

    diff = angle - *prevAngle;
    *prevAngle = angle;
    if (diff > 3.1415927f) {
        diff = 6.2831855f - diff;
    } else if (diff < -3.1415927f) {
        diff = -(6.2831855f + diff);
    }
    diff *= 0.15915494f;
    return diff;
}

// Per-type view: 0x178 is this actor type's second component pointer (see Actor).
typedef struct F56AActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ KongChain *weaponState;
} F56AActor;


void playerWeaponAimTarget(Actor *actor, BoneRotation *slots, s32 *count) {
    KongChain *state = ((F56AActor *) actor)->weaponState;
    KongChainNode *node;
    s32 pad5[1];
    f32 posB[3];
    f32 posA[3];
    s32 value = -0x80;
    f32 accel0 = 0.0f;
    f32 accel1 = 0.0f;
    f32 angle;
    s32 active;
    s32 index;
    s32 i;
    f32 ret;
    f32 angle0;
    f32 angle1;
    s32 kind;
    s32 pad4[2];

    node = state->nodes;
    active = playerWeaponCalculateTrajectory26(actor, state, 2);
    angle0 = 0.0f;
    angle1 = 0.0f;
    index = *count;
    kind = 0x14;
    actorGetNodePos(actor, 0xD, &posA[0], &posA[1], &posA[2]);
    actorGetNodePos(actor, 0xE, &posB[0], &posB[1], &posB[2]);
    angle = mathAtan2(posA[2] - posB[2], posA[0] - posB[0]);
    if (active == 0) {
        state->prevAngle = angle;
        state->prevY = posA[1];
        if ((state->holdTimer != 0) && (actor->flags & 0x100) && (state->kind == 2)) {
            state->holdTimer -= 1;
        }
    } else {
        ret = mathAngleRadDeltaTurns(&state->prevAngle, angle);
        state->weight += (-128.0f - state->weight) * 0.3;
        value = (s8) state->weight;
        accel1 = 0.4f * ret;
        accel0 = playerWeaponCalculateTrajectory25(actor, state, 0.02f);
    }
    for (i = 0; i != 4; i++) {
        if (active != 0) {
            playerWeaponCalculateTrajectory24(accel0, 0.06f, &node->springX, &angle0);
            playerWeaponCalculateTrajectory24(accel1, 0.06f, &node->springY, &angle1);
        }
        slots[index].weight = value;
        slots[index].bone = kind;
        slots[index].rotX = (s32) ((node->springX.angle + node->springX.offset) * 10430.218905280077);
        slots[index].rotY = 0;
        slots[index].rotZ = (s32) ((node->springY.angle + node->springY.offset) * 10430.218905280077);
        node++;
        index++;
        kind++;
    }
    *count = index;
}

extern s8 D_80752CBF[];

void playerWeaponSpawnProjectile(Actor *actor, BoneRotation *slots, s32 *count) {
    KongChain *state = ((F56AActor *) actor)->weaponState;
    KongChainNode *node;
    f32 target;
    f32 trajectory;
    s32 index;
    s32 kind;
    s8 value;
    s32 i;
    s32 k;
    f32 angle0;
    f32 angle1;
    f32 turnDelta;
    f32 angle;
    f32 pos[2][3];
    f32 turnSpeed;
    f32 velY;
    f32 accelY;
    KongChain *cur;
    s32 active;
    f32 boost;
    f32 accel0;
    f32 accel1;

    index = *count;
    turnDelta = 0;
    kind = 0x16;
    cur = state;
    active = playerWeaponCalculateTrajectory26(actor, state, 5);
    value = -0x80;
    actorGetNodePos(actor, 0xD, &pos[0][0], &pos[0][1], &pos[0][2]);
    actorGetNodePos(actor, 0xE, &pos[1][0], &pos[1][1], &pos[1][2]);
    angle = mathAtan2(pos[0][2] - pos[1][2], pos[0][0] - pos[1][0]);
    if (active == 0) {
        for (k = 0; k != 2; k++) {
            cur[k].prevAngle = angle;
            cur[k].prevY = pos[k][1];
        }
        if ((state->holdTimer != 0) && (actor->flags & 0x100) && (state->kind == 5)) {
            state->holdTimer -= 1;
        }
    } else {
        s16 idx = actor->sub4->model->animId;

        if (idx >= 0) {
            target = D_80752CBF[idx];
        } else {
            target = -128.0f;
        }
        state->weight += (target - state->weight) * 0.3;
        value = state->weight;
        turnDelta = mathAngleRadDeltaTurns(&state->prevAngle, angle);
        trajectory = playerWeaponCalculateTrajectory25(actor, state, 0.02f);
    }
    for (k = 0; k != 2; k++, cur++) {
        accel1 = 0.0f;
        accel0 = 0.0f;
        angle0 = 0.0f;
        angle1 = 0.0f;
        node = cur->nodes;
        if (active != 0) {
            velY = pos[k][1] - cur->prevY;
            accelY = velY - cur->prevVelY;
            cur->prevY = pos[k][1];
            cur->prevVelY = velY;
            boost = 0.4f * turnDelta;
            turnSpeed = (turnDelta > 0) ? turnDelta : -turnDelta;
            if (k != 0) {
                accel0 = -trajectory;
                accel1 = -((turnSpeed * 0.3f) + (-0.015f * accelY - 0.0008f * velY));
            } else {
                accel0 = trajectory;
                accel1 = (turnSpeed * 0.3f) + (-0.015f * accelY - 0.0008f * velY);
            }
            accel0 += boost;
        }
        for (i = 0; i != 8; i++) {
            if (active != 0) {
                playerWeaponCalculateTrajectory24(accel1, 0.06f, &node->springX, &angle0);
                playerWeaponCalculateTrajectory24(accel0, 0.06f, &node->springY, &angle1);
            }
            slots[index].weight = value;
            slots[index].bone = kind;
            slots[index].rotX = 0;
            slots[index].rotY = (s32) ((node->springY.angle + node->springY.offset) * 10430.218905280077);
            slots[index].rotZ = (s32) ((node->springX.angle + node->springX.offset) * 10430.218905280077);
            node++;
            index++;
            kind++;
        }
    }
    *count = index;
}

void kongChainUpdateDiddy(Actor *actor, BoneRotation *slots, s32 *count) {
    KongChain *state;
    KongChainNode *node;
    s32 index;
    s32 kind;
    s32 active;
    s32 i;
    s32 pad;
    f32 angle0;
    f32 angle1;
    f32 jitterScale;
    f32 gain;
    f32 forceX;
    f32 forceY;
    f32 damping;
    f32 yawDelta;
    f32 z;
    f32 y;
    f32 x;
    s8 value;
    f32 target;
    f32 accelY;
    f32 result;
    f64 pad2;

    state = ((F56AActor *) actor)->weaponState;
    index = *count;
    kind = 0x1A;
    node = state->nodes;
    angle1 = 0.0f;
    angle0 = 0.0f;
    forceX = 0.0f;
    forceY = 0.0f;
    jitterScale = 0.0003f;
    gain = 1.0f;
    damping = 0.06f;
    active = playerWeaponCalculateTrajectory26(actor, state, 3);
    value = -0x80;
    actorGetNodePos(actor, 5, &x, &y, &z);
    if (active == 0) {
        state->prevAngle = actor->yaw;
        state->prevY = y;
        D_80752F4C = 0.0f;
        if ((state->holdTimer != 0) && (actor->flags & 0x100) && (state->kind == 3)) {
            state->holdTimer -= 1;
        }
    } else {
        forceY = y - state->prevY;
        accelY = forceY - state->prevVelY;
        yawDelta = state->prevAngle - actor->yaw;
        if (actor->sub4->model->animId >= 0) {
            target = gDiddyChainAnimWeights[actor->sub4->model->animId - 0xA2];
        } else {
            target = -128.0f;
        }
        state->prevAngle = actor->yaw;
        state->weight = state->weight + (target - state->weight) * 0.3;
        value = state->weight;
        if (actor->state == 0x4F) {
            damping = 0.01f;
            jitterScale = 0.0001f;
            gain = 0.4f;
        }
        result = playerWeaponCalculateTrajectory25(actor, state, 0.011f);
        state->prevY = y;
        state->prevVelY = forceY;
        forceX = (-result - ((0.005f * accelY) + (0.0008f * forceY))) * gain;
        if ((32.0f + ((1.0f - gain) * 8.0f)) < (randomNonNegative() >> 15) % 40) {
            D_80752F4C = (0x14 - ((randomNonNegative() >> 15) % 40)) * jitterScale;
        }
        if (yawDelta > 2048.0f) {
            yawDelta = 4096.0f - yawDelta;
        } else if (yawDelta < -2048.0f) {
            yawDelta = -(4096.0f + yawDelta);
        }
        forceY = (1.0f - actor->speedXZ / 130.0f) * D_80752F4C + 2e-05 * yawDelta;
    }
    for (i = 0; i != 11; i++) {
        if (active != 0) {
            playerWeaponCalculateTrajectory24(forceX, damping, &node->springX, &angle0);
            playerWeaponCalculateTrajectory24(forceY, damping, &node->springY, &angle1);
        }
        slots[index].weight = value;
        slots[index].bone = kind;
        slots[index].rotX = (s32) ((node->springX.angle + node->springX.offset) * 10430.218905280077);
        slots[index].rotY = (s32) ((node->springY.angle + node->springY.offset) * 10430.218905280077);
        slots[index].rotZ = 0;
        node++;
        index++;
        kind++;
    }
    *count = index;
}

void playerWeaponCrosshairUpdate(Actor *actor, BoneRotation *slots, s32 *count) {
    f32 x;
    s16 delta;
    CamState *camState;
    f32 y;
    f32 planarAngle;
    camState = ((PlayerState *)actor->customState)->camActor->customState;
    delta = (camState->unkB2 - actor->yaw) - 0x800;
    x = gPlayerSlots[gCurrentPlayerIndex].camZ - gPlayerSlots[gCurrentPlayerIndex].focusZ;
    y = gPlayerSlots[gCurrentPlayerIndex].camX - gPlayerSlots[gCurrentPlayerIndex].focusX;
    planarAngle = mathAtan2(gPlayerSlots[gCurrentPlayerIndex].camY - gPlayerSlots[gCurrentPlayerIndex].focusY, sqrtf((x * x) + (y * y)));
    delta &= 0xFFF;
    if ((delta < 0xC00) && (delta >= 0x801)) {
        actor->yaw = (actor->yaw + delta) - 0xC00;
        delta = 0xC00;
    } else if ((delta >= 0x401) && (delta < 0x800)) {
        actor->yaw = (actor->yaw + delta) - 0x400;
        delta = 0x400;
    }
    slots[*count].weight = -128;
    slots[*count].bone = 2;
    slots[*count].rotY = (s16)(u32)((delta / 4095.0) * 65535.0);
    slots[*count].rotX = (s16)(u32)((planarAngle / 6.2831855f) * 65535.0);
    slots[*count].rotZ = 0;
    *count += 1;
}



void playerWeaponCrosshairRender(Actor *actor, BoneVector *entries, s32 *count) {
    f32 fade;
    f32 scaleY;
    f32 scaleX;
    s32 remaining;
    fade = gActivePlayerState->unk21E * 0.033333335f;
    if (fade < 1e-05) {
        fade = 1e-05f;
    }
    switch (actor->state) {
        case 0x34:
        case 0x84:
            if (gActivePlayerState->unk25C > 0.01) {
                gActivePlayerState->unk258 *= 1.07;
                gActivePlayerState->unk25C *= 0.7;
            } else {
                actor->flags &= ~0x8000;
                if (gActivePlayerState->unk21E != 0) {
                    gActivePlayerState->unk21E--;
                }
                actor->alpha = 255.0f * fade;
            }
            scaleX = gActivePlayerState->unk258;
            scaleY = gActivePlayerState->unk25C;
            break;
        default:
            scaleY = fade;
            scaleX = fade;
            if (gActivePlayerState->unk21E < 0x1E) {
                actor->flags |= 0x8000;
                remaining = 0x1E - gActivePlayerState->unk21E;
                gActivePlayerState->unk21E += (remaining >= 3) ? 2 : remaining;
                gActivePlayerState->unk258 = 1.0f;
                gActivePlayerState->unk25C = gActivePlayerState->unk258;
            }
            break;
    }
    entries[*count].bone = 0;
    entries[*count].lastBone = 0xFF;
    entries[*count].x = scaleX;
    entries[*count].y = scaleY;
    entries[*count].z = scaleX;
    *count += 1;
}

void playerWeaponUpdateHomingTarget(Actor *actor, BoneRotation *slots, s32 *count) {
    s32 index;
    s8 v;
    u16 angle;
    u16 yaw;
    u16 scaled;
    f32 amplitude;
    f32 sine;
    index = *count;
    if (actor->contactFlags & 1) {
        gActivePlayerState->homingStrength += 2;
        if (gActivePlayerState->homingStrength >= 0x80) gActivePlayerState->homingStrength = 0x7F;
    } else {
        gActivePlayerState->homingStrength -= 2;
        if (gActivePlayerState->homingStrength < 0) gActivePlayerState->homingStrength = 0;
    }
    if (gActivePlayerState->homingStrength != 0) {
        yaw = (actor->floorSlopeYaw - 0x800) & 0xFFF;
        scaled = (0x400 - actor->floorSlopePitch) & 0xFFF;
        if (scaled >= 0x156) scaled = 0x155;
        scaled = scaled * 0x10;
        angle = mathAngleSignedDistance(actor->yaw, yaw);
        amplitude = mathCosF(angle) * scaled;
        sine = mathSinF(angle);
        v = gActivePlayerState->homingStrength * 6 / 10;
        if (v != 0) {
            slots[index].bone = 1;
            slots[index].rotY = 0;
            slots[index].weight = v;
            slots[index].rotX = (s16)amplitude;
            slots[index].rotZ = (s16)(-sine * scaled);
            index += 1;
        }
        v = gActivePlayerState->homingStrength * 3 / 10;
        if (v != 0) {
            slots[index].bone = 2;
            slots[index].rotY = 0;
            slots[index].weight = v;
            slots[index].rotX = (s16)amplitude;
            slots[index].rotZ = (s16)(-sine * scaled);
            index += 1;
        }
    }
    *count = index;
}


void playerWeaponFireGun(Actor *actor, BoneVector *entries, s32 *count, u8 kind0, u8 kind1, f32 charge, f32 amplitude) {
    f32 angle;

    angle = mathSinF((s16)(charge * 2048.0f));
    entries[*count].bone = kind0;
    entries[*count].lastBone = kind1;
    entries[*count].x = 1.0f;
    entries[*count].y = (angle * amplitude) + 1.0;
    entries[*count].z = 1.0f;
    *count += 1;
}


void playerWeaponReload(Actor *actor, PlayerState *ps, u16 weapon) {
    u8 state0;
    u8 state2;
    u16 bone;
    s32 selector;
    s32 shouldSpawn;

    switch (weapon) {
    case 0:
        state0 = ps->recoilTimer;
        if (state0 != 0) {
            if ((state0 == 0x10) && (ps->recentShotCount < 4)) {
                ps->recentShotCount = 0;
                return;
            }
        } else if (ps->recentShotCount >= 4) {
            effectSpawnBoneWhite(actor, 0xA, 0.3f, 0.0f, 0.0f, 0.0f, -10);
        }
        break;
    case 1:
        selector = ps->recoilTimer;
        shouldSpawn = 0;
        if ((selector != 0) && (selector != 3)) {
            if ((selector == 0x10) && (ps->recentShotCount < 6)) {
                ps->recentShotCount = 0;
            }
        } else if (ps->recentShotCount >= 6) {
            shouldSpawn = 1;
        }
        if (shouldSpawn != 0) {
            if (ps->recoilTimer != 0) {
                bone = ps->gunHand + 9;
            } else {
                bone = ps->lastFireHand + 9;
            }
            effectSpawnBoneWhite(actor, bone, 0.2f, 0.0f, 0.0f, 0.0f, -10);
            return;
        }
        break;
    case 4:
    case 5:
        state2 = ps->recoilTimer;
        if (state2 != 0) {
            if ((state2 == 0x10) && (ps->recentShotCount < 3)) {
                ps->recentShotCount = 0;
                return;
            }
        } else if (ps->recentShotCount >= 3) {
            effectSpawnBoneWhite(actor, 0xA, 0.6f, 0.0f, 0.0f, 0.0f, -10);
        }
        break;
    }
}


extern u8 gWaypointFlags;

void playerWeaponSpawnMuzzleFlash(Actor *actor, u16 weapon) {
    PlayerState *ps;
    s32 slotCount;
    s32 entryCount;
    ActorSub4 *sub;
    BoneRotation *slots;
    BoneVector *entries;
    BoneVector *offsets;
    f32 charge;
    f32 t;
    f32 v;

    ps = actor->customState;
    if ((actor->state != 0x77) && (actor->flags & 4)) {
        sub = actor->sub4;
        slots = sub->boneRotations;
        entries = sub->boneScales;
        offsets = sub->boneOffsets;
        slotCount = 0;
        entryCount = 0;
        if ((mpIsMatchType(0) != 0) && ((ps->unk21E != 0x1E) || (actor->state == 0x34))) {
            playerWeaponCrosshairRender(actor, entries, &entryCount);
        }
        switch (weapon) {
        case 0:
            playerWeaponUpdateHomingTarget(actor, slots, &slotCount);
            playerWeaponAimTarget(actor, slots, &slotCount);
            if (ps->recoilTimer != 0) {
                playerWeaponCalculateTrajectory4(actor, slots, &slotCount);
            }
            break;
        case 1:
            switch (actor->state) {
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                break;
            case 2:
                playerWeaponCrosshairUpdate(actor, slots, &slotCount);
                break;
            default:
            case 3:
            case 4:
            case 5:
            case 6:
                playerWeaponUpdateHomingTarget(actor, slots, &slotCount);
                break;
            }
            kongChainUpdateDiddy(actor, slots, &slotCount);
            if (ps->recoilTimer != 0) {
                playerWeaponCalculateTrajectory7(actor, slots, &slotCount);
            }
            break;
        case 2:
            switch (actor->state) {
            case 0x26:
                if (actor->unk155 != 0) {
                    t = actor->sub4->model->frame;
                    if (t < 6.0f) {
                        v = 0.0f;
                    } else {
                        v = t - 6.0f;
                    }
                    charge = v / 17.0 > 1.0 ? 1.0 : v / 17.0;
                    playerWeaponFireGun(actor, entries, &entryCount, 0xA, 0xB, charge, gCurrentMap == 0xCD ? 17.0 : 2.5);
                }
                break;
            case 0x27: {
                t = actor->sub4->model->frame;
                if (t < 6.0f) {
                    v = 0.0f;
                } else {
                    v = t - 6.0f;
                }
                charge = v / 17.0 > 1.0 ? 1.0 : v / 17.0;
                playerWeaponFireGun(actor, entries, &entryCount, 5, 6, charge, gCurrentMap == 0xCD ? 17.0 : 2.5);
                break;
            }
            case 0x28: {
                t = actor->sub4->model->frame;
                if (t < 7.0f) {
                    v = 0.0f;
                } else {
                    v = t - 7.0f;
                }
                charge = v / 14.0 > 1.0 ? 1.0 : v / 14.0;
                playerWeaponFireGun(actor, entries, &entryCount, 9, 0xB, charge, 1.8f);
                playerWeaponFireGun(actor, entries, &entryCount, 4, 6, charge, 1.8f);
                break;
            }
            case 0x29: {
                t = actor->sub4->model->frame;
                if (t < 4.0f) {
                    v = 0.0f;
                } else {
                    v = t - 4.0f;
                }
                charge = v / 6.0 > 1.0 ? 1.0 : v / 6.0;
                playerWeaponFireGun(actor, entries, &entryCount, 9, 0xB, charge, 1.3f);
                playerWeaponFireGun(actor, entries, &entryCount, 4, 6, charge, 1.3f);
                break;
            }
            }
            break;
        case 3:
            playerWeaponSpawnProjectile(actor, slots, &slotCount);
            if (ps->recoilTimer != 0) {
                playerWeaponCalculateTrajectory23(actor, slots, &slotCount);
            }
            break;
        case 4:
        case 5:
            if (ps->recoilTimer != 0) {
                playerWeaponCalculateTrajectory22(actor, slots, &slotCount);
            }
            break;
        case 6:
            break;
        }
        slots[slotCount].weight = 0;
        entries[entryCount].bone = 0xFF;
        offsets->bone = 0xFF;
        if (ps->recoilTimer != 0) {
            ps->recoilTimer -= 1;
            if (ps->gunDrawn != 0) {
                playerWeaponReload(actor, ps, weapon);
            }
        }
        if (ps->recoilTimer == 0) {
            ps->recentShotCount = 0;
        }
    }
}



void playerWaypointPathsLoad(s16 pathsId) {
    void *buffer;

    buffer = assetLoad(0x15, pathsId, 1, 0);
    playerWaypointPathsParse(buffer);
    if (buffer != NULL) {
        assetFreeBuffer(buffer, 0x4C, 0x56);
    }
}

typedef struct WaypointNode {
    s16 x;
    s16 y;
    s16 z;
    u8 timer0;
    u8 timer1;
    u8 timer2;
    u8 speed;
    s16 timer3;
    s16 timer4;
    s16 timer5;
    s16 delay;
} WaypointNode;

void actorSetPositionAndFacingAngle(Actor *actor, WaypointNode *node) {
    s16 angle;

    actorClearMovementFlags(actor);
    actor->x = node->x;
    actor->y = node->y;
    actor->z = node->z;
    angle = mathAngleBetweenPoints2D(node[1].x, node[1].z, node->x, node->z);
    actor->moveYaw = angle;
    actor->yaw = angle;
}

typedef struct WaypointPath {
    s16 count;
    u8 pad2[2];
    WaypointNode *nodes;
} WaypointPath;

typedef struct WaypointPathTable {
    s16 count;
    u8 pad2[2];
    WaypointPath *paths;
} WaypointPathTable;

extern s8 gDemoPlaybackState;
extern u8 gScreenRenderFlags;
extern WaypointPath *gWaypointPathEntry;
extern WaypointNode *gWaypointCursor;
extern Actor *gWaypointActor;
extern s16 gWaypointIndex;
extern s16 gWaypointCallbackId;
extern void *gWaypointCallbackParam;

void playerWaypointPathStart(u8 pathIndex, Actor *actor, void *callbackParam, s16 callbackId, u8 skipPlace) {
    PlayerState *ps;

    ps = actor->customState;
    if (gWaypointPaths->count >= pathIndex) {
        gDemoPlaybackState = 3;
        gScreenRenderFlags |= 0x10;
        gWaypointActor = actor;
        ps->stateFlags &= ~1;
        gWaypointIndex = 0;
        gWaypointPathEntry = gWaypointPaths->paths + pathIndex;
        gWaypointCursor = gWaypointPathEntry->nodes;
        gWaypointCallbackId = callbackId;
        gWaypointCallbackParam = callbackParam;
        if (skipPlace == 0) {
            actorSetPositionAndFacingAngle(actor, gWaypointCursor);
        }
    }
}


typedef struct F5DDeferredEntry {
    s16 count;
    u8 pad2[2];
    void *data;
} F5DDeferredEntry;


void deferredEntryFree(F5DDeferredEntry *entry) {
    heapFreeDeferred(entry->data);
    entry->count = 0;
}



void playerWaypointPathStartPacked(Actor *actor, void *callbackParam, s16 packedPath, s16 callbackId) {
    s32 skipPlace;

    if (packedPath & 0x8000) {
        skipPlace = 1;
    } else {
        skipPlace = 0;
    }
    packedPath &= 0x7FFF;
    playerWaypointPathStart(packedPath, actor, callbackParam, callbackId, skipPlace);
    gWaypointFlags = 0;
}



void playerWaypointPathStartLineFromPoint(Actor *actor, G01Pos *spawn, u8 length) {
    WaypointNode *p;
    WaypointNode *q;
    WaypointPath *entry;

    entry = &gWaypointPaths->paths[gWaypointPaths->count];
    entry->count = 2;
    entry->nodes = heapAlloc(2 * sizeof(WaypointNode));
    heapClearBlock(entry->nodes);
    q = entry->nodes + 1;
    p = entry->nodes;
    p->x = spawn->x;
    p->y = spawn->y;
    p->z = spawn->z;
    p->speed = 0x32;
    q->x = mathSinF((s16)((spawn->yaw / 255.0) * 4095.0)) * length + spawn->x;
    q->y = spawn->y;
    q->z = mathCosF((s16)((spawn->yaw / 255.0) * 4095.0)) * length + spawn->z;
    q->speed = 0x32;
    playerWaypointPathStart(gWaypointPaths->count, actor, NULL, 0, 0);
    gWaypointFlags = 0;
    gGlobalPauseFlags |= 0x400;
}


void playerWaypointPathStartLineFromActor(Actor *actor, s16 targetX, s16 targetZ, u8 length) {
    WaypointNode *p;
    s16 angle;
    WaypointNode *q;
    WaypointPath *entry;

    angle = mathAngleBetweenPoints2D(targetX, targetZ, actor->x, actor->z);
    entry = &gWaypointPaths->paths[gWaypointPaths->count];
    if (actor->state != 0x44) {
        entry->count = 2;
        entry->nodes = heapAlloc(2 * sizeof(WaypointNode));
        heapClearBlock(entry->nodes);
        q = entry->nodes + 1;
        p = entry->nodes;
        p->x = actor->x;
        p->y = actor->y;
        p->z = actor->z;
        p->speed = 0x28;
        q->x = mathSinF(angle) * length + actor->x;
        q->y = actor->y;
        q->z = mathCosF(angle) * length + actor->z;
        q->speed = 0x28;
        playerWaypointPathStart(gWaypointPaths->count, actor, NULL, 0, 0);
        gWaypointFlags = 0;
        gGlobalPauseFlags |= 0x400;
    }
}


void playerWaypointSnapInput(void) {
    gWaypointFlags |= 2;
}

void timerDecrementOrSetFlag(u16 *flags, s16 *timer, u8 *count, u16 bit) {
    if (*timer != 0) {
        (*timer)--;
        return;
    }
    if (*count != 0) {
        (*count)--;
        *flags |= bit;
    }
}


#define WAYPOINT_MAX(a, b) ((a) > (b) ? (a) : (b))
#define WAYPOINT_MIN(a, b) ((a) < (b) ? (a) : (b))
#define WAYPOINT_CLAMP_S8(x) WAYPOINT_MIN(WAYPOINT_MAX(x, -128.0f), 127.0f)

extern u8 gGameMode;
extern u8 gLetterboxRetractTimer;

void playerStateWaypointAimUpdate(OSContPad *control, OSContPad *unused) {
    PlayerState *tgt;
    f32 ang;
    f32 camAng;
    f32 pitch;
    WaypointNode *cur;
    WaypointNode *next;
    f32 blend;
    f32 speed;
    s16 yawT;
    s32 eq;
    u8 close;
    s32 starting;
    s16 pitchT;

    cur = gWaypointCursor;
    tgt = gWaypointActor->customState;
    blend = 0.2f;
    next = gWaypointCursor + 1;
    speed = (u32)cur->speed * 0.7;
    close = (gWaypointActor->x - next->x) * (gWaypointActor->x - next->x) + (gWaypointActor->z - next->z) * (gWaypointActor->z - next->z) < 100.0f;
    starting = !gWaypointFlags;
    if (starting & 1) {  // ORIG: target masks the 0/1 flag again (andi t4,a1,0x1 at 0x3504)
        gWaypointFlags |= 1;
        control->stick_x = 0;
        control->stick_y = 0;
    }
    if (close) {
        eq = gWaypointIndex + 2 == gWaypointPathEntry->count;
        if (eq) {
            if (gWaypointIndex && gWaypointIndex) {}  // FAKE: same-value read keeps the gWaypointIndex load live into this arm, so it outranks eq for $v0
            gDemoPlaybackState = 0;
            if (gGameMode == 0) {
                gScreenRenderFlags &= 0xFFEF;
                gLetterboxRetractTimer = 0xFF;
            }
            if (gWaypointCallbackId != 0) {
                playerStateQueueCallback(gWaypointCallbackId, gWaypointCallbackParam, 0);
            }
            tgt->stateFlags |= 1;
            gGlobalPauseFlags &= ~0x400;
            playerInitMoveParams();
        } else {
            gWaypointIndex++;
            gWaypointCursor++;
            cur = gWaypointCursor;
            next = cur + 1;
        }
    }
    control->button = 0;
    timerDecrementOrSetFlag(&control->button, &cur->timer3, &cur->timer0, 0x8000);
    timerDecrementOrSetFlag(&control->button, &cur->timer4, &cur->timer1, 0x4000);
    timerDecrementOrSetFlag(&control->button, &cur->timer5, &cur->timer2, 0x2000);
    pitchT = 0;
    if (cur->delay != 0) {
        cur->delay--;
        yawT = 0;
    } else {
        if (gWaypointFlags & 2) {
            blend = 1.0f;
            gWaypointFlags &= 0xFFFD;
        }
        if (gWaypointActor->state == 0x4F) {
            ang = mathAngleBetweenPointsDeg(next->x, next->z, gWaypointActor->x, gWaypointActor->z) * 0.017453292f - (gWaypointActor->yaw * 3.1415927f) * 0.00048828125;
            pitch = mathCalculatePitchAngle(next->x, next->y, next->z, gWaypointActor->x, gWaypointActor->y, gWaypointActor->z, 0);
            control->button |= 0x4000;
            yawT = ang;
            pitchT = WAYPOINT_CLAMP_S8(sinApprox(pitch) * speed);
        } else {
            camAng = mathAngleBetweenPointsDeg(gPlayerSlots->focusX, gPlayerSlots->focusZ, gPlayerSlots->camX, gPlayerSlots->camZ);
            ang = mathAngleBetweenPointsDeg(next->x, next->z, gWaypointActor->x, gWaypointActor->z) * 0.017453292f - camAng * 0.017453292f;
            yawT = WAYPOINT_CLAMP_S8(sinApprox(ang) * speed);
            pitchT = WAYPOINT_CLAMP_S8(cosApprox(ang) * speed);
        }
    }
    control->stick_x += (yawT - control->stick_x) * blend;
    control->stick_y += (pitchT - control->stick_y) * blend;
}

void playerWaypointPathsParse(void *data) {
    u8 *next;
    WaypointNode *destination;
    u8 *source;
    WaypointPath *entry;
    s16 outer;
    s16 inner;

    if (data != NULL) {
        gWaypointPaths->count = *(s16 *)data;
        source = (u8 *)data + 2;
        gWaypointPaths->paths = heapAlloc((gWaypointPaths->count + 1) * sizeof(WaypointPath));
        entry = gWaypointPaths->paths;
        for (outer = 0; outer < gWaypointPaths->count; outer++) {
            entry->count = *(s16 *)source;
            next = source + 2;
            for (inner = 0; inner < entry->count; inner++) {
                if (inner == 0) {
                    entry->nodes = heapAlloc(entry->count * sizeof(WaypointNode));
                    destination = entry->nodes;
                } else {
                    destination++;
                }
                *destination = *(WaypointNode *)next;
                next += sizeof(WaypointNode);
            }
            source = next;
            entry++;
        }
    } else {
        gWaypointPaths->count = 0;
    }
}

