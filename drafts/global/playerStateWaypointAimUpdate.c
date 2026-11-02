// playerStateWaypointAimUpdate (src/global/F56F0.c): UNPARKED 2026-11-02: park was 456 insns vs target 455 (count-inexact parks stay drafts); playerStateWaypointAimUpdate (src/global/F56F0.c): MidA: stage 6, diff 6 (unchanged best; parked NON_MATCHING in F56F0). Mechanism found (uopt -l5/-l6): 'close' must land in t2 because the (flags==0)&1 expr cand (uand, 55) must be coloured BEFORE the u8 'close' ucvtl cand (46); both adjsave 0.75 and 46 wins the number tie, so close takes a1 (ord 4) and the uand t2. Any extra basic block in close's live range drops 46's adjsave to 0.6 and flips it (a dead test at the START of the then-block or between yaw/pitch stores both flip; symbol irrelevant). But a dead test between the stores makes the arg0 reload (lw t7,80(sp)) = the stored 6 diff; a test at block start (no reload) gives text 22 / shape 0 ONLY with 'arg0->pitch = 0 * (s32)gWaypointCursor' (needed for the a3 &gWaypointCursor pointerization; folded, but costs one hidden ring pick => lui t8 vs t7 cascade), plain pitch=0 loses a3. Also needed there: drop the yawT temp (eq = *F5L1_YAWP == gWaypointIndex + 2; if (eq)). hill-climb (dead tests, annealing, decl swaps, constrained to no split between yaw/pitch) 22->10 only with the reload back. Untried: another way to reference &gWaypointCursor for pointerization with no ring pick. || W3IntC 2026-11-02 (unchanged 6): re-ran 3 annealers (stored base + FAKE-free base, 40 dead forms on locals/globals/fields, ~45k evals) and grids over the then-block test positions x forms (10^4) and pitch-store spellings ('0 * (s32)gWaypointCursor', (s8)): none below 6 (best other: full 9). The reload 'lw t7,80(sp)' only disappears when no block boundary sits between the yaw/pitch stores, which loses close in t2 (text 22).
typedef struct F5L1Control {
    u16 flags;
    s8 yaw;
    s8 pitch;
} F5L1Control;

typedef struct F5L1Waypoint {
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
} F5L1Waypoint;

typedef struct F5L1Target {
    u8 pad0[0x1F0];
    s32 flags;
} F5L1Target;

typedef struct F5L1CamBlock {
    u8 pad0[0x210];
    f32 x;
    u8 pad214[4];
    f32 z;
    u8 pad21C[0xC];
    f32 targetX;
    u8 pad22C[4];
    f32 targetZ;
} F5L1CamBlock;

#define F5L1Cam ((F5L1CamBlock *)gPlayerSlots)
#define F5L1_MAX(a, b) ((a) > (b) ? (a) : (b))
#define F5L1_MIN(a, b) ((a) < (b) ? (a) : (b))
#define F5L1_CLAMP(x) F5L1_MIN(F5L1_MAX(x, -128.0f), 127.0f)

void playerInitMoveParams(void);
s32 playerStateQueueCallback();
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
extern u8 D_807444EC;
extern u8 D_8076A0B3;
#define F5L1_B8 (*(s8 *)&D_807463B8)
#define F5L1_YAWP (*(s16 **)&gWaypointPathEntry)
#define F5L1_WP (*(F5L1Waypoint **)&gWaypointCursor)
#define F5L1_TGTA (*(Actor **)&gWaypointActor)

