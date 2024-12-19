// SOFLE RGB
#include <stdio.h>
#include QMK_KEYBOARD_H

// Custom keycodes
enum custom_keycodes {
    PAIR_PR = SAFE_RANGE, // ()
    PAIR_BR, // []
    PAIR_CB, // {}
    MY_SAVE,    // Ctrl+S
    MY_COPY,    // Ctrl+C
    MY_PASTE,   // Ctrl+V
    MY_CUT,     // Ctrl+X
    MY_UNDO,    // Ctrl+Z
    MY_FIND,    // Ctrl+F
    ALT_TAB,    // Alt-Tab
    SELECTALL,  // Ctrl+A
};

// Tap Dance declarations
enum {
    TD_LSFT_CAPS,
    TD_RSFT_CAPS,
};

// Define tap dance function
void dance_caps_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_LSFT);
    } else if (state->count == 2) {
        register_code(KC_CAPS);
    }
}

void dance_caps_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_LSFT);
    } else if (state->count == 2) {
        unregister_code(KC_CAPS);
    }
}

// Define tap dance actions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_caps_finished, dance_caps_reset),
    [TD_RSFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_caps_finished, dance_caps_reset),
};

// Alt-Tab tracking
static bool is_alt_tab_active = false;

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

// Layer definitions
enum sofle_layers {
    _GRAPHITE = 0,
    _RAISE,
    _LOWER,
    _ADJUST,
    _NUMPAD,
    _SWITCH
};

#define KC_LOWER MO(_LOWER)
#define KC_RAISE MO(_RAISE)

