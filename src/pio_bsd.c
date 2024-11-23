#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_bsd.h"

static inline int parity(int x) {
        int res = 0;
        int i;
        for(i = 0; i < 8; ++i) {
                res ^= x & 1;
                x >>= 1;
        }
        return res;
}

static inline int pio_bsd_master_read(PIO pio, uint32_t sm, uint32_t dir,
                                  uint32_t slave_addr, uint32_t reg, uint32_t *pdata) {
        uint32_t tmp = dir << 7 | slave_addr << 4 | reg;
        uint32_t data = tmp << 1 | parity(tmp);
        // BSD TX 9bits DIR:1 Slave Address:3 Register Address:4 Parity:1
        pio_sm_put_blocking(pio, sm, data << 23u);
        // BSD RX 10bits Data:4 Parity:1 ACK:1
        data = ~pio_sm_get_blocking(pio, sm) & 0x3ff;
        if(data == 0) {
                // TIMEOUT
                return -1;
        }

        uint32_t ack = data & 1;
        uint32_t p2 = (data >> 1) & 1;
        if(p2 != parity(data >> 2)) {
                printf("parity incorrect! %d %d\n", p2, parity(data >> 2));
                return -2;
        } else {
                // printf("parity correct.\n");
        }
        if(ack) {
                printf("ACK = 1 transmission is unsuccessful.\n");
                return -3;
        } else {
                // printf("ACK = 0 transmission is successful.\n");
        }
        *pdata = data >> 2;

        return 0;
}

int ibs_pio_bsd_get_voltage(PIO pio, uint32_t sm, float *pdata)
{
        // Addr:0 Reg:1 might be voltage 0xaf00:12V?
        uint32_t data_hi;
        uint32_t data_lo;
        int ret;

        ret = pio_bsd_master_read(pio, sm, 0, 0, 1, &data_hi);
        if(ret == -1) {
                return ret;
        }
        pio_bsd_master_read(pio, sm, 0, 0, 1, &data_lo);
        uint32_t data = data_hi << 8 | data_lo;
        float voltage = (data - 0xaf00) * 0.0005 + 12;
        *pdata = voltage;
        printf("BSD ADDR %d REG %d HI %x LO %x Voltage %.2fV\n",
               0, 1, data_hi, data_lo, voltage);

        return 0;
}

int ibs_pio_bsd_get_current(PIO pio, uint32_t sm, float *pdata)
{
        // Addr:0 Reg:1 might be voltage 0xaf00:12V?
        uint32_t data_hi;
        uint32_t data_lo;
        int ret;
        // pio_sm_clear_fifos(pio, sm);
        ret = pio_bsd_master_read(pio, sm, 0, 0, 0, &data_hi);
        if(ret == -1) {
                return ret;
        }
        pio_bsd_master_read(pio, sm, 0, 0, 0, &data_lo);
        uint32_t data = data_hi << 8 | data_lo;
        float current = (data - 0x9344) * 0.04;
        *pdata = current;
        printf("BSD ADDR %d REG %d HI %x LO %x Current %.2fA\n",
               0, 0, data_hi, data_lo, current);

        return 0;
}

int ibs_pio_bsd_get_temperature(PIO pio, uint32_t sm, float *pdata)
{
        uint32_t data;
        int ret;
        // pio_sm_clear_fifos(pio, sm);
        ret = pio_bsd_master_read(pio, sm, 0, 0, 3, &data);
        if(ret == -1) {
                return ret;
        }
        *pdata = data;
        printf("BSD ADDR %d REG %d Data %x Temp %.2f (Fahrenheit)\n", 0, 3, data, (float)data);

        return 0;
}

int pio_bsd_get_val(PIO pio, uint32_t sm, uint32_t dir, uint32_t saddr, uint32_t reg, uint16_t *pdata)
{
        // Addr:0 Reg:1 might be voltage 0xaf00:12V?
        uint32_t data_hi;
        uint32_t data_lo;
        int ret;
        // pio_sm_clear_fifos(pio, sm);
        ret = pio_bsd_master_read(pio, sm, dir, saddr, reg, &data_hi);
        if(ret == -1) {
                return ret;
        }
        pio_bsd_master_read(pio, sm, dir, saddr, reg, &data_lo);
        uint16_t data = data_hi << 8 | data_lo;
        *pdata = data;
        printf("BSD ADDR %d REG %d HI %x LO %x Val %x\n",
               saddr, reg, data_hi, data_lo, data);

        return 0;
}
