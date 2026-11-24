#include "common.h"
#include "compiler/ido/memory.h"

#include "actor.h"
#include "sched.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2F550_map_render.h"
#include "proto/global/42630_cutscene_interp.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7AF60_hit_conditions.h"
#include "proto/global/7BBD0_actor_collision.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/80150_barrels.h"
#include "proto/global/89250_effect_spawn.h"
#include "proto/global/8F4B0.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/9BF30_projectile_ring.h"
#include "proto/global/9CE20_projectile_behaviours.h"
#include "proto/global/9DD70.h"
#include "proto/global/A2F10.h"
#include "proto/global/A6280.h"
#include "proto/global/A7710_countdown_timer.h"
#include "proto/global/A8400_text_box.h"
#include "proto/global/AA960_pickup_drops.h"
#include "proto/global/ACDC0_pause_menu.h"
#include "proto/global/B1F60_enemy_patrol.h"
#include "proto/global/B2CE0_enemy_attack.h"
#include "proto/global/B5EC0_kong_item_enemy.h"
#include "proto/global/B6C50_smoke_target.h"
#include "proto/global/B7490_enemy_swim_fly.h"
#include "proto/global/BA790_enemy_chaser.h"
#include "proto/global/BB300_enemy_pulse.h"
#include "proto/global/BC3B0_cursor_emitters.h"
#include "proto/global/BD820_delivery_door.h"
#include "proto/global/BDEE0_armadillo_fairy.h"
#include "proto/global/C0EE0_enemy_grid.h"
#include "proto/global/C1E70_rings.h"
#include "proto/global/C2A90.h"
#include "proto/global/C4620_npc_kongs.h"
#include "proto/global/C8C10.h"
#include "proto/global/CB230_spotlight_follower.h"
#include "proto/global/CBEA0_banner_text.h"
#include "proto/global/CEAE0_player_update.h"

// This TU's .data (0x8074AC10-0x8074DA2C + 4-byte TU pad), in address order: the per-actor-type
// tables, defined between 7A510's data (ends with a 4-byte TU pad at 0x8074AC0C) and 7CA80's
// (starts 16-aligned at 0x8074DA30 after gActorTypeInitIndex's 4-byte TU pad). The tentative owner is
// 7BBD0: 7AF60 and 7BA00 sit between 7A510 and 7CA80 too, and none of these lists' pointers reaches a
// 7BBD0 function.

