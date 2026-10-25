// func_8070D754 (src/global/112080.c): stage 2: compilable structural reconstruction; instruction scheduling and local types remain.
typedef struct M112aLink { void *key; Actor *actor; void *entries; struct M112aLink *next; } M112aLink;
extern M112aLink *D_807550C4; extern void *func_80610FE8(s32); extern void heapClearBlock(void *); extern void actorSpawn(s32, s32, void *); extern Actor *D_807FBB44;
M112aLink *func_8070D754(void *arg0) { M112aLink **link = &D_807550C4; M112aLink *node; while (*link != NULL && (*link)->key != arg0) link = &(*link)->next; node = *link; if (node == NULL) { node = func_80610FE8(0x10); *link = node; heapClearBlock(node); node->key = arg0; actorSpawn(0x12B, 0, arg0); node->actor = D_807FBB44; } return node; }
