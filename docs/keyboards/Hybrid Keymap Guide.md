# Hybrid Keymap Guide

Created hybrid keymap combining best features from Urchin ZMK and Voyager QMK.

**File**: `urchin-zmk-firmware/config/urchin-hybrid.keymap`

---

## What's New in Hybrid

### Added from Voyager

#### 1. Four Essential Combos
| Keys | Action | Purpose |
|------|--------|---------|
| **Y + U** | Backspace | Most useful - natural typing flow |
| **R + T** | Tab | Quick access without leaving home row area |
| **F + G** | Escape | Quick escape from home row |
| **H + J** | Enter | Right hand enter combo |

#### 2. Symbols Layer (Layer 2)
New layer with Voyager-style symbols:
```
!    @    #    $    %         ^    &    *    -    =
~    `    {    }    |         ←    ↓    ↑    →    PgUp
⌥    _    (    )    \         ESC  BSPC DEL  ⌃    PgDn
               TG2  _              _    _
```

Access by toggling Layer 1 (tap the EXT thumb twice).

#### 3. Layout Adjustments
- Right pinky `L` changed to **CTRL** (was SHIFT) - matches Voyager
- Layer 1 now uses `'` and `\` instead of `~` and `|` - matches Voyager Layer 4

---

## Layer Breakdown

### Layer 0 - BASE (QWERTY + Homerow Mods)

```
     Q    W    E    R    T         Y    U    I    O    P
     A/⇧  S/⌃  D/⌥  F    G         H    J    K/⌥  L/⌃  ;/⇧
     Z    X    C    V    B         N    M    ,    .    /
               MO1  SPC/⌘              SPC/⌘ ↵
```

**Combos active**:
- Y+U → Backspace
- R+T → Tab
- F+G → Escape
- H+J → Enter

**Thumb behavior**:
- Hold left thumb → Access Layer 1 momentarily
- Tap left thumb → Toggle Layer 1 persistent
- Tap right thumb → Space
- Hold right thumb → Command/GUI modifier

---

### Layer 1 - EXT (Numbers, Brackets, Navigation)

```
     1    2    3    4    5         6    7    8    9    0
     ⇧    `    [    ]    ⇥         ←    ↓    ↑    →    ⇧
     ⌥    -/⌃  '    =    \         ESC  BSPC DEL  ⌃    ⌥
               _    _                   _    _
```

**Usage**:
- Numbers on home row
- Brackets for coding
- Vim-style arrows on right hand
- Editing keys (ESC, BSPC, DEL) on right lower

**Getting here**:
- Hold left thumb from base
- Or tap left thumb to lock

---

### Layer 2 - SYM (Symbols, Voyager-style)

```
     !    @    #    $    %         ^    &    *    -    =
     ~    `    {    }    |         ←    ↓    ↑    →    PgUp
     ⌥    _    (    )    \         ESC  BSPC DEL  ⌃    PgDn
               TG2  _                   _    _
```

