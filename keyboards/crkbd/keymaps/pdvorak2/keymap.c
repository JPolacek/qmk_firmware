#include QMK_KEYBOARD_H


#ifdef OLED_DRIVER_ENABLE
static uint32_t        oled_timer = 0;
static char     keylog_str[6]   = {};
static uint16_t log_timer       = 0;
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};

void add_keylog(uint16_t keycode);
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

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
        add_keylog(keycode);
#endif
#ifndef SPLIT_KEYBOARD
        if (keycode == RESET && !is_master) {
            return false;
        }
#endif
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    for (uint8_t i = 4; i > 0; --i) {
        keylog_str[i] = keylog_str[i - 1];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
    }

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        //add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Lyout"), false);
    switch (biton32(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(" QRTY"), false);
            break;
}

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Lower"), layer_state_is(_LOWER));
    oled_write_P(PSTR("Raise"), layer_state_is(_RAISE));
    oled_write_P(PSTR("Adjust"), layer_state_is(_ADJUST));
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    oled_write_P(PSTR("BTMGK"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
}

// void render_user_status(void) {
//     oled_write_P(PSTR("USER:"), false);
//     oled_write_P(PSTR(" Anim"), userspace_config.rgb_matrix_idle_anim);
//     oled_write_P(PSTR(" Layr"), userspace_config.rgb_layer_change);
//     oled_write_P(PSTR(" Nuke"), userspace_config.nuke_switch);
// }

void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_keylock_status(host_keyboard_leds());
    render_bootmagic_status();
    // render_user_status();

    render_keylogger_status();
}

void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_layer_state();
    render_mod_status(get_mods()|get_oneshot_mods());

    render_keylogger_status();
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    update_log();
    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif

// uint16_t get_tapping_term(uint16_t keycode) {
//     switch (keycode) {
//         case ALT_T(KC_A):
//             return TAPPING_TERM + 100;
//         default:
//             return TAPPING_TERM;
//     }
// }

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

void check_default_layer(uint8_t mode, uint8_t type) {
    switch (biton32(default_layer_state)) {
        case _QWERTY:
            rgb_matrix_layer_helper(HSV_CYAN, mode, rgb_matrix_config.speed, type);
            break;
        case _COLEMAK:
            rgb_matrix_layer_helper(HSV_MAGENTA, mode, rgb_matrix_config.speed, type);
            break;
        case _DVORAK:
            rgb_matrix_layer_helper(HSV_SPRINGGREEN, mode, rgb_matrix_config.speed, type);
            break;
        case _WORKMAN:
            rgb_matrix_layer_helper(HSV_GOLDENROD, mode, rgb_matrix_config.speed, type);
            break;
        case _NORMAN:
            rgb_matrix_layer_helper(HSV_CORAL, mode, rgb_matrix_config.speed, type);
            break;
        case _MALTRON:
            rgb_matrix_layer_helper(HSV_YELLOW, mode, rgb_matrix_config.speed, type);
            break;
        case _EUCALYN:
            rgb_matrix_layer_helper(HSV_PINK, mode, rgb_matrix_config.speed, type);
            break;
        case _CARPLAX:
            rgb_matrix_layer_helper(HSV_BLUE, mode, rgb_matrix_config.speed, type);
            break;
    }
}

void rgb_matrix_indicators_user(void) {
    if (userspace_config.rgb_layer_change &&
#    ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
        !g_suspend_state &&
#    endif
#    if defined(RGBLIGHT_ENABLE)
        (!rgblight_config.enable && rgb_matrix_config.enable)
#    else
        rgb_matrix_config.enable
#    endif
    ) {
        switch (biton32(layer_state)) {
            case _GAMEPAD:
                rgb_matrix_layer_helper(HSV_ORANGE, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _DIABLO:
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _RAISE:
                rgb_matrix_layer_helper(HSV_YELLOW, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _LOWER:
                rgb_matrix_layer_helper(HSV_GREEN, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _ADJUST:
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            default: {
                check_default_layer(IS_LAYER_ON(_MODS), LED_FLAG_UNDERGLOW);
                break;
            }
        }
        check_default_layer(0, LED_FLAG_MODIFIER);
    }
}
#endif

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
