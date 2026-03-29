/* © 2023–2026  Tony Zorman <mail@tony-zorman.com> (@slotThe)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define LSPR_SC  LGUI_T(KC_SCLN)
#define LALT_BR  LALT_T(KC_LBRC)
#define LSFT_INS LSFT(KC_INS)
#define OSMSFT   OSM(MOD_LSFT)
#define Z_SFT    LSFT_T(KC_Z)
#define ZE_SFT   LSFT_T(KC_0)
#define SL_SFT   RSFT_T(KC_SLSH)
#define M_LEFT   LALT(KC_LEFT)
#define M_DOWN   LALT(KC_DOWN)
#define M_UP     LALT(KC_UP)
#define M_RIGHT  LALT(KC_RIGHT)
#define CTL_BSPC LCTL(KC_BSPC)
#define M_SPC    LALT(KC_SPC)

/// Tap dance declarations

// So far, tap dances do different things on
//
//   - a single press,
//   - a double press,
//   - when held,
//
// so expect this many keys as comments.
enum tap_dances {
  ALT_BR,  // [ ] lalt  (also works shifted, which gets us { and } for free)
  CTL_PR,  // ( ) lctl
  SFT_CI,  // ^ ^ lsft  (working around LSFT_T not being able to output shifted keys)
  SFT_EX,  // ! ! lsft  (ditto)
  L1_CLY,  // { } lower
  TD_DCK,
};

#define CTLPAR TD(CTL_PR)
#define ALTBRC TD(ALT_BR)
#define SFTCRC TD(SFT_CI)
#define SFTEXL TD(SFT_EX)
#define L1CLYB TD(L1_CLY)
#define DUCK   TD(TD_DCK)

/// Macro declarations

enum custom_keycodes {
  // ->              <-    =<<   >>=   <*>  <*    *>    <$>   <&>   <|>   =>     ::
  RARR = SAFE_RANGE, LARR, LBND, RBND, APP, RAPP, LAPP, FMAP, PAMF, AALT, IMPLS, DCOL,
  // smerge-mode: C-c ^   ä    ö    ü    ß
  Cc_UP,                  AEH, OEH, UEH, SZ
};

/// Key overrides

const key_override_t *key_overrides[] = {
  &ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL), // S-BSP ≡ DEL
  // Emacs got me used to these, so let's convince other programs that
  // we are in fact sending the correct keys.
  &ko_make_basic(MOD_MASK_CTRL, KC_I, KC_TAB),     // C-i ≡ Tab
  &ko_make_basic(MOD_MASK_CTRL, KC_M, KC_ENT),     // C-m ≡ Return
};

/// Layers

enum layer_names { _COLEMAK_DH, _LOWER, _RAISE, _ADJUST };

#define LOWER    MO(_LOWER)
#define RAISE    MO(_RAISE)
#define ADJUST   MO(_ADJUST)
#define D_RAISE  LT(_RAISE, KC_DOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Colemak base layer
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     |  Q  |  W  |  F  |  P  |  B  |           |  J  |  L  |  U  |  Y  | ;+S |
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     |  A  |  R  |  S  |  T  |  G  |           |  M  |  N  |  E  |  I  |  O  |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     | S+Z |  X  |  C  |  D  |  V  | ARP | REP |  K  |  H  |  ,  |  .  | S+/ |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     | ESC | TAB | SPR | L{} | SPC | A[] | BSC | C() | L2  |  -  |  '  | RET |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
  */
  [_COLEMAK_DH] = LAYOUT(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    LSPR_SC,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
    Z_SFT,   KC_X,    KC_C,    KC_D,    KC_V,    DUCK,    QK_REP,  KC_K,    KC_H,    KC_COMM, D_RAISE, SL_SFT,
    KC_ESC,  KC_TAB,  KC_LGUI, L1CLYB,  KC_SPC,  ALTBRC,  KC_BSPC, CTLPAR,  RAISE,   KC_MINS, KC_QUOT, KC_ENT),

  /* Layer 1 (LOWER)
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-------.
     |  &  | *>  | >>= | <&> |     |           | <-  |  +  |     |  -  | M+SPC |
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-------.
     | ::  | =>  | =<< | <|> |  @  |           |  ←  |  ↓  |  ↑  |  →  |   \   |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-------.
     | !+S | <*  | <*> | <$> |     |     | MEN |  -> |  $  |  #  |  %  |  ^+S  |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-------.
     |     |     |     |     |     |     |     | C-B | L3  | ALT |     |  S-I  |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-------.
  */
  [_LOWER] = LAYOUT(
    KC_AMPR, RAPP,    RBND,    PAMF,    _______,                    LARR,    KC_PLUS, _______, KC_MINS, M_SPC,
    DCOL,    IMPLS,   LBND,    AALT,    KC_AT,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSLS,
    SFTEXL,  LAPP,    APP,     FMAP,    _______, _______, KC_APP,   RARR,    KC_DLR,  KC_HASH, KC_PERC, SFTCRC,
    _______, _______, _______, _______, _______, _______, CTL_BSPC, _______, ADJUST,  KC_LALT, _______, LSFT_INS),

  /* Layer 2 (RAISE)
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     |  %  |  7  |  8  |  9  |     |           |     |  +  |  *  |  -  |     |
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     |  :  |  4  |  5  |  6  |  =  |           |  &  |  `  |  _  |  '  |  "  |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     | 0+S |  1  |  2  |  3  |  $  |     |     |     |  !  |  ,  |  .  | ^+S |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     |     |     |     | L3  |     |     |     |  ←  |     |  ↓  |  ↑  |  →  |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
  */
  [_RAISE] = LAYOUT(
    KC_PERC, KC_7,    KC_8,    KC_9,    _______,                   _______, KC_PLUS, KC_ASTR, KC_MINS, _______,
    KC_COLN, KC_4,    KC_5,    KC_6,    KC_EQL,                    KC_AMPR, KC_GRV,  KC_UNDS, KC_QUOT, KC_DQT,
    ZE_SFT,  KC_1,    KC_2,    KC_3,    KC_DLR,  _______, _______, _______, KC_EXLM, KC_COMM, KC_DOT,  SFTCRC,
    _______, _______, _______, ADJUST,  _______, _______, _______, KC_LEFT, _______, KC_DOWN, KC_UP,   KC_RIGHT),

  /* Layer 3 (ADJUST)
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     | MUT | F7  | F8  | F9  | F10 |           | ACT |C-c ^|     |     |     |
     .-----.-----.-----.-----.-----.           .-----.-----.-----.-----.-----.
     | VUP | F4  | F5  | F6  | F11 |           | M-L | M-D | M-U | M-R | PUP |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     | VDN | F1  | F2  | F3  | F12 | BUP | BDN |     |     |     |     | PDN |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
     | ä/Ä | ö/Ö | ü/Ü |     | ß/ẞ |     |     |     |     |     |     |     |
     .-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.-----.
  */
  [_ADJUST] = LAYOUT(
    KC_MUTE, KC_F7,   KC_F8,   KC_F9,   KC_F10,                   _______, Cc_UP,   _______, _______, _______,
    KC_VOLU, KC_F4,   KC_F5,   KC_F6,   KC_F11,                   M_LEFT,  M_DOWN,  M_UP,    M_RIGHT, KC_PGUP,
    KC_VOLD, KC_F1,   KC_F2,   KC_F3,   KC_F12, KC_BRIU, KC_BRID, _______, _______, _______, _______, KC_PGDN,
    AEH    , OEH  ,   UEH  ,   _______, SZ    , _______, _______, _______, _______, _______, _______, _______)
};

