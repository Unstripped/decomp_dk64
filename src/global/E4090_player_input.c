#include "common.h"
#include "actor.h"
#include "sched.h"
#include "proto/global/10E1D0_screen_transition.h"
#include "proto/global/117190_menu_transition.h"
#include "proto/global/119370_effect_grid.h"
#include "proto/global/11BC10_effect_update.h"
#include "proto/global/131B0_rumble.h"
#include "proto/global/133A90_prox_path.h"
#include "proto/global/135D30_flags.h"
#include "proto/global/13A7A0_n_sndplayer.h"
#include "proto/global/166A0_random.h"
#include "proto/global/17B90_anim_controller.h"
#include "proto/global/19A00_actor_script.h"
#include "proto/global/201B0_camera.h"
#include "proto/global/2DE90_screen_wipe.h"
#include "proto/global/36880_model_slot.h"
#include "proto/global/3C10_map_transition.h"
#include "proto/global/450_main_loop.h"
#include "proto/global/5650_timer_queue.h"
#include "proto/global/5E2F0_light.h"
#include "proto/global/69E60_actor_physics.h"
#include "proto/global/70FD0_collision_geometry.h"
#include "proto/global/7130_sfx.h"
#include "proto/global/7CA80_actor_manager.h"
#include "proto/global/89250_effect_spawn.h"
#include "proto/global/90D80_render_callbacks.h"
#include "proto/global/936B0_projectile.h"
#include "proto/global/CC800_player_setup.h"
#include "proto/global/CEAE0_player_update.h"
#include "proto/global/E4090_player_input.h"
#include "proto/global/EFDC0_player_state_enter.h"
#include "proto/global/F56F0_player_weapon.h"
#include "proto/global/FCCD0_slot_queue.h"


extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;
extern Actor *gPrimaryPlayerActor;
extern u8 gPlayerCount;
extern u8 gCurrentPlayerIndex;
extern PlayerState *gActivePlayerState;
extern s16 gCurrentCharacterIndex;

void playerHolsterGun(Actor *actor, PlayerState *state, u8 isFirstPerson) {
    s32 id;

    id = 0x4A;
    if (isFirstPerson) {
        id = 0x4C;
    }
    state->isHoldingObject = 0;
    actorScriptStartByIndex(actor, id);
}

void playerDrawGun(Actor *actor, PlayerState *state, u8 isFirstPerson) {
    s32 id;
    s32 a;

    id = 0x4B;
    a = 2;
    if (slotQueueGetValue(3, state->playerIndex)) {
        a = 3;
    }
    slotQueueUpdate(a, 0, 0);
    if (isFirstPerson) {
        id = 0x4D;
    }
    actorScriptStartByIndex(actor, id);
}

void playerToggleGun(Actor *actor, PlayerState *state, u8 isFirstPerson) {
    if (state->gunDrawn) {
        playerHolsterGun(actor, state, isFirstPerson);
    } else {
        playerDrawGun(actor, state, isFirstPerson);
    }
}

void mathAngleStepToward(s16 *angle, s16 target, s16 rate) {
    s16 delta;
    s16 dist;
    s32 absStep;
    s16 step;

    target &= 0xFFF;
    delta = target - *angle;
    if (delta != 0) {
        if (delta > 0) {
            dist = delta;
        } else {
            dist = -delta;
        }
        step = rate;
        delta = delta / dist;
        if (dist > 0x800) {
            dist = 0x1000 - dist;
            delta = delta * -1;
        }
        if (step > 0) {
            absStep = step;
        } else {
            absStep = -step;
        }
        if (dist < absStep) {
            *angle = target;
            return;
        }
        *angle = *angle + (delta * step);
        *angle &= 0xFFF;
    }
}

void mathAngleStepTowardThreshold(s16 *angle, s16 target, s16 step, s16 threshold) {
    s16 delta;
    s16 dist;

    target = target & 0xFFF;
    delta = target - *angle;
    if (delta != 0) {
        if (delta > 0) {
            dist = delta;
        } else {
            dist = -delta;
        }
        delta = delta & 0xFFF;
        if (dist > 0x800) {
            dist = 0x1000 - dist;
        }
        if (step >= dist) {
            *angle = target;
        } else if (threshold < delta) {
            *angle = *angle - step;
        } else {
            *angle = *angle + step;
        }
        *angle &= 0xFFF;
    }
}

void mathAngleStepForward(s16 *angle, s16 target, s16 step) {
    s16 delta;

    delta = target - *angle;
    if (delta != 0) {
        if (((s16) (delta & 0xFFF) + step) >= 0x1000) {
            *angle = target;
            return;
        }
        *angle = (*angle + step) & 0xFFF;
    }
}




typedef struct PlayerInputHandlers {
    void (*fn[17])(void);
} PlayerInputHandlers;

#define INPUT_MAX(a, b) ((a) > (b) ? (a) : (b))
#define INPUT_MIN(a, b) ((a) < (b) ? (a) : (b))


extern PlayerStruct *gPlayerSlots;
extern OSContPad *gCurrentContPad;
extern u16 gContPressedButtons;
u16 gButtonRemapTable[2] = { 0, 0 };
f32 sZInteractRadiusType3D = 30.0f;
f32 sLaneBrakeMaxSpeed = 10.0f;
f32 sLaneSteerScale = 1.7f;
f32 sHeldActorVineSpeed = 0.5f;
PlayerInputHandlers gPlayerInputHandlers[107] = {
    { {
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputUpdateStickSwimming, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerClearMoveTarget, playerInputRecordAPress, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputRecordAPress, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputRecordAPress, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandleCUpMode7, playerInputHandleCLeftEnterFirstPerson, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputRecordAPress, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickFacingYawSlow, playerInputHandleAButtonSlopeJump, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickFacingYawSlow, playerInputHandleAButtonSlopeJump, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputNoop, playerInputNoop,
        playerInputHandleCDownRotateMinus120, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandleCUpRotate120, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, aimUpdateFromStick, playerInputHandleAButtonAimRight, playerInputHandleBButtonAimLeft,
        playerInputHandleZButtonFire, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandleCUpLeaveFirstPerson, playerInputNoop, playerInputNoop, playerInputHandleCDownLeaveFirstPerson,
        playerInputPostUpdateFirstPerson,
    } },
    { {
        playerInputRequestPause, aimUpdateFromStick, playerInputHandleAButtonAimUp, playerInputHandleBButtonAimDown,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandleCUpLeaveFirstPersonInWater, playerInputNoop, playerInputNoop, playerInputHandleCDownLeaveFirstPersonInWater,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, aimUpdateFromStick, playerInputNoop, playerFireWeaponFirstPerson,
        playerInputHandleZButtonShoot, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandleCUpLeaveFirstPerson, playerInputNoop, playerInputNoop, playerInputHandleCDownLeaveFirstPerson,
        playerInputPostUpdateFirstPerson,
    } },
    { {
        playerInputRequestPause, aimUpdateFromStick, playerInputNoop, playerFireWeaponFirstPerson,
        playerInputHandleZButtonShoot, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandleCUpLeaveFirstPerson, cameraZoomOut, cameraZoomIn, playerInputHandleCDownLeaveFirstPerson,
        playerInputUpdateStickFirstPersonAim,
    } },
    { {
        playerInputRequestPause, aimUpdateFromStick, playerInputNoop, playerInputHandleBButtonFairyPhoto,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandleCUpLeaveFairyCamera, playerInputNoop, playerInputNoop, playerInputHandleCDownLeaveFairyCamera,
        playerInputPostUpdateFirstPerson,
    } },
    { {
        playerInputRequestPause, aimUpdateFromStick, playerInputNoop, playerInputHandleBButtonFairyPhotoInWater,
        playerInputHandleZButtonLeaveFairyCamera, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandleCUpLeaveFairyCamera, playerInputNoop, playerInputNoop, playerInputHandleCDownLeaveFairyCamera,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputNoop, playerInputHandleAButtonShopConfirm, playerInputHandleBButtonShopDecline,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonSlopeJump, playerInputHandleBButtonGun,
        playerInputHandleAButtonFire, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpCameraZoomIn, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonSlopeJump, playerInputHandleBButtonGun,
        playerInputHandleAButtonFire, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputNoop, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickFacingYaw, playerInputHandleAButtonSlopeJump, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickFacingYaw, playerInputHandleAButtonState0, playerInputRecordBPress,
        playerInputNoop, playerInputHandleAButtonState0, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickFacingYaw, playerInputHandleAButtonState17, playerInputRecordBPress,
        playerInputNoop, playerInputHandleAButtonState0, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardAngle, playerInputHandleAButtonJump, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonJump, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardAngle, playerInputHandleAButtonJump, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerTurnByStickX, playerInputHandleCannonBButton, playerFireWeaponIfOwned,
        playerInputHandleStickAction, playerInputStopSoundOnZRelease, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpCameraZoomIn, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonState61, playerFireWeaponIfOwned,
        playerInputHandleZButtonCrouch, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpCameraZoomIn, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonState61, playerInputHandlerCheckBAndFireWeapon,
        playerInputHandleZButtonCrouch, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpCameraZoomIn, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateMoveTargetWithDeadzone2, playerInputHandleAButtonState61, playerFireWeaponIfOwned,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputCheckZButtonResume,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpCameraZoomIn, playerInputQueueGunState5F, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateMoveTargetWithDeadzone2, playerInputNoop, playerFireWeaponIfOwned,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputRecordAPress, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardTarget, playerInputRecordAPress, playerInputHandleBButtonPunch,
        playerInputCheckEnterLongJump, playerInputClearVelocity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardTarget, playerInputCheckBButtonChargeCallback, playerInputHandleBButtonPunch,
        playerInputCheckEnterLongJump, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardTarget, playerInputRecordAPress, playerInputHandleBButtonGun,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardTarget, playerInputNoop, playerInputHandleBButtonGun,
        playerInputCheckEnterLongJump, playerInputHandlerResumeDecel, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardTarget, playerInputRecordAPress, playerFireWeaponIfOwned,
        playerInputNoop, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputRecordAPress, playerFireWeaponIfOwned,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputNoop, playerInputRecordAPress, playerInputHandleBButtonGun,
        playerInputCheckEnterLongJump, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputNoop, playerInputCheckBButtonChargeCallback, playerInputHandleBButtonGun,
        playerInputCheckEnterLongJump, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputRecordAPress, playerInputHandleBButtonPunch,
        playerInputCheckEnterLongJump, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputNoop, playerInputCheckBButtonChargeCallback, playerInputHandleBButtonPunch,
        playerInputCheckEnterLongJump, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardTarget, playerInputRecordAPress, playerInputHandleBButtonGun,
        playerInputCheckEnterLongJump, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputRecordAPress, playerInputHandleBButtonGun,
        playerInputCheckEnterLongJump, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardAngle, playerInputRecordAPress, playerInputHandleBButtonGun,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputNoop, playerInputRecordAPress, playerInputHandleBButtonGun,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputRecordAPress, playerInputHandleBButtonGun,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonSub17, playerInputHandleBButtonGun,
        playerInputHandleAButtonFire, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonSlopeJump, playerInputHandleBButtonGun,
        playerInputHandleAButtonFire, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputRecordAPress, playerFireWeaponIfOwned,
        playerInputNoop, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonSub17, playerInputHandleBButtonGun,
        playerInputNoop, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonSub61, playerFireWeaponIfOwned,
        playerInputHandleZButtonCrouch, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonSlopeJump, playerInputHandleBButtonGun,
        playerInputHandleAButtonFire, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardAngle, playerInputNoop, playerInputHandleBButtonGun,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputHandlerStartScript15,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputUpdateCannonAim, playerInputHandleZButtonState4B,
        playerInputHandleZButtonInteract, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpCameraZoomIn, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputUpdateCannonAim, playerInputHandleZButtonState4B,
        playerInputHandleZButtonInteract, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardTarget, playerInputRecordAPress, playerInputThrowHeldActor,
        playerInputNoop, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardAngle, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateFacingYawNormal, playerInputHandleAButtonSlopeJump, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateFacingYawOffset, playerInputHandleAButtonSlopeJump, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateMoveTargetClamped, playerInputHandleAButtonGravity, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputUpdateMoveTargetClamped, playerInputRecordAPress, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputHandleAButtonSlopeJump, playerInputHandleBButtonGun,
        playerInputHandlerNoop1, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputHandleAButtonSlopeJump, playerInputHandleBButtonGun,
        playerInputHandlerNoop1, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputHandleAButtonSlopeJump, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonSlopeJump, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputRecordAPress, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandleCUpCameraZoomIn, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateMoveTargetWithDeadzone2, playerInputHandleAButtonKong, playerInputHandleBButtonSpecial,
        playerInputCheckInstrumentPlayback, playerInputNoop, playerInputNoop, playerInputQueueCrouchCallback,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputQueueGunAimState60, playerInputHandlerCheckZAndTriggerState2C, playerInputHandleCDownFairyCamera,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateMoveTargetWithDeadzone, playerInputHandleAButtonKong, playerInputHandleBButtonSpecial,
        playerInputCheckInstrumentPlayback, playerInputNoop, playerInputNoop, playerInputQueueCrouchCallbackDirect,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputQueueGunAimState60, playerInputHandlerCheckZAndTriggerState2C, playerInputHandleCDownFairyCamera,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonState41, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputQueueCrouchCallback,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputNoop,
        playerInputHandleCUpCameraZoomIn, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerUpdateMoveTargetFromStick, playerInputRecordAPress, playerInputNoop,
        playerInputCheckEnterLongJump, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawTowardTarget, playerInputRecordAPress, playerInputNoop,
        playerInputCheckEnterLongJump, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerStepYawAndProjectSpeed, playerInputRecordAPress, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        (void (*)(void))playerInputPostUpdate,
    } },
    { {
        playerInputRequestPause, playerInputCalculateStickForwardSpeed, playerInputHandleAButtonSlopeJump, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputNoop, playerInputNoop, playerInputInitDashParams,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickTurnYaw, playerInputHandleAButtonJumpQueue, playerInputSurfaceSwimBButtonNoop,
        playerInputHandleCDownCameraSnap, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpEnterFirstPersonInWater, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickTurnYaw, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpEnterFirstPersonInWater, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputCalculateStickTurnRate, playerInputCheckAButtonScriptTrigger, playerInputHandleBButtonComboPunch,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputCalculateTurnStep, playerInputCheckAButtonScriptTrigger, playerInputHandleBButtonComboPunch,
        playerInputHandleCDownFairyCheck, playerInputNoop, playerInputNoop, playerInputSetCharacterDecelRate,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpEnterFirstPersonInWater, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputCalculateTurnStep, playerInputNoop, playerInputHandleBButtonDashAttack,
        playerInputHandleCDownFairyCheck, playerInputNoop, playerInputNoop, playerInputSetCharacterDecelRate,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpEnterFirstPersonInWater, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputCalculateTurnStep, playerInputHandleBButtonRollingAttack, playerInputHandleBButtonDashAttack,
        playerInputHandleCDownFairyCheck, playerInputNoop, playerInputNoop, playerInputSetCharacterDecelRate,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpEnterFirstPersonInWater, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputCalculateTurnStep, playerInputHandleBButtonSlideAttack, playerInputHandleBButtonDashAttack,
        playerInputHandleCDownFairyCheck, playerInputSetSubstate6, playerInputNoop, playerInputSetCharacterDecelRate,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpEnterFirstPersonInWater, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputStepTurnFacingAngle, playerInputHandleBButtonDiveAttack, playerInputHandleBButtonAttack,
        playerInputHandleCDownFairyCheck, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpEnterFirstPersonInWater, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputStepTurnFacingAngle, playerInputHandleAButtonSuperJump, playerInputHandleBButtonUnderwaterCharge,
        playerInputHandleCDownFairyCheck, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpEnterFirstPersonInWater, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputCalculateTurnStep, playerInputHandleAButtonSuperJump, playerInputHandleBButtonUnderwaterCharge,
        playerInputHandleCDownFairyCheck, playerInputNoop, playerInputNoop, playerInputResetDecelRate,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpEnterFirstPersonInWater, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputCalculateStickTurnRate, playerInputHandleAButtonSuperJump2, playerInputHandleBButtonUnderwaterCharge,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputHandlerNoop3, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerPathMoveByStickY, playerInputHandleAButtonSub58, playerInputNoop,
        playerInputInitCannonLaunch, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerFlipHeading180, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerPathMoveByStickYAndTurn, playerInputHandleAButtonSub5A, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputNoop,
        playerInputHandleCUpCameraZoomIn, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerSetMoveSpeedFromStickX, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputRegisterAnimatedEffect, playerInputSetClimbTimer20, playerInputSetClimbTimer20,
        playerInputSetClimbTimer100, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputSetClimbTimer50,
    } },
    { {
        playerInputRequestPause, playerInputUpdateLadderState, playerInputHandleAButtonJumpOff, playerInputNoop,
        playerInputHandleZButtonRideCrouch, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonFixedLook, playerInputNoop, playerInputHandleRButtonFixedLook,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputUpdateLadderState, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputHandleZButtonReleaseRideCrouch,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputUpdateLadderState, playerInputRecordAPress, playerInputNoop,
        playerInputNoop, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputStepLadderClimb, playerInputHandleAButtonLadderJump, playerInputNoop,
        playerInputHandleZButtonRideCrouch, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonFixedLook, playerInputNoop, playerInputHandleRButtonFixedLook,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputCheckLadderTopOrBottom, playerInputHandleAButtonLadderJump, playerInputNoop,
        playerInputHandleZButtonRideCrouch, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonFixedLook, playerInputNoop, playerInputHandleRButtonFixedLook,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputStepLane, playerInputHandleAButtonLaneRaceFire, playerInputNoop,
        playerInputHandleZButtonLaneRaceThrottle, playerInputNoop, playerInputNoop, playerInputHandleZButtonReleaseLaneRaceThrottle,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputNoop, playerInputHandleAButtonReelGame, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputPlayHeldActorClimbSfx, playerInputHandleAButtonVehicleJump, playerInputNoop,
        playerInputScaleHeldActorVineClimb, playerInputNoop, playerInputNoop, playerInputHandleZButtonReleaseVehicleThrottle,
        playerInputNoop, playerInputHandleRButtonVehicleSharpTurn, playerInputNoop, playerInputHandleRButtonReleaseVehicleSharpTurn,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputUpdateHeldActorVineClimb, playerInputNoop, playerInputSetHeldActorVineSpeed,
        playerInputScaleHeldActorVineClimb, playerInputNoop, playerInputClearHeldActorVineSpeed, playerInputHandleZButtonReleaseVehicleThrottle,
        playerInputNoop, playerInputHandleRButtonVehicleSharpTurn, playerInputNoop, playerInputHandleRButtonReleaseVehicleSharpTurn,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputWiggleOffStatusEffect, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickMoveTarget, playerInputHandleAButtonGroundJump, playerInputHandleBButtonPulse,
        playerInputNoop, playerInputSetBaseGravity, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickTurnYawFast, playerInputDiveFromSurface, playerInputHandleBButtonSurfaceCharge,
        playerInputDiveFromSurface, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputHandleRButtonCameraLock, playerInputNoop, playerInputHandleRButtonReleaseCameraLock,
        playerInputHandleCUpEnterFirstPersonInWater, playerInputCamRotateLeft, playerInputCamRotateRight, playerInputCycleCameraZoom,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickFacingYawSlow, playerInputRecordAPress, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputCalculateTurnStep, playerInputRecordAPress, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
    { {
        playerInputRequestPause, playerInputUpdateStickFacingYawSlow, playerInputRecordAPress, playerInputRecordBPress,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop, playerInputNoop, playerInputNoop, playerInputNoop,
        playerInputNoop,
    } },
};

s32 playerInputUpdate(s32 handlerSet) {
    f32 minSq;
    f32 maxSq;
    f32 tmp;
    f32 mag;
    s32 pad;
    s32 i;
    s32 prevState;
    s16 angle;

    prevState = gActivePlayerActor->state;
    gPlayerPadState[gCurrentPlayerIndex].heldButtons = inputRemapButtons(gCurrentContPad->button, gButtonRemapTable);
    gPlayerPadState[gCurrentPlayerIndex].pressedButtons = inputRemapButtons(gContPressedButtons, gButtonRemapTable);
    if (gActivePlayerState->stateFlags2 & 0x20) {
        gPlayerPadState[gCurrentPlayerIndex].heldButtons = 0;
        gPlayerPadState[gCurrentPlayerIndex].pressedButtons = 0;
    }
    gCurrentContPad->stick_x = INPUT_MIN(INPUT_MAX(gCurrentContPad->stick_x, -80), 80);
    gCurrentContPad->stick_y = INPUT_MIN(INPUT_MAX(gCurrentContPad->stick_y, -80), 80);
    gPlayerPadState[gCurrentPlayerIndex].stickX = gCurrentContPad->stick_x;
    gPlayerPadState[gCurrentPlayerIndex].stickY = gCurrentContPad->stick_y;
    if (gActivePlayerState->stateFlags2 & 0x20) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickY = 0;
    }
    if (gActivePlayerState->stateFlags & 0x100) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = gPlayerPadState[gCurrentPlayerIndex].stickX * 0.5;
        gPlayerPadState[gCurrentPlayerIndex].stickY = gPlayerPadState[gCurrentPlayerIndex].stickY * 0.5;
    }
    if (gActivePlayerState->stateFlags & 0x80) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = -gPlayerPadState[gCurrentPlayerIndex].stickX;
        gPlayerPadState[gCurrentPlayerIndex].stickY = -gPlayerPadState[gCurrentPlayerIndex].stickY;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickX > 0) {
        gPlayerPadState[gCurrentPlayerIndex].stickAbsX = gPlayerPadState[gCurrentPlayerIndex].stickX;
    } else {
        gPlayerPadState[gCurrentPlayerIndex].stickAbsX = -gPlayerPadState[gCurrentPlayerIndex].stickX;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickY > 0) {
        gPlayerPadState[gCurrentPlayerIndex].stickAbsY = gPlayerPadState[gCurrentPlayerIndex].stickY;
    } else {
        gPlayerPadState[gCurrentPlayerIndex].stickAbsY = -gPlayerPadState[gCurrentPlayerIndex].stickY;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsX < 5 && gPlayerPadState[gCurrentPlayerIndex].stickAbsY < 5) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickAbsX = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickY = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickAbsY = 0;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsX < 2) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickAbsX = 0;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsY < 2) {
        gPlayerPadState[gCurrentPlayerIndex].stickY = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickAbsY = 0;
    }
    minSq = gPlayerPadState[gCurrentPlayerIndex].stickAbsX * gPlayerPadState[gCurrentPlayerIndex].stickAbsX;
    maxSq = gPlayerPadState[gCurrentPlayerIndex].stickAbsY * gPlayerPadState[gCurrentPlayerIndex].stickAbsY;
    mag = sqrtf(minSq + maxSq);
    if (maxSq < minSq) {
        tmp = minSq;
        minSq = maxSq;
        maxSq = tmp;
    }
    if (maxSq != 0.0f) {
        tmp = 1.0 - (minSq / maxSq) * 0.15;
        mag *= tmp;
    }
    if (mag > 70.0f) {
        mag = 70.0f;
    }
    gPlayerPadState[gCurrentPlayerIndex].stickMagDelta = mag - gPlayerPadState[gCurrentPlayerIndex].stickMag;
    gPlayerPadState[gCurrentPlayerIndex].stickMag = mag;
    if (mag != 0.0f) {
        gPlayerPadState[gCurrentPlayerIndex].stickHeldFrames = 0;
        gPlayerPadState[gCurrentPlayerIndex].stickMagNorm = (mag - 5.0f) / 65.0f;
    } else {
        gPlayerPadState[gCurrentPlayerIndex].stickMagNorm = 0.0f;
        gPlayerPadState[gCurrentPlayerIndex].stickHeldFrames++;
    }
    if (mag != 0.0f) {
        angle = mathAtan2(gPlayerPadState[gCurrentPlayerIndex].stickX, -gPlayerPadState[gCurrentPlayerIndex].stickY) * 4096.0f / 6.2831855f;
        gPlayerPadState[gCurrentPlayerIndex].stickAngle = (gPlayerSlots[gCurrentPlayerIndex].camYawInt + angle) & 0xFFF;
    } else {
        angle = gPlayerPadState[gCurrentPlayerIndex].stickAngleHistory[0];
    }
    for (i = 3; i != 0; i--) {
        gPlayerPadState[gCurrentPlayerIndex].stickAngleHistory[i] = gPlayerPadState[gCurrentPlayerIndex].stickAngleHistory[i - 1];
        gPlayerPadState[gCurrentPlayerIndex].stickMagHistory[i] = gPlayerPadState[gCurrentPlayerIndex].stickMagHistory[i - 1];
    }
    gPlayerPadState[gCurrentPlayerIndex].stickAngleHistory[0] = angle;
    gPlayerPadState[gCurrentPlayerIndex].stickMagHistory[0] = mag;
    gPlayerInputHandlers[handlerSet].fn[1]();
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x1000) {
        gPlayerInputHandlers[handlerSet].fn[0]();
    }
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x8000) {
        gPlayerInputHandlers[handlerSet].fn[2]();
    } else {
        gPlayerInputHandlers[handlerSet].fn[5]();
    }
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x4000) {
        gPlayerInputHandlers[handlerSet].fn[3]();
    } else {
        gPlayerInputHandlers[handlerSet].fn[6]();
    }
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) {
        gPlayerInputHandlers[handlerSet].fn[4]();
    } else {
        gPlayerInputHandlers[handlerSet].fn[7]();
    }
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x10) {
        gPlayerInputHandlers[handlerSet].fn[9]();
    } else {
        gPlayerInputHandlers[handlerSet].fn[11]();
    }
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x20) {
        gPlayerInputHandlers[handlerSet].fn[8]();
    }
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 8) {
        gPlayerInputHandlers[handlerSet].fn[12]();
    }
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 4) {
        gPlayerInputHandlers[handlerSet].fn[15]();
    }
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 2) {
        gPlayerInputHandlers[handlerSet].fn[13]();
    }
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 1) {
        gPlayerInputHandlers[handlerSet].fn[14]();
    }
    gPlayerInputHandlers[handlerSet].fn[16]();
    return gActivePlayerActor->state - prevState;
}

