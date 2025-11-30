# Graphite Keyboard Layout

This document describes the custom Graphite-based layout for Estonian users. Use this to implement the same layout on other keyboards (QMK, ZMK, etc).

## Hardware Notes
- Layout designed for split keyboards with 6 columns per side
- Center display/encoder buttons (2 keys) on rows 1-2 if available
- 3 thumb keys per side

---

## Layer 0 - Graphite (Base Layer)

```
┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │  B  │  L  │  D  │  W  │  Z  │  (MUTE/PP)  │  -  │  F  │  O  │  U  │  J  │ DEL │
├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  N  │  R  │  T  │  S  │  G  │  (ALT/ALT)  │  Y  │  H  │  A  │  E  │  I  │  '  │
├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
│SHIFT│  Q  │  X  │  M  │  C  │  V  │             │  K  │  P  │  ,  │  .  │  /  │SHIFT│
└─────┴─────┴─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │CTRL │ L1  │SPACE│             │BSPC │ L2  │ GUI │
                  └─────┴─────┴─────┘             └─────┴─────┴─────┘
```

**Notes:**
- Center keys (MUTE/PP and ALT/ALT) only if keyboard has encoder/display buttons
- L1 = Layer 1 (Navigate), L2 = Layer 2 (Symbols)

---

## Layer 1 - Navigate

```
┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │(CTRL/CTRL)  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │
├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
│ ESC │sk(G)│sk(A)│sk(C)│sk(S)│HOME │ (ALT/ALT)   │HOME │  ←  │  ↓  │  ↑  │  →  │ END │
├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
│SHIFT│  1  │  2  │  3  │  4  │  5  │             │  6  │  7  │  8  │  9  │  0  │ ESC │
└─────┴─────┴─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │SPACE│             │ENTER│ L3  │     │
                  └─────┴─────┴─────┘             └─────┴─────┴─────┘
```

**Notes:**
- sk(G) = Sticky GUI, sk(A) = Sticky ALT, sk(C) = Sticky CTRL, sk(S) = Sticky SHIFT
- Sticky keys stay active for one keypress only
- L3 = Layer 3 (Adjust)

---

## Layer 2 - Symbols

```
┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │  @  │  "  │  '  │  #  │  +  │(CTRL/CTRL)  │  $  │  &  │  %  │  ~  │  \  │ DEL │
├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  ?  │ ( ) │ [ ] │ { } │  -  │ (ALT/ALT)   │  |  │  =  │  _  │  `  │PgUp │PgDn │
├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
│SHIFT│  !  │  <  │  >  │  ^  │  *  │             │  :  │  ;  │  ,  │  .  │  /  │SHIFT│
└─────┴─────┴─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │ L3  │SPACE│             │ENTER│ L2  │ DEL │
                  └─────┴─────┴─────┘             └─────┴─────┴─────┘
```

**Notes:**
- `( )` = Mod-morph: tap for `(`, shift+tap for `)`
- `[ ]` = Mod-morph: tap for `[`, shift+tap for `]`
- `{ }` = Mod-morph: tap for `{`, shift+tap for `}`

---

## Layer 3 - Adjust

```
┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
│BTCLR│ BT0 │ BT1 │ BT2 │ BT3 │ BT4 │(CTRL/CTRL)  │UNLCK│     │     │     │     │BOOT │
├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
│RGBTG│RGB+ │RGB- │BRI+ │BRI- │UNLCK│ (ALT/ALT)   │UNLCK│  ä  │  õ  │  ü  │  ö  │SLEEP│
├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
│RGBEF│HUE+ │HUE- │SAT+ │SAT- │UNLCK│             │PREV │VOL- │MUTE │VOL+ │NEXT │PLAY │
└─────┴─────┴─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ GUI │     │SPACE│             │ENTER│     │ DEL │
                  └─────┴─────┴─────┘             └─────┴─────┴─────┘
```

**Notes:**
- Estonian umlauts (ä, õ, ü, ö):
  - ZMK: Use Ctrl+Shift+U Unicode input (Linux): e4, f5, fc, f6
  - QMK: Use UNICODE_ENABLE or UC_LINX mode with UC(0x00E4), etc.
- BTCLR = Clear Bluetooth bonds
- BT0-BT4 = Bluetooth profile selection
- RGBTG = RGB Toggle, RGBEF = RGB Effect cycle
- UNLCK = ZMK Studio unlock (ZMK only, use RESET for QMK)
- BOOT = Bootloader mode
- SLEEP = System sleep

---

## QMK Implementation Notes

### Mod-Morph Brackets
In QMK, use `LT()` or custom keycodes with `process_record_user()`:

```c
// Example for parentheses
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
```

### Sticky Keys
Use `OSM(MOD_LGUI)`, `OSM(MOD_LALT)`, `OSM(MOD_LCTL)`, `OSM(MOD_LSFT)`

### Unicode (Estonian Umlauts)
```c
// In config.h
#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX

// In keymap.c
enum unicode_names {
    UML_A,  // ä
    UML_O,  // õ
    UML_U,  // ü
    UML_OE, // ö
};

const uint32_t PROGMEM unicode_map[] = {
    [UML_A]  = 0x00E4,  // ä
    [UML_O]  = 0x00F5,  // õ
    [UML_U]  = 0x00FC,  // ü
    [UML_OE] = 0x00F6,  // ö
};

// Use X(UML_A), X(UML_O), etc. in keymap
```

---

## Encoder Bindings (if available)

| Layer | Left Encoder | Right Encoder |
|-------|--------------|---------------|
| 0 | Volume Down/Up | Page Up/Down |
| 1 | Previous/Next Track | Brightness Down/Up |
| 2 | - | - |
| 3 | - | - |