/// Macros

#define _I(p,n)     if(p){n;}else                // if-then-else
#define _C(x,a...)  case x:{a;}break;            // case
#define _IP(a)     _I(record->event.pressed, a); // if pressed
#define _IPS(a)    _IP(SEND_STRING(a));          // if pressed then send
#define _CMPS(l,u) _IP(_I(keyboard_report->mods & MOD_BIT(KC_LSFT), \
                         SEND_STRING(SS_TAP(X_APP) u))              \
                       SEND_STRING(SS_TAP(X_APP) l))   // else

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  _C(RARR, _IPS("->"))         ; _C(LARR , _IPS("<-"))            ; _C(LBND, _IPS("=<<"));
  _C(RBND, _IPS(">>="))        ; _C(APP  , _IPS("<*>"))           ; _C(RAPP, _IPS("*>"));
  _C(LAPP, _IPS("<*"))         ; _C(FMAP , _IPS("<$>"))           ; _C(PAMF, _IPS("<&>"));
  _C(AALT, _IPS("<|>"))        ; _C(IMPLS, _IPS("=>"))            ; _C(DCOL, _IPS("::"));
  _C(AEH , _CMPS("\"a", "\"A")); _C(OEH  , _CMPS("\"o", "\"O"))   ; _C(UEH , _CMPS("\"u", "\"U"));
  _C(SZ  , _CMPS("ss" , "SS" )); _C(Cc_UP, _IPS(SS_LCTL("c") "^"));
  }
  return true;
};

