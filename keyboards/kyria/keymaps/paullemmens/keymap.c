/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

#ifdef WPM_ENABLE
#include <stdio.h>
char wpm_str[10];
#endif
#ifdef WPM_GRAPH
uint16_t wpm_graph_timer = 0;
#endif

#ifdef VELOCIKEY_ENABLE
#include "velocikey.h"
#endif

#ifdef ENCODER_ENABLE
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
#endif

// Tap dance stuff
#ifdef TAP_DANCE_ENABLE
enum {
    TD_5_6,
    TD_6_7,
    TD_PERC_CIRC,
    TD_AMPR_CIRC
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_5_6] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_6),
    [TD_6_7] = ACTION_TAP_DANCE_DOUBLE(KC_6, KC_7),
    [TD_PERC_CIRC] = ACTION_TAP_DANCE_DOUBLE(KC_PERC, KC_CIRC),
    [TD_AMPR_CIRC] = ACTION_TAP_DANCE_DOUBLE(KC_AMPR, KC_CIRC)
};
#endif

// Personal key definitions:
// Very special combinations
#define SGUI_LWR    LM(_LOWER, MOD_LSFT|MOD_LGUI)
#define OSX_DSP     LM(_LOWER, MOD_LCTL|MOD_LALT|MOD_LGUI)
#define GUI_LWR     LM(_LOWER, MOD_LGUI)
#define O_ACUTE     ALGR(KC_P)
#define O_UMLAU     ALGR(KC_O)
#define E_ACUTE     ALGR(KC_E)
#define E_UMLAU     ALGR(KC_W)
#define I_UMLAU     ALGR(KC_I)
#define EURO        ALGR(KC_5)
#define _ACUTE_     ALGR(KC_QUOTE)
#define _GRAVE_     ALGR(KC_GRAVE)
#define _UMLAU_     ALGR(S(KC_QUOTE))
#define _CIRCFL     ALGR(KC_CIRC)
// Home row mods
#define LGUI__Z     LGUI_T(KC_Z)
#define Z_LCTRL     LCTL_T(KC_Z)
#define G_LSHFT     LSFT_T(KC_G)
#define V_LSHFT     LSFT_T(KC_V)
#define V_LCTRL     LCTL_T(KC_V)
#define B_LCTRL     LCTL_T(KC_B)
#define V__LCMD     LCMD_T(KC_V)
#define N_RSHFT     RSFT_T(KC_N)
#define N_RCTRL     RCTL_T(KC_N)
#define M_RSHFT     RSFT_T(KC_M)
#define M_RCTRL     RCTL_T(KC_M)
#define M__RCMD     RCMD_T(KC_M)
#define D_LCTRL     LCTL_T(KC_D)
#define D_LSHFT     LSFT_T(KC_D)
#define K_RCTRL     RCTL_T(KC_K)
#define K_RSHFT     RSFT_T(KC_K)
#define S__LALT     LALT_T(KC_S)
#define L__LALT     LALT_T(KC_L)
#define BS_LALT     LALT_T(KC_BSPC)
#define ENT_RSF     RSFT_T(KC_ENT)
// Layer toggles
#define R_ADJST     LT(_ADJUST, KC_R)
#define F_RAISE     LT(_RAISE, KC_F)
#define SPC_LWR     LT(_LOWER, KC_SPC)
#define DEL_RAI     LT(_RAISE, KC_DEL)
#define ESC_RAI     LT(_RAISE, KC_ESC)
#define H_LOWER     LT(_LOWER, KC_H)
#define G_LOWER     LT(_LOWER, KC_G)
#define J_RAISE     LT(_RAISE, KC_J)
#define U_ADJST     LT(_ADJUST, KC_U)
#define MACOS_L     DF(_MACOS)
#define DEFAU_L     DF(_QWERTY)

// https://precondition.github.io/home-row-mods#using-non-basic-keycodes-in-mod-taps
enum custom_keycodes {
    MT_OUMLA = SAFE_RANGE,
    MT_EACUT,
    MT_RCBR
};
#define OU_LCTL LCTL_T(MT_OUMLA)
#define EA_LSFT LSFT_T(MT_EACUT)
#define RB_LCTL LCTL_T(MT_RCBR)

