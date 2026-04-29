# Urchin vs Voyager Comparison

Comparison between your existing Urchin ZMK firmware and the ZSA Voyager QMK firmware.

---

## What's Already There ✅

Your Urchin firmware **already matches** your Voyager gaming layers (3/4) almost perfectly:

### Base Layer Comparison

**Urchin Base**:
```
Q    W    E    R    T         Y    U    I    O    P
A/⇧  S/⌃  D/⌥  F    G         H    J    K/⌥  L/⇧  ;/⇧
Z    X    C    V    B         N    M    ,    .    /
          MO1  SPC/⌘              SPC/⌘ ↵
```

**Voyager Layer 3** (Gaming Base):
```
Q    W    E    R    T         Y    U    I    O    P
A/⇧  S/⌃  D/⌥  F    G         H    J    K/⌥  L/⌃  ;/⇧
Z    X    C    V    B         N    M    ,    .    /
          TT4  SPC/⌘              SPC/⌘ ↵
```

**Differences**:
- Urchin right pinky: `L` has SHIFT mod-tap
- Voyager right pinky: `L` has CTRL mod-tap
- Thumb layer access: Similar behavior (MO1 vs TT4)

### Layer 1/Symbols Comparison

**Urchin Layer 1** (EXT):
```
1    2    3    4    5         6    7    8    9    0
⇧    `    [    ]    ⇥         ←    ↓    ↑    →    ⇧
⌥    -/⌃  ~    =    |         ESC  BSPC DEL  ⌃    ⌥
          _    _                   _    _
```

**Voyager Layer 4** (Gaming Symbols):
```
1    2    3    4    5         6    7    8    9    0
⇧    `    [    ]    ⇥         ←    ↓    ↑    →    ⇧
⌥    -/⌃  '    =    \         ESC  BSPC DEL  ⌃    ⌥
          _    SPC/⌘              SPC/⌘ ↵
```

**Differences**:
- Urchin: `~` (tilde) and `|` (pipe) on left hand
- Voyager: `'` (quote) and `\` (backslash) on left hand
- Urchin thumbs: transparent
- Voyager thumbs: keep Command/Space access

---

## What's Missing in Urchin ⚠️

### 1. Combos (10 missing)

Voyager has 11 combos, Urchin only has 1 (thumb combo for settings layer).

**Missing Combos from Voyager**:

| Keys | Action | Purpose | Priority |
|------|--------|---------|----------|
| Y + U | Backspace | Common typing flow | 🔴 HIGH |
| R + T | Tab | Quick access | 🟡 MEDIUM |
| F + G | Escape | Quick access | 🟡 MEDIUM |
| H + J | Enter | Home row combo | 🟡 MEDIUM |
| H + J (alt) | Delete | Alternative | 🟢 LOW |
| V + B | TT(5) - Mouse layer | Toggle mouse | 🟢 LOW (no mouse) |
| Q + P | TO(0) - Base | Return to base | 🟢 LOW |
| X + Y | TO(3) - Gaming | Gaming layer | 🟢 LOW |
| F5 + F6 | TO(2) - Config | Config layer | 🟢 LOW |

**Recommended to add**:
- ✅ Y+U → Backspace
- ✅ R+T → Tab
- ✅ F+G → Escape
- ✅ H+J → Enter

### 2. Tap Dances (7 missing, 4 can't port)

**Voyager Tap Dances**:

| ID | Single Tap | Double Tap/Hold | Can Port? |
|----|------------|-----------------|-----------|
| DANCE_0 | `[` | `]` | ✅ YES - useful brackets |
| DANCE_1 | `6` | `MS_BTN1` | ❌ NO - mouse button |
| DANCE_2 | `7` | `MS_BTN3` | ❌ NO - mouse button |
| DANCE_3 | `8` | `MS_BTN2` | ❌ NO - mouse button |
| DANCE_4 | `I` | Layer 6 hold | ❌ NO - nav layer |
| DANCE_5 | Play/Pause | Next Track | ✅ YES - media control |
| DANCE_6 | Stop | Prev Track | ✅ YES - media control |

**Recommendation**: 
- Add DANCE_0 (bracket tap-dance) if you use it frequently
- Add DANCE_5/6 (media controls) if you control music from keyboard
- Skip mouse-related tap-dances (can't port)

### 3. Mouse Layers (Layers 5 & 6) ❌

**Cannot port** - ZMK experimental mouse support doesn't include:
- Mouse movement keys (KC_MS_LEFT/DOWN/UP/RIGHT)
- Mouse wheel (KC_MS_WH_*)
- Mouse buttons in tap-dances
- CPI adjustment
- Scroll toggle modes
- Acceleration modes

### 4. Additional Layers from Voyager

**Voyager Layer 0** (Main QWERTY with more keys):
```
ESC  1    2    3    4    5         6    7    8    9    0    -
TAB  Q    W    E    R    T         Y    U    I    O    P    \
`    A/⇧  S/⌃  D/⌥  F    G         H    J    K/⌥  L/⌃  ;/⇧  '
[    Z    X    C    V    B         N    M    ,    .    /    ↵
          TT1  SPC/⌘                    SPC/⌘ TT1
```