/// Tap dance definitions

// Heavily inspired by:
//
//     https://docs.qmk.fm/?ref=blog.splitkb.com#/feature_tap_dance?id=example-4

typedef enum { TD_NONE, TD_UNKNOWN, TD_SINGLE_TAP, TD_SINGLE_HOLD, TD_DOUBLE_TAP, } td_state_t;

// Return an integer that corresponds to what kind of tap dance should
// be executed.
//
// Pressed: Whether or not the key is still being pressed. If this value
//  is true, that means the tapping term has ended, but the key is still
//  being pressed down. This generally means the key is being "held".
td_state_t cur_dance(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed)         return TD_SINGLE_HOLD;
    else                        return TD_SINGLE_TAP;
  } else if (state->count == 2) return TD_DOUBLE_TAP;
  else                          return TD_UNKNOWN;
}

#define DuckMods(n)                                                                                     \
    register_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)); tap_code(KC_V); tap_code(n); \
  unregister_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));

#define   _R0(x) {}                           // Ignore
#define   _R1(x) register_code(x)
#define   _Rl(x) layer_on(x)
#define  _R16(x) register_code16(x)
#define  _Rd1(x) DuckMods(KC_1)
#define  _Rd2(x) DuckMods(KC_2)
#define  _Rd3(x) DuckMods(KC_3)
#define _RC(n,x) _R##n(x)
#define   _U0(x) {}                           // Ignore
#define   _U1(x) unregister_code(x)
#define   _Ul(x) layer_off(x)
#define  _Ud1(x) {}
#define  _Ud2(x) {}
#define  _Ud3(x) {}
#define  _U16(x) unregister_code16(x)
#define _UC(n,x) _U##n(x)

#define DEFTAP(name,n,st,m,sh,k,dt)                                     \
  static td_state_t name##_state = TD_NONE;                             \
  void name##_finished(tap_dance_state_t *state, void *user_data) {     \
    name##_state = cur_dance(state);                                    \
    switch (name##_state) {                                             \
    _C(TD_SINGLE_TAP , _RC(n,st));                                      \
    _C(TD_SINGLE_HOLD, _RC(m,sh));                                      \
    _C(TD_DOUBLE_TAP , _RC(k,dt));                                      \
    default: break;                                                     \
    }                                                                   \
  }                                                                     \
  void name##_reset(tap_dance_state_t *state, void *user_data) {        \
    switch (name##_state) {                                             \
    _C(TD_SINGLE_TAP , _UC(n,st));                                      \
    _C(TD_SINGLE_HOLD, _UC(m,sh));                                      \
    _C(TD_DOUBLE_TAP , _UC(k,dt));                                      \
    default: break;                                                     \
    }                                                                   \
    name##_state = TD_NONE;                                             \
  }

DEFTAP(lalt_br,  1,KC_LBRC, 1,KC_LALT,  1,KC_RBRC)
DEFTAP(lctl_pr, 16,KC_LPRN, 1,KC_LCTL, 16,KC_RPRN)
DEFTAP(lsft_ci, 16,KC_CIRC, 1,KC_LSFT,  0,NULL)
DEFTAP(lsft_ex, 16,KC_EXLM, 1,KC_LSFT,  0,NULL)
DEFTAP(l1_clyb, 16,KC_LCBR, l,_LOWER , 16,KC_RCBR)
DEFTAP(duck,    d1,{}     , d2,{}    , d3,{})

tap_dance_action_t tap_dance_actions[] = {
  [ALT_BR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lalt_br_finished, lalt_br_reset),
  [CTL_PR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lctl_pr_finished, lctl_pr_reset),
  [SFT_CI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsft_ci_finished, lsft_ci_reset),
  [SFT_EX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsft_ex_finished, lsft_ex_reset),
  [L1_CLY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l1_clyb_finished, l1_clyb_reset),
  [TD_DCK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, duck_finished   , duck_reset   ),
};
