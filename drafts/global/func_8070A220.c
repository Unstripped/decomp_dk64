// func_8070A220 (src/global/10E1D0.c): Stage 1: indexed vertex groups use keyed transform matrices; type 2 copies source vertex from destination. Compiles; frame/layout and helper argument recovery remain unmatched.
typedef struct R2F10E1D0c_Vec3 {
    f32 x;
    f32 y;
    f32 z;
} R2F10E1D0c_Vec3;

typedef f32 R2F10E1D0c_Matrix[4][4];

typedef struct R2F10E1D0c_Model {
    s32 unk0;
    s32 unk4;
    R2F10E1D0c_Vec3 *vertices;
} R2F10E1D0c_Model;

typedef struct R2F10E1D0c_AnimationEntry {
    s32 kind;
    s32 group;
    s32 start;
    s32 end;
    f32 scale;
    s32 source;
    s32 destination;
} R2F10E1D0c_AnimationEntry;

typedef struct R2F10E1D0c_Animation {
    s32 *counts;
    u16 **indices;
    R2F10E1D0c_AnimationEntry *entries;
} R2F10E1D0c_Animation;

void mtxMulAffineF(f32 *, f32 *, f32 *);
void mtxRotateZDegF(f32 *, f32);
void func_8070D07C(f32 *, f32 *, f32, f32, f32, f32, f32, f32, f32, f32);

void func_8070A220(R2F10E1D0c_Model *model, R2F10E1D0c_Animation *animation, s32 frame) {
    R2F10E1D0c_AnimationEntry *entry;
    R2F10E1D0c_Matrix rotation;
    R2F10E1D0c_Matrix source_matrix;
    R2F10E1D0c_Matrix step_matrix;
    R2F10E1D0c_Matrix matrix;
    s16 entry_index;

    for (entry_index = 0, entry = animation->entries; entry->kind != 0; entry_index++, entry++) {
        s32 frame_end = frame;

        if (frame < entry->start) {
            continue;
        }
        if (entry->end < frame) {
            frame_end = entry->end;
        }
        if (entry->kind == 1) {
            R2F10E1D0c_Vec3 *source = &model->vertices[entry->source];
            R2F10E1D0c_Vec3 *destination = &model->vertices[entry->destination];
            s32 count = animation->counts[entry->group];
            u16 *indices = animation->indices[entry->group];
            s32 i;

            func_8070D07C(&source_matrix[0][0], &matrix[0][0],
                source->x - destination->x, source->y - destination->y, source->z - destination->z,
                -source->x, -source->y, -source->z, 0.0f, 0.0f);
            mtxRotateZDegF(&rotation[0][0], entry->scale * (f32)(entry->start - frame_end));
            mtxMulAffineF(&rotation[0][0], &source_matrix[0][0], &step_matrix[0][0]);
            mtxMulAffineF(&matrix[0][0], &step_matrix[0][0], &matrix[0][0]);
            for (i = 0; i < count; i++) {
                R2F10E1D0c_Vec3 *vertex = &model->vertices[indices[i]];
                f32 x = vertex->x;
                f32 y = vertex->y;
                f32 z = vertex->z;

                vertex->x = matrix[3][0] + ((x * matrix[0][0]) + (y * matrix[1][0]) + (z * matrix[2][0]));
                vertex->y = matrix[3][1] + ((x * matrix[0][1]) + (y * matrix[1][1]) + (z * matrix[2][1]));
                vertex->z = matrix[3][2] + ((x * matrix[0][2]) + (y * matrix[1][2]) + (z * matrix[2][2]));
            }
        } else if (entry->kind == 2) {
            model->vertices[entry->source] = model->vertices[entry->destination];
        }
    }
}