u16 inputRemapButtons(u16 buttons, u16 *map) {
    u32 mask;
    u16 seen;
    u16 mapped;
    u32 ghost0;
    u32 ghost1;

    mask = *map;
    seen = 0;
    mapped = 0;
    if (mask != 0) {
        ghost0 = mask; // FAKE: pre-loop def, holds a0 across the loop so buttons spills and the mask load takes t0
        do {
            ghost1 = seen; // FAKE: loop-head def, holds a3 against the mask load (steers its colour to t0)
            seen |= mask;
            if (ghost1) {} // FAKE: dead test keeping ghost1 a coloured web
            map++;
            if ((u32)mask & buttons) {} // FAKE: makes the and-result a uopt candidate
            if (ghost0) {} // FAKE: dead test keeping ghost0 a coloured web
            if ((u32)mask & buttons) {
                mapped |= map[0];
            }
            mask = map[1];
            map++;
        } while (mask != 0);
    }
    return mapped | (buttons & ~seen);
}


f32 mathScaleByAngleDeltaCos(f32 value, s16 from, s16 to) {
    return mathCosF(to - from) * value;
}


void playerProjectMoveSpeedOntoAngle(s16 angle) {
    f32 speed;

    speed = mathScaleByAngleDeltaCos(gActivePlayerState->maxSpeed, gActivePlayerState->targetYaw, angle);
    if (speed > 0.0f) {
        gActivePlayerState->maxSpeed = speed;
    } else {
        gActivePlayerState->maxSpeed = 0.0f;
    }
    gActivePlayerState->targetYaw = angle;
}

void playerClearMoveTarget(void) {
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->targetYaw = gCurrentActor->yaw;
}


void playerUpdateMoveTargetFromStick(void) {
    f32 prevSpeed;
    f32 speed;
    PadInputState *pad;

    speed = gActivePlayerState->targetSpeed;
    if (gActivePlayerState->chargeTimer == 0) {
        speed = speed * 0.5;
    }
    if (gActivePlayerState->breathTimer != 0) {
        speed = speed * 0.5;
    }
    pad = &gPlayerPadState[gCurrentPlayerIndex];
    if ((pad->stickMag != 0.0f) && !(gActivePlayerState->stateFlags2 & 8)) {
        prevSpeed = gActivePlayerState->stopSpeed;
        gActivePlayerState->maxSpeed = (pad->stickMagNorm * (speed - prevSpeed)) + prevSpeed;
        gActivePlayerState->targetYaw = gPlayerPadState[gCurrentPlayerIndex].stickAngle;
        return;
    }
    gActivePlayerState->maxSpeed = 0.0f;
    gActivePlayerState->targetYaw = gCurrentActor->yaw;
}


void playerInputUpdateStickFacingYaw(void) {
    f32 dist;
    f32 scale;
    s32 delta;

    playerUpdateMoveTargetFromStick();
    scale = gPlayerPadState[gCurrentPlayerIndex].stickMagNorm;
    if (scale < 0.3) {
        scale = 0.3f;
    }
    delta = gCurrentActor->moveYaw - gActivePlayerState->targetYaw;
    if (delta > 0) {
        dist = delta;
    } else {
        dist = -delta;
    }
    if (dist > 2048.0f) {
        dist = 4096.0f - dist;
    }
    if (dist > 400.0f) {
        dist = 400.0f;
    }
    dist = dist * 0.2;
    mathAngleStepToward(&gCurrentActor->moveYaw, gActivePlayerState->targetYaw, (s16)(dist * scale));
}

void playerInputUpdateStickFacingYawSlow(void) {
    f32 dist;
    f32 scale;
    s32 delta;

    playerUpdateMoveTargetFromStick();
    scale = gPlayerPadState[gCurrentPlayerIndex].stickMagNorm;
    if (scale < 0.3) {
        scale = 0.3f;
    }
    delta = gCurrentActor->moveYaw - gActivePlayerState->targetYaw;
    if (delta > 0) {
        dist = delta;
    } else {
        dist = -delta;
    }
    if (dist > 2048.0f) {
        dist = 4096.0f - dist;
    }
    if (dist > 400.0f) {
        dist = 400.0f;
    }
    dist = dist * (gActivePlayerState->turnRate / 400.0);
    mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, (s16)(dist * scale));
}

f32 inputLerpByStickAbsX(f32 from, f32 to) {
    f32 t;
    u8 stickAbs;

    stickAbs = gPlayerPadState[gCurrentPlayerIndex].stickAbsX;
    if (stickAbs) {
        if (stickAbs >= 0x47) {
            t = 70.0f;
        } else {
            t = (s32)stickAbs;
        }
        t -= 2.0f;
        t /= 68.0f;
        return ((to - from) * t) + from;
    }
    return 0.0f;
}

f32 inputLerpByStickAbsY(f32 from, f32 to) {
    f32 t;
    u8 stickAbs;

    stickAbs = gPlayerPadState[gCurrentPlayerIndex].stickAbsY;
    if (stickAbs) {
        if (stickAbs >= 0x47) {
            t = 70.0f;
        } else {
            t = (s32)stickAbs;
        }
        t -= 2.0f;
        t /= 68.0f;
        return ((to - from) * t) + from;
    }
    return 0.0f;
}

void playerInputUpdateStickMoveTarget(void) {
    f32 magDelta;
    f32 dist;
    f32 scale;
    s32 delta;
    PadInputState *pad;

    playerUpdateMoveTargetFromStick();
    pad = &gPlayerPadState[gCurrentPlayerIndex];
    magDelta = pad->stickMagDelta;
    if (magDelta > 0.0f) {
        scale = magDelta;
    } else {
        scale = -magDelta;
    }
    if (scale < 14.0f) {
        scale = (pad->stickMagNorm * 0.7) + 0.3;
        delta = gCurrentActor->yaw - gActivePlayerState->targetYaw;
        if (delta > 0) {
            dist = delta;
        } else {
            dist = -delta;
        }
        if (dist > 2048.0f) {
            dist = 4096.0f - dist;
        }
        if (dist > 400.0f) {
            dist = 400.0f;
        }
        dist = dist * (gActivePlayerState->turnRate / 400.0);
        mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, (s16)(dist * scale));
    }
}

void playerStepYawTowardTarget(void) {
    playerUpdateMoveTargetFromStick();
    mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->targetYaw, gActivePlayerState->turnRate);
}

void playerStepYawTowardAngle(void) {
    playerUpdateMoveTargetFromStick();
    mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, gActivePlayerState->turnRate);
    gActivePlayerState->maxSpeed = 0.0f;
}

void playerInputUpdateFacingYawNormal(void) {
    s16 targetYaw;

    if (gCurrentActor->floorTiltPitch < 0x3C7) {
        targetYaw = gCurrentActor->floorTiltYaw + 0x800;
    } else {
        targetYaw = gCurrentActor->moveYaw + 0x800;
    }
    mathAngleStepToward(&gCurrentActor->yaw, targetYaw, gActivePlayerState->turnRate / 4);
    gActivePlayerState->maxSpeed = 0.0f;
}

void playerInputUpdateFacingYawOffset(void) {
    s16 targetYaw;

    if (gCurrentActor->floorTiltPitch < 0x3C7) {
        targetYaw = gCurrentActor->floorTiltYaw;
    } else {
        targetYaw = gCurrentActor->moveYaw;
    }
    mathAngleStepToward(&gCurrentActor->yaw, targetYaw, gActivePlayerState->turnRate / 4);
    gActivePlayerState->maxSpeed = 0.0f;
}



extern f32 gKongPathForwardMinSpeeds[];
extern f32 gKongPathForwardMaxSpeeds[];
extern f32 gKongPathBackMinSpeeds[];
extern f32 gKongPathBackMaxSpeeds[];
extern f32 gKongLedgeShimmyMinSpeeds[];
extern f32 gKongLedgeShimmyMaxSpeeds[];
extern u16 *gActorScriptIndexTable;


void playerInputUpdateMoveTargetClamped(void) {
    f32 dist;
    s16 moveYaw;
    s32 delta;
    PadInputState *pad;

    playerUpdateMoveTargetFromStick();
    moveYaw = gCurrentActor->moveYaw;
    delta = gCurrentActor->yaw - moveYaw;
    if (delta > 0) {
        dist = delta;
    } else {
        dist = -delta;
    }
    if (dist > 2048.0f) {
        dist = 4096.0f - dist;
    }
    if (dist > 400.0f) {
        dist = 400.0f;
    }
    dist = dist * (0.25 + 0.75 * (gCurrentActor->speedXZ / gActivePlayerState->targetSpeed));
    if (dist > 1.0f) {} // FAKE: keeps the scaled dist chain alive (Q0200)
    mathAngleStepToward(&gCurrentActor->yaw, moveYaw, gActivePlayerState->turnRate / 4);
    if (gCurrentActor->state != 0x14) {
        if (gCurrentActor->state == 0xF && (gCurrentActor->sub4->model->animId == 0x1F2 || gCurrentActor->sub4->model->animId == 0x1B3)) {
            pad = &gPlayerPadState[gCurrentPlayerIndex];
            if (pad->stickX < -0x1E) {
                actorScriptStartByIndex(gCurrentActor, 0x61);
                gCurrentActor->state = 0x10;
                gCurrentActor->subState = 0;
            } else if (pad->stickX >= 0x1F) {
                actorScriptStartByIndex(gCurrentActor, 0x5F);
                gCurrentActor->state = 0x11;
                gCurrentActor->subState = 0;
            } else if (pad->stickY >= 0x1F) {
                actorScriptStartByIndex(gCurrentActor, 0x63);
                gCurrentActor->state = 0x12;
                gCurrentActor->subState = 0;
            } else if (pad->stickY < -0x1E) {
                actorScriptStartByIndex(gCurrentActor, 0x65);
                gCurrentActor->state = 0x13;
                gCurrentActor->subState = 0;
            }
        }
        pad = &gPlayerPadState[gCurrentPlayerIndex];
        if ((pad->stickX < 0x1E && gCurrentActor->state == 0x11) || (pad->stickY >= -0x1D && gCurrentActor->state == 0x13) || (pad->stickY < 0x1E && gCurrentActor->state == 0x12) || (pad->stickX >= -0x1D && gCurrentActor->state == 0x10)) {
            if (gPlayerCharacterId[gCurrentPlayerIndex] == 2 && gCurrentActor->state != 0x12) {
                actorScriptStart(gCurrentActor, 0x191);
            } else if (gCurrentActor->subState == 1) {
                switch (gCurrentActor->state) {
                    case 0x11:
                        actorScriptStartByIndex(gCurrentActor, 0x60);
                        break;
                    case 0x10:
                        actorScriptStartByIndex(gCurrentActor, 0x62);
                        break;
                    case 0x12:
                        actorScriptStartByIndex(gCurrentActor, 0x64);
                        break;
                    case 0x13:
                        actorScriptStartByIndex(gCurrentActor, 0x66);
                        break;
                }
            } else {
                actorScriptStartByIndex(gCurrentActor, 0x68);
            }
            gCurrentActor->state = 0xF;
            gCurrentActor->subState = 0;
        }
    }
}

void playerInputUpdateMoveTargetWithDeadzone(void) {
    f32 dist;
    f32 scale;
    s32 delta;

    playerUpdateMoveTargetFromStick();
    if (gActivePlayerState->maxSpeed != 0.0f) {
        scale = gPlayerPadState[gCurrentPlayerIndex].stickMagNorm;
        scale = scale * scale;
        if (scale < 0.2) {
            scale = 0.2f;
        }
        delta = gCurrentActor->yaw - gActivePlayerState->targetYaw;
        if (delta > 0) {
            dist = delta;
        } else {
            dist = -delta;
        }
        if (dist > 2048.0f) {
            dist = 4096.0f - dist;
        }
        if (dist > 400.0f) {
            dist = 400.0f;
        }
        dist = dist * (gActivePlayerState->turnRate / 400.0);
        mathAngleStepToward(&gCurrentActor->yaw, gActivePlayerState->targetYaw, (s16)(dist * scale));
    }
}

