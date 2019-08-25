#include <stdio.h>
#include <string.h>

#include "exception.h"
#include "interrupt.h"
#include "mmu.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static int v = 10;

// list of memory regions in 1MiB sections with populated I/O devices and
// memories
static const struct region regions[] = {
    {"sram"   , 0x40200000, 0x40200000,  1, STRONG},
    {"l3_ocmc", 0x40300000, 0x40300000,  1, NORMAL},
    {"l3f_cfg", 0x44000000, 0x44000000,  4, STRONG},
    {"l3s_cfg", 0x44800000, 0x44800000,  4, STRONG},
    {"l4_wkup", 0x44c00000, 0x44c00000,  4, STRONG},
    {"mcasp0 ", 0x46000000, 0x46000000,  4, STRONG},
    {"mcasp1 ", 0x46000000, 0x46000000,  4, STRONG},
    {"usb    ", 0x47400000, 0x47400000,  1, STRONG},
    {"mmchs2 ", 0x47800000, 0x47800000,  1, STRONG},
    {"l4_per ", 0x48000000, 0x48000000, 16, STRONG},
    {"tpcc   ", 0x49000000, 0x49000000,  1, STRONG},
    {"tptc0  ", 0x49800000, 0x49800000,  1, STRONG},
    {"tptc1  ", 0x49900000, 0x49900000,  1, STRONG},
    {"tptc2  ", 0x49a00000, 0x49a00000,  1, STRONG},
    {"l4_fast", 0x4a000000, 0x4a000000, 16, STRONG},
    {"debug  ", 0x4b100000, 0x4b100000,  1, STRONG},
    {"emif0  ", 0x4c000000, 0x4c000000, 16, STRONG},
    {"gpmc   ", 0x50000000, 0x50000000, 16, STRONG},
    {"adc_tsc", 0x54c00000, 0x54c00000,  4, STRONG},
    {"sgx530 ", 0x56000000, 0x56000000, 16, STRONG},
    {"sdram  ", 0x80000000, 0x80000000, 15, NORMAL},
    {"dmasafe", 0x80f00000, 0x80f00000,  1, STRONG},  // for dma access...
    {"sdram2", 0x88000000, 0x88000000, 256, NORMAL},
};

int main()
{
    interrupt_init();
    exception_init();
    mmu_init();
    mmu_configure_regions(regions, ARRAY_SIZE(regions));
    mmu_enable();

    printf("test null-pointer access...\n");
    int* x = (int*)0;
    v      = *x;

    printf("test wrong address (faulty section) access...\n");
    int* y = (int*)0x40100000;
    v      = *y;

    printf("\n");
    char* sdram = (char*)0x80000000;
    char* dup   = (char*)0xfff00000;
    strcpy(sdram, "hello duplicated ram area...\n");

    struct region region[] = {
        {
            .region_name  = "dup",
            .virtual_addr = 0xfff00000,
            .sz           = 1,
        },
    };
    mmu_configure_regions(region, ARRAY_SIZE(region));
    printf("access duplicated ram area w/o mapping --> should not work:\n");
    printf("%c\n", *dup);

    region[0].physical_addr = 0x80000000;
    region[0].cfg           = NORMAL;
    mmu_configure_regions(region, ARRAY_SIZE(region));
    printf("access duplicated ram area w/ mapping --> should work: ");
    printf("%s\n", dup);

    region[0].physical_addr = 0;
    region[0].cfg           = 0;
    mmu_configure_regions(region, ARRAY_SIZE(region));
    printf("access duplicated ram area w/o mapping --> should not work:\n");
    printf("%c\n", *dup);

    printf("test passed!\n");
    while (1)
        ;
    return 0;
}
