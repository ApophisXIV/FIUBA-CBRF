#include "switch_rf.h"

action_fn open(switch_rf_t *switch_rf) {
    digitalWrite(switch_rf->ctrl_pin, OPEN_STATE);
}

action_fn close(switch_rf_t *switch_rf) {
    digitalWrite(switch_rf->ctrl_pin, CLOSE_STATE);
}

bool rf_switch_init(switch_rf_t *switch_rf, uint8_t gpio, bool initial_state) {
    switch_rf->close = close;
    switch_rf->open  = open;

    digitalWrite(gpio, initial_state);
    switch_rf->is_open = digitalRead(gpio);
}
