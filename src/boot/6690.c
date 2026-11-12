#include "common.h"
#include "render.h"
#include "proto/boot/6690.h"

void dlInitTextureDescriptor(texDesc, texture, pal, width, rectWidth, rectHeight, format, type, s, t) // FAKE: K&R definition keeps callers passing promoted ints (callee prototype steer)
    TextureDescriptor *texDesc;
    void *texture;
    s32 pal;
    s16 width;
    s16 rectWidth;
    s16 rectHeight;
    u8 format;
    u8 type;
    s16 s;
    s16 t;
{
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