void playerTurnByStickX(void) {
    f32 turn;
    f32 scale;
    s32 delta;
    PadInputState *pad;

    playerUpdateMoveTargetFromStick();
    if (gActivePlayerState->maxSpeed != 0.0f) {
        pad = &gPlayerPadState[gCurrentPlayerIndex];
        scale = pad->stickMagNorm; // FAKE: dead copy of the sibling's scaled turn (playerInputUpdateMoveTargetWithDeadzone2), this scale chain through the turnRate/scale store below, overwritten by the stick term; the deleted stickMagNorm read and 0.2 compare split the block after the pad address (&gCurrentActor in a3 after it, pad in a1), and the store's read of turn keeps the 400 compare (Q0200)
        scale = scale * scale;
        if (scale < 0.2) {
            scale = 0.2f;
        }
        delta = gCurrentActor->yaw - gActivePlayerState->targetYaw;
        if (delta > 0) {
            turn = delta;
        } else {
            turn = -delta;
        }
        if (turn > 2048.0f) {
            turn = 4096.0f - turn;
        }
        if (turn > 400.0f) {
            turn = 400.0f;
        }
        turn = turn * (gActivePlayerState->turnRate / 400.0) * scale;
        turn = (pad->stickX * gActivePlayerState->turnRate) / 400;
        gCurrentActor->yaw -= turn;
        if (gCurrentActor->yaw >= 0x1000) {
            gCurrentActor->yaw -= 0x1000;
        }
        if (gCurrentActor->yaw < 0) {
            gCurrentActor->yaw += 0x1000;
        }
    }
    pad = &gPlayerPadState[gCurrentPlayerIndex];
    if (!(pad->heldButtons & 0x2000)) {
        gActivePlayerState->aimPitch = pad->stickY * 0xCC * 0.6 + 63000.0;
    }
}

void playerInputUpdateMoveTargetWithDeadzone2(void) {
    f32 turn;
    f32 scale;
    s16 targetYaw;
    u16 script;

    playerUpdateMoveTargetFromStick();
    if (gActivePlayerState->maxSpeed != 0.0f && !gCurrentActor->speedXZ) {
        scale = gPlayerPadState[gCurrentPlayerIndex].stickMagNorm;
        scale = scale * scale;
        if (scale < 0.2) {
            scale = 0.2f;
        }
        targetYaw = gActivePlayerState->targetYaw;
        turn = gCurrentActor->yaw - targetYaw;
        if (turn >= 2048.0f) {
            turn -= 4096.0f;
        }
        if (turn <= -2048.0f) {
            turn += 4096.0f;
        }
        if (turn > 400.0f) {
            turn = 400.0f;
        }
        if (turn < -400.0f) {
            turn = -400.0f;
        }
        turn = turn * (gActivePlayerState->turnRate / 400.0);
        turn = turn * scale;
        if (turn > 0.0f) {
            scale = turn;
        } else {
            scale = -turn;
        }
        mathAngleStepToward(&gCurrentActor->yaw, targetYaw, (s16)scale);
        if (turn != 0.0f) {
            if (gCurrentActor->state != 0x3C) {
                if (gCurrentActor->state == 0x62) {
                    script = gActorScriptIndexTable[gCurrentActor->actorType + 0x23C];
                    if (gCurrentActor->sub4->animId != script) {
                        actorScriptStart(gCurrentActor, script);
                    }
                    scriptSetActorRampTarget(gCurrentActor, turn / 80.0, 0.0f);
                }
            } else {
                script = gActorScriptIndexTable[gCurrentActor->actorType + 0x52];
                if (gCurrentActor->sub4->animId != script) {
                    actorScriptStart(gCurrentActor, script);
                }
                scriptSetActorRampTarget(gCurrentActor, turn / 80.0, 0.0f);
            }
        }
    } else {
        if (gCurrentActor->state != 0x3C) {
            if (gCurrentActor->state == 0x62) {
                script = gActorScriptIndexTable[gCurrentActor->actorType + 0x243];
                if (gCurrentActor->sub4->animId != script) {
                    actorScriptStart(gCurrentActor, script);
                }
            }
        } else if (gCurrentActor->subState == 1) {
            script = gActorScriptIndexTable[gCurrentActor->actorType + 0x4B];
            if (gCurrentActor->sub4->animId != script) {
                actorScriptStart(gCurrentActor, script);
            }
        }
    }
    gActivePlayerState->maxSpeed = 0.0f;
}

void playerPathMoveByStickYAndTurn(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].stickY < 0) {
        gActivePlayerState->maxSpeed = inputLerpByStickAbsY(gKongPathBackMinSpeeds[gCurrentCharacterIndex], gKongPathBackMaxSpeeds[gCurrentCharacterIndex]);
    } else {
        gActivePlayerState->maxSpeed = inputLerpByStickAbsY(gKongPathForwardMinSpeeds[gCurrentCharacterIndex], gKongPathForwardMaxSpeeds[gCurrentCharacterIndex]);
    }
    if (gActivePlayerState->maxSpeed != 0.0f) {
        gActivePlayerState->moveDir = gActivePlayerState->maxSpeed > 0.0f ? 1 : -1;
    } else {
        gActivePlayerState->moveDir = 0;
    }
    proxPathAdvance(gPlayerPadState[gCurrentPlayerIndex].stickY / 80.0);
    gCurrentActor->yaw += gPlayerPadState[gCurrentPlayerIndex].stickX;
    gCurrentActor->yaw &= 0xFFF;
    playerClampYawToArc();
}

void playerPathMoveByStickY(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].stickY < 0) {
        gActivePlayerState->maxSpeed = inputLerpByStickAbsY(gKongPathBackMinSpeeds[gCurrentCharacterIndex], gKongPathBackMaxSpeeds[gCurrentCharacterIndex]);
    } else {
        gActivePlayerState->maxSpeed = inputLerpByStickAbsY(gKongPathForwardMinSpeeds[gCurrentCharacterIndex], gKongPathForwardMaxSpeeds[gCurrentCharacterIndex]);
    }
    if (gActivePlayerState->maxSpeed != 0.0f) {
        gActivePlayerState->moveDir = gActivePlayerState->maxSpeed > 0.0f ? 1 : -1;
    } else {
        gActivePlayerState->moveDir = 0;
    }
    proxPathAdvance(gPlayerPadState[gCurrentPlayerIndex].stickY / 80.0);
}

void playerClampYawToArc(void) {
    s16 lo;
    s16 distLo;
    s16 hi;
    s16 cur;
    s32 outside = 0;

    hi = gActivePlayerState->pathYawMax;
    lo = gActivePlayerState->pathYawMin;
    if (lo < hi) {
        cur = gCurrentActor->yaw;
        if (cur < lo || hi < cur) {
            outside = 1;
        }
    } else {
        cur = gCurrentActor->yaw;
        if (hi < cur && cur < lo) {
            outside = 1;
        }
    }
    if (outside) {
        distLo = mathAngleDistance(cur, lo);
        if (distLo < mathAngleDistance(gCurrentActor->yaw, gActivePlayerState->pathYawMax)) {
            gCurrentActor->yaw = gActivePlayerState->pathYawMin;
        } else {
            gCurrentActor->yaw = gActivePlayerState->pathYawMax;
        }
    }
}

void playerSetMoveSpeedFromStickX(void) {
    f32 v = inputLerpByStickAbsX(gKongLedgeShimmyMinSpeeds[gCurrentCharacterIndex], gKongLedgeShimmyMaxSpeeds[gCurrentCharacterIndex]);

    if (gPlayerPadState[gCurrentPlayerIndex].stickX < 0) {
        gActivePlayerState->maxSpeed = -v;
        gActivePlayerState->moveDir = -1;
    } else {
        gActivePlayerState->maxSpeed = v;
        if (v != 0.0f) {
            gActivePlayerState->moveDir = 1;
        } else {
            gActivePlayerState->moveDir = 0;
        }
    }
}

void playerStepYawAndProjectSpeed(void) {
    playerUpdateMoveTargetFromStick();
    mathAngleStepToward(&gCurrentActor->moveYaw, gActivePlayerState->targetYaw, gActivePlayerState->turnRate);
    mathAngleStepToward(&gCurrentActor->yaw, gCurrentActor->moveYaw, gActivePlayerState->turnRate);
    playerProjectMoveSpeedOntoAngle(gCurrentActor->yaw);
}

void playerInputNoop(void) {
}


extern SchedStruct gScheduler;
extern f32 gKongTurnDecelRates[];
extern f32 gKongDecelRate[];
extern f32 gKongJumpVelocityY[];

void playerInputHandleAButtonSlopeJump(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    gCurrentActor->roll = 0;
    gCurrentActor->pitch = 0;
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    if (gActivePlayerState->chargeTimer != -1) {
        return;
    }
    if (gCurrentActor->floorSlopeFactor != 0.0f) {
        gCurrentActor->moveYaw = gCurrentActor->floorSlopeYaw;
        gCurrentActor->speedXZ = 200.0f;
        gActivePlayerState->approachTimer = 0x1E;
        gActivePlayerState->approachYaw = gCurrentActor->floorSlopeYaw;
        gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex] * 0.5;
    } else {
        gActivePlayerState->airTimer = 0;
        gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex];
    }
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
    gActivePlayerState->decelRate = gKongDecelRate[gCurrentCharacterIndex];
    gCurrentActor->state = 0x17;
    gCurrentActor->subState = 0;
    gActivePlayerState->gravityDelay = 0;
    actorScriptStartByIndex(gCurrentActor, 0x10);
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
}

void playerInputHandleAButtonState0(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    if ((gCurrentActor->contactFlags & 1) && (gCurrentActor->floorSlopeFactor != 0.0f)) {
        return;
    }
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
    gActivePlayerState->decelRate = gKongDecelRate[gCurrentCharacterIndex];
    gCurrentActor->state = 0x17;
    gCurrentActor->subState = 0;
    gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    actorScriptStart(gCurrentActor, 0xB0);
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
}

void playerInputHandleAButtonJump(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    if ((gCurrentActor->contactFlags & 1) && (gCurrentActor->floorSlopeFactor != 0.0f)) {
        return;
    }
    gActivePlayerState->targetSpeed = gKongTurnDecelRates[gCurrentCharacterIndex];
    gCurrentActor->speedXZ = INPUT_MIN(gCurrentActor->speedXZ, gActivePlayerState->targetSpeed);
    gActivePlayerState->decelRate = gKongDecelRate[gCurrentCharacterIndex];
    gActivePlayerState->airAccel = 20.0f;
    gCurrentActor->state = 0x17;
    gCurrentActor->subState = 0;
    gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    actorScriptStartByIndex(gCurrentActor, 0x10);
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
}

void playerInputHandleAButtonState17(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    if ((gCurrentActor->contactFlags & 1) && (gCurrentActor->floorSlopeFactor != 0.0f)) {
        return;
    }
    gCurrentActor->state = 0x17;
    gCurrentActor->subState = 0;
    gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    actorScriptStart(gCurrentActor, 0xAF);
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
}


void playerInputHandleAButtonGravity(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    if (gCurrentActor->accelY == -260.0f) {
        gCurrentActor->accelY = -31.0f;
    } else {
        playerSetBaseGravity();
    }
    gCurrentActor->state = 0x14;
    gCurrentActor->subState = 0;
    gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    actorScriptStartByIndex(gCurrentActor, 0x67);
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
}

void playerInputHandleAButtonState41(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    if (gActivePlayerState->hitStatus != 0) {
        return;
    }
    gCurrentActor->state = 0x41;
    gCurrentActor->subState = 0;
    gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    actorScriptStart(gCurrentActor, 0x156);
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
}

extern s32 gCurrentMap;

void playerInputCheckBButtonChargeCallback(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) && (gPlayerInventoryTable[gCurrentPlayerIndex].kong[3].moveLevel >= 2) && (gCurrentMap != 0xE)) {
        playerStateQueueCallback(9, 0, gCurrentPlayerIndex);
        gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
    }
}

void playerInputHandleAButtonState61(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    if ((gCurrentActor->contactFlags & 1) && (gCurrentActor->floorSlopeFactor != 0.0f)) {
        return;
    }
    gCurrentActor->state = 0x61;
    gCurrentActor->subState = 0;
    gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    actorScriptStartByIndex(gCurrentActor, 0x50);
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
}



extern u8 gEffectSpriteBlast;
extern u8 gEffectSpriteMuzzleFlash;
extern f32 gKongProjectileSpeed[];
extern s16 gKongMaxActiveProjectiles[];


void playerFireWeapon(u8 isFirstPerson, u8 force) {
    s16 spawnId;
    f32 scale;
    u16 sfx;
    u8 vol;
    f32 dz;
    f32 dx;
    f32 pitch;
    f32 speedXZ;
    f32 speedY;
    s32 weaponFlags;
    s32 ammoSlot;
    s16 yaw;
    f32 z;
    s32 isHoming;

    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) || force) {
        weaponFlags = gCurrentKongInventory->weaponFlags;
        if ((weaponFlags & 2) && slotQueueGetValue(3, gCurrentPlayerIndex)) {
            ammoSlot = 3;
        } else {
            weaponFlags &= ~2;
            ammoSlot = 2;
        }
        if (!isFirstPerson) {
            weaponFlags &= ~4;
        }
        slotQueueUpdate(ammoSlot, 0, 0);
        if (slotQueueGetValue(ammoSlot, gCurrentPlayerIndex)) {
            if (actorCountOwnedByClass(gCurrentActor, 4, actorIsActiveType2B) < gKongMaxActiveProjectiles[gCurrentCharacterIndex]) {
                isHoming = weaponFlags & 2;
                slotQueueAddValue(ammoSlot, gCurrentPlayerIndex, -1);
                if (!isFirstPerson) {
                    gActivePlayerState->recentShotCount = (gActivePlayerState->recentShotCount + 1 >= 0x15) ? 0x14 : gActivePlayerState->recentShotCount + 1;
                }
                rumbleRequest(gActivePlayerState->playerIndex, 0xFF, 3);
                switch (gCurrentActor->actorType) {
                    case 7:
                        spawnId = 0xAB;
                        scale = 0.5f;
                        gActivePlayerState->recoilTimer = 0x1A;
                        sfx = 0x2A5;
                        vol = 5;
                        if (!isFirstPerson) {
                            camStartShake(gActivePlayerState->camActor, 7, 7);
                        }
                        break;
                    case 6:
                        spawnId = 0x26;
                        scale = 0.5f;
                        gActivePlayerState->recoilTimer = 0x1A;
                        sfx = 0x2A5;
                        vol = 5;
                        if (!isFirstPerson) {
                            camStartShake(gActivePlayerState->camActor, 7, 7);
                        }
                        break;
                    case 4:
                        sfx = 0x77;
                        vol = 2;
                        spawnId = 0x2A;
                        scale = 0.5f;
                        break;
                    case 5:
                        spawnId = 0x2B;
                        scale = 0.36f;
                        sfx = 0xEF;
                        vol = 0;
                        gActivePlayerState->recoilTimer = 4;
                        break;
                    case 2:
                        spawnId = 0x30;
                        scale = 0.3f;
                        sfx = 0x7B;
                        vol = 5;
                        gActivePlayerState->recoilTimer = 0x1A;
                        break;
                    default:
                        spawnId = 0x24;
                        scale = 0.3f;
                        sfx = 0x7A;
                        vol = 5;
                        gActivePlayerState->recoilTimer = 0x1A;
                        break;
                }
                if (isFirstPerson) {
                    sfxPlayOnFreeSlot(sfx, 0x7FFF, 63.0f, 1.0f, vol, 0);
                } else {
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, sfx, 0xFF, 0x7F, vol);
                }
                if (isHoming != 0) {
                    if (isFirstPerson) {
                        sfxPlayOnFreeSlot(0x1EE, 0x7FFF, 63.0f, 1.0f, 0x1E, 0);
                    } else {
                        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x1EE, 0xFF, 0x7F, 0xA);
                    }
                }
                gActivePlayerState->lastFireHand = gActivePlayerState->gunHand;
                if (isFirstPerson) {
                    yaw = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].focusX, gPlayerSlots[gCurrentPlayerIndex].focusZ, gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ);
                } else {
                    yaw = gCurrentActor->yaw;
                }
                if (gCurrentActor->actorType == 4) {
                    if ((!isFirstPerson && actorTestNodeSegmentCollision(gCurrentActor)) || actorAngleInArcWithMargin(gCurrentActor, yaw, 0) == 0) {
                        projectileSetSpawnFlag();
                    }
                } else if (actorAngleInArcWithMargin(gCurrentActor, yaw, 0) == 0) {
                    projectileSetSpawnFlag();
                }
                if (isFirstPerson) {
                    z = gPlayerSlots[gCurrentPlayerIndex].camZ; // ORIG: the target loads camZ into $f0 (lwc1 at 0x33b8) and passes it with mfc1 a2 (0x33c4); a direct argument is lw a2
                    projectileSetTargetCoords(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camY, z);
                    dz = gPlayerSlots[gCurrentPlayerIndex].focusZ - gPlayerSlots[gCurrentPlayerIndex].camZ;
                    dx = gPlayerSlots[gCurrentPlayerIndex].focusX - gPlayerSlots[gCurrentPlayerIndex].camX;
                    pitch = mathAtan2(gPlayerSlots[gCurrentPlayerIndex].focusY - gPlayerSlots[gCurrentPlayerIndex].camY, sqrtf(dz * dz + dx * dx));
                    speedY = gKongProjectileSpeed[gCurrentCharacterIndex] * sinApprox(pitch);
                    speedXZ = gKongProjectileSpeed[gCurrentCharacterIndex] * cosApprox(pitch);
                    yaw = mathAngleBetweenPoints2D(gPlayerSlots[gCurrentPlayerIndex].focusX, gPlayerSlots[gCurrentPlayerIndex].focusZ, gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camZ);
                    projectileSpawnNodeEntry(spawnId, weaponFlags, scale, yaw, speedXZ, speedY, gActivePlayerActor);
                } else {
                    if (gCurrentActor->actorType == 2 || gCurrentActor->actorType == 3 || gCurrentActor->actorType == 6 || gCurrentActor->actorType == 7) {
                        effectSetDepth(1);
                        effectSetSpeed(0x50);
                        effectSetCallback(effectLightPulseOscillate);
                        effectCreateAtActorBone(&gEffectSpriteMuzzleFlash, 0.5f, gActivePlayerActor, gActivePlayerState->gunHand + 9, 2);
                        if (gCurrentActor->actorType == 6 || gCurrentActor->actorType == 7) {
                            effectSetDepth(1);
                            effectSetSpeed(0x50);
                            effectSetCallback(effectLightPulseOscillate);
                            effectCreateAtActorBone(&gEffectSpriteBlast, 0.5f, gActivePlayerActor, 9, 2);
                        }
                    }
                    projectileGetTargetCoords(gActivePlayerActor, gActivePlayerState->gunHand + 9);
                    projectileSpawnNodeEntry(spawnId, weaponFlags, scale, gActivePlayerActor->yaw, gKongProjectileSpeed[gCurrentCharacterIndex], 0.0f, gActivePlayerActor);
                }
                if ((mpIsMatchType(0) != 0) && (slotQueueGetValue(ammoSlot, gCurrentPlayerIndex) == 0)) {
                    playerKongHolsterGun(gCurrentActor);
                    playerResumeLocomotion(gCurrentActor);
                }
                playerInputToggleActiveState(gCurrentActor);
            }
        } else {
            switch (gCurrentActor->actorType) {
                case 6:
                case 7:
                    sfx = 0x190;
                    vol = 5;
                    break;
                case 4:
                    sfx = 0x77;
                    vol = 2;
                    break;
                case 5:
                    sfx = 0x7C;
                    vol = 0;
                    break;
                case 2:
                    sfx = 0xB0;
                    vol = 0xA;
                    gActivePlayerState->recoilTimer = 0x1A;
                    break;
                default:
                    sfx = 0x83;
                    vol = 5;
                    break;
            }
            if (isFirstPerson) {
                sfxPlayOnFreeSlot(sfx, 0x7FFF, 63.0f, 1.0f, vol, 0);
            } else {
                sfxPlayFromActorWithAltitudeCheck(gCurrentActor, sfx, 0xFF, 0x7F, vol);
            }
        }
    }
}