enum layers {
    _QWERTY = 0,
    _MACOS,
    _LOWER,
    _RAISE,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |  E   |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  BS    |
 * |        |      |      |      |adjust|      |                              |      |adjust|      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  ESC   |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |        |      |      | LShft| raise|lower |                              | lower| raise|RShift|      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |  C   |   V  |   B  | Esc  |SLGui+|  | Del  | LAlt |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * |        | LGui |      |      | LCtrl|      | Raise| lower|  | Raise| BS   |      | RCtrl|      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | LGUI | LAlt | Space| LCtrl| LGui+|  | RCtrl| Enter| Space| AltGr| Menu |
 *                        |      |      | lower|      | lower|  |      |RSHift|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      KC_TAB,  KC_Q,    KC_W, KC_E,    R_ADJST, KC_T,                                            KC_Y,    U_ADJST, KC_I,    KC_O,   KC_P,    KC_BSPC,
      KC_ESC,  KC_A,    KC_S, D_LSHFT, F_RAISE, G_LOWER,                                         H_LOWER, J_RAISE, K_RSHFT, KC_L,   KC_SCLN, KC_QUOT,
      KC_LSFT, LGUI__Z, KC_X, KC_C,    V_LCTRL, KC_B,    ESC_RAI,  SGUI_LWR,  DEL_RAI,  BS_LALT, KC_N,    M_RCTRL, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                              KC_LGUI, KC_LALT, SPC_LWR, KC_LCTRL, GUI_LWR,   KC_RCTRL, ENT_RSF, KC_SPC,  KC_RALT, KC_APP
    ),
