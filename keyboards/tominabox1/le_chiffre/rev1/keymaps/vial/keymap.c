/*
Le chiffre rev2
*/

#include QMK_KEYBOARD_H
#include "lib/lib8tion/lib8tion.h"

enum layers{
  _BASE,
  _NUM_SYM,
  _NAV,
  //_PAD,
  _META
};

enum custom_keycodes{
  RGBRST = SAFE_RANGE,
};

#define KC_NAV_SPC LT(_NAV, KC_SPC)
#define KC_NUM_BSPC LT(_NUM_SYM, KC_BSPC)
//#define KC_GZ LGUI_T(KC_Z)
//#define KC_AV LALT_T(KC_V)
//define KC_CR LCTL_T(KC_R)
#define KC_SF LSFT_T(KC_F)
#define KC_SJ RSFT_T(KC_J)
//#define KC_CU RCTL_T(KC_U)
//#define KC_AM RALT_T(KC_M)
//#define KC_GSCLN RGUI_T(KC_SCLN)
//#define KC_GSLSH RGUI_T(KC_SLSH)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,  KC_MUTE,  KC_Y,   KC_U,    KC_I,   KC_O,     KC_P,
    KC_A,   KC_S,  KC_D,   KC_SF,   KC_G,            KC_H,  KC_SJ,    KC_K,   KC_L,  KC_QUOT,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,            KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH,
                         KC_LCTL, KC_NUM_BSPC,            KC_NAV_SPC, KC_RALT
  ),

  [_NUM_SYM] = LAYOUT(
        KC_1,  KC_2,     KC_3,     KC_4,      KC_5,  KC_MPLY,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_EXLM,  KC_AT,  KC_HASH,   KC_DLR,   KC_PERC,            KC_CIRC,  KC_AMPR,  KC_ASTR, KC_EQUAL,  KC_MINS,
    KC_BSLS, KC_UNDS,   KC_LCBR,  KC_LBRC,  KC_LPRN,            KC_RPRN,  KC_RBRC,  KC_RCBR,   KC_DOT,   KC_GRV,
                                KC_TRNS,   KC_TRNS,            KC_TRNS,  KC_TRNS
  ),

  [_NAV] = LAYOUT(
    KC_WBAK,  KC_PGDN,	 KC_UP,  KC_PGUP,   KC_WFWD, KC_WHOM, KC_WBAK,  KC_PGDN,    KC_UP,  KC_PGUP,  KC_WFWD,
    KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_END,           KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
    KC_LSFT,  KC_CUT,  KC_COPY,  KC_PASTE,  KC_UNDO,                KC_MINS,    KC_RO,  KC_COMM,   KC_DOT,  KC_RSFT,
                                  KC_TRNS,KC_TRNS,           KC_TRNS,  KC_TRNS
  ),

  [_META] = LAYOUT(
     RESET,  KC_F19,  KC_F20,  KC_F21,  KC_F22,    RGB_TOG,   KC_F1,  KC_F2,    KC_F3,  KC_F4,  KC_SLEP,
    RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  KC_F23,           KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_PAUS,
    RGB_RMOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  KC_F24,           KC_F9,    KC_F10,  KC_F11,   KC_F12,  KC_BSLS,
                                  KC_TRNS,KC_TRNS,           KC_TRNS,  KC_TRNS
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _NUM_SYM, _NAV, _META);
     return state;
   }



void rgb_matrix_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t i, uint8_t mode) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    switch (mode) {
        case 1:  // breathing
        {
            uint8_t speed = rgb_matrix_config.speed;
            uint16_t time = scale16by8(g_rgb_timer, speed / 8);
            hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb       = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

            break;
        }
        default:  // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            //RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
            break;
        }
    }
}

void rgb_matrix_indicators_user() {
	if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_helper(21, 255, 100, 9, 1);
        rgb_matrix_helper(21, 255, 100, 10, 1);
    } else {
        rgb_matrix_helper(0, 0, 0, 9, 0);
        rgb_matrix_helper(0, 0, 0, 10, 0);
    }

switch (get_highest_layer(layer_state)) {
    case _NUM_SYM:
        rgb_matrix_helper(148, 255, 70, 9, 0);
        break;
    case _NAV:
        rgb_matrix_helper(85, 255, 70, 10, 0);
        break;
    case _META:
        rgb_matrix_helper(148, 255, 70, 9, 0);
        rgb_matrix_helper(85, 255, 70, 10, 0);
        break;
    //default:
    //rgb_matrix_helper(0, 0, 0, 9, 0);
    //rgb_matrix_helper(0, 0, 0, 10, 0);

	//case _:
		//rgb_matrix_helper(h, 255, v, i, 0);
       // break;
	}
}

