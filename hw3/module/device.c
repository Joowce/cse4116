//
// Created by 민지우 on 2019-05-24.
//
#include <asm/io.h>

#include "device.h"

#define FND_DIGIT 4
#define IOM_FND_ADDRESS 0x08000004 // pysical address

static unsigned char *iom_fpga_fnd_addr;

/**
 * write val to fnd device
 * @param val
 */
void fnd_write(char *val) {
    int i;
    unsigned short int fnd_val = 0;

    for (i =0; i < FND_DIGIT; i++) {
        fnd_val |= val[i];
        fnd_val <<= 4;
    }

    outw(fnd_val, (unsigned int)iom_fpga_fnd_addr);
}

/**
 * map address for fnd
 */
void fnd_init (void) {
    iom_fpga_fnd_addr = ioremap(IOM_FND_ADDRESS, 0x4);
}
