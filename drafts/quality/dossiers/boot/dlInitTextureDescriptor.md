# dlInitTextureDescriptor (boot, src/boot/6690.c)
## Sites
- boot:80005A90:proto-steer:dceeba: the K&R definition. Classified as the original form (proposal: untag).
## Attempts
- round 25 (opus:low): ANSI s16/u8/u16/s32 definitions; consolidate.
- 2026-11-14 U HackdlInitTextureDescriptor:
  - owner, 128 ANSI width combinations: only the exact K&R types match, and those compile identically to K&R
  - arcade/0.c stand-ins:
    - s16 prototype: +32 bytes
    - u8, u16, s32 prototypes: OK
  - so no single prototype fits both objects
## Evidence
- owner:
  - sw a3,12(sp) home; sh a3,8(a0)
  - lh 18/22(sp), lbu 27/31(sp), lh 34/38(sp): low halves/bytes of promoted words
- arcade arcadeRunFrame call at 0x1d0c:
  - lbu s0 (D_8004C719) at 0x1cc8
  - move a3,s0 at 0x1d04 and sw s0,16(sp) at 0x1d08, with no narrowing
