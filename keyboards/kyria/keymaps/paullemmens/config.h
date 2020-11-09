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

#pragma once

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  /* #define OLED_SCROLL_TIMEOUT 5000 */
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_SLEEP
  /* #define RGBLIGHT_SPLIT */
#endif

// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
/* #define ENCODER_RESOLUTION 2 */

// The Leader key allows to flexibly assign macros to key sequences.
/* #define LEADER_PER_KEY_TIMING */
/* #define LEADER_TIMEOUT 350 */

// For home row mods
#define TAPPING_TERM 300
// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT
/* #define PERMISSIVE_HOLD */
/* #define TAPPING_FORCE_HOLD */
#define TAPPING_TOGGLE 2

// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
/* #define EE_HANDS */

// Encoder settings.
// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10

#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION 2
// From j-inc kyria keyboard.
/* #ifdef RGBLIGHT_ENABLE */
/*     #define RGBLIGHT_LED_MAP {0,1,2,9,8,7,4,3,5,6,19,18,17,10,11,12,15,16,14,13} // Orients Kyria LEDs to a circle around both halves. */
/*     //#define RBGLIGHT_LED_MAP {9,8,6,7,5,3,2,4,1,0,10,12,13,11,14,16,17,15,18,19} // Orients Kyria LEDs for a left half-right half columnar progression. */
/*     #define RGBLIGHT_EFFECT_RAINBOW_SWIRL */
/*     //#define RGBLIGHT_EFFECT_STATIC_GRADIENT */
/*     #define RGBLIGHT_SLEEP */
/* #endif */
