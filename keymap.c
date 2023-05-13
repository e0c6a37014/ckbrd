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

typedef struct {
  bool is_press_action;
  int state;
} td_tap_t;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};


//MACROS
enum custom_keycodes {
  SELWORD = SAFE_RANGE, //Select Word - press Esc to make the macro tap right arrow → to deselect and leave the cursor at the end of the selection. Or press ← or → directly to deselect and choose which selection endpoint to jump the cursor to
  ALT_OSL1 = 0,  // Tap Dance Alt key - hold for alt, tap for one-shot layer hold, tap and hold for layer hold + alt hold
  MACRO_THAT_DOESNT_DO_ANYTHING,    // Empty macro needs to be here because the third macro doesn't work ever for some reason
  M_EURSYM,
};

//Functions associated with tap dances
int cur_dance (tap_dance_state_t *state);
void alt_finished (tap_dance_state_t *state, void *user_data);
void alt_reset (tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //Colemak - base
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------.                            ,-----------------------------------------------------------------------.
    LT(0,KC_TAB),       KC_Q,       KC_W,       KC_F,       KC_P,       KC_G,                                    KC_J,       KC_L,       KC_U,       KC_Y,    KC_SCLN,    KC_BSPC,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
   OSM(MOD_LCTL),       KC_A,       KC_R,       KC_S,       KC_T,       KC_D,                                    KC_H,       KC_N,       KC_E,       KC_I,       KC_O,    KC_QUOT,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
   OSM(MOD_LSFT),       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,                                    KC_K,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,LSFT_T(KC_ESC),
  //|-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                    TD(ALT_OSL1),      TT(1),     KC_ENT,          KC_SPC,      TT(2),OSM(MOD_RALT)
                                                  //`-----------------------------------'    `-----------------------------------'

  ),
    //Lower
  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------.                            ,-----------------------------------------------------------------------.
         QK_GESC,   M_EURSYM,    KC_HOME,      KC_UP,     KC_END,LT(0,KC_LBRC),                         LT(0,KC_RBRC),    KC_AMPR,    KC_ASTR,    KC_UNDS,    KC_PIPE,     KC_DEL,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
   OSM(MOD_LCTL),    CW_TOGG,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_LPRN,                                 KC_RPRN,    KC_PLUS,    KC_PERC,    KC_MINS,    KC_BSLS,     KC_EQL,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
   OSM(MOD_LSFT),     KC_F13,      KC_AT,    XXXXXXX,     KC_SPC,      KC_LT,                                   KC_GT,    KC_HASH,     KC_DLR,    KC_CIRC,    KC_EXLM,    SELWORD,
  //|-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                         KC_BSPC,    _______,    KC_CALC,          KC_SPC,      TT(3),    XXXXXXX
                                                  //`-----------------------------------'    `-----------------------------------'
  ),
    //Raise
  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------.                            ,-----------------------------------------------------------------------.
          KC_ESC,     KC_F12,      KC_F7,      KC_F8,      KC_F9,    KC_PSCR,                                 KC_PGUP, LT(0,KC_7), LT(0,KC_8),       KC_9,    KC_BSPC,     KC_DEL,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
 LCTL_T(KC_CAPS),     KC_F11,      KC_F4,      KC_F5,      KC_F6,     KC_INS,                                 KC_HOME, LT(0,KC_4), LT(0,KC_5), LT(0,KC_6),       KC_0,     KC_END,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
   OSM(MOD_LSFT),     KC_F10,      KC_F1,      KC_F2,      KC_F3,    KC_PAUS,                                 KC_PGDN, LT(0,KC_1), LT(0,KC_2), LT(0,KC_3),LT(0,KC_NO),     KC_ENT,
  //|-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                    TD(ALT_OSL1),      TT(3),    KC_LGUI,          KC_SPC,    _______,    KC_RALT
                                                  //`-----------------------------------'    `-----------------------------------'
  ),
    //Adjust
  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------.                            ,-----------------------------------------------------------------------.
           TO(4),    XXXXXXX,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MUTE,                                  KC_NUM,      KC_P7,      KC_P8,      KC_P9,    XXXXXXX,    KC_BSPC,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
           TO(5), LT(0,KC_1), LT(0,KC_2), LT(0,KC_3), LT(0,KC_4), LT(0,KC_5),                              LT(0,KC_6), LT(0,KC_7), LT(0,KC_8),       KC_9,      KC_P0,    XXXXXXX,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
           TO(6),    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_VOLD,                                 KC_VOLU,      KC_P1,    KC_COMM,     KC_DOT,LT(0,KC_NO),    KC_PENT,
  //|-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                         XXXXXXX,    _______,      TO(0),           TO(0),    _______,    KC_RALT
                                                  //`-----------------------------------'    `-----------------------------------'
  ),
    //RGB Setup
   [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------.                            ,-----------------------------------------------------------------------.
         RGB_TOG,    RGB_MOD,    RGB_SAI,    RGB_HUI,    RGB_SPI,    RGB_VAI,                                 XXXXXXX,      KC_P7,      KC_P8,      KC_P9,     KC_DEL,    KC_BSPC,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
         XXXXXXX,   RGB_RMOD,    RGB_SAD,    RGB_HUD,    RGB_SPD,    RGB_VAD,                                 XXXXXXX,      KC_P4,      KC_P5,      KC_P6,      KC_P0,    XXXXXXX,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
         KC_LSFT,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                                 XXXXXXX,      KC_P1,      KC_P2,      KC_P3,LT(0,KC_NO),     KC_ENT,
  //|-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                         XXXXXXX,      TO(0),    QK_BOOT,         XXXXXXX,      TO(0),    KC_RALT
                                                  //`-----------------------------------'    `-----------------------------------'
  ),
    //QWERTY
   [5] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------.                            ,-----------------------------------------------------------------------.
    LT(0,KC_TAB),       KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                                    KC_Y,       KC_U,       KC_I,       KC_O,      KC_P,     KC_BSPC,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
   OSM(MOD_LCTL),       KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                                    KC_H,       KC_J,       KC_K,       KC_L,    KC_SCLN,    KC_QUOT,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
   OSM(MOD_LSFT),       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,                                    KC_N,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,     KC_ESC,
  //|-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                         KC_LGUI,      TO(0),     KC_ENT,          KC_SPC,      TO(0),    KC_RALT
                                                  //`-----------------------------------'    `-----------------------------------'
  ),
    //Game
   [6] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------.                            ,-----------------------------------------------------------------------.
          KC_TAB,       KC_Q,       KC_W,       KC_E,       KC_T,       KC_Y,                                 XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_BSPC,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
         KC_LSFT,       KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                                 XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
         KC_LCTL,       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,                                 XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     KC_ESC,
  //|-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                         KC_LALT,LT(7,KC_SPC),  KC_RCTL,         XXXXXXX,      TO(0),    KC_RGUI
                                                  //`-----------------------------------'    `-----------------------------------'
  ),
    //GameLower
   [7] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------.                            ,-----------------------------------------------------------------------.
          KC_ESC,       KC_I,      KC_UP,       KC_M,       KC_L,       KC_O,                                 XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
         KC_LSFT,    KC_LEFT,    KC_DOWN,    KC_RGHT,     KC_ENT,       KC_P,                                 XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
  //|-----------+-----------+-----------+-----------+-----------+-----------|                            |-----------+-----------+-----------+-----------+-----------+-----------|
         KC_LCTL,       KC_1,       KC_2,       KC_3,       KC_4,       KC_5,                                 XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
  //|-----------+-----------+-----------+-----------+-----------+-----------+-----------|    |-----------+-----------+-----------+-----------+-----------+-----------+-----------|
                                                         KC_LALT,     KC_SPC,    _______,         XXXXXXX,      TO(0),    XXXXXXX
                                                  //`-----------------------------------'    `-----------------------------------'
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
  }
  return OLED_ROTATION_270;
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
    //oled_write_P(PSTR("Layer:"), false);
    switch (get_highest_layer(layer_state)) {
        case L_BASE:
            oled_write_ln_P(PSTR("_"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("LOWER     "), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("RAISE     "), false);
            break;
        case L_ADJUST:
            oled_write_ln_P(PSTR("ADJST     "), false);
            break;
        case L_RGB:
            oled_write_ln_P(PSTR("RGB       "), false);
            break;
        case L_QWERTY:
            oled_write_ln_P(PSTR("QWRTY     "), false);
            break;
        case L_GAME:
            oled_write_ln_P(PSTR("GAME      "), false);
            break;
        case L_GAMELOWER:
            oled_write_ln_P(PSTR("GAME ALT"), false);
            break;
    }
}

