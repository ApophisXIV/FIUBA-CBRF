#include "dir_coupler.h"
#include "switch_rf.h"
#include <HardwareSerial.h>

void log_initialize_HW(bool value, char *name) {
    if (value) {
        Serial.print("Failed to initialize ");
        Serial.print(name);
    } else {
        Serial.print(name);
        Serial.println(" initialized successfully");
    }
}

void setup() {

    Serial.begin(115200);
    delay(1000);

    switch_rf_t *rf_switch_1, *rf_switch_2;
    log_initialize_HW(rf_switch_init(rf_switch_1, 2, LOW), "RF Switch 1");
    log_initialize_HW(rf_switch_init(rf_switch_2, 3, LOW), "RF Switch 2");

    // Initialize Directional Coupler
    dir_coupler_t *dir_coupler;
    log_initialize_HW(dir_coupler_init(dir_coupler, 0, 1), "Directional Coupler");
}

void loop() {
}
