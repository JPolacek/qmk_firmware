#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;
uint16_t lt_timer;
uint16_t raise_timer;
uint16_t def_timer;
int was_lower, was_raise, was_adj;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

#define TG_LOWER TG(_LOWER)
#define KC_TMB1 ALT_T(KC_TAB)
#define KC_PNK2 CMD_T(KC_QUOT)
#define KC_TMB2 CMD_T(KC_SPC)
#define TT_DEF TT(_QWERTY) // act as LOWER when hold, toggle LOWER when tapped
#define TT_LOW TT(_LOWER) // act as LOWER when hold, toggle LOWER when tapped
#define TT_RSE TT(_RAISE) // act as RAISE when hold, toggle RAISE when tapped
#define KC_TMB5 CTL_T(KC_BSPC)
#define KC_TMB6 CMD_T(KC_ENT)
#define KC_TMB7 CTL_T(KC_DEL)
#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_LOCK LGUI(LCTL(KC_Q))        // lock screen

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  TH_LOW,
  TH_RSE,
  TH_DEF
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
      KC_TAB,  KC_SCLN, KC_COMM, KC_DOT,   KC_P,    KC_Y,          KC_F,    KC_G,    KC_C,    KC_R,    KC_L,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
      KC_QUOT,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,          KC_D,   KC_H,    KC_T,     KC_N,    KC_S,   KC_MINS,
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,          KC_M,   KC_W,    KC_V,     KC_Z,   KC_SLSH, KC_RSFT,
  //'--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
                                 KC_TMB1,  TH_LOW, KC_TMB2,      KC_TMB6,   TH_RSE, KC_TMB7
  //                           `--------+--------+--------'     '--------+--------+--------'
  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.     ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
      KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLU,       KC_SLCK, KC_CAPP, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
      _______, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_VOLD,       KC_PAUS, KC_LEFT,   KC_UP, KC_DOWN,KC_RIGHT, _______,
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
                                 _______,  TH_DEF, _______,       _______,  TH_RSE, _______
                             //`--------------------------'     '--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.     ,-----------------------------------------------------.
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_LOCK,\
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,       KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE,  KC_GRV,\
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,       KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,\
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
                                 _______,  TH_LOW, _______,       _______,  TH_DEF, _______ \
                             //`--------------------------'     '--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.     ,-----------------------------------------------------.
        RESET,  RGBRST, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,       _______, _______, _______, _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|     |--------+--------+--------+--------+--------+--------|
                                 _______,  TH_DEF, _______,       _______,  TH_DEF, _______ \
                             //`--------------------------'     `--------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    // matrix_write_ln(matrix, read_timelog());
    // matrix_write(matrix, read_logo());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case TH_RSE:
        if(record->event.pressed){
            raise_timer = timer_read();
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_RAISE);
            if (timer_elapsed(raise_timer) < 100) {
                layer_on(_RAISE);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
    case TH_LOW:
        if(record->event.pressed){
            lt_timer = timer_read();
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        } else {
            layer_off(_LOWER);
            if (timer_elapsed(lt_timer) < 100) {
                layer_on(_LOWER);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
    case TH_DEF:
        was_lower = IS_LAYER_ON(_LOWER); was_raise = IS_LAYER_ON(_RAISE); was_adj = IS_LAYER_ON(_ADJUST);
        if(record->event.pressed){
            def_timer = timer_read();
            if(was_adj) {
                layer_off(_ADJUST);
            }
            if(was_lower) {
                layer_off(_LOWER);
            }
            if(was_raise) {
                layer_off(_RAISE);
            }
            layer_on(_QWERTY);
        } else {
            layer_off(_QWERTY);
            if(was_adj) {
                layer_on(_ADJUST);
            }
            if(was_lower) {
                layer_on(_LOWER);
            }
            if(was_raise) {
                layer_on(_RAISE);
            }
            if (timer_elapsed(lt_timer) < 100) {
                layer_clear();
                layer_on(_QWERTY);
                was_lower = 0; was_raise = 0; was_adj = 0;
            }
        }
        return false;
  }
  return true;
}
