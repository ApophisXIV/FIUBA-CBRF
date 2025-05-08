#ifndef DIR_COUPLER_H
#define DIR_COUPLER_H

#include <Arduino.h>

/* --------------------------- Directional coupler -------------------------- */
struct dir_coupler;
typedef struct dir_coupler dir_coupler_t;

bool dir_coupler_init(dir_coupler_t *hdir_coupler, uint8_t adc_forward_channel, uint8_t adc_reflected_channel);
void dir_coupler_deinit(dir_coupler_t *hdir_coupler);

float dir_coupler_get_vswr(dir_coupler_t *hdir_coupler);
float dir_coupler_get_dir_value(dir_coupler_t *hdir_coupler);
float dir_coupler_get_ref_value(dir_coupler_t *hdir_coupler);

#endif    // DIR_COUPLER_H