#include <Arduino.h>

#define OPEN_STATE  0
#define CLOSE_STATE 1

/* -------------------------------- Switch RF ------------------------------- */
struct switch_rf;
typedef struct switch_rf switch_rf_t;
typedef void (*action_fn)(switch_rf_t*);

typedef struct {
    bool is_open;
    action_fn open;
    action_fn close;
    uint8_t ctrl_pin;
} switch_rf_t;

bool rf_switch_init(switch_rf_t *switch_rf, uint8_t gpio, bool initial_state);