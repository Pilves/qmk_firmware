#include <stdio.h>
#include QMK_KEYBOARD_H

// Custom keycodes for mod-morph brackets
enum custom_keycodes {
    KC_PAREN = SAFE_RANGE, // ( or ) with shift
    KC_BRACK,              // [ or ] with shift
    KC_CURLY,              // { or } with shift
};

// Custom keycodes for Estonian umlauts (Windows Alt codes)
enum umlaut_keycodes {
    EST_A = KC_CURLY + 1,  // ä (Alt+0228)
    EST_O,                  // õ (Alt+0245)
    EST_U,                  // ü (Alt+0252)
    EST_OE,                 // ö (Alt+0246)
};

#define INDICATOR_BRIGHTNESS 30
#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
    {0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
    {1, 6, hsv}, \
    {35+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
    {35+15, 5, hsv},\
    {35+22, 3, hsv},\
    {35+27, 3, hsv}
#define SET_NUMROW(hsv) \
    {10, 2, hsv}, \
    {20, 2, hsv}, \
    {30, 2, hsv}, \
    {35+ 10, 2, hsv}, \
    {35+ 20, 2, hsv}, \
    {35+ 30, 2, hsv}
#define SET_INNER_COL(hsv)    \
    {33, 4, hsv}, \
    {35+ 33, 4, hsv}
#define SET_OUTER_COL(hsv) \
    {7, 4, hsv}, \
    {35+ 7, 4, hsv}
#define SET_THUMB_CLUSTER(hsv)     \
    {25, 2, hsv}, \
    {35+ 25, 2, hsv}
#define SET_LAYER_ID(hsv)     \
    {0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {1, 6, hsv}, \
    {35+1, 6, hsv}, \
    {7, 4, hsv}, \
    {35+ 7, 4, hsv}, \
    {25, 2, hsv}, \
    {35+ 25, 2, hsv}

enum sofle_layers {
    _BASE = 0,
    _NAV,
    _SYMBOLS,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Layer 0: BASE (Graphite)
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  `  │  1  │  2  │  3  │  4  │  5  │             │  6  │  7  │  8  │  9  │  0  │BSPC │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │ TAB │  B  │  L  │  D  │  W  │  Z  │             │  '  │  F  │  O  │  U  │  J  │  -  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │ ESC │  N  │  R  │  T  │  S  │  G  │             │  Y  │  H  │  A  │  E  │  I  │  =  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │SHIFT│  Q  │  X  │  M  │  C  │  V  │MUTE │ │PLAY │  K  │  P  │  ,  │  .  │  /  │SHIFT│
 * └─────┴─────┴─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┴─────┴─────┘
 *                   │ GUI │CTRL │ NAV │SPACE│ │BSPC │ SYM │ ENT │ ALT │
 *                   └─────┴─────┴─────┴─────┘ └─────┴─────┴─────┴─────┘
 */
[_BASE] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_B,    KC_L,    KC_D,    KC_W,    KC_Z,                          KC_QUOT, KC_F,    KC_O,    KC_U,    KC_J,    KC_MINS,
    KC_ESC,  KC_N,    KC_R,    KC_T,    KC_S,    KC_G,                          KC_Y,    KC_H,    KC_A,    KC_E,    KC_I,    KC_EQL,
    KC_LSFT, KC_Q,    KC_X,    KC_M,    KC_C,    KC_V,    KC_MUTE,     KC_MPLY, KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                      KC_LGUI, KC_LCTL, MO(_NAV),KC_SPC,  XXXXXXX,     XXXXXXX, KC_BSPC, MO(_SYMBOLS), KC_ENT, KC_LALT
),

/* Layer 1: NAV (Navigate)
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  `  │  1  │  2  │  3  │  4  │  5  │             │  6  │  7  │  8  │  9  │  0  │BSPC │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │ TAB │ F1  │ F2  │ F3  │ F4  │ F5  │             │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │ ESC │sk(G)│sk(A)│sk(C)│sk(S)│HOME │             │PgUp │  ←  │  ↓  │  ↑  │  →  │ F12 │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │SHIFT│UNDO │ CUT │COPY │PASTE│ END │     │ │     │PgDn │HOME │     │ END │ INS │SHIFT│
 * └─────┴─────┴─────┴─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┴─────┴─────┘
 *                   │     │     │     │     │ │ DEL │ ADJ │     │     │
 *                   └─────┴─────┴─────┴─────┘ └─────┴─────┴─────┴─────┘
 */
[_NAV] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    KC_ESC,  OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), KC_HOME, KC_PGUP, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_F12,
    KC_LSFT, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), KC_END,  _______,     _______, KC_PGDN, KC_HOME, XXXXXXX, KC_END,  KC_INS,  KC_RSFT,
                      _______, _______, _______, _______, XXXXXXX,     XXXXXXX, KC_DEL,  MO(_ADJUST), _______, _______
),

/* Layer 2: SYMBOLS
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  `  │  1  │  2  │  3  │  4  │  5  │             │  6  │  7  │  8  │  9  │  0  │BSPC │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │ TAB │  !  │  @  │  #  │  $  │  %  │             │  ^  │  &  │  *  │  (  │  )  │  \  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │ ESC │  ?  │ ( ) │ [ ] │ { } │  ~  │             │  |  │  -  │  =  │  [  │  ]  │  `  │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │SHIFT│  +  │  <  │  >  │  _  │  :  │     │ │     │  ;  │  "  │  '  │  {  │  }  │SHIFT│
 * └─────┴─────┴─────┴─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┴─────┴─────┘
 *                   │     │     │ ADJ │     │ │     │     │     │     │
 *                   └─────┴─────┴─────┴─────┘ └─────┴─────┴─────┴─────┘
 */
[_SYMBOLS] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS,
    KC_ESC,  KC_QUES, KC_PAREN,KC_BRACK,KC_CURLY,KC_TILD,                       KC_PIPE, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_GRV,
    KC_LSFT, KC_PLUS, KC_LT,   KC_GT,   KC_UNDS, KC_COLN, _______,     _______, KC_SCLN, KC_DQUO, KC_QUOT, KC_LCBR, KC_RCBR, KC_RSFT,
                      _______, _______, MO(_ADJUST), _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______
),

