# ZSA Voyager to ZMK Porting Analysis

**Source**: ZSA Voyager 52-key keyboard
**Target**: 34-key Urchin/Ferris Sweep variant
**Firmware**: QMK → ZMK

## Summary

Analysis of porting a ZSA Voyager keyboard configuration to ZMK on a 34-key split keyboard. The main challenge is mouse functionality - many advanced features used in the source firmware don't have ZMK equivalents.

---

## Critical Mouse Functionality Issues

### Advanced Mouse Features - NOT SUPPORTED in ZMK

**Layer 6** uses several custom mouse features that have **no ZMK equivalents**:

| Feature | Location | Description | ZMK Status |
|---------|----------|-------------|------------|
| `DRAG_SCROLL` | keymap.c:525-531 | Temporarily enables scroll mode while held | ❌ Not supported |
| `TOGGLE_SCROLL` | keymap.c:532-536 | Toggles persistent scroll mode | ❌ Not supported |
| `NAVIGATOR_INC_CPI` | keymap.c:552-561 | Dynamic CPI increase | ❌ Not supported |
| `NAVIGATOR_DEC_CPI` | keymap.c:552-561 | Dynamic CPI decrease | ❌ Not supported |
| `NAVIGATOR_TURBO` | keymap.c:538-551 | Speed boost mode | ❌ Not supported |
| `NAVIGATOR_AIM` | keymap.c:538-551 | Precision aim mode | ❌ Not supported |
| Hi-res scrolling | config.h:8-9 | `POINTING_DEVICE_HIRES_SCROLL_ENABLE` | ❌ Not supported |
| Cursor glide | config.h:10 | `POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE` | ❌ Not supported |
| Extended reports | config.h:11 | `MOUSE_EXTENDED_REPORT` | ❌ Not supported |

**ZMK Status**: ZMK has basic mouse key support but it's experimental and lacks these advanced features. No pointing device support exists for scroll toggling or CPI changes.

### Basic Mouse Keys - LIMITED SUPPORT

**Layer 5** (keymap.c:72-78) uses standard mouse keys:

- **Movement**: `KC_MS_LEFT`, `KC_MS_DOWN`, `KC_MS_UP`, `KC_MS_RIGHT`
- **Wheel**: `KC_MS_WH_LEFT`, `KC_MS_WH_DOWN`, `KC_MS_WH_UP`, `KC_MS_WH_RIGHT`
- **Buttons**: `KC_MS_BTN1`, `KC_MS_BTN2`, `KC_MS_BTN3`
- **Acceleration**: `KC_MS_ACCEL0`, `KC_MS_ACCEL1`, `KC_MS_ACCEL2`

**ZMK Equivalent**: Requires enabling `CONFIG_ZMK_MOUSE` (experimental). Mouse acceleration modes may not work identically.

### Mouse Keys with Modifiers

keymap.c:491-506 has special handling to ensure modifiers apply correctly to mouse keys across different OS.

**ZMK Issue**: This level of custom processing isn't available in ZMK's mouse implementation.

---

## Other Porting Challenges

### Tap Dance - COMPLEX WORKAROUND NEEDED

7 tap dances defined (DANCE_0 through DANCE_6):

| Tap Dance | Location | Single Tap | Double Tap/Hold | Notes |
|-----------|----------|------------|-----------------|-------|
| DANCE_0 | keymap.c:243-271 | `[` | `]` | Simple bracket dance |
| DANCE_1 | keymap.c:276-306 | `6` | `MS_BTN1` | Mouse button integration |
| DANCE_2 | keymap.c:311-339 | `7` | `MS_BTN3` | Mouse button integration |
| DANCE_3 | keymap.c:344-372 | `8` | `MS_BTN2` | Mouse button integration |
| DANCE_4 | keymap.c:377-411 | `I` | Layer 6 on double-hold | Layer switching |
| DANCE_5 | keymap.c:416-444 | Play/Pause | Next Track | Media controls |
| DANCE_6 | keymap.c:449-477 | Stop | Previous Track | Media controls |

**ZMK Workaround**: Use tap-dance behavior, but ZMK's tap-dance is more limited than QMK. The mouse button integration in tap-dances will be particularly tricky.

### Combos - GOOD SUPPORT

11 combos defined (keymap.c:89-113):

| Keys | Action | Purpose |
|------|--------|---------|
| Y+U | Backspace | Common typing flow |
| F5+F6 | TO(2) | Layer switch |
| Q+P | TO(0) | Return to base |
| X+Y | TO(3) | Gaming layer |
| R+T | Tab | Quick access |
| F+G | Escape | Quick access |
| H+J | Enter | Home row combo |
| H+J | Delete | Alternative action |
| V+B | TT(5) | Toggle mouse layer |

**ZMK Support**: ✅ Excellent support, should port directly.

### Homerow Mods - EXCELLENT SUPPORT

Multiple `MT()` modifier-tap keys throughout:
- `MT(MOD_LSFT, KC_A)` - Left shift on hold, A on tap
- `MT(MOD_LCTL, KC_S)` - Left control on hold, S on tap
- `MT(MOD_LALT, KC_D)` - Left alt on hold, D on tap
- Similar pattern on right hand (K, L, SCLN)

