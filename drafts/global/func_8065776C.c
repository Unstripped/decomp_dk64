// func_8065776C (src/global/55B20.c): stage 2: frame must be 0x78 (locals 0x74 mx,0x70 my,0x6C ex,0x68 ey,0x64 vx,0x60 vy,0x40 x0,0x3C y2,0x38 y0). Target ALSO emits dead loads of ex/ey/vy/vx from 0x6C/0x68/0x60/0x64 at entry (into fs3/fs4/ft5/ft4) and dead stores of vx/vy/ex/ey at 0x64/0x60/0x6C/0x68 just before return 1 - these 4 locals are read before written, so the source must read them pre-loop; FCR map: vx=ft4 vy=ft5 ex=fs3 ey=fs4. Cross test is dx*ey-dy*ex vs (mx-vx)*ey-(my-vy)*ex, both in f64 vs 0.0 (f32 0.0 pair fs0/fs0f); mid = (x0+x2)*0.5 in f64 (untyped 0.5)
#include "common.h"

typedef struct {
    f32 x[4];
    f32 y[4];
    f32 px;
    f32 py;
} M55P5Quad;

s32 func_8065776C(M55P5Quad *arg0) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 vx;
    f32 vy;
    f32 ex;
    f32 ey;
    f32 dx;
    f32 dy;
    f32 cross;
    f32 cross2;
    s32 i;

    sp74 = (arg0->x[0] + arg0->x[2]) * 0.5;
    sp70 = (arg0->y[0] + arg0->y[2]) * 0.5;
    sp40 = arg0->x[0];
    sp38 = arg0->y[0];
    sp3C = arg0->y[2];

    i = 0;
    do {
        switch (i) {
        case 0:
            vx = sp40;
            vy = sp38;
            ex = arg0->x[1] - vx;
            ey = arg0->y[1] - vy;
            break;
        case 1:
            vx = arg0->x[1];
            vy = arg0->y[1];
            ex = arg0->x[2] - vx;
            ey = sp3C - vy;
            break;
        case 2:
            vx = arg0->x[2];
            vy = sp3C;
            ex = arg0->x[3] - vx;
            ey = arg0->y[3] - vy;
            break;
        case 3:
            vx = arg0->x[3];
            vy = arg0->y[3];
            ex = sp40 - vx;
            ey = sp38 - vy;
            break;
        }
        dx = arg0->px - vx;
        dy = arg0->py - vy;
        cross = dx * ey - dy * ex;
        if (cross != 0.0) {
            cross2 = (sp74 - vx) * ey - (sp70 - vy) * ex;
            if (cross > 0.0) {
                if (cross2 <= 0.0) {
                    return 0;
                }
            } else if (cross2 >= 0.0) {
                return 0;
            }
        }
        i++;
    } while (i != 4);
    sp68 = ey;
    sp6C = ex;
    sp60 = vy;
    sp64 = vx;
    return 1;
}
