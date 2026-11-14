#include "common.h"
#include "proto/global/17B40.h"

f32 floatCeil(f32 val) {
    s32 intVal;

    intVal = (s32)val;
    if ((val - (f32)intVal) > 0.00001f) {
        intVal++;
    }
    return (f32)intVal;
}