/*
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
    // Show Ctrl-Gui Swap options 
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
*/

static const char image [] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0x1c, 0x0e, 0x06, 
    0x03, 0x03, 0x0f, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0xf0, 0xc0, 0x80, 
    0x00, 0x00, 0x00, 0x01, 0x07, 0x0e, 0x1c, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1f, 
    0xfe, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0e, 0x1c, 0x38, 0x70, 
    0xc0, 0xe0, 0x30, 0x30, 0x18, 0x18, 0x08, 0x0c, 0x0c, 0x0c, 0x0c, 0x04, 0x06, 0x86, 0x86, 0x86, 
    0x87, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x3f, 0xf8, 0xe0, 0xc0, 0x80, 0x80, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x81, 0x81, 0xc1, 
    0xc1, 0xc1, 0x63, 0x67, 0x7e, 0xfc, 0xf8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x1f, 0x3f, 0x71, 0x61, 0xe3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc1, 0xc1, 0xe1, 
    0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x18, 0x1d, 0x3f, 0x7e, 0xe4, 0xc0, 0x80, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0e, 0x18, 0x18, 0x38, 0xf8, 0xf8, 0x38, 0x10, 0x10, 0x10, 
    0x18, 0x18, 0x18, 0x0c, 0x0c, 0x0e, 0x06, 0x86, 0x87, 0x8f, 0xdf, 0xf9, 0x71, 0x60, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x06, 0x06, 0x86, 
    0xc6, 0xe6, 0xc6, 0x86, 0x06, 0x07, 0x07, 0x07, 0x07, 0x05, 0x04, 0x04, 0x04, 0x06, 0x06, 0x03, 
    0xc0, 0xf0, 0x30, 0x30, 0x60, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe3, 
    0x00, 0x00, 0x00, 0x03, 0x0e, 0x1c, 0x70, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x30, 
    0x03, 0x0f, 0x1c, 0x30, 0x60, 0xc0, 0x80, 0x81, 0x01, 0x03, 0x06, 0x04, 0x0c, 0x18, 0x38, 0x33, 
    0x7f, 0xfc, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0e, 0x38, 0xf0, 0xf0, 0xff, 0x01, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x18, 0xb0, 0xe0, 0xe0, 
    0xc0, 0xc0, 0x80, 0x81, 0x83, 0x83, 0x06, 0x0c, 0x0c, 0x18, 0x30, 0x70, 0x61, 0xc7, 0xde, 0xf8, 
    0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x00, 0x00, 
    0x00, 0x00, 0x80, 0x80, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x02, 0x06, 0x07, 0x07, 
    0x00, 0x00, 0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x7c, 0x0c, 0x06, 0x06, 0x03, 
    0x03, 0x01, 0x01, 0x01, 0x03, 0x06, 0x0c, 0x08, 0x18, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x07, 0xc6, 0xe4, 0xbe, 0x1e, 0x1f, 0x0d, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 
    0x08, 0x18, 0x10, 0x18, 0x18, 0x18, 0x08, 0x0c, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x02, 0x06, 0x06, 0xfc, 0x03, 0x03, 
    0xfe, 0x18, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0x30, 0x60, 0x60, 0xc0, 0x80, 0x80, 
    0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0xf8, 0x06, 0x06, 0x06, 0xff, 0x00, 0x00, 
    0x7f, 0x7e, 0x06, 0x06, 0x7c, 0x48, 0x08, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01};



bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        //oled_render_keylog();
            //Caps Lock status
        led_t led_state = host_keyboard_led_state();
        oled_set_cursor(0, 2);
        oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR("       "), false);
        oled_set_cursor(0, 4);
        oled_write_P(is_caps_word_on() ? PSTR("CAPS WORD") : PSTR("            "), false);
    } else {
        //oled_render_logo_custom();
        oled_write_raw_P(image, sizeof(image));
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_select_word(keycode, record, SELWORD)) { return false; }/*
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
*/
    switch (keycode) {
        case LT(0,KC_TAB):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_ESC); // Intercept hold function to send ESC
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_1):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_EXLM); // Intercept hold function to send "!"
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_2):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_AT); // Intercept hold function to send "@"
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_3):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_HASH); // Intercept hold function to send "#"
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_4):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_DLR); // Intercept hold function to send "$"
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_5):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_PERC); // Intercept hold function to send "%"
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_6):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_CIRC); // Intercept hold function to send "^"
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_7):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_AMPR); // Intercept hold function to send "&"
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case LT(0,KC_8):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_ASTR); // Intercept hold function to send "&"
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        // Below two cases configured this way due to issue registering KC_LBRC on tap instead of KC_LCBR
        case LT(0,KC_LBRC):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LCBR); // Intercept tap function to send "{"
                return false;
            }else if (record->event.pressed) {
                tap_code16(KC_LBRC); // Intercept hold function to send "["
            }
            return false;
        case LT(0,KC_RBRC):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_RCBR); // Intercept tap function to send "{"
                return false;
            }else if (record->event.pressed) {
                tap_code16(KC_RBRC); // Intercept hold function to send "["
            }
            return false;

        case LT(0,KC_NO):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_DOT); // Intercept tap function to send Dot
            } else if (record->event.pressed) {
                tap_code16(KC_COMM); // Intercept hold function to send Comma
            }
            return false;
        case M_EURSYM:
            if (record->event.pressed) {
                // when keycode M_EURSYM is pressed
                register_code(KC_RALT);
                tap_code(KC_P0);
                tap_code(KC_P1);
                tap_code(KC_P2);
                tap_code(KC_P8);
                unregister_code(KC_RALT);
            } else {
                // when keycode M_EURSYM is released
            }
            break;
    }
    return true;
}
#endif  //END OLED config


