// func_8070DED4 (src/global/112080.c): Stage 4 (parked NON_MATCHING in ResA copy): same callee-saved set s0-s8/fs0-fs1, frame 0x98. Remaining diff (75 insn lines): 4 locals' stack offsets (line 0x80 vs 0x88, character 0x7B vs 0x79, time 0x60 vs 0x64, textBuffer 0x88 vs 0x6C), character=1 store scheduled in bnez delay region (target: nop, lw v0, ... sb), li a0,32 vs move a0,s4 (0x20 hoisted into s4 in loop), xor flags/width addu operand order, tmp loop var shares s0 with text (target keeps it in a0 = separate local, but a separate local grows frame to 0xA0). Needed: do{width=0;}while(0) in the wrap branch and do{}while(0) after character=0 (block splits, found by permuter; fixes rowLines/text reg allocation), rowLink=&owner->rows; rowHead=&owner->rows (order matters for s0/s3), (*rowLink)->width used directly (no value local), rowLines assigned before width=0.0f store in new-row block, switch(byte){case 0x7E; case 0x40; default} for sprintf layout, u32 width/textGetFontHeight for unsigned float fixup.
extern void *heapAlloc(s32);
extern void heapClearBlock(void *);
extern void heapFreeDeferred();
extern Actor *D_807FBB48;

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
    S112cLine **rowLines;
    u8 textBuffer[0xC];
    S112cRow **rowLink;
    S112cLine *line;
    s32 i;
    u8 character;
    S112cRow **rowHead;
    u32 width;
    S112cLine **lineLink;
    u32 flags;
    u8 *text;
    f32 time;
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
        if ((i == arg2) || ((((u8 *)arg1)[i] == 0x20) && (character == 0))) {
            character = 1;
            if (((*rowLink)->width == 0.0f) || ((f64)((*rowLink)->width + (f32)width) < 124.8f)) {
                (*rowLink)->width += (f32)width;
                width = 0;
            } else {
                do { width = 0; } while (0); // FAKE: splits the basic block like the original
                while ((line != NULL) && (line->character == 0x20)) {
                    text = (u8 *)line;
                    line = ((S112cLine *)text)->next;
                    heapFreeDeferred(text);
                }
                if (line != NULL) {
                    rowLink = &(*rowLink)->next;
                    *rowLink = heapAlloc(0x20);
                    heapClearBlock(*rowLink);
                    (*rowLink)->kind = 1;
                    (*rowLink)->height = time;
                    rowLines = &(*rowLink)->lines;
                    (*rowLink)->width = 0.0f;
                    for (text = (u8 *)line; text != NULL; text = (u8 *)((S112cLine *)text)->next) {
                        (*rowLink)->width += (f32)((S112cLine *)text)->width;
                    }
                }
            }
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
            flags = (flags ^ (1 << ((u8 *)arg1)[i])) & 0xFFFF;
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
                    width = (width + (*lineLink)->width) & 0xFFFF;
                    lineLink = &(*lineLink)->next;
                    text++;
                } while (text[0] != 0);
            }
        }
    }
}