u8 actorTestNodeSegmentCollision(Actor *actor) {
    f32 z;
    f32 y;
    f32 x;
    f32 t;
    f32 x2;
    f32 x1;
    f32 y2;
    f32 y1;
    f32 z2;
    f32 z1;
    s16 hitA;
    s16 hitB;
    u8 hit;

    hit = 0;
    t = 0.0f;
    actorGetNodePos(actor, 4, &x1, &y1, &z1);
    actorGetNodePos(actor, 0xA, &x2, &y2, &z2);
    for (; t <= 1.0 && hit == 0; t += 0.2) {
        do { // FAKE: do/while(0) block ends the copy block so x1/y1/z1 reach the lerp as x/y/z variables, not copy-propagated (x1 f2, y1 f16, z1 f18 at 0x3834-0x3848)
            x = x1;
            y = y1;
            z = z1;
        } while (0);
        x = ((x2 - x1) * t) + x;
        y = ((y2 - y1) * t) + y;
        z = ((z2 - z1) * t) + z;
        hit = collisionTestSphere(x, y, z, 10.0f, &hitA, &hitB, 0, 0);
    }
    return hit;
}

void playerInputToggleActiveState(Actor *actor) {
    PlayerState *state = actor->customState;

    switch (actor->actorType) {
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
        state->gunHand = 1;
        return;
    default:
        state->gunHand = 1 - state->gunHand;
        return;
    }
}

u8 playerInputCanFireWeapon(void) {
    s32 ok;

    ok = !mpIsMatchType(0) && !(gGlobalOverlayFlags & 0x200) && slotQueueGetValue(4, gCurrentPlayerIndex) &&
           gPlayerCharacterId[gCurrentPlayerIndex] < 6 &&
           actorCountOwnedByClass(gCurrentActor, 4, 0) < gKongMaxActiveProjectiles[gCurrentCharacterIndex] &&
           (flagGet(0x184, 0) || (gGlobalOverlayFlags & 0x10000000) || gPlayerCount >= 2 || menuIsTransitionType3Or4() ||
            menuIsTransitionTypeC());
    return ok;
}


void playerInputHandlerCheckZAndTriggerState2C(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 1) && playerInputCanFireWeapon()) {
        actorScriptStartByIndex(gCurrentActor, 0x47);
        gCurrentActor->state = 0x2C;
        gCurrentActor->subState = 0;
    }
}


void playerFireWeaponIfOwned(void) {
    if (gCurrentKongInventory->weaponFlags & 1) {
        playerFireWeapon(0, 0);
    }
}

void playerFireWeaponFirstPerson(void) {
    playerFireWeapon(1, 0);
}

void playerInputHandlerCheckBAndFireWeapon(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC000) == 0x4000) {
        actorScriptStartByIndex(gCurrentActor, 0x54);
        return;
    }
    playerFireWeapon(0, 0);
}

extern s16 D_80753354[];

void playerInputHandleZButtonCrouch(void) {
    s32 canCrouch;

    canCrouch = 1;
    if (gPlayerCount >= 2) {
        canCrouch = playerInputCheckMultiplayerPlayerTarget() == 0;
    }
    if (canCrouch && (gCurrentActor->state != 0x62) && (gCurrentActor->contactFlags & 1)) {
        gActivePlayerState->turnRate = D_80753354[gCurrentCharacterIndex];
        gCurrentActor->state = 0x62;
        gCurrentActor->subState = 0;
        actorScriptStartByIndex(gCurrentActor, 0x52);
    }
}


void playerInputCheckZButtonResume(void) {
    if (!(gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x2000)) {
        playerResumeLocomotion(gCurrentActor);
    }
}

extern f32 gKongCrouchHighJumpVelocityY[];
extern f32 gKongCrouchLeapVelocityY[];

void playerInputHandleAButtonKong(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 6) {
        return;
    }
    if ((gCurrentActor->contactFlags & 1) && (gCurrentActor->floorSlopeFactor != 0.0f)) {
        return;
    }
    if (gActivePlayerState->actualSpeedXZ > 70.0f) {
        gCurrentActor->state = 0x1D;
        gCurrentActor->subState = 0;
        gActivePlayerState->jumpVelocityY = gKongCrouchLeapVelocityY[gCurrentCharacterIndex];
        gActivePlayerState->gravityDelay = 0;
        actorScriptStartByIndex(gCurrentActor, 0x1A);
        gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
    } else {
        gCurrentActor->state = 0x3E;
        gCurrentActor->subState = 0;
        gActivePlayerState->jumpVelocityY = gKongCrouchHighJumpVelocityY[gCurrentCharacterIndex];
        gActivePlayerState->gravityDelay = 0;
        actorScriptStartByIndex(gCurrentActor, 0xE);
        gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
    }
}




void playerInputHandleAButtonSub17(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    if (gCurrentActor->state != 0x17) {
        return;
    }
    if ((gCurrentActor->contactFlags & 1) && (gCurrentActor->floorSlopeFactor != 0.0f)) {
        return;
    }
    gCurrentActor->state = 0x17;
    gCurrentActor->subState = 0;
    gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    actorScriptStartByIndex(gCurrentActor, 0x10);
}


void playerInputHandleAButtonSub61(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    if (gCurrentActor->state != 0x61) {
        return;
    }
    if ((gCurrentActor->contactFlags & 1) && (gCurrentActor->floorSlopeFactor != 0.0f)) {
        return;
    }
    gCurrentActor->state = 0x61;
    gCurrentActor->subState = 0;
    gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    actorScriptStartByIndex(gCurrentActor, 0x50);
}




void playerInputHandleAButtonSub58(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    gCurrentActor->state = 0x58;
    gCurrentActor->subState = 0;
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->approachTimer = 0;
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
}


void playerFlipHeading180(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x10) {
        gCurrentActor->moveYaw = (gCurrentActor->moveYaw + 0x800) & 0xFFF;
    }
}


extern s16 gKongCannonLaunchSpeeds[];
extern f32 gKongCannonLaunchTimers[];

void playerInputInitCannonLaunch(void) {
    gCurrentActor->contactFlags &= 0xFFBF;
    gActivePlayerState->respawnTimer = gKongCannonLaunchSpeeds[gCurrentCharacterIndex];
    gCurrentActor->state = 0x17;
    gCurrentActor->subState = 0;
    gCurrentActor->speedXZ = 0.0f;
    gActivePlayerState->jumpVelocityY = gKongCannonLaunchTimers[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    actorScriptStartByIndex(gCurrentActor, 0x10);
}


void playerInputHandleAButtonSub5A(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    gCurrentActor->state = 0x5A;
    gCurrentActor->subState = 0;
    gActivePlayerState->approachTimer = 0;
    gActivePlayerState->gravityDelay = 0;
    actorScriptStartByIndex(gCurrentActor, 0x74);
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
}


void playerInputUpdateCannonAim(void) {
    u32 sel;

    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if ((gScheduler.tickCount - gActivePlayerState->jumpTimer) < 0xF) {
        if (gCurrentActor) {} // FAKE: dead read of gCurrentActor at the jump-block head makes its load a coloured uopt web ($v1 for the state store, lw v1,0(a3) at 0x43a4) and leaves sel in $v0; replaces the one-use p and sel ^= 0
        gCurrentActor->state = 0x4C;
        gCurrentActor->subState = 0;
        gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex];
        gActivePlayerState->gravityDelay = 0;
        sel = gActivePlayerState->heldActor->actorType;
        switch (sel) {
            case 0x3D:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
            case 0x55:
            case 0x82:
                actorScriptStart(gCurrentActor, 0x1CB);
                break;
            default:
                actorScriptStartByIndex(gCurrentActor, 0x30);
                break;
        }
        gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
    }
}



void playerInputClearVelocity(void) {
    playerSetTerminalVelocity594();
}



void playerInputSetBaseGravity(void) {
    playerSetBaseGravity();
}


extern f32 gKongLightGravity[];

void playerInputStepCannonPitch(void) {
    f32 b;
    f32 c;
    f32 a;
    s32 t;

    a = gActivePlayerState->aimPitch + 0x9E8;
    if (a >= 32768.0f) {
        a -= 65536.0f;
    }
    a /= 16;
    if (gCurrentActor->soundSlots[0] == -1) {
        sfxPlayActorSound(gCurrentActor, 0x114, 0, 0, 0, 0xFF, 1.0f, 0);
    }
    t = (s16)a;
    c = mathCosF(t);
    b = gKongLightGravity[gCurrentCharacterIndex];
    gCurrentActor->accelY = gKongLightGravity[gCurrentCharacterIndex] + (-2.0f * b * c);
    if (gCurrentActor->speedY < 0.0f) {
        gCurrentActor->accelY = gCurrentActor->accelY - gCurrentActor->speedY / 100.0;
    }
    if (gCurrentActor->contactFlags & 1) {
        gActivePlayerState->decelRate = gKongDecelRate[gCurrentCharacterIndex];
    } else {
        c = mathSinF(t) * 8.0f;
        if (c >= 0.0f) {
            a = gCurrentActor->yaw;
        } else {
            a = gCurrentActor->yaw + 0x800;
            if (a > 4096.0f) {
                a -= 4096.0f;
            }
        }
        if (c > 0.0f) {
            gActivePlayerState->airAccel = c;
        } else {
            gActivePlayerState->airAccel = -c;
        }
        playerApproachVelocity((s32)a, 900.0f, gActivePlayerState->targetSpeed);
        a = gCurrentActor->speedXZ;
        gActivePlayerState->decelRate = (a * a) / 10000.0f + 1.0f;
    }
    gActivePlayerState->thrustApplied = 1;
}



void playerInputHandleCannonBButton(void) {
    f32 temp;

    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000)) {
        if (slotQueueGetValue(5, gCurrentPlayerIndex) && gActivePlayerState->isHoldingObject) {
            playerInputStepCannonPitch();
        } else {
            sfxStopSlotSound(gCurrentActor, 0);
            gCurrentActor->accelY = gKongLightGravity[gCurrentCharacterIndex];
            temp = gCurrentActor->speedXZ;
            gActivePlayerState->decelRate = (temp * temp) / 10000.0f + 1.0f;
        }
    } else {
        gCurrentActor->accelY = gKongLightGravity[gCurrentCharacterIndex];
    }
    playerApplyDeceleration();
}



void playerInputHandlerResumeDecel(void) {
    playerResumeLocomotionDecel(gCurrentActor);
}


void playerInputStopSoundOnZRelease(void) {
    f32 temp;

    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000)) {
        sfxStopSlotSound(gCurrentActor, 0);
    }
    gCurrentActor->accelY = gKongLightGravity[gCurrentCharacterIndex];
    temp = gCurrentActor->speedXZ;
    gActivePlayerState->decelRate = (temp * temp) / 10000.0f + 1.0f;
    playerApplyDeceleration();
}


void playerInputResetCannonPitch(void) {
    gActivePlayerState->decelRate = gKongDecelRate[gCurrentCharacterIndex];
}


void playerStepPitchAngleToward(f32 target) {
    PlayerState *ps;
    f32 pitch;
    u16 raw;

    ps = gActivePlayerState;
    raw = ps->aimPitch;
    if (raw < 0x8000) {
        pitch = raw + 0x10000;
    } else {
        pitch = raw;
    }
    if (target < pitch) {
        pitch -= 3000.0f;
        if (pitch < target) {
            pitch = target;
        }
    }
    if (pitch < target) {
        pitch += 3000.0f;
        if (target < pitch) {
            pitch = target;
        }
    }
    ps->aimPitch = pitch;
}

void playerInputHandleStickAction(void) {
    static u8 sThrustBurstFrames; // function-local static (only user): uopt treats it as non-aliased; needs the E4090 .bss carve
    static u8 sThrustCooldownFrames;
    f32 ang;
    f32 ground;
    f32 a;
    f32 arg;
    s16 t;

    if (slotQueueGetValue(5, gCurrentPlayerIndex) && gActivePlayerState->isHoldingObject) {
        if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x2000) {
            sThrustBurstFrames = 0;
            sThrustCooldownFrames = 0;
        }
        ang = gCurrentActor->moveYaw - gCurrentActor->yaw;
        if (ang < 0.0f) {
            ang += 4096.0f;
        }
        t = (s16)ang;
        ground = mathSinF(t) * gCurrentActor->speedXZ;
        if (ground > 0.0f) {
            a = ground;
        } else {
            a = -ground;
        }
        if (a > 10.0f) {
            if (ang > 2048.0f) {
                arg = 1024.0f;
            } else {
                arg = 3072.0f;
            }
            arg += gCurrentActor->yaw;
            if (arg >= 4096.0f) {
                arg -= 4096.0f;
            }
            gActivePlayerState->airAccel = 8.0f;
            playerApproachVelocity((s32)arg, 0.0f, gActivePlayerState->targetSpeed);
        }
        ang = mathCosF(t) * gCurrentActor->speedXZ;
        ground = gCurrentActor->speedY;
        if (ground > 0.0f) {
            ground = 0.0f;
        }
        if (ang > 0.0f) {
            a = ang;
        } else {
            a = -ang;
        }
        if (a > 10.0f) {
            if (ground > 0.0f) {
                a = ground;
            } else {
                a = -ground;
            }
            arg = (mathAtan2(a, ang) - 1.5707964f) * 16384.0 / 1.5707963705062866 + 63000.0;
        } else {
            arg = 63000.0f;
        }
        playerStepPitchAngleToward(arg);
        if (ang > 0.0f) {
            a = ang;
        } else {
            a = -ang;
        }
        if (((a > 10.0f) || (gCurrentActor->speedY < 0.0f)) && (sThrustCooldownFrames == 0)) {
            sThrustBurstFrames = 4;
        }
        if (sThrustBurstFrames) {
            sThrustBurstFrames -= 1;
            if (sThrustBurstFrames == 0) {
                sThrustCooldownFrames = 8;
            }
            playerInputStepCannonPitch();
        } else {
            sfxStopSlotSound(gCurrentActor, 0);
        }
        if (sThrustCooldownFrames) {
            sThrustCooldownFrames -= 1;
        }
    }
}


void playerInputHandlerStartScript15(void) {
    actorScriptStartByIndex(gCurrentActor, 0x15);
    gCurrentActor->subState = 7;
}



extern f32 gKongMaxTierExitSpeeds[];
extern f32 gKongHighTierEnterSpeeds[];
extern f32 gKongUnderwaterPaddleDecelRate[];
extern s16 gKongUnderwaterPaddleTurnRate[];
extern s16 gKongChargeLaunchSpeeds[];
extern s16 gKongChargeTargetSpeeds[];
extern s16 gKongChargeDecelRates[];
extern s16 gKongChargeTurnRates[];

void playerInputHandleBButtonGun(void) {
    PadInputState *pad;

    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gActivePlayerState->jumpStartTime = gScheduler.tickCount;
    }
    if (gActorGlobalState.grabCandidateReceived &&
        (flagGet(0x185, 0) || (gGlobalOverlayFlags & 0x10000000) || (gPlayerCount >= 2) || menuIsTransitionTypeC())) {
        playerStateQueueCallback(3, 0, gCurrentPlayerIndex);
        return;
    }
    if (playerInputCheckBButtonTarget()) {
        return;
    }
    pad = &gPlayerPadState[gCurrentPlayerIndex];
    if (!(pad->pressedButtons & 0x4000)) {
        return;
    }
    if (!(gCurrentActor->contactFlags & 1)) {
        return;
    }
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 6) {
        if (pad->heldButtons & 0x2000) {
            gCurrentActor->state = 0x2F;
            gCurrentActor->subState = 0;
            actorScriptStartByIndex(gCurrentActor, 0x48);
            gActivePlayerState->slideLaunchSpeed = gKongChargeLaunchSpeeds[gCurrentCharacterIndex];
            gActivePlayerState->targetSpeed = gKongChargeTargetSpeeds[gCurrentCharacterIndex];
            gActivePlayerState->decelRate = gKongChargeDecelRates[gCurrentCharacterIndex];
            gActivePlayerState->turnRate = gKongChargeTurnRates[gCurrentCharacterIndex];
            gCurrentActor->moveYaw = gCurrentActor->yaw;
        } else {
            gCurrentActor->state = 0x29;
            gCurrentActor->subState = 0;
            actorScriptStart(gCurrentActor, 0x1DF);
            gActivePlayerState->unk64 = 0;
            gActivePlayerState->slideLaunchSpeed = gKongChargeLaunchSpeeds[gCurrentCharacterIndex];
        }
    } else {
        if (!mpIsMatchType(0) && (gKongMaxTierExitSpeeds[gCurrentCharacterIndex] <= gActivePlayerState->actualSpeedXZ) && (gCurrentActor->floorSlopeFactor == 0.0f)) {
            actorScriptStartByIndex(gCurrentActor, 0x44);
            gCurrentActor->state = 0x29;
            gCurrentActor->subState = 0;
            gCurrentActor->targetYaw = gCurrentActor->moveYaw;
            gCurrentActor->speedXZ = 150.0f;
            gActivePlayerState->targetSpeed = 150.0f;
        } else {
            actorScriptStartByIndex(gCurrentActor, 0x3F);
            gCurrentActor->state = 0x26;
            gCurrentActor->subState = 0;
        }
        gActivePlayerState->chargeTimer = 0x32;
        gActivePlayerState->unk64 = 0;
    }
}

s32 playerInputCheckBButtonTarget(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) && gActorGlobalState.eventReceived && (gActorGlobalState.eventSubtype == 8)) {
        gActivePlayerState->targetPos[0] = gActorGlobalState.eventX;
        gActivePlayerState->targetPos[1] = gActorGlobalState.eventY;
        gActivePlayerState->targetPos[2] = gActorGlobalState.eventZ;
        playerStateQueueCallback(0x1F, 0, gCurrentPlayerIndex);
        return 1;
    }
    return 0;
}

void playerInputHandleBButtonPunch(void) {
    f32 v;
    f32 w;

    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gActivePlayerState->jumpStartTime = gScheduler.tickCount;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        v = gCurrentActor->distToFloor;
        if (gCurrentActor->contactFlags & 2) {
            w = gCurrentActor->y - gCurrentActor->waterY;
            if (!(v < w)) {
                v = w;
            }
        }
        if ((3.0f < v) && (gPlayerCharacterId[gCurrentPlayerIndex] != 6)) {
            playerStateQueueCallback(0xF, 0, gCurrentPlayerIndex);
        }
    }
}