//Tap Dance config
int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static td_tap_t alttap_state = {
  .is_press_action = true,
  .state = 0
};

void alt_finished (tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: set_oneshot_layer(2, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    //case DOUBLE_TAP: set_oneshot_layer(2, ONESHOT_START); set_oneshot_layer(2, ONESHOT_PRESSED); break;       //uncomment to use layer lock
    case DOUBLE_HOLD: register_code(KC_LALT); layer_on(2); break;
  }
}

void alt_reset (tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(2); unregister_code(KC_LALT); break;
  }
  alttap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
  [ALT_OSL1]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset)
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    default:
      return true;
  }
  return true;
}
//END Tap Dance config

//Tapping term setup
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OSM(MOD_LCTL):
        case OSM(MOD_LSFT):
        case OSM(MOD_LALT):
        case OSM(MOD_RALT):
        case LT(0,KC_1):
        case LT(0,KC_2):
        case LT(0,KC_3):
        case LT(0,KC_4):
        case LT(0,KC_5):
        case LT(0,KC_6):
        case LT(0,KC_7):
            return 150;
        case LT(0,KC_TAB): 
        case LSFT_T(KC_ESC):
        case TT(1):
        case TT(2):
        case TT(3):
            return 180;
        default:
            return TAPPING_TERM;
    }
}

#ifdef RGB_MATRIX_ENABLE
//RGB Layer control
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case L_LOWER:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_effect_lower);
        break;
    case L_RAISE:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_effect_raise);
        break;
    case L_ADJUST:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_effect_adjust);
        break;
    case L_QWERTY:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_effect_qwerty);
        break;
    case L_GAME:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_effect_game);
        break;
    case L_RGB:
        rgb_matrix_mode_noeeprom(RGB_MATRIX_BAND_VAL);
        break;
    default:
        if (!is_caps_word_on()) {
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_default_effect);
        }
        else {
            rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_effect_caps_word_default);
        }
        break;
    }
  return state;
}

//Caps Lock indicator 
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(3, 100, 85, 75);
        rgb_matrix_set_color(2, 100, 85, 75);
    }
    return false;
}
//Caps Word indicator
void caps_word_set_user(bool active) {
    if (active) {
        // Turn on indicator light when Caps Word activates.
        rgb_matrix_set_color(0, 0, 70, 0);
        rgb_matrix_set_color(27, 0, 70, 0);
    }
        // Set RGB to default effect
    else {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_default_effect);
    }
}
#endif //End RGB Matrix config