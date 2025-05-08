#ifndef SWITCH_RF_H
#define SWITCH_RF_H

#include <Arduino.h>

#define OPEN_STATE  0
#define CLOSE_STATE 1

/* -------------------------------- Switch RF ------------------------------- */
struct switch_rf;
typedef struct switch_rf switch_rf_t;

bool rf_switch_init(switch_rf_t *hswitch_rf, uint8_t gpio, bool initial_state);

bool rf_switch_is_open(switch_rf_t *hswitch_rf);

void rf_switch_open(switch_rf_t *hswitch_rf);

void rf_switch_close(switch_rf_t *hswitch_rf);

#endif    // SWITCH_RF_H