void playerInputHandleBButtonSpecial(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        if ((gKongHighTierEnterSpeeds[gCurrentCharacterIndex] < gActivePlayerState->actualSpeedXZ) &&
            ((gPlayerCharacterId[gCurrentPlayerIndex] == 3) || (gPlayerCharacterId[gCurrentPlayerIndex] == 0) || (gPlayerCharacterId[gCurrentPlayerIndex] == 5))) {
            if (gPlayerCharacterId[gCurrentPlayerIndex] == 3) {
                gCurrentActor->speedY = 200.0f;
            }
            playerSetBaseGravity();
            gCurrentActor->state = 0x2B;
            gCurrentActor->subState = 0;
            actorScriptStartByIndex(gCurrentActor, 0x45);
            gActivePlayerState->chargeTimer = 0x32;
        } else {
            switch (gPlayerCharacterId[gCurrentPlayerIndex]) {
                case 2:
                    if (gPlayerInventoryTable[gCurrentPlayerIndex].kong[2].moveLevel > 0) {
                        playerStateQueueCallback(0x25, 0, gCurrentPlayerIndex);
                    }
                    break;
                case 4:
                    if (gPlayerInventoryTable[gCurrentPlayerIndex].kong[4].moveLevel >= 2) {
                        playerStateQueueCallback(0x26, 0, gCurrentPlayerIndex);
                    }
                    break;
                case 1:
                    if (gPlayerInventoryTable[gCurrentPlayerIndex].kong[1].moveLevel > 0) {
                        gActivePlayerState->turnRate = 0x64;
                        gCurrentActor->state = 0x2E;
                        gCurrentActor->subState = 0;
                        actorScriptStartByIndex(gCurrentActor, 0x48);
                        gActivePlayerState->slideLaunchSpeed = gKongChargeLaunchSpeeds[gCurrentCharacterIndex] * 4;
                        gActivePlayerState->targetSpeed = gKongChargeTargetSpeeds[gCurrentCharacterIndex] * 2;
                        gActivePlayerState->decelRate = gKongChargeDecelRates[gCurrentCharacterIndex];
                    }
                    break;
                case 6:
                    gCurrentActor->state = 0x2F;
                    gCurrentActor->subState = 0;
                    actorScriptStartByIndex(gCurrentActor, 0x48);
                    gActivePlayerState->slideLaunchSpeed = gKongChargeLaunchSpeeds[gCurrentCharacterIndex];
                    gActivePlayerState->targetSpeed = gKongChargeTargetSpeeds[gCurrentCharacterIndex];
                    gActivePlayerState->decelRate = gKongChargeDecelRates[gCurrentCharacterIndex];
                    gActivePlayerState->turnRate = gKongChargeTurnRates[gCurrentCharacterIndex];
                    gCurrentActor->moveYaw = gCurrentActor->yaw;
                    break;
            }
        }
    }
}

void playerInputHandleZButtonInteract(void) {
    s16 arcCenter;
    s16 arcWidth;
    u8 pad;
    u8 ok;
    f32 radius;

    ok = 1;
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x2000) {
        if (gActivePlayerState->heldActor->hasArcBounds == 0) {
            radius = (gActivePlayerState->heldActor->actorType == 0x3D) ? sZInteractRadiusType3D : 30.0f;
            if (collisionTestSphere(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, radius, &arcCenter, &arcWidth, 1, 0)) {
                if (!mathAngleInArcWithMargin(arcCenter, arcWidth, gCurrentActor->yaw, 0)) {
                    ok = 0;
                }
            }
            if (ok) {
                gCurrentActor->state = 0x4A;
                gCurrentActor->subState = 0;
                switch (gActivePlayerState->heldActor->actorType) {
                    case 0x3D:
                    case 0x3F:
                    case 0x40:
                    case 0x41:
                    case 0x42:
                    case 0x55:
                    case 0x82:
                        actorScriptStart(gCurrentActor, 0x1CD);
                        break;
                    default:
                        actorScriptStartByIndex(gCurrentActor, 0x2C);
                        break;
                }
            }
        }
    }
}

void playerInputHandleZButtonState4B(void) {
    if ((gActivePlayerState->heldActor->actorType != 0x55) && (gActivePlayerState->heldActor->actorType != 0x82)) {
        gCurrentActor->state = 0x4B;
        gCurrentActor->subState = 0;
        switch (gActivePlayerState->heldActor->actorType) {
            case 0x3D:
            case 0x3F:
            case 0x40:
            case 0x41:
            case 0x42:
                actorScriptStart(gCurrentActor, 0x1CC);
                break;
            default:
                actorScriptStartByIndex(gCurrentActor, 0x2D);
                break;
        }
    }
}

void playerInputThrowHeldActor(void) {
    if ((gActivePlayerState->heldActor->actorType != 0x55) && (gActivePlayerState->heldActor->actorType != 0x82)) {
        gCurrentActor->speedY = 200.0f;
        gCurrentActor->state = 0x4D;
        gCurrentActor->subState = 0;
        actorScriptStartByIndex(gCurrentActor, 0x2D);
    }
}

void playerInputHandleAButtonFire(void) {
    if ((playerInputCheckMultiplayerPlayerTarget() == 0) && (gActivePlayerState->chargeTimer == -1)) {
        if ((gPlayerCharacterId[gCurrentPlayerIndex] != 6) || (gCurrentActor->speedXZ < gKongMaxTierExitSpeeds[gCurrentCharacterIndex])) {
            gCurrentActor->state = 0x3C;
            gCurrentActor->subState = 0;
            actorScriptStartByIndex(gCurrentActor, 0xA);
            gActivePlayerState->turnRate = gKongUnderwaterPaddleTurnRate[gCurrentCharacterIndex];
        }
        gActivePlayerState->decelRate = gKongUnderwaterPaddleDecelRate[gCurrentCharacterIndex];
    }
}

void playerInputHandleZButtonFire(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 1) && playerInputCanFireWeapon()) {
        projectileTrySpawnFromSlot(gCurrentActor);
        sfxPlayScriptActorSoundForPlayer(gCurrentActor, 0x21, 0x19);
    }
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) {
        if (gScheduler.tickCount - gActivePlayerState->lastZPressTick < 0xF) {
            if (gActivePlayerState->gunDrawn) {
                playerKongPlayHolsterSfx(gCurrentActor);
            }
            gActivePlayerState->gunDrawn = 0;
            playerLeaveViewMode(gCurrentActor, 0);
        } else if (!mpIsMatchType(0) && !(gGlobalOverlayFlags & 0x80000200) && (gCurrentKongInventory->weaponFlags & 1) &&
                   !(gActivePlayerState->stateFlags & 0x30) &&
                   (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1)) {
            playerToggleGun(gCurrentActor, gActivePlayerState, 1);
        }
        gActivePlayerState->lastZPressTick = gScheduler.tickCount;
    }
}

void playerInputHandleZButtonShoot(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 1) && playerInputCanFireWeapon()) {
        projectileTrySpawnFromSlot(gCurrentActor);
        sfxPlayScriptActorSoundForPlayer(gCurrentActor, 0x21, 0x19);
    }
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) {
        if (gScheduler.tickCount - gActivePlayerState->lastZPressTick < 0xF) {
            if (gActivePlayerState->gunDrawn) {
                playerKongPlayHolsterSfx(gCurrentActor);
            }
            gActivePlayerState->gunDrawn = 0;
            playerLeaveViewMode(gCurrentActor, 0);
        } else if (!mpIsMatchType(0) && !(gGlobalOverlayFlags & 0x200) && (gCurrentKongInventory->weaponFlags & 1) &&
                   (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1)) {
            playerToggleGun(gCurrentActor, gActivePlayerState, 1);
            gPlayerSlots[gCurrentPlayerIndex].fov = 45.0f;
        }
        gActivePlayerState->lastZPressTick = gScheduler.tickCount;
    }
}

void playerInputUpdateStickSwimming(void) {
    if (mpIsMatchType(0)) {
        if (((gCurrentActor->state == 0x31) || (gCurrentActor->state == 0x32)) && (gActivePlayerState->gunDrawn == 0)) {
            playerInputHandleAButtonFire();
        }
    }
}

s32 actorAnyActiveHasFlag2000000(void) {
    s32 ret;
    s32 i;
    Actor *actor;

    ret = 0;
    for (i = 0; i < gActiveActorCount && ret == 0; i++) {
        actor = gActiveActors[i].actor;
        ret = actor->flags & 0x2000000;
    }
    return ret;
}

extern s32 gGlobalCutsceneFlags;

void playerInputCheckInstrumentPlayback(void) {
    u8 onOwnPad;

    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 8) && (gFrameCounter >= 3) && (gCurrentKongInventory->instrumentFlags & 1) &&
        !(gGlobalOverlayFlags & 0x4000) && !(gGlobalCutsceneFlags & 1) &&
        (gPlayerSlots[gCurrentPlayerIndex].sizeMode != 2) &&
        (playerInputCheckTargetMoved(gCurrentActor) == 0) && (actorAnyActiveHasFlag2000000() == 0) &&
        (gActivePlayerState->damageCooldown == 0)) {
        onOwnPad = playerIsOnOwnInstrumentPad(gCurrentActor);
        if ((gCurrentMap != 0xCD) || onOwnPad) {
            if (slotQueueGetValue(7, gCurrentPlayerIndex) || onOwnPad) {
                playerStateQueueCallback(0x53, 0, gActivePlayerState->playerIndex);
                if (!(gGlobalCutsceneFlags & 2)) {
                    gCurrentActor->collisionMode = 1;
                }
                if (!onOwnPad) {
                    slotQueueAddValue(7, gCurrentPlayerIndex, -1);
                }
            }
            if (!onOwnPad) {
                slotQueueUpdate(7, 0, 0);
            }
        }
    }
}


u8 playerInputCheckTargetMoved(Actor *mob) {
    f32 dx;
    f32 dy;
    f32 dz;

    if (mob->attachMode == 1) {
        dx = mob->attachWorldX - mob->prevX;
        dz = mob->attachWorldZ - mob->prevZ;
        if (sqrtf(dx * dx + dz * dz) > 1.0) {
            return 1;
        }
    }
    if (mob->contactFlags & 8) {
        dx = mob->x - mob->prevX;
        dz = mob->y - mob->prevY;
        dy = mob->z - mob->prevZ;
        if (sqrtf(dx * dx + dz * dz + dy * dy) > 1.0) {
            return 1;
        }
    }
    if ((mob->attachMode == 1) && (modelSlotGetType(mob->cutsceneId) == 0x88)) {
        return 1;
    }
    if ((mob->attachMode == 1) && (modelSlotGetType(mob->cutsceneId) == 0x219)) {
        return 1;
    }
    if ((mob->attachMode == 1) && (modelSlotGetType(mob->cutsceneId) == 0x132)) {
        return 1;
    }
    return 0;
}

int playerIsOnOwnInstrumentPad(Actor *mob) {
    u8 ret;

    ret = 0;
    if (mob->attachMode == 1) {
        switch (modelSlotGetType(mob->cutsceneId)) {
            case 0xA8:
                if (mob->actorType == 2) {
                    ret = 1;
                }
                break;
            case 0xA9:
                if (mob->actorType == 3) {
                    ret = 1;
                }
                break;
            case 0xAA:
                if (mob->actorType == 5) {
                    ret = 1;
                }
                break;
            case 0xAB:
                if (mob->actorType == 6) {
                    ret = 1;
                }
                break;
            case 0xAC:
                if (mob->actorType == 4) {
                    ret = 1;
                }
                break;
        }
    }
    return ret;
}


extern s32 gMapWarpCount;
extern u8 gMapLoadCountdown;
extern f32 gKongHoverLaunchVelocityY[];
extern u8 gEffectSpriteSmokePuff[];

s32 playerInputCheckMultiplayerPlayerTarget(void) {
    s32 i;

    if (gActorGlobalState.eventReceived != 0) {
        switch (gActorGlobalState.eventSubtype) {
            case 9:
                if (gActivePlayerState->transitionTimer == 0) {
                    gActivePlayerState->warpX = gActorGlobalState.eventX;
                    gActivePlayerState->warpY = gActorGlobalState.eventY;
                    gActivePlayerState->warpZ = gActorGlobalState.eventZ;
                    gActivePlayerState->warpYaw = gActorGlobalState.eventValue0;
                    playerStateQueueCallback(0x1E, 0, gCurrentPlayerIndex);
                    playerRestoreKongState(gCurrentActor, gActivePlayerState);
                    return 1;
                }
                break;
            case 5:
                if (gCsCondFlag == 0) {
                    if (++gMapWarpCount < 0x5DD) {
                        gActivePlayerState->warpX = gActorGlobalState.eventX;
                        gActivePlayerState->warpY = gActorGlobalState.eventY;
                        gActivePlayerState->warpZ = gActorGlobalState.eventZ;
                        playerStateQueueCallback(0x1C, 0, gCurrentPlayerIndex);
                        playerRestoreKongState(gCurrentActor, gActivePlayerState);
                        return 1;
                    }
                }
                break;
            case 3:
                if (gCsCondFlag == 0) {
                    if (++gMapWarpCount < 0x5DD) {
                        gActivePlayerState->warpX = gActorGlobalState.eventX;
                        gActivePlayerState->warpY = gActorGlobalState.eventY;
                        gActivePlayerState->warpZ = gActorGlobalState.eventZ;
                        playerStateQueueCallback(0x1D, 0, gCurrentPlayerIndex);
                        playerRestoreKongState(gCurrentActor, gActivePlayerState);
                        return 1;
                    }
                }
                break;
            case 10:
                if (gMapLoadCountdown == 0) {
                    sfxPlayAtPositionPooled(gCurrentActor->x, gCurrentActor->y, gCurrentActor->z, 0xE6, 0xFF, 0x7F, 0, 0, 0.3f, 0);
                    screenSetTransitionFadeType(0);
                    mapSaveSlotAndTransition(gActorGlobalState.eventValue0, gActorGlobalState.eventValue1, 0, 0);
                }
                return 1;
            case 4:
                if (!(gActivePlayerState->stateFlags & 0x40)) {
                    playerTransformAnimalStartSfx(gPrimaryPlayerActor);
                    gActivePlayerState->transformTimer = gActorGlobalState.eventValue0;
                }
                return 1;
            case 0:
                if (gFrameCounter >= 4) {
                    camStartPath(gCurrentActor, 0x26, 5);
                    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x18, 0xFF, 0x7F, 0x19);
                    gCurrentActor->state = 0x18;
                    gCurrentActor->subState = 0;
                    gCurrentActor->collisionMode = 1;
                    gActivePlayerState->jumpVelocityY = gKongJumpVelocityY[gCurrentCharacterIndex] * 2.5;
                    gActivePlayerState->gravityDelay = 0x28;
                    actorScriptStartByIndex(gCurrentActor, 0x22);
                    timerQueueAdd(playerInputStartTransitionToMap, 0x14, gActorGlobalState.eventValue0, gActorGlobalState.eventValue1, 0);
                    for (i = 0; i != 0x14; i++) {
                        effectSetDepth(1);
                        effectSetCallback(effectFollowPlayerUpdate);
                        effectSetStartDelay(i);
                        effectCreateAtPosition(gEffectSpriteSmokePuff, 0.8f, gCurrentActor->x, gCurrentActor->y, gCurrentActor->z);
                    }
                    effectSpawnBurstParticleCluster(gPrimaryPlayerActor);
                    return 1;
                }
                break;
            case 2:
                gCurrentActor->state = 0x1B;
                gCurrentActor->subState = 0;
                gActivePlayerState->jumpVelocityY = gKongHoverLaunchVelocityY[gCurrentCharacterIndex];
                gActivePlayerState->gravityDelay = 0;
                actorScriptStartByIndex(gCurrentActor, 0x14);
                return 1;
            case 6:
                gCurrentActor->state = 0x6E;
                gCurrentActor->subState = 0;
                gCurrentActor->speedY = 0.0f;
                gCurrentActor->accelY = gActorGlobalState.eventValue0 * 0.2 + 2.0;
                gActivePlayerState->twirlTimer = gActorGlobalState.eventValue1;
                actorScriptStart(gCurrentActor, 0x169);
                return 1;
            case 7:
                gCurrentActor->collisionMode = 1;
                gActivePlayerState->destMap = gActorGlobalState.eventValue0;
                gCurrentActor->state = 0x76;
                gCurrentActor->subState = 0;
                actorScriptStartByIndex(gCurrentActor, 0x86);
                return 1;
        }
    }
    return 0;
}


void playerInputStartTransitionToMap(s32 mapId, s32 fade, s32 unused) {
    if (fade != 0) {
        transitionSetState(2);
        screenSetTransitionFadeType(0);
    }
    mapSaveSlotAndTransition(mapId, 0, 0, 0);
}


extern u8 gSplitScreenMode;

int playerInputCanSlam(void) {
    f32 fv;
    f32 t;

    fv = gCurrentActor->distToFloor;
    if (gCurrentActor->contactFlags & 2) {
        t = gCurrentActor->y - gCurrentActor->waterY;
        if (!(fv < t)) {
            fv = t;
        }
    }
    return ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x2000) != 0) && (gActivePlayerState->currentScale[0] * 66.0 < fv) &&
           (gPlayerCharacterId[gCurrentPlayerIndex] != 6) && (gCurrentKongInventory->slamLevel != 0);
}


void playerInputCheckEnterLongJump(void) {
    if (playerInputCanSlam() != 0) {
        switch (gCurrentKongInventory->slamLevel) {
            case 2:
                actorScriptStartByIndex(gCurrentActor, 0x17);
                controllerAnimSetStateRemap(gCurrentActor, 0x18, 0.0f, 3.0f);
                scriptSetActorRampTarget(gCurrentActor, 1.35f, 0.0f);
                break;
            case 3:
                actorScriptStartByIndex(gCurrentActor, 0x19);
                break;
            default:
                actorScriptStartByIndex(gCurrentActor, 0x16);
                controllerAnimSetStateRemap(gCurrentActor, 0x17, 0.0f, 3.0f);
                scriptSetActorRampTarget(gCurrentActor, 1.35f, 0.0f);
                break;
        }
        gCurrentActor->state = 0x1C;
        gCurrentActor->subState = 0;
    }
}

void playerInputHandlerNoop1(void) {
}

void playerInputHandlerNoop2(void) {
}

void playerInputQueueCrouchCallback(void) {
    if (!(gActivePlayerState->stateFlags & 0x20)) {
        playerStateQueueCallback(0x24, 0, gCurrentPlayerIndex);
    }
}

void playerInputQueueCrouchCallbackDirect(void) {
    playerStateQueueCallback(0x24, 0, gCurrentPlayerIndex);
}

void playerInputQueueGunState5F(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) && (gCurrentKongInventory->weaponFlags & 1) &&
        (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) && !(gActivePlayerState->stateFlags & 0x30) &&
        (mpIsMatchType(0) == 0)) {
        playerStateQueueCallback(0x14, 0, gCurrentPlayerIndex);
    }
}

void playerInputQueueGunAimState60(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) && (gCurrentKongInventory->weaponFlags & 1) && !(gGlobalOverlayFlags & 0x200) &&
        (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) && !(gActivePlayerState->stateFlags & 0x30) &&
        (mpIsMatchType(0) == 0)) {
        playerStateQueueCallback(0x15, 0, gCurrentPlayerIndex);
    }
}


