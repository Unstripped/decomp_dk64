#include "common.h"
#include "actor.h"

extern Actor *D_807FBB40;
extern Actor *D_807FBB44;
extern Actor *D_807FBB48;

void func_8070D380(s32 size, void *dst, s32 *src) {
    memcpy(dst, *src, size);
    *src += size;
}

typedef struct S112a2Record {
    u8 count;
    u8 pad1[3];
    u8 *data;
} S112a2Record;

extern void *heapAlloc(s32);

void func_8070D3CC(S112a2Record *arg0, s32 *arg1) {
    s32 i;
    u8 *data;

    func_8070D380(1, arg0, arg1);
    data = arg0->data = heapAlloc(arg0->count * 8);
    for (i = 0; i < arg0->count; i++) {
        func_8070D380(8, data, arg1);
        data += 8;
    }
}

typedef struct S112bVariantRec {
    u8 count;
    u8 pad1[3];
    u8 *data;
} S112bVariantRec;

typedef struct S112bVariant {
    u8 flags;
    u8 pad1[7];
    void *data;
} S112bVariant;

void func_8070D464(void *arg0, s32 *arg1) {
#define V ((S112bVariant *)arg0)
    s32 i;
    u8 *p;
    S112bVariantRec *rec;

    if (V->flags & 1) {
        p = V->data = heapAlloc(8);
        for (i = 0; i != 1; i++) {
            func_8070D3CC((S112a2Record *)p, arg1);
            p += 8;
        }
    } else if (V->flags & 2) {
        rec = V->data = heapAlloc(8);
        func_8070D380(1, rec, arg1);
        p = rec->data = heapAlloc(rec->count * 4);
        for (i = 0; i < rec->count; i++) {
            func_8070D380(4, p, arg1);
            p += 4;
        }
    }
#undef V
}

typedef struct S112a2ItemList {
    u8 count;
    u8 pad1[3];
    void *items;
} S112a2ItemList;

typedef struct S112a2Item {
    u8 flags;
    u8 pad1[3];
    u8 *data;
    u8 pad8[4];
    u8 tail[4];
} S112a2Item;

void func_8070D568(S112a2ItemList *arg0, s32 *arg1) {
    s32 i;
    S112a2Item *item;

    func_8070D380(1, arg0, arg1);
    item = arg0->items = heapAlloc(arg0->count * 16);
    for (i = 0; i < arg0->count; i++, item++) {
        func_8070D380(1, item, arg1);
        if (item->flags & 4) {
            item->data = heapAlloc(4);
            func_8070D380(4, item->data, arg1);
        } else {
            item->data = NULL;
        }
        func_8070D464(item, arg1);
        func_8070D380(4, item->tail, arg1);
    }
}

extern s32 D_807550C0;

typedef struct S112aListNode {
    u16 id;
    u8 count;
    u8 pad3[9];
    struct S112aListNode *next;
} S112aListNode;

#define S112aListHead ((S112aListNode *)D_807550C0)

typedef struct S112aItemList {
    u8 count;
    u8 pad1[3];
    void *items;
} S112aItemList;

void func_8070D568(S112a2ItemList *, s32 *);

void func_8070D654(S112aItemList *arg0, s32 *arg1) {
    s32 i;
    S112aItemList *item;

    item = arg0->items = heapAlloc(arg0->count * 8);
    for (i = 0; i < arg0->count; i++) {
        func_8070D568((S112a2ItemList *)item, arg1);
        item = (S112aItemList *)((u8 *)item + 8);
    }
}

typedef struct S112aParsedList {
    u8 count;
    u8 pad1[3];
    void *items;
    u16 length;
    u8 padA[2];
    void *payload;
} S112aParsedList;

S112aParsedList *func_8070D6D8(s32 arg0) {
    void *payload;
    s32 length;
    S112aParsedList *header;

    header = heapAlloc(0x10);
    func_8070D380(1, header, &arg0);
    func_8070D654((S112aItemList *)header, &arg0);
    func_8070D380(2, (u8 *)header + 8, &arg0);
    length = header->length;
    payload = heapAlloc(length);
    header->payload = payload;
    memcpy(payload, arg0, length);
    return header;
}

