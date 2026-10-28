// func_8070A220 (src/global/10E1D0.c): stage 3: 394 insns (same count) and callee-saved set (s0-s8,f20) OK, shape nearly identical (vertex loop 2x unroll, s3 loop-carried via off=idx*28, dx/dy/dz locals before angle, sum+m30 operand order, per-component float copy for kind 2, sidx/didx locals). Frame is 0x208 vs 0x200 and matrices 8 bytes high: need 2 fewer local words (try merging locals); then regalloc/scheduling (beqz delay order, one move position)
typedef f32 EaMatrix[4][4];

typedef struct EaVec3 {
    f32 x;
    f32 y;
    f32 z;
} EaVec3;

typedef struct EaModel {
    s32 unk0;
    s32 unk4;
    EaVec3 *vertices;
} EaModel;

typedef struct EaAnimEntry {
    s32 kind;
    s32 group;
    s32 start;
    s32 end;
    f32 scale;
    u32 source;
    u32 destination;
} EaAnimEntry;

typedef struct EaAnim {
    s32 *counts;
    u16 **indices;
    EaAnimEntry *entries;
} EaAnim;

void mtxMulAffineF(f32 *, f32 *, f32 *);
void mtxRotateZDegF(f32 *, f32);
void func_8070D07C(f32 *, f32 *, f32, f32, f32, f32, f32, f32);

void func_8070A220(EaModel *model, EaAnim *anim, s32 frame) {
    u32 sidx;
    u32 didx;
    EaMatrix m1B8;
    EaMatrix m178;
    EaMatrix m138;
    EaMatrix mF8;
    EaMatrix mB8;
    EaAnimEntry *entry;
    s16 idx;
    s32 i;
    s32 count;
    u16 *indices;
    s32 end;
    EaVec3 *src;
    EaVec3 *dst;
    EaVec3 *v;
    f32 angle;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 x;
    f32 y;
    f32 z;
    u32 j;
    s32 kindv;
    s32 off;

    for (idx = 0, off = 0, entry = anim->entries; *(s32 *)((u8 *)anim->entries + off) != 0; idx++, off = idx * 28, entry = (EaAnimEntry *)((u8 *)anim->entries + off)) {
        end = frame;
        if (frame < entry->start) {
            continue;
        }
        kindv = entry->kind;
        if (entry->end < frame) {
            end = entry->end;
        }
        switch (kindv) {
        case 1:
                sidx = entry->source;
                didx = entry->destination;
                src = &model->vertices[sidx];
                dst = &model->vertices[didx];
                dx = dst->x - src->x;
                dy = dst->y - src->y;
                dz = dst->z - src->z;
                angle = entry->scale * (f32)(entry->start - end);
                func_8070D07C(&m1B8[0][0], &m138[0][0],
                    -dx, -dy, -dz,
                    -src->x, -src->y, -src->z);
                mtxRotateZDegF(&m178[0][0], angle);
                mtxMulAffineF(&m178[0][0], &m1B8[0][0], &mB8[0][0]);
                mtxMulAffineF(&m138[0][0], &mB8[0][0], &mF8[0][0]);
                count = anim->counts[((EaAnimEntry *)((u8 *)anim->entries + off))->group];
                indices = anim->indices[((EaAnimEntry *)((u8 *)anim->entries + off))->group];
                for (i = 0; i < count; i++) {
                    j = indices[i];
                v = &model->vertices[j];
                    x = v->x;
                    y = v->y;
                    z = v->z;
                    v->x = x * mF8[0][0] + y * mF8[1][0] + z * mF8[2][0] + mF8[3][0];
                    model->vertices[j].y = x * mF8[0][1] + y * mF8[1][1] + z * mF8[2][1] + mF8[3][1];
                    model->vertices[j].z = x * mF8[0][2] + y * mF8[1][2] + z * mF8[2][2] + mF8[3][2];
                }
            break;
        case 2:
            sidx = entry->source;
            didx = entry->destination;
            model->vertices[sidx].x = model->vertices[didx].x;
            model->vertices[sidx].y = model->vertices[didx].y;
            model->vertices[sidx].z = model->vertices[didx].z;
            break;
        }
    }
}
