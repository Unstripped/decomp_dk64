// func_8071EFDC (src/global/11BC10.c): stage 6: exact fdiff scale permutation; assignment expression preserves caller-saved register allocation

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef signed char s8;
typedef short s16;
typedef long s32;
typedef long long s64;
typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned long vu32;
typedef volatile unsigned long long vu64;
typedef volatile signed char vs8;
typedef volatile short vs16;
typedef volatile long vs32;
typedef volatile long long vs64;
typedef float f32;
typedef double f64;
typedef unsigned int size_t;
typedef s32 OSPri;
typedef s32 OSId;
typedef union 
{
  struct 
  {
    f32 f_odd;
    f32 f_even;
  } f;
  f64 d;
} __OSfp;
typedef struct 
{
  u64 at;
  u64 v0;
  u64 v1;
  u64 a0;
  u64 a1;
  u64 a2;
  u64 a3;
  u64 t0;
  u64 t1;
  u64 t2;
  u64 t3;
  u64 t4;
  u64 t5;
  u64 t6;
  u64 t7;
  u64 s0;
  u64 s1;
  u64 s2;
  u64 s3;
  u64 s4;
  u64 s5;
  u64 s6;
  u64 s7;
  u64 t8;
  u64 t9;
  u64 gp;
  u64 sp;
  u64 s8;
  u64 ra;
  u64 lo;
  u64 hi;
  u32 sr;
  u32 pc;
  u32 cause;
  u32 badvaddr;
  u32 rcp;
  u32 fpcsr;
  __OSfp fp0;
  __OSfp fp2;
  __OSfp fp4;
  __OSfp fp6;
  __OSfp fp8;
  __OSfp fp10;
  __OSfp fp12;
  __OSfp fp14;
  __OSfp fp16;
  __OSfp fp18;
  __OSfp fp20;
  __OSfp fp22;
  __OSfp fp24;
  __OSfp fp26;
  __OSfp fp28;
  __OSfp fp30;
} __OSThreadContext;
typedef struct 
{
  u32 flag;
  u32 count;
  u64 time;
} __OSThreadprofile_s;
typedef struct OSThread_s
{
  struct OSThread_s *next;
  OSPri priority;
  struct OSThread_s **queue;
  struct OSThread_s *tlnext;
  u16 state;
  u16 flags;
  OSId id;
  int fp;
  __OSThreadprofile_s *thprof;
  __OSThreadContext context;
} OSThread;
extern void osCreateThread(OSThread *, OSId, void (*)(void *), void *, void *, OSPri);
extern void osDestroyThread(OSThread *);
extern void osYieldThread(void);
extern void osStartThread(OSThread *);
extern void osStopThread(OSThread *);
extern OSId osGetThreadId(OSThread *);
extern void osSetThreadPri(OSThread *, OSPri);
extern OSPri osGetThreadPri(OSThread *);
typedef u32 OSEvent;
typedef void *OSMesg;
typedef struct OSMesgQueue_s
{
  OSThread *mtqueue;
  OSThread *fullqueue;
  s32 validCount;
  s32 first;
  s32 msgCount;
  OSMesg *msg;
} OSMesgQueue;
extern void osCreateMesgQueue(OSMesgQueue *, OSMesg *, s32);
extern s32 osSendMesg(OSMesgQueue *, OSMesg, s32);
extern s32 osJamMesg(OSMesgQueue *, OSMesg, s32);
extern s32 osRecvMesg(OSMesgQueue *, OSMesg *, s32);
extern void osSetEventMesg(OSEvent, OSMesgQueue *, OSMesg);
typedef u32 OSIntMask;
typedef u32 OSHWIntr;
extern OSIntMask osGetIntMask(void);
extern OSIntMask osSetIntMask(OSIntMask);
typedef u32 OSPageMask;
extern void osMapTLB(s32, OSPageMask, void *, u32, u32, s32);
extern void osMapTLBRdb(void);
extern void osUnmapTLB(s32);
extern void osUnmapTLBAll(void);
extern void osSetTLBASID(s32);
typedef struct 
{
  u32 errStatus;
  void *dramAddr;
  void *C2Addr;
  u32 sectorSize;
  u32 C1ErrNum;
  u32 C1ErrSector[4];
} __OSBlockInfo;
typedef struct 
{
  u32 cmdType;
  u16 transferMode;
  u16 blockNum;
  s32 sectorNum;
  u32 devAddr;
  u32 bmCtlShadow;
  u32 seqCtlShadow;
  __OSBlockInfo block[2];
} __OSTranxInfo;
typedef struct OSPiHandle_s
{
  struct OSPiHandle_s *next;
  u8 type;
  u8 latency;
  u8 pageSize;
  u8 relDuration;
  u8 pulse;
  u8 domain;
  u32 baseAddress;
  u32 speed;
  __OSTranxInfo transferInfo;
} OSPiHandle;
typedef struct 
{
  u8 type;
  u32 address;
} OSPiInfo;
typedef struct 
{
  u16 type;
  u8 pri;
  u8 status;
  OSMesgQueue *retQueue;
} OSIoMesgHdr;
typedef struct 
{
  OSIoMesgHdr hdr;
  void *dramAddr;
  u32 devAddr;
  u32 size;
  OSPiHandle *piHandle;
} OSIoMesg;
typedef struct 
{
  s32 active;
  OSThread *thread;
  OSMesgQueue *cmdQueue;
  OSMesgQueue *evtQueue;
  OSMesgQueue *acsQueue;
  s32 (*dma)(s32, u32, void *, u32);
  s32 (*edma)(OSPiHandle *, s32, u32, void *, u32);
} OSDevMgr;
extern OSPiHandle *__osPiTable;
extern u32 osPiGetStatus(void);
extern s32 osPiGetDeviceType(void);
extern s32 osPiWriteIo(u32, u32);
extern s32 osPiReadIo(u32, u32 *);
extern s32 osPiStartDma(OSIoMesg *, s32, s32, u32, void *, u32, OSMesgQueue *);
extern void osCreatePiManager(OSPri, OSMesgQueue *, OSMesg *, s32);
extern s32 osPiRawStartDma(s32, u32, void *, u32);
extern s32 osPiRawWriteIo(u32, u32);
extern s32 osPiRawReadIo(u32, u32 *);
extern s32 __osPiRawStartDma(s32, u32, void *, u32);
extern s32 __osPiRawWriteIo(u32, u32);
extern s32 __osPiRawReadIo(u32, u32 *);
extern OSPiHandle *osCartRomInit(void);
extern OSPiHandle *osLeoDiskInit(void);
extern OSPiHandle *osDriveRomInit(void);
extern s32 osEPiDeviceType(OSPiHandle *, OSPiInfo *);
extern s32 osEPiWriteIo(OSPiHandle *, u32, u32);
extern s32 osEPiReadIo(OSPiHandle *, u32, u32 *);
extern s32 osEPiStartDma(OSPiHandle *, OSIoMesg *, s32);
extern s32 osEPiLinkHandle(OSPiHandle *);
typedef struct 
{
  u32 ctrl;
  u32 width;
  u32 burst;
  u32 vSync;
  u32 hSync;
  u32 leap;
  u32 hStart;
  u32 xScale;
  u32 vCurrent;
} OSViCommonRegs;
typedef struct 
{
  u32 origin;
  u32 yScale;
  u32 vStart;
  u32 vBurst;
  u32 vIntr;
} OSViFieldRegs;
typedef struct 
{
  u8 type;
  OSViCommonRegs comRegs;
  OSViFieldRegs fldRegs[2];
} OSViMode;
extern OSViMode osViModeTable[];
extern OSViMode osViModeNtscLpn1;
extern OSViMode osViModeNtscLpf1;
extern OSViMode osViModeNtscLan1;
extern OSViMode osViModeNtscLaf1;
extern OSViMode osViModeNtscLpn2;
extern OSViMode osViModeNtscLpf2;
extern OSViMode osViModeNtscLan2;
extern OSViMode osViModeNtscLaf2;
extern OSViMode osViModeNtscHpn1;
extern OSViMode osViModeNtscHpf1;
extern OSViMode osViModeNtscHan1;
extern OSViMode osViModeNtscHaf1;
extern OSViMode osViModeNtscHpn2;
extern OSViMode osViModeNtscHpf2;
extern OSViMode osViModePalLpn1;
extern OSViMode osViModePalLpf1;
extern OSViMode osViModePalLan1;
extern OSViMode osViModePalLaf1;
extern OSViMode osViModePalLpn2;
extern OSViMode osViModePalLpf2;
extern OSViMode osViModePalLan2;
extern OSViMode osViModePalLaf2;
extern OSViMode osViModePalHpn1;
extern OSViMode osViModePalHpf1;
extern OSViMode osViModePalHan1;
extern OSViMode osViModePalHaf1;
extern OSViMode osViModePalHpn2;
extern OSViMode osViModePalHpf2;
extern OSViMode osViModeMpalLpn1;
extern OSViMode osViModeMpalLpf1;
extern OSViMode osViModeMpalLan1;
extern OSViMode osViModeMpalLaf1;
extern OSViMode osViModeMpalLpn2;
extern OSViMode osViModeMpalLpf2;
extern OSViMode osViModeMpalLan2;
extern OSViMode osViModeMpalLaf2;
extern OSViMode osViModeMpalHpn1;
extern OSViMode osViModeMpalHpf1;
extern OSViMode osViModeMpalHan1;
extern OSViMode osViModeMpalHaf1;
extern OSViMode osViModeMpalHpn2;
extern OSViMode osViModeMpalHpf2;
extern OSViMode osViModeFpalLpn1;
extern OSViMode osViModeFpalLpf1;
extern OSViMode osViModeFpalLan1;
extern OSViMode osViModeFpalLaf1;
extern OSViMode osViModeFpalLpn2;
extern OSViMode osViModeFpalLpf2;
extern OSViMode osViModeFpalLan2;
extern OSViMode osViModeFpalLaf2;
extern OSViMode osViModeFpalHpn1;
extern OSViMode osViModeFpalHpf1;
extern OSViMode osViModeFpalHan1;
extern OSViMode osViModeFpalHaf1;
extern OSViMode osViModeFpalHpn2;
extern OSViMode osViModeFpalHpf2;
extern u32 osViGetStatus(void);
extern u32 osViGetCurrentMode(void);
extern u32 osViGetCurrentLine(void);
extern u32 osViGetCurrentField(void);
extern void *osViGetCurrentFramebuffer(void);
extern void *osViGetNextFramebuffer(void);
extern void osViSetXScale(f32);
extern void osViSetYScale(f32);
extern void osViExtendVStart(u32);
extern void osViSetSpecialFeatures(u32);
extern void osViSetMode(OSViMode *);
extern void osViSetEvent(OSMesgQueue *, OSMesg, u32);
extern void osViSwapBuffer(void *);
extern void osViBlack(u8);
extern void osViFade(u8, u16);
extern void osViRepeatLine(u8);
extern void osCreateViManager(OSPri);
extern u32 osAiGetStatus(void);
extern u32 osAiGetLength(void);
extern s32 osAiSetFrequency(u32);
extern s32 osAiSetNextBuffer(void *, u32);
typedef u64 OSTime;
typedef struct OSTimer_s
{
  struct OSTimer_s *next;
  struct OSTimer_s *prev;
  OSTime interval;
  OSTime value;
  OSMesgQueue *mq;
  OSMesg msg;
} OSTimer;
extern OSTime osGetTime(void);
extern void osSetTime(OSTime);
extern int osSetTimer(OSTimer *, OSTime, OSTime, OSMesgQueue *, OSMesg);
extern int osStopTimer(OSTimer *);
typedef struct 
{
  u16 type;
  u8 status;
  u8 errno;
} OSContStatus;
typedef struct 
{
  u16 button;
  s8 stick_x;
  s8 stick_y;
  u8 errno;
} OSContPad;
typedef struct 
{
  void *address;
  u8 databuffer[32];
  u8 addressCrc;
  u8 dataCrc;
  u8 errno;
} OSContRamIo;
extern s32 osContInit(OSMesgQueue *, u8 *, OSContStatus *);
extern s32 osContReset(OSMesgQueue *, OSContStatus *);
extern s32 osContStartQuery(OSMesgQueue *);
extern s32 osContStartReadData(OSMesgQueue *);
extern s32 osContSetCh(u8);
extern void osContGetQuery(OSContStatus *);
extern void osContGetReadData(OSContPad *);
typedef struct 
{
  int status;
  OSMesgQueue *queue;
  int channel;
  u8 id[32];
  u8 label[32];
  int version;
  int dir_size;
  int inode_table;
  int minode_table;
  int dir_table;
  int inode_start_page;
  u8 banks;
  u8 activebank;
} OSPfs;
typedef struct 
{
  u32 file_size;
  u32 game_code;
  u16 company_code;
  char ext_name[4];
  char game_name[16];
} OSPfsState;
extern s32 osPfsInitPak(OSMesgQueue *, OSPfs *, int);
extern s32 osPfsRepairId(OSPfs *);
extern s32 osPfsInit(OSMesgQueue *, OSPfs *, int);
extern s32 osPfsReFormat(OSPfs *, OSMesgQueue *, int);
extern s32 osPfsChecker(OSPfs *);
extern s32 osPfsAllocateFile(OSPfs *, u16, u32, u8 *, u8 *, int, s32 *);
extern s32 osPfsFindFile(OSPfs *, u16, u32, u8 *, u8 *, s32 *);
extern s32 osPfsDeleteFile(OSPfs *, u16, u32, u8 *, u8 *);
extern s32 osPfsReadWriteFile(OSPfs *, s32, u8, int, int, u8 *);
extern s32 osPfsFileState(OSPfs *, s32, OSPfsState *);
extern s32 osPfsGetLabel(OSPfs *, u8 *, int *);
extern s32 osPfsSetLabel(OSPfs *, u8 *);
extern s32 osPfsIsPlug(OSMesgQueue *, u8 *);
extern s32 osPfsFreeBlocks(OSPfs *, s32 *);
extern s32 osPfsNumFiles(OSPfs *, s32 *, s32 *);
typedef struct 
{
  u16 fixed1;
  u16 start_address;
  u8 nintendo_chr[0x30];
  u8 game_title[16];
  u16 company_code;
  u8 body_code;
  u8 cart_type;
  u8 rom_size;
  u8 ram_size;
  u8 country_code;
  u8 fixed2;
  u8 version;
  u8 isum;
  u16 sum;
} OSGbpakId;
extern s32 osGbpakInit(OSMesgQueue *, OSPfs *, int);
extern s32 osGbpakPower(OSPfs *, s32);
extern s32 osGbpakGetStatus(OSPfs *, u8 *);
extern s32 osGbpakReadWrite(OSPfs *, u16, u16, u8 *, u16);
extern s32 osGbpakReadId(OSPfs *, OSGbpakId *, u8 *);
extern s32 osGbpakCheckConnector(OSPfs *, u8 *);
typedef struct 
{
  OSMesgQueue *__mq;
  int __channel;
  s32 __mode;
  u8 cmd_status;
} OSVoiceHandle;
typedef struct 
{
  u16 warning;
  u16 answer_num;
  u16 voice_level;
  u16 voice_sn;
  u16 voice_time;
  u16 answer[5];
  u16 distance[5];
} OSVoiceData;
extern s32 osVoiceInit(OSMesgQueue *, OSVoiceHandle *, int);
extern s32 osVoiceCheckWord(u8 *data);
extern s32 osVoiceClearDictionary(OSVoiceHandle *, u8);
extern s32 osVoiceControlGain(OSVoiceHandle *, s32, s32);
extern s32 osVoiceSetWord(OSVoiceHandle *, u8 *);
extern s32 osVoiceStartReadData(OSVoiceHandle *);
extern s32 osVoiceStopReadData(OSVoiceHandle *);
extern s32 osVoiceGetReadData(OSVoiceHandle *, OSVoiceData *);
extern s32 osVoiceMaskDictionary(OSVoiceHandle *, u8 *, int);
extern void osVoiceCountSyllables(u8 *, u32 *);
extern void osInvalDCache(void *, s32);
extern void osInvalICache(void *, s32);
extern void osWritebackDCache(void *, s32);
extern void osWritebackDCacheAll(void);
typedef struct 
{
  u16 *histo_base;
  u32 histo_size;
  u32 *text_start;
  u32 *text_end;
} OSProf;
extern void osProfileInit(OSProf *, u32 profcnt);
extern void osProfileStart(u32);
extern void osProfileFlush(void);
extern void osProfileStop(void);
extern void osThreadProfileClear(OSId);
extern void osThreadProfileInit(void);
extern void osThreadProfileStart(void);
extern void osThreadProfileStop(void);
extern u32 osThreadProfileReadCount(OSId);
extern u32 osThreadProfileReadCountTh(OSThread *);
extern OSTime osThreadProfileReadTime(OSId);
extern OSTime osThreadProfileReadTimeTh(OSThread *);
extern u32 osGetCount(void);
extern s32 osRomType;
extern void *osRomBase;
extern s32 osTvType;
extern s32 osResetType;
extern s32 osCicId;
extern s32 osVersion;
extern u32 osMemSize;
extern s32 osAppNMIBuffer[];
extern u64 osClockRate;
extern OSIntMask __OSGlobalIntMask;
extern void osInitialize(void);
extern void osExit(void);
extern u32 osGetMemSize(void);
extern s32 osAfterPreNMI(void);
extern s32 osEepromProbe(OSMesgQueue *);
extern s32 osEepromRead(OSMesgQueue *, u8, u8 *);
extern s32 osEepromWrite(OSMesgQueue *, u8, u8 *);
extern s32 osEepromLongRead(OSMesgQueue *, u8, u8 *, int);
extern s32 osEepromLongWrite(OSMesgQueue *, u8, u8 *, int);
extern OSPiHandle *osFlashReInit(u8 latency, u8 pulse, u8 page_size, u8 rel_duration, u32 start);
extern OSPiHandle *osFlashInit(void);
extern void osFlashReadStatus(u8 *flash_status);
extern void osFlashReadId(u32 *flash_type, u32 *flash_maker);
extern void osFlashClearStatus(void);
extern s32 osFlashAllErase(void);
extern s32 osFlashSectorErase(u32 page_num);
extern s32 osFlashWriteBuffer(OSIoMesg *mb, s32 priority, void *dramAddr, OSMesgQueue *mq);
extern s32 osFlashWriteArray(u32 page_num);
extern s32 osFlashReadArray(OSIoMesg *mb, s32 priority, u32 page_num, void *dramAddr, u32 n_pages, OSMesgQueue *mq);
extern void osFlashChange(u32 flash_num);
extern void osFlashAllEraseThrough(void);
extern void osFlashSectorEraseThrough(u32 page_num);
extern s32 osFlashCheckEraseEnd(void);
extern void __osInitialize_common(void);
extern s32 osTestHost(void);
extern void osReadHost(void *, u32);
extern void osWriteHost(void *, u32);
extern void osAckRamromRead(void);
extern void osAckRamromWrite(void);
extern void osInitRdb(u8 *sendBuf, u32 sendSize);
extern u32 osVirtualToPhysical(void *);
extern void *osPhysicalToVirtual(u32);
extern u32 osDpGetStatus(void);
extern void osDpSetStatus(u32);
extern void osDpGetCounters(u32 *);
extern s32 osDpSetNextBuffer(void *, u64);
extern s32 osMotorInit(OSMesgQueue *, OSPfs *, int);
extern s32 __osMotorAccess(OSPfs *, s32);
extern void bcopy(const void *, void *, int);
extern int bcmp(const void *, const void *, int);
extern void bzero(void *, int);
extern int sprintf(char *s, const char *fmt, ...);
extern void osSyncPrintf(const char *fmt, ...);
typedef struct _Region_s
{
  u8 *r_startBufferAddress;
  u8 *r_endAddress;
  s32 r_bufferSize;
  s32 r_bufferCount;
  u16 r_freeList;
  u16 r_alignSize;
} OSRegion;
extern void *osCreateRegion(void *, u32, u32, u32);
extern void *osMalloc(void *);
extern void osFree(void *, void *);
extern s32 osGetRegionBufCount(void *);
extern s32 osGetRegionBufSize(void *);
extern void rmonMain(void *);
extern void rmonPrintf(const char *, ...);
typedef struct 
{
  u32 type;
  u32 flags;
  u64 *ucode_boot;
  u32 ucode_boot_size;
  u64 *ucode;
  u32 ucode_size;
  u64 *ucode_data;
  u32 ucode_data_size;
  u64 *dram_stack;
  u32 dram_stack_size;
  u64 *output_buff;
  u64 *output_buff_size;
  u64 *data_ptr;
  u32 data_size;
  u64 *yield_data_ptr;
  u32 yield_data_size;
} OSTask_t;
typedef union 
{
  OSTask_t t;
  long long int force_structure_alignment;
} OSTask;
typedef u32 OSYieldResult;
extern void osSpTaskLoad(OSTask *tp);
extern void osSpTaskStartGo(OSTask *tp);
extern void osSpTaskYield(void);
extern OSYieldResult osSpTaskYielded(OSTask *tp);
typedef struct 
{
  short ob[3];
  unsigned short flag;
  short tc[2];
  unsigned char cn[4];
} Vtx_t;
typedef struct 
{
  short ob[3];
  unsigned short flag;
  short tc[2];
  signed char n[3];
  unsigned char a;
} Vtx_tn;
typedef union 
{
  Vtx_t v;
  Vtx_tn n;
  long long int force_structure_alignment;
} Vtx;
typedef struct 
{
  void *SourceImagePointer;
  void *TlutPointer;
  short Stride;
  short SubImageWidth;
  short SubImageHeight;
  char SourceImageType;
  char SourceImageBitSize;
  short SourceImageOffsetS;
  short SourceImageOffsetT;
  char dummy[4];
} uSprite_t;
typedef union 
{
  uSprite_t s;
  long long int force_structure_allignment[3];
} uSprite;
typedef struct 
{
  unsigned char flag;
  unsigned char v[3];
} Tri;
typedef long Mtx_t[4][4];
typedef union 
{
  Mtx_t m;
  long long int force_structure_alignment;
} Mtx;
typedef struct 
{
  short vscale[4];
  short vtrans[4];
} Vp_t;
typedef union 
{
  Vp_t vp;
  long long int force_structure_alignment;
} Vp;
typedef struct 
{
  unsigned char col[3];
  char pad1;
  unsigned char colc[3];
  char pad2;
  signed char dir[3];
  char pad3;
} Light_t;
typedef struct 
{
  unsigned char col[3];
  char pad1;
  unsigned char colc[3];
  char pad2;
} Ambient_t;
typedef struct 
{
  int x1;
  int y1;
  int x2;
  int y2;
} Hilite_t;
typedef union 
{
  Light_t l;
  long long int force_structure_alignment[2];
} Light;
typedef union 
{
  Ambient_t l;
  long long int force_structure_alignment[1];
} Ambient;
typedef struct 
{
  Ambient a;
  Light l[7];
} Lightsn;
typedef struct 
{
  Ambient a;
  Light l[1];
} Lights0;
typedef struct 
{
  Ambient a;
  Light l[1];
} Lights1;
typedef struct 
{
  Ambient a;
  Light l[2];
} Lights2;
typedef struct 
{
  Ambient a;
  Light l[3];
} Lights3;
typedef struct 
{
  Ambient a;
  Light l[4];
} Lights4;
typedef struct 
{
  Ambient a;
  Light l[5];
} Lights5;
typedef struct 
{
  Ambient a;
  Light l[6];
} Lights6;
typedef struct 
{
  Ambient a;
  Light l[7];
} Lights7;
typedef struct 
{
  Light l[2];
} LookAt;
typedef union 
{
  Hilite_t h;
  long int force_structure_alignment[4];
} Hilite;
typedef struct 
{
  int cmd : 8;
  unsigned int par : 8;
  unsigned int len : 16;
  unsigned int addr;
} Gdma;
typedef struct 
{
  int cmd : 8;
  int pad : 24;
  Tri tri;
} Gtri;
typedef struct 
{
  int cmd : 8;
  int pad1 : 24;
  int pad2 : 24;
  unsigned char param : 8;
} Gpopmtx;
typedef struct 
{
  int cmd : 8;
  int pad0 : 8;
  int mw_index : 8;
  int number : 8;
  int pad1 : 8;
  int base : 24;
} Gsegment;
typedef struct 
{
  int cmd : 8;
  int pad0 : 8;
  int sft : 8;
  int len : 8;
  unsigned int data : 32;
} GsetothermodeL;
typedef struct 
{
  int cmd : 8;
  int pad0 : 8;
  int sft : 8;
  int len : 8;
  unsigned int data : 32;
} GsetothermodeH;
typedef struct 
{
  unsigned char cmd;
  unsigned char lodscale;
  unsigned char tile;
  unsigned char on;
  unsigned short s;
  unsigned short t;
} Gtexture;
typedef struct 
{
  int cmd : 8;
  int pad : 24;
  Tri line;
} Gline3D;
typedef struct 
{
  int cmd : 8;
  int pad1 : 24;
  short int pad2;
  short int scale;
} Gperspnorm;
typedef struct 
{
  int cmd : 8;
  unsigned int fmt : 3;
  unsigned int siz : 2;
  unsigned int pad : 7;
  unsigned int wd : 12;
  unsigned int dram;
} Gsetimg;
typedef struct 
{
  int cmd : 8;
  unsigned int muxs0 : 24;
  unsigned int muxs1 : 32;
} Gsetcombine;
typedef struct 
{
  int cmd : 8;
  unsigned char pad;
  unsigned char prim_min_level;
  unsigned char prim_level;
  unsigned long color;
} Gsetcolor;
typedef struct 
{
  int cmd : 8;
  int x0 : 10;
  int x0frac : 2;
  int y0 : 10;
  int y0frac : 2;
  unsigned int pad : 8;
  int x1 : 10;
  int x1frac : 2;
  int y1 : 10;
  int y1frac : 2;
} Gfillrect;
typedef struct 
{
  int cmd : 8;
  unsigned int fmt : 3;
  unsigned int siz : 2;
  unsigned int pad0 : 1;
  unsigned int line : 9;
  unsigned int tmem : 9;
  unsigned int pad1 : 5;
  unsigned int tile : 3;
  unsigned int palette : 4;
  unsigned int ct : 1;
  unsigned int mt : 1;
  unsigned int maskt : 4;
  unsigned int shiftt : 4;
  unsigned int cs : 1;
  unsigned int ms : 1;
  unsigned int masks : 4;
  unsigned int shifts : 4;
} Gsettile;
typedef struct 
{
  int cmd : 8;
  unsigned int sl : 12;
  unsigned int tl : 12;
  int pad : 5;
  unsigned int tile : 3;
  unsigned int sh : 12;
  unsigned int th : 12;
} Gloadtile;
typedef Gloadtile Gloadblock;
typedef Gloadtile Gsettilesize;
typedef Gloadtile Gloadtlut;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int xl : 12;
  unsigned int yl : 12;
  unsigned int pad1 : 5;
  unsigned int tile : 3;
  unsigned int xh : 12;
  unsigned int yh : 12;
  unsigned int s : 16;
  unsigned int t : 16;
  unsigned int dsdx : 16;
  unsigned int dtdy : 16;
} Gtexrect;
typedef struct 
{
  unsigned long w0;
  unsigned long w1;
  unsigned long w2;
  unsigned long w3;
} TexRect;
typedef struct 
{
  unsigned int w0;
  unsigned int w1;
} Gwords;
typedef union 
{
  Gwords words;
  Gdma dma;
  Gtri tri;
  Gline3D line;
  Gpopmtx popmtx;
  Gsegment segment;
  GsetothermodeH setothermodeH;
  GsetothermodeL setothermodeL;
  Gtexture texture;
  Gperspnorm perspnorm;
  Gsetimg setimg;
  Gsetcombine setcombine;
  Gsetcolor setcolor;
  Gfillrect fillrect;
  Gsettile settile;
  Gloadtile loadtile;
  Gsettilesize settilesize;
  Gloadtlut loadtlut;
  long long int force_structure_alignment;
} Gfx;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int flags : 8;
  unsigned int gain : 16;
  unsigned int addr;
} Aadpcm;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int flags : 8;
  unsigned int gain : 16;
  unsigned int addr;
} Apolef;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int flags : 8;
  unsigned int pad1 : 16;
  unsigned int addr;
} Aenvelope;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int pad1 : 8;
  unsigned int dmem : 16;
  unsigned int pad2 : 16;
  unsigned int count : 16;
} Aclearbuff;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int pad1 : 8;
  unsigned int pad2 : 16;
  unsigned int inL : 16;
  unsigned int inR : 16;
} Ainterleave;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int pad1 : 24;
  unsigned int addr;
} Aloadbuff;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int flags : 8;
  unsigned int pad1 : 16;
  unsigned int addr;
} Aenvmixer;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int flags : 8;
  unsigned int gain : 16;
  unsigned int dmemi : 16;
  unsigned int dmemo : 16;
} Amixer;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int flags : 8;
  unsigned int dmem2 : 16;
  unsigned int addr;
} Apan;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int flags : 8;
  unsigned int pitch : 16;
  unsigned int addr;
} Aresample;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int flags : 8;
  unsigned int pad1 : 16;
  unsigned int addr;
} Areverb;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int pad1 : 24;
  unsigned int addr;
} Asavebuff;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int pad1 : 24;
  unsigned int pad2 : 2;
  unsigned int number : 4;
  unsigned int base : 24;
} Asegment;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int flags : 8;
  unsigned int dmemin : 16;
  unsigned int dmemout : 16;
  unsigned int count : 16;
} Asetbuff;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int flags : 8;
  unsigned int vol : 16;
  unsigned int voltgt : 16;
  unsigned int volrate : 16;
} Asetvol;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int pad1 : 8;
  unsigned int dmemin : 16;
  unsigned int dmemout : 16;
  unsigned int count : 16;
} Admemmove;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int pad1 : 8;
  unsigned int count : 16;
  unsigned int addr;
} Aloadadpcm;
typedef struct 
{
  unsigned int cmd : 8;
  unsigned int pad1 : 8;
  unsigned int pad2 : 16;
  unsigned int addr;
} Asetloop;
typedef struct 
{
  unsigned int w0;
  unsigned int w1;
} Awords;
typedef union 
{
  Awords words;
  Aadpcm adpcm;
  Apolef polef;
  Aclearbuff clearbuff;
  Aenvelope envelope;
  Ainterleave interleave;
  Aloadbuff loadbuff;
  Aenvmixer envmixer;
  Aresample resample;
  Areverb reverb;
  Asavebuff savebuff;
  Asegment segment;
  Asetbuff setbuff;
  Asetvol setvol;
  Admemmove dmemmove;
  Aloadadpcm loadadpcm;
  Amixer mixer;
  Asetloop setloop;
  long long int force_union_align;
} Acmd;
typedef short ADPCM_STATE[16];
typedef short POLEF_STATE[4];
typedef short RESAMPLE_STATE[16];
typedef short ENVMIX_STATE[40];
typedef s32 ALMicroTime;
typedef u8 ALPan;
typedef struct ALLink_s
{
  struct ALLink_s *next;
  struct ALLink_s *prev;
} ALLink;
void alUnlink(ALLink *element);
void alLink(ALLink *element, ALLink *after);
typedef s32 (*ALDMAproc)(s32 addr, s32 len, void *state);
typedef ALDMAproc (*ALDMANew)(void *state);
void alCopy(void *src, void *dest, s32 len);
typedef struct 
{
  u8 *base;
  u8 *cur;
  s32 len;
  s32 count;
} ALHeap;
void alHeapInit(ALHeap *hp, u8 *base, s32 len);
void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size);
s32 alHeapCheck(ALHeap *hp);
typedef u8 ALFxId;
typedef void *ALFxRef;
enum 
{
  AL_ADPCM_WAVE = 0,
  AL_RAW16_WAVE
};
typedef struct 
{
  s32 order;
  s32 npredictors;
  s16 book[1];
} ALADPCMBook;
typedef struct 
{
  u32 start;
  u32 end;
  u32 count;
  ADPCM_STATE state;
} ALADPCMloop;
typedef struct 
{
  u32 start;
  u32 end;
  u32 count;
} ALRawLoop;
typedef struct 
{
  ALMicroTime attackTime;
  ALMicroTime decayTime;
  ALMicroTime releaseTime;
  u8 attackVolume;
  u8 decayVolume;
} ALEnvelope;
typedef struct 
{
  u8 velocityMin;
  u8 velocityMax;
  u8 keyMin;
  u8 keyMax;
  u8 keyBase;
  s8 detune;
} ALKeyMap;
typedef struct 
{
  ALADPCMloop *loop;
  ALADPCMBook *book;
} ALADPCMWaveInfo;
typedef struct 
{
  ALRawLoop *loop;
} ALRAWWaveInfo;
typedef struct ALWaveTable_s
{
  u8 *base;
  s32 len;
  u8 type;
  u8 flags;
  union 
  {
    ALADPCMWaveInfo adpcmWave;
    ALRAWWaveInfo rawWave;
  } waveInfo;
} ALWaveTable;
typedef struct ALSound_s
{
  ALEnvelope *envelope;
  ALKeyMap *keyMap;
  ALWaveTable *wavetable;
  ALPan samplePan;
  u8 sampleVolume;
  u8 flags;
} ALSound;
typedef struct 
{
  u8 volume;
  ALPan pan;
  u8 priority;
  u8 flags;
  u8 tremType;
  u8 tremRate;
  u8 tremDepth;
  u8 tremDelay;
  u8 vibType;
  u8 vibRate;
  u8 vibDepth;
  u8 vibDelay;
  s16 bendRange;
  s16 soundCount;
  ALSound *soundArray[1];
} ALInstrument;
typedef struct ALBank_s
{
  s16 instCount;
  u8 flags;
  u8 pad;
  s32 sampleRate;
  ALInstrument *percussion;
  ALInstrument *instArray[1];
} ALBank;
typedef struct 
{
  s16 revision;
  s16 bankCount;
  ALBank *bankArray[1];
} ALBankFile;
void alBnkfNew(ALBankFile *f, u8 *table);
typedef struct 
{
  u8 *offset;
  s32 len;
} ALSeqData;
typedef struct 
{
  s16 revision;
  s16 seqCount;
  ALSeqData seqArray[1];
} ALSeqFile;
void alSeqFileNew(ALSeqFile *f, u8 *base);
typedef ALMicroTime (*ALVoiceHandler)(void *);
typedef struct 
{
  s32 maxVVoices;
  s32 maxPVoices;
  s32 maxUpdates;
  s32 maxFXbusses;
  void *dmaproc;
  ALHeap *heap;
  s32 outputRate;
  ALFxId fxType;
  s32 *params;
} ALSynConfig;
typedef struct ALPlayer_s
{
  struct ALPlayer_s *next;
  void *clientData;
  ALVoiceHandler handler;
  ALMicroTime callTime;
  s32 samplesLeft;
} ALPlayer;
typedef struct ALVoice_s
{
  ALLink node;
  struct PVoice_s *pvoice;
  ALWaveTable *table;
  void *clientPrivate;
  s16 state;
  s16 priority;
  s16 fxBus;
  s16 unityPitch;
} ALVoice;
typedef struct ALVoiceConfig_s
{
  s16 priority;
  s16 fxBus;
  u8 unityPitch;
} ALVoiceConfig;
typedef struct 
{
  ALPlayer *head;
  ALLink pFreeList;
  ALLink pAllocList;
  ALLink pLameList;
  s32 paramSamples;
  s32 curSamples;
  ALDMANew dma;
  ALHeap *heap;
  struct ALParam_s *paramList;
  struct ALMainBus_s *mainBus;
  struct ALAuxBus_s *auxBus;
  struct ALFilter_s *outputFilter;
  s32 numPVoices;
  s32 maxAuxBusses;
  s32 outputRate;
  s32 maxOutSamples;
} ALSynth;
void alSynNew(ALSynth *s, ALSynConfig *config);
void alSynDelete(ALSynth *s);
void alSynAddPlayer(ALSynth *s, ALPlayer *client);
void alSynRemovePlayer(ALSynth *s, ALPlayer *client);
s32 alSynAllocVoice(ALSynth *s, ALVoice *v, ALVoiceConfig *vc);
void alSynFreeVoice(ALSynth *s, ALVoice *voice);
void alSynStartVoice(ALSynth *s, ALVoice *voice, ALWaveTable *w);
void alSynStartVoiceParams(ALSynth *s, ALVoice *voice, ALWaveTable *w, f32 pitch, s16 vol, ALPan pan, u8 fxmix, ALMicroTime t);
void alSynStopVoice(ALSynth *s, ALVoice *voice);
void alSynSetVol(ALSynth *s, ALVoice *v, s16 vol, ALMicroTime delta);
void alSynSetPitch(ALSynth *s, ALVoice *voice, f32 ratio);
void alSynSetPan(ALSynth *s, ALVoice *voice, ALPan pan);
void alSynSetFXMix(ALSynth *s, ALVoice *voice, u8 fxmix);
void alSynSetPriority(ALSynth *s, ALVoice *voice, s16 priority);
s16 alSynGetPriority(ALSynth *s, ALVoice *voice);
ALFxRef *alSynAllocFX(ALSynth *s, s16 bus, ALSynConfig *c, ALHeap *hp);
ALFxRef alSynGetFXRef(ALSynth *s, s16 bus, s16 index);
void alSynFreeFX(ALSynth *s, ALFxRef *fx);
void alSynSetFXParam(ALSynth *s, ALFxRef fx, s16 paramID, void *param);
typedef struct 
{
  ALSynth drvr;
} ALGlobals;
extern ALGlobals *alGlobals;
void alInit(ALGlobals *glob, ALSynConfig *c);
void alClose(ALGlobals *glob);
Acmd *alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen);
enum ALMsg
{
  AL_SEQ_REF_EVT,
  AL_SEQ_MIDI_EVT,
  AL_SEQP_MIDI_EVT,
  AL_TEMPO_EVT,
  AL_SEQ_END_EVT,
  AL_NOTE_END_EVT,
  AL_SEQP_ENV_EVT,
  AL_SEQP_META_EVT,
  AL_SEQP_PROG_EVT,
  AL_SEQP_API_EVT,
  AL_SEQP_VOL_EVT,
  AL_SEQP_LOOP_EVT,
  AL_SEQP_PRIORITY_EVT,
  AL_SEQP_SEQ_EVT,
  AL_SEQP_BANK_EVT,
  AL_SEQP_PLAY_EVT,
  AL_SEQP_STOP_EVT,
  AL_SEQP_STOPPING_EVT,
  AL_TRACK_END,
  AL_CSP_LOOPSTART,
  AL_CSP_LOOPEND,
  AL_CSP_NOTEOFF_EVT,
  AL_TREM_OSC_EVT,
  AL_VIB_OSC_EVT
};
enum AL_MIDIstatus
{
  AL_MIDI_ChannelMask = 0x0F,
  AL_MIDI_StatusMask = 0xF0,
  AL_MIDI_ChannelVoice = 0x80,
  AL_MIDI_NoteOff = 0x80,
  AL_MIDI_NoteOn = 0x90,
  AL_MIDI_PolyKeyPressure = 0xA0,
  AL_MIDI_ControlChange = 0xB0,
  AL_MIDI_ChannelModeSelect = 0xB0,
  AL_MIDI_ProgramChange = 0xC0,
  AL_MIDI_ChannelPressure = 0xD0,
  AL_MIDI_PitchBendChange = 0xE0,
  AL_MIDI_SysEx = 0xF0,
  AL_MIDI_SystemCommon = 0xF1,
  AL_MIDI_TimeCodeQuarterFrame = 0xF1,
  AL_MIDI_SongPositionPointer = 0xF2,
  AL_MIDI_SongSelect = 0xF3,
  AL_MIDI_Undefined1 = 0xF4,
  AL_MIDI_Undefined2 = 0xF5,
  AL_MIDI_TuneRequest = 0xF6,
  AL_MIDI_EOX = 0xF7,
  AL_MIDI_SystemRealTime = 0xF8,
  AL_MIDI_TimingClock = 0xF8,
  AL_MIDI_Undefined3 = 0xF9,
  AL_MIDI_Start = 0xFA,
  AL_MIDI_Continue = 0xFB,
  AL_MIDI_Stop = 0xFC,
  AL_MIDI_Undefined4 = 0xFD,
  AL_MIDI_ActiveSensing = 0xFE,
  AL_MIDI_SystemReset = 0xFF,
  AL_MIDI_Meta = 0xFF
};
enum AL_MIDIctrl
{
  AL_MIDI_VOLUME_CTRL = 0x07,
  AL_MIDI_PAN_CTRL = 0x0A,
  AL_MIDI_PRIORITY_CTRL = 0x10,
  AL_MIDI_FX_CTRL_0 = 0x14,
  AL_MIDI_FX_CTRL_1 = 0x15,
  AL_MIDI_FX_CTRL_2 = 0x16,
  AL_MIDI_FX_CTRL_3 = 0x17,
  AL_MIDI_FX_CTRL_4 = 0x18,
  AL_MIDI_FX_CTRL_5 = 0x19,
  AL_MIDI_FX_CTRL_6 = 0x1A,
  AL_MIDI_FX_CTRL_7 = 0x1B,
  AL_MIDI_FX_CTRL_8 = 0x1C,
  AL_MIDI_FX_CTRL_9 = 0x1D,
  AL_MIDI_SUSTAIN_CTRL = 0x40,
  AL_MIDI_FX1_CTRL = 0x5B,
  AL_MIDI_FX3_CTRL = 0x5D
};
enum AL_MIDImeta
{
  AL_MIDI_META_TEMPO = 0x51,
  AL_MIDI_META_EOT = 0x2f
};
typedef struct 
{
  u8 *curPtr;
  s32 lastTicks;
  s32 curTicks;
  s16 lastStatus;
} ALSeqMarker;
typedef struct 
{
  s32 ticks;
  u8 status;
  u8 byte1;
  u8 byte2;
  u32 duration;
} ALMIDIEvent;
typedef struct 
{
  s32 ticks;
  u8 status;
  u8 type;
  u8 len;
  u8 byte1;
  u8 byte2;
  u8 byte3;
} ALTempoEvent;
typedef struct 
{
  s32 ticks;
  u8 status;
  u8 type;
  u8 len;
} ALEndEvent;
typedef struct 
{
  struct ALVoice_s *voice;
} ALNoteEvent;
typedef struct 
{
  struct ALVoice_s *voice;
  ALMicroTime delta;
  u8 vol;
} ALVolumeEvent;
typedef struct 
{
  s16 vol;
} ALSeqpVolEvent;
typedef struct 
{
  ALSeqMarker *start;
  ALSeqMarker *end;
  s32 count;
} ALSeqpLoopEvent;
typedef struct 
{
  u8 chan;
  u8 priority;
} ALSeqpPriorityEvent;
typedef struct 
{
  void *seq;
} ALSeqpSeqEvent;
typedef struct 
{
  ALBank *bank;
} ALSeqpBankEvent;
typedef struct 
{
  struct ALVoiceState_s *vs;
  void *oscState;
  u8 chan;
} ALOscEvent;
typedef struct 
{
  s16 type;
  union 
  {
    ALMIDIEvent midi;
    ALTempoEvent tempo;
    ALEndEvent end;
    ALNoteEvent note;
    ALVolumeEvent vol;
    ALSeqpLoopEvent loop;
    ALSeqpVolEvent spvol;
    ALSeqpPriorityEvent sppriority;
    ALSeqpSeqEvent spseq;
    ALSeqpBankEvent spbank;
    ALOscEvent osc;
  } msg;
} ALEvent;
typedef struct 
{
  ALLink node;
  ALMicroTime delta;
  ALEvent evt;
} ALEventListItem;
typedef struct 
{
  ALLink freeList;
  ALLink allocList;
  s32 eventCount;
} ALEventQueue;
void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount);
ALMicroTime alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt);
void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta);
void alEvtqFlush(ALEventQueue *evtq);
void alEvtqFlushType(ALEventQueue *evtq, s16 type);
typedef struct ALVoiceState_s
{
  struct ALVoiceState_s *next;
  ALVoice voice;
  ALSound *sound;
  ALMicroTime envEndTime;
  f32 pitch;
  f32 vibrato;
  u8 envGain;
  u8 channel;
  u8 key;
  u8 velocity;
  u8 envPhase;
  u8 phase;
  u8 tremelo;
  u8 flags;
} ALVoiceState;
typedef struct 
{
  ALInstrument *instrument;
  s16 bendRange;
  ALFxId fxId;
  ALPan pan;
  u8 priority;
  u8 vol;
  u8 fxmix;
  u8 sustain;
  f32 pitchBend;
} ALChanState;
typedef struct ALSeq_s
{
  u8 *base;
  u8 *trackStart;
  u8 *curPtr;
  s32 lastTicks;
  s32 len;
  f32 qnpt;
  s16 division;
  s16 lastStatus;
} ALSeq;
typedef struct 
{
  u32 trackOffset[16];
  u32 division;
} ALCMidiHdr;
typedef struct ALCSeq_s
{
  ALCMidiHdr *base;
  u32 validTracks;
  f32 qnpt;
  u32 lastTicks;
  u32 lastDeltaTicks;
  u32 deltaFlag;
  u8 *curLoc[16];
  u8 *curBUPtr[16];
  u8 curBULen[16];
  u8 lastStatus[16];
  u32 evtDeltaTicks[16];
} ALCSeq;
typedef struct 
{
  u32 validTracks;
  s32 lastTicks;
  u32 lastDeltaTicks;
  u8 *curLoc[16];
  u8 *curBUPtr[16];
  u8 curBULen[16];
  u8 lastStatus[16];
  u32 evtDeltaTicks[16];
} ALCSeqMarker;
typedef struct 
{
  s32 maxVoices;
  s32 maxEvents;
  u8 maxChannels;
  u8 debugFlags;
  ALHeap *heap;
  void *initOsc;
  void *updateOsc;
  void *stopOsc;
} ALSeqpConfig;
typedef ALMicroTime (*ALOscInit)(void **oscState, f32 *initVal, u8 oscType, u8 oscRate, u8 oscDepth, u8 oscDelay);
typedef ALMicroTime (*ALOscUpdate)(void *oscState, f32 *updateVal);
typedef void (*ALOscStop)(void *oscState);
typedef struct 
{
  ALPlayer node;
  ALSynth *drvr;
  ALSeq *target;
  ALMicroTime curTime;
  ALBank *bank;
  s32 uspt;
  s32 nextDelta;
  s32 state;
  u16 chanMask;
  s16 vol;
  u8 maxChannels;
  u8 debugFlags;
  ALEvent nextEvent;
  ALEventQueue evtq;
  ALMicroTime frameTime;
  ALChanState *chanState;
  ALVoiceState *vAllocHead;
  ALVoiceState *vAllocTail;
  ALVoiceState *vFreeList;
  ALOscInit initOsc;
  ALOscUpdate updateOsc;
  ALOscStop stopOsc;
  ALSeqMarker *loopStart;
  ALSeqMarker *loopEnd;
  s32 loopCount;
} ALSeqPlayer;
typedef struct 
{
  ALPlayer node;
  ALSynth *drvr;
  ALCSeq *target;
  ALMicroTime curTime;
  ALBank *bank;
  s32 uspt;
  s32 nextDelta;
  s32 state;
  u16 chanMask;
  s16 vol;
  u8 maxChannels;
  u8 debugFlags;
  ALEvent nextEvent;
  ALEventQueue evtq;
  ALMicroTime frameTime;
  ALChanState *chanState;
  ALVoiceState *vAllocHead;
  ALVoiceState *vAllocTail;
  ALVoiceState *vFreeList;
  ALOscInit initOsc;
  ALOscUpdate updateOsc;
  ALOscStop stopOsc;
} ALCSPlayer;
void alSeqNew(ALSeq *seq, u8 *ptr, s32 len);
void alSeqNextEvent(ALSeq *seq, ALEvent *event);
s32 alSeqGetTicks(ALSeq *seq);
f32 alSeqTicksToSec(ALSeq *seq, s32 ticks, u32 tempo);
u32 alSeqSecToTicks(ALSeq *seq, f32 sec, u32 tempo);
void alSeqNewMarker(ALSeq *seq, ALSeqMarker *m, u32 ticks);
void alSeqSetLoc(ALSeq *seq, ALSeqMarker *marker);
void alSeqGetLoc(ALSeq *seq, ALSeqMarker *marker);
void alCSeqNew(ALCSeq *seq, u8 *ptr);
void alCSeqNextEvent(ALCSeq *seq, ALEvent *evt);
s32 alCSeqGetTicks(ALCSeq *seq);
f32 alCSeqTicksToSec(ALCSeq *seq, s32 ticks, u32 tempo);
u32 alCSeqSecToTicks(ALCSeq *seq, f32 sec, u32 tempo);
void alCSeqNewMarker(ALCSeq *seq, ALCSeqMarker *m, u32 ticks);
void alCSeqSetLoc(ALCSeq *seq, ALCSeqMarker *marker);
void alCSeqGetLoc(ALCSeq *seq, ALCSeqMarker *marker);
f32 alCents2Ratio(s32 cents);
void alSeqpNew(ALSeqPlayer *seqp, ALSeqpConfig *config);
void alSeqpDelete(ALSeqPlayer *seqp);
void alSeqpSetSeq(ALSeqPlayer *seqp, ALSeq *seq);
ALSeq *alSeqpGetSeq(ALSeqPlayer *seqp);
void alSeqpPlay(ALSeqPlayer *seqp);
void alSeqpStop(ALSeqPlayer *seqp);
s32 alSeqpGetState(ALSeqPlayer *seqp);
void alSeqpSetBank(ALSeqPlayer *seqp, ALBank *b);
void alSeqpSetTempo(ALSeqPlayer *seqp, s32 tempo);
s32 alSeqpGetTempo(ALSeqPlayer *seqp);
s16 alSeqpGetVol(ALSeqPlayer *seqp);
void alSeqpSetVol(ALSeqPlayer *seqp, s16 vol);
void alSeqpLoop(ALSeqPlayer *seqp, ALSeqMarker *start, ALSeqMarker *end, s32 count);
void alSeqpSetChlProgram(ALSeqPlayer *seqp, u8 chan, u8 prog);
s32 alSeqpGetChlProgram(ALSeqPlayer *seqp, u8 chan);
void alSeqpSetChlFXMix(ALSeqPlayer *seqp, u8 chan, u8 fxmix);
u8 alSeqpGetChlFXMix(ALSeqPlayer *seqp, u8 chan);
void alSeqpSetChlVol(ALSeqPlayer *seqp, u8 chan, u8 vol);
u8 alSeqpGetChlVol(ALSeqPlayer *seqp, u8 chan);
void alSeqpSetChlPan(ALSeqPlayer *seqp, u8 chan, ALPan pan);
ALPan alSeqpGetChlPan(ALSeqPlayer *seqp, u8 chan);
void alSeqpSetChlPriority(ALSeqPlayer *seqp, u8 chan, u8 priority);
u8 alSeqpGetChlPriority(ALSeqPlayer *seqp, u8 chan);
void alSeqpSendMidi(ALSeqPlayer *seqp, s32 ticks, u8 status, u8 byte1, u8 byte2);
void alCSPNew(ALCSPlayer *seqp, ALSeqpConfig *config);
void alCSPDelete(ALCSPlayer *seqp);
void alCSPSetSeq(ALCSPlayer *seqp, ALCSeq *seq);
ALCSeq *alCSPGetSeq(ALCSPlayer *seqp);
void alCSPPlay(ALCSPlayer *seqp);
void alCSPStop(ALCSPlayer *seqp);
s32 alCSPGetState(ALCSPlayer *seqp);
void alCSPSetBank(ALCSPlayer *seqp, ALBank *b);
void alCSPSetTempo(ALCSPlayer *seqp, s32 tempo);
s32 alCSPGetTempo(ALCSPlayer *seqp);
s16 alCSPGetVol(ALCSPlayer *seqp);
void alCSPSetVol(ALCSPlayer *seqp, s16 vol);
void alCSPSetChlProgram(ALCSPlayer *seqp, u8 chan, u8 prog);
s32 alCSPGetChlProgram(ALCSPlayer *seqp, u8 chan);
void alCSPSetChlFXMix(ALCSPlayer *seqp, u8 chan, u8 fxmix);
u8 alCSPGetChlFXMix(ALCSPlayer *seqp, u8 chan);
void alCSPSetChlPan(ALCSPlayer *seqp, u8 chan, ALPan pan);
ALPan alCSPGetChlPan(ALCSPlayer *seqp, u8 chan);
void alCSPSetChlVol(ALCSPlayer *seqp, u8 chan, u8 vol);
u8 alCSPGetChlVol(ALCSPlayer *seqp, u8 chan);
void alCSPSetChlPriority(ALCSPlayer *seqp, u8 chan, u8 priority);
u8 alCSPGetChlPriority(ALCSPlayer *seqp, u8 chan);
void alCSPSendMidi(ALCSPlayer *seqp, s32 ticks, u8 status, u8 byte1, u8 byte2);
typedef struct 
{
  s32 maxSounds;
  s32 maxEvents;
  ALHeap *heap;
} ALSndpConfig;
typedef struct 
{
  ALPlayer node;
  ALEventQueue evtq;
  ALEvent nextEvent;
  ALSynth *drvr;
  s32 target;
  void *sndState;
  s32 maxSounds;
  ALMicroTime frameTime;
  ALMicroTime nextDelta;
  ALMicroTime curTime;
} ALSndPlayer;
typedef s16 ALSndId;
void alSndpNew(ALSndPlayer *sndp, ALSndpConfig *c);
void alSndpDelete(ALSndPlayer *sndp);
ALSndId alSndpAllocate(ALSndPlayer *sndp, ALSound *sound);
void alSndpDeallocate(ALSndPlayer *sndp, ALSndId id);
void alSndpSetSound(ALSndPlayer *sndp, ALSndId id);
ALSndId alSndpGetSound(ALSndPlayer *sndp);
void alSndpPlay(ALSndPlayer *sndp);
void alSndpPlayAt(ALSndPlayer *sndp, ALMicroTime delta);
void alSndpStop(ALSndPlayer *sndp);
void alSndpSetVol(ALSndPlayer *sndp, s16 vol);
void alSndpSetPitch(ALSndPlayer *sndp, f32 pitch);
void alSndpSetPan(ALSndPlayer *sndp, ALPan pan);
void alSndpSetPriority(ALSndPlayer *sndp, ALSndId id, u8 priority);
void alSndpSetFXMix(ALSndPlayer *sndp, u8 mix);
s32 alSndpGetState(ALSndPlayer *sndp);
typedef struct 
{
  unsigned char *base;
  int fmt;
  int siz;
  int xsize;
  int ysize;
  int lsize;
  int addr;
  int w;
  int h;
  int s;
  int t;
} Image;
typedef struct 
{
  float col[3];
  float pos[3];
  float a1;
  float a2;
} PositionalLight;
extern int guLoadTextureBlockMipMap(Gfx **glist, unsigned char *tbuf, Image *im, unsigned char startTile, unsigned char pal, unsigned char cms, unsigned char cmt, unsigned char masks, unsigned char maskt, unsigned char shifts, unsigned char shiftt, unsigned char cfs, unsigned char cft);
extern int guGetDPLoadTextureTileSz(int ult, int lrt);
extern void guDPLoadTextureTile(Gfx *glistp, void *timg, int texl_fmt, int texl_size, int img_width, int img_height, int uls, int ult, int lrs, int lrt, int palette, int cms, int cmt, int masks, int maskt, int shifts, int shiftt);
extern void guMtxIdent(Mtx *m);
extern void guMtxIdentF(float mf[4][4]);
extern void guOrtho(Mtx *m, float l, float r, float b, float t, float n, float f, float scale);
extern void guOrthoF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale);
extern void guFrustum(Mtx *m, float l, float r, float b, float t, float n, float f, float scale);
extern void guFrustumF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale);
extern void guPerspective(Mtx *m, u16 *perspNorm, float fovy, float aspect, float near, float far, float scale);
extern void guPerspectiveF(float mf[4][4], u16 *perspNorm, float fovy, float aspect, float near, float far, float scale);
extern void guLookAt(Mtx *m, float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp);
extern void guLookAtF(float mf[4][4], float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp);
extern void guLookAtReflect(Mtx *m, LookAt *l, float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp);
extern void guLookAtReflectF(float mf[4][4], LookAt *l, float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp);
extern void guLookAtHilite(Mtx *m, LookAt *l, Hilite *h, float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp, float xl1, float yl1, float zl1, float xl2, float yl2, float zl2, int twidth, int theight);
extern void guLookAtHiliteF(float mf[4][4], LookAt *l, Hilite *h, float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp, float xl1, float yl1, float zl1, float xl2, float yl2, float zl2, int twidth, int theight);
extern void guLookAtStereo(Mtx *m, float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp, float eyedist);
extern void guLookAtStereoF(float mf[4][4], float xEye, float yEye, float zEye, float xAt, float yAt, float zAt, float xUp, float yUp, float zUp, float eyedist);
extern void guRotate(Mtx *m, float a, float x, float y, float z);
extern void guRotateF(float mf[4][4], float a, float x, float y, float z);
extern void guRotateRPY(Mtx *m, float r, float p, float y);
extern void guRotateRPYF(float mf[4][4], float r, float p, float h);
extern void guAlign(Mtx *m, float a, float x, float y, float z);
extern void guAlignF(float mf[4][4], float a, float x, float y, float z);
extern void guScale(Mtx *m, float x, float y, float z);
extern void guScaleF(float mf[4][4], float x, float y, float z);
extern void guTranslate(Mtx *m, float x, float y, float z);
extern void guTranslateF(float mf[4][4], float x, float y, float z);
extern void guPosition(Mtx *m, float r, float p, float h, float s, float x, float y, float z);
extern void guPositionF(float mf[4][4], float r, float p, float h, float s, float x, float y, float z);
extern void guMtxF2L(float mf[4][4], Mtx *m);
extern void guMtxL2F(float mf[4][4], Mtx *m);
extern void guMtxCatF(float m[4][4], float n[4][4], float r[4][4]);
extern void guMtxCatL(Mtx *m, Mtx *n, Mtx *res);
extern void guMtxXFMF(float mf[4][4], float x, float y, float z, float *ox, float *oy, float *oz);
extern void guMtxXFML(Mtx *m, float x, float y, float z, float *ox, float *oy, float *oz);
extern void guNormalize(float *x, float *y, float *z);
void guPosLight(PositionalLight *pl, Light *l, float xOb, float yOb, float zOb);
void guPosLightHilite(PositionalLight *pl1, PositionalLight *pl2, Light *l1, Light *l2, LookAt *l, Hilite *h, float xEye, float yEye, float zEye, float xOb, float yOb, float zOb, float xUp, float yUp, float zUp, int twidth, int theight);
extern int guRandom(void);
extern float sinf(float angle);
extern float cosf(float angle);
extern signed short sins(unsigned short angle);
extern signed short coss(unsigned short angle);
extern float sqrtf(float value);
extern void guParseRdpDL(u64 *rdp_dl, u64 nbytes, u8 flags);
extern void guParseString(char *StringPointer, u64 nbytes);
extern void guBlinkRdpDL(u64 *rdp_dl_in, u64 nbytes_in, u64 *rdp_dl_out, u64 *nbytes_out, u32 x, u32 y, u32 radius, u8 red, u8 green, u8 blue, u8 flags);
extern void guParseGbiDL(u64 *gbi_dl, u32 nbytes, u8 flags);
extern void guDumpGbiDL(OSTask *tp, u8 flags);
typedef struct 
{
  int dataSize;
  int dlType;
  int flags;
  u32 paddr;
} guDLPrintCB;
void guSprite2DInit(uSprite *SpritePointer, void *SourceImagePointer, void *TlutPointer, int Stride, int SubImageWidth, int SubImageHeight, int SourceImageType, int SourceImageBitSize, int SourceImageOffsetS, int SourceImageOffsetT);
typedef struct 
{
  long type;
  long length;
  long magic;
  char userdata[(4096 * 6) - (3 * (sizeof(long)))];
} RamRomBuffer;
struct bitmap
{
  s16 width;
  s16 width_img;
  s16 s;
  s16 t;
  void *buf;
  s16 actualHeight;
  s16 LUToffset;
};
typedef struct bitmap Bitmap;
struct sprite
{
  s16 x;
  s16 y;
  s16 width;
  s16 height;
  f32 scalex;
  f32 scaley;
  s16 expx;
  s16 expy;
  u16 attr;
  s16 zdepth;
  u8 red;
  u8 green;
  u8 blue;
  u8 alpha;
  s16 startTLUT;
  s16 nTLUT;
  int *LUT;
  s16 istart;
  s16 istep;
  s16 nbitmaps;
  s16 ndisplist;
  s16 bmheight;
  s16 bmHreal;
  u8 bmfmt;
  u8 bmsiz;
  Bitmap *bitmap;
  Gfx *rsp_dl;
  Gfx *rsp_dl_next;
  s16 frac_s;
  s16 frac_t;
};
typedef struct sprite Sprite;
void spSetAttribute(Sprite *sp, s32 attr);
void spClearAttribute(Sprite *sp, s32 attr);
void spX2Move(Sprite *sp, s32 x, s32 y);
void spScale(Sprite *sp, f32 sx, f32 sy);
void spX2SetZ(Sprite *sp, s32 z);
void spColor(Sprite *sp, u8 red, u8 green, u8 blue, u8 alpha);
Gfx *spX2Draw(Sprite *sp);
void spX2Init(Gfx **glistp);
void spX2Scissor(s32 xmin, s32 xmax, s32 ymin, s32 ymax);
void spX2Finish(Gfx **glistp);
extern long long int rspbootTextStart[];
extern long long int rspbootTextEnd[];
extern long long int gspFast3DTextStart[];
extern long long int gspFast3DTextEnd[];
extern long long int gspFast3DDataStart[];
extern long long int gspFast3DDataEnd[];
extern long long int gspFast3D_dramTextStart[];
extern long long int gspFast3D_dramTextEnd[];
extern long long int gspFast3D_dramDataStart[];
extern long long int gspFast3D_dramDataEnd[];
extern long long int gspFast3D_fifoTextStart[];
extern long long int gspFast3D_fifoTextEnd[];
extern long long int gspFast3D_fifoDataStart[];
extern long long int gspFast3D_fifoDataEnd[];
extern long long int gspF3DNoNTextStart[];
extern long long int gspF3DNoNTextEnd[];
extern long long int gspF3DNoNDataStart[];
extern long long int gspF3DNoNDataEnd[];
extern long long int gspF3DNoN_dramTextStart[];
extern long long int gspF3DNoN_dramTextEnd[];
extern long long int gspF3DNoN_dramDataStart[];
extern long long int gspF3DNoN_dramDataEnd[];
extern long long int gspF3DNoN_fifoTextStart[];
extern long long int gspF3DNoN_fifoTextEnd[];
extern long long int gspF3DNoN_fifoDataStart[];
extern long long int gspF3DNoN_fifoDataEnd[];
extern long long int gspLine3DTextStart[];
extern long long int gspLine3DTextEnd[];
extern long long int gspLine3DDataStart[];
extern long long int gspLine3DDataEnd[];
extern long long int gspLine3D_dramTextStart[];
extern long long int gspLine3D_dramTextEnd[];
extern long long int gspLine3D_dramDataStart[];
extern long long int gspLine3D_dramDataEnd[];
extern long long int gspLine3D_fifoTextStart[];
extern long long int gspLine3D_fifoTextEnd[];
extern long long int gspLine3D_fifoDataStart[];
extern long long int gspLine3D_fifoDataEnd[];
extern long long int gspSprite2DTextStart[];
extern long long int gspSprite2DTextEnd[];
extern long long int gspSprite2DDataStart[];
extern long long int gspSprite2DDataEnd[];
extern long long int gspSprite2D_dramTextStart[];
extern long long int gspSprite2D_dramTextEnd[];
extern long long int gspSprite2D_dramDataStart[];
extern long long int gspSprite2D_dramDataEnd[];
extern long long int gspSprite2D_fifoTextStart[];
extern long long int gspSprite2D_fifoTextEnd[];
extern long long int gspSprite2D_fifoDataStart[];
extern long long int gspSprite2D_fifoDataEnd[];
extern long long int aspMainTextStart[];
extern long long int aspMainTextEnd[];
extern long long int aspMainDataStart[];
extern long long int aspMainDataEnd[];
extern long long int gspF3DEX_fifoTextStart[];
extern long long int gspF3DEX_fifoTextEnd[];
extern long long int gspF3DEX_fifoDataStart[];
extern long long int gspF3DEX_fifoDataEnd[];
extern long long int gspF3DEX_NoN_fifoTextStart[];
extern long long int gspF3DEX_NoN_fifoTextEnd[];
extern long long int gspF3DEX_NoN_fifoDataStart[];
extern long long int gspF3DEX_NoN_fifoDataEnd[];
extern long long int gspF3DLX_fifoTextStart[];
extern long long int gspF3DLX_fifoTextEnd[];
extern long long int gspF3DLX_fifoDataStart[];
extern long long int gspF3DLX_fifoDataEnd[];
extern long long int gspF3DLX_NoN_fifoTextStart[];
extern long long int gspF3DLX_NoN_fifoTextEnd[];
extern long long int gspF3DLX_NoN_fifoDataStart[];
extern long long int gspF3DLX_NoN_fifoDataEnd[];
extern long long int gspF3DLX_Rej_fifoTextStart[];
extern long long int gspF3DLX_Rej_fifoTextEnd[];
extern long long int gspF3DLX_Rej_fifoDataStart[];
extern long long int gspF3DLX_Rej_fifoDataEnd[];
extern long long int gspF3DLP_Rej_fifoTextStart[];
extern long long int gspF3DLP_Rej_fifoTextEnd[];
extern long long int gspF3DLP_Rej_fifoDataStart[];
extern long long int gspF3DLP_Rej_fifoDataEnd[];
extern long long int gspL3DEX_fifoTextStart[];
extern long long int gspL3DEX_fifoTextEnd[];
extern long long int gspL3DEX_fifoDataStart[];
extern long long int gspL3DEX_fifoDataEnd[];
extern long long int gspF3DEX2_fifoTextStart[];
extern long long int gspF3DEX2_fifoTextEnd[];
extern long long int gspF3DEX2_fifoDataStart[];
extern long long int gspF3DEX2_fifoDataEnd[];
extern long long int gspF3DEX2_NoN_fifoTextStart[];
extern long long int gspF3DEX2_NoN_fifoTextEnd[];
extern long long int gspF3DEX2_NoN_fifoDataStart[];
extern long long int gspF3DEX2_NoN_fifoDataEnd[];
extern long long int gspF3DEX2_Rej_fifoTextStart[];
extern long long int gspF3DEX2_Rej_fifoTextEnd[];
extern long long int gspF3DEX2_Rej_fifoDataStart[];
extern long long int gspF3DEX2_Rej_fifoDataEnd[];
extern long long int gspF3DLX2_Rej_fifoTextStart[];
extern long long int gspF3DLX2_Rej_fifoTextEnd[];
extern long long int gspF3DLX2_Rej_fifoDataStart[];
extern long long int gspF3DLX2_Rej_fifoDataEnd[];
extern long long int gspL3DEX2_fifoTextStart[];
extern long long int gspL3DEX2_fifoTextEnd[];
extern long long int gspL3DEX2_fifoDataStart[];
extern long long int gspL3DEX2_fifoDataEnd[];
extern long long int gspF3DEX2_xbusTextStart[];
extern long long int gspF3DEX2_xbusTextEnd[];
extern long long int gspF3DEX2_xbusDataStart[];
extern long long int gspF3DEX2_xbusDataEnd[];
extern long long int gspF3DEX2_NoN_xbusTextStart[];
extern long long int gspF3DEX2_NoN_xbusTextEnd[];
extern long long int gspF3DEX2_NoN_xbusDataStart[];
extern long long int gspF3DEX2_NoN_xbusDataEnd[];
extern long long int gspF3DEX2_Rej_xbusTextStart[];
extern long long int gspF3DEX2_Rej_xbusTextEnd[];
extern long long int gspF3DEX2_Rej_xbusDataStart[];
extern long long int gspF3DEX2_Rej_xbusDataEnd[];
extern long long int gspF3DLX2_Rej_xbusTextStart[];
extern long long int gspF3DLX2_Rej_xbusTextEnd[];
extern long long int gspF3DLX2_Rej_xbusDataStart[];
extern long long int gspF3DLX2_Rej_xbusDataEnd[];
extern long long int gspL3DEX2_xbusTextStart[];
extern long long int gspL3DEX2_xbusTextEnd[];
extern long long int gspL3DEX2_xbusDataStart[];
extern long long int gspL3DEX2_xbusDataEnd[];
typedef void (*OSErrorHandler)(s16, s16, ...);
OSErrorHandler osSetErrorHandler(OSErrorHandler);
typedef struct 
{
  u32 magic;
  u32 len;
  u32 *base;
  s32 startCount;
  s32 writeOffset;
} OSLog;
typedef struct 
{
  u32 magic;
  u32 timeStamp;
  u16 argCount;
  u16 eventID;
} OSLogItem;
typedef struct 
{
  u32 magic;
  u32 version;
} OSLogFileHdr;
void osCreateLog(OSLog *log, u32 *base, s32 len);
void osLogEvent(OSLog *log, s16 code, s16 numArgs, ...);
void osFlushLog(OSLog *log);
u32 osLogFloat(f32);
extern void osDelay(int count);
struct Actor;
typedef struct ActorSub4
{
  u8 unk00[0x34];
  f32 unk34;
  f32 unk38;
  f32 unk3C;
} ActorSub4;
typedef struct ModelNode
{
  u8 pad0[0xC];
  f32 unkC;
  u8 pad10[0x14];
  u16 unk24;
  u8 unk26;
  u8 unk27;
  struct ModelNode *next;
} ModelNode;
typedef struct ModelSubNode
{
  u8 pad0[0x1C];
  struct ModelSubNode *next;
} ModelSubNode;
typedef struct ActorSub140
{
  s32 unk0;
  s32 unk4;
  s32 unk8;
  s32 unkC;
  s32 unk10;
  f32 unk14;
  f32 unk18;
  u8 pad1C[0x8];
  u8 unk24;
  u8 pad25[0x3B];
  s32 unk60;
  u8 pad64[4];
  s32 unk68;
  u8 unk6C;
  u8 pad6D[3];
  s32 unk70;
  s32 unk74;
  s32 unk78;
  s32 unk7C;
  s32 unk80;
  s32 unk84;
  s32 unk88;
  ModelNode *unk8C;
  ModelSubNode *unk90;
  s32 unk94;
  void *unk98;
  s32 unk9C;
  void *unkA0;
  s32 unkA4;
  s32 unkA8;
  u8 unkAC;
  u8 padAD[0x17];
} ActorSub140;
typedef struct ActorList
{
  s32 items[4];
  u8 count;
} ActorList;
typedef struct ActorCallbackNode
{
  void *callback;
  u8 unk4;
  u8 unk5[3];
  s32 unk8;
  s32 unkC;
  void *unk10;
  struct ActorCallbackNode *next;
  struct ActorCallbackNode *prev;
} ActorCallbackNode;
typedef struct ActorQueueEntry
{
  ActorCallbackNode *node;
  s32 arg0;
  s32 arg6;
} ActorQueueEntry;
typedef struct ActorEntry
{
  struct Actor *actor;
  s32 unk4;
} ActorEntry;
typedef struct ActorGlobalState
{
  u8 unk0;
  u8 unk1[1];
  u8 unk2;
  u8 unk3[0x12];
  u8 unk15;
  u8 unk16;
  u8 unk17;
  u8 unk18;
  u8 unk19;
  u8 unk1A;
  u8 unk1B;
  u8 unk1C;
  u8 unk1D[7];
  u8 unk24;
  u8 unk25;
  u8 unk26[6];
  u8 unk2C;
  u8 unk2D[0xB];
  u8 unk38;
  u8 unk39;
  u8 unk3A[0x56];
  u8 unk90;
  u8 unk91;
  u8 unk92[0x52];
  u8 unkE4;
  u8 unkE5;
  u8 unkE6[2];
  f32 unkE8;
  u8 unkEC[4];
  f32 unkF0;
  f32 unkF4;
  u8 unkF8[0x100];
  s32 unk1F8;
  s32 unk1FC;
  u8 unk200;
  u8 unk201;
  u8 unk202[2];
  s32 unk204[16];
  u8 unk244[16];
  u8 unk254;
  u8 unk255[3];
  s32 unk258[8];
  s16 *unk278[8];
} ActorGlobalState;
typedef struct Actor
{
  u8 unk00[4];
  ActorSub4 *unk4;
  u8 unk08[0x50];
  s32 unk58;
  u16 unk5C;
  u8 unk5E[2];
  u32 unk60;
  u32 unk64;
  u16 unk68;
  u16 unk6A;
  u16 unk6C;
  u8 unk6E[0xE];
  f32 unk7C;
  f32 unk80;
  f32 unk84;
  f32 unk88;
  f32 unk8C;
  f32 unk90;
  u8 unk94[8];
  f32 unk9C;
  f32 unkA0;
  f32 unkA4;
  u8 unkA8[4];
  f32 unkAC;
  u8 unkB0[8];
  f32 unkB8;
  f32 unkBC;
  u8 unkC0[0x26];
  s16 unkE6;
  u8 unkE8[0xC];
  s16 unkF4;
  s16 unkF6;
  u8 unkF8[4];
  u8 unkFC;
  u8 unkFD;
  u8 unkFE[0xE];
  s16 unk10C;
  u8 unk10E[2];
  u8 unk110;
  u8 unk111[3];
  ActorList *unk114;
  u8 unk118[4];
  s32 unk11C;
  u8 unk120[4];
  s32 unk124;
  s16 unk128;
  s16 unk12A;
  u8 unk12C[6];
  s16 unk132;
  u8 unk134[4];
  s32 unk138;
  ActorCallbackNode *unk13C;
  ActorSub140 *unk140;
  u8 unk144;
  u8 unk145[0xB];
  s32 unk150;
  u8 unk154;
  u8 unk155[7];
  s16 unk15C;
  u8 unk15E;
  u8 unk15F;
  u8 unk160[8];
  s16 unk168;
  u8 unk16A;
  u8 unk16B;
  u8 unk16C;
  u8 unk16D;
  u8 unk16E[6];
  void *unk174;
} Actor;
typedef struct Struct807FDC90
{
  u8 pad0[0xA];
  s16 unkA;
  s16 unkC;
  s16 unkE;
  u8 pad10[8];
  u16 unk18;
  u8 pad1A[0xE];
  u8 unk28[4];
  s16 unk2C;
  u8 pad2E[2];
  f32 unk30;
} Struct807FDC90;
typedef struct Struct807FDC98
{
  u8 pad0[0x46];
  u16 unk46;
} Struct807FDC98;
typedef struct Struct807FDC9C
{
  u8 pad0[6];
  s16 unk6;
  u8 pad8[2];
  u8 unkA;
  u8 unkB;
  u8 unkC;
  u8 padD[3];
  u8 unk10;
} Struct807FDC9C;
typedef struct Struct807FD580
{
  u8 pad0[0x1F0];
  s32 unk1F0;
} Struct807FD580;
extern Struct807FDC90 *D_807FDC90;
extern Actor *D_807FDC94;
extern Struct807FDC98 *D_807FDC98;
extern Struct807FDC9C *D_807FDC9C;
extern u8 D_807444FC;
extern u32 D_8076A064;
extern s32 D_8076A0A8;
extern Actor *D_807FBB4C;
void *func_80610FE8(s32);
u32 func_806119A0(void);
f32 func_806119FC(void);
s32 func_80611A44(void);
f32 func_80612790(s16);
f32 func_80612794(s16);
f32 func_80612D10(f32);
f32 func_80612D1C(f32);
typedef struct 
{
  u8 pad0[0x32C];
  u8 unk32C;
  u8 pad32D[0x13];
  f32 unk340;
  f32 unk344;
  f32 unk348;
  u8 pad34C[0x10];
  s32 unk35C;
  f32 unk360;
  f32 unk364;
  u8 pad368[0x1C];
  void *unk384;
} Ub1ActorView;
void func_80716F10(Ub1ActorView *arg0, void *arg1);
typedef struct 
{
  f32 unk0;
  f32 unk4;
} Ub1Rotation;
void func_80716FB4(Ub1ActorView *arg0, void *arg1);
void func_80714950(s32);
void func_80717404();
void func_8071498C(void *);
void func_807149B8(s32);
void func_80714CC0(s32, f32, f32, f32, f32);
extern s32 D_8074E880[];
void func_80717760(Ub1ActorView *arg0, u8 *arg1);
typedef struct 
{
  u8 pad0[0x330];
  void *unk330;
  u8 pad334[4];
  void *unk338;
  u8 pad33C[4];
  f32 unk340;
  f32 unk344;
  f32 unk348;
  s16 unk34C;
  u8 pad34E[2];
  u8 unk350;
  u8 pad351[0xB];
  s32 unk35C;
  f32 unk360;
  f32 unk364;
  u8 pad368[5];
  u8 unk36D;
  u8 pad36E[0x16];
  void *unk384;
} Ub2ActorView;
void func_80714998(s32);
void func_80718380();
extern u8 D_8071FEF4;
void func_80717CE8(arg0, arg1);
void func_80717D4C(arg0, arg1);
void func_80717D84(Ub2ActorView *arg0, s8 *arg1);
typedef struct 
{
  f32 unk0;
  f32 unk4;
  f32 unk8;
  f32 unkC;
} Ub2VelocityMotion;
void func_80718080(Ub2ActorView *arg0);
void func_807180F4(s32 arg0, s32 arg1);
void func_80718124(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
typedef f32 Ub2bMtxF[4][4];
void func_8071827C(Ub2ActorView *arg0, s8 *arg1);
void func_80718380(Ub2ActorView *arg0, s8 *arg1);
typedef struct 
{
  u8 pad0[0x16];
  s16 unk16;
} Ub5Timer;
typedef struct 
{
  u8 pad0[0x330];
  Ub5Timer *unk330;
  u8 pad334[0xC];
  f32 unk340;
  f32 unk344;
  f32 unk348;
  u8 pad34C[2];
  s16 unk34E;
  u8 pad34F[0xC];
  s32 unk35C;
} Ub5Actor;
void lightSetFlags(s32);
void lightAdd(f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32);
void func_8071A8B0(Ub5Actor *arg0, s8 *arg1);
void func_8071AADC(Ub5Actor *arg0, s8 *arg1);
void func_8071B758(Ub2ActorView *arg0, s8 *arg1);
void func_8071B89C(Ub2ActorView *arg0, s8 *arg1);
typedef struct 
{
  f32 unk0;
  f32 unk4;
  f32 unk8;
} Ub6Motion;
void func_8071BC80(Ub2ActorView *arg0, s8 *arg1);
void func_8071C620(Ub2ActorView *arg0, s8 *arg1);
void func_8071C818(Ub2ActorView *arg0, s8 *arg1);
void func_8071C914(Ub2ActorView *arg0, s8 *arg1);
void func_8071D260(Ub2ActorView *arg0, s8 *arg1);
void func_8071E028(Ub2ActorView *arg0, s8 *arg1);
typedef struct 
{
  f32 unk0;
  f32 unk4;
  f32 unk8;
  f32 unkC;
  f32 unk10;
  f32 unk14;
} Ub7E110Motion;
void func_8071E110(Ub2ActorView *arg0, u8 arg1, u16 arg2, f32 arg3, f32 arg4, s32 arg5);
void func_8071EEA4(Ub2ActorView *arg0, s32 arg1);
typedef struct 
{
  u8 unk0[0x330];
  void *unk330;
  u8 unk334[4];
  void *unk338;
  u8 unk33C[4];
  f32 unk340;
  f32 unk344;
  f32 unk348;
  s16 unk34C;
  u8 unk34E[2];
  u8 unk350;
  u8 unk351[0xB];
  s32 unk35C;
  f32 unk360;
  f32 unk364;
  u8 unk368[5];
  u8 unk36D;
} Ud1dActorView;
void func_8071EFDC(Ud1dActorView *arg0, s8 *arg1)
{
  s32 temp_t7;
  arg0->unk360 = (f32) (((f64) arg0->unk360) * 1.05);
  arg0->unk364 = (f32) ((((f64) arg0->unk364) * 1.05) * 1.0);
  temp_t7 = (arg0->unk36D = (arg0->unk36D & 0xFFu) - 5);
  if ((temp_t7 & 0xFF) < 6)
  {
    *arg1 = 1;
  }
}

typedef struct 
{
  u8 unk0[0x7C];
  f32 unk7C;
  f32 unk80;
  f32 unk84;
} Ud1dPositionSource;
void func_8071F034(Ub2ActorView *arg0, s32 arg1);
typedef struct 
{
  f32 unk0;
  f32 unk4;
  f32 unk8;
  f32 unkC;
} Ud1MotionState;
typedef struct 
{
  u8 unk0[4];
  f32 *unk4;
} Ud1ScaleRoot;
typedef struct 
{
  u8 unk0[0x38];
  f32 unk38;
} Ud1ScaleSource;
typedef struct 
{
  u8 unk0[0x338];
  Ud1ScaleRoot *unk338;
  u8 unk33C[4];
  f32 unk340;
  f32 unk344;
  f32 unk348;
  u8 unk34C[2];
  s16 unk34E;
  u8 unk350;
  u8 unk351[3];
  s32 unk354;
  s32 unk358;
  s32 unk35C;
  f32 unk360;
  f32 unk364;
  u8 unk368[0x1C];
  Ud1MotionState *unk384;
} Ud1ActorView;
void func_8071F2F8(Ud1ActorView *arg0, s32 arg1);
void func_8071F3C0(Ud1ActorView *arg0, s32 arg1);
typedef struct 
{
  u8 unk0[0x32C];
  u8 unk32C;
  u8 unk32D[0xB];
  u8 unk338[0x1C];
  s32 unk354;
  s32 unk358;
  u8 unk35C[4];
  f32 unk360;
  f32 unk364;
} Ud1F660ActorView;
void func_80612CA0(f32 (*arg0)[4], f32 arg1);
void func_8071F660(Ud1F660ActorView *arg0, void *arg1);
