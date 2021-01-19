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
    MT_RCBR
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

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Shortcut to make keymap more readable
#define RAISE_L MO(_RAISE)

#define KC_ALAS LALT_T(KC_PAST)
#define KC_CTPL LCTL_T(KC_BSLS)

#define KC_NAGR LT(_NAV, KC_GRV)
#define KC_NAMI LT(_NAV, KC_MINS)

#define KC_ADEN LT(_ADJUST, KC_END)
#define KC_ADPU LT(_ADJUST, KC_PGUP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NAGR ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_NAMI ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,SYM_L   ,                          SYM_L   ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_LBRC ,                          KC_RBRC ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LGUI ,KC_PPLS ,KC_PMNS ,KC_ALAS ,     KC_CTPL ,    KC_BSPC ,KC_DEL  ,        KC_ENT  ,KC_SPC  ,    KC_RALT ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_PIPE ,_______ ,                          _______ ,KC_PSLS ,KC_P7 ,KC_P8 ,KC_P9 ,KC_PMNS ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_HASH ,KC_DLR  ,KC_LBRC ,KC_RBRC ,KC_GRV  ,_______ ,                          _______ ,KC_PAST ,KC_P4 ,KC_P5 ,KC_P6 ,KC_PPLS ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_PERC ,KC_CIRC ,KC_LPRN ,KC_RPRN ,KC_TILD ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,KC_P1 ,KC_P2 ,KC_P3 ,KC_PENT ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    KC_P0 ,     KC_P0 ,KC_PDOT ,KC_PENT ,XXXXXXX 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,KC_MS_U ,XXXXXXX ,KC_WH_U ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D ,XXXXXXX ,_______ ,                          _______ ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,_______ ,        _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     KC_BTN1 ,    KC_BTN2 ,_______ ,        _______ ,_______ ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,RESET   ,RGB_M_P ,RGB_TOG ,RGB_MOD ,RGB_HUD ,RGB_HUI ,                          RGB_SAD ,RGB_SAI ,RGB_VAD ,RGB_VAI ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX 
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
