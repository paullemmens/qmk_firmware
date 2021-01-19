/*
Copyright 2018 Mattia Dal Ben <matthewdibi@gmail.com>

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

#pragma once

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_ANIMATIONS
    /* #define RGBLIGHT_EFFECT_STATIC_LIGHT */
    /* #define RGBLIGHT_EFFECT_BREATHING */
    /* #define RGBLIGHT_EFFECT_RAINBOW_MOOD */
    /* #define RGBLIGHT_EFFECT_RAINBOW_SWIRL */
    #undef RGBLED_NUM
    #define RGBLED_NUM 14
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_SLEEP
    #define RGBLIGHT_SPLIT
#endif

#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY
// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD

/* #define TAPPING_FORCE_HOLD */
#define TAPPING_TOGGLE 2