void playerInputHandleRButtonCameraLock(void) {
    CamState *obj;

    obj = gActivePlayerState->camActor->customState;
    obj->flags |= 4;
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x10) {
        if ((gGlobalOverlayFlags & 1) || ((gPlayerCount >= 2) && (gSplitScreenMode == 0))) {
            if (obj->flags & 0x10000) {
                camClearSecondTarget(gActivePlayerState->camActor);
                return;
            }
            camSetSecondTarget(gActivePlayerState->camActor, 0, 0);
            return;
        }
        if (!(obj->flags & 0x4000)) {
            obj->flags ^= 2;
            if ((obj->repositionFrames < 3) && (obj->snapBehindFrames == 0) && (obj->mode != 2)) {
                obj->repositionFrames = 0x14;
                obj->orbitYaw = gCurrentActor->yaw;
                gActivePlayerState->camActor->distToFloor = obj->followHeightGoal;
                obj->snapBehindFrames = 0xA;
            }
        }
    }
}

void playerInputHandleRButtonReleaseCameraLock(void) {
    CamState *obj;

    if (!(gGlobalOverlayFlags & 1) && ((gPlayerCount < 2) || (gSplitScreenMode != 0))) {
        obj = gActivePlayerState->camActor->customState;
        obj->secondTarget = 0;
        obj->flags &= ~4;
    }
}

extern u8 gPausingPlayer;
extern f32 gScreenFadeProgress;

void playerInputRequestPause(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x1000) && (camIsCutsceneActive() == 0) && (gScreenFadeProgress == 0.0f) &&
        ((menuIsTransitionType6() != 0) || (menuIsTransitionTypeC() != 0) || (menuIsTransitionType3Or4() != 0)) &&
        (screenWipeGetState() == 0) && (screenWipeGetCooldown() == 0)) {
        gPausingPlayer = gCurrentPlayerIndex;
        gGlobalPauseFlags |= 1;
    }
}



extern f32 gKongSwimTopSpeeds[];
extern s16 gKongStickTurnRates[];
extern f32 gKongUnderwaterEntryThrustSpeeds[];
extern f32 gKongSurfaceStrokeSpeeds[];
extern f32 gKongSurfaceStrokeRepeatSpeeds[];
extern s16 gKongSurfaceStrokeFrames[];
extern s16 D_8075395C[];
extern s16 gKongStickRollAngles[];

void playerInputRecordAPress(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
}

void playerInputRecordBPress(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gActivePlayerState->jumpStartTime = gScheduler.tickCount;
    }
}

void playerInputCalculateStickForwardSpeed(void) {
    f32 temp;

    if (gPlayerPadState[gCurrentPlayerIndex].stickMag != 0.0f) {
        temp = gActivePlayerState->stopSpeed;
        gActivePlayerState->maxSpeed = (gPlayerPadState[gCurrentPlayerIndex].stickMagNorm * (gActivePlayerState->targetSpeed - temp)) + temp;
    } else {
        gActivePlayerState->maxSpeed = 0.0f;
    }
    gActivePlayerState->maxSpeed = gActivePlayerState->maxSpeed / 4;
    if (gPlayerPadState[gCurrentPlayerIndex].stickMag != 0.0f) {
        mathAngleStepToward(&gCurrentActor->yaw, gPlayerPadState[gCurrentPlayerIndex].stickAngle, gActivePlayerState->turnRate);
    }
    mathAngleStepToward(&gCurrentActor->roll, 0, 0x10);
    mathAngleStepToward(&gCurrentActor->pitch, 0, 0x10);
}

void playerInputCalculateStickTurnRate(void) {
    s16 pitch;

    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsX != 0) {
        pitch = gKongStickTurnRates[gCurrentCharacterIndex] * ((gPlayerPadState[gCurrentPlayerIndex].stickX >= 0) ? 1 : -1);
        pitch &= 0xFFF;
    } else {
        pitch = 0;
    }
    mathAngleStepToward(&gCurrentActor->pitch, pitch, 0x10);
    mathAngleStepToward(&gCurrentActor->roll, gActivePlayerState->subTimer, 0x10);
    gActivePlayerState->targetSpeed = gKongSwimTopSpeeds[gCurrentCharacterIndex];
}

extern s16 gKongUnderwaterIdleTurnPitchAngles[];
extern s16 gKongUnderwaterIdleRollAngles[];

void playerInputStepTurnFacingAngle(void) {
    s32 ang;
    s16 target;
    s16 rollStep;

    ang = gCurrentActor->yaw;
    rollStep = 0x10;
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 7) {
        rollStep = 0x19;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsX != 0) {
        ang -= gPlayerPadState[gCurrentPlayerIndex].stickX / 2;
        gCurrentActor->yaw = (s16)ang & 0xFFF;
        target = gKongUnderwaterIdleTurnPitchAngles[gCurrentCharacterIndex] * ((gPlayerPadState[gCurrentPlayerIndex].stickX >= 0) ? 1 : -1);
        target &= 0xFFF;
    } else {
        target = 0;
    }
    mathAngleStepToward(&gCurrentActor->pitch, target, 0x10);
    if (gPlayerPadState[gCurrentPlayerIndex].stickY != 0) {
        target = (gKongStickRollAngles[gCurrentCharacterIndex] * gPlayerPadState[gCurrentPlayerIndex].stickY) / 70;
        target &= 0xFFF;
        mathAngleStepToward(&gCurrentActor->roll, target, (s16)(s32)((((f64)gPlayerPadState[gCurrentPlayerIndex].stickY * 0.125) > 0.0 ? ((f64)gPlayerPadState[gCurrentPlayerIndex].stickY * 0.125) : -((f64)gPlayerPadState[gCurrentPlayerIndex].stickY * 0.125)) + (f64)rollStep));
        return;
    }
    mathAngleStepToward(&gCurrentActor->roll, gKongUnderwaterIdleRollAngles[gCurrentCharacterIndex], 0x10);
}

void playerInputUpdateStickTurnYaw(void) {
    f32 dist;
    f32 scale;
    s16 targetYaw;
    s32 delta;

    playerUpdateMoveTargetFromStick();
    if (gActivePlayerState->maxSpeed != 0.0f) {
        scale = gPlayerPadState[gCurrentPlayerIndex].stickMagNorm * 0.5 + 0.5;
        targetYaw = gActivePlayerState->targetYaw;
        delta = gCurrentActor->yaw - targetYaw;
        if (delta > 0) {
            dist = delta;
        } else {
            dist = -delta;
        }
        if (dist > 2048.0f) {
            dist = 4096.0f - dist;
        }
        if (dist > 400.0f) {
            dist = 400.0f;
        }
        dist = dist * (gActivePlayerState->turnRate / 400.0);
        mathAngleStepToward(&gCurrentActor->yaw, targetYaw, (s16)(dist * scale));
    }
    mathAngleStepToward(&gCurrentActor->roll, 0, 0x10);
    mathAngleStepToward(&gCurrentActor->pitch, 0, 0x10);
    gActivePlayerState->subTimer = 0;
    gActivePlayerState->pitchAngle = gCurrentActor->yaw;
    gActivePlayerState->actionTimer = D_8075395C[gCurrentCharacterIndex];
    gActivePlayerState->targetSpeed = gKongSwimTopSpeeds[gCurrentCharacterIndex] * gPlayerPadState[gCurrentPlayerIndex].stickMagNorm;
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x4000) {
        gActivePlayerState->targetSpeed = gActivePlayerState->targetSpeed * 1.33;
    }
}

void playerInputUpdateStickTurnYawFast(void) {
    f32 dist;
    f32 scale;
    s16 targetYaw;
    s32 delta;

    playerUpdateMoveTargetFromStick();
    if (gActivePlayerState->maxSpeed != 0.0f) {
        scale = gPlayerPadState[gCurrentPlayerIndex].stickMagNorm * 0.5 + 0.5;
        targetYaw = gActivePlayerState->targetYaw;
        delta = gCurrentActor->yaw - targetYaw;
        if (delta > 0) {
            dist = delta;
        } else {
            dist = -delta;
        }
        if (dist > 2048.0f) {
            dist = 4096.0f - dist;
        }
        if (dist > 400.0f) {
            dist = 400.0f;
        }
        dist = dist * 0.45;
        mathAngleStepToward(&gCurrentActor->yaw, targetYaw, (s16)(dist * scale));
    }
    mathAngleStepToward(&gCurrentActor->roll, 0, 0x10);
    mathAngleStepToward(&gCurrentActor->pitch, 0, 0x10);
}

void playerInputCalculateTurnStep(void) {
    s16 pad;
    s16 target;
    s16 ang;
    s16 rollStep;

    ang = gCurrentActor->yaw;
    rollStep = 0x10;
    if (gPlayerPadState[gCurrentPlayerIndex].stickAbsX != 0) {
        if (gPlayerCharacterId[gCurrentPlayerIndex] == 7) {
            ang -= gPlayerPadState[gCurrentPlayerIndex].stickX * 0.8;
        } else {
            ang -= gPlayerPadState[gCurrentPlayerIndex].stickX * 0.5;
        }
        gCurrentActor->yaw = ang & 0xFFF;
        target = gKongStickTurnRates[gCurrentCharacterIndex] * ((gPlayerPadState[gCurrentPlayerIndex].stickX >= 0) ? 1 : -1);
        target &= 0xFFF;
    } else {
        target = 0;
    }
    mathAngleStepToward(&gCurrentActor->pitch, target, 0x10);
    target = (gKongStickRollAngles[gCurrentCharacterIndex] * gPlayerPadState[gCurrentPlayerIndex].stickY) / 70;
    target = target & 0xFFF;
    if (gPlayerCharacterId[gCurrentPlayerIndex] == 7) {
        rollStep = ((gPlayerPadState[gCurrentPlayerIndex].stickY * 0.5 > 0.0) ? gPlayerPadState[gCurrentPlayerIndex].stickY * 0.5 : -(gPlayerPadState[gCurrentPlayerIndex].stickY * 0.5)) + 16.0;
    }
    mathAngleStepToward(&gCurrentActor->roll, target, rollStep);
}

void playerInputHandleAButtonJumpQueue(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    playerStateQueueCallback(1, 0, gCurrentPlayerIndex);
}

void playerInputInitDashParams(void) {
    gActivePlayerState->subTimer = 0;
    gActivePlayerState->pitchAngle = gCurrentActor->yaw;
    if (gActivePlayerState->actionTimer == 0) {
        gActivePlayerState->actionTimer = 1;
        gActivePlayerState->targetSpeed = gKongUnderwaterEntryThrustSpeeds[gCurrentCharacterIndex];
    }
}

void playerInputCheckAButtonScriptTrigger(void) {
    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000)) {
        actorScriptStartByIndex(gCurrentActor, 0x37);
        gCurrentActor->subState = 4;
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
}

void playerInputHandleBButtonDiveAttack(void) {
    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000)) {
        actorScriptStartByIndex(gCurrentActor, 0x37);
        gCurrentActor->subState = 4;
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
}

void playerInputHandleBButtonRollingAttack(void) {
    gActivePlayerState->jumpTimer = gScheduler.tickCount;
    scriptSetActorRampTarget(gCurrentActor, 2.0f, 0.0f);
    actorScriptStartByIndex(gCurrentActor, 0x38);
    gCurrentActor->subState = 7;
}

void playerInputHandleBButtonSlideAttack(void) {
    actorScriptStartByIndex(gCurrentActor, 0x39);
    gCurrentActor->subState = 7;
}

void playerInputSetSubstate6(void) {
    gCurrentActor->subState = 6;
}

void playerInputHandleBButtonComboPunch(void) {
    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000)) {
        if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
            gActivePlayerState->subTimer = gCurrentActor->roll;
            gActivePlayerState->pitchAngle = gCurrentActor->yaw;
            if (gActivePlayerState->actionTimer == 0) {
                gActivePlayerState->targetSpeed = gKongSurfaceStrokeSpeeds[gCurrentCharacterIndex];
                actorScriptStartByIndex(gCurrentActor, 0x36);
            } else {
                gActivePlayerState->targetSpeed = gKongSurfaceStrokeRepeatSpeeds[gCurrentCharacterIndex];
            }
            gActivePlayerState->actionTimer = gKongSurfaceStrokeFrames[gCurrentCharacterIndex];
            gActivePlayerState->jumpStartTime = gScheduler.tickCount;
        } else if (!(gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000)) {
            gActivePlayerState->subTimer = gCurrentActor->roll;
            gActivePlayerState->pitchAngle = gCurrentActor->yaw;
            if (gActivePlayerState->actionTimer == 0) {
                gActivePlayerState->actionTimer = 1;
                gActivePlayerState->targetSpeed = gKongSurfaceStrokeRepeatSpeeds[gCurrentCharacterIndex];
            }
        }
    }
}

void playerInputHandleBButtonAttack(void) {
    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000)) {
        gActivePlayerState->subTimer = gCurrentActor->roll;
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        if (gActivePlayerState->actionTimer == 0) {
            gActivePlayerState->targetSpeed = gKongSurfaceStrokeSpeeds[gCurrentCharacterIndex];
            actorScriptStartByIndex(gCurrentActor, 0x36);
        } else {
            gActivePlayerState->targetSpeed = gKongSurfaceStrokeRepeatSpeeds[gCurrentCharacterIndex];
        }
        gActivePlayerState->actionTimer = gKongSurfaceStrokeFrames[gCurrentCharacterIndex];
        gActivePlayerState->jumpStartTime = gScheduler.tickCount;
    }
}

typedef struct ClimbActorState {
    /* 0x00 */ s16 inputLocked;
    /* 0x02 */ s16 stickX;
    /* 0x04 */ u8 pad4[0x28];
    /* 0x2C */ f32 junctionBlend;
    /* 0x30 */ u8 pad30[4];
    /* 0x34 */ u8 *flagsPtr;
    /* 0x38 */ u8 pad38[6];
    /* 0x3E */ u8 climbSpeed;
    /* 0x3F */ u8 rung;
    /* 0x40 */ u8 prevRung;
    /* 0x41 */ u8 pad41;
    /* 0x42 */ u8 leanDir;
} ClimbActorState;


void playerInputHandleAButtonSuperJump(void) {
    s32 btn;

    btn = gPlayerPadState[gCurrentPlayerIndex].pressedButtons;
    if (btn & 0x8000) {
        gCurrentActor->subState = 3;
        gActivePlayerState->subTimer = gCurrentActor->roll;
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        if (gActivePlayerState->actionTimer == 0) {
            gActivePlayerState->targetSpeed = 300.0f;
            actorScriptStart(gCurrentActor, 0x318);
        } else {
            gActivePlayerState->targetSpeed = 250.0f;
        }
        gActivePlayerState->actionTimer = 0xF;
        gActivePlayerState->jumpStartTime = gScheduler.tickCount;
        return;
    }
    if (!(btn & 0x4000)) {
        gActivePlayerState->subTimer = gCurrentActor->roll;
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        if (gActivePlayerState->actionTimer == 0) {
            gActivePlayerState->actionTimer = 1;
            gActivePlayerState->targetSpeed = 250.0f;
        }
    }
}

extern f32 gKongUnderwaterDecelRates[];

void playerInputHandleAButtonSuperJump2(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gCurrentActor->subState = 3;
        gActivePlayerState->subTimer = gCurrentActor->roll;
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        if (gActivePlayerState->actionTimer == 0) {
            gActivePlayerState->targetSpeed = 300.0f;
            actorScriptStart(gCurrentActor, 0x318);
        } else {
            gActivePlayerState->targetSpeed = 250.0f;
        }
        gActivePlayerState->actionTimer = 0xF;
        gActivePlayerState->jumpStartTime = gScheduler.tickCount;
    }
}


void playerInputHandleBButtonDashAttack(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gActivePlayerState->subTimer = gCurrentActor->roll;
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        gActivePlayerState->targetSpeed = gKongSurfaceStrokeSpeeds[gCurrentCharacterIndex];
        actorScriptStartByIndex(gCurrentActor, 0x36);
        gCurrentActor->subState = 3;
        gActivePlayerState->actionTimer = gKongSurfaceStrokeFrames[gCurrentCharacterIndex];
        gActivePlayerState->jumpStartTime = gScheduler.tickCount;
    }
}


void playerInputHandleCDownFairyCheck(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4) && !(gGlobalOverlayFlags & 2)) {
        playerInputTryEnterFairyCamera(8);
        return;
    }
    gActivePlayerState->subTimer = gCurrentActor->roll;
    gActivePlayerState->pitchAngle = gCurrentActor->yaw;
    gActivePlayerState->actionTimer = 0;
    gActivePlayerState->decelRate = 8.0f;
}

u8 playerInputCanPerformFairySnap(void) {
    s32 ok;

    ok = flagGet(0x182, 0) || (gGlobalOverlayFlags & 0x10000000) || gPlayerCount >= 2 || menuIsTransitionTypeC();
    return ok;
}


extern s16 gKongNormalSwimEnterDepths[];
extern f32 gKongSwimEnterDepths[];

void playerInputHandleCDownCameraSnap(void) {
    f32 minHeight;
    s32 btn;

    btn = gPlayerPadState[gCurrentPlayerIndex].pressedButtons;
    if ((btn & 4) && !(gGlobalOverlayFlags & 2)) {
        playerInputTryEnterFairyCamera(8);
        return;
    }
    if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) {
        minHeight = gKongNormalSwimEnterDepths[gCurrentCharacterIndex];
    } else {
        minHeight = gKongSwimEnterDepths[gCurrentCharacterIndex];
    }
    if ((btn & 0x2000) && (minHeight < gCurrentActor->distToFloor) && playerInputCanPerformFairySnap()) {
        playerStateQueueCallback(0x3E, 0, gCurrentPlayerIndex);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x10, 0xFF, 0x7F, 1);
    }
}

void playerInputSetCharacterDecelRate(void) {
    gActivePlayerState->decelRate = gKongUnderwaterDecelRates[gCurrentCharacterIndex];
}

void playerInputResetDecelRate(void) {
    gActivePlayerState->decelRate = 1.0f;
}

void playerInputSurfaceSwimBButtonNoop(void) {
}

void playerInputHandleLadderClimb(void) {
    ClimbActorState *st;
    PadInputState *pad;
    s8 stick;
    u8 state;

    st = gActivePlayerState->actor->customState;
    if (gCurrentActor->state == 7) {
        pad = &gPlayerPadState[gCurrentPlayerIndex];
        if (!(pad->heldButtons & 0x10)) {
            stick = pad->stickX;
            if (stick < -0x1E && gCurrentActor->sub4->model->animId != 0xFB) {
                actorScriptStartByIndex(gCurrentActor, 0x81);
                gCurrentActor->state = 0xA;
                gCurrentActor->subState = 0;
                st->leanDir = 1;
            } else if (stick >= 0x1F && gCurrentActor->sub4->model->animId != 0xFF) {
                actorScriptStartByIndex(gCurrentActor, 0x7D);
                gCurrentActor->state = 0xB;
                gCurrentActor->subState = 0;
                st->leanDir = 2;
            }
        }
    }
    stick = gPlayerPadState[gCurrentPlayerIndex].stickX;
    if ((stick < 0x1E && gCurrentActor->state != 0xA) || (stick >= -0x1D && gCurrentActor->state != 0xB)) {
        st->leanDir = 0;
        state = gCurrentActor->state;
        if (state != 0xA) {
            if (state == 0xB) {
                if (gCurrentActor->subState == 1) {
                    actorScriptStartByIndex(gCurrentActor, 0x7E);
                } else {
                    actorScriptStartByIndex(gCurrentActor, 0x80);
                }
                gCurrentActor->state = 7;
                gCurrentActor->subState = 0;
            }
        } else {
            if (gCurrentActor->subState == 1) {
                actorScriptStartByIndex(gCurrentActor, 0x82);
            } else {
                actorScriptStartByIndex(gCurrentActor, 0x80);
            }
            gCurrentActor->state = 7;
            gCurrentActor->subState = 0;
        }
    }
}

