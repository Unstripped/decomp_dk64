// controllerBuildSubcommandList (src/global/17B90.c): stage 4+: matches frame 0x38, callee-saved set s0-s7,ra, stack layout; ~20 lines regalloc diff in inner loop and entry save scheduling
typedef struct ControllerSubCmd {
    u32 unk0;
    u32 unk4;
} ControllerSubCmd;

typedef struct ControllerSubNode {
    ControllerSubCmd *unk0;
    ControllerSubCmd *unk4;
    u8 unk8;
    struct ControllerSubNode *next;
} ControllerSubNode;

void *heapAlloc(s32);

void controllerBuildSubcommandList(ControllerSubCmd *arg0, ControllerSubCmd *arg1, ControllerSubNode **arg2) {
    ControllerSubCmd *curr;
    ControllerSubCmd *search;
    ControllerSubNode **tail;
    ControllerSubNode *node;
    u32 cmd0;
    u32 id;
    s32 found;
    u32 search_cmd;

    curr = arg0;
    tail = arg2;
    if (arg0 != arg1) {
        do {
            cmd0 = curr->unk0;
            if (((cmd0 >> 24) == (0, 0xDE)) && (((cmd0 >> 16) & 0xFF) == (0, 1))) {
                id = (u32)(curr->unk4 * 0x10) >> 0x1C;
                search = arg0;
                found = 0;
                if (arg0 != arg1) {
                    do {
                        search_cmd = search->unk0;
                        if (((search_cmd >> 24) == 0) && (id == search->unk4)) {
                            found = 1;
                        } else {
                            search++;
                        }
                    } while (!found && (search != arg1));
                }
                node = heapAlloc(sizeof(ControllerSubNode));
                *tail = node;
                tail = &node->next;
                node->unk8 = id;
                node->unk0 = curr + 1;
                node->unk4 = search;
            }
            curr++;
        } while (curr != arg1);
    }
    *tail = NULL;
}