**Usage**:
- Shifted symbols (!@#$%^&*)
- Braces for coding {}, ()
- All symbols in one layer

**Getting here**:
- From Layer 1, tap the layer thumb again to toggle to Layer 2
- Or uncomment the V+B combo in keymap to toggle directly

---

### Layer 3 - SETTINGS (Bluetooth, Bootloader)

```
BTLDR _    _    BTCLR BT0         BT3  _    UNSTK _    BTLDR
_     _    _    _     BT1         BT4  _    _     _    _
STDUNL _   _    _     BT2         BT5  _    _     _    STDUNL
                      _    _           _    _
```

**Usage**:
- Bluetooth pairing (BT0-BT5 = 6 devices)
- Clear Bluetooth (BTCLR)
- Enter bootloader mode for flashing
- Unstick macro for stuck modifiers
- Studio unlock for ZMK Studio

**Getting here**:
- Press both left thumb keys simultaneously

---

## Key Differences from Original Urchin

| Feature | Original Urchin | Hybrid |
|---------|----------------|--------|
| Combos | 1 (settings only) | 5 (settings + 4 typing) |
| Layers | 2 + settings | 3 + settings |
| Right pinky `L` | SHIFT mod-tap | CTRL mod-tap |
| Layer 1 symbols | ~, \| | ', \ |
| Symbol layer | No | Yes (Layer 2) |

---

## Key Differences from Voyager

| Feature | Voyager (QMK) | Hybrid (ZMK) |
|---------|---------------|--------------|
| Layers | 7 layers | 4 layers |
| Mouse support | Full (Layers 5-6) | None (ZMK limitation) |
| Tap dances | 7 dances | None (can add later) |
| RGB | Per-key LED matrix | None (Urchin has display) |
| Power | USB powered | Battery + sleep |
| Key count | 52 keys | 34 keys |

---

## Usage Tips

### Quick Access Patterns

**Common typing flow**:
- Type normally on base layer
- Y+U for backspace without leaving flow
- R+T for tab
- F+G for escape

**Coding flow**:
- Hold left thumb for Layer 1 (numbers + brackets)
- Use [ ] for arrays
- Use ' for strings
- Release thumb to return to base

**Heavy symbol work**:
- Tap left thumb twice to lock Layer 2
- Access all symbols (!@#$%^&*{})
- Tap Layer 2 thumb again to exit

**Settings**:
- Press both left thumbs together
- Select Bluetooth device or bootloader

### Combo Timing

All typing combos use 50ms timeout (fast).
Settings combo uses 200ms timeout (deliberate).

If combos feel too sensitive or not sensitive enough:
- Adjust `timeout-ms` in the combo definitions
- Lower = faster/more sensitive
- Higher = slower/more deliberate

---

## Optional Modifications

### Add Bracket Tap-Dance

If you miss the Voyager bracket tap-dance (single tap `[`, double tap `]`):

Add to behaviors section:
```c
td_brackets: tap_dance_brackets {
    compatible = "zmk,behavior-tap-dance";
    #binding-cells = <0>;
    tapping-term-ms = <200>;
    bindings = <&kp LBKT>, <&kp RBKT>;
};
```

Replace `&kp LEFT_BRACKET` in Layer 1 with `&td_brackets`.

### Add Media Controls

Add combos for media control:
```c
// J + K = Play/Pause
combo_play {
    timeout-ms = <50>;
    key-positions = <16 17>;
    bindings = <&kp C_PP>;
};

// K + L = Next track
combo_next {
    timeout-ms = <50>;
    key-positions = <17 18>;
    bindings = <&kp C_NEXT>;
};
```

### Enable V+B Symbol Layer Toggle

Uncomment in the combos section:
```c
combo_sym {
    timeout-ms = <50>;
    key-positions = <23 24>;
    bindings = <&tog SYM>;
};
```

---

## Building and Flashing

### Build with GitHub Actions

1. Edit `build.yaml` to use `urchin-hybrid.keymap`:
```yaml
include:
  - board: nice_nano_v2
    shield: urchin_left
    keymap: urchin-hybrid
  - board: nice_nano_v2
    shield: urchin_right
    keymap: urchin-hybrid
```

2. Commit and push to trigger build
3. Download firmware from Actions tab
4. Flash to keyboard halves

### Local Build

```bash
# In urchin-zmk-firmware directory
west build -b nice_nano_v2 -- -DSHIELD=urchin_left -DKEYMAP=urchin-hybrid
west build -b nice_nano_v2 -- -DSHIELD=urchin_right -DKEYMAP=urchin-hybrid
```

---

## Testing Checklist

After flashing:

- [ ] All letters work (QWERTY)
- [ ] Homerow mods work (A=shift, S=ctrl, D=alt)
- [ ] Y+U combo produces backspace
- [ ] R+T combo produces tab
- [ ] F+G combo produces escape
- [ ] H+J combo produces enter
- [ ] Left thumb accesses Layer 1 (numbers appear)
- [ ] Layer 1 has brackets and arrows
- [ ] Double-tap left thumb accesses Layer 2 (symbols)
- [ ] Both left thumbs access settings layer
- [ ] Settings layer can pair Bluetooth
- [ ] Unstick macro works if modifiers stuck

---

**Date**: 2025-11-05
**Version**: 1.0
**Status**: Ready to test
**File**: `config/urchin-hybrid.keymap`
