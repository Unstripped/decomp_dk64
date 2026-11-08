#include "common.h"

f32 floatCeil(f32 val) {
    s32 intVal;

    intVal = (s32)val;
    intVal = intVal;
    if ((val - (f32)intVal) > 0.00001f) {
        intVal = intVal + 1;
    }
    return (f32)intVal;
}
