# Keyboard notes

Personal reference for the keyboards I own and the recurring gotchas
when fixing them. Imported from `aaronrea/one-liners:keyboards.tar.gz`
plus session lessons.

## Boards

| Board | Firmware | Repo |
|---|---|---|
| ZSA Voyager (+ trackball) | QMK (ZSA fork) | this one |
| Drop ALT v2 | QMK (mainline + custom keymap) | [aaronrea/drop-alt-v2](https://github.com/aaronrea/drop-alt-v2) |
| Urchin (34-key split) | ZMK | [aaronrea/urchin-zmk-firmware](https://github.com/aaronrea/urchin-zmk-firmware) |

## Notes in this directory

- **[Voyager Layer Maps - 34 Key Extract.md](./Voyager%20Layer%20Maps%20-%2034%20Key%20Extract.md)** — Voyager full layout with 34-key center extracts.
- **[Urchin vs Voyager Comparison.md](./Urchin%20vs%20Voyager%20Comparison.md)** — Side-by-side keymap diff between the two.
- **[Hybrid Keymap Guide.md](./Hybrid%20Keymap%20Guide.md)** — Combined Urchin/Voyager keymap design.
- **[ZSA Voyager to ZMK Porting Analysis.md](./ZSA%20Voyager%20to%20ZMK%20Porting%20Analysis.md)** — What QMK features have no ZMK equivalent (mouse stuff: drag scroll, CPI control, navigator turbo).
- **[Drop ALT v2.md](./Drop%20ALT%20v2.md)** — Quick reference for the Drop ALT.

---

## Voyager build pipeline (this repo)

The whole point of this repo is: edit in Oryx → fetch latest layout → merge with custom QMK source → CI build → flash.

### Triggering a build
```
gh workflow run fetch-and-build-layout.yml \
  --repo aaronrea/oryx-with-custom-qmk \
  -f layout_id=y4zgr \
  -f layout_geometry=voyager \
  -f qmk_branch=feat/trackball_default_cpi
```

Then download the artifact:
```
gh run download <run-id> --repo aaronrea/oryx-with-custom-qmk
```

### QMK branch matters — pick based on accessory

| Accessory | QMK branch | Why |
|---|---|---|
| Trackball (current) | `feat/trackball_default_cpi` | `firmware*` branches dropped `navigator_trackball.c` |
| None / vanilla | `firmware25` (or latest) | Standard release branch |
| Trackpad (future) | `firmware25`+ with `navigator_trackpad` | New WIP driver; different chip (Cirque Gen6) |

### Flashing

| Tool | When |
|---|---|
| **Wally** (GUI) | Easiest. Drag `.bin` in, press reset on underside of left half. |
| **Keymapp** | ZSA's newer GUI, same flow. |
| `wally-cli <file>.bin` | CLI alternative. |

Reset = paperclip in the small hole on the **underside of the left half**. Both halves auto-reboot after flash.

---

## Homerow mod tuning (the real lesson from this session)

Oryx exposes `TAPPING_TERM` and sometimes per-key tapping terms in its UI. Everything else is source-only. The classic GACS layout (`A=Sft, S=Ctl, D=Alt, K=Alt, L=Ctl, ;=Sft`) needs careful tuning or you get spurious mods on rolls.

### What worked (final state)
```c
#define CHORDAL_HOLD          // same-hand rolls = tap, opposite-hand = hold
#define TAPPING_TERM 200
#define QUICK_TAP_TERM 0
#define TAPPING_TERM_PER_KEY  // pinkies +40ms, ring +20ms in get_tapping_term()
```
Plus a `chordal_hold_handedness()` function in keymap.c (cols 0–5 = L, 6–11 = R, thumbs = `*`).

### What didn't work
- `PERMISSIVE_HOLD` + `HOLD_ON_OTHER_KEY_PRESS` together → S and L stuck because permissive hold fires the mod as soon as another key is pressed-and-released inside the tapping term. Pinky-rolls (`as`, `kl`, `l;`) are exactly that pattern.

### Reference
- QMK tap-hold docs: https://docs.qmk.fm/tap_hold
- ZSA blog on Achordion (similar concept): https://blog.zsa.io/oryx-custom-qmk-features/
- Precondition's classic article: https://precondition.github.io/home-row-mods

---

## Common gotchas

1. **Workflow expects an `oryx` branch.** First-time setup of the fork: create `oryx` from `main`, otherwise `actions/checkout` fails.
2. **Submodule shallow-fetch.** When pulling a non-`firmware*` QMK branch, use explicit refspec `+refs/heads/$BRANCH:refs/remotes/origin/$BRANCH` so the remote-tracking ref is created.
3. **Oryx fetches stomp `oryx` branch only.** Custom changes go on `main`. The merge step preserves them via `-Xignore-all-space`.
4. **Combos are global, not per-layer.** Use `COMBO_ONLY_FROM_LAYER` if you need to scope.
5. **Tap dances on letters/numbers cost typing latency.** Every press waits `TAPPING_TERM` to disambiguate. Avoid on vowels and frequently-typed digits.