typedef struct S112dLink {
    void *key;
    Actor *actor;
    void *entries;
    struct S112dLink *next;
} S112dLink;

typedef struct S112dActorKeyState {
    u8 pad0[4];
    void *key;
} S112dActorKeyState;

extern void *D_807550C4;
extern s8 D_807550CC;
extern void heapClearBlock(void *);
extern unsigned long actorSpawn(s32, s32, void *);

void *func_8070D754(void *arg0) {
    S112dLink **link;
    S112dActorKeyState *state;
    link = (S112dLink **)&D_807550C4;
    if ((*link != NULL) && ((*link)->key != arg0)) {
        do {
            link = &(*link)->next;
        } while ((*link != NULL) && ((*link)->key != arg0));
    }
    if (*link == NULL) {
        *link = heapAlloc(0x10);
        heapClearBlock(*link);
        (*link)->key = arg0;
        actorSpawn(0x12B, 0, arg0);
        D_807FBB44->unk154 = 0;
        (*link)->actor = D_807FBB44;
        state = (S112dActorKeyState *)D_807FBB44->unk174;
        state->key = arg0;
    }
    return *link;
}

typedef struct S112dEntry {
    u16 id;
    u8 count;
    u8 pad3;
    struct S112dEntry *next;
} S112dEntry;

typedef struct S112dContainer {
    u8 pad0[4];
    Actor *actor;
    S112dEntry *entries;
} S112dContainer;

void func_8070D82C(S112dContainer *arg0, u16 arg1, u8 arg2) {
    S112dEntry **entry;

    entry = &arg0->entries;
    while (*entry != NULL) {
        entry = &(*entry)->next;
    }
    *entry = heapAlloc(8);
    (*entry)->id = arg1;
    (*entry)->count = arg2;
    (*entry)->next = NULL;
    if (arg0->actor->unk154 == 4) {
        arg0->actor->unk154 = 0;
    }
}

typedef struct S112dActorValueState {
    u8 pad0[0x54];
    u8 value;
} S112dActorValueState;

void func_8070D8C0(Actor *arg0, s32 arg1, u8 arg2) {
    S112dActorValueState *state;
    Actor *actor;
    S112dLink *node;
    u8 value;

    node = func_8070D754(arg0);
    if (1) {
        value = D_807550CC;
    }
    state = (S112dActorValueState *)node->actor->unk174;
    state->value = value & 0xFFu;
    if (1) {
        D_807550CC = 0;
        actor = arg0;
        func_8070D82C((S112dContainer *)node, arg1, arg2);
        actor->unk60 |= 0x2000000;
    }
}

S112aListNode *func_8070D928(u16 id) {
    S112aListNode *node;

    node = S112aListHead;
    if ((node != NULL) && (node->id != id)) {
        do {
            node = node->next;
        } while ((node != NULL) && (node->id != id));
    }
    return node;
}

void func_8070D970(arg0)
u16 arg0;
{
    S112aListNode *node;

    node = func_8070D928(arg0);
    if (node != NULL) {
        node->count--;
    }
}

typedef struct S112aChildNode {
    u8 pad0[0x14];
    s32 handle;
    u8 pad18[0x88];
    struct S112aChildNode *next;
} S112aChildNode;

typedef struct S112aFreeNode {
    u8 flags;
    u8 pad1[0xB];
    S112aChildNode *children;
    u8 pad10[0xC];
    struct S112aFreeNode *next;
} S112aFreeNode;

void effectFreeAndUnlink(s32);
extern void heapFreeDeferred();

void func_8070D9AC(S112aFreeNode *arg0) {
    s32 handle;
    s32 flags;
    S112aChildNode *current;
    S112aChildNode *node;

    node = arg0->children;
    flags = arg0->flags & 2;
    if (node != NULL) {
        do {
            current = node;
            node = node->next;
            if (flags != 0) {
                handle = current->handle;
                if (handle != 0) {
                    effectFreeAndUnlink(handle);
                }
            }
            heapFreeDeferred(current);
        } while (node != NULL);
    }
    heapFreeDeferred(arg0);
}