void playerInputUpdateLadderState(void) {
    ClimbActorState *st;

    st = gActivePlayerState->actor->customState;
    if (gActivePlayerState->stateFlags & 8) {
        st->climbSpeed = 4;
    } else {
        st->climbSpeed = (gPlayerPadState[gCurrentPlayerIndex].stickY * 0.5) + 60.0;
    }
    playerInputHandleLadderClimb();
}

void playerInputStepLadderClimb(void) {
    ClimbActorState *st;

    st = gActivePlayerState->actor->customState;
    if (st->inputLocked != 0) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = 0;
    }
    playerInputHandleLadderClimb();
    if (gActivePlayerState->stateFlags & 8) {
        st->climbSpeed = 3;
    } else {
        st->climbSpeed = (gPlayerPadState[gCurrentPlayerIndex].stickY / 1.5) + 80.0;
    }
    st->stickX = gPlayerPadState[gCurrentPlayerIndex].stickX;
}

extern s16 gLadderJumpSpeed;

void playerInputCheckLadderTopOrBottom(void) {
    ClimbActorState *st;
    u8 mirrored;
    s32 rungLimit;
    u8 oldRung;

    st = gActivePlayerState->actor->customState;
    if (st->inputLocked != 0) {
        gPlayerPadState[gCurrentPlayerIndex].stickX = 0;
    } else {
        mirrored = (gActivePlayerState->actor->state == 5) ? 1 : 0;
        rungLimit = (*st->flagsPtr & 0x80) ? 1 : 3;
        if (mirrored) {
            gPlayerPadState[gCurrentPlayerIndex].stickX = gPlayerPadState[gCurrentPlayerIndex].stickX * -1;
        }
        if (gActivePlayerState->stateFlags & 0x10000002) {
            gPlayerPadState[gCurrentPlayerIndex].stickX = gPlayerPadState[gCurrentPlayerIndex].stickX * -1;
        }
        if (gActivePlayerState->stateFlags & 0x10000002) {
            gPlayerPadState[gCurrentPlayerIndex].stickY = gPlayerPadState[gCurrentPlayerIndex].stickY * -1;
        }
        if ((*st->flagsPtr & 0xC0) &&
            ((gPlayerPadState[gCurrentPlayerIndex].stickX >= 0x1F && st->rung > 0) || (gPlayerPadState[gCurrentPlayerIndex].stickX < -0x1E && st->rung < rungLimit))) {
            gActivePlayerState->jumpTimer = gScheduler.tickCount;
            gActivePlayerState->actor->speedY = gLadderJumpSpeed;
            gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
            oldRung = st->rung;
            st->junctionBlend = 1.0f;
            st->prevRung = oldRung;
            if (gPlayerPadState[gCurrentPlayerIndex].stickX >= 0x1F) {
                st->rung = oldRung - 1;
                if (st->rung == 1) {
                    st->rung = 0;
                }
                actorScriptStartByIndex(gCurrentActor, mirrored ? 0x81 : 0x7D);
                actorScriptStart(gActivePlayerState->actor, mirrored ? 0x295 : 0x296);
            } else {
                st->rung = oldRung + 1;
                if (st->rung == 1 && (*st->flagsPtr & 0x40)) {
                    st->rung = 2;
                }
                actorScriptStartByIndex(gCurrentActor, mirrored ? 0x7D : 0x81);
                actorScriptStart(gActivePlayerState->actor, mirrored ? 0x296 : 0x295);
            }
        }
    }
    if (gActivePlayerState->stateFlags & 8) {
        st->climbSpeed = 3;
        gActivePlayerState->actor->speedXZ = 3.0f;
        return;
    }
    st->climbSpeed = (gPlayerPadState[gCurrentPlayerIndex].stickY / 1.5) + 80.0;
}

typedef struct LaneComponent {
    u8 lane;
    u8 targetLane;
    u8 pad2[2];
    u8 action;
    u8 pad5[3];
    f32 actionProgress;
    u8 padC[8];
    f32 boostAmount;
} LaneComponent;

typedef struct LaneActorState {
    u8 pad0[2];
    s16 stickInput;
    f32 throttle;
    f32 vineSpeed;
    f32 steer;
    f32 steerGain;
    u8 pad14[0xC];
    s32 braking;
    u8 pad24[1];
    u8 throttleHoldTimer;
    u8 pad26[3];
    u8 fireRequested;
    u8 pad2A[6];
    Actor *manager;
    u8 mode;
    u8 pad35[9];
    u8 targetSpeed;
    u8 pad3F[3];
    u8 stickDirection;
    u8 pad43[2];
    u8 inputLocked;
} LaneActorState;

typedef struct LaneActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ LaneComponent *component;
} LaneActor;





void playerInputRegisterAnimatedEffect(void) {
    LaneActorState *st;
    s16 yaw;

    st = gActivePlayerState->actor->customState;
    if (hudCanRender() != 0) {
        renderCallbacksRegister(actorDrawAnimatedEffect, gActivePlayerState->actor, 5);
    }
    yaw = gCurrentActor->yaw;
    if (yaw < 0x200 || yaw >= 0xE01) {
        st->stickInput = gPlayerPadState[gCurrentPlayerIndex].stickX;
    } else if (yaw >= 0x201 && yaw < 0x600) {
        s8 t;
        st->stickInput = gPlayerPadState[gCurrentPlayerIndex].stickY;
        t = gPlayerPadState[gCurrentPlayerIndex].stickX;
        gPlayerPadState[gCurrentPlayerIndex].stickX = gPlayerPadState[gCurrentPlayerIndex].stickY;
        gPlayerPadState[gCurrentPlayerIndex].stickY = t;
    } else if (yaw >= 0x601 && yaw < 0xA00) {
        st->stickInput = -gPlayerPadState[gCurrentPlayerIndex].stickX;
        gPlayerPadState[gCurrentPlayerIndex].stickX = -gPlayerPadState[gCurrentPlayerIndex].stickX;
        gPlayerPadState[gCurrentPlayerIndex].stickY = -gPlayerPadState[gCurrentPlayerIndex].stickY;
    } else {
        s8 t;
        st->stickInput = -gPlayerPadState[gCurrentPlayerIndex].stickY;
        t = gPlayerPadState[gCurrentPlayerIndex].stickX;
        gPlayerPadState[gCurrentPlayerIndex].stickX = -gPlayerPadState[gCurrentPlayerIndex].stickY;
        gPlayerPadState[gCurrentPlayerIndex].stickY = -t;
    }
    if (gPlayerPadState[gCurrentPlayerIndex].stickX < -0x1E) {
        gActivePlayerState->stateCountdown = 0x28;
        st->stickDirection = 1;
    } else if (gPlayerPadState[gCurrentPlayerIndex].stickX >= 0x1F) {
        gActivePlayerState->stateCountdown = 0x28;
        st->stickDirection = 2;
    } else if (gActivePlayerState->stateCountdown != 0) {
        gActivePlayerState->stateCountdown--;
    } else {
        st->stickDirection = 0;
    }
}

void playerInputSetClimbTimer20(void) {
    LaneActorState *st;

    st = gActivePlayerState->actor->customState;
    st->targetSpeed = 0x14;
}

void playerInputSetClimbTimer100(void) {
    LaneActorState *st;

    st = gActivePlayerState->actor->customState;
    st->targetSpeed = 0x64;
    if (gActivePlayerState->stateCountdown != 0) {
        gActivePlayerState->stateCountdown--;
    }
}

void playerInputSetClimbTimer50(void) {
    LaneActorState *st;

    if (!(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0xE000)) {
        st = gActivePlayerState->actor->customState;
        st->targetSpeed = 0x32;
    }
}

void playerInputUpdateSteerAnim(LaneActorState *st, s32 idleAnim, s32 moveAnim) {
    AnimSlot *sub;
    s32 n;
    f32 f;
    f32 h;
    f32 cur;

    sub = gActivePlayerActor->sub4->model;
    if (moveAnim != sub->animId) {
        if (idleAnim == sub->animId) {
            controllerAnimSetStateIfChanged(gActivePlayerActor, moveAnim, 0.0f, 5.0f);
            return;
        }
        if (gCurrentActor->sub4->model->speed >= 0.0f && sub->frame > 0.0f) {
            scriptSetRampValue(gActivePlayerActor, -1.0f, 0.0f);
        }
        if (gCurrentActor->sub4->model->frame == 0.0f) {
            controllerAnimSetStateIfChanged(gActivePlayerActor, moveAnim, 0.0f, 5.0f);
        }
    } else {
        cur = st->steer;
        f = (cur > 0.0f) ? cur : -cur;
        h = f - 0.2f;
        n = st->steerGain > 1.0 ? 8 : 5;
        cur = sub->frame;
        f = n * h * 1.25f;
        if (f - 1.0f <= cur && cur <= f + 1.0f) {
            n = 0;
        } else {
            n = f <= cur ? -1 : 1;
        }
        scriptSetRampValue(gActivePlayerActor, n, 5.0f);
    }
}

void playerInputReadLaneSteer(LaneActor *actor, LaneActorState *st) {
    s32 sign;
    s32 pullBack;
    f32 absX;
    f32 clamped;
    f32 steer;

    if (st->inputLocked == 0 && st->mode == 2) {
        pullBack = gPlayerPadState[gCurrentPlayerIndex].stickY < -0x14;
        sign = gPlayerPadState[gCurrentPlayerIndex].stickX >= 0 ? 1 : -1;
        absX = gPlayerPadState[gCurrentPlayerIndex].stickAbsX;
        clamped = (absX > 80.0f) ? 80.0f : absX;
        steer = clamped;
        steer *= sign;
        steer *= 0.0125f;
        st->steer = steer;
        st->steer *= sLaneSteerScale;
        if (st->braking == 0) {
            st->braking = (actor->base.speedXZ < sLaneBrakeMaxSpeed) & pullBack;
        } else {
            st->braking = pullBack;
        }
    } else {
        st->braking = 0;
        st->steer = 0.0f;
    }
}

void playerInputUpdateHeldActorVineClimb(void) {
    LaneActor *a;

    a = ((LaneActor *)gActivePlayerState->actor);
    if (a != NULL) {
        playerInputReadLaneSteer(a, a->base.customState);
    }
}

void playerInputSetHeldActorVineSpeed(void) {
    Actor *actor;
    LaneActorState *st;

    actor = gActivePlayerState->actor;
    if (actor != NULL) {
        st = actor->customState;
        st->vineSpeed = sHeldActorVineSpeed;
    }
}

void playerInputClearHeldActorVineSpeed(void) {
    Actor *a;
    LaneActorState *st;

    a = gActivePlayerState->actor;
    if (a != NULL) {
        st = a->customState;
        st->vineSpeed = 0.0f;
    }
}

void playerInputPlayHeldActorClimbSfx(void) {
    LaneActor *a;
    LaneActorState *st;
    s32 idleAnim;
    s32 leftAnim;
    s32 rightAnim;

    a = ((LaneActor *)gActivePlayerState->actor);
    if (a != NULL) {
        if (gCurrentActor->actorType == 4) {
            idleAnim = 0x1C7;
            leftAnim = 0x1C5;
            rightAnim = 0x1C6;
        } else {
            idleAnim = 0x53;
            leftAnim = 0x54;
            rightAnim = 0x55;
        }
        st = a->base.customState;
        playerInputReadLaneSteer(a, st);
        if (camIsCutsceneActive() == 0 && gActivePlayerActor->sub4->animId != 0x3B5) {
            if (st->steer < 0.2f && st->steer > -0.2f && idleAnim != gActivePlayerActor->sub4->model->animId) {
                if (gActivePlayerActor->sub4->model->speed >= 0.0f && gActivePlayerActor->sub4->model->frame > 0.0f) {
                    scriptSetRampValue(gActivePlayerActor, -1.0f, 5.0f);
                    return;
                }
                if (gCurrentActor->sub4->model->frame == 0.0f) {
                    controllerAnimSetStateIfChanged(gActivePlayerActor, idleAnim, 0.0f, 5.0f);
                }
            } else {
                if (st->steer < -0.2f) {
                    playerInputUpdateSteerAnim(st, idleAnim, leftAnim);
                    return;
                }
                if (st->steer > 0.2f) {
                    playerInputUpdateSteerAnim(st, idleAnim, rightAnim);
                }
            }
        }
    }
}

void playerInputScaleHeldActorVineClimb(void) {
    Actor *a;
    LaneActorState *st;

    a = gActivePlayerState->actor;
    if (a != NULL) {
        st = a->customState;
        if (st->inputLocked == 0 && st->mode == 2) {
            if (st->throttleHoldTimer == 0) {
                st->throttle = 1.1f;
            }
        } else {
            st->throttle = 0.0f;
        }
    }
}

void playerInputHandleZButtonReleaseVehicleThrottle(void) {
    Actor *a;
    LaneActorState *st;

    a = gActivePlayerState->actor;
    if (a != NULL) {
        st = a->customState;
        if (st->throttleHoldTimer == 0) {
            st->throttle = 0.0f;
        }
    }
}

void playerInputHandleAButtonVehicleJump(void) {
    LaneActor *a;
    LaneActorState *st;
    LaneComponent *o;

    a = ((LaneActor *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->base.customState;
        if (st->inputLocked == 0 && st->mode == 2) {
            o = a->component;
            if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
                o->action = 1;
            }
        }
    }
}

void playerInputHandleRButtonVehicleSharpTurn(void) {
    Actor *a;
    LaneActorState *st;

    a = gActivePlayerState->actor;
    if (a != NULL) {
        st = a->customState;
        if (st->inputLocked == 0 && st->mode == 2) {
            st->steerGain = 2.0f;
        } else {
            st->steerGain = 1.0f;
        }
    }
}

void playerInputHandleRButtonReleaseVehicleSharpTurn(void) {
    Actor *a;
    LaneActorState *st;

    a = gActivePlayerState->actor;
    if (a != NULL) {
        st = a->customState;
        st->steerGain = 1.0f;
    }
}

void playerInputStepLane(void) {
    LaneActor *a;
    LaneActorState *st;
    LaneComponent *o;
    s32 current;
    s32 target;
    s8 stickX;

    a = (LaneActor *)gActivePlayerState->actor;
    if (a != NULL) {
        if (gActivePlayerActor->sub4->model->animId != 0x22A) {
            controllerAnimSetStateIfChanged(gActivePlayerActor, 0x22A, 0.0f, 0.0f);
        }
        st = a->base.customState;
        if (st->inputLocked == 0 && st->manager->state == 2) {
            o = a->component;
            target = o->targetLane;
            current = o->lane;
            stickX = gPlayerPadState[gCurrentPlayerIndex].stickX;
            if (target == current && o->action == 0) {
                if (stickX >= 0x1F && current < 2) {
                    o->targetLane = current + 1;
                } else if (stickX < -0x1E) {
                    if (current > 0) {
                        o->targetLane = current - 1;
                    }
                }
                target = o->targetLane;
                if (target != current) {
                    o->action = 2;
                    o->actionProgress = 0.0f;
                }
            }
        }
    }
}

void playerInputHandleZButtonLaneRaceThrottle(void) {
    LaneActor *a;
    LaneActorState *st;
    LaneComponent *o;

    a = ((LaneActor *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->base.customState;
        if (st->mode != 0 && st->mode < 3 && st->inputLocked == 0) {
            o = a->component;
            st->throttle = o->boostAmount + 1.1;
        }
    }
}

void playerInputHandleZButtonReleaseLaneRaceThrottle(void) {
    LaneActor *a;
    LaneActorState *st;
    LaneComponent *o;

    a = ((LaneActor *)gActivePlayerState->actor);
    if (a != NULL) {
        st = a->base.customState;
        if (st->mode != 0 && st->mode < 3 && st->inputLocked == 0) {
            o = a->component;
            st->throttle = o->boostAmount;
        }
    }
}

void playerInputHandleAButtonLaneRaceFire(void) {
    Actor *a;
    LaneActorState *st;

    a = gActivePlayerState->actor;
    if (a != NULL) {
        st = a->customState;
        if (st->inputLocked == 0 && st->mode == 2 && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000)) {
            st->fireRequested = 1;
        }
    }
}

void playerInputHandleZButtonRideCrouch(void) {
    if (gCurrentActor->state == 7 && !(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x10)) {
        actorScriptStartByIndex(gCurrentActor, 0x7F);
        gCurrentActor->state = 8;
        gCurrentActor->subState = 0;
    }
}

typedef struct LockableActorState {
    /* 0x00 */ s16 locked;
} LockableActorState;



extern f32 gKongRideJumpVelocityY[];
extern s16 gKongDiveFrames[];
extern s16 gKongDiveAngles[];

void playerInputHandleZButtonReleaseRideCrouch(void) {
    if (gCurrentActor->subState == 1) {
        actorScriptStartByIndex(gCurrentActor, 0x7B);
    } else {
        actorScriptStartByIndex(gCurrentActor, 0x80);
    }
    gCurrentActor->state = 7;
    gCurrentActor->subState = 0;
}

void playerInputHandleAButtonJumpOff(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) && !(gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x10)) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    gCurrentActor->state = 9;
    gCurrentActor->subState = 0;
    gActivePlayerState->jumpVelocityY = gKongRideJumpVelocityY[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    actorScriptStartByIndex(gCurrentActor, 0x7C);
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
}

void playerInputHandleAButtonLadderJump(void) {
    LockableActorState *st;

    st = gActivePlayerState->actor->customState;
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    if (st->locked != 0) {
        return;
    }
    gActivePlayerState->actor->speedY = gLadderJumpSpeed;
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
    actorScriptStartByIndex(gCurrentActor, 0x7C);
    if (gCurrentActor->actorType == 2) {
        actorScriptStart(gActivePlayerState->actor, 0x294);
    } else {
        actorScriptStart(gActivePlayerState->actor, 0x293);
    }
}


void playerInputHandleRButtonFixedLook(void) {
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;

    if (!(gActivePlayerState->stateFlags & 0x10000000)) {
        if ((gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x10) && (gCurrentActor->state == 7)) {
            actorGetNodePos(gActivePlayerState->actor, 3, &x1, &y1, &z1);
            actorGetNodePos(gActivePlayerState->actor, 4, &x2, &y2, &z2);
            camSetFixedView(gActivePlayerState->camActor, x2, y2 + 8.0f, z2, (x2 - x1) + x2, (y2 - y1) + y2 + 5.0f, (z2 - z1) + z2, 1);
            gActivePlayerState->stateFlags |= 2;
            gCurrentActor->flags |= 0x400;
        } else {
            if (gActivePlayerState->stateFlags & 2) {
                gActivePlayerState->stateFlags &= ~2;
                camSetTargetScaled(gActivePlayerState->camActor, gActivePlayerState->actor, 4, 0x800, 0x28, 0, 5, 0x19, 0x14, 0, 0.15f);
                if (gCurrentActor->state == 7) {
                    actorScriptStartByIndex(gCurrentActor, 0x84);
                }
            }
            gCurrentActor->flags &= ~0x400;
        }
    }
}

void playerInputHandleBButtonSurfaceCharge(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gCurrentActor->state = 0x80;
        gCurrentActor->subState = 0;
        actorScriptStart(gCurrentActor, 0x316);
    }
}

