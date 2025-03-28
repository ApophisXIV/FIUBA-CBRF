#include <Arduino.h>

/* --------------------------- Directional coupler -------------------------- */
typedef float (*float_fn)(bool);
typedef struct {
    bool (*init)(uint8_t adc_ch1, uint8_t adc_ch2);
    float_fn get_vswr;
    float_fn get_dir_value;
    float_fn get_ref_value;
} dir_coupler_rf_t;


