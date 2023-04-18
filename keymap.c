/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "features/select_word.h"

//MACROS
enum custom_keycodes {
  SELWORD = SAFE_RANGE, //Select Word - press Esc to make the macro tap right arrow → to deselect and leave the cursor at the end of the selection. Or press ← or → directly to deselect and choose which selection endpoint to jump the cursor to
  // Other custom keys...
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //Colemak - base
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   MO(1),  KC_ENT,     KC_SPC,   MO(2), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),
    //Lower
  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_MPRV,   KC_UP, KC_MNXT, KC_PSCR, KC_EXEC,                      KC_PGUP,    KC_1,    KC_2,    KC_3, KC_PAUS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT,  KC_ENT,  KC_INS,                      KC_HOME,    KC_4,    KC_5,    KC_6,    KC_0,  KC_END,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_F13, KC_CAPS, KC_CALC,  KC_F14, KC_MPLY,                      KC_PGDN,    KC_7,    KC_8,    KC_9,   KC_NO, KC_FIND,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, _______,  KC_ENT,    KC_RCTL,   MO(3), RALT(KC_ENT)
                                      //`--------------------------'  `--------------------------'
  ),
    //Raise
  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_GRV, KC_CIRC,RALT(KC_5),KC_PERC, KC_LPRN,                      KC_RPRN, KC_PEQL, KC_ASTR, XXXXXXX, KC_PIPE,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_AT,  KC_DLR,   KC_LT, KC_MINS, KC_LBRC,                      KC_RBRC, KC_PLUS,   KC_GT, KC_AMPR, KC_BSLS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,KC_TILD,XXXXXXX,RALT(KC_K), KC_HASH, KC_LCBR,                      KC_RCBR, SELWORD, XXXXXXX, KC_UNDS, KC_EXLM,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3), CW_TOGG,     KC_SPC, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),
    //Adjust
  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,   TO(5), XXXXXXX, XXXXXXX,   TO(4),   TO(6),                        TO(0), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PDOT,   KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,                        KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0, KC_PENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
    //RGB Setup
   [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      RGB_TOG, RGB_MOD, RGB_SAI, RGB_HUI, RGB_SPI, RGB_VAI,                        BL_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   BL_ON,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,RGB_RMOD, RGB_SAD, RGB_HUD, RGB_SPD, RGB_VAD,                      BL_DOWN, BL_TOGG, BL_STEP, BL_BRTG, XXXXXXX,  BL_OFF,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,   TO(0), XXXXXXX,    XXXXXXX,   TO(0), XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),
    //QWERTY
   [5] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_ENT,     KC_SPC,   MO(2), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),
    //Game
   [6] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_T,    KC_Y,                  RCS(KC_ESC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LCA(KC_DEL),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, MO(7),  KC_SPC,     XXXXXXX,    TO(0), KC_RGUI
                                      //`--------------------------'  `--------------------------'
  ),
    //GameLower
   [7] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_I,   KC_UP,    KC_M,    KC_L,    KC_O,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT,  KC_ENT,    KC_P,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, XXXXXXX,    XXXXXXX,   TO(0), XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 1
#define L_RAISE 2
#define L_ADJUST 3
#define L_RGB 4
#define L_QWERTY 5
#define L_GAME 6
#define L_GAMELOWER 7

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        case L_RGB:
            oled_write_ln_P(PSTR("RGB Setup"), false);
            break;
        case L_QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case L_GAME:
            oled_write_ln_P(PSTR("Game"), false);
            break;
        case L_GAMELOWER:
            oled_write_ln_P(PSTR("Game ALT"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();

        led_t led_state = host_keyboard_led_state();  // caps lock stuff, prints CAPS on new line if caps led is on

        oled_set_cursor(0, 1);
        oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("       "), false);
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_select_word(keycode, record, SELWORD)) { return false; }
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return true;
}
#endif  //END OLED config

//RGB Layer control
#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
layer_state_t layer_state_set_keymap(layer_state_t state) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); //Solid color
    switch (get_highest_layer(state)) {
        case L_QWERTY:
            rgblight_sethsv_noeeprom(HSV_GOLD);
            break;
        case L_GAME:
            rgblight_sethsv_noeeprom(HSV_ORANGE);
            break;
        case L_RGB:
            rgblight_sethsv_noeeprom(HSV_BLACK);
            break;
        default:  // for any other layers, or the default layer
            rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT + 3);
            rgblight_sethsv(HSV_WHITE);
            break;
    }
    return state;
}
#endif
