#include "common.h"

typedef struct {
    /* 0x00 */ s32 image;
    /* 0x04 */ s32 pal;
    /* 0x08 */ s16 width;
    /* 0x0A */ s16 rectWidth;
    /* 0x0C */ s16 rectHeight;
    /* 0x0E */ u8 format;
    /* 0x0F */ u8 type;
    /* 0x10 */ s16 s;
    /* 0x12 */ s16 t;
} TextureDescriptor;

void dlInitTextureDescriptor(TextureDescriptor *texDesc, s32 texture, s32 pal, s16 width, s16 rectWidth, s16 rectHeight, u8 format, u8 type, s16 s, s16 t) {
    texDesc->image = texture;
    texDesc->pal = pal;
    texDesc->width = width;
    texDesc->rectWidth = rectWidth;
    texDesc->rectHeight = rectHeight;
    texDesc->format = format;
    texDesc->type = type;
    texDesc->s = s;
    texDesc->t = t;
}
