#pragma once
#include "quantum.h"

#ifndef TAP_FLOW_TERM
#  define TAP_FLOW_TERM  150
#endif  // TAP_FLOW_TERM

bool process_tap_flow(uint16_t keycode, keyrecord_t* record);

// Optional: override this to customize which keys Tap Flow acts on
bool is_tap_flow_key(uint16_t keycode);

// Optional: override this to customize the timeout per key
uint16_t get_tap_flow_term(uint16_t keycode, keyrecord_t* record,
                           uint16_t prev_keyccsode);