typedef struct S112bNodeList {
    u8 pad0[0xC];
    S112aFreeNode *first;
    u8 state;
} S112bNodeList;

void func_8070DA28(S112bNodeList *arg0) {
    S112aFreeNode *node;

    S112aFreeNode *current;

    node = arg0->first;
    if (node != NULL) {
        do {
            current = node;
            node = node->next;
            func_8070D9AC(current);
        } while (node != NULL);
    }
    arg0->first = NULL;
    arg0->state = 0;
}

typedef struct S112bActorState {
    u8 pad0[8];
    u16 id;
    u8 padA[0x2A];
    void *unk34;
} S112bActorState;

typedef struct S112bFreeLink {
    u8 pad0[4];
    struct S112bFreeLink *next;
} S112bFreeLink;

typedef struct S112bQueueEntry {
    void *key;
    Actor *actor;
    S112bFreeLink *entries;
    struct S112bQueueEntry *next;
} S112bQueueEntry;

extern void actorDespawn(void *);

void func_8070DA74(Actor *arg0) {
    Actor *actor;
    S112bActorState *state;
    S112bQueueEntry **link;
    S112bQueueEntry *found;
    S112bFreeLink *node;
    S112bFreeLink *current;

    link = (S112bQueueEntry **)&D_807550C4;
    found = NULL;
    if ((*link != NULL) && ((*link)->key != arg0)) {
        do {
            link = &(*link)->next;
        } while ((*link != NULL) && ((*link)->key != arg0));
    }
    if (*link != NULL) {
        found = *link;
        *link = found->next;
    }
    if (found != NULL) {
        actor = found->actor;
        state = actor->unk174;
        func_8070DA28((S112bNodeList *)state);
        func_8070D970(state->id);
        node = found->entries;
        if (node != NULL) {
            do {
                current = node;
                node = node->next;
                heapFreeDeferred(current);
            } while (node != NULL);
        }
        heapFreeDeferred(found);
        heapFreeDeferred(state->unk34);
        actorDespawn(actor);
        arg0->unk60 &= 0xFDFFFFFF;
    }
}

typedef struct M112bFreeEntry {
    void *unk0;
    void *unk4;
} M112bFreeEntry;


void func_8070DB7C(M112bFreeEntry *arg0) {
    heapFreeDeferred(arg0->unk4);
}

typedef struct M112bRecord {
    u8 flags;
    u8 pad1[3];
    void *unk4;
    M112bFreeEntry *unk8;
    void *unkC;
} M112bRecord;

typedef struct M112bRecordList {
    u8 count;
    u8 pad1[3];
    M112bRecord *entries;
} M112bRecordList;

typedef struct M112bRecordListArray {
    u8 count;
    u8 pad1[3];
    M112bRecordList *entries;
    void *unk8;
    void *unkC;
} M112bRecordListArray;

void func_8070DB9C(M112bRecord *arg0) {
    s32 i;
    s32 flags;
    void *temp;

    temp = arg0->unk4;
    if (temp != NULL) {
        heapFreeDeferred(temp);
    }
    flags = arg0->flags;
    i = 0;
    if (flags & 1) {
        do {
            func_8070DB7C(&arg0->unk8[i]);
            i++;
        } while (i != 1);
        heapFreeDeferred(arg0->unk8);
        return;
    }
    if (flags & 2) {
        heapFreeDeferred(arg0->unk8->unk4);
        heapFreeDeferred(arg0->unk8);
    }
}


void func_8070DC40(M112bRecordList *arg0) {
    s32 i;

    i = 0;
    if (arg0->count > 0) {
        do {
            func_8070DB9C(&arg0->entries[i]);
            i++;
        } while (i < arg0->count);
    }
    heapFreeDeferred(arg0->entries);
}


