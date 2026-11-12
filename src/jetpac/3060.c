#include "common.h"
#include "jetpac.h"
#include "proto/global/166A0.h"
#include "proto/jetpac/3060.h"

s32 jetpacCheckAabbOverlap(f32 minX1, f32 minY1, f32 maxX1, f32 maxY1, f32 minX2, f32 minY2, f32 maxX2, f32 maxY2) {
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
    f32 wrappedMin;
    f32 wrappedMax;

    if (minX < 0.0f) {
        if (maxX <= 0.0f) {
            wrappedMin = minX + 256.0f;
            wrappedMax = maxX + 256.0f;
            *outSpan1Min = wrappedMin;
            *outSpan1Max = wrappedMax;
            *outSpan2Min = wrappedMin;
            *outSpan2Max = wrappedMax;
            return;
        }
        *outSpan1Min = 0.0f;
        *outSpan1Max = maxX;
        *outSpan2Min = minX + 256.0f;
        *outSpan2Max = 256.0f;
        return;
    }
    if (minX >= 256.0f) {
        wrappedMin = minX - 256.0f;
        wrappedMax = maxX - 256.0f;
        *outSpan1Min = wrappedMin;
        *outSpan1Max = wrappedMax;
        *outSpan2Min = wrappedMin;
        *outSpan2Max = wrappedMax;
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
    return ((randomNonNegative() >> 15) % 60000) / 60000.0f;
}

int jetpacCheckAabbOverlapWrapped(f32 minX1, f32 minY1, f32 maxX1, f32 maxY1, f32 minX2, f32 minY2, f32 maxX2, f32 maxY2) {
    f32 aMin1, aMax1, bMin1, bMax1, aMin2, aMax2, bMin2, bMax2;

    jetpacWrapSpanX(minX1, maxX1, &aMin1, &aMax1, &bMin1, &bMax1);
    jetpacWrapSpanX(minX2, maxX2, &aMin2, &aMax2, &bMin2, &bMax2);
    return jetpacCheckAabbOverlap(aMin1, minY1, aMax1, maxY1, aMin2, minY2, aMax2, maxY2)
        || jetpacCheckAabbOverlap(bMin1, minY1, bMax1, maxY1, bMin2, minY2, bMax2, maxY2);
}

int jetpacIsOverRocket(f32 x) {
    return (165.0f <= x) && (x <= 171.0f);
}

f32 jetpacGetEntityCenterX(JetpacActor *actor) {
    return actor->x + actor->boxX1 + (f32)(actor->boxX2 - actor->boxX1) * 0.5;
}

f32 jetpacGetEntityCenterY(JetpacActor *actor) {
    return actor->y + actor->boxY1 + (f32)(actor->boxY2 - actor->boxY1) * 0.5;
}

f32 jetpacRoundFloat(f32 val) {
    if (val >= 0.0f) {
        return (s32)(val + 0.5f);
    }
    return (s32)(val - 0.5f);
}