void playerInputHandleBButtonUnderwaterCharge(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        gCurrentActor->state = 0x81;
        gCurrentActor->subState = 0;
        actorScriptStart(gCurrentActor, 0x316);
    }
}

void playerInputDiveFromSurface(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xA000) {
        gActivePlayerState->subTimer = gKongDiveAngles[gCurrentCharacterIndex];
        gActivePlayerState->pitchAngle = gCurrentActor->yaw;
        gActivePlayerState->actionTimer = gKongDiveFrames[gCurrentCharacterIndex];
        gCurrentActor->state = 0x7F;
        gCurrentActor->subState = 0;
        gCurrentActor->subState = 1;
        if (gCurrentActor->speedY > 0.0f) {
            gCurrentActor->speedY = 0.0f;
        }
        actorScriptStart(gCurrentActor, 0x318);
        sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x10, 0xFF, 0x7F, 1);
    }
}

extern s16 gKongNormalSwimSurfaceDepths[];
extern s16 gKongSwimSurfaceDepths[];

s32 playerInputPostUpdate(void) {
    f32 depth;
    f32 depthLimit;
    f32 pad;
    u8 ret;
    s32 snapDepth;

    ret = 0;
    gActivePlayerState->swimFrames = 0;
    snapDepth = 0x1E;
    if (gCurrentActor->contactFlags & 4) {
        if (gCurrentActor->speedY <= 0.0f) {
            gCurrentActor->speedY = MAX(gCurrentActor->speedY, -150.0f);
            depth = gCurrentActor->waterY - gCurrentActor->y;
            if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 2) {
                snapDepth = 0x3C;
            }
            if ((snapDepth < depth) && playerInputCanPerformFairySnap()) {
                playerStateQueueCallback(0x3E, 0, gCurrentPlayerIndex);
                playerClearCarriedItemState();
            } else if (gCurrentActor->contactFlags & 1) {
                if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) {
                    depthLimit = gKongNormalSwimEnterDepths[gCurrentCharacterIndex];
                } else {
                    depthLimit = gKongSwimEnterDepths[gCurrentCharacterIndex];
                }
                if (depthLimit < depth) {
                    playerStateQueueCallback(0x3D, 0, gCurrentPlayerIndex);
                    ret = 1;
                    playerClearCarriedItemState();
                }
            } else {
                if (gPlayerSlots[gCurrentPlayerIndex].sizeMode == 1) {
                    depthLimit = gKongNormalSwimSurfaceDepths[gCurrentCharacterIndex];
                } else {
                    depthLimit = gKongSwimSurfaceDepths[gCurrentCharacterIndex];
                }
                if (depthLimit < gCurrentActor->distToFloor + depth) {
                    playerStateQueueCallback(0x3D, 0, gCurrentPlayerIndex);
                    actorScriptStart(gCurrentActor, 0);
                    if (gActivePlayerState->sfxHandle) {
                        n_alSndpStop(gActivePlayerState->sfxHandle);
                    }
                    ret = 1;
                    playerClearCarriedItemState();
                }
            }
        }
    }
    return ret;
}

void playerInputTryEnterFairyCamera(s16 callbackId) {
    if (flagGet(0x179, 0)) {
        if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4) {
            playerTryEnterViewMode(callbackId, 0xB, 0);
        }
    }
}

void playerInputTryEnterFairyCameraOnLand(void) {
    if (!(gGlobalOverlayFlags & 2) && (gPlayerCharacterId[gCurrentPlayerIndex] < 5)) {
        playerInputTryEnterFairyCamera(6);
        gPlayerSlots[gCurrentPlayerIndex].fov = 45.0f;
    }
}

void playerInputHandleCDownFairyCamera(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) && ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 4)) {
        playerInputTryEnterFairyCameraOnLand();
    }
}

void playerLeaveFairyCamera(PlayerState *ps) {
    Actor *a;
    s32 flag;

    a = gCurrentActor;
    flag = (a->state == 5) || (a->state == 0x65);
    if ((gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4)) {
        if (flag) {
            playerTryEnterViewMode(7, 3, 0);
        } else {
            playerTryEnterViewMode(5, 3, 0);
        }
    } else {
        playerLeaveViewMode(a, flag);
    }
    slotQueueCancel(6, 1);
    slotQueueCancel(0xC, 1);
    ps->stateFlags &= ~0x8000;
}

void playerInputHandleCUpLeaveFairyCamera(void) {
    if (!(gActivePlayerState->stateFlags & 0x8000) && ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 8)) {
        playerLeaveFairyCamera(gActivePlayerState);
    }
}

void playerInputHandleCDownLeaveFairyCamera(void) {
    if (!(gActivePlayerState->stateFlags & 0x8000) && ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 4)) {
        playerLeaveFairyCamera(gActivePlayerState);
    }
}

void playerInputHandleZButtonLeaveFairyCamera(void) {
    if (!(gActivePlayerState->stateFlags & 0x8000) && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4)) {
        playerLeaveFairyCamera(gActivePlayerState);
    }
}


void playerInputTakeFairyPhoto(s32 newState) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
        if (!(gActivePlayerState->stateFlags & 0x8000)) {
            if (slotQueueGetValue(6, gCurrentPlayerIndex) > 0) {
                sfxPlayOnFreeSlot(0x263, 0x7FFF, 63.0f, 1.0f, 0xA, 0);
                gCurrentActor->state = newState;
                gCurrentActor->subState = 0;
                slotQueueAddValue(6, gCurrentPlayerIndex, -1);
                lightAdd(gPlayerSlots[gCurrentPlayerIndex].camX, gPlayerSlots[gCurrentPlayerIndex].camY, gPlayerSlots[gCurrentPlayerIndex].camZ, gPlayerSlots[gCurrentPlayerIndex].focusX, gPlayerSlots[gCurrentPlayerIndex].focusY, gPlayerSlots[gCurrentPlayerIndex].focusZ, 0.0f, 1, 0xFF, 0xFF, 0xFF);
            }
        }
    }
}

void playerInputHandleBButtonFairyPhoto(void) {
    playerInputTakeFairyPhoto(0x64);
}

void playerInputHandleBButtonFairyPhotoInWater(void) {
    playerInputTakeFairyPhoto(0x65);
}


s32 playerTryEnterViewMode(s16 callbackId, u8 param1, u8 param2) {
    if (((gPlayerCount < 2) || (gSplitScreenMode != 1)) && (gScreenFadeProgress == 0.0f) && (gCurrentActor->floorSlopeFactor == 0.0f)) {
        playerStateSetCallbackParameters(gCurrentPlayerIndex, param1, param2, 0);
        playerStateQueueCallback(callbackId, 0, gCurrentPlayerIndex);
        gCurrentActor->speedXZ = 0.0f;
        return 1;
    }
    return 0;
}


void playerInputHandleCUpCameraZoomIn(void) {
    CamState *state;
    s32 act;

    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 8) {
        state = gActivePlayerState->camActor->customState;
        if ((mpIsMatchType(0) == 0) && !(state->flags & 0x80000000)) {
            act = gCurrentActor->state;
            if (((act == 0x5D || act == 0x5E || act == 0x62) && !(gGlobalOverlayFlags & 0x80000000)) || act == 0x4E || act == 0x4F ||
                act == 0xD || act == 0xC) {
                playerTryEnterViewMode(5, 3, 0);
            }
        }
    }
}




void playerInputHandleCLeftEnterFirstPerson(void) {
    CamState *state;

    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) && (gCurrentActor->contactFlags & 1)) {
        state = gActivePlayerState->camActor->customState;
        if ((mpIsMatchType(0) == 0) && !(state->flags & 0x80000000) && !(gGlobalOverlayFlags & 0x80000000)) {
            playerTryEnterViewMode(5, 3, 1);
        }
    }
}

void playerInputHandleCUpMode7(void) {
    CamState *state;

    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 8) && (gCurrentActor->contactFlags & 1)) {
        state = gActivePlayerState->camActor->customState;
        if ((mpIsMatchType(0) == 0) && !(state->flags & 0x80000000) && !(gGlobalOverlayFlags & 0x80000000)) {
            playerTryEnterViewMode(5, 3, 1);
        }
    }
}

void playerInputHandleCUpEnterFirstPersonInWater(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 8) {
        playerTryEnterViewMode(7, 3, 0);
    }
}


void playerInputCycleCameraZoom(void) {
    CamState *state;
    u8 max;
    s32 cur;

    state = gActivePlayerState->camActor->customState;
    if ((gGlobalOverlayFlags & 1) && !(gGlobalCutsceneFlags & 2)) {
        max = 2;
    } else {
        max = 3;
    }
    cur = state->zoomLevel;
    if ((cur != 0) && ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 4) && ((state->preferredZoomLevel == max) || (state->wallCollisionMode == 0))) {
        state->savedZoomLevel = cur;
        if (cur < max) {
            state->zoomLevel = cur + 1;
        } else {
            state->zoomLevel = 1;
        }
        camSetZoomLevel(gActivePlayerState->camActor, state->zoomLevel);
        state->preferredZoomLevel = state->zoomLevel;
        if ((state->zoomLevel != state->savedZoomLevel) && ((state->roomHeight == 0) || (state->roomHeight >= 0x96)) && (state->mode != 2)) {
            sfxPlayOnFreeSlot(0x27, 0x7FFF, 63.0f, 1.0f, 0, 0);
        }
        state->repositionFrames = 0xB;
        state->fastBlendFrames = 0xF;
    }
}

void playerInputCamRotateLeft(void) {
    CamState *state;

    state = gActivePlayerState->camActor->customState;
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 2) && (state->repositionFrames < 3)) {
        state->pendingTurn -= 0x2D;
        state->repositionFrames = 0xB;
    }
}

void playerInputCamRotateRight(void) {
    CamState *state;

    state = gActivePlayerState->camActor->customState;
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 1) && (state->repositionFrames < 3)) {
        state->pendingTurn += 0x2D;
        state->repositionFrames = 0xB;
    }
}


f32 aimStickSpeedScale(void) {
    return (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) ? 0.2 : 1.0;
}

void cameraZoomIn(void) {
    f32 limit;
    f32 next;
    s32 buttons;

    buttons = gPlayerPadState[gCurrentPlayerIndex].heldButtons;
    if (!(buttons & 0x2000) && !(buttons & 2) && (gCurrentActor->state == 2)) {
        limit = (gCurrentMap == 0x22) ? 15.0 : 13.0;
        next = gPlayerSlots[gCurrentPlayerIndex].fov - 1.5f;
        if (limit < next) {
            gPlayerSlots[gCurrentPlayerIndex].fov = next;
            sfxPlayActorSound(gCurrentActor, 0x1F0, 0, 0, 0, 0xFF, 1.0f, -1);
            return;
        }
        gPlayerSlots[gCurrentPlayerIndex].fov = limit;
        sfxStopSlotSound(gCurrentActor, 0);
    }
}

void cameraZoomOut(void) {
    f32 next;
    s32 buttons;

    buttons = gPlayerPadState[gCurrentPlayerIndex].heldButtons;
    if (!(buttons & 0x2000) && !(buttons & 1) && (gCurrentActor->state == 2)) {
        next = gPlayerSlots[gCurrentPlayerIndex].fov + 1.5f;
        if (next < 45.0) {
            gPlayerSlots[gCurrentPlayerIndex].fov = next;
            sfxPlayActorSound(gCurrentActor, 0x1F0, 0, 0, 0, 0xFF, 1.0f, -1);
            return;
        }
        gPlayerSlots[gCurrentPlayerIndex].fov = 45.0f;
        sfxStopSlotSound(gCurrentActor, 0);
    }
}

void cameraZoomStopSound(void) {
    u16 buttons;

    buttons = gPlayerPadState[gCurrentPlayerIndex].heldButtons & 3;
    if ((buttons != 2) && (buttons != 1)) {
        sfxStopSlotSound(gCurrentActor, 0);
    }
}


void playerInputPostUpdateFirstPerson(void) {
    if (playerInputPostUpdate()) {
        playerLeaveViewMode(gCurrentActor, 1);
    }
}

void playerInputUpdateStickFirstPersonAim(void) {
    cameraZoomStopSound();
    playerInputPostUpdateFirstPerson();
}

void aimUpdateFromStick(void) {
    CamState *state;
    s16 *angle;
    f32 *dist;
    f32 scale;

    if (!(gActivePlayerState->stateFlags & 0x8000)) {
        state = gActivePlayerState->camActor->customState;
        angle = &state->orbitYaw;
        *angle = *angle - aimStickSpeedScale() * (gPlayerPadState[gCurrentPlayerIndex].stickX * 0.08) * 4096.0 / 360.0;
        dist = &state->followHeightGoal;
        scale = aimStickSpeedScale();
        *dist = gPlayerPadState[gCurrentPlayerIndex].stickY * 0.04 * scale + *dist;
        *angle &= 0xFFF;
        if (state->aimHeightBase + 0x32 < *dist) {
            *dist = state->aimHeightBase + 0x32;
        } else if (*dist < state->aimHeightBase - 0x50) {
            *dist = state->aimHeightBase - 0x50;
        }
        gActivePlayerState->camActor->distToFloor = *dist;
        gCurrentActor->yaw = (state->orbitYaw + 0x800) & 0xFFF;
    }
}

void playerInputHandleAButtonAimRight(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC000) == 0x8000) {
        playerLeaveViewMode(gCurrentActor, 0);
    }
}

void playerInputHandleBButtonAimLeft(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC000) == 0x4000) {
        playerLeaveViewMode(gCurrentActor, 0);
    }
}

void playerInputHandleAButtonAimUp(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC000) == 0x8000) {
        playerLeaveViewMode(gCurrentActor, 1);
    }
}

void playerInputHandleBButtonAimDown(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC000) == 0x4000) {
        playerLeaveViewMode(gCurrentActor, 1);
    }
}

void playerInputHandleCUpLeaveFirstPerson(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 8) {
        playerLeaveViewMode(gCurrentActor, 0);
    }
}


void playerInputHandleCDownLeaveFirstPerson(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4)) {
        playerInputTryEnterFairyCameraOnLand();
        return;
    }
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 4) {
        playerLeaveViewMode(gCurrentActor, 0);
    }
}

void playerInputHandleCUpLeaveFirstPersonInWater(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 8) {
        playerLeaveViewMode(gCurrentActor, 1);
    }
}

void playerInputHandleCDownLeaveFirstPersonInWater(void) {
    if ((gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) && (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 4) && !(gGlobalOverlayFlags & 2)) {
        playerInputTryEnterFairyCamera(8);
        return;
    }
    if ((gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0xC) == 4) {
        playerLeaveViewMode(gCurrentActor, 1);
    }
}


void playerLeaveViewMode(Actor *actor, u8 isFirstPerson) {
    PlayerState *state;

    state = actor->customState;
    if (!(state->stateFlags2 & 0x10)) {
        sfxPlayOnFreeSlot(0x27, 0x7FFF, 63.0f, 1.0f, 0, 0);
    }
    if (isFirstPerson) {
        if (gPlayerCharacterId[gCurrentPlayerIndex] == 7) {
            if (actor->waterY - actor->y < 20.0f) {
                actor->state = 0x7E;
                actor->subState = 0;
            } else {
                actor->state = 0x7F;
                actor->subState = 0;
            }
        } else {
            actor->state = 0x4F;
            actor->subState = 3;
        }
    } else {
        actor->state = 1;
        actor->subState = 0;
        playerResumeLocomotion(actor);
        if (actor->state == 0xC) {
            actor->subState = 0xA;
        }
    }
    if (state->gunDrawn) {
        playerKongDrawGun(actor);
    } else {
        playerKongHolsterGun(actor);
    }
    actor->speedXZ = 0.0f;
    actor->yaw = camExitFirstPerson(state->camActor);
}

typedef struct LinkedComponent {
    /* 0x00 */ u8 pad0[0xE];
    /* 0x0E */ u8 mode;
} LinkedComponent;

typedef struct LinkedComponentActor {
    /* 0x000 */ Actor base;
    /* 0x178 */ LinkedComponent *component;
} LinkedComponentActor;


void playerInputHandleAButtonShopConfirm(void) {
    LinkedComponent *inner;

    inner = ((LinkedComponentActor *)gActivePlayerState->actor)->component;
    if (inner->mode == 5) {
        inner->mode = 10;
    }
}

void playerInputHandleBButtonShopDecline(void) {
    LinkedComponent *inner;

    inner = ((LinkedComponentActor *)gActivePlayerState->actor)->component;
    if (inner->mode == 5) {
        inner->mode = 0xF;
    }
}

void playerInputHandleAButtonGroundJump(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        gActivePlayerState->jumpTimer = gScheduler.tickCount;
    }
    if (!(gCurrentActor->contactFlags & 1)) {
        return;
    }
    if (gScheduler.tickCount - gActivePlayerState->jumpTimer >= 0xF) {
        return;
    }
    playerSetTerminalVelocity5B0();
    gCurrentActor->speedY = gKongJumpVelocityY[gCurrentCharacterIndex];
    gActivePlayerState->gravityDelay = 0;
    gActivePlayerState->airTimer = 0;
    gActivePlayerState->jumpTimer = gScheduler.tickCount - 0x1E;
    sfxPlayFromActorWithAltitudeCheck(gCurrentActor, 0x309, 0xFF, 0x7F, 0);
}

void playerInputHandleBButtonPulse(void) {
    Actor *mid;

    mid = gActivePlayerState->actor;
    if (mid->state == 0) {
        if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x4000) {
            mid->state = 1;
        }
    }
}

void playerInputWiggleOffStatusEffect(void) {
    PadInputState *pad;
    s32 v;

    pad = &gPlayerPadState[gCurrentPlayerIndex];
    if ((pad->stickX >= 0x29) || (pad->stickY >= 0x29)) {
        if (gActivePlayerState->wiggleSide != 0.0f) {
            gActivePlayerState->wiggleSide = 0.0f;
            v = gActivePlayerState->statusEffectTimer - 5;
            if (v <= 0) {
                gActivePlayerState->statusEffectTimer = 1;
            } else {
                gActivePlayerState->statusEffectTimer = v;
            }
            return;
        }
    }
    if ((pad->stickX < -0x28) || (pad->stickY < -0x28)) {
        if (gActivePlayerState->wiggleSide == 0.0f) {
            gActivePlayerState->wiggleSide = 1.0f;
            v = gActivePlayerState->statusEffectTimer - 5;
            if (v <= 0) {
                gActivePlayerState->statusEffectTimer = 1;
            } else {
                gActivePlayerState->statusEffectTimer = v;
            }
        }
    }
}

void playerInputHandleAButtonReelGame(void) {
    Actor *mid;

    mid = gActivePlayerState->actor;
    if (gPlayerPadState[gCurrentPlayerIndex].pressedButtons & 0x8000) {
        switch (mid->state) {
            case 2:
                mid->state = 4;
                mid->subState = 0;
                break;
            case 5:
                mid->subState++;
                break;
        }
    }
}

void playerInputHandlerNoop3(void) {
}

void playerInputHandleCUpRotate120(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0x2000) {
        gCurrentActor->speedY = 0.0f;
    } else {
        gCurrentActor->speedY = 120.0f;
    }
}

void playerInputHandleCDownRotateMinus120(void) {
    if (gPlayerPadState[gCurrentPlayerIndex].heldButtons & 0xC) {
        gCurrentActor->speedY = 0.0f;
    } else {
        gCurrentActor->speedY = -120.0f;
    }
}