void func_8070DCA4(M112bRecordListArray *arg0) {
    s32 i;

    i = 0;
    if (arg0->count > 0) {
        do {
            func_8070DC40(&arg0->entries[i]);
            i++;
        } while (i < arg0->count);
    }
    heapFreeDeferred(arg0->entries);
    heapFreeDeferred(arg0->unkC);
    heapFreeDeferred(arg0);
}

typedef struct M112bRecordListHolder {
    void *unk0;
    M112bRecordListArray *unk4;
} M112bRecordListHolder;

void func_8070DD18(M112bRecordListHolder *arg0) {
    func_8070DCA4(arg0->unk4);
    heapFreeDeferred(arg0);
}

typedef struct S112bSlotNode {
    u16 id;
    u8 count;
    u8 pad3[5];
    u8 kind;
    u8 pad9[3];
    struct S112bSlotNode *next;
} S112bSlotNode;

void func_8070DD44(void) {
    S112bSlotNode **link;
    S112bSlotNode *node;

    link = (S112bSlotNode **)&D_807550C0;
    if (*link != NULL) {
        do {
            if ((*link)->kind == 1) {
                if ((*link)->count != 0) {
                    (*link)->count--;
                }
            }
            if ((*link)->count == 0) {
                node = *link;
                *link = node->next;
                func_8070DD18((M112bRecordListHolder *)node);
            } else {
                link = &(*link)->next;
            }
        } while (*link != NULL);
    }
}

typedef struct S112bResNode {
    u16 id;
    u8 count;
    u8 pad3;
    S112aParsedList *parsed;
    u8 kind;
    u8 pad9[3];
    struct S112bResNode *next;
} S112bResNode;

extern void *assetLoad(s32, s32, s32, s32);
extern void assetFreeBuffer(void *, s32, s32);

S112aParsedList *func_8070DDDC(u16 arg0, s32 arg1) {
    S112bResNode *node;
    S112aParsedList *parsed;
    void *asset;
    S112bResNode **link;

    node = (S112bResNode *)func_8070D928(arg0);
    if (node == NULL) {
        asset = assetLoad(0xC, arg0, 1, 1);
        link = (S112bResNode **)&D_807550C0;
        if (*link != NULL) {
            do {
                link = &(*link)->next;
            } while (*link != NULL);
        }
        parsed = func_8070D6D8((s32)asset);
        assetFreeBuffer(asset, 0x1F1, 0x50);
        node = heapAlloc(0x10);
        *link = node;
        node->parsed = parsed;
        node->id = arg0;
        node->kind = arg1;
        node->count = 0;
        node->next = NULL;
    }
    if (node->kind != 0) {
        if (node->kind == 1) {
            node->count = 2;
        }
    } else {
        node->count++;
    }
    return node->parsed;
}

typedef struct S112cLine {
    s16 width;
    u8 pad2[0xE];
    u16 flags;
    u8 character;
    u8 pad13[0x8D];
    struct S112cLine *next;
} S112cLine;

typedef struct S112cRow {
    u8 kind;
    u8 pad1[0xB];
    S112cLine *lines;
    u8 pad10[4];
    f32 width;
    f32 height;
    struct S112cRow *next;
} S112cRow;

typedef struct S112cOwner {
    u8 pad0[0xC];
    S112cRow *rows;
} S112cOwner;

extern u32 textGetFontHeight(s32);
extern s16 textGetCharAdvance(s32, u8);
extern s32 _sprintf(u8 *, char *, ...);
extern void *D_8074E778[];
extern u16 D_80750AC8;

