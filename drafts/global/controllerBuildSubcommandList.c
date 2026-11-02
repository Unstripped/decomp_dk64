// controllerBuildSubcommandList (src/global/17B90.c): controllerBuildSubcommandList (src/global/17B90.c): stage 4+; frame/regs/layout match; score 2 (down from 17): tail pointer is arg2 itself (no `tail` copy: fixes entry `move s5,a2`), op/sub locals (`op = cmd0 >> 24; sub = (cmd0 >> 16) & 0xFF;`) + dead tests `op && op`, `sub != 0` give v1/v0/a0 loop values; remaining 2 lines: bne operand order (const left in ours) and `srl a0` in bne delay slot (target hoists it above bne)
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
    ControllerSubNode *node;
    u32 cmd0;
    u32 id;
    s32 found;
    u32 op;
    u32 sub;
    u32 search_cmd;
    curr = arg0;
    if (arg0 != arg1) {
        do {
            cmd0 = curr->unk0;
            op = cmd0 >> 24;
            sub = (cmd0 >> 16) & 0xFF;
            if ((op == 0xDE) && (sub == 1)) {
                id = (curr->unk4 << 4) >> 28;
                if (op && op) {} // FAKE: dead statement (steers uopt colouring)
                search = arg0;
                found = 0;
                if (arg0 != arg1) {
                    if (sub != 0) {} // FAKE: dead statement (steers uopt colouring)
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
                *arg2 = node;
                arg2 = &node->next;
                node->unk8 = id;
                node->unk0 = curr + 1;
                node->unk4 = search;
            }
            curr++;
        } while (curr != arg1);
    }
    *arg2 = NULL;
}
