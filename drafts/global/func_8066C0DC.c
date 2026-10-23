// func_8066C0DC (src/global/6AD90.c): quicksort with Hoare partition, size=20 multu vs shift diff
void func_8066C0DC(void *arg0, s32 low, s32 high) {
    R1EBufferItem *arr = (R1EBufferItem *)arg0;
    s32 i;
    s32 j;
    u32 pivot;
    R1EBufferItem *pivot_ptr;
    s32 size = 20;
    u32 temp0;
    s32 temp1;
    s32 temp2;
    s32 temp3;
    u8 temp4;

    while (low < high) {
        pivot_ptr = (R1EBufferItem *)((u8 *)arr + high * size);
        pivot = pivot_ptr->unk0;
        i = low - 1;
        j = high;

        while (1) {
            while (arr[++i].unk0 < pivot && i < high)
                ;
            while (pivot < arr[--j].unk0 && low < j)
                ;
            if (i < j) {
                temp0 = arr[i].unk0;
                temp1 = arr[i].unk4;
                temp2 = arr[i].unk8;
                temp3 = arr[i].unkC;
                temp4 = arr[i].unk10;
                arr[i].unk0 = arr[j].unk0;
                arr[i].unk4 = arr[j].unk4;
                arr[i].unk8 = arr[j].unk8;
                arr[i].unkC = arr[j].unkC;
                arr[i].unk10 = arr[j].unk10;
                arr[j].unk0 = temp0;
                arr[j].unk4 = temp1;
                arr[j].unk8 = temp2;
                arr[j].unkC = temp3;
                arr[j].unk10 = temp4;
            } else {
                break;
            }
        }

        temp0 = arr[i].unk0;
        temp1 = arr[i].unk4;
        temp2 = arr[i].unk8;
        temp3 = arr[i].unkC;
        temp4 = arr[i].unk10;
        arr[i].unk0 = pivot_ptr->unk0;
        arr[i].unk4 = pivot_ptr->unk4;
        arr[i].unk8 = pivot_ptr->unk8;
        arr[i].unkC = pivot_ptr->unkC;
        arr[i].unk10 = pivot_ptr->unk10;
        pivot_ptr->unk0 = temp0;
        pivot_ptr->unk4 = temp1;
        pivot_ptr->unk8 = temp2;
        pivot_ptr->unkC = temp3;
        pivot_ptr->unk10 = temp4;

        func_8066C0DC(arr, low, i - 1);
        low = i + 1;
    }
}
