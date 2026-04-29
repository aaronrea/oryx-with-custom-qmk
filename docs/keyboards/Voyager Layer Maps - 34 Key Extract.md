# Voyager Layer Maps - 34 Key Extract

Quick reference for extracting 34-key layouts from ZSA Voyager firmware.

---

## Layer 0 - Base QWERTY with Homerow Mods

**Full Voyager Layout** (52 keys):
```
ESC  1    2    3    4    5              6    7    8    9    0    -
TAB  Q    W    E    R    T              Y    U    I    O    P    \
`    A/⇧  S/⌃  D/⌥  F    G              H    J    K/⌥  L/⌃  ;/⇧  '
[    Z    X    C    V    B              N    M    ,    .    /    ↵
               TT1  SPC/⌘                     SPC/⌘ TT1
```

**34-Key Extract** (center positions only):
```
     Q    W    E    R    T         Y    U    I    O    P
     A/⇧  S/⌃  D/⌥  F    G         H    J    K/⌥  L/⌃  ;/⇧
     Z    X    C    V    B         N    M    ,    .    /
                    TT1  SPC/⌘          SPC/⌘ TT1
```

**Notes**:
- `⇧` = Shift mod-tap
- `⌃` = Control mod-tap  
- `⌥` = Alt mod-tap
- `⌘` = GUI/Command mod-tap
- TD keys (6, 7, 8, I) contain mouse button double-taps

---

## Layer 1 - Symbols & Navigation

**Full Voyager Layout**:
```
ESC  F1   F2   F3   F4   F5             F6   F7   F8   F9   F10  F11
`    !    @    #    $    %              ^    &    *    -    =    /
DEL  _    _    2/⌥← _    VOL+           ←    ↓    ↑    →    PgUp BSPC
←W   →W  `⌘   ⇆⇥⌘  ⇥⌘   VOL-           ⏯    ⏹    ⇆⇥⌃  ⇥⌃   PgDn ↵
               _    _                        BTN1 _
```

**34-Key Extract**:
```
     !    @    #    $    %         ^    &    *    -    =
     _    _    2/⌥← _    VOL+      ←    ↓    ↑    →    PgUp
     →W   `⌘   ⇆⇥⌘  ⇥⌘   VOL-      ⏯    ⏹    ⇆⇥⌃  ⇥⌃   PgDn
                    _    _              BTN1 _
```

**Notes**:
- `←W` / `→W` = Word left/right (Ctrl+arrows)
- `⇥⌘` / `⇆⇥⌘` = Cmd+Tab / Cmd+Shift+Tab (app switching)
- `⇥⌃` / `⇆⇥⌃` = Ctrl+Tab / Ctrl+Shift+Tab (tab switching)
- Layer includes mouse button (BTN1) on thumb

---

## Layer 3 - Gaming Base (Already 34-key!)

**Layout**:
```
.    Q    W    E    R    T         Y    U    I    O    P    .
.    A/⇧  S/⌃  D/⌥  F    G         H    J    K/⌥  L/⌃  ;/⇧  .
.    Z    X    C    V    B         N    M    ,    .    /    .
                    TT4  SPC/⌘          SPC/⌘ ↵
```

**34-Key Extract** (same as above, drop outer columns):
```
     Q    W    E    R    T         Y    U    I    O    P
     A/⇧  S/⌃  D/⌥  F    G         H    J    K/⌥  L/⌃  ;/⇧
     Z    X    C    V    B         N    M    ,    .    /
                    TT4  SPC/⌘          SPC/⌘ ↵
```

**Notes**:
- Pure gaming layer - no number row
- Same homerow mods as Layer 0
- Different thumb keys (TT4 instead of TT1, Enter instead of TT1)

---

## Layer 4 - Gaming Symbols (Already 34-key!)

**Layout**:
```
.    1    2    3    4    5         6    7    8    9    0    .
.    ⇧    `    [    ]    ⇥         ←    ↓    ↑    →    ⇧    .
.    ⌥    -/⌃  '    =    \         ESC  BSPC DEL  ⌃    ⌥    .
                    _    SPC/⌘          SPC/⌘ ↵
```

**34-Key Extract**:
```
     1    2    3    4    5         6    7    8    9    0
     ⇧    `    [    ]    ⇥         ←    ↓    ↑    →    ⇧
     ⌥    -/⌃  '    =    \         ESC  BSPC DEL  ⌃    ⌥
                    _    SPC/⌘          SPC/⌘ ↵
```

**Notes**:
- Number row on top
- Direct modifier access (not mod-tap) on home row outer positions
- Navigation arrows on right hand
- Editing keys (ESC, BSPC, DEL) easily accessible

---

## Layer 5 - Mouse Layer

**Full Voyager Layout**:
```
TO0  _    AC0  AC1  AC2  _              _    _    _    _    _    TO4
_    _    _    _    _    SIRI           WH←  WH↓  WH↑  WH→  _    _
_    _    _    _    _    _              MS←  MS↓  MS↑  MS→  _    _
_    _    _    _    _    _              _    _    _    _    _    _
               _    BTN1                     BTN2 BTN3
```

**34-Key Extract**:
```
     _    AC0  AC1  AC2  _         _    _    _    _    _
     _    _    _    _    _         WH←  WH↓  WH↑  WH→  _
     _    _    _    _    _         MS←  MS↓  MS↑  MS→  _
                    _    BTN1           BTN2 BTN3
```

**Notes**:
- `MS←/↓/↑/→` = Mouse cursor movement
- `WH←/↓/↑/→` = Mouse wheel scroll
- `AC0/1/2` = Mouse acceleration modes
- `BTN1/2/3` = Mouse buttons (left/right/middle)
- ⚠️ Mouse keys are experimental in ZMK

---

## Layer 6 - Navigator/Scroll Layer

**34-Key Extract**:
```
     _    _    _    BTN3 TGSCRL    TGSCRL BTN3 _    _    _
     _    _    BTN2 BTN1 DRGSCRL   DRGSCRL BTN1 BTN2 _    _
     _    _    _    _    _         _    TO0  _    _    _
                    _    _              _    _
```

**Notes**:
- `TGSCRL` = Toggle scroll mode ❌ Not in ZMK
- `DRGSCRL` = Drag scroll (hold) ❌ Not in ZMK
- Layer designed for trackball/pointing device
- ⚠️ This layer likely not portable to ZMK

---

## Combos

Key combos that work across layers:

| Left Keys | Right Keys | Action | Layer |
|-----------|------------|--------|-------|
| Y + U | | Backspace | 0 |
| F5 + F6 | | TO(2) - Config layer | 1 |
| Q + P | | TO(0) - Base layer | Any |
| X + Y | | TO(3) - Gaming layer | Any |
| R + T | | Tab | 0 |
| F + G | | Escape | 0 |
| H + J | | Enter | 0 |
| H + J | | Delete (alt) | 0 |
| V + B | | TT(5) - Mouse layer | 0 |

---

## ZMK Conversion Quick Ref

### Mod-Tap Conversions

| QMK | ZMK |
|-----|-----|
| `MT(MOD_LSFT, KC_A)` | `&mt LSHFT A` |
| `MT(MOD_LCTL, KC_S)` | `&mt LCTRL S` |
| `MT(MOD_LALT, KC_D)` | `&mt LALT D` |
| `MT(MOD_LGUI, KC_SPACE)` | `&mt LGUI SPACE` |

### Layer Tap Conversions

| QMK | ZMK |
|-----|-----|
| `LT(1, KC_X)` | `&lt 1 X` |
| `TT(1)` | `&tog 1` or custom behavior |

### Combo Definition Example

QMK:
```c
const uint16_t PROGMEM combo0[] = { KC_Y, KC_U, COMBO_END};
COMBO(combo0, KC_BSPC)
```

ZMK:
```
combo_bspc {
    timeout-ms = <50>;
    key-positions = <7 8>;  // Y and U positions
    bindings = <&kp BSPC>;
};
```

---

**Date**: 2025-11-05
**Source**: ZSA Voyager firmware y4zgr/zL4pWj
