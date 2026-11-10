#include "common.h"
#include "actor.h"
#include "proto/boot/3D20.h"
#include "proto/global/100180.h"
#include "proto/global/112080.h"
#include "proto/global/119370.h"
#include "proto/global/15050.h"
#include "proto/global/201B0.h"
#include "proto/global/5650.h"
#include "proto/global/6AD90.h"
#include "proto/global/7CA80.h"

extern Actor *gCurrentActor;
extern Actor *gSpawnedActor;
extern Actor *gActivePlayerActor;

// One span of language text: `length` bytes at `offset` into the resource payload.
typedef struct ResTextSpan {
    /* 0x00 */ s32 offset;
    /* 0x04 */ u16 length;
    /* 0x06 */ u8 pad6[2];
} ResTextSpan;

// One cell of an effect grid row.
typedef struct ResGridCell {
    /* 0x00 */ u16 effectId;
    /* 0x02 */ u8 sub;
    /* 0x03 */ u8 pad3;
} ResGridCell;

// Counted array read from a resource stream: text spans (one record per language)
// or grid cells.
typedef struct ResRecord {
    /* 0x00 */ u8 count;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ union {
        u8 *bytes;
        ResTextSpan *spans;
        ResGridCell *cells;
    } data;
} ResRecord;

// flags & 1: text item (variant = records indexed by language);
// flags & 2: grid item (variant = one record of cells); flags & 4: has data.
typedef struct ResItem {
    /* 0x00 */ u8 flags;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ void *data;
    /* 0x08 */ ResRecord *variant;
    /* 0x0C */ f32 duration;
} ResItem;

typedef struct ResItemList {
    /* 0x00 */ u8 count;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ ResItem *items;
} ResItemList;

// A parsed resource (asset class 0xC).
typedef struct ResParsedList {
    /* 0x00 */ u8 count;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ ResItemList *lists;
    /* 0x08 */ u16 length;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ u8 *payload;
} ResParsedList;

// Cache entry of the loaded-resource list.
typedef struct ResNode {
    /* 0x00 */ u16 id;
    /* 0x02 */ u8 refCount;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ ResParsedList *parsed;
    /* 0x08 */ u8 kind;
    /* 0x09 */ u8 pad9[3];
    /* 0x0C */ struct ResNode *next;
} ResNode;

// A pending (resource id, kind index) request of a queue.
typedef struct ResQueueEntry {
    /* 0x00 */ u16 resId;
    /* 0x02 */ u8 kindIndex;
    /* 0x03 */ u8 pad3;
    /* 0x04 */ struct ResQueueEntry *next;
} ResQueueEntry;

// One queue per key actor, processed by a spawned actor 0x12B.
typedef struct ResQueueLink {
    /* 0x00 */ Actor *key;
    /* 0x04 */ Actor *actor;
    /* 0x08 */ ResQueueEntry *entries;
    /* 0x0C */ struct ResQueueLink *next;
} ResQueueLink;

// A laid-out glyph (text rows) or effect cell (grid rows).
typedef struct ResGlyph {
    /* 0x00 */ s16 width;
    /* 0x02 */ u8 pad2[0xE];
    /* 0x10 */ u16 attr; // text: style flags; grid: effect id
    /* 0x12 */ u8 code; // text: character; grid: sub index
    /* 0x13 */ u8 pad13;
    /* 0x14 */ struct EffectNode *effect;
    /* 0x18 */ u8 pad18[0x88];
    /* 0xA0 */ struct ResGlyph *next;
} ResGlyph;

typedef struct ResRow {
    /* 0x00 */ u8 kind; // 1: text, 2: grid
    /* 0x01 */ u8 pad1[7];
    /* 0x08 */ void *data;
    /* 0x0C */ ResGlyph *glyphs;
    /* 0x10 */ u16 timer;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ f32 width;
    /* 0x18 */ f32 height;
    /* 0x1C */ struct ResRow *next;
} ResRow;

// customState of the queue actor (actor 0x12B).
typedef struct ResQueueActorState {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ Actor *key;
    /* 0x08 */ u16 resId;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ ResRow *rows;
    /* 0x10 */ u8 rowState;
    /* 0x11 */ u8 pad11[0x23];
    /* 0x34 */ void *unk34;
    /* 0x38 */ u8 pad38[0x1C];
    /* 0x54 */ u8 queueFlags;
} ResQueueActorState;