/*
 * MacOS: specific keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |  V   |  B   |      | Move |  |      |      |  N   |  M   |      |      |      |        |
 * |        |      |      |      | Cmd  | Ctrl |      |window|  |      |      | RCtrl| Cmd  |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |Option|      | Cmd  |      |  | Cmd  |      |      | RAlt|      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_MACOS] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, V__LCMD, B_LCTRL, _______, OSX_DSP, _______, _______, N_RCTRL, M__RCMD, _______, _______, _______, _______,
                                 _______, KC_LOPT, _______, KC_LCMD, _______, KC_RCMD, _______, _______, KC_RALT, _______
    ),
/*
 * Lower Layer: F-keys, Numpad
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |                              |  F6  |  F7  |  F8  |  F9  | - _  |  = +   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F11 |  F12 |   é  |   ë  |   ô  |                              | Left | Down |  Up  | Right|  |   |  \ |   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F10 |  ò   |   ó  |   ö  |   €  |      |      |  |      |      | Home | PgDn | PgUp |  End |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      _______,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_MINS,    KC_EQL,
      TO(_QWERTY), KC_F11,  KC_F12,  EA_LSFT, E_UMLAU, _CIRCFL,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, S(KC_BSLS), KC_BSLS,
      _______,     KC_F10,  _GRAVE_, _ACUTE_, OU_LCTL, EURO,    _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,    _______,
                                     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Raise Layer: numbers, arrows, and some symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  1   |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   | - _  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |  [   |  4   |  5   |  6   |  +   |   *    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  {   |  }   |  ~   |  [   |   ]  |  |      |      |  ]   |  1   |  2   |  3   |      |   /    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |  0   |  .   |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8, KC_9, KC_MINS, _______,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                      KC_LBRC, KC_4,    KC_5, KC_6, KC_PPLS, KC_PAST,
      _______, KC_PERC, KC_CIRC, KC_LCBR, RB_LCTL, KC_TILD, KC_LBRC, KC_RBRC, _______, _______, KC_RBRC, KC_1,    KC_2, KC_3, _______, KC_PSLS,
                                 _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_PDOT, _______
    ),
/*
 * Adjust Layer: Symbols, volume, locks, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   VLK  |  !   |  @   |  #   |  $   |  %   |                              |  ^   |   &  |   *  |   (  |  _   |   _    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  CAPS  | SAI  | HUI  | VAI  | Eff+ | MOD  |                              | BrDn | BrUp |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  RTOG  |      |      |      |      |      | RGB P| RGB B|  | RGB R|RGB SW|RGB SN| RGB K| RGB X| RGB G| RGB T|        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | Mute |      |      | NumLk|Scrllk|  |Insert| OSX  | QWERT|      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      VLK_TOG, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                      KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN, KC_UNDS, KC_UNDS,
      KC_CAPS, RGB_SAI, RGB_HUI, RGB_VAI, RGB_SPI, RGB_MOD,                                      KC_BRID,  KC_BRIU, _______, _______, _______, _______,
      RGB_TOG, _______, _______, _______, _______, _______, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, _______,
                                 KC_MUTE, _______, _______, KC_NLCK, KC_SLCK, KC_INS,  MACOS_L,  DEFAU_L,  _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case K_RSHFT:
            return TAPPING_TERM + 75;
        case J_RAISE:
            return TAPPING_TERM + 25;
        case N_RCTRL:
        case M_RCTRL:
            return TAPPING_TERM + 100;
        default:
            return TAPPING_TERM;
    }
}
#endif

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_BSPC):
            return true;
        default:
            return false;
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OU_LCTL:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    // send advanced keycode, etc.
                    // the 16 bit version of the `tap_code` function is used here
                    // because KC_HASH is a non-basic keycode.
                    tap_code16(ALGR(S(KC_QUOTE)));
                }
                // do not continue with default tap action
                // if the MT was pressed or released, but not held
                return false;
            }
            break;
        case EA_LSFT:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    // send advanced keycode, etc.
                    if (get_highest_layer(default_layer_state) == _MACOS) {
                        SEND_STRING(SS_RALT("ee"));
                    } else {
                        // the 16 bit version of the `tap_code` function is used here
                        // because KC_HASH is a non-basic keycode.
                        tap_code16(ALGR(KC_E));
                    }
                }
                // do not continue with default tap action
                // if the MT was pressed or released, but not held
                return false;
            }
            break;
        case _ACUTE_: // This is ugly, because it was originally intended as a single key press
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    if (get_highest_layer(default_layer_state) == _MACOS) {
                        SEND_STRING(SS_RALT("eo"));
                    } else {
                        // the 16 bit version of the `tap_code` function is used here
                        // because KC_HASH is a non-basic keycode.
                        tap_code16(ALGR(KC_QUOTE));
                    }
                }
                return false;
            }
            break;
        case RB_LCTL:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    // send advanced keycode, etc.
                    // the 16 bit version of the `tap_code` function is used here
                    // because KC_HASH is a non-basic keycode.
                    tap_code16(KC_RCBR);
                }
                // do not continue with default tap action
                // if the MT was pressed or released, but not held
                return false;
            }
            break;
        case KC_HOME:
            if (get_highest_layer(default_layer_state) == _MACOS) {
                if (record->event.pressed) {
                    tap_code16(LCMD(KC_LEFT));
                }
                return false;
            }
            break;
        case KC_END:
            if (get_highest_layer(default_layer_state) == _MACOS) {
                if (record->event.pressed) {
                    tap_code16(LCMD(KC_RIGHT));
                }
                return false;
            }
            break;
        default:
            return true;
    }

    return true;
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0"), false);
    if (get_highest_layer(default_layer_state) == _MACOS) {
        oled_write_P(PSTR(" OSX"), false);
    }
    else {
        oled_write_P(PSTR("    "), false);
    }
    #ifdef VELOCIKEY_ENABLE
    if (velocikey_enabled()) {
        oled_write_P(PSTR(" VLK"), false);
    }
    #endif
    oled_write_P(PSTR("\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCR ") : PSTR("    "), false);

    #ifdef WPM_ENABLE
        // Write WPM
        sprintf(wpm_str, "WPM: %03d", get_current_wpm());
        /* oled_write_P(PSTR("\n"), false); */
        oled_write(wpm_str, false);
    #endif
}

#ifdef WPM_GRAPH
static uint8_t zero_bar_count = 0;
static uint8_t bar_count = 0;
#define WPM_CUTOFF 20

