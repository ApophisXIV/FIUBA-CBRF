#include <Arduino.h>

#include "dir_coupler.h"
#include "switch_rf.h"

void setup() {

    switch_rf_t switch_vhf, switch_uhf;

    rf_switch_init(&switch_uhf, PIN4, LOW);
    rf_switch_init(&switch_vhf, PIN5, LOW);

    switch_vhf

}

void loop() {}