extern ResNode *sResNodeListHead;
extern ResQueueLink *sResQueueHead;
extern s8 sResQueueValue;

void streamReadBytes(s32 size, void *dst, s32 *src) {
    memcpy(dst, *src, size);
    *src += size;
}

void resParseRecord(ResRecord *rec, s32 *src) {
    s32 i;
    u8 *data;

    streamReadBytes(1, rec, src);
    data = rec->data.bytes = heapAlloc(rec->count * 8);
    for (i = 0; i < rec->count; i++) {
        streamReadBytes(8, data, src);
        data += 8;
    }
}

void resParseVariant(ResItem *item, s32 *src) {
    s32 i;
    u8 *p;
    ResRecord *rec;

    if (item->flags & 1) {
        item->variant = heapAlloc(8);
        p = (u8 *)item->variant;
        for (i = 0; i != 1; i++) {
            resParseRecord((ResRecord *)p, src);
            p += 8;
        }
    } else if (item->flags & 2) {
        rec = item->variant = heapAlloc(8);
        streamReadBytes(1, rec, src);
        p = rec->data.bytes = heapAlloc(rec->count * 4);
        for (i = 0; i < rec->count; i++) {
            streamReadBytes(4, p, src);
            p += 4;
        }
    }
}

void resParseItem(ResItemList *list, s32 *src) {
    s32 i;
    ResItem *item;

    streamReadBytes(1, list, src);
    item = list->items = heapAlloc(list->count * 16);
    for (i = 0; i < list->count; i++, item++) {
        streamReadBytes(1, item, src);
        if (item->flags & 4) {
            item->data = heapAlloc(4);
            streamReadBytes(4, item->data, src);
        } else {
            item->data = NULL;
        }
        resParseVariant(item, src);
        streamReadBytes(4, &item->duration, src);
    }
}

void resParseItemList(ResParsedList *parsed, s32 *src) {
    s32 i;
    ResItemList *list;

    list = parsed->lists = heapAlloc(parsed->count * 8);
    for (i = 0; i < parsed->count; i++) {
        resParseItem(list, src);
        list++;
    }
}

ResParsedList *resParseList(s32 src) {
    void *payload;
    s32 length;
    ResParsedList *header;

    header = heapAlloc(0x10);
    streamReadBytes(1, header, &src);
    resParseItemList(header, &src);
    streamReadBytes(2, &header->length, &src);
    length = header->length;
    payload = heapAlloc(length);
    header->payload = payload;
    memcpy(payload, src, length);
    return header;
}

ResQueueLink *resQueueGetOrCreate(Actor *key) {
    ResQueueLink **link;
    ResQueueActorState *state;

    link = &sResQueueHead;
    if ((*link != NULL) && ((*link)->key != key)) {
        do {
            link = &(*link)->next;
        } while ((*link != NULL) && ((*link)->key != key));
    }
    if (*link == NULL) {
        *link = heapAlloc(0x10);
        heapClearBlock(*link);
        (*link)->key = key;
        actorSpawn(0x12B, 0);
        gSpawnedActor->state = 0;
        (*link)->actor = gSpawnedActor;
        state = gSpawnedActor->customState;
        state->key = key;
    }
    return *link;
}

void resQueueAddEntry(ResQueueLink *queue, u16 resId, u8 kindIndex) {
    ResQueueEntry **entry;

    entry = &queue->entries;
    while (*entry != NULL) {
        entry = &(*entry)->next;
    }
    *entry = heapAlloc(8);
    (*entry)->resId = resId;
    (*entry)->kindIndex = kindIndex;
    (*entry)->next = NULL;
    if (queue->actor->state == 4) {
        queue->actor->state = 0;
    }
}

void resQueueAttachActor(Actor *targetActor, s32 id, u8 count) {
    ResQueueActorState *state;
    ResQueueLink *node;
    u8 value;

    node = resQueueGetOrCreate(targetActor);
    if (1) { // FAKE: the two if (1) blocks and value & 0xFFu reproduce the load/store order around the customState load
        value = sResQueueValue;
    }
    state = node->actor->customState;
    state->queueFlags = value & 0xFFu;
    if (1) {
        sResQueueValue = 0;
        resQueueAddEntry(node, id, count);
        targetActor->flags |= 0x2000000;
    }
}