// Combos
enum combos {
    JK_ESC,
    FD_TAB,
    AS_CTRL,
    QW_SAVE,
    XC_COPY,
    CV_PASTE,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM fd_combo[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM as_combo[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};

combo_t key_combos[] = {
    [JK_ESC] = COMBO(jk_combo, KC_ESC),
    [FD_TAB] = COMBO(fd_combo, KC_TAB),
    [AS_CTRL] = COMBO(as_combo, KC_LCTL),
    [QW_SAVE] = COMBO(qw_combo, MY_SAVE),
    [XC_COPY] = COMBO(xc_combo, MY_COPY),
    [CV_PASTE] = COMBO(cv_combo, MY_PASTE),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * GRAPHITE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | `    |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   B  |   L  |   D  |   W  |   Z  |                    | -    |   F  |   O  |   U  |   J  | BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   N  |   R  |   T  |   S  |   G  |-------.    ,-------|   Y  |   H  |   A  |   E  |   I  |   "  |
 * |------+------+------+------+------+------| PSCR  |    |  APP  |------+------+------+------+------+------|
 * |LShift|   Q  |   X  |   M  |   C  |   V  |-------|    |-------|   K  |   P  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LALT |LCTRL|LOWER| /Space  /       \Enter \  |RAISE |RCTRL | RALT |RGUI |
 *            |      |      |      |     |/       /         \      \ |      |      |      |     |
 *            `----------------------------------'           '------''---------------------------'
 */
[_GRAPHITE] = LAYOUT(
  //,-----------------------------------------------------------.                    ,-----------------------------------------------------------.
      KC_GRV,    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //|--------+--------+--------+--------+--------+-----------------|                   |--------+--------+--------+--------+--------+----------------|
     KC_ESC,   KC_B,   KC_L,    KC_D,    KC_W,    KC_Z,                                   KC_MINS, KC_F,    KC_O,    KC_U,    KC_J,    KC_BSPC,
  //|--------+--------+--------+--------+--------+-----------------|                   |--------+--------+--------+--------+--------+----------------|
     KC_TAB,   KC_N,   KC_R,    KC_T,    KC_S,    KC_G,                                   KC_Y,    KC_H,    KC_A,    KC_E,    KC_I,    KC_QUOT,
  //|--------+--------+--------+--------+--------+-----------------|  ===  |   |  ===  |--------+--------+--------+--------+--------+----------------|
     KC_LSFT,  KC_Q,   KC_X,    KC_M,    KC_C,    KC_V,            KC_PSCR,      KC_APP,    KC_K,    KC_P,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+-----------------|  ===  |   |  ===  |--------+--------+--------+--------+--------+----------------|
                      KC_LGUI, KC_LALT, KC_LCTL, KC_LOWER, KC_SPC,         KC_ENT,  KC_RAISE, KC_RCTL, KC_RALT, KC_RGUI
  //                 \--------+--------+--------+---------+--------|        |--------+---------+--------+---------+-------/
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  |  F12 |  
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|   !  |   `  |   '  |   "  |   +  |                    |   <  |   >  |  ^  |  ~   |  $    | BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|   ?  | ()  |   []  |  {}  |   -  |-------.    ,-------|   /  | Left | Down  | Up   |Right | Del |
 * |------+------+------+------+------+------|PRINTSCRN| |   APP |------+------+------+------+------+------|
 * | trans|   & |  @   |  #   |   =  |   *  |-------|    |-------|   \  |  :  |  ;  |   _   |   |   | Shift|  
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | WIN   | ALT  | CTRL |LOWER| / Space /       \Enter \  | RAISE | RCTRL | RAlt | WIN
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_RAISE] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_TRNS, KC_EXLM, KC_GRV,  KC_QUOT, KC_DQT,  KC_PLUS,                    KC_LT,   KC_GT,   KC_CIRC, KC_TILD, KC_DLR,  KC_BSPC,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_TRNS, KC_QUES, PAIR_PR, PAIR_BR, PAIR_CB, KC_MINS,                    KC_SLSH, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DEL,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  KC_TRNS, KC_AMPR, KC_AT,   KC_HASH, KC_EQL,  KC_ASTR, KC_TRNS, KC_TRNS, KC_BSLS, KC_COLN, KC_SCLN, KC_UNDS, KC_PIPE, KC_RSFT,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   /  |   7  |   8  |   9  |   -  |                    | HOME | PGDN | PGUP | END  | DEL  | BSPC |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   *  |   4  |   5  |   6  |   +  |                    | INS  | PREV |  UP  | NEXT | PLAY | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   =  |   1  |   2  |   3  |   .  |-------.    ,-------|PAUSE | LEFT | DOWN |RIGHT |VolUp |PrtSc |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   0  |   ,  |   .  |   =  |Enter |-------|    |-------|STOP  | MENU | MUTE |VolDn | APP  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LALT |LCTRL|LOWER| /Space  /       \Enter \  |RAISE |RCTRL | RALT | RGUI |
 *            |      |      |      |     |/       /         \      \ |      |      |      |     |
 *            `----------------------------------'           '------''---------------------------'
 */
[_LOWER] = LAYOUT(
  //,-----------------------------------------------------------.                    ,-----------------------------------------------------------.
      KC_GRV,  KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,                          KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,  KC_BSPC,
  //|--------+--------+--------+--------+--------+-----------------|                   |--------+--------+--------+--------+--------+----------------|
      KC_ESC,  KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,                          KC_INS,  KC_MPRV, KC_UP,   KC_MNXT, KC_MPLY, KC_DEL,
  //|--------+--------+--------+--------+--------+-----------------|                   |--------+--------+--------+--------+--------+----------------|
      KC_TAB,  KC_PEQL, KC_P1,   KC_P2,   KC_P3,   KC_PDOT,                          KC_PAUS, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLU, KC_PSCR,
  //|--------+--------+--------+--------+--------+-----------------|  ===  |   |  ===  |--------+--------+--------+--------+--------+----------------|
      KC_LSFT, KC_P0,   KC_COMM, KC_DOT,  KC_EQL,  KC_PENT,       KC_TRNS,    KC_TRNS, KC_MSTP, KC_MENU, KC_MUTE, KC_VOLD, KC_APP,  KC_RSFT,
  //|--------+--------+--------+--------+--------+-----------------|  ===  |   |  ===  |--------+--------+--------+--------+--------+----------------|
                       KC_LGUI, KC_LALT, KC_LCTL, KC_LOWER, KC_SPC,         KC_ENT,  KC_RAISE, KC_RCTL, KC_RALT, KC_RGUI
  //                  \--------+--------+--------+---------+--------|       |--------+---------+--------+---------+-------/
),
[_ADJUST] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, XXXXXXX, XXXXXXX,          C(G(KC_LEFT)), KC_NO, KC_NO, C(G(KC_RGHT)), XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  UG_NEXT, UG_HUED, UG_SATD, UG_VALD, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
),

[_NUMPAD] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   _______, KC_NUM,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_CIRC, KC_P7,   KC_P8,   KC_P9,   KC_ASTR, KC_BSPC,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MINS, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_PIPE,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_EQL,  KC_P1,   KC_P2,   KC_P3,   KC_SLSH, _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_BSPC, KC_LGUI, _______, KC_ENT,  KC_SPC,     KC_ENT,  KC_SPC,  KC_P0,   KC_PDOT, KC_RALT
),

[_SWITCH] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  TO(0),   TO(1),   TO(2),   TO(3),   TO(4),   TO(5),                    TO(6),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_NO,   KC_NO,   KC_BRIU, KC_NO,   KC_NO,   KC_NO,                    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   EE_CLR,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  KC_SYSTEM_SLEEP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
),
};