**ZMK Support**: ✅ Excellent support via `&mt` behavior. Well-tested and reliable.

### RGB Lighting

Extensive RGB configuration:
- Per-layer LED maps (keymap.c:129-201)
- 52 LEDs defined per layer
- Custom HSV color definitions

**ZMK Support**: ⚠️ Depends on your board. Most Ferris Sweep builds don't have RGB. If yours does, ZMK's underglow support is more basic than QMK's per-key RGB matrix.

### MAC_SIRI Custom Keycode

keymap.c:507-508 sends consumer HID code for Siri (`HCS(0xCF)`)

**ZMK Equivalent**: Consumer keys are supported. Will need to find the correct ZMK binding for Siri.

---

## 34-Key Layer Extraction

**Layers 3 & 4** appear to be 34-key subset (gaming layers). Positions with `KC_NO` are the outer columns to drop:

### Layer 3 - Gaming Base Layer
```
Layer 3 (keymap.c:58-64): Gaming base layer
- Q W E R T | Y U I O P
- A S D F G | H J K L ;
- Z X C V B | N M , . /
```

### Layer 4 - Gaming Symbols/Nav Layer  
```
Layer 4 (keymap.c:65-71): Gaming symbols/nav layer
- 1 2 3 4 5 | 6 7 8 9 0
- Shift ` [ ] Tab | ← ↓ ↑ → Shift
- Alt - ' = \ | Esc Bspc Del Ctrl Alt
```

These layers avoid the number row and outer columns, making them suitable templates for 34-key extraction.

---

## Porting Recommendations

### 1. Mouse Functionality Strategy

Consider these options:

**Option A**: Sacrifice advanced mouse features
- Drop Layer 6 entirely (scroll toggle, CPI adjust, turbo/aim modes)
- Keep basic Layer 5 mouse keys if enabling experimental support
- Use combos or dedicated keys instead of tap-dance mouse buttons

**Option B**: Use separate pointing device
- Add trackball/trackpad with ZMK's input-listener module
- Better integration than basic mouse keys
- Requires hardware modification

**Option C**: Hybrid approach
- Use basic mouse keys for occasional cursor movement
- Primary mouse interaction via regular mouse/trackpad
- Fastest path to working firmware

### 2. Simplify Tap-Dances

The mouse button tap-dances (DANCE_1/2/3) need alternatives:

- **Replace with dedicated keys**: Put mouse buttons on Layer 5 directly
- **Use combos**: Define combos for mouse buttons (e.g., `6+7` → BTN1)
- **Accept key number on base layer**: Trade-off for simpler implementation

### 3. Start with Layer 3/4

These are already 34-key layouts - use as templates:

1. Copy Layer 3 as base layer
2. Copy Layer 4 as symbol/nav layer
3. Build up from there

### 4. Incremental Testing Order

Port features in this order:

1. ✅ **Basic layer with homerow mods** - Core functionality
2. ✅ **Combos** - Well-supported in ZMK
3. ⚠️ **Simplified tap-dances** - Media controls first, avoid mouse integration
4. ⚠️ **Basic mouse keys** - If needed, enable experimental support
5. ❌ **Abandon advanced mouse features** - Not feasible in ZMK

---

## Configuration Reference

### Key QMK Configuration (config.h)

```c
#define USB_SUSPEND_WAKEUP_DELAY 0
#define SERIAL_NUMBER "y4zgr/zL4pWj"
#define LAYER_STATE_8BIT
#define COMBO_COUNT 11

// Mouse/pointing device config (NOT SUPPORTED IN ZMK)
#define WHEEL_EXTENDED_SUPPORT
#define POINTING_DEVICE_HIRES_SCROLL_ENABLE
#define POINTING_DEVICE_HIRES_SCROLL_EXPONENT 1
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
#define MOUSE_EXTENDED_REPORT
#define NAVIGATOR_SCROLL_DIVIDER 50

#define RGB_MATRIX_STARTUP_SPD 60
```

### Custom Keycodes (keymap.c:8-20)

```c
enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
  MAC_SIRI,
  DRAG_SCROLL,          // ❌ Not in ZMK
  TOGGLE_SCROLL,        // ❌ Not in ZMK
  NAVIGATOR_INC_CPI,    // ❌ Not in ZMK
  NAVIGATOR_DEC_CPI,    // ❌ Not in ZMK
  NAVIGATOR_TURBO,      // ❌ Not in ZMK
  NAVIGATOR_AIM         // ❌ Not in ZMK
};
```

---

## Next Steps

1. Decide on mouse functionality approach (A, B, or C above)
2. Extract 34-key positions from desired layers
3. Create initial ZMK keymap with homerow mods
4. Add combos
5. Test and iterate
6. Add optional features (tap-dances, mouse) as needed

---

## Files Referenced

- `keymap.c` - Main keymap definition with 7 layers, tap dances, combos
- `config.h` - Hardware and feature configuration
- `keymap.json` - Module references (zsa/oryx, zsa/defaults)

**Date**: 2025-11-05
**Firmware Version**: y4zgr/zL4pWj
