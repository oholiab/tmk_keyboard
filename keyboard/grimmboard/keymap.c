/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"


/* Need to find space for:
 * ENTER: FN SHIFT
 * BS: FN SPACE
 * DEL: ALT SPACE
 * SUPER: FN CTRL
 * ARROWS: FN WASD
 * PGUP/DOWN: FN JK
 * HOME/END: FN HL
 * TAB: FN Q
 * ESC: SINGLE CTRL/FN ALT
 * F1-12: FN top row
 */
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    {
      {FN,    KC_1,	KC_2,	KC_3,	KC_4,	KC_5,	KC_6,	KC_7,	KC_8,			KC_9,			KC_0,			KC_MINS,	KC_EQL},
      {SHIFT, KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,	KC_Y,	KC_U,	KC_I,			KC_O,			KC_P,			KC_LBRC,	KC_RBRC},
      {CTRL,  KC_A,	KC_S,	KC_D,	KC_F,	KC_G,	KC_H,	KC_J,	KC_K,			KC_L,			KC_SCLN,	KC_QUOT,  KC_BSLS},
      {ALT,   KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,	KC_N,	KC_M,	KC_COMMA,	KC_DOT, 	KC_SLSH,  KC_GRV,   KC_SPACE},
    },
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
};



#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
    if (layer < KEYMAPS_SIZE) {
        return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
    } else {
        // fall back to layer 0
        return pgm_read_byte(&keymaps[0][(key.row)][(key.col)]);
    }
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    } else {
        action.code = ACTION_NO;
    }
    return action;
}