Has number row and more symbols. Can adapt to 34-key by moving to combos/layers.

**Voyager Layer 1** (Symbols & Nav):
```
ESC  F1   F2   F3   F4   F5        F6   F7   F8   F9   F10  F11
`    !    @    #    $    %         ^    &    *    -    =    /
DEL  _    _    2/⌥← _    VOL+      ←    ↓    ↑    →    PgUp BSPC
←W   →W   `⌘   ⇆⇥⌘  ⇥⌘   VOL-      ⏯    ⏹    ⇆⇥⌃  ⇥⌃   PgDn ↵
          _    _                        BTN1 _
```

Has more symbols (!@#$%^&*), function keys, and app/tab switching shortcuts.

**Voyager Layer 2** (Config/RGB):
Similar to Urchin settings layer - RGB controls, media, bootloader.

---

## What Urchin Has That Voyager Doesn't ✅

### Custom Behaviors

**`mo_tog`** (urchin.keymap:38-45):
- Hold: Momentary layer (like MO)
- Tap: Toggle layer (like TG)
- Very useful for layer access!

**`qt` (quick_tap)** (urchin.keymap:29-37):
- Custom hold-tap with 200ms timing
- Used for Command/Space thumb keys
- Enables tap-release-hold sequence

**`unstick` macro** (urchin.keymap:51-56):
- Fixes stuck modifiers
- Presses all modifiers to reset state
- Accessed from settings layer

### Configuration Features

**Deep Sleep** (urchin.conf:8-14):
- Saves battery by sleeping after 30 minutes
- Not in Voyager (USB powered)

**BT Power Boost** (urchin.conf:5):
- +8dBm transmit power
- Better Bluetooth range

**Display Support** (urchin.conf:24-28):
- Nice!View display configured
- Custom status screen
- Voyager uses RGB LEDs instead

---

## Recommended Hybrid Approach

### Keep from Urchin
✅ Current base layer (already similar to Voyager)
✅ `mo_tog` and `qt` behaviors (very useful)
✅ Settings layer structure
✅ Display and sleep config

### Add from Voyager
✅ Essential combos (Y+U=Bspc, R+T=Tab, F+G=Esc, H+J=Enter)
✅ Consider adding symbols layer with !@#$%^&*
✅ Consider adding bracket tap-dance if you use it
✅ Consider media control tap-dances

### Skip from Voyager
❌ Mouse layers (can't port to ZMK)
❌ Mouse button tap-dances
❌ RGB lighting (no LEDs on Urchin)
❌ Navigator features (CPI, scroll toggle, etc.)

---

## Key Differences to Remember

| Feature | Urchin | Voyager |
|---------|--------|---------|
| Right pinky homerow | L = SHIFT | L = CTRL |
| Symbols row 3 | ~, | (tilde, pipe) | ', \ (quote, backslash) |
| Thumb behavior | mo_tog (tap=toggle) | TT (tap toggle) |
| Combos | 1 combo | 11 combos |
| Layers | 3 layers | 7 layers |
| Mouse support | None | Full (Layers 5-6) |
| Power | Battery + sleep | USB powered |

---

**Date**: 2025-11-05
**Current Config**: urchin-zmk-firmware cloned from aaronrea/urchin-zmk-firmware
