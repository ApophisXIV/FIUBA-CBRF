#include "switch_rf.h"

#define MAX_INSTANCES 3

static switch_rf_t *rf_instances[MAX_INSTANCES] = {0};

struct switch_rf {
    bool is_open;
    uint8_t ctrl_pin;
};

static void rf_switch_write(switch_rf_t *hswitch_rf, bool state) {
    if (hswitch_rf == NULL) return;
    digitalWrite(hswitch_rf->ctrl_pin, state);
    hswitch_rf->is_open = digitalRead(hswitch_rf->ctrl_pin);
}

static bool rf_switch_register(switch_rf_t *hswitch_rf) {
    if (hswitch_rf == NULL) return false;

    for (uint8_t i = 0; i < MAX_INSTANCES; i++) {
        if (rf_instances[i] == NULL) {
            rf_instances[i] = hswitch_rf;
            return true;
        }
        if (rf_instances[i]->ctrl_pin == hswitch_rf->ctrl_pin) {
            return false;
        }
    }
    return false;
}

static bool rf_switch_unregister(switch_rf_t *hswitch_rf) {
    if (hswitch_rf == NULL) return false;

    for (uint8_t i = 0; i < MAX_INSTANCES; i++) {
        if (rf_instances[i] != NULL && rf_instances[i]->ctrl_pin == hswitch_rf->ctrl_pin) {
            rf_instances[i] = NULL;
            return true;
        }
    }
    return false;
}

void rf_switch_open(switch_rf_t *hswitch_rf) {
    rf_switch_write(hswitch_rf, OPEN_STATE);
}

void rf_switch_close(switch_rf_t *hswitch_rf) {
    rf_switch_write(hswitch_rf, CLOSE_STATE);
}

bool rf_switch_is_open(switch_rf_t *hswitch_rf) {
    return hswitch_rf->is_open;
}

bool rf_switch_init(switch_rf_t *hswitch_rf, uint8_t gpio, bool initial_state) {

    pinMode(gpio, OUTPUT);
    digitalWrite(gpio, initial_state);

    hswitch_rf->ctrl_pin = gpio;
    hswitch_rf->is_open  = digitalRead(gpio);

    if (hswitch_rf->is_open != initial_state) return false;

    return rf_switch_register(hswitch_rf);
}