#ifdef RGBLIGHT_ENABLE
// Layer lighting definitions
const rgblight_segment_t PROGMEM graphite_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_PURPLE)
);

const rgblight_segment_t PROGMEM raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_BLUE),
    SET_NUMROW(HSV_BLUE),      // F-keys row
    SET_INNER_COL(HSV_AZURE)   // Navigation cluster
);

const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_PINK),
    SET_NUMPAD(HSV_CORAL),     // Numpad area
    SET_OUTER_COL(HSV_PURPLE)  // Media controls
);

const rgblight_segment_t PROGMEM adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_RED),
    SET_INDICATORS(HSV_RED)
);

const rgblight_segment_t PROGMEM numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_ORANGE),
    SET_NUMPAD(HSV_ORANGE)
);

const rgblight_segment_t PROGMEM switch_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_TEAL),
    SET_INDICATORS(HSV_TEAL)
);

// Array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = {
    graphite_layer,
    raise_layer,
    lower_layer,
    adjust_layer,
    numpad_layer,
    switch_layer
};

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
    rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
    return state;
}
#endif

#ifdef OLED_ENABLE

// Keymap display data with 5 characters per line
static const char PROGMEM legends[][2][4][6] = {  // Note the [6] for null terminator
// GRAPHITE (0)
    {
        // Left side
        {
            "12345",
            "BLDWZ",
            "NRTSG",
            "QXMCV"
        },
        // Right side
        {
            "67890",
            "-FOUJ",
            "YHAEI",
            "KP,./"
        }
    },
    // RAISE (1)
    {
        // Left side
        {
            "F1-F6",
            "!`'\"+",
            "?()[]",
            "&@#=*"
        },
        // Right side
        {
            "F7-12",
            "<>^~$",
            "/UDLR",  // Changed from arrows to UDLR
            "\\:;_|"
        }
    },
    // LOWER (2)
    {
        // Left side
        {
            "/789-",
            "*456+",
            "=123.",
            "0,. ="
        },
        // Right side
        {
            "HOME",
            "NAV^",
            "PLAY",
            "MEDI"
        }
    },
    // ADJUST (3)
    {
        // Left side
        {
            "CLEAR",
            "QBOOT",
            "RGB++",
            "RGB--"
        },
        // Right side
        {
            "DESK",
            "DESK",
            "PREV",
            "VOL+-"
        }
    },
    // NUMPAD (4)
    {
        // Left side
        {
            "     ",
            "     ",
            "     ",
            "     "
        },
        // Right side
        {
            "NUM_",
            "789*",
            "456+",
            "123/"
        }
    },
    // SWITCH (5)
    {
        // Left side
        {
            "     ",
            "LAYER",
            "BRITE",
            "SLEEP"
        },
        // Right side
        {
            "     ",
            "BOOT",
            "CLEAR",
            "     "
        }
    }
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_270;  // Both sides vertical, slave side rotated
    }
    return OLED_ROTATION_270;      // Master side vertical
}

