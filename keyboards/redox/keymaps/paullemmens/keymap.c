#include QMK_KEYBOARD_H

#ifdef VELOCIKEY_ENABLE
#include "velocikey.h"
#endif

// Tap dance stuff
#ifdef TAP_DANCE_ENABLE
enum {
    TD_5_6,
    TD_6_7,
    TD_PERC_CIRC,
    TD_AMPR_CIRC
};

qmk_tap_dance_action_t tap_dance_actions[] = {
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
#define G_LSHFT     LSFT_T(KC_G)
#define V_LSHFT     LSFT_T(KC_V)
#define V_LCTRL     LCTL_T(KC_V)
#define N_RSHFT     RSFT_T(KC_N)
#define N_RCTRL     RCTL_T(KC_N)
#define M_RSHFT     RSFT_T(KC_M)
#define M_RCTRL     RCTL_T(KC_M)
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
#define H_LOWER     LT(_LOWER, KC_H)
#define J_RAISE     LT(_RAISE, KC_J)
#define U_ADJST     LT(_ADJUST, KC_U)

// https://precondition.github.io/home-row-mods#using-non-basic-keycodes-in-mod-taps
enum custom_keycodes {
    MT_OUMLA = SAFE_RANGE,
    MT_EACUT,
    MT_RCBR,
    QWERTY,
    LOWER,
    RAISE,
    ADJUST,
};
#define OU_LCTL LCTL_T(MT_OUMLA)
#define EA_LSFT LSFT_T(MT_EACUT)
#define RB_LCTL LCTL_T(MT_RCBR)

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

// Shortcut to make keymap more readable
#define RAISE_L MO(_RAISE)
#define T_RAI_L TT(_RAISE)
#define KC_LOSP LT(_LOWER, KC_SPC)
#define KC_RALB LT(_RAISE, KC_LBRC)
#define KC_RARB LT(_RAISE, KC_RBRC)

#define KC_ADJ6 LT(_ADJUST, KC_6)
#define KC_ADSL LT(_ADJUST, KC_BSLS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_BSPC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,R_ADJST ,KC_T    ,KC_ADJ6 ,                          KC_ADSL ,KC_Y    ,U_ADJST ,KC_I    ,KC_O    ,KC_P    ,KC_BSPC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC  ,KC_A    ,KC_S    ,D_LSHFT ,F_RAISE ,KC_G    ,KC_RALB ,                          KC_RARB ,H_LOWER ,J_RAISE ,K_RSHFT ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,LGUI__Z ,KC_X    ,KC_C    ,V_LCTRL ,KC_B    ,T_RAI_L ,SGUI_LWR,        DEL_RAI ,BS_LALT ,KC_N    ,M_RCTRL ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTRL,RAISE_L ,KC_LGUI ,KC_LALT ,     KC_LOSP ,    KC_LCTRL,GUI_LWR ,        KC_RCTRL,ENT_RSF ,    KC_SPC  ,     KC_RALT ,KC_APP  ,KC_RCTRL,RAISE_L
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,_______ ,                          _______ ,KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_MINS ,KC_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_F11  ,KC_F12  ,EA_LSFT ,E_UMLAU ,_CIRCFL ,_______ ,                          _______ ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,S(KC_BSLS),KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_F10  ,_GRAVE_ ,_ACUTE_ ,OU_LCTL ,EURO    ,_______ ,_______ ,        _______ ,_______ ,KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END  ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,_______ ,                          _______ ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_MINS ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_GRV  ,_______ ,                          _______ ,KC_LBRC ,KC_4    ,KC_5    ,KC_6    ,KC_PPLS ,KC_PAST ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_PERC ,KC_CIRC ,KC_LCBR ,RB_LCTL ,KC_TILD ,KC_LBRC ,KC_RBRC ,        _______ ,_______ ,KC_RBRC ,KC_1    ,KC_2    ,KC_3    ,_______ ,KC_PSLS ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    KC_0    ,     KC_PDOT ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     VLK_TOG ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,_______ ,                          _______ ,KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_UNDS ,KC_UNDS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LOCK ,RGB_SAI ,RGB_HUI ,RGB_VAI ,RGB_SPI ,RGB_MOD ,_______ ,                          _______ ,KC_BRID ,KC_BRIU ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG ,_______ ,_______ ,_______ ,_______ ,_______ ,RGB_M_P ,RGB_M_B ,        RGB_M_R ,RGB_M_SW,RGB_M_SN,RGB_M_K ,RGB_M_X ,RGB_M_G ,RGB_M_T ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_MUTE ,_______ ,_______ ,_______ ,     _______ ,    KC_NLCK ,KC_SLCK ,        KC_INS  ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
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
                    // the 16 bit version of the `tap_code` function is used here
                    // because KC_HASH is a non-basic keycode.
                    tap_code16(ALGR(KC_E));
                }
                // do not continue with default tap action
                // if the MT was pressed or released, but not held
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
    }

    return true;
};