/* Layer 3: ADJUST
 * ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
 * │  `  │  1  │  2  │  3  │  4  │  5  │             │  6  │  7  │  8  │  9  │  0  │BSPC │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │     │     │     │     │     │             │     │  ä  │  õ  │  ü  │  ö  │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │     │     │BRI+ │BRI- │     │             │     │PREV │VOL- │VOL+ │NEXT │     │
 * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
 * │     │     │     │     │     │     │     │ │     │     │MUTE │PLAY │STOP │     │BOOT │
 * └─────┴─────┴─────┴─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┴─────┴─────┘
 *                   │     │     │     │     │ │     │     │     │     │
 *                   └─────┴─────┴─────┴─────┘ └─────┴─────┴─────┴─────┘
 */
[_ADJUST] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, EST_A,   EST_O,   EST_U,   EST_OE,  XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIU, KC_BRID, XXXXXXX,                       XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,     _______, XXXXXXX, KC_MUTE, KC_MPLY, KC_MSTP, XXXXXXX, QK_BOOT,
                      _______, _______, _______, _______, XXXXXXX,     XXXXXXX, _______, _______, _______, _______
),
};

#ifdef RGBLIGHT_ENABLE
// Layer lighting definitions
const rgblight_segment_t PROGMEM base_layer_rgb[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PURPLE));
const rgblight_segment_t PROGMEM nav_layer_rgb[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_BLUE), SET_INNER_COL(HSV_AZURE));
const rgblight_segment_t PROGMEM symbol_layer_rgb[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PINK), SET_NUMPAD(HSV_CORAL));
const rgblight_segment_t PROGMEM adjust_layer_rgb[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_RED), SET_NUMROW(HSV_RED));

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = {
    base_layer_rgb, nav_layer_rgb, symbol_layer_rgb, adjust_layer_rgb
};

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(2, layer_state_cmp(state, _SYMBOLS));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    return state;
}
#endif

