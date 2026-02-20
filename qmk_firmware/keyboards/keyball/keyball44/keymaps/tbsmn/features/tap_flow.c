#include "tap_flow.h"

#ifndef TAP_FLOW_TERM
#    define TAP_FLOW_TERM 150
#endif

static uint16_t prev_keycode = KC_NO;
static uint32_t prev_event_time = 0;

// Default: filter only on letter/punctuation keys, same as upstream
__attribute__((weak)) bool is_tap_flow_key(uint16_t keycode) {
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            break;
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
            break;
    }
    switch (keycode) {
        case KC_A ... KC_Z:
        case KC_COMM:
        case KC_DOT:
        case KC_SCLN:
        case KC_SLSH:
        case KC_SPC:
            return true;
    }
    return false;
}

__attribute__((weak)) uint16_t get_tap_flow_term(uint16_t keycode,
                                                  keyrecord_t* record,
                                                  uint16_t prev_kc) {
    if (is_tap_flow_key(keycode) && is_tap_flow_key(prev_kc)) {
        return TAP_FLOW_TERM;
    }
    return 0;
}

bool process_tap_flow(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        if (IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode)) {
            uint16_t term = get_tap_flow_term(keycode, record, prev_keycode);
            if (term > 0 &&
                TIMER_DIFF_32(record->event.time, prev_event_time) < term) {
                // Force tap behavior by setting tap count > 0
                record->tap.count = 1;
                record->tap.interrupted = true;
            }
        }
        prev_keycode = keycode;
        prev_event_time = record->event.time;
    }
    return true;
}
