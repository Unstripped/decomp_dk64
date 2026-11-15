# menuHandleHighScoreNameEntryInput (menu, src/menu/3E10.c)
## Sites
menu:8002EF68:other:8f795c other: the comma assignment places the hold-frame store in the target schedule.
menu:8002EF68:dead-if:a43a4a dead-if: repeated column reads retain the column-address candidate and its colour.
menu:8002EF68:dead-if:6fbc84 dead-if: first `row == 0xF` extends the row/constant web; base key 969b12.
menu:8002EF68:dead-if:6fbc84#2 dead-if: second row test completes the same lifetime constraint; base key 969b12#2.
menu:8002EF68:other:0b7fb5 other: base key 085a79. A typed `MenuHighScoreEntry *entry` role local retires the byte-pointer cast; the split `entry = table; entry += row;` is a codegen-chosen respelling of `&table[row]` and stays tagged (lead ruling, Q0816 precedent).
## Attempts
- Previous rounds: direct `&table[row].initial0`, indexed variants, individual/coupled steer removal, uopt traces and long permutes all failed (see supplied history).
- 2026-11-15 HackmenuHandleHighScoreNameEntryInput openai-codex/gpt-5.6-sol:high: `entry = table; entry += row; p = &entry->initial0 + D_80033F61` -> whole-file fdiff exit 0; at merge, `entry = &table[row]`, `entry = table + row`, `p = &table[row].initial0 + D_80033F61` each 10 rows.
- 2026-11-15 HackmenuHandleHighScoreNameEntryInput openai-codex/gpt-5.6-sol:high: switch/fallthrough hold handling, named column locals, parity switch, and coupled remaining-steer removal -> no match.
## Untried ideas
None in natural C after direct/indexed/compound pointer forms, coupled lifetime rewrites, switch forms, and declaration variants.
## Evidence
- Target row address at text 0x72e4 requires the target operand order; direct typed indexing reverses that `addu` pair.
- Splitting the typed cursor update into assignment plus compound addition preserves the target `sll/subu` scale and `addu` operand order (base-first); the single-expression forms reverse it.
- The two row-test keys change because their expression now reuses the role-named `row`; deleting either still changes allocation (Q0469/Q0502).
- Relevant guidance: Q0282, Q0469, Q0502, Q0602, Q0604, Q0813.