// Collision interaction lists and pattern tables reached through gActorTypeCollisionTables (the unlabelled ones are
// reached only through other unreferenced tables).
CollisionInteractionEntry D_8074AC10[1] = { { -1, -1, NULL, 9, 5, 0 } };
CollisionInteractionEntry D_8074AC1C[1] = { { -1, -1, NULL, 1, 0, 0 } };
CollisionInteractionEntry D_8074AC28[1] = { { -1, -1, NULL, 1, 5, 0 } };
CollisionInteractionEntry D_8074AC34[1] = { { -1, -1, NULL, 9, 0, 0 } };
CollisionInteractionEntry D_8074AC40[1] = { { -1, -1, NULL, 4, 5, 0 } };
CollisionInteractionEntry D_8074AC4C[1] = { { -1, -1, NULL, 1, 0, 0 } };
CollisionInteractionEntry D_8074AC58[6] = {
    { -2789, -1, (CollisionFilterFn)actorCheckPlayerSmallerThanAttacker, 6, 2, 2 },
    { -1, 128, (CollisionFilterFn)actorIsTargetAbovePitchThreshold, 6, 3, 2 },
    { -1, 132, (CollisionFilterFn)actorIsBelowTargetStationary, 1, 3, 2 },
    { -1, 2912, (CollisionFilterFn)actorIsFacingTarget, 6, 2, 2 },
    { -1, -1, (CollisionFilterFn)actorHitTargetNode5, 1, 5, 2 },
    { -1, -1, NULL, 1, 2, 0 },
};
CollisionInteractionEntry D_8074ACA0[1] = { { -1, -1, NULL, 9, 5, 0 } };
CollisionInteractionEntry D_8074ACAC[1] = { { -1, -1, NULL, 10, 5, 0 } };
CollisionInteractionEntry D_8074ACB8[4] = {
    { -3813, -1, (CollisionFilterFn)actorCheckPlayerSmallerThanAttacker, 6, 2, 2 },
    { -1, -1, (CollisionFilterFn)playerIsGiantLandingOnEnemy, 1, 13, 2 },
    { -1, -1, (CollisionFilterFn)playerIsGiantGroundedAgainstEnemy, 1, 5, 1 },
    { -1, -1, NULL, 1, 2, 0 },
};
CollisionInteractionEntry D_8074ACE8[1] = { { -1, -1, NULL, 1, 2, 0 } };
CollisionTableEntry D_8074ACF4[15] = {
    { -1, D_8074AC58 }, { 108, D_8074AC1C }, { 263, D_8074AC34 }, { 99, D_8074ACAC },
    { 44, D_8074AC1C }, { -3, D_8074ACA0 }, { 246, D_8074AC1C }, { -2, D_8074ACB8 },
    { 293, D_8074AC1C }, { 294, D_8074AC1C }, { 295, D_8074AC1C }, { -8, D_8074ACE8 },
    { 319, D_8074AC1C }, { 307, D_8074AC1C }, { 0, D_8074AC4C },
};
CollisionInteractionEntry D_8074AD6C[1] = { { -1, -1, NULL, 4, 0, 0 } };
CollisionTableEntry D_8074AD78[2] = { { -1, D_8074AD6C }, { 0, NULL } };
CollisionInteractionEntry D_8074AD88[1] = { { -1, -1, NULL, 4, 0, 0 } };
CollisionTableEntry D_8074AD94[2] = { { -3, D_8074AD88 }, { 0, NULL } };
CollisionTableEntry D_8074ADA4[2] = { { -1, D_8074AC34 }, { 0, NULL } };
CollisionInteractionEntry D_8074ADB4[4] = {
    { 1, -1, (CollisionFilterFn)actorHitTargetNode1, 4, 0, 2 },
    { 2, -1, (CollisionFilterFn)actorHitTargetNode2, 4, 0, 2 },
    { 4, -1, (CollisionFilterFn)actorHitTargetNode3, 4, 0, 2 },
    { -1, -1, NULL, 1, 0, 0 },
};
CollisionTableEntry D_8074ADE4[3] = { { -1, D_8074ADB4 }, { 252, D_8074AC1C }, { 0, NULL } };
CollisionInteractionEntry D_8074ADFC[2] = {
    { -1, -1, (CollisionFilterFn)actorHitTargetNode1, 9, 15, 2 },
    { -1, -1, NULL, 1, 0, 0 },
};
CollisionTableEntry D_8074AE14[2] = { { -1, D_8074ADFC }, { 0, NULL } };
CollisionInteractionEntry D_8074AE24[1] = { { -1, -1, (CollisionFilterFn)actorHitTargetNode1, 1, 0, 0 } };
CollisionInteractionEntry D_8074AE30[2] = {
    { -1, -1, (CollisionFilterFn)actorHitTargetNode1, 9, 5, 2 },
    { -1, -1, NULL, 1, 0, 0 },
};
CollisionTableEntry D_8074AE48[3] = { { 319, D_8074AE24 }, { -1, D_8074AE30 }, { 0, NULL } };
CollisionInteractionEntry D_8074AE60[2] = {
    { 2, -1, NULL, 1, 0, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionTableEntry D_8074AE78[2] = { { -1, D_8074AE60 }, { 0, NULL } };
CollisionInteractionEntry D_8074AE88[1] = { { -1, -1, NULL, 1, 5, 0 } };
CollisionInteractionEntry D_8074AE94[1] = { { -1, -1, NULL, 9, 5, 0 } };
CollisionInteractionEntry D_8074AEA0[1] = { { -1, -1, NULL, 1, 5, 0 } };
CollisionTableEntry D_8074AEAC[6] = {
    { -1, D_8074AEA0 }, { 186, D_8074AE88 }, { 327, D_8074AE94 }, { 328, D_8074AE94 },
    { 331, D_8074AE94 }, { 0, NULL },
};
CollisionInteractionEntry D_8074AEDC[2] = {
    { -1, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 1, 1 },
    { -1, -1, (CollisionFilterFn)actorCheckPlayerProximityVertical, 1, 9, 0 },
};
CollisionInteractionEntry D_8074AEF4[1] = { { -1, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 2, 0 } };
CollisionInteractionEntry D_8074AF00[2] = {
    { -1, 2, (CollisionFilterFn)actorHitTargetNode2, 9, 0, 2 },
    { -1, -1, (CollisionFilterFn)actorHitTargetNode2, 9, 5, 0 },
};
CollisionInteractionEntry D_8074AF18[2] = {
    { -1, -1, (CollisionFilterFn)actorHitTargetNode3, 9, 0, 2 },
    { -1, -1, NULL, 9, 5, 0 },
};
CollisionInteractionEntry D_8074AF30[1] = { { -1, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 1, 0 } };
CollisionTableEntry D_8074AF3C[5] = {
    { -1, D_8074AEDC }, { 19, D_8074AEF4 }, { 26, D_8074AEF4 }, { 21, D_8074AEF4 },
    { 0, NULL },
};
CollisionTableEntry D_8074AF64[6] = {
    { 6, D_8074AEDC }, { -1, D_8074AF30 }, { 19, D_8074AEF4 }, { 26, D_8074AEF4 },
    { 21, D_8074AEF4 }, { 0, NULL },
};
CollisionTableEntry D_8074AF94[9] = {
    { -1, D_8074AEDC }, { 19, D_8074AEF4 }, { 26, D_8074AEF4 }, { 263, D_8074AC34 },
    { -3, D_8074AF00 }, { 21, D_8074AEF4 }, { 185, D_8074AC34 }, { 236, D_8074AF18 },
    { 0, NULL },
};
CollisionInteractionEntry D_8074AFDC[3] = {
    { -1, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 2, 1 },
    { 2, -1, (CollisionFilterFn)actorGiantKongInReach, 1, 9, 2 },
    { 1, -1, (CollisionFilterFn)actorCheckPlayerProximityVertical, 1, 9, 0 },
};
CollisionInteractionEntry D_8074B000[1] = { { -1, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 2, 0 } };
CollisionTableEntry D_8074B00C[4] = {
    { 6, D_8074AFDC }, { -1, D_8074B000 }, { -3, D_8074AC28 }, { 0, NULL },
};
CollisionInteractionEntry D_8074B02C[2] = {
    { -1, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 1, 1 },
    { -1, -1, (CollisionFilterFn)actorCheckPlayerProximityVertical, 1, 9, 0 },
};
CollisionInteractionEntry D_8074B044[1] = { { -1, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 1, 0 } };
CollisionTableEntry D_8074B050[3] = { { 6, D_8074B02C }, { -1, D_8074B044 }, { 0, NULL } };
CollisionInteractionEntry D_8074B068[2] = {
    { -1, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 2, 1 },
    { -1, -1, (CollisionFilterFn)actorCheckPlayerProximityVertical, 1, 9, 0 },
};
CollisionInteractionEntry D_8074B080[1] = { { -1, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 2, 0 } };
CollisionTableEntry D_8074B08C[3] = { { 6, D_8074B068 }, { -1, D_8074B080 }, { 0, NULL } };
CollisionInteractionEntry D_8074B0A4[2] = {
    { 1, -1, NULL, 1, 2, 2 },
    { 2, -1, (CollisionFilterFn)actorListHasId2TargetVulnerable, 4, 6, 0 },
};
CollisionInteractionEntry D_8074B0BC[2] = {
    { 1, -1, (CollisionFilterFn)actorHitTargetNode2, 5, 5, 1 },
    { 1, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 14, 0 },
};
CollisionTableEntry D_8074B0D4[3] = { { -1, D_8074B0A4 }, { 67, D_8074B0BC }, { 0, NULL } };
CollisionInteractionEntry D_8074B0EC[2] = {
    { 1, -1, NULL, 4, 6, 2 },
    { 2, -1, NULL, 4, 7, 0 },
};
CollisionTableEntry D_8074B104[2] = { { 2, D_8074B0EC }, { 0, NULL } };
CollisionInteractionEntry D_8074B114[3] = {
    { -1, -1, (CollisionFilterFn)actorTargetIsGiantKong, 1, 2, 2 },
    { -1, -1, (CollisionFilterFn)actorTargetIsMiniKong, 1, 2, 2 },
    { -1, -1, (CollisionFilterFn)actorTargetIsVulnerable, 4, 6, 0 },
};
CollisionTableEntry D_8074B138[3] = { { -1, D_8074B114 }, { -3, D_8074AC28 }, { 0, NULL } };
CollisionInteractionEntry D_8074B150[2] = {
    { 1, -1, (CollisionFilterFn)actorTargetIsVulnerable, 4, 6, 2 },
    { 2, -1, NULL, 1, 0, 0 },
};
CollisionTableEntry D_8074B168[2] = { { -1, D_8074B150 }, { 0, NULL } };
CollisionInteractionEntry D_8074B178[2] = {
    { 1, -1, (CollisionFilterFn)actorTargetIsVulnerable, 4, 6, 2 },
    { 2, -1, NULL, 1, 0, 0 },
};
CollisionTableEntry D_8074B190[2] = { { 6, D_8074B178 }, { 0, NULL } };
CollisionTableEntry D_8074B1A0[2] = { { 5, D_8074B178 }, { 0, NULL } };
CollisionTableEntry D_8074B1B0[2] = { { 3, D_8074B178 }, { 0, NULL } };
CollisionTableEntry D_8074B1C0[2] = { { 4, D_8074B178 }, { 0, NULL } };
CollisionTableEntry D_8074B1D0[2] = { { 2, D_8074B178 }, { 0, NULL } };
CollisionInteractionEntry D_8074B1E0[3] = {
    { 1, -1, (CollisionFilterFn)actorTargetIsVulnerable, 4, 6, 2 },
    { 2, -1, NULL, 1, 2, 2 },
    { 4, -1, NULL, 1, 0, 0 },
};
CollisionTableEntry D_8074B204[2] = { { -1, D_8074B1E0 }, { 0, NULL } };
CollisionTableEntry D_8074B214[1] = { { 0, NULL } };
CollisionInteractionEntry D_8074B21C[3] = {
    { 1, 72, NULL, 4, 0, 2 },
    { 2, -1, (CollisionFilterFn)actorHitTargetNode1GroundPound, 9, 3, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionTableEntry D_8074B240[5] = {
    { -1, D_8074B21C }, { 26, D_8074AC28 }, { 19, D_8074AC28 }, { -3, D_8074AC28 },
    { 0, NULL },
};
CollisionTableEntry D_8074B268[2] = { { -1, D_8074AC28 }, { 0, NULL } };
CollisionInteractionEntry D_8074B278[2] = {
    { 2, -1, NULL, 1, 5, 2 },
    { -1, -1, NULL, 1, 2, 0 },
};
CollisionTableEntry D_8074B290[2] = { { -1, D_8074B278 }, { 0, NULL } };
CollisionInteractionEntry D_8074B2A0[8] = {
    { 1, 4, (CollisionFilterFn)actorIsTargetFallingFromAbove, 6, 3, 2 },
    { 1, 2560, (CollisionFilterFn)actorIsFacingTarget, 6, 0, 2 },
    { -1, 1024, NULL, 9, 0, 2 },
    { 1, 488, NULL, 6, 8, 2 },
    { 1, 16, NULL, 6, 10, 2 },
    { 2, -1, NULL, 1, 2, 2 },
    { -1, -1, (CollisionFilterFn)actorCheckTargetOnSurfaceOrSmaller, 1, 2, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionInteractionEntry D_8074B300[4] = {
    { 4, -1, NULL, 1, 5, 2 },
    { 8, -1, (CollisionFilterFn)actorHitTargetNode3, 6, 5, 2 },
    { 8, -1, NULL, 1, 5, 2 },
    { -1, -1, NULL, 6, 5, 0 },
};
CollisionTableEntry D_8074B330[5] = {
    { -1, D_8074B2A0 }, { 26, D_8074AC10 }, { 19, D_8074AC10 }, { -3, D_8074B300 },
    { 0, NULL },
};
CollisionInteractionEntry D_8074B358[1] = { { -1, -1, NULL, 1, 1, 0 } };
CollisionTableEntry D_8074B364[3] = { { -1, D_8074B2A0 }, { 115, D_8074AC1C }, { 0, NULL } };
CollisionTableEntry D_8074B37C[3] = { { -1, D_8074AC28 }, { -3, D_8074AC28 }, { 0, NULL } };
CollisionInteractionEntry D_8074B394[1] = { { -1, -1, NULL, 1, 2, 0 } };
CollisionInteractionEntry D_8074B3A0[2] = {
    { -1, 132, (CollisionFilterFn)actorIsTargetFallingFromAbove, 1, 3, 2 },
    { -1, -1, NULL, 1, 2, 0 },
};
CollisionTableEntry D_8074B3B8[3] = { { -1, D_8074B394 }, { -3, D_8074AC28 }, { 0, NULL } };
CollisionTableEntry D_8074B3D0[3] = { { -1, D_8074B3A0 }, { -3, D_8074AC28 }, { 0, NULL } };
CollisionTableEntry D_8074B3E8[2] = { { -1, D_8074B394 }, { 0, NULL } };
CollisionInteractionEntry D_8074B3F8[2] = {
    { 2, -1, NULL, 1, 5, 2 },
    { -1, -1, NULL, 2, 2, 0 },
};
CollisionTableEntry D_8074B410[3] = { { -1, D_8074B3F8 }, { -3, D_8074B300 }, { 0, NULL } };
CollisionTableEntry D_8074B428[4] = {
    { -1, D_8074B394 }, { -3, D_8074B300 }, { 273, D_8074B300 }, { 0, NULL },
};
CollisionInteractionEntry D_8074B448[7] = {
    { -1, 4, (CollisionFilterFn)actorIsTargetFallingFromAbove, 6, 3, 2 },
    { -1, 8, NULL, 6, 8, 2 },
    { -1, 1024, NULL, 9, 0, 2 },
    { -1, 2560, (CollisionFilterFn)actorIsFacingTarget, 6, 2, 2 },
    { -1, 488, NULL, 6, 8, 2 },
    { -1, -1, (CollisionFilterFn)actorCheckTargetOnSurfaceOrSmaller, 1, 2, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionInteractionEntry D_8074B49C[1] = { { -1, -1, NULL, 4, 5, 0 } };
CollisionInteractionEntry D_8074B4A8[2] = {
    { -1, -1, (CollisionFilterFn)actorCheckTargetOnSurfaceOrSmaller, 1, 2, 2 },
    { -1, -1, NULL, 4, 5, 0 },
};
CollisionTableEntry D_8074B4C0[5] = {
    { -1, D_8074B448 }, { 26, D_8074AC10 }, { 19, D_8074AC10 }, { -3, D_8074B300 },
    { 0, NULL },
};
CollisionTableEntry D_8074B4E8[10] = {
    { -1, D_8074B4A8 }, { 48, D_8074AC10 }, { 43, D_8074AC10 }, { 42, D_8074AC10 },
    { 36, D_8074AC10 }, { 38, D_8074AC10 }, { 41, D_8074AC10 }, { 171, D_8074AC10 },
    { 26, D_8074AC10 }, { 0, NULL },
};
CollisionTableEntry D_8074B538[6] = {
    { -1, D_8074B4A8 }, { 41, D_8074AC10 }, { 171, D_8074AC10 }, { 26, D_8074AC10 },
    { -3, D_8074B49C }, { 0, NULL },
};
CollisionInteractionEntry D_8074B568[8] = {
    { -1, 4, (CollisionFilterFn)actorIsTargetFallingFromAbove, 5, 3, 2 },
    { -1, 32, NULL, 4, 2, 2 },
    { -1, 1024, NULL, 9, 2, 2 },
    { -1, 2560, (CollisionFilterFn)actorIsFacingTarget, 4, 2, 2 },
    { -1, 128, (CollisionFilterFn)actorIsTargetAbovePitchThreshold, 4, 2, 2 },
    { -1, 328, (CollisionFilterFn)actorIsFacingTarget, 5, 2, 2 },
    { 2, -1, (CollisionFilterFn)actorHitTargetNode1, 1, 12, 2 },
    { -1, -1, NULL, 2, 2, 0 },
};
CollisionTableEntry D_8074B5C8[7] = {
    { -1, D_8074B568 }, { 41, D_8074B300 }, { 171, D_8074B300 }, { 26, D_8074AC10 },
    { -3, D_8074AC40 }, { 252, D_8074AC34 }, { 0, NULL },
};
CollisionInteractionEntry D_8074B600[11] = {
    { 1, 2560, (CollisionFilterFn)actorIsFacingTarget, 6, 2, 2 },
    { 1, 128, (CollisionFilterFn)actorIsTargetAbovePitchThreshold, 6, 2, 2 },
    { 1, 4, (CollisionFilterFn)actorIsTargetFallingFromAbove, 6, 3, 2 },
    { 1, 1056, NULL, 6, 2, 2 },
    { 1, 2888, (CollisionFilterFn)actorIsFacingTarget, 6, 2, 2 },
    { 2, -1, NULL, 2, 2, 2 },
    { 4, -1, NULL, 1, 5, 2 },
    { 8, 3680, NULL, 4, 2, 2 },
    { 8, -1, NULL, 2, 2, 2 },
    { -1, -1, (CollisionFilterFn)actorCheckTargetOnSurfaceOrSmaller, 1, 2, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionInteractionEntry D_8074B684[2] = {
    { 1, -1, NULL, 6, 5, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionInteractionEntry D_8074B69C[2] = {
    { 1, -1, NULL, 9, 5, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionTableEntry D_8074B6B4[6] = {
    { -1, D_8074B600 }, { -8, D_8074AC1C }, { 26, D_8074B69C }, { 19, D_8074B69C },
    { -3, D_8074B684 }, { 0, NULL },
};
CollisionInteractionEntry D_8074B6E4[2] = {
    { 1, -1, NULL, 6, 5, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionTableEntry D_8074B6FC[6] = {
    { -1, D_8074AC28 }, { 41, D_8074B6E4 }, { 171, D_8074B6E4 }, { 26, D_8074AC10 },
    { -3, D_8074B49C }, { 0, NULL },
};
CollisionInteractionEntry D_8074B72C[2] = {
    { 2, -1, (CollisionFilterFn)actorHitTargetNode2, 4, 1, 2 },
    { -1, -1, NULL, 1, 1, 0 },
};
CollisionTableEntry D_8074B744[3] = { { -1, D_8074B72C }, { -3, D_8074B49C }, { 0, NULL } };
CollisionInteractionEntry D_8074B75C[9] = {
    { -1, 4, (CollisionFilterFn)actorIsTargetFallingFromAbove, 7, 3, 2 },
    { -1, 1056, NULL, 6, 2, 2 },
    { -1, 2560, (CollisionFilterFn)actorIsFacingTarget, 6, 2, 2 },
    { -1, 128, (CollisionFilterFn)actorIsTargetAbovePitchThreshold, 6, 2, 2 },
    { -1, 328, (CollisionFilterFn)actorIsFacingTarget, 7, 2, 2 },
    { -1, 16, NULL, 6, 10, 2 },
    { 2, -1, (CollisionFilterFn)actorHitTargetNode5, 1, 5, 2 },
    { 2, -1, (CollisionFilterFn)actorHitTargetNode3, 1, 5, 2 },
    { -1, -1, NULL, 2, 2, 0 },
};
CollisionInteractionEntry D_8074B7C8[1] = { { -1, -1, NULL, 6, 5, 0 } };
CollisionTableEntry D_8074B7D4[5] = {
    { -1, D_8074B75C }, { 26, D_8074AC10 }, { 19, D_8074AC10 }, { -3, D_8074B7C8 },
    { 0, NULL },
};
CollisionInteractionEntry D_8074B7FC[9] = {
    { -1, 3072, NULL, 9, 2, 2 },
    { -1, 4, (CollisionFilterFn)actorIsTargetFallingFromAbove, 5, 3, 2 },
    { -1, 32, NULL, 4, 2, 2 },
    { -1, 512, (CollisionFilterFn)actorIsFacingTarget, 4, 2, 2 },
    { -1, 128, (CollisionFilterFn)actorIsTargetAbovePitchThreshold, 4, 2, 2 },
    { -1, 328, (CollisionFilterFn)actorIsFacingTarget, 5, 2, 2 },
    { 2, -1, (CollisionFilterFn)actorHitTargetNode5, 1, 5, 2 },
    { 2, -1, (CollisionFilterFn)actorHitTargetNode3, 1, 5, 2 },
    { -1, -1, NULL, 2, 2, 0 },
};
CollisionTableEntry D_8074B868[6] = {
    { -1, D_8074B7FC }, { 41, D_8074AC10 }, { 171, D_8074AC10 }, { 26, D_8074AC10 },
    { -3, D_8074B49C }, { 0, NULL },
};
CollisionInteractionEntry D_8074B898[11] = {
    { -1, 4, (CollisionFilterFn)actorIsTargetFallingFromAbove, 5, 3, 2 },
    { -1, 32, (CollisionFilterFn)actorHitTargetNode1, 4, 2, 2 },
    { -1, 1024, NULL, 9, 2, 2 },
    { -1, 2560, (CollisionFilterFn)actorListHasId1FacingTarget, 4, 2, 2 },
    { -1, 128, (CollisionFilterFn)actorIsTargetAbovePitchThreshold, 4, 2, 2 },
    { -1, 328, (CollisionFilterFn)actorListHasId1FacingTarget, 5, 2, 2 },
    { 4, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 13, 2 },
    { 4, -1, (CollisionFilterFn)actorHitTargetNode3, 1, 13, 2 },
    { 2, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 12, 2 },
    { 2, -1, (CollisionFilterFn)actorHitTargetNode3, 1, 12, 2 },
    { -1, -1, NULL, 1, 2, 0 },
};
CollisionInteractionEntry D_8074B91C[4] = {
    { -1, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 1, 2 },
    { -1, -1, (CollisionFilterFn)actorHitTargetNode3, 1, 1, 2 },
    { 8, -1, (CollisionFilterFn)actorHitTargetNode1, 9, 5, 2 },
    { -1, -1, (CollisionFilterFn)actorHitTargetNode1, 1, 5, 0 },
};
CollisionTableEntry D_8074B94C[6] = {
    { -1, D_8074B898 }, { 41, D_8074B91C }, { 171, D_8074B91C }, { 26, D_8074AC10 },
    { -3, D_8074B49C }, { 0, NULL },
};
CollisionInteractionEntry D_8074B97C[10] = {
    { 1, 4, (CollisionFilterFn)actorIsTargetFallingFromAbove, 7, 3, 2 },
    { -1, 1056, NULL, 6, 2, 2 },
    { -1, 2560, (CollisionFilterFn)actorIsFacingTarget, 6, 2, 2 },
    { -1, 128, (CollisionFilterFn)actorIsTargetAbovePitchThreshold, 6, 2, 2 },
    { -1, 328, (CollisionFilterFn)actorIsFacingTarget, 7, 2, 2 },
    { 2, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 11, 2 },
    { 2, -1, (CollisionFilterFn)actorHitTargetNode3, 1, 11, 2 },
    { 4, -1, (CollisionFilterFn)actorHitTargetNode2, 1, 12, 2 },
    { 4, -1, (CollisionFilterFn)actorHitTargetNode3, 1, 12, 2 },
    { -1, -1, NULL, 2, 2, 0 },
};
CollisionTableEntry D_8074B9F4[6] = {
    { -1, D_8074B97C }, { 26, D_8074AC10 }, { 19, D_8074AC10 }, { 67, D_8074AC10 },
    { -3, D_8074B7C8 }, { 0, NULL },
};
CollisionInteractionEntry D_8074BA24[3] = {
    { -1, 1024, NULL, 9, 2, 2 },
    { -1, 8, NULL, 2, 8, 2 },
    { -1, -1, NULL, 1, 4, 0 },
};
CollisionInteractionEntry D_8074BA48[1] = { { -1, -1, NULL, 6, 5, 0 } };
CollisionInteractionEntry D_8074BA54[1] = { { -1, -1, NULL, 2, 5, 0 } };
CollisionTableEntry D_8074BA60[5] = {
    { -1, D_8074BA24 }, { 41, D_8074BA48 }, { 171, D_8074BA48 }, { -3, D_8074BA54 },
    { 0, NULL },
};
CollisionInteractionEntry D_8074BA88[1] = { { -1, -1, NULL, 9, 4, 0 } };
CollisionTableEntry D_8074BA94[6] = {
    { -1, D_8074BA88 }, { 29, D_8074AC1C }, { 41, D_8074BA48 }, { 171, D_8074BA48 },
    { -3, D_8074BA48 }, { 0, NULL },
};
CollisionInteractionEntry D_8074BAC4[1] = { { -1, -1, NULL, 4, 5, 0 } };
CollisionInteractionEntry D_8074BAD0[1] = { { -1, -1, NULL, 4, 0, 0 } };
CollisionTableEntry D_8074BADC[3] = { { -1, D_8074BAC4 }, { 29, D_8074BAD0 }, { 0, NULL } };
CollisionTableEntry D_8074BAF4[2] = { { -1, D_8074AC1C }, { 0, NULL } };
CollisionInteractionEntry D_8074BB04[1] = { { -1, -1, NULL, 9, 5, 0 } };
CollisionTableEntry D_8074BB10[3] = { { -1, D_8074BB04 }, { 29, D_8074AC1C }, { 0, NULL } };
CollisionInteractionEntry D_8074BB28[1] = { { -1, -1, NULL, 4, 0, 0 } };
CollisionInteractionEntry D_8074BB34[1] = { { -1, -1, NULL, 5, 5, 0 } };
CollisionTableEntry D_8074BB40[4] = {
    { 302, D_8074BB28 }, { 312, D_8074BB34 }, { 305, D_8074BB34 }, { 0, NULL },
};
CollisionTableEntry D_8074BB60[2] = { { 312, D_8074BB34 }, { 0, NULL } };
CollisionTableEntry D_8074BB70[2] = { { 312, D_8074BB34 }, { 0, NULL } };
CollisionInteractionEntry D_8074BB80[1] = { { -1, -1, NULL, 4, 0, 0 } };
CollisionTableEntry D_8074BB8C[2] = { { 307, D_8074BB80 }, { 0, NULL } };
CollisionInteractionEntry D_8074BB9C[1] = { { -1, -1, NULL, 4, 0, 0 } };
CollisionTableEntry D_8074BBA8[2] = { { 322, D_8074BB9C }, { 0, NULL } };
CollisionTableEntry D_8074BBB8[5] = {
    { -1, D_8074B448 }, { 26, D_8074AC10 }, { 19, D_8074AC10 }, { -3, D_8074B300 },
    { 0, NULL },
};
CollisionInteractionEntry D_8074BBE0[1] = { { -1, -1, NULL, 1, 5, 0 } };
CollisionTableEntry D_8074BBEC[5] = {
    { -1, D_8074BBE0 }, { 26, D_8074AC10 }, { 19, D_8074AC10 }, { -3, D_8074B300 },
    { 0, NULL },
};
CollisionInteractionEntry D_8074BC14[1] = { { -1, -1, NULL, 1, 12, 0 } };
CollisionTableEntry D_8074BC20[2] = { { -1, D_8074BC14 }, { 0, NULL } };
CollisionTableEntry D_8074BC30[5] = {
    { -1, D_8074BBE0 }, { 26, D_8074B684 }, { 19, D_8074B684 }, { -3, D_8074B684 },
    { 0, NULL },
};
CollisionInteractionEntry D_8074BC58[3] = {
    { 1, -1, NULL, 4, 0, 2 },
    { 2, 3944, NULL, 5, 1, 2 },
    { 2, -1, NULL, 1, 1, 0 },
};
CollisionTableEntry D_8074BC7C[2] = { { -1, D_8074BC58 }, { 0, NULL } };
CollisionInteractionEntry D_8074BC8C[4] = {
    { -1, -1, (CollisionFilterFn)actorHitTargetNode3, 6, 5, 2 },
    { -1, -1, (CollisionFilterFn)actorHitTargetNode4, 6, 5, 2 },
    { -1, -1, (CollisionFilterFn)actorHitTargetNode5, 6, 5, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionInteractionEntry D_8074BCBC[2] = {
    { -1, -1, NULL, 1, 2, 1 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionTableEntry D_8074BCD4[6] = {
    { -1, D_8074BCBC }, { 26, D_8074BC8C }, { 89, D_8074BC8C }, { 30, D_8074AC1C },
    { -3, D_8074AC28 }, { 0, NULL },
};
CollisionInteractionEntry D_8074BD04[3] = {
    { 4, -1, (CollisionFilterFn)actorHitTargetNode1GroundPound, 4, 3, 2 },
    { 4, -1, (CollisionFilterFn)actorHitTargetNode1, 1, 2, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionInteractionEntry D_8074BD28[2] = {
    { 2, -1, (CollisionFilterFn)actorHitTargetNode1, 6, 5, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionTableEntry D_8074BD40[3] = { { -1, D_8074BD04 }, { -3, D_8074BD28 }, { 0, NULL } };
CollisionInteractionEntry D_8074BD58[2] = {
    { -1, -1, (CollisionFilterFn)actorIsTargetBelowNode, 1, 13, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionInteractionEntry D_8074BD70[2] = {
    { 2, -1, NULL, 6, 5, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionTableEntry D_8074BD88[4] = {
    { -1, D_8074BD58 }, { 26, D_8074BD70 }, { -3, D_8074AC28 }, { 0, NULL },
};
CollisionInteractionEntry D_8074BDA8[4] = {
    { 4, 2560, (CollisionFilterFn)actorTargetIsLargeMode, 7, 2, 2 },
    { 4, 64, (CollisionFilterFn)actorTargetIsLargeMode, 7, 2, 2 },
    { 4, -1, (CollisionFilterFn)actorTargetIsLargeMode, 1, 2, 2 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionTableEntry D_8074BDD8[4] = {
    { -1, D_8074BDA8 }, { 26, D_8074BD70 }, { -3, D_8074AC28 }, { 0, NULL },
};
CollisionInteractionEntry D_8074BDF8[2] = {
    { -1, -1, (CollisionFilterFn)actorHitTargetNode3, 5, 2, 2 },
    { -1, -1, NULL, 1, 2, 0 },
};
CollisionInteractionEntry D_8074BE10[1] = { { -1, -1, NULL, 4, 5, 0 } };
CollisionInteractionEntry D_8074BE1C[2] = {
    { -1, -1, NULL, 1, 2, 1 },
    { -1, -1, NULL, 1, 5, 0 },
};
CollisionTableEntry D_8074BE34[5] = {
    { 9, D_8074BDF8 }, { -1, D_8074BE1C }, { 319, D_8074ACE8 }, { -3, D_8074BE10 },
    { 0, NULL },
};
CollisionInteractionEntry D_8074BE5C[1] = { { -1, -1, NULL, 4, 2, 0 } };
CollisionTableEntry D_8074BE68[3] = { { 216, D_8074BE5C }, { -3, D_8074AC1C }, { 0, NULL } };
CollisionInteractionEntry D_8074BE80[1] = { { -1, -1, NULL, 1, 5, 0 } };
CollisionTableEntry D_8074BE8C[2] = { { 41, D_8074BE80 }, { 0, NULL } };
CollisionInteractionEntry D_8074BE9C[1] = { { -1, -1, NULL, 1, 5, 0 } };
CollisionTableEntry D_8074BEA8[2] = { { 171, D_8074BE9C }, { 0, NULL } };
CollisionInteractionEntry D_8074BEB8[1] = { { -1, -1, NULL, 4, 5, 0 } };
CollisionTableEntry D_8074BEC4[2] = { { 35, D_8074BEB8 }, { 0, NULL } };
CollisionInteractionEntry D_8074BED4[1] = { { -1, -1, NULL, 1, 2, 0 } };
CollisionTableEntry D_8074BEE0[2] = { { -1, D_8074BED4 }, { 0, NULL } };
CollisionTableEntry D_8074BEF0[2] = { { -1, D_8074AC28 }, { 0, NULL } };
CollisionInteractionEntry D_8074BF00[1] = { { -1, -1, NULL, 5, 2, 0 } };
CollisionTableEntry D_8074BF0C[3] = { { -1, D_8074BF00 }, { 180, D_8074AC40 }, { 0, NULL } };
CollisionInteractionEntry D_8074BF24[1] = { { -1, -1, NULL, 4, 5, 0 } };
CollisionTableEntry D_8074BF30[2] = { { 36, D_8074BF24 }, { 0, NULL } };
CollisionTableEntry D_8074BF40[2] = { { 38, D_8074BF24 }, { 0, NULL } };
CollisionTableEntry D_8074BF50[2] = { { 43, D_8074BF24 }, { 0, NULL } };
CollisionTableEntry D_8074BF60[2] = { { 42, D_8074BF24 }, { 0, NULL } };
CollisionTableEntry D_8074BF70[2] = { { 48, D_8074BF24 }, { 0, NULL } };
CollisionInteractionEntry D_8074BF80[2] = {
    { 1, -1, NULL, 4, 5, 2 },
    { 2, -1, NULL, 4, 0, 0 },
};
CollisionTableEntry D_8074BF98[2] = { { -1, D_8074BF80 }, { 0, NULL } };
CollisionTableEntry D_8074BFA8[2] = { { -2, D_8074AC28 }, { 0, NULL } };
CollisionInteractionEntry D_8074BFB8[6] = {
    { 4, -1, NULL, 5, 0, 2 },
    { 8, -1, (CollisionFilterFn)actorHitTargetNode5, 5, 2, 2 },
    { 2, -1, NULL, 4, 4, 2 },
    { -1, -1, (CollisionFilterFn)actorTargetIsLargeMode, 1, 2, 2 },
    { -1, -1, NULL, 1, 2, 1 },
    { -1, -1, NULL, 2, 5, 0 },
};
CollisionTableEntry D_8074C000[4] = {
    { 25, D_8074AC1C }, { -1, D_8074BFB8 }, { -3, D_8074AC28 }, { 0, NULL },
};
CollisionInteractionEntry D_8074C020[1] = { { -1, -1, NULL, 9, 13, 0 } };
CollisionTableEntry D_8074C02C[2] = { { -8, D_8074C020 }, { 0, NULL } };
CollisionInteractionEntry D_8074C03C[1] = { { -1, -1, NULL, 1, 5, 0 } };
CollisionInteractionEntry D_8074C048[2] = {
    { 2, -1, (CollisionFilterFn)actorHitTargetNode1, 6, 5, 2 },
    { -1, -1, NULL, 5, 5, 0 },
};
CollisionTableEntry D_8074C060[3] = { { -1, D_8074C03C }, { -3, D_8074C048 }, { 0, NULL } };
CollisionInteractionEntry D_8074C078[2] = {
    { -1, 4088, NULL, 4, 2, 2 },
    { -1, -1, NULL, 1, 2, 0 },
};
CollisionTableEntry D_8074C090[2] = { { -1, D_8074C078 }, { 0, NULL } };

// Per-actor-type update functions, called by 7CA80 (one more entry than actor types).
void (*gActorUpdateFuncs[345])(void) = {
    actorStub7CA80_00,
    actorStub7CA80_02,
    playerUpdateSoundEffect0,
    playerUpdateSoundEffect1,
    playerUpdateSoundEffect2,
    playerUpdateSoundEffect3,
    playerUpdateSoundEffect4,
    playerUpdateSoundEffect5,
    playerUpdateSoundEffect6,
    playerUpdateSoundEffect7,
    actorVolumeTriggersUpdate,
    actorSpawnNodesUpdate,
    actorCutsceneDispatchEvents,
    volumeHookModelStateUpdate,
    volumeHookActorEventUpdate,
    volumeHookCameraLightUpdate,
    actorStub7CA80_03,
    movingLaunchBarrelUpdate,
    transformBarrelWrapperUpdateC,
    actorTransformCameraUpdateC,
    csCamPathActorUpdate,
    tagBarrelRotateUpdate,
    tagBarrelCheckProximity,
    launchBarrelUpdate,
    actorNumberedTargetUpdate,
    tagBarrelUpdateAndCheckRecoil,
    actorTransformCameraUpdateB,
    tagBarrelCheckProximity1A,
    tagBarrelActorUpdate,
    OVL_FN(void (*)(void), 0x80024890) /* minecartUpdateHeadlightAndSpeed (minecart) */,
    projectileSpawnParticleEffect2,
    actorBridgeUpdate,
    actorSpotLightUpdate,
    projectileBehaviourEntryB,
    OVL_FN(void (*)(void), 0x800277F8) /* bonusTargetGameUpdate (bonus) */,
    projectileDespawnOrExplode,
    projectileHomingUpdate,
    mountedBarrelUpdate,
    projectileBeamUpdate,
    actorLongBridgeUpdate,
    tagBarrelUpdateRecoilState0,
    projectileBounceExplodeScaledUpdate,
    projectileMultiplayerUpdate,
    projectileMatrixRotationUpdate,
    actorApplyTransformAndRender,
    actorBounceFadeInSpinUpdateType1,
    OVL_FN(void (*)(void), 0x80027F14) /* bonusTurtleTroubleGameUpdate (bonus) */,
    actorHealthDropUpdate,
    projectileRotatingUpdate,
    rocketbarrelUpdate,
    projectileBounceExplodeGreenUpdate,
    actorAmmoCrateDropUpdate,
    actorThrowAmmoDropUpdate,
    actorKongDropUpdate,
    actorMinigameCoinDropUpdate,
    projectileParticleSpawnerTick,
    transformBarrelWrapperUpdateA,
    transformBarrelWrapperUpdateB,
    actorSpotLightUpdateEntry,
    projectileSpawnParticleEffect3,
    actorPlayerWarpEffectUpdate,
    actorUpdateTimerBarAndRange,
    OVL_FN(void (*)(void), 0x80024B00) /* minecartReverseTrackBehaviour (minecart) */,
    actorUrnType1Update,
    actorUrnType2Update,
    actorUrnType3Update,
    actorUrnType4Update,
    actorChunkyCannonballUpdate,
    projectileBehaviourEntryA,
    projectileBehaviourEntryC,
    textUpdateThreeDigitCounter,
    actorTriggerRampWithSfx,
    actorUpdateSfxAndGround,
    cannonUpdate,
    projectileHomingParticleUpdate,
    effectSpawnAttachedSpriteColoredType3,
    effectSpawnAttachedSpriteColoredType6,
    effectSpawnAttachedSpriteColoredType4,
    effectSpawnAttachedSpriteColoredType2,
    effectSpawnAttachedSpriteColoredType5,
    OVL_FN(void (*)(void), 0x80024914) /* minecartUpdatePhysics (minecart) */,
    projectileSparkleUpdateGold,
    projectileFallBounceUpdate,
    actorSagSingleUpdate,
    tagBarrelCheckPlayerState,
    textMarkerUpdateMatrixWrapper,
    actorSpawnRingBurstAndUpdate,
    OVL_FN(void (*)(void), 0x80024FD0) /* minecartPlayerCartJunctionBehaviour (minecart) */,
    textUpdateTwoDigitCounter,
    projectileChaseTargetUpdate,
    actorUpdateSpinAndVelocityWrapperA,
    actorPathCollectibleUpdateFBC,
    actorFallAndBurstUpdate,
    actorUpdateSpinAndVelocityWrapperB,
    actorClearSubState,
    hudPauseMenuUpdate,
    transformBarrelInitScale,
    tagBarrelInitDrawDistanceAndState,
    tagBarrelWrapperUpdateA,
    projectileSpawnParticleEffect,
    tagBarrelSpawnType13A,
    tagBarrelSpawnType13B,
    tagBarrelSpawnType13C,
    tagBarrelSpawnType13D,
    tagBarrelSpawnType13E,
    tagBarrelSpawnType13F,
    actorMirrorParentModelY,
    tagBarrelCheckDespawn,
    projectileSpawnParticleEffectWithScale,
    actorSeekTargetUpdate,
    actorKongDropPersistentUpdate,
    actorPathCollectibleUpdateF98,
    actorPathCollectibleUpdate1028,
    actorPathCollectibleUpdate1004A,
    actorPathCollectibleUpdateFE0,
    actorFinishInRange,
    projectileBehaviourEntryD,
    actorSparkCutsceneUpdate,
    actorRandomEffectDropUpdate,
    actorOpponentKnockbackDropUpdate,
    actorSpeedBoostDropUpdate,
    actorAbilityEnergyDropUpdate,
    effectSpawnA6230Wrapper,
    actorMirrorParentModelAxis,
    OVL_FN(void (*)(void), 0x8002A398) /* bonusPerilPathPanicGameUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x80029364) /* bonusLightFlashGameUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x8002AED8) /* bonusBigBugBashGameUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x8002BF98) /* bonusSearchlightSeekGameUpdate (bonus) */,
    effectActorSparkleTick,
    transformBarrelUpdateNear,
    actorSpawnEffectAndTick,
    appleWormUpdate,
    transformBarrelWrapperUpdateD,
    actorTransformCameraUpdateA,
    tagBarrelUpdateStateCheck,
    actorPlaySoundVariantAndFinish,
    tagBarrelWrapperUpdateB,
    tagBarrelWrapperUpdateC,
    OVL_FN(void (*)(void), 0x80027448) /* critterBananaFairyUpdate (critter) */,
    actorSinkAndDespawn,
    actorLargeDropUpdate,
    actorStubCBEA0_02,
    actorStubCBEA0_03,
    actorStubCBEA0_04,
    actorStubCBEA0_05,
    stub_806A1FD0,
    actorPlaceModelAtCamera,
    actorPathCollectibleUpdate1004B,
    actorGroupBoneFrameUpdate,
    actorTransformCameraUpdateD,
    tagBarrelSpawnType95,
    actorStubCBEA0_12,
    actorStubCBEA0_13,
    actorStubCBEA0_14,
    actorStubCBEA0_15,
    actorStubCBEA0_16,
    actorHintTextUpdate,
    actorStubCBEA0_18,
    actorStubCBEA0_19,
    actorStubCBEA0_20,
    actorStubCBEA0_21,
    actorStubCBEA0_22,
    actorStubCBEA0_23,
    OVL_FN(void (*)(void), 0x80027DC0) /* critterBananaFairyRewardUpdate (critter) */,
    enemyGridStateStep,
    OVL_FN(void (*)(void), 0x80031AA0) /* bossSpawnerUpdate (boss) */,
    OVL_FN(void (*)(void), 0x80032B08) /* bossFollowerActorUpdate (boss) */,
    tagBarrelPeerUpdate,
    OVL_FN(void (*)(void), 0x80028120) /* critterFlutterFlyUpdate (critter) */,
    projectileChaseReflectUpdate,
    actorOrbitPlayerMidpointUpdate,
    projectileImpactExplosionUpdate,
    actorStub7CA80_04,
    camNoop201B0,
    func_8067B280,
    explodingChaserUpdate,
    hudCountdownTimerUpdate,
    hudCountdownTimerHostUpdate,
    behaviourTrackingPatrolEnemyEvadeUpdate,
    OVL_FN(void (*)(void), 0x8003575C) /* bossShockwaveTriggerDamage (boss) */,
    OVL_FN(void (*)(void), 0x800280BC) /* minecartUpdateObstacleType1 (minecart) */,
    behaviourEnemyFlySwoop,
    chaserEnemyUpdate,
    behaviourFlyPatrolState,
    OVL_FN(void (*)(void), 0x80024CB0) /* menuDispatchAction (menu) */,
    OVL_FN(void (*)(void), 0x800254D0) /* bossArmydilloStep (boss) */,
    OVL_FN(void (*)(void), 0x800284C0) /* bonusTargetUpdate (bonus) */,
    behaviourProjectileEnemyUpdate,
    playerCameraUpdateFromTarget,
    OVL_FN(void (*)(void), 0x800270E0) /* menuUpdateCrankyShopActor (menu) */,
    OVL_FN(void (*)(void), 0x80027738) /* menuUpdateFunkyShopActor (menu) */,
    OVL_FN(void (*)(void), 0x800275FC) /* menuUpdateCandyShopActor (menu) */,
    OVL_FN(void (*)(void), 0x80024690) /* raceOpponentBehaviourUpdate (race) */,
    actorNpcFlagCountQuestUpdate,
    behaviourEnemyBatUpdate,
    behaviourEnemyFlyStep,
    actorNpcDonkeyUpdate,
    actorNpcDiddyUpdate,
    actorNpcLankyUpdate,
    actorNpcTinyUpdate,
    actorNpcChunkyUpdate,
    func_806C1E44,
    actorPhotoUpdate,
    bananaDeliveryDoorLockUpdate,
    OVL_FN(void (*)(void), 0x80033AF0) /* bossMainStep (boss) */,
    behaviourPulseEnemyVulnerableUpdate,
    behaviourFlyPatrolState2,
    actorTargetGameHostUpdate,
    behaviourPulseEnemyExplosiveOnlyUpdate,
    behaviourPulseEnemyProjectileOnlyUpdate,
    actorUpdateLockOnCursor,
    behaviourPulseEnemyDeathChaserUpdate,
    behaviourTrackingPatrolEnemyUpdate,
    actorUpdatePeriodicParticleEmitter,
    OVL_FN(void (*)(void), 0x8002835C) /* minecartUpdateObstacleType2 (minecart) */,
    OVL_FN(void (*)(void), 0x800286EC) /* minecartUpdateObstacleType3 (minecart) */,
    OVL_FN(void (*)(void), 0x80029468) /* bossMadJackStep (boss) */,
    actorPhotoUpdateEntry,
    OVL_FN(void (*)(void), 0x8002570C) /* bonusReelGameUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x800261B8) /* bonusReelUpdate (bonus) */,
    actorUpdateCannonballBurstEmitter,
    OVL_FN(void (*)(void), 0x8002DCE0) /* bossUpdateAttachment (boss) */,
    OVL_FN(void (*)(void), 0x8002E82C) /* bossPhaseTick (boss) */,
    actorUpdateFlameBurstEmitter,
    behaviourAmbushEnemyUpdate,
    actorNpcKongWarpEffectUpdate,
    bananaDeliveryPartnerUpdate,
    OVL_FN(void (*)(void), 0x8002FF74) /* bossKRoolTinyStep (boss) */,
    behaviourFairyInitPlayerScale,
    OVL_FN(void (*)(void), 0x80030888) /* bossKRoolTinyUpdateMinion (boss) */,
    behaviourFairyIdle4,
    behaviourFairyWanderUpdate,
    textMarkerUpdate,
    actorPerMapCarrierUpdate,
    bananaDeliveryNpcUpdate,
    behaviourArmadilloPatrol,
    OVL_FN(void (*)(void), 0x8002A92C) /* bossPufftossStep (boss) */,
    behaviourTumbleDebrisUpdate,
    behaviourMeleePatrolEnemyUpdate,
    actorPlaySoundAndFinish,
    spotlightFollowerSubmergedUpdate,
    b5ec0SetMode4,
    b5ec0SetMode2,
    b5ec0SetMode3,
    b5ec0SetMode0,
    b5ec0SetMode1,
    timedWarpTargetUpdate,
    actorNpcSealUpdate,
    actorPhotoSubjectUpdate,
    spotlightFollowerUpdate,
    actorGatedTargetGameHostUpdate,
    OVL_FN(void (*)(void), 0x8002C964) /* bossKutOutStep (boss) */,
    actorTargetCourseHostUpdate,
    OVL_FN(void (*)(void), 0x80032550) /* menuLightSpotlightActorUpdate (menu) */,
    actorScriptedUpdate,
    actorLightPulseUpdate,
    OVL_FN(void (*)(void), 0x80024158) /* bonusControllerUpdate (bonus) */,
    actorUpdateAimedProjectileEmitter,
    actorShockwaveUpdate,
    behaviourSearchlightGuardUpdate,
    actorUpdateBannerFade,
    behaviourFlyPatrolState3,
    behaviourArmoredEnemyUpdate,
    projectileSpriteRingUpdate,
    actorPresentBeforePlayerUpdate,
    effectActorGrowthTick,
    OVL_FN(void (*)(void), 0x8002904C) /* critterUpdateText (critter) */,
    behaviourSwimLungeUpdate,
    behaviourSwimShooterUpdate,
    behaviourFairyIdle1,
    behaviourFairyIdle2,
    behaviourFairyIdle3,
    timedSmokeTargetHostUpdate,
    smokeTargetChaserUpdate,
    projectileSparkleUpdateSilver,
    actorNodeRingUpdate,
    behaviourDropInEnemyUpdate,
    actorBehaviourNoop,
    projectileActorUpdate,
    actorShadowFollowUpdate,
    actorFollowLinkedNodeFadeUpdate,
    OVL_FN(void (*)(void), 0x8002D230) /* bossKRoolDkStep (boss) */,
    actorFollowParentPulseUpdate,
    OVL_FN(void (*)(void), 0x800265F0) /* minecartFollowerBehaviour (minecart) */,
    OVL_FN(void (*)(void), 0x80026DA8) /* minecartFollowerChildBehaviour (minecart) */,
    behaviourEnemyFlyIdle,
    behaviourTimedScriptCycleUpdate,
    OVL_FN(void (*)(void), 0x80027778) /* minecartUpdateFollower (minecart) */,
    behaviourProximityChaseEnemyUpdate,
    behaviourSimplePatrolEnemyUpdate,
    actorSwellBurstUpdate,
    behaviourExplosiveAwareEnemyUpdate,
    OVL_FN(void (*)(void), 0x8002DE04) /* bossKRoolDiddyStep (boss) */,
    OVL_FN(void (*)(void), 0x8002EA7C) /* bossKRoolLankyStep (boss) */,
    OVL_FN(void (*)(void), 0x8002F100) /* bossDogadonStep (boss) */,
    OVL_FN(void (*)(void), 0x80030EC4) /* bossKRoolChunkyStep (boss) */,
    actorStub7CA80_05,
    OVL_FN(void (*)(void), 0x80024E38) /* bonusMazeChallengeUpdate (bonus) */,
    actorStub7CA80_06,
    textBoxUpdate,
    OVL_FN(void (*)(void), 0x8002881C) /* bonusTurtleTroubleSnakeUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x80028E3C) /* bonusTurtleTroubleTurtleUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x80026F04) /* raceVehicleBehaviorUpdate (race) */,
    OVL_FN(void (*)(void), 0x80028440) /* raceOpponentCarBehaviorUpdate (race) */,
    OVL_FN(void (*)(void), 0x80028AD0) /* raceCameraBehaviorUpdate (race) */,
    OVL_FN(void (*)(void), 0x800274C0) /* raceProjectileBehaviorUpdate (race) */,
    OVL_FN(void (*)(void), 0x8002D778) /* raceManagerBehaviorUpdate (race) */,
    OVL_FN(void (*)(void), 0x800294A8) /* raceCompetitorMotionUpdate (race) */,
    OVL_FN(void (*)(void), 0x8002A0AC) /* raceOpponentRacerBehaviorUpdate (race) */,
    effectActorShrinkTick,
    actorStaticModelUpdate,
    OVL_FN(void (*)(void), 0x8002DC24) /* raceFinishBannerBehaviorUpdate (race) */,
    OVL_FN(void (*)(void), 0x80029054) /* raceObstacleCarBehaviorUpdate (race) */,
    actorChildEffectUpdate,
    OVL_FN(void (*)(void), 0x8003264C) /* menuUpdateLightFadeActor (menu) */,
    OVL_FN(void (*)(void), 0x8002E484) /* racePlayerTrackerBehaviorUpdate (race) */,
    tagBarrelInteractiveUpdate,
    tagBarrelUpdateSelectedKong,
    OVL_FN(void (*)(void), 0x80026094) /* mpUpdate (multiplayer) */,
    actorUpdatePlayerInteraction,
    OVL_FN(void (*)(void), 0x80027988) /* menuUpdateTransformedWidgets (menu) */,
    cutsceneRestoreUpdate,
    OVL_FN(void (*)(void), 0x8002AE9C) /* raceParticipantMotionUpdate (race) */,
    OVL_FN(void (*)(void), 0x8002B964) /* raceOpponentRacerMotionUpdate (race) */,
    OVL_FN(void (*)(void), 0x80027DEC) /* menuUpdateOverlayWidgetActor (menu) */,
    actorScaleGrowthUpdate,
    OVL_FN(void (*)(void), 0x8002FEBC) /* menuInit (menu) */,
    OVL_FN(void (*)(void), 0x8002A010) /* bonusLightFlashTargetUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x8002AAA4) /* bonusPerilPathPanicKlaptrapUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x8002AD10) /* bonusPerilPathPanicFairyUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x8002B920) /* bonusBigBugBashFlyUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x8002C8EC) /* bonusSearchlightSeekTargetUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x8002BE44) /* bonusBigBugBashSwatterShadowUpdate (bonus) */,
    OVL_FN(void (*)(void), 0x80032024) /* menuUpdateKioskPodActor (menu) */,
    actorRingUpdate,
    OVL_FN(void (*)(void), 0x80024EF0) /* menuUpdateProgressGrid (menu) */,
    OVL_FN(void (*)(void), 0x80029118) /* critterBattleArenaUpdate (critter) */,
    OVL_FN(void (*)(void), 0x8002CB18) /* menuCharacterSelectUpdateActor (menu) */,
    bannerTextUpdate,
    OVL_FN(void (*)(void), 0x8002D2F0) /* bonusScoreHudUpdate (bonus) */,
    behaviourEnemyFlyReturn,
    OVL_FN(void (*)(void), 0x80028C18) /* menuMainScreenNoop (menu) */,
    hudTextScreenUpdate,
    hudTwoOptionMenuUpdate,
    actorStub7CA80_01,
};
CollisionTableSlot gActorTypeCollisionTables[344] = {
    { NULL, 0 }, { NULL, 0 }, { D_8074ACF4, 0 }, { D_8074ACF4, 0 },
    { D_8074ACF4, 0 }, { D_8074ACF4, 0 }, { D_8074ACF4, 0 }, { D_8074ACF4, 0 },
    { D_8074ACF4, 0 }, { D_8074ACF4, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { D_8074B104, 0 }, { D_8074B168, 0 }, { D_8074AF3C, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { D_8074B138, 0 },
    { D_8074ADA4, 0 }, { D_8074B190, 0 }, { D_8074AF94, 0 }, { NULL, 0 },
    { D_8074B204, 0 }, { D_8074BAF4, 0 }, { D_8074AE48, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { D_8074AEAC, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { D_8074B1A0, 0 }, { D_8074BE8C, 0 }, { NULL, 0 }, { NULL, 0 },
    { D_8074AE78, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { D_8074B1B0, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 1 },
    { D_8074B1C0, 0 }, { D_8074B1D0, 0 }, { D_8074AD94, 0 }, { D_8074AE48, 0 },
    { NULL, 0 }, { D_8074B00C, 0 }, { NULL, 0 }, { D_8074B08C, 0 },
    { D_8074B08C, 0 }, { D_8074B08C, 0 }, { D_8074B08C, 0 }, { D_8074B050, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { D_8074B0D4, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { D_8074BF0C, 0 }, { NULL, 0 },
    { NULL, 0 }, { D_8074B00C, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { D_8074AE48, 0 }, { NULL, 0 }, { D_8074BF30, 0 },
    { D_8074BF98, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { D_8074B190, 0 }, { NULL, 0 }, { D_8074B204, 0 }, { D_8074AE14, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { D_8074B204, 0 },
    { D_8074AE48, 0 }, { D_8074ADE4, 0 }, { NULL, 0 }, { D_8074BF40, 0 },
    { D_8074BF50, 0 }, { D_8074BF60, 0 }, { D_8074BF70, 0 }, { D_8074B3B8, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { D_8074AD78, 0 }, { D_8074B168, 0 }, { D_8074B00C, 0 }, { NULL, 0 },
    { D_8074B168, 0 }, { D_8074AF94, 0 }, { D_8074B204, 0 }, { D_8074B3B8, 0 },
    { D_8074B204, 0 }, { D_8074B204, 0 }, { D_8074B3B8, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { D_8074B3B8, 0 }, { NULL, 0 }, { D_8074BF60, 0 },
    { NULL, 0 }, { D_8074AF3C, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { D_8074B3B8, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { D_8074B138, 0 },
    { D_8074C090, 0 }, { D_8074AE48, 0 }, { D_8074AE48, 0 }, { D_8074BEA8, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { D_8074BA94, 1 },
    { NULL, 0 }, { NULL, 0 }, { D_8074B330, 1 }, { NULL, 0 },
    { D_8074BADC, 1 }, { D_8074BC20, 1 }, { D_8074BA60, 1 }, { D_8074BBEC, 1 },
    { D_8074B3B8, 0 }, { D_8074BCD4, 1 }, { NULL, 1 }, { D_8074B5C8, 1 },
    { NULL, 0 }, { D_8074B3B8, 0 }, { D_8074B3B8, 0 }, { D_8074B3B8, 0 },
    { D_8074BC7C, 1 }, { D_8074B3B8, 1 }, { D_8074BC30, 1 }, { D_8074BBEC, 1 },
    { D_8074B3B8, 1 }, { D_8074B3B8, 1 }, { D_8074B3B8, 1 }, { D_8074B3B8, 1 },
    { D_8074B3B8, 1 }, { D_8074B3D0, 1 }, { NULL, 0 }, { D_8074BEE0, 1 },
    { D_8074BD88, 1 }, { D_8074B4C0, 1 }, { D_8074BBEC, 1 }, { D_8074B3B8, 1 },
    { D_8074B538, 1 }, { D_8074B4E8, 1 }, { NULL, 1 }, { D_8074B4C0, 1 },
    { D_8074B330, 1 }, { D_8074BEF0, 1 }, { D_8074BB10, 1 }, { D_8074BADC, 1 },
    { D_8074BE34, 1 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 1 }, { NULL, 0 }, { D_8074C02C, 1 }, { NULL, 1 },
    { D_8074B330, 1 }, { NULL, 1 }, { D_8074B3B8, 1 }, { D_8074C060, 1 },
    { NULL, 1 }, { D_8074C060, 1 }, { D_8074B6B4, 1 }, { D_8074B3B8, 1 },
    { NULL, 0 }, { D_8074B3B8, 1 }, { D_8074B3B8, 1 }, { D_8074B868, 1 },
    { D_8074BDD8, 1 }, { NULL, 1 }, { D_8074B7D4, 1 }, { NULL, 0 },
    { NULL, 0 }, { D_8074B9F4, 1 }, { D_8074B9F4, 1 }, { D_8074B9F4, 1 },
    { D_8074B9F4, 1 }, { D_8074B9F4, 1 }, { D_8074B744, 1 }, { D_8074B3B8, 1 },
    { D_8074B3B8, 1 }, { D_8074B3B8, 1 }, { D_8074B3B8, 1 }, { D_8074B330, 1 },
    { D_8074B3B8, 1 }, { D_8074B3B8, 1 }, { NULL, 1 }, { D_8074BFA8, 0 },
    { NULL, 0 }, { D_8074BEF0, 1 }, { NULL, 0 }, { D_8074B7D4, 1 },
    { NULL, 0 }, { D_8074BBEC, 1 }, { D_8074B7D4, 1 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { D_8074B410, 1 },
    { D_8074B410, 1 }, { D_8074B6B4, 1 }, { D_8074B6B4, 1 }, { D_8074B6B4, 1 },
    { D_8074B428, 1 }, { D_8074B364, 1 }, { NULL, 0 }, { D_8074B3B8, 1 },
    { D_8074B330, 1 }, { D_8074B3B8, 1 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { D_8074C000, 1 }, { NULL, 0 }, { NULL, 0 },
    { D_8074B268, 0 }, { D_8074BBEC, 1 }, { D_8074B290, 1 }, { NULL, 0 },
    { D_8074B330, 1 }, { D_8074B330, 1 }, { D_8074B330, 1 }, { D_8074B94C, 1 },
    { D_8074C000, 1 }, { D_8074C000, 1 }, { D_8074C000, 1 }, { D_8074C000, 1 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { D_8074BEC4, 1 }, { NULL, 1 }, { D_8074BB60, 1 }, { D_8074BB40, 1 },
    { NULL, 1 }, { D_8074BB70, 1 }, { NULL, 0 }, { NULL, 0 },
    { D_8074BB8C, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { D_8074B3B8, 1 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { D_8074BE68, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { D_8074BBA8, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { NULL, 0 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
    { D_8074BBEC, 1 }, { NULL, 0 }, { NULL, 0 }, { NULL, 0 },
};
ActorTypeStat gActorTypeStats[344] = {
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 1 }, { 0, 0 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 0 }, { 0, 3 }, { 0, 0 },
    { 0, 0 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 0 }, { 0, 1 },
    { 0, 2 }, { 0, 0 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 1, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, 0 }, { 0, 1 },
    { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 },
    { 0, 0 }, { 0, 1 }, { 0, 0 }, { 0, 1 }, { 0, 0 }, { 0, 1 }, { 0, 1 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, 1 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, 1 },
    { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 1 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 1, 0 },
    { 0, 0 }, { 0, 0 }, { 1, 0 }, { 0, 0 }, { 1, 0 }, { 5, 0 }, { 1, 0 }, { 1, 0 },
    { 0, 0 }, { 4, 0 }, { 1, 0 }, { 3, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 1, 0 }, { 3, 0 }, { 5, 0 }, { 3, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 },
    { 1, 0 }, { 1, 0 }, { 0, 1 }, { 1, 0 }, { 5, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 },
    { 1, 0 }, { 1, 0 }, { 1, 0 }, { 3, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 },
    { 5, 0 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 1, 0 }, { 0, 0 }, { 1, 0 }, { 1, 0 },
    { 1, 0 }, { 1, 0 }, { 1, 0 }, { 10, 0 }, { 16, 0 }, { 10, 0 }, { 1, 0 }, { 1, 0 },
    { 0, 0 }, { 1, 0 }, { 1, 0 }, { 3, 0 }, { 65, 0 }, { 1, 0 }, { 3, 0 }, { 0, 0 },
    { 0, 0 }, { 15, 0 }, { 15, 0 }, { 15, 0 }, { 15, 0 }, { 15, 0 }, { 1, 0 }, { 1, 0 },
    { 3, 0 }, { 1, 0 }, { 1, 0 }, { 6, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 0, 0 },
    { 0, 0 }, { 1, 0 }, { 0, 0 }, { 3, 0 }, { 0, 0 }, { 3, 0 }, { 3, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 1, 0 }, { 3, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 },
    { 5, 0 }, { 1, 1 }, { 0, 0 }, { 1, 0 }, { 5, 0 }, { 1, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 70, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 1, 0 }, { 1, 0 }, { 0, 0 },
    { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 70, 0 }, { 70, 0 }, { 70, 0 }, { 70, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 }, { 1, 0 },
    { 1, 0 }, { 1, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 1, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
    { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 1 },
    { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 1 }, { 0, 0 },
    { 0, 0 }, { 0, 1 }, { 0, 0 }, { 0, 0 }, { 1, 0 }, { 0, 1 }, { 0, 0 }, { 0, 0 },
};
u16 gActorTypeCollisionFlags[344] = {
    0x0010, 0x0010, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001,
    0x0001, 0x0001, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010, 0x0010,
    0x0010, 0x0008, 0x0008, 0x0008, 0x0010, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0020, 0x0004, 0x0008,
    0x0008, 0x0008, 0x0008, 0x0004, 0x0004, 0x0020, 0x0004, 0x0008,
    0x0008, 0x0004, 0x0004, 0x0004, 0x0004, 0x0008, 0x0008, 0x0008,
    0x0004, 0x0008, 0x0004, 0x0008, 0x0008, 0x0008, 0x0008, 0x0004,
    0x0008, 0x0008, 0x0008, 0x0004, 0x0008, 0x0008, 0x0020, 0x0008,
    0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0008, 0x0004, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008,
    0x0020, 0x0004, 0x0008, 0x0008, 0x0010, 0x0008, 0x0008, 0x0020,
    0x0008, 0x0004, 0x0008, 0x0008, 0x0008, 0x0008, 0x0020, 0x0010,
    0x0008, 0x0008, 0x0008, 0x0004, 0x0008, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0008, 0x0008, 0x0008, 0x0004, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0008, 0x0010, 0x0008,
    0x0008, 0x0008, 0x0008, 0x0008, 0x0002, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0008, 0x0008, 0x0002, 0x0008, 0x0008, 0x0008, 0x0008,
    0x0008, 0x0004, 0x0004, 0x0004, 0x0010, 0x0010, 0x0010, 0x0002,
    0x0010, 0x0010, 0x0002, 0x0008, 0x0002, 0x0002, 0x0002, 0x0002,
    0x0040, 0x0080, 0x0002, 0x0002, 0x0010, 0x0040, 0x0040, 0x0040,
    0x0002, 0x0040, 0x0002, 0x0002, 0x0040, 0x0040, 0x0040, 0x0040,
    0x0040, 0x0040, 0x0008, 0x0002, 0x0080, 0x0002, 0x0002, 0x0040,
    0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002,
    0x0080, 0x0008, 0x0008, 0x0008, 0x0002, 0x0008, 0x0008, 0x0002,
    0x0002, 0x0008, 0x0002, 0x0002, 0x0080, 0x0002, 0x0002, 0x0040,
    0x0010, 0x0040, 0x0002, 0x0002, 0x0080, 0x0002, 0x0002, 0x0008,
    0x0040, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0040,
    0x0002, 0x0040, 0x0040, 0x0080, 0x0040, 0x0040, 0x0040, 0x0008,
    0x0010, 0x0002, 0x0008, 0x0002, 0x0010, 0x0002, 0x0002, 0x0004,
    0x0008, 0x0008, 0x0010, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002,
    0x0040, 0x0002, 0x0004, 0x0040, 0x0002, 0x0040, 0x0004, 0x0008,
    0x0008, 0x0080, 0x0008, 0x0002, 0x0008, 0x0002, 0x0008, 0x0004,
    0x0002, 0x0002, 0x0002, 0x0002, 0x0080, 0x0080, 0x0080, 0x0080,
    0x0010, 0x0010, 0x0010, 0x0010, 0x0002, 0x0002, 0x0002, 0x0002,
    0x0010, 0x0002, 0x0010, 0x0010, 0x0002, 0x0002, 0x0002, 0x0020,
    0x0002, 0x0002, 0x0040, 0x0020, 0x0040, 0x0008, 0x0010, 0x0010,
    0x0008, 0x0040, 0x0020, 0x0002, 0x0010, 0x0008, 0x0010, 0x0002,
    0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0010,
    0x0010, 0x0002, 0x0010, 0x0010, 0x0002, 0x0002, 0x0010, 0x0010,
};
u8 gActorTypeInitIndex[344] = {
    1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3,
    1, 2, 2, 2, 3, 2, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 4, 4, 2, 4, 2, 2, 4, 4, 2, 2, 2, 2, 4,
    4, 2, 4, 4, 4, 4, 4, 4, 2, 2, 2, 4, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4,
    2, 4, 2, 2, 3, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 3,
    2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 4, 4,
    4, 4, 4, 2, 2, 2, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2,
    4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2,
    2, 2, 2, 4, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 3, 2, 2,
    3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 3, 2, 2, 4, 2, 2, 2, 2, 2, 2, 3, 2, 2, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 4, 2, 2, 3, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2,
    2, 2, 4, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 1, 3, 2, 2, 2, 2,
    3, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 3, 2,
    2, 2, 2, 2, 3, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3,
    3, 2, 3, 3, 2, 2, 3, 3,
};

extern u8 gCollisionResolvePass;
extern u8 gCollisionDeferredHit;
extern u8 gCollisionDeferredPush;

s32 collisionSpheresOverlap(s32, s32, s32, s32, s32, s32, s32, s32);
u8 func_80673708(s32, s32, s32, s32, CollisionBox *, CollisionBox *, s16 *, s16 *);

u8 actorCheckCollisionsAgainstActiveActors(Actor *self, s16 *arcMin, s16 *arcMax) {
    ActorSub140 *sub140;
    s32 pad78;
    s32 posX;
    s32 posY;
    s32 posZ;
    s32 radius;
    s32 i;
    s32 pad60;
    s16 pad5E;
    s16 pad5C;
    u8 pad5B;
    u8 ret;
    ActorEntry *entry;
    u8 hitMask;
    ModelNode *node;
    Actor *other;
    ActorSub140 *otherSub140;

    ret = 0;
    hitMask = 0;
    if (!(self->flags & 0x10)) {
        return 0;
    }
    sub140 = self->collision;
    posX = sub140->scaledX;
    posY = sub140->scaledY;
    posZ = sub140->scaledZ;
    radius = sub140->scaledRadius;
    gCollisionResolvePass = 0;
    i = 0; if (gActiveActorCount > 0) { entry = gActiveActors; do { // LAYOUT: same-line preheader steers ugen tie-break order
        other = entry->actor;
        otherSub140 = other->collision;
        if (!(other->flags & 0x2000) && sub140 != otherSub140 && other->collisionMode != 1 && (other->flags & 0x10)) {
            if (collisionSpheresOverlap(posX, posY, posZ, radius, otherSub140->scaledX, otherSub140->scaledY, otherSub140->scaledZ, otherSub140->scaledRadius)) {
                node = sub140->nodes;
                gCollisionDeferredHit = 0;
                if (other->renderFlags & 0x20) {
                    gCollisionDeferredPush = 0;
                } else {
                    gCollisionDeferredPush = 1;
                }
                while (node != NULL && gCollisionDeferredHit == 0) {
                    if (node->active != 0 && !(node->collisionSkipFlags & 2)) {
                        hitMask |= func_80673708(node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius, otherSub140->box_start, otherSub140->box_end, arcMin, arcMax);
                    }
                    node = node->next;
                }
                if (other->renderFlags & 0x20) {
                    self->hasArcBounds |= hitMask;
                }
                if (gCollisionDeferredHit != 0) {
                    ret |= actorCollisionReflectAndPush(self, other);
                }
            }
        }
        i++; entry++; } while (i < gActiveActorCount); } // LAYOUT: increments on the loop-test line keep the sw t5 in the bnez delay slot
    return ret;
}

typedef f32 CollisionMtxF[4][4];

extern s32 gCollisionPlanePointX;
extern s32 gCollisionPlanePointY;
extern s32 gCollisionPlanePointZ;
extern s32 gCollisionPlaneDist;
extern CollisionBox *gCollisionHitBox;

s32 func_806744A8(CollisionBox *, s32, s32, s32, s32);

u8 actorCollisionReflectAndPush(Actor *self, Actor *other) {
    f32 posX;
    f32 posY;
    u8 hitMode;
    CollisionMtxF otherMtx;
    CollisionMtxF invMtx;
    f32 posZ;
    s32 i;
    f32 padD0[1];
    f32 localPos[3];
    f32 ptX[3];
    f32 ptY[3];
    f32 ptZ[3];
    f32 localPts[3][3];
    ActorSub140 *selfBounds;
    ActorSub140 *otherBounds;

    hitMode = 0;
    selfBounds = self->collision;
    otherBounds = other->collision;
    if (func_806744A8(gCollisionHitBox, selfBounds->scaledX, selfBounds->scaledY, selfBounds->scaledZ, selfBounds->scaledRadius) == 0) {
        return 0;
    }
    if ((self->flags2 & 2) && (other->flags2 & 4)) {
        hitMode = 1;
    }
    if (actorCheckFacingTarget(self) == 0) {
        hitMode = 0;
    }
    if (other->flags2 & 8) {
        hitMode = 2;
    }
    selfBounds->hitBoxIndex = gCollisionHitBox - otherBounds->box_start;
    actorGetMatrix(otherBounds, otherMtx, gCollisionHitBox->mtxIndex);
    matrix4Invert(invMtx, otherMtx);
    if (other->renderFlags & 0x10) {
        posX = self->x;
        posY = self->y;
        posZ = self->z;
    } else {
        posX = (f32)gCollisionPlanePointX / 8;
        posY = (f32)gCollisionPlanePointY / 8;
        posZ = (f32)gCollisionPlanePointZ / 8;
    }
    if (!(self->flags & 0x800)) {
        guMtxXFMF(invMtx, posX, posY, posZ, &localPos[0], &localPos[1], &localPos[2]);
    } else {
        localPos[0] = selfBounds->hitBoxPosX;
        localPos[1] = selfBounds->hitBoxPosY;
        localPos[2] = selfBounds->hitBoxPosZ;
    }
    selfBounds->hitBoxPosX = localPos[0];
    selfBounds->hitBoxPosY = localPos[1];
    selfBounds->hitBoxPosZ = localPos[2];

    ptX[0] = (f32)gCollisionHitBox->x0 / 8;
    ptY[0] = (f32)gCollisionHitBox->y0 / 8;
    ptZ[0] = (f32)gCollisionHitBox->z0 / 8;
    ptX[1] = (f32)gCollisionHitBox->x1 / 8;
    ptY[1] = (f32)gCollisionHitBox->y1 / 8;
    ptZ[1] = (f32)gCollisionHitBox->z1 / 8;
    ptX[2] = (f32)gCollisionHitBox->x2 / 8;
    ptY[2] = (f32)gCollisionHitBox->y2 / 8;
    ptZ[2] = (f32)gCollisionHitBox->z2 / 8;

    for (i = 0; i < 3; i++) {
        guMtxXFMF(invMtx, ptX[i], ptY[i], ptZ[i], &localPts[i][0], &localPts[i][1], &localPts[i][2]);
    }

    selfBounds->hitNormalYaw = gCollisionHitBox->normalYaw;
    if (gCollisionHitBox->normalFlipped != 0) {
        selfBounds->hitNormalYaw -= 0x800;
    }
    if (selfBounds->hitNormalYaw < 0) {
        selfBounds->hitNormalYaw += 0x1000;
    }

    switch (hitMode) {
    case 2:
        if (self->collisionFlags & 1) {
            actorReflectCollisionAngle(self, gCollisionHitBox, selfBounds);
        }
    case 0:
        actorAppendCollisionHit(self, other, &localPos[0], &localPts[0][0], gCollisionHitBox->mtxIndex, gCollisionPlaneDist, actorGetCollisionThreshold(self));
        break;
    case 1:
        actorAppendSurfaceHit(self, other, self->yaw, (s16)(s32)self->speedXZ, &localPos[0], &localPts[0][0], gCollisionHitBox->mtxIndex, gCollisionPlaneDist, actorGetCollisionThreshold(self));
        if (actorIsTargetWithinAngle(gPlayerPadState[0].stickAngle, 400) && (f64)gPlayerPadState[0].stickMag > 30.0) {
            self->yaw = selfBounds->hitNormalYaw;
        }
        break;
    }
    return hitMode == 1;
}


extern u8 gGfxBufferIndex;
void actorGetMatrix(ActorSub140 *owner, CollisionMtxF dst, s8 mtxIndex) {
    u8 bufIdx;
    Mtx *mtx;

    if (gFrameCounter == owner->mtxFrame) {
        bufIdx = gGfxBufferIndex;
    } else {
        bufIdx = gGfxBufferIndex ^ 1;
    }
    mtx = owner->nodeMtx[bufIdx];
    if (mtxIndex == -1) {
        memcpy(dst, owner->modelMtxF, 0x40);
    } else {
        guMtxL2F(dst, &mtx[mtxIndex]);
    }
}

extern u8 D_807FB603;
extern u8 gCollisionHit;
extern PlayerStruct *gPlayerSlots;
extern u8 gCurrentPlayerIndex;
extern s16 gKongNormalWallContactOffsets[];
extern s16 gKongWallContactOffsets[];
extern s16 gCurrentCharacterIndex;

void func_80672E90(s32, s32, s32);
u8 func_806738D0(s32, s32, s32, s32, CollisionBox *, CollisionBox *);

void actorCollisionResolveSurfaceHit(Actor *self, Actor *other, f32 *pos, f32 *verts, s8 mtxIndex, s32 hitRadius, s32 maxClamp, u8 flag) {
    ActorSub140 *selfBounds;
    ActorSub140 *otherBounds;
    ModelNode *node;
    CollisionMtxF selfMtx;
    f32 worldX;
    f32 worldY;
    f32 worldZ;
    f32 triX[3];
    f32 triY[3];
    f32 triZ[3];
    f32 edge1[3];
    f32 edge2[3];
    f32 cross[3];
    f32 normal[3];
    f32 scale;
    f32 norm;
    s32 clamp;
    PlayerState *playerState;
    f32 scaledNormal[3];
    s32 i;
    f32 pushX;
    f32 pushZ;
    u8 hit;

    selfBounds = self->collision;
    otherBounds = other->collision;
    D_807FB603 = selfBounds->unkAC;
    gCollisionDeferredPush = 1;
    gCollisionResolvePass = 1;
    gCollisionHit = 0;
    func_80672E90(otherBounds->scaledX, otherBounds->scaledY, otherBounds->scaledZ);
    actorSetCameraBoundaryMode(other->actorType);
    if (flag != 0) {
        hit = func_80673708(otherBounds->scaledX, otherBounds->scaledY, otherBounds->scaledZ, hitRadius, selfBounds->box_start, selfBounds->box_end, &other->arcYawMin, &other->arcYawMax);
    } else {
        actorSetTargetAngleBounds(selfBounds->box_start + otherBounds->hitBoxIndex);
        if (!(self->renderFlags & 0x10)) {
            hit = func_806738D0(otherBounds->scaledX, otherBounds->scaledY, otherBounds->scaledZ, hitRadius, selfBounds->box_start, selfBounds->box_end);
        } else {
            hit = func_80673708(otherBounds->scaledX, otherBounds->scaledY, otherBounds->scaledZ, hitRadius, selfBounds->box_start, selfBounds->box_end, &other->arcYawMin, &other->arcYawMax);
        }
    }
    if ((*(u8 *)&flag != 0) && (gPlayerPadState[playerFindIndexByActor(other)].stickMag > 30.0)) { // FAKE: punned *(u8 *)&flag re-reads the u8 param from its stack home (lbu 343(sp) into t8, not a callee-saved copy)
        hit = 1;
    }
    if (hit != 0) {
        actorGetMatrix(selfBounds, selfMtx, mtxIndex);
        guMtxXFMF(selfMtx, pos[0], pos[1], pos[2], &worldX, &worldY, &worldZ);
        pushX = worldX;
        if (self->renderFlags & 0x10) {
            pushZ = worldZ;
        } else {
            for (i = 0; i < 3; i++) {
                guMtxXFMF(selfMtx, verts[i * 3], verts[i * 3 + 1], verts[i * 3 + 2], &triX[i], &triY[i], &triZ[i]);
            }
            edge1[0] = triX[2] - triX[0];
            edge1[1] = triY[2] - triY[0];
            edge1[2] = triZ[2] - triZ[0];
            edge2[0] = triX[1] - triX[0];
            edge2[1] = triY[1] - triY[0];
            edge2[2] = triZ[1] - triZ[0];
            cross[0] = (edge1[1] * edge2[2]) - (edge1[2] * edge2[1]);
            cross[1] = (edge1[2] * edge2[0]) - (edge1[0] * edge2[2]);
            cross[2] = (edge1[0] * edge2[1]) - (edge1[1] * edge2[0]);
            norm = sqrtf((cross[0] * cross[0]) + (cross[1] * cross[1]) + (cross[2] * cross[2]));
            normal[0] = cross[0] / norm;
            normal[1] = cross[1] / norm;
            normal[2] = cross[2] / norm;
            if (other->collisionFlags & 1) {
                scale = (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1 ? (f32)gKongNormalWallContactOffsets[gCurrentCharacterIndex] : (f32)gKongWallContactOffsets[gCurrentCharacterIndex]) / 8;
                playerState = other->customState;
                scaledNormal[0] = normal[0] * scale;
                scaledNormal[1] = normal[1] * scale;
                scaledNormal[2] = normal[2] * scale;
                playerState->wallContactX = worldX - scaledNormal[0];
                playerState->wallContactZ = worldZ - scaledNormal[2];
            }
            if (otherBounds->actorPushDist != 0) {
                clamp = gCollisionPlaneDist = otherBounds->actorPushDist + 5;
                if (maxClamp < clamp) {
                    clamp = gCollisionPlaneDist = maxClamp;
                }
            } else {
                clamp = gCollisionPlaneDist = hitRadius;
                if (clamp < 0xF) {
                    clamp = gCollisionPlaneDist = 0xF;
                }
                if (maxClamp < clamp) {
                    clamp = gCollisionPlaneDist = maxClamp;
                }
            }
            normal[0] *= (f32)clamp / 8;
            normal[1] *= (f32)clamp / 8;
            normal[2] *= (f32)clamp / 8;
            do {} while (0); // FAKE: splits BB so pushX/pushZ can reuse $f0 after the CSE'd division
            pushX = worldX - normal[0];
            pushZ = worldZ - normal[2];
            actorAppendCallbackS32(self, other, clamp);
        }
        actorAppendMoveTarget2D(self, other, pushX, pushZ, 1, 1);
        for (node = otherBounds->nodes; node != 0; node = node->next) {
            if (node->active != 0) {
                other->hasArcBounds |= func_80673708(node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius, selfBounds->box_start, selfBounds->box_end, &other->arcYawMin, &other->arcYawMax);
            }
        }
    } else {
        for (node = otherBounds->nodes; node != 0; node = node->next) {
            if (node->active != 0) {
                other->hasArcBounds |= func_80673708(node->scaledX, node->scaledY, node->scaledZ, node->scaledRadius, selfBounds->box_start, selfBounds->box_end, &other->arcYawMin, &other->arcYawMax);
            }
        }
    }
    other->collisionHit = gCollisionHit;
}

s32 actorIsTargetWithinAngle(s16 angle, s16 threshold) {
    s16 targetAngle;
    s16 diff;

    targetAngle = gCollisionHitBox->normalYaw;
    if (gCollisionHitBox->normalFlipped != 0) {
        targetAngle -= 0x800;
    }
    if (targetAngle < 0) {
        targetAngle += 0x1000;
    }
    diff = targetAngle - angle;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff >= 0x801) {
        diff = 0xFFF - diff;
    }
    if (diff < threshold) {
        return 1;
    }
    return 0;
}

s32 actorCheckFacingTarget(Actor *actor) {
    return actorIsTargetWithinAngle(actor->yaw, 400);
}