s32 func_8070DED4(s32 arg0, s32 arg1, u16 arg2) {
    S112cRow **rowHead;
    S112cRow **rowLink;
    S112cLine **rowLines;
    S112cLine *line;
    S112cLine **lineLink;
    u32 width;
    s32 i;
    u16 flags;
    u8 character;
    u8 textBuffer[0xC];
    u8 *text;
    f32 time;
    S112cLine *p;
    rowLink = &((S112cOwner *)arg0)->rows;
    rowHead = &((S112cOwner *)arg0)->rows;
    line = NULL;
    lineLink = &line;
    flags = 0;
    width = 0;
    character = 1;
    time = (f32)textGetFontHeight(6);
    if (*rowHead != NULL) {
        do {
            rowLink = &(*rowLink)->next;
        } while (*rowLink != NULL);
    }
    *rowLink = heapAlloc(0x20);
    heapClearBlock(*rowLink);
    (*rowLink)->kind = 1;
    (*rowLink)->height = time;
    rowLines = &(*rowLink)->lines;
    for (i = 0; i <= arg2; i++) {
        if ((i == arg2) || ((((u8 *)arg1)[i] == 0x20U) && (character == 0))) { // FAKE: unsigned 0x20 keeps heapAlloc's li a0,32 apart from the hoisted s4
            if (((*rowLink)->width == 0.0f) || ((f64)((*rowLink)->width + (f32)width) < 124.8f)) {
                (*rowLink)->width += (f32)width;
                width = 0;
            } else {
                do { width = 0; } while (0); // FAKE: splits the basic block like the original
                while ((line != NULL) && (line->character == 0x20U)) { // FAKE: unsigned 0x20 keeps heapAlloc's li a0,32 apart from the hoisted s4
                    p = line;
                    line = p->next;
                    heapFreeDeferred(p);
                }
                if (line != NULL) {
                    rowLink = &(*rowLink)->next;
                    *rowLink = heapAlloc(0x20);
                    heapClearBlock(*rowLink);
                    (*rowLink)->kind = 1;
                    (*rowLink)->height = time;
                    rowLines = &(*rowLink)->lines;
                    (*rowLink)->width = 0.0f;
                    for (p = line; p != NULL; p = p->next) {
                        (*rowLink)->width += (f32)p->width;
                    }
                }
            }
            character = 1;
            if (line != NULL) {
                *rowLines = line;
                rowLines = lineLink;
            }
            line = NULL;
            lineLink = &line;
            if (i != arg2) {
                i--;
            }
        } else if ((((u8 *)arg1)[i] > 0) && (((u8 *)arg1)[i] < 0x10)) {
            flags ^= 1 << ((u8 *)arg1)[i];
        } else {
            character = 0;
            do { } while (0); // FAKE: splits the basic block like the original
            text = textBuffer;
            switch (((u8 *)arg1)[i]) {
            case 0x7E:
                _sprintf(textBuffer, "%s", D_8074E778[D_807FBB48->unk58]);
                break;
            case 0x40:
                _sprintf(textBuffer, "%d", D_80750AC8);
                break;
            default:
                _sprintf(textBuffer, "%c", ((u8 *)arg1)[i]);
                break;
            }
            if (text[0] != 0) {
                do {
                    *lineLink = heapAlloc(0xA8);
                    heapClearBlock(*lineLink);
                    (*lineLink)->width = textGetCharAdvance(6, text[0]);
                    (*lineLink)->flags = flags;
                    (*lineLink)->character = text[0];
                    width += (*lineLink)->width;
                    width &= 0xFFFF;
                    lineLink = &(*lineLink)->next;
                    text++;
                } while (text[0] != 0);
            }
        }
    }
}

extern s32 func_8070DED4(s32, s32, u16);
extern u8 D_807550C8;

typedef struct R112cDrawCommand {
    s32 unk0;
    u16 unk4;
} R112cDrawCommand;

typedef struct R112cDrawList {
    u8 count;
    u8 pad1[3];
    void *commands;
} R112cDrawList;

typedef struct R112cDrawListContainer {
    u8 pad0[8];
    R112cDrawList *list;
} R112cDrawListContainer;

typedef struct R112cDrawContext {
    u8 pad0[0xC];
    s32 unkC;
} R112cDrawContext;

