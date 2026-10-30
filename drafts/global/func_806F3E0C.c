// func_806F3E0C (src/global/F56F0.c): Stage 5 (parked NON_MATCHING in src copy): frame 0x50, saved set (none; t0-t3 + a3 hoist), block/opcode order identical, 455 insns. Remaining diff regalloc only: target close=t2, val716(u8 D_807FD716 CSE)=a2 with early lui a2, &D_807FD714=a0, ring scratch t7/t8; mine close=a1, val716=v1, &714=t2, yawT temp in a0. Matched pieces: 4-arg K&R playerStateQueueCallback with &D_807FD70C (keeps it in a3), next=D_807FD70C+1 (not cur+1: frame 0x68), D_807FD70C++;cur=D_807FD70C, close &= 0xFF (andi+move), u8 flags=D_807FD716, yawT=*D_807FD708 + eq temp, blend=1.0f before flag clear, 1 deadsweep dead if. Tried: permuter ~100 min total, deadsweep+local-extras beam (best 15 text lines but +1 insn), decl-order/stmt-order brute force (no effect), temp-naming sweep.
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

#define F5L1Cam ((F5L1CamBlock *)D_807FC924)
#define F5L1_MAX(a, b) ((a) > (b) ? (a) : (b))
#define F5L1_MIN(a, b) ((a) < (b) ? (a) : (b))
#define F5L1_CLAMP(x) F5L1_MIN(F5L1_MAX(x, -128.0f), 127.0f)

f32 sinApprox(f32);
f32 cosApprox(f32);
void func_806D03BC(void);
s32 playerStateQueueCallback();
f32 mathAngleBetweenPointsDeg(s32, s32, s32, s32);
f32 mathCalculatePitchAngle(f32, f32, f32, f32, f32, f32, s32);
extern u8 D_807444EC;
extern s8 D_807463B8;
extern u8 D_8076A0B1;
extern u8 D_8076A0B3;
extern s32 D_807FBB60;
extern s16 *D_807FD708;
extern F5L1Waypoint *D_807FD70C;
extern Actor *D_807FD710;
extern s16 D_807FD714;
extern s16 D_807FD718;
extern s32 D_807FD71C;

void func_806F3E0C(F5L1Control *arg0, s32 arg1) {
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
    s32 close;
    u8 flags;
    s16 pitchT;

    cur = D_807FD70C;
    tgt = D_807FD710->unk174;
    blend = 0.2f;
    next = D_807FD70C + 1;
    speed = (u32)cur->speed * 0.7;
    close = 0;
    dx = D_807FD710->unk7C - next->x;
    dz = D_807FD710->unk84 - next->z;
    if (dx * dx + dz * dz < 100.0f) {
        close = 1;
    }
    close &= 0xFF; // FAKE: andi + move of the close flag
    flags = D_807FD716;
    if ((flags == 0) & 1) {
        D_807FD716 |= 1;
        arg0->yaw = 0;
        arg0->pitch = 0;
    }
    if (close) {
        yawT = *D_807FD708; // FAKE: s16 temp steers uopt candidate priorities
        eq = yawT == D_807FD714 + 2; // FAKE: bool temp steers uopt candidate priorities
        if (eq) {
            D_807463B8 = 0;
            if (D_807444EC == 0) {
                D_8076A0B1 &= 0xFFEF;
                D_8076A0B3 = 0xFF;
            }
            if (D_807FD718 != 0) {
                playerStateQueueCallback(D_807FD718, D_807FD71C, 0, &D_807FD70C); // FAKE: 4th arg keeps &D_807FD70C hoisted in $a3
                if (D_807FD714 && D_807FD714) {} // FAKE: deadsweep, raises &D_807FD714 priority
            }
            tgt->flags |= 1;
            D_807FBB60 &= ~0x400;
            func_806D03BC();
        } else {
            D_807FD714 += 1;
            D_807FD70C++;
            cur = D_807FD70C;
            next = cur + 1;
        }
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
        if (D_807FD716 & 2) {
            blend = 1.0f;
            D_807FD716 &= 0xFFFD;
        }
        if (D_807FD710->unk154 == 0x4F) {
            ang = mathAngleBetweenPointsDeg(next->x, next->z, (s32)D_807FD710->unk7C, (s32)D_807FD710->unk84) * 0.017453292f - (D_807FD710->unkE6 * 3.1415927f) * 0.00048828125;
            pitch = mathCalculatePitchAngle(next->x, next->y, next->z, D_807FD710->unk7C, D_807FD710->unk80, D_807FD710->unk84, 0);
            arg0->flags |= 0x4000;
            yawT = ang;
            pitchT = F5L1_CLAMP(sinApprox(pitch) * speed);
        } else {
            camAng = mathAngleBetweenPointsDeg((s32)F5L1Cam->targetX, (s32)F5L1Cam->targetZ, (s32)F5L1Cam->x, (s32)F5L1Cam->z);
            ang = mathAngleBetweenPointsDeg(next->x, next->z, (s32)D_807FD710->unk7C, (s32)D_807FD710->unk84) * 0.017453292f - camAng * 0.017453292f;
            yawT = F5L1_CLAMP(sinApprox(ang) * speed);
            pitchT = F5L1_CLAMP(cosApprox(ang) * speed);
        }
    }
    arg0->yaw = arg0->yaw + (yawT - arg0->yaw) * blend;
    arg0->pitch = arg0->pitch + (pitchT - arg0->pitch) * blend;
}
