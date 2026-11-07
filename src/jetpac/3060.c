#include "common.h"
s32 randomNonNegative(void);


u32 jetpacCheckAabbOverlap(f32 minX1, f32 minY1, f32 maxX1, f32 maxY1, f32 minX2, f32 minY2, f32 maxX2, f32 maxY2) {
    minX1 = (minX2 < minX1) ? minX1 : minX2;
    minY1 = (minY2 < minY1) ? minY1 : minY2;
    maxX1 = (maxX1 < maxX2) ? maxX1 : maxX2;
    maxY1 = (maxY1 < maxY2) ? maxY1 : maxY2;
    if (minX1 <= maxX1 && minY1 <= maxY1) {
        return 1;
    }
    return 0;
}

void jetpacWrapSpanX(f32 minX, f32 maxX, f32 *outSpan1Min, f32 *outSpan1Max, f32 *outSpan2Min, f32 *outSpan2Max) {
    f32 wrappedMinX;
    f32 wrappedMinX2;
    f32 wrappedMaxX;
    f32 wrappedMaxX2;

    if (minX < 0.0f) {
        if (maxX <= 0.0f) {
            wrappedMinX = minX + 256.0f;
            wrappedMaxX = maxX + 256.0f;
            *outSpan1Min = wrappedMinX;
            *outSpan1Max = wrappedMaxX;
            *outSpan2Min = wrappedMinX;
            *outSpan2Max = wrappedMaxX;
            return;
        }
        *outSpan1Min = 0.0f;
        *outSpan1Max = maxX;
        *outSpan2Min = minX + 256.0f;
        *outSpan2Max = 256.0f;
        return;
    }
    if (minX >= 256.0f) {
        wrappedMinX2 = minX - 256.0f;
        wrappedMaxX2 = maxX - 256.0f;
        *outSpan1Min = wrappedMinX2;
        *outSpan1Max = wrappedMaxX2;
        *outSpan2Min = wrappedMinX2;
        *outSpan2Max = wrappedMaxX2;
        return;
    }
    if (maxX > 256.0f) {
        *outSpan1Min = 0.0f;
        *outSpan1Max = maxX - 256.0f;
        *outSpan2Min = minX;
        *outSpan2Max = 256.0f;
        return;
    }
    *outSpan1Min = minX;
    *outSpan1Max = maxX;
    *outSpan2Min = minX;
    *outSpan2Max = maxX;
}

f32 jetpacRandFloat(void) {
    return (f32)((randomNonNegative() >> 15) % 60000) / 60000.0f;
}

int jetpacCheckAabbOverlapWrapped(f32 minX1, f32 minY1, f32 maxX1, f32 maxY1, f32 minX2, f32 minY2, f32 maxX2, f32 maxY2) {
    f32 span1A_min, span1A_max, span1B_min, span1B_max, span2A_min, span2A_max, span2B_min, span2B_max;
    jetpacWrapSpanX(minX1, maxX1, &span1A_min, &span1A_max, &span1B_min, &span1B_max);
    jetpacWrapSpanX(minX2, maxX2, &span2A_min, &span2A_max, &span2B_min, &span2B_max);
    return jetpacCheckAabbOverlap(span1A_min, minY1, span1A_max, maxY1, span2A_min, minY2, span2A_max, maxY2) || jetpacCheckAabbOverlap(span1B_min, minY1, span1B_max, maxY1, span2B_min, minY2, span2B_max, maxY2);
}

int jetpacIsOverRocket(f32 x) {
    return (165.0f <= x) && (x <= 171.0f);
}

typedef struct {
    f32 x;
    f32 y;
    s32 pad8[5];
    s32 min_x;
    s32 min_y;
    s32 max_x;
    s32 max_y;
} JetpacEntity;

f32 jetpacGetEntityCenterX(JetpacEntity *entity) {
    return (f32)((f64)(entity->x + (f32)entity->min_x) + (f64)(f32)(entity->max_x - entity->min_x) * 0.5);
}

f32 jetpacGetEntityCenterY(JetpacEntity *entity) {
    return (f32)((f64)(entity->y + (f32)entity->min_y) + (f64)(f32)(entity->max_y - entity->min_y) * 0.5);
}

f32 jetpacRoundFloat(f32 val) {
    if (val >= 0.0f) {
        return (f32)(s32)(val + 0.5f);
    }
    return (f32)(s32)(val - 0.5f);
}
