#include "dir_coupler.h"

#define MAX_INSTANCES 4
static dir_coupler_t *dir_coupler_instances[MAX_INSTANCES] = {0};

struct dir_coupler {
    uint8_t adc_ch1, adc_ch2;
};

static bool dir_coupler_register(dir_coupler_t *hdir_coupler) {
    if (hdir_coupler == NULL) return false;

    for (uint8_t i = 0; i < MAX_INSTANCES; i++) {
        if (dir_coupler_instances[i] == NULL) {
            dir_coupler_instances[i] = hdir_coupler;
            return true;
        }
        if (dir_coupler_instances[i]->adc_ch1 == hdir_coupler->adc_ch1 &&
            dir_coupler_instances[i]->adc_ch2 == hdir_coupler->adc_ch2) {
            return false;
        }
    }
    return false;
}

static bool dir_coupler_unregister(dir_coupler_t *hdir_coupler) {
    if (hdir_coupler == NULL) return false;

    for (uint8_t i = 0; i < MAX_INSTANCES; i++) {
        if (dir_coupler_instances[i] != NULL &&
            dir_coupler_instances[i]->adc_ch1 == hdir_coupler->adc_ch1 &&
            dir_coupler_instances[i]->adc_ch2 == hdir_coupler->adc_ch2) {
            dir_coupler_instances[i] = NULL;
            return true;
        }
    }
    return false;
}

bool dir_coupler_init(dir_coupler_t *hdir_coupler, uint8_t adc_ch1, uint8_t adc_ch2) {
    if (hdir_coupler == NULL) return false;
    hdir_coupler->adc_ch1 = adc_ch1;
    hdir_coupler->adc_ch2 = adc_ch2;
    return dir_coupler_register(hdir_coupler);
}

float dir_coupler_get_vswr(dir_coupler_t *hdir_coupler) {
    if (hdir_coupler == NULL) return 0.0f;

    float dir_value = dir_coupler_get_dir_value(hdir_coupler);
    float ref_value = dir_coupler_get_ref_value(hdir_coupler);

    if (ref_value <= 0.0f) return 0.0f;

    return (1 + (dir_value / ref_value)) / (1 - (dir_value / ref_value));
}

float dir_coupler_get_dir_value(dir_coupler_t *hdir_coupler) {
    if (hdir_coupler == NULL) return 0.0f;
    return analogRead(hdir_coupler->adc_ch1);
}

float dir_coupler_get_ref_value(dir_coupler_t *hdir_coupler) {
    if (hdir_coupler == NULL) return 0.0f;
    return analogRead(hdir_coupler->adc_ch2);
}

void dir_coupler_deinit(dir_coupler_t *hdir_coupler) {
    if (hdir_coupler == NULL) return;
    dir_coupler_unregister(hdir_coupler);
}