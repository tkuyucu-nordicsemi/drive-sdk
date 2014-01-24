#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "greatest.h"

extern SUITE(ble_advertisement);
extern SUITE(vehicle_advertisement);
extern SUITE(vehicle_protocol);

/* Add all the definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line arguments, initialization. */
    RUN_SUITE(ble_advertisement);
    RUN_SUITE(vehicle_advertisement);
    RUN_SUITE(vehicle_protocol);
    GREATEST_MAIN_END();        /* display results */
}
