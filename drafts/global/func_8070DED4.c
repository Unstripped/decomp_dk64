// func_8070DED4 (src/global/112080.c): stage 2: behavior and blocks recovered from local asm; frame/register allocation differs (0xA0 vs 0x98)
extern s32 textGetFontHeight(s32);
extern s16 textGetCharAdvance(s32, u8);
extern s32 _sprintf(u8 *, char *, ...);
extern void *D_8074E778[];
extern u16 D_80750AC8;
extern Actor *D_807FBB48;
extern void *heapAlloc(s32);
extern void heapClearBlock(void *);
extern void heapFreeDeferred();

typedef struct L112dEntry {
    s16 width;
    u8 pad2[0xE];
    u16 flags;
    u8 character;
    u8 pad13[0x8D];
    struct L112dEntry *next;
} L112dEntry;

typedef struct L112dGroup {
    u8 unk0;
    u8 pad1[0xB];
    L112dEntry *entries;
    u8 pad10[4];
    f32 width;
    f32 height;
    struct L112dGroup *next;
} L112dGroup;

typedef struct L112dContainer {
    u8 pad0[0xC];
    L112dGroup *groups;
} L112dContainer;

s32 func_8070DED4(L112dContainer *arg0, u8 *arg1, u16 arg2) {
    L112dEntry *entry;
    L112dEntry **entryLink;
    L112dGroup *group;
    L112dGroup **groupLink;
    f32 time;
    f32 value;
    s16 flags;
    s32 i;
    s32 width;
    s32 limit;
    u8 character;
    u8 textBuffer[0xC];
    u8 *text;

    limit = arg2;
    groupLink = &arg0->groups;
    entry = NULL;
    entryLink = &entry;
    flags = 0;
    width = 0;
    character = 1;
    time = (f32)textGetFontHeight(6);
    if (time < 0.0f) {
        time += 4294967296.0f;
    }
    if (arg0->groups != NULL) {
        group = arg0->groups;
        do {
            groupLink = &group->next;
            group = group->next;
        } while (group != NULL);
    }
    *groupLink = heapAlloc(0x20);
    heapClearBlock(*groupLink);
    (*groupLink)->unk0 = 1;
    (*groupLink)->height = time;
    if (limit >= 0) {
        for (i = 0; i <= limit; i++) {
            if ((i == limit) || ((arg1[i] == 0x20) && (character == 0))) {
                value = (*groupLink)->width;
                character = 1;
                if (value != 0.0f) {
                    if ((f64)(value + (f32)width) < 124.800003051757812) {
                        (*groupLink)->width = value + (f32)width;
                    } else {
                        width = 0;
                        if ((entry != NULL) && (entry->character == 0x20)) {
                            do {
                                L112dEntry *next = entry->next;
                                heapFreeDeferred(entry);
                                entry = next;
                            } while ((entry != NULL) && (entry->character == 0x20));
                        }
                        if (entry != NULL) {
                            groupLink = &(*groupLink)->next;
                            *groupLink = heapAlloc(0x20);
                            heapClearBlock(*groupLink);
                            (*groupLink)->unk0 = 1;
                            (*groupLink)->height = time;
                            (*groupLink)->width = 0.0f;
                            group = *groupLink;
                            do {
                                group->width += (f32)entry->width;
                                entry = entry->next;
                            } while (entry != NULL);
                            entryLink = &(*groupLink)->entries;
                        }
                    }
                } else {
                    (*groupLink)->width = value + (f32)width;
                    width = 0;
                }
                if (entry != NULL) {
                    *entryLink = entry;
                    entryLink = &entry;
                }
                entry = NULL;
                entryLink = &entry;
                if (i != limit) {
                    i--;
                }
            } else if ((arg1[i] > 0) && (arg1[i] < 0x10)) {
                flags = (flags ^ (1 << arg1[i])) & 0xFFFF;
            } else {
                character = 0;
                text = textBuffer;
                if (arg1[i] == 0x40) {
                    _sprintf(text, "%d", D_80750AC8);
                } else if (arg1[i] == 0x7E) {
                    _sprintf(text, "%s", D_8074E778[D_807FBB48->unk58]);
                } else {
                    _sprintf(text, "%c", arg1[i]);
                }
                if (text[0] != 0) {
                    do {
                        *entryLink = heapAlloc(0xA8);
                        heapClearBlock(*entryLink);
                        (*entryLink)->width = textGetCharAdvance(6, text[0]);
                        (*entryLink)->flags = flags;
                        (*entryLink)->character = text[0];
                        width = (width + (*entryLink)->width) & 0xFFFF;
                        entryLink = &(*entryLink)->next;
                        text++;
                    } while (text[0] != 0);
                }
            }
        }
    }
}
