#define USB_SUSPEND_WAKEUP_DELAY 0
#define SERIAL_NUMBER "y4zgr/zL4pWj"
#define LAYER_STATE_8BIT
#define COMBO_COUNT 10
#define HCS(report) host_consumer_send(record->event.pressed ? report : 0); return false

#define WHEEL_EXTENDED_SUPPORT
#define POINTING_DEVICE_HIRES_SCROLL_ENABLE
#define POINTING_DEVICE_HIRES_SCROLL_EXPONENT 1
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
#define MOUSE_EXTENDED_REPORT
#define NAVIGATOR_SCROLL_DIVIDER 50

#define RGB_MATRIX_STARTUP_SPD 60

// Homerow-mod tuning (custom; not exposed in Oryx)
// CHORDAL_HOLD: same-hand rolls stay as taps, opposite-hand triggers hold.
// Eliminates spurious mods on rolls like "as", "df", "kl", "l;" without
// PERMISSIVE_HOLD's tendency to fire holds on slow pinkies.
#define CHORDAL_HOLD
#define TAPPING_TERM 200
#define QUICK_TAP_TERM 0
#define TAPPING_TERM_PER_KEY

