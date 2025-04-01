#include "switch_rf.h"

typedef void (*action_fn)(switch_rf_t *);

typedef struct {
    bool is_open;
    uint8_t ctrl_pin;

    action_fn open;
    action_fn close;
} switch_rf_t;

static action_fn open(switch_rf_t *switch_rf) {
    if (switch_rf == NULL) return;
    digitalWrite(switch_rf->ctrl_pin, OPEN_STATE);
    switch_rf->is_open = digitalRead(switch_rf->ctrl_pin);
}

static action_fn close(switch_rf_t *switch_rf) {
    if (switch_rf == NULL) return;
    digitalWrite(switch_rf->ctrl_pin, CLOSE_STATE);
    switch_rf->is_open = digitalRead(switch_rf->ctrl_pin);
}

void rf_switch_init(switch_rf_t *switch_rf, uint8_t gpio, bool initial_state) {
    switch_rf->close = close;
    switch_rf->open  = open;

    pinMode(gpio, OUTPUT);
    digitalWrite(gpio, initial_state);

    switch_rf->is_open  = digitalRead(gpio);
    switch_rf->ctrl_pin = gpio;

    switch_rf->open  = open;
    switch_rf->close = close;
}
