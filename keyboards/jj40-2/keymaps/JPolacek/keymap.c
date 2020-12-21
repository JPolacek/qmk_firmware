/* Copyright 2019
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define TLOWER TG(_LOWER)
#define TRAISE TG(_RAISE)
#define TADJUST TG(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | TAB  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |ENTER |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  UP  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | GUI  |  Alt | Ctrl |TRaise|Raise | space|space |Lower |TLower| LEFT | DOWN |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_SLSH , \
  KC_LGUI, KC_LALT, KC_LCTL, TRAISE,  RAISE,   KC_SPC,  KC_SPC,  LOWER,   TLOWER,  KC_LEFT, KC_DOWN, KC_RGHT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  ESC |      |      |      |      |      |      |PTSCRN|      |  BR+ |      |  DEL |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  | HOME | PGUP |  BR- | SLEP | ent  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |  F8  |  F9  |  F10 |  F11 |      |      |      | END  | PGDN | NEXT | Vol+ | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | f6   | f12  |      | TAdj |  Adj |      |      |      |      | Prev | Vol- | Mute |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  KC_ESC, _______, _______, _______, _______, _______, _______, KC_PSCR, _______, KC_BRMU, _______, KC_DEL, \
  KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, KC_HOME, KC_PGUP, KC_BRMD, KC_SLEP, KC_ENT, \
  KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, _______, KC_END,  KC_PGDN, KC_MNXT, KC_VOLU, KC_MPLY, \
  _______, _______, _______, TADJUST, ADJUST, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC__MUTE \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | DEL  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Caps |   4  |   5  |   6  |      |      |  [   |   ]  |  \   |  "   |   :  | ent  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   7  |   8  |   9  |      |      |  -   |   +  |  ,   |  .   |  UP  |   /  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  Adj | TAdj | LEFT | DOWN |RIGHT |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_CAPS,  KC_4,    KC_5,    KC_6,    _______, _______, KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT, KC_SCLN, KC_ENT, \
  KC_LSFT,  KC_7,    KC_8,    KC_9,    _______, _______, KC_MINS, KC_EQL,  KC_COMM, KC_DOT,  KC_UP,   KC_SLSH, \
  _______,  _______, _______, _______, _______, _______, _______, ADJUST,  TADJUST, KC_LEFT, KC_DOWN, KC_RGHT \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Reset |      |      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | LEAD |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT_ortho_4x12( \
  RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)
};

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(0,0,0);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _ADJUST:
        rgblight_setrgb (255, 0, 0);
        break;
    case _RAISE:
        rgblight_setrgb (255, 255, 255);
        break;
    case _LOWER:
        rgblight_setrgb (255, 140, 0);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0, 0, 0);
        break;
  }

  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}