// func_8065776C (src/global/55B20.c): stage 5: prototyped f32 locals mx,my,ex,ey,vx,vy (decl order gives 0x60-0x74 slots + dead entry loads/exit stores), cross inlined (named f32 cross was spilled swc1 f0,84(sp); inlining 'dx*ey-dy*ex' twice gives CSE'd cvt.d.s in f0 as target). Frame 0x78 ok, size 130 vs 131? Remaining 17 text lines after random dead-statement search (rs.py): dy colours f2 where target has f14 (dx f12 ok), case0 first lwc1 is y0(0x38) in target vs x0, cross2 sub operand temps f12/f14 vs f6/f8. 7 FAKE stmts
typedef struct {
    f32 x[4];
    f32 y[4];
    f32 px;
    f32 py;
} S55eQuad;

#define Q ((S55eQuad *)arg0)
s32 func_8065776C(u8 *arg0) {
    f32 mx;
    f32 my;
    f32 ex;
    f32 ey;
    f32 vx;
    f32 vy;
    f32 dx;
    f32 dy;
    f32 cross;
    f32 cross2;
    s32 i;

    mx = (Q->x[0] + Q->x[2]) * 0.5;
    my = (Q->y[0] + Q->y[2]) * 0.5;
    for (i = 0; i != 4; i++) {
        switch (i) {
        case 0:
            vx = Q->x[0];
            vy = Q->y[0];
            ex = Q->x[1] - vx;
            ey = Q->y[1] - vy;
            if (mx == 0.0f) {} // FAKE: rs
            break;
        case 1:
            vx = Q->x[1];
            vy = Q->y[1];
            ex = Q->x[2] - vx;
            ey = Q->y[2] - vy;
            if (cross && cross) {} // FAKE: rs
            break;
        case 2:
            vx = Q->x[2];
            vy = Q->y[2];
            ex = Q->x[3] - vx;
            ey = Q->y[3] - vy;
            break;
        case 3:
            vx = Q->x[3];
            vy = Q->y[3];
            ex = Q->x[0] - vx;
            ey = Q->y[0] - vy;
            break;
        }
        dx = Q->px - vx;
        dy = Q->py - vy;
        if (1) {} // FAKE: rs
        if (dy > 0.0f) {} // FAKE: rs
        if (dx * ey - dy * ex != 0.0) {
            if (1) {} // FAKE: rs
            cross2 = (mx - vx) * ey - (my - vy) * ex;
            if (cross2 == 0) {}  // FAKE: deadsweep dead statement (steers uopt; replace with natural C)
            if (dx * ey - dy * ex > 0.0) {
                if (i) {} // FAKE: rs
                if (cross2 <= 0.0) {
                    return 0;
                }
            } else if (cross2 >= 0.0) {
                return 0;
            }
        }
    }
    return 1;
}