ResNode *resNodeFindById(u16 id) {
    ResNode *node;

    node = sResNodeListHead;
    if ((node != NULL) && (node->id != id)) {
        do {
            node = node->next;
        } while ((node != NULL) && (node->id != id));
    }
    return node;
}

void resNodeDecRef(u16 id) {
    ResNode *node;

    node = resNodeFindById(id);
    if (node != NULL) {
        node->refCount--;
    }
}

void resNodeFree(ResRow *row) {
    struct EffectNode *effect;
    s32 isGrid;
    ResGlyph *current;
    ResGlyph *glyph;

    glyph = row->glyphs;
    isGrid = row->kind & 2;
    if (glyph != NULL) {
        do {
            current = glyph;
            glyph = glyph->next;
            if (isGrid != 0) {
                effect = current->effect;
                if (effect != NULL) {
                    effectFreeAndUnlink(effect);
                }
            }
            heapFreeDeferred(current);
        } while (glyph != NULL);
    }
    heapFreeDeferred(row);
}

void resNodeListFree(ResQueueActorState *state) {
    ResRow *row;
    ResRow *current;

    row = state->rows;
    if (row != NULL) {
        do {
            current = row;
            row = row->next;
            resNodeFree(current);
        } while (row != NULL);
    }
    state->rows = NULL;
    state->rowState = 0;
}

void resQueueRemove(Actor *targetActor) {
    Actor *actor;
    ResQueueActorState *state;
    ResQueueLink **link;
    ResQueueLink *found;
    ResQueueEntry *entry;
    ResQueueEntry *current;

    link = &sResQueueHead;
    found = NULL;
    if ((*link != NULL) && ((*link)->key != targetActor)) {
        do {
            link = &(*link)->next;
        } while ((*link != NULL) && ((*link)->key != targetActor));
    }
    if (*link != NULL) {
        found = *link;
        *link = found->next;
    }
    if (found != NULL) {
        actor = found->actor;
        state = actor->customState;
        resNodeListFree(state);
        resNodeDecRef(state->resId);
        entry = found->entries;
        if (entry != NULL) {
            do {
                current = entry;
                entry = entry->next;
                heapFreeDeferred(current);
            } while (entry != NULL);
        }
        heapFreeDeferred(found);
        heapFreeDeferred(state->unk34);
        actorDespawn(actor);
        targetActor->flags &= 0xFDFFFFFF;
    }
}

void resFreeRecordData(ResRecord *rec) {
    heapFreeDeferred(rec->data.bytes);
}

void resFreeRecord(ResItem *item) {
    s32 i;
    s32 flags;
    void *data;

    data = item->data;
    if (data != NULL) {
        heapFreeDeferred(data);
    }
    flags = item->flags;
    i = 0;
    if (flags & 1) {
        do {
            resFreeRecordData(&item->variant[i]);
            i++;
        } while (i != 1);
        heapFreeDeferred(item->variant);
        return;
    }
    if (flags & 2) {
        heapFreeDeferred(item->variant->data.bytes);
        heapFreeDeferred(item->variant);
    }
}

void resFreeRecordList(ResItemList *list) {
    s32 i;

    i = 0;
    if (list->count > 0) {
        do {
            resFreeRecord(&list->items[i]);
            i++;
        } while (i < list->count);
    }
    heapFreeDeferred(list->items);
}

void resFreeRecordListArray(ResParsedList *parsed) {
    s32 i;

    i = 0;
    if (parsed->count > 0) {
        do {
            resFreeRecordList(&parsed->lists[i]);
            i++;
        } while (i < parsed->count);
    }
    heapFreeDeferred(parsed->lists);
    heapFreeDeferred(parsed->payload);
    heapFreeDeferred(parsed);
}

void resNodeDestroy(ResNode *node) {
    resFreeRecordListArray(node->parsed);
    heapFreeDeferred(node);
}

void resListTick(void) {
    ResNode **link;
    ResNode *node;

    link = &sResNodeListHead;
    if (*link != NULL) {
        do {
            if ((*link)->kind == 1) {
                if ((*link)->refCount != 0) {
                    (*link)->refCount--;
                }
            }
            if ((*link)->refCount == 0) {
                node = *link;
                *link = node->next;
                resNodeDestroy(node);
            } else {
                link = &(*link)->next;
            }
        } while (*link != NULL);
    }
}