void func_8070E2AC(s32 arg0, void *arg1, void *arg2) {
    s32 var_s0;
    s32 var_s1;
    R112cDrawList *temp_s2;
    R112cDrawCommand *temp_v0;
    R112cDrawContext *var_s3;
    s32 var_s4;

    temp_s2 = (R112cDrawList *) ((u8 *) ((R112cDrawListContainer *) arg1)->list + (D_807550C8 * 8));
    var_s3 = arg2;
    var_s4 = arg0;
    var_s0 = 0;
    var_s1 = 0;
    if (temp_s2->count > 0) {
        do {
            temp_v0 = (R112cDrawCommand *) ((u8 *) temp_s2->commands + var_s1);
            func_8070DED4(var_s4, temp_v0->unk0 + var_s3->unkC, temp_v0->unk4);
            var_s0 += 1;
            var_s1 += 8;
        } while (var_s0 < temp_s2->count);
    }
}

typedef struct S112bGridEntry {
    s16 width;
    u8 pad2[0xE];
    u16 id;
    u8 sub;
    u8 pad13[0x8D];
    struct S112bGridEntry *next;
} S112bGridEntry;

typedef struct S112bGridGroup {
    u8 kind;
    u8 pad1[0xB];
    S112bGridEntry *entries;
    u8 pad10[4];
    f32 width;
    f32 height;
    struct S112bGridGroup *next;
} S112bGridGroup;

typedef struct S112bGridOwner {
    u8 pad0[0xC];
    S112bGridGroup *groups;
} S112bGridOwner;

typedef struct S112bGridSourceEntry {
    u16 id;
    u8 sub;
    u8 pad3;
} S112bGridSourceEntry;

typedef struct S112bGridSource {
    u8 count;
    u8 pad1[3];
    S112bGridSourceEntry *entries;
} S112bGridSource;

typedef struct S112bGridRequest {
    u8 pad0[8];
    S112bGridSource *source;
} S112bGridRequest;

extern void *D_80755390[];
extern void effectGridGetScaledDimensions(void *, s16 *, s16 *);

void func_8070E34C(S112bGridOwner *arg0, S112bGridRequest *arg1, void *arg2) {
    S112bGridGroup **link;
    S112bGridEntry **entry;
    S112bGridSource *source;
    S112bGridSourceEntry *item;
    s32 i;
    s32 pad;
    s16 width;
    s16 height;

    link = &arg0->groups;
    source = arg1->source;
    if (*link != NULL) {
        do {
            link = &(*link)->next;
        } while (*link != NULL);
    }
    *link = heapAlloc(0x20);
    heapClearBlock(*link);
    (*link)->kind = 2;
    i = 0;
    entry = &(*link)->entries;
    if (source->count > 0) {
        do {
            item = &source->entries[i];
            effectGridGetScaledDimensions(D_80755390[item->id], &width, &height);
            if ((f64)((*link)->width + (f32)width) >= 124.8f) {
                link = &(*link)->next;
                *link = heapAlloc(0x20);
                heapClearBlock(*link);
                (*link)->kind = 2;
                entry = &(*link)->entries;
            }
            *entry = heapAlloc(0xA8);
            heapClearBlock(*entry);
            (*entry)->width = width;
            (*entry)->id = item->id;
            (*entry)->sub = item->sub;
            (*link)->width += (f32)(*entry)->width;
            (*link)->height = ((f32)height < (*link)->height) ? (*link)->height : (f32)height;
            entry = &(*entry)->next;
            i++;
        } while (i < source->count);
    }
}


typedef struct S112bResLink {
    u8 pad0[8];
    s32 unk8;
    u8 padC[4];
    u16 unk10;
    u8 pad12[0x0A];
    struct S112bResLink *next;
} S112bResLink;

typedef struct S112bResState {
    u8 pad0[8];
    u16 id;
    u8 padA[2];
    S112bResLink *links;
} S112bResState;

typedef struct S112bResItem {
    u8 flags;
    u8 pad1[3];
    s32 unk4;
    u8 pad8[4];
    f32 duration;
} S112bResItem;

typedef struct S112bResKind {
    u8 count;
    u8 pad1[3];
    S112bResItem *items;
} S112bResKind;

typedef struct S112bResParsed {
    u8 pad0[4];
    S112bResKind *kinds;
} S112bResParsed;

