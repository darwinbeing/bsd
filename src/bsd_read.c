#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_bsd.h"

#ifdef PICO_DEFAULT_BSD_PIN
#define BSD_PIN PICO_DEFAULT_BSD_PIN
#else
// default to pin 15 if the board doesn't have a default BSD pin defined
#define BSD_PIN 15
#endif

int main() {
        stdio_init_all();
        printf("BSD Smoke Test, using pin %d", BSD_PIN);

        PIO pio = pio0;
        int sm_read = 0;
        int sm_write = 0;
        sm_read = pio_claim_unused_sm(pio, true);
        sm_write = pio_claim_unused_sm(pio, true);
        bsd_program_init(pio, sm_read, sm_write, BSD_PIN, 1200);
        sleep_ms(100);

        while (1) {
                int i;
                int j;
                for(i = 0; i < 1; ++i) {
                        for(j = 0; j < 8; ++j) {
                                float voltage;
                                float current;
                                ibs_pio_bsd_get_voltage(pio, sm_read, &voltage);
                                // ibs_pio_bsd_get_current(pio, sm, &current);
                                // uint16_t val;
                                // pio_bsd_get_val(pio, sm_read, 0, i, j, &val);
                                // pio_bsd_get_val(pio, sm_read, 0, 0, 3, &val);
                                float val;
                                ibs_pio_bsd_get_temperature(pio, sm_read, &val);

                                // uint16_t val = 0x40;
                                // pio_bsd_set_val(pio, sm_read, 0, 0, 3, &val);

                                // sleep_ms(200);
                        }
                }

        }
}