static void render_wpm_graph(void) {
    uint8_t bar_height = 0;
    uint8_t bar_segment = 0;

    if (wpm_graph_timer == 0) {
        render_kyria_logo();
        wpm_graph_timer = timer_read();
        return;
    }

    if(timer_elapsed(wpm_graph_timer) > 500) {
        wpm_graph_timer = timer_read();

        if(OLED_DISPLAY_HEIGHT == 64)
            bar_height = get_current_wpm() / 2;
        if(OLED_DISPLAY_HEIGHT == 32)
            bar_height = get_current_wpm() / 4;
        if(bar_height > OLED_DISPLAY_HEIGHT)
            bar_height = OLED_DISPLAY_HEIGHT;

        if(bar_height == 0) {
            // keep track of how many zero bars we have drawn.  If
            // there is a whole screen worth, turn the display off and
            // wait until there is something to do
            if (zero_bar_count > OLED_DISPLAY_WIDTH / 5) {
                /* oled_off(); */
                render_kyria_logo();
                return;
            }
            zero_bar_count++;
        } else
            zero_bar_count=0;

        oled_pan(false);
        bar_count++;
        for (uint8_t i = (OLED_DISPLAY_HEIGHT / 8); i > 0; i--) {
            if (bar_height > 7) {
                if (i % 2 == 1 && bar_count % 3 == 0)
                    bar_segment = 254;
                else
                    bar_segment = 255;
                bar_height -= 8;
            } else {
                switch (bar_height) {
                case 0:
                    bar_segment = 0;
                    break;

                case 1:
                    bar_segment = 128;
                    break;

                case 2:
                    bar_segment = 192;
                    break;

                case 3:
                    bar_segment = 224;
                    break;

                case 4:
                    bar_segment = 240;
                    break;

                case 5:
                    bar_segment = 248;
                    break;

                case 6:
                    bar_segment = 252;
                    break;

                case 7:
                    bar_segment = 254;
                    break;
                }
                bar_height = 0;

                if (i % 2 == 1 && bar_count % 3 == 0)
                    bar_segment++;
            }
            oled_write_raw_byte(bar_segment, (i-1) * OLED_DISPLAY_WIDTH);
        }
    }
}
#endif // WPM_GRAPH

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        #ifdef WPM_GRAPH
            render_wpm_graph();
        #else
            render_kyria_logo();
        #endif
    }
}
#endif // OLED_DRIVER_ENABLE

#ifdef ENCODER_ENABLE
// Use code from plattfot as example to make layer specifc encoder actions
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            // Move and move to windows in i3-wm or using Rectangle in macOS.
            case _RAISE:
                if (clockwise) {
                    if (get_highest_layer(default_layer_state) == _MACOS) {
                        tap_code16(LCTL(LOPT(LCMD(KC_RIGHT))));
                    }
                    else {
                        tap_code16(LGUI(KC_RIGHT));
                    }
                } else {
                    if (get_highest_layer(default_layer_state) == _MACOS) {
                        tap_code16(LCTL(LOPT(LCMD(KC_LEFT))));
                    }
                    else {
                        tap_code16(LGUI(KC_LEFT));
                    }
                }
                break;
            // Volume control on adjust
            case _ADJUST:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            // Alt-tab code from https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder-
            default:
                if (clockwise) {
                    if (!is_alt_tab_active) {
                        is_alt_tab_active = true;
                        if (get_highest_layer(default_layer_state) == _MACOS) {
                            register_code(KC_LCMD);
                        }
                        else {
                            register_code(KC_LALT);
                        }
                    }
                    alt_tab_timer = timer_read();
                    tap_code16(KC_TAB);
                } else {
                    // TODO: a bit weird: first do clockwise turn so you can counter clockwise to another app, otherwise
                    // S-tab is sent in the current application. Is also convenient to some degree so ...
                    alt_tab_timer = timer_read();
                    tap_code16(S(KC_TAB));
                }
                break;
        }
    }
    else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            default:
                // Page up/Page down
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
        }
    }
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
      if (get_highest_layer(default_layer_state) == _MACOS) {
          unregister_code(KC_LCMD);
      }
      else {
          unregister_code(KC_LALT);
      }
      is_alt_tab_active = false;
    }
  }
}
#endif