void func_8070E548(Actor *arg0, u16 arg1, u8 arg2) {
    S112bResState *state;
    S112bResParsed *parsed;
    S112bResLink **link;
    S112bResItem *item;
    s32 i;

    state = arg0->unk174;
    if (arg0->unk60 & 0x10) {
        func_8070D970(state->id);
    }
    parsed = (S112bResParsed *)func_8070DDDC(arg1, 0);
    link = &state->links;
    state->id = arg1;
    item = parsed->kinds[arg2].items;
    for (i = 0; i < parsed->kinds[arg2].count; i++) {
        if (*link != NULL) {
            do {
                link = &(*link)->next;
            } while (*link != NULL);
        }
        if (item->flags & 1) {
            func_8070E2AC((s32)state, item, parsed);
        } else if (item->flags & 2) {
            func_8070E34C((S112bGridOwner *)state, (S112bGridRequest *)item, parsed);
        }
        if (*link != NULL) {
            (*link)->unk8 = item->unk4;
        }
        while ((*link != NULL) && ((*link)->next != NULL)) {
            link = &(*link)->next;
        }
        (*link)->unk10 = item->duration * 30.0f;
        item++;
    }
}

typedef struct S112bTextEntry {
    char *text;
    u16 length;
} S112bTextEntry;

typedef struct S112bTextChoice {
    void *pad0;
    S112bTextEntry *entry;
} S112bTextChoice;

typedef struct S112bTextGroup {
    u8 pad0[8];
    S112bTextChoice *choices;
} S112bTextGroup;

typedef struct S112bTextRow {
    void *pad0;
    S112bTextGroup *group;
} S112bTextRow;

typedef struct S112bTextTable {
    u8 pad0[4];
    S112bTextRow *rows;
    u8 pad8[4];
    s32 base;
} S112bTextTable;

char *func_8070E750(s32 arg0, s32 arg1, s32 arg2) {
    S112bTextGroup *group;
    S112bTextChoice *choice;
    S112bTextEntry *entry;
    char *source;
    s32 length;
    char *dest;
    S112bTextTable *table;

    table = (S112bTextTable *)func_8070DDDC(arg0, 1);
    group = table->rows[arg1].group;
    choice = group->choices + D_807550C8;
    entry = choice->entry;
    source = entry->text + table->base;
    length = entry->length;
    dest = heapAlloc(length + 1);
    if (arg2 & 1) {
        heapFreeDeferred(dest);
    }
    memcpy(dest, source, length);
    dest[length] = 0;
    return dest;
}

extern void *func_8070D754(void *);
extern void timerQueueAdd();
extern void camResumePathCallback(void);

typedef struct R112cE808State {
    u8 pad0[0x54];
    u8 unk54;
} R112cE808State;

typedef struct R112cE808Item {
    u16 unk0;
    u8 unk2;
    u8 pad3;
    void *unk4;
} R112cE808Item;

typedef struct R112cE808Node {
    u8 pad0[8];
    R112cE808Item *unk8;
} R112cE808Node;

typedef struct R112cE808Arg1 {
    u8 pad0[0x60];
    s32 unk60;
} R112cE808Arg1;

void func_8070E808(Actor *arg0, void *arg1) {
    R112cE808State *sp24;
    R112cE808Node *temp_v0;
    

    sp24 = arg0->unk174;
    temp_v0 = func_8070D754(arg1);
    if (temp_v0->unk8 == NULL) {
        ((R112cE808Arg1 *) arg1)->unk60 &= 0xFDFFFFFF;
        if (sp24->unk54 & 1) {
            timerQueueAdd(camResumePathCallback, 0x1E, 0, 0, 0);
        }
        arg0->unk154 = 4;
        return;
    }
    func_8070E548(arg0, temp_v0->unk8->unk0, temp_v0->unk8->unk2);
    arg1 = temp_v0->unk8;
    temp_v0->unk8 = ((R112cE808Item *) arg1)->unk4;
    heapFreeDeferred(arg1);
}



void func_8070E8C8(void) {
    D_807550C0 = 0;
    D_807550C4 = 0;
}

void func_8070E8DC(s8 arg0) {
    D_807550CC = arg0;
}
