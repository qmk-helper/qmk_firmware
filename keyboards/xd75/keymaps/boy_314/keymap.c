#include QMK_KEYBOARD_H

// Layer shorthand
#define _DV 0
#define _QW 1
#define _NP 2
#define _FN1 3
#define _FN2 4

#define RGBLIGHT_LIGHT_VAL 255
const uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {10, 10, 10};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* DVORAK
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | '      | .      | .      | P      | Y      | [      | UP      | ]      | F      | G      | C      | R      | L      | /      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | O      | E      | U      | I      | LEFT   | DOWN   | RIGHT  | D      | H      | T      | N      | S      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | ;      | Q      | J      | K      | X      | PG DN  | UP     | PG UP  | M      | W      | W      | V      | Z      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | DEL    | LALT   | WIN    | FN1    | SPACE  | LEFT   | DOWN   | RIGHT  | SPACE  | FN2    | LEFT   | DOWN   | UP     | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_DV] = LAYOUT_ortho_5x15( /* DVORAK */
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_LBRC, KC_UP,   KC_RBRC, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
  LCTL_T(KC_CAPS), KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_LEFT, KC_DOWN, KC_RGHT, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT,
  KC_LSPO, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_PGDN,  KC_UP,  KC_PGUP, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSPC,
  KC_LCTL, KC_DEL,  KC_LALT, KC_LGUI, MO(_FN1),KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,  MO(_FN2),KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
 ),

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | \      | ]      | Y      | U      | I      | O      | P      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | HOME   | DEL    | PG UP  | H      | J      | K      | L      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | UP     | PG DN  | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | DEL    | LALT   | WIN    | FN1    | SPACE  | LEFT   | DOWN   | RIGHT  | SPACE  | FN2    | LEFT   | DOWN   | UP     | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_DEL,  KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_END,  KC_UP,   KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
  KC_LCTL, KC_DEL,  KC_LALT, KC_LGUI, MO(_FN1),KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,  MO(_FN2),KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
 ),

/* NUMPAD
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        | /      | *      | -      |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | 7      | 8      | 9      |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | 4      | 5      | 6      |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | 1      | 2      | 3      |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | 0      | +      | .      |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_NP] = LAYOUT_ortho_5x15( /* NUMPAD */
  _______, _______, _______, _______, _______, _______, KC_SLSH, KC_ASTR, KC_MINS, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,    KC_7,    KC_8,    KC_9, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,    KC_4,    KC_5,    KC_6, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,    KC_1,    KC_2,    KC_3, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,    KC_0, KC_PLUS,  KC_DOT, _______, _______, _______, _______, _______, _______
 ),

/* FUNCTION1
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |   `    |   !    |   @    |   #    |   $    |   %    |        |        |        |    ^   |   &    |   *    |   (    |   )    | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |   ~    |   !    |   @    |   #    |   $    |   %    | RESET  |RGB HUE-|RGB HUE+|    ^   |   &    |   *    |   (    |   )    | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | DEL    |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |RGB SAT-|RGB SAT+| DVORAK |   _    |   +    |   {    |   }    |   |    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |   F7   |   F8   |   F9   |   F10  |   F11  |   F12  |BRIGHT- |BRIGHT+ | QWERTY |        |        | HOME   | END    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |RGB MODE|RGB MODE|        |        | PREV   | VOL UP |VOL DOWN| NEXT   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_FN1] = LAYOUT_ortho_5x15( /* FUNCTION1 */
  KC_GRV , KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,   RESET, RGB_HUD, RGB_HUI, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  KC_DEL,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, RGB_SAD, RGB_SAI, TO(_DV), KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, RGB_VAD, RGB_VAI, TO(_QW), _______, _______, KC_HOME,  KC_END, _______,
  _______, _______, _______, _______, _______, _______, _______,RGB_RMOD, RGB_MOD, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
 ),


/* FUNCTION2
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |   `    | 1      | 2      | 3      | 4      | 5      |        |        |        | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |   `    |        |        |   UP   |        |        | RESET  |RGB HUE-|RGB HUE+| NUMPAD |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | DEL    |        |  LEFT  |  DOWN  | RIGHT  |        |        |RGB SAT-|RGB SAT+| DVORAK |   -    |   =    |   [    |   ]    |   \    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |BRIGHT- |BRIGHT+ | QWERTY |        |        | PAGE UP| PAGE DN|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |RGB MODE|RGB MODE|        |        | PREV   | VOL UP |VOL DOWN| NEXT   |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_FN2] = LAYOUT_ortho_5x15( /* FUNCTION2 */
  KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, _______, _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_GRV, _______, _______,   KC_UP, _______, _______,   RESET, RGB_HUD, RGB_HUI, TG(_NP), _______, _______, _______, _______, KC_DEL,
  KC_DEL, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, RGB_SAD, RGB_SAI, TG(_DV), KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
  _______, _______, _______, _______, _______, _______, _______, RGB_VAD, RGB_VAI, TG(_QW), _______, _______, KC_PGDN, KC_PGUP, _______,
  _______, _______, _______, _______, _______, _______, _______,RGB_RMOD, RGB_MOD, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
 )
};

void matrix_init_user(void) {
  if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
    register_code(KC_NUMLOCK);
    unregister_code(KC_NUMLOCK);
  }
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        rgblight_mode(18);
    } else {
        rgblight_mode(14);
    }
}