#ifdef OLED_ENABLE
static const char PROGMEM legends[][2][4][6] = {
    // BASE - Graphite layout
    {{"12345","BLDWZ","NRTSG","QXMCV"}, {"67890","'FOUJ","YHAEI","KP,./"}},
    // NAV - F-keys, sticky mods, arrows
    {{"12345","F1-F5","MODS ","EDITS"}, {"67890","F6-11","ARROW","PgNav"}},
    // SYMBOLS - shifted numbers + brackets
    {{"12345","!@#$%","?(){}","+ < >"}, {"67890","^&*()","|-=-`","; \" '"}},
    // ADJUST - umlauts, media
    {{"12345","     ","BRI  ","     "}, {"67890","aouoe","MEDIA","BOOT "}}
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

static void render_status(void) {
    uint8_t current_layer = get_highest_layer(layer_state);
    switch (current_layer) {
        case _BASE:     oled_write_P(PSTR("GRAPH\n"), false); break;
        case _NAV:      oled_write_P(PSTR("NAV  \n"), false); break;
        case _SYMBOLS:  oled_write_P(PSTR("SYMB \n"), false); break;
        case _ADJUST:   oled_write_P(PSTR("ADJST\n"), false); break;
        default:        oled_write_P(PSTR("UNDEF\n"), false); break;
    }
    oled_write_P(PSTR("\n"), false);
    for (int row = 0; row < 4; row++) {
        oled_write_P(legends[current_layer][0][row], false);
        oled_write_P(PSTR("\n"), false);
    }
}

static void render_status_secondary(void) {
    uint8_t current_layer = get_highest_layer(layer_state);
    switch (current_layer) {
        case _BASE:     oled_write_P(PSTR("GRAPH\n"), false); break;
        case _NAV:      oled_write_P(PSTR("NAV  \n"), false); break;
        case _SYMBOLS:  oled_write_P(PSTR("SYMB \n"), false); break;
        case _ADJUST:   oled_write_P(PSTR("ADJST\n"), false); break;
        default:        oled_write_P(PSTR("UNDEF\n"), false); break;
    }
    oled_write_P(PSTR("\n"), false);
    for (int row = 0; row < 4; row++) {
        oled_write_P(legends[current_layer][1][row], false);
        oled_write_P(PSTR("\n"), false);
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) { render_status(); } else { render_status_secondary(); }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Mod-morph brackets: tap = open, shift+tap = close
        case KC_PAREN:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_code16(KC_RPRN);
                    set_mods(get_mods());
                } else {
                    tap_code16(KC_LPRN);
                }
            }
            return false;
        case KC_BRACK:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_code(KC_RBRC);
                    set_mods(get_mods());
                } else {
                    tap_code(KC_LBRC);
                }
            }
            return false;
        case KC_CURLY:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_code16(KC_RCBR);
                    set_mods(get_mods());
                } else {
                    tap_code16(KC_LCBR);
                }
            }
            return false;
        // Estonian umlauts via Windows Alt codes (numpad)
        case EST_A:  // ä = Alt+0228
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_8)));
            }
            return false;
        case EST_O:  // õ = Alt+0245
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_5)));
            }
            return false;
        case EST_U:  // ü = Alt+0252
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_KP_2)));
            }
            return false;
        case EST_OE: // ö = Alt+0246
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_6)));
            }
            return false;
        default:
            return true;
    }
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t current_layer = get_highest_layer(layer_state);

    if (index == 0) {  // Left encoder
        switch (current_layer) {
            case _NAV:
                // Previous/Next Track
                if (clockwise) { tap_code(KC_MNXT); } else { tap_code(KC_MPRV); }
                break;
            default:
                // Volume Down/Up
                if (clockwise) { tap_code(KC_VOLU); } else { tap_code(KC_VOLD); }
                break;
        }
    } else if (index == 1) {  // Right encoder
        switch (current_layer) {
            case _NAV:
                // Brightness Down/Up
                if (clockwise) { tap_code(KC_BRIU); } else { tap_code(KC_BRID); }
                break;
            default:
                // Page Up/Down
                if (clockwise) { tap_code(KC_PGDN); } else { tap_code(KC_PGUP); }
                break;
        }
    }
    return false;
}
#endif
