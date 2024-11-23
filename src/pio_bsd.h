#ifndef _PIO_BSD_H_
#define _PIO_BSD_H_

#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "bsd.pio.h"

void  pio_bsd_write_bytes     (PIO pio, uint sm, uint8_t bytes[], int len);
void  pio_bsd_read_bytes      (PIO pio, uint sm, uint8_t bytes[], int len);
int   ibs_pio_bsd_get_temperature(PIO pio, uint32_t sm, float *pdata);
uint  pio_bsd_get_resolution  (PIO pio, uint sm);
void  pio_bsd_get_address     (PIO pio, uint sm, uint8_t *address);
int   ibs_pio_bsd_get_voltage(PIO pio, uint32_t sm, float *pdata);
int   ibs_pio_bsd_get_current(PIO pio, uint32_t sm, float *pdata);
int   pio_bsd_get_val(PIO pio, uint32_t sm, uint32_t dir, uint32_t saddr, uint32_t reg, uint16_t *pdata);

#endif