void playerStateWaypointAimUpdate(F5L1Control *arg0, s32 arg1) {
    F5L1Target *tgt;
    f32 ang;
    f32 camAng;
    f32 pitch;
    F5L1Waypoint *cur;
    F5L1Waypoint *next;
    f32 blend;
    f32 speed;
    s16 yawT;
    s32 eq;
    f32 dx;
    f32 dz;
    u8 close;
    u8 flags;
    s16 pitchT;

    cur = F5L1_WP;
    tgt = F5L1_TGTA->unk174;
    blend = 0.2f;
    next = F5L1_WP + 1;
    speed = (u32)cur->speed * 0.7;
    dx = F5L1_TGTA->unk7C - next->x;
    dz = F5L1_TGTA->unk84 - next->z;
    close = dx * dx + dz * dz < 100.0f;
    if (close) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    flags = gWaypointFlags;
    if (cur->speed) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if ((flags == 0) & 1) {
        gWaypointFlags |= 1;
        arg0->yaw = 0;
        if (gWaypointCursor != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        arg0->pitch = 0;
        if (gWaypointPathEntry == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    }
    if (gWaypointFlags || gWaypointCallbackParam) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    if (close) {
        yawT = *F5L1_YAWP; // FAKE: s16 temp steers uopt candidate priorities
        eq = yawT == gWaypointIndex + 2; // FAKE: bool temp steers uopt candidate priorities
        if (eq) {
            F5L1_B8 = 0;
            if (D_807444EC == 0) {
                D_8076A0B1 &= 0xFFEF;
                D_8076A0B3 = 0xFF;
                if ((flags == 0) & 1) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            }
            if (gWaypointCallbackId != 0) {
                if (gWaypointFlags != 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
                playerStateQueueCallback(gWaypointCallbackId, gWaypointCallbackParam, 0, &F5L1_WP); // FAKE: 4th arg keeps &F5L1_WP hoisted in $a3
            }
            tgt->flags |= 1;
            D_807FBB60 &= ~0x400;
            playerInitMoveParams();
        } else {
            gWaypointIndex += 1;
            F5L1_WP++;
            cur = F5L1_WP;
            next = cur + 1;
            if (gWaypointIndex || gWaypointFlags) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
        }
        if (gWaypointIndex + 1) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    }
    arg0->flags = 0;
    timerDecrementOrSetFlag(&arg0->flags, &cur->timer3, &cur->timer0, 0x8000);
    timerDecrementOrSetFlag(&arg0->flags, &cur->timer4, &cur->timer1, 0x4000);
    timerDecrementOrSetFlag(&arg0->flags, &cur->timer5, &cur->timer2, 0x2000);
    pitchT = 0;
    if (cur->delay != 0) {
        cur->delay = cur->delay - 1;
        yawT = 0;
    } else {
        if (gWaypointFlags & 2) {
            blend = 1.0f;
            gWaypointFlags &= 0xFFFD;
        }
        if (F5L1_TGTA->unk154 == 0x4F) {
            ang = mathAngleBetweenPointsDeg(next->x, next->z, (s32)F5L1_TGTA->unk7C, (s32)F5L1_TGTA->unk84) * 0.017453292f - (F5L1_TGTA->unkE6 * 3.1415927f) * 0.00048828125;
            pitch = mathCalculatePitchAngle(next->x, next->y, next->z, F5L1_TGTA->unk7C, F5L1_TGTA->unk80, F5L1_TGTA->unk84, 0);
            arg0->flags |= 0x4000;
            yawT = ang;
            pitchT = F5L1_CLAMP(sinApprox(pitch) * speed);
        } else {
            camAng = mathAngleBetweenPointsDeg((s32)F5L1Cam->targetX, (s32)F5L1Cam->targetZ, (s32)F5L1Cam->x, (s32)F5L1Cam->z);
            ang = mathAngleBetweenPointsDeg(next->x, next->z, (s32)F5L1_TGTA->unk7C, (s32)F5L1_TGTA->unk84) * 0.017453292f - camAng * 0.017453292f;
            yawT = F5L1_CLAMP(sinApprox(ang) * speed);
            pitchT = F5L1_CLAMP(cosApprox(ang) * speed);
        }
        if (gWaypointCallbackParam && gWaypointCallbackParam) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
    }
    arg0->yaw = arg0->yaw + (yawT - arg0->yaw) * blend;
    arg0->pitch = arg0->pitch + (pitchT - arg0->pitch) * blend;
}
