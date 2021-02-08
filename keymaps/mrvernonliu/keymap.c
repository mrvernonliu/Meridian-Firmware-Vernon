/*
Copyright 2020 Holten Campbell

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

#define SWITCH_LANG M(10)
#define RESET_INDICATORS M(20)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_unified_bs_split_rshift(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,
        MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,            KC_RSFT, MO(2),
        KC_LCTL, KC_LALT,                KC_LGUI, KC_SPC,   KC_SPC,  KC_RALT,                     KC_F24, SWITCH_LANG, KC_RCTL
    ),
    [1] = LAYOUT_unified_bs_split_rshift(
        KC_GRAVE,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,        KC_BSPC,
        _______, KC_HOME,   KC_UP,  KC_END, KC_PGUP, _______, _______, _______,   KC_UP, _______, _______, _______, _______,          _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, KC_PSCR,
        _______, _______, _______,          _______,          _______,          _______,                   _______, _______, _______
    ),
    [2] = LAYOUT_unified_bs_split_rshift(
        _______, RGB_M_B, RGB_M_R, RGB_M_SW, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RESET_INDICATORS,
        _______, RGB_HUD, RGB_VAI, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, RGB_SAD, RGB_VAD, RGB_SAI, _______, _______, _______, _______, _______, _______, KC__VOLDOWN, KC__VOLUP,             KC_MEDIA_PLAY_PAUSE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_MEDIA_STOP, _______,
        _______, _______, _______,          RGB_MOD,          RGB_TOG,          _______,                   _______, _______, _______
    )
};