ResParsedList *resNodeGetOrLoad(u16 id, s32 kind) {
    ResNode *node;
    ResParsedList *parsed;
    void *asset;
    ResNode **link;

    node = resNodeFindById(id);
    if (node == NULL) {
        asset = assetLoad(0xC, id, 1, 1);
        link = &sResNodeListHead;
        if (*link != NULL) {
            do {
                link = &(*link)->next;
            } while (*link != NULL);
        }
        parsed = resParseList((s32)asset);
        assetFreeBuffer(asset, 0x1F1, 0x50);
        node = heapAlloc(0x10);
        *link = node;
        node->parsed = parsed;
        node->id = id;
        node->kind = kind;
        node->refCount = 0;
        node->next = NULL;
    }
    if (node->kind != 0) {
        if (node->kind == 1) {
            node->refCount = 2;
        }
    } else {
        node->refCount++;
    }
    return node->parsed;
}

extern void *D_8074E778[];
extern u16 D_80750AC8;

void textLayoutAppendRows(ResQueueActorState *state, u8 *textBytes, u16 length) {
    ResRow **rowHead;
    ResRow **rowLink;
    ResGlyph **rowLines;
    ResGlyph *line;
    ResGlyph **lineLink;
    u32 width;
    s32 i;
    u16 flags;
    u8 character;
    u8 textBuffer[0xC];
    u8 *text;
    f32 height;
    ResGlyph *p;

    rowLink = &state->rows;
    rowHead = &state->rows;
    line = NULL;
    lineLink = &line;
    flags = 0;
    width = 0;
    character = 1;
    height = (f32)textGetFontHeight(6);
    if (*rowHead != NULL) {
        do {
            rowLink = &(*rowLink)->next;
        } while (*rowLink != NULL);
    }
    *rowLink = heapAlloc(0x20);
    heapClearBlock(*rowLink);
    (*rowLink)->kind = 1;
    (*rowLink)->height = height;
    rowLines = &(*rowLink)->glyphs;
    for (i = 0; i <= length; i++) {
        if ((i == length) || ((textBytes[i] == 0x20) && (character == 0))) {
            if (((*rowLink)->width == 0.0f) || ((f64)((*rowLink)->width + (f32)width) < 124.8f)) {
                (*rowLink)->width += (f32)width;
                width = 0;
            } else {
                do { width = 0; } while (0); // FAKE: splits the basic block like the original
                while ((line != NULL) && (line->code == 0x20)) {
                    p = line;
                    line = p->next;
                    heapFreeDeferred(p);
                }
                if (line != NULL) {
                    rowLink = &(*rowLink)->next;
                    *rowLink = heapAlloc(0x20);
                    heapClearBlock(*rowLink);
                    (*rowLink)->kind = 1;
                    (*rowLink)->height = height;
                    rowLines = &(*rowLink)->glyphs;
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
            if (i != length) {
                i--;
            }
        } else if ((textBytes[i] > 0) && (textBytes[i] < 0x10)) {
            flags ^= 1 << textBytes[i];
        } else {
            character = 0;
            do { } while (0); // FAKE: splits the basic block like the original
            text = textBuffer;
            switch (textBytes[i]) {
            case 0x7E:
                _sprintf(textBuffer, "%s", D_8074E778[gActivePlayerActor->actorType]);
                break;
            case 0x40:
                _sprintf(textBuffer, "%d", D_80750AC8);
                break;
            default:
                _sprintf(textBuffer, "%c", textBytes[i]);
                break;
            }
            if (text[0] != 0) {
                do {
                    *lineLink = heapAlloc(0xA8);
                    heapClearBlock(*lineLink);
                    (*lineLink)->width = textGetCharAdvance(6, text[0]);
                    (*lineLink)->attr = flags;
                    (*lineLink)->code = text[0];
                    width += (*lineLink)->width;
                    width &= 0xFFFF;
                    lineLink = &(*lineLink)->next;
                    text++;
                } while (text[0] != 0);
            }
        }
    }
}

extern u8 sLanguageIndex;

void textLayoutAppendCommandList(ResQueueActorState *state, ResItem *item, ResParsedList *parsed) {
    s32 i;
    s32 offset;
    ResRecord *rec;
    ResTextSpan *span;
    ResParsedList *res;

    rec = &item->variant[sLanguageIndex];
    res = parsed; // FAKE: copying parsed into a local fixes which argument gets $s3/$s4 (Q0233)
    i = 0;
    offset = 0;
    if (rec->count > 0) {
        do {
            span = (ResTextSpan *)(rec->data.bytes + offset);
            textLayoutAppendRows(state, span->offset + res->payload, span->length);
            i += 1;
            offset += 8;
        } while (i < rec->count);
    }
}

extern struct EffectGridAsset *D_80755390[];

void resGridBuildGroups(ResQueueActorState *state, ResItem *item, ResParsedList *unused) {
    ResRow **link;
    ResGlyph **entry;
    ResRecord *source;
    ResGridCell *cell;
    s32 i;
    s32 pad;
    s16 width;
    s16 height;

    link = &state->rows;
    source = item->variant;
    if (*link != NULL) {
        do {
            link = &(*link)->next;
        } while (*link != NULL);
    }
    *link = heapAlloc(0x20);
    heapClearBlock(*link);
    (*link)->kind = 2;
    i = 0;
    entry = &(*link)->glyphs;
    if (source->count > 0) {
        do {
            cell = &source->data.cells[i];
            effectGridGetScaledDimensions(D_80755390[cell->effectId], &width, &height);
            if ((f64)((*link)->width + (f32)width) >= 124.8f) {
                link = &(*link)->next;
                *link = heapAlloc(0x20);
                heapClearBlock(*link);
                (*link)->kind = 2;
                entry = &(*link)->glyphs;
            }
            *entry = heapAlloc(0xA8);
            heapClearBlock(*entry);
            (*entry)->width = width;
            (*entry)->attr = cell->effectId;
            (*entry)->code = cell->sub;
            (*link)->width += (f32)(*entry)->width;
            (*link)->height = ((f32)height < (*link)->height) ? (*link)->height : (f32)height;
            entry = &(*entry)->next;
            i++;
        } while (i < source->count);
    }
}

void resApplyKind(Actor *actor, u16 resId, u8 kindIndex) {
    ResQueueActorState *state;
    ResParsedList *parsed;
    ResRow **link;
    ResItem *item;
    s32 i;

    state = actor->customState;
    if (actor->flags & 0x10) {
        resNodeDecRef(state->resId);
    }
    parsed = resNodeGetOrLoad(resId, 0);
    link = &state->rows;
    state->resId = resId;
    item = parsed->lists[kindIndex].items;
    for (i = 0; i < parsed->lists[kindIndex].count; i++) {
        if (*link != NULL) {
            do {
                link = &(*link)->next;
            } while (*link != NULL);
        }
        if (item->flags & 1) {
            textLayoutAppendCommandList(state, item, parsed);
        } else if (item->flags & 2) {
            resGridBuildGroups(state, item, parsed);
        }
        if (*link != NULL) {
            (*link)->data = item->data;
        }
        while ((*link != NULL) && ((*link)->next != NULL)) {
            link = &(*link)->next;
        }
        (*link)->timer = item->duration * 30.0f;
        item++;
    }
}

char *textTableGetString(s32 tableId, s32 rowIndex, s32 flags) {
    ResItem *row;
    ResRecord *choice;
    ResTextSpan *span;
    char *source;
    s32 length;
    char *dest;
    ResParsedList *table;

    table = resNodeGetOrLoad(tableId, 1);
    row = table->lists[rowIndex].items;
    choice = row->variant + sLanguageIndex;
    span = choice->data.spans;
    source = (char *)(span->offset + table->payload);
    length = span->length;
    dest = heapAlloc(length + 1);
    if (flags & 1) {
        heapFreeDeferred(dest);
    }
    memcpy(dest, source, length);
    dest[length] = 0;
    return dest;
}

void resQueueProcessNext(Actor *actor, Actor *key) {
    ResQueueActorState *state;
    ResQueueLink *queue;
    ResQueueEntry *entry;

    state = actor->customState;
    queue = resQueueGetOrCreate(key);
    if (queue->entries == NULL) {
        key->flags &= 0xFDFFFFFF;
        if (state->queueFlags & 1) {
            timerQueueAdd(camResumePathCallback, 0x1E, 0, 0, 0);
        }
        actor->state = 4;
        return;
    }
    resApplyKind(actor, queue->entries->resId, queue->entries->kindIndex);
    entry = queue->entries;
    queue->entries = entry->next;
    heapFreeDeferred(entry);
}

void resListReset(void) {
    sResNodeListHead = NULL;
    sResQueueHead = NULL;
}

void resQueueSetValue(s8 val) {
    sResQueueValue = val;
}