// Display Status on master side
static void render_status(void) {
    uint8_t current_layer = get_highest_layer(layer_state);
    
    // Layer name
    switch (current_layer) {
        case _GRAPHITE: oled_write_P(PSTR("GRPHT\n"), false); break;
        case _RAISE:    oled_write_P(PSTR("RAISE\n"), false); break;
        case _LOWER:    oled_write_P(PSTR("LOWER\n"), false); break;
        case _ADJUST:   oled_write_P(PSTR("ADJST\n"), false); break;
        case _NUMPAD:   oled_write_P(PSTR("NUMPD\n"), false); break;
        case _SWITCH:   oled_write_P(PSTR("SWTCH\n"), false); break;
        default:        oled_write_P(PSTR("UNDEF\n"), false); break;
    }
    
    oled_write_P(PSTR("\n"), false);
    
    // Display legend for left side
    for (int row = 0; row < 4; row++) {
        oled_write_P(legends[current_layer][0][row], false);
        oled_write_P(PSTR("\n"), false);
    }

    // WPM counter
    oled_write_P(PSTR("\nWPM:"), false);
    char wpm_str[6];
    sprintf(wpm_str, "%3d", get_current_wpm());
    oled_write(wpm_str, false);
}

// Display Status on secondary side
static void render_status_secondary(void) {
    uint8_t current_layer = get_highest_layer(layer_state);
    
    // Layer name
    switch (current_layer) {
        case _GRAPHITE: oled_write_P(PSTR("GRPHT\n"), false); break;
        case _RAISE:    oled_write_P(PSTR("RAISE\n"), false); break;
        case _LOWER:    oled_write_P(PSTR("LOWER\n"), false); break;
        case _ADJUST:   oled_write_P(PSTR("ADJST\n"), false); break;
        case _NUMPAD:   oled_write_P(PSTR("NUMPD\n"), false); break;
        case _SWITCH:   oled_write_P(PSTR("SWTCH\n"), false); break;
        default:        oled_write_P(PSTR("UNDEF\n"), false); break;
    }
    
    oled_write_P(PSTR("\n"), false);
    
    // Display legend for right side
    for (int row = 0; row < 4; row++) {
        oled_write_P(legends[current_layer][1][row], false);
        oled_write_P(PSTR("\n"), false);
    }

    // Empty space where WPM would be on primary side
    oled_write_P(PSTR("\n     "), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_status_secondary();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PAIR_PR:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING("(");
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING(")");
                } else {
                    SEND_STRING("()");
                    tap_code(KC_LEFT);
                }
            }
            return false;
        case PAIR_BR:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING("[");
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING("]");
                } else {
                    SEND_STRING("[]");
                    tap_code(KC_LEFT);
                }
            }
            return false;
        case PAIR_CB:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT)) {
                    SEND_STRING("{");
                } else if (get_mods() & MOD_BIT(KC_RSFT)) {
                    SEND_STRING("}");
                } else {
                    SEND_STRING("{}");
                    tap_code(KC_LEFT);
                }
            }
            return false;
        case MY_COPY:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_C));
            }
            return false;
        case MY_PASTE:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_V));
            }
            return false;
        case MY_CUT:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_X));
            }
            return false;
        case MY_UNDO:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_Z));
            }
            return false;
        case MY_SAVE:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_S));
            }
            return false;
        case MY_FIND:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_F));
            }
            return false;
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                tap_code(KC_TAB);
            }
            return false;
        case SELECTALL:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_A));
            }
            return false;
        default:
            return true;
    }

}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {  // First encoder (left side)
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {  // Second encoder (right side)
        uint8_t current_layer = get_highest_layer(layer_state);
        
        if (clockwise) {
            // Cycle forward through layers
            if (current_layer == _SWITCH) {  // If at highest layer
                layer_clear();  // Go back to base layer
            } else {
                layer_on(current_layer + 1);  // Go to next layer
            }
        } else {
            // Cycle backward through layers
            if (current_layer == 0) {  // If at base layer
                layer_on(_SWITCH);  // Go to highest layer
            } else {
                layer_off(current_layer);  // Go to previous layer
            }
        }
    }
    return false;
}

#endif
