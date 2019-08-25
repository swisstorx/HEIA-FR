#include <stdio.h>

#include "cache.h"
#include "dmtimer1.h"
#include "mmu.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

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

static uint32_t x[4096][128];

static void foo_bad()
{
    for (int j = 0; j < 128; j++)
        for (int i = 0; i < 4096; i++) x[i][j] = x[i][j] * 2;
}

static void foo_good()
{
    for (int i = 0; i < 4096; i++)
        for (int j = 0; j < 128; j++) x[i][j] = x[i][j] * 2;
}

static uint32_t measure(const char* s, void (*foo)())
{
    uint32_t middle = 0;
    printf("--> %s algo\n", s);
    const int iter = 5;
    for (int i = 0; i < iter; i++) {
        uint32_t st = dmtimer1_get_counter();
        foo();
        uint32_t sp    = dmtimer1_get_counter();
        uint32_t delta = (sp - st) / (dmtimer1_get_frequency() / 1000000);
        middle += delta;
        printf("delta: %8lu [us]\n", delta);
    }
    return middle / iter;
}

int main()
{
    printf("p.06 - performance test on i- & d-cache...\n");
    printf("------------------------------------------\n");
    mmu_init();
    mmu_configure_regions(regions, ARRAY_SIZE(regions));
    mmu_enable();

    dmtimer1_init();

    printf("performance test w/o i- & d-cache enabled\n");
    uint32_t m11 = measure("bad", foo_bad);
    uint32_t m12 = measure("good", foo_good);
    float f1     = (float)m11 / (float)m12;
    printf("factor=%f\n\n", f1);

    cache_i_enable();
    printf("performance test w/ i-cache enabled & d-cache disabled\n");
    uint32_t m21 = measure("bad", foo_bad);
    uint32_t m22 = measure("good", foo_good);
    float f2     = (float)m21 / (float)m22;
    float f25    = (float)m11 / (float)m22;
    printf("factor=%f - %f\n\n", f2, f25);

    cache_d_enable();
    printf("performance test w/ i- & d-cache enabled\n");
    uint32_t m31 = measure("bad", foo_bad);
    uint32_t m32 = measure("good", foo_good);
    float f3     = (float)m31 / (float)m32;
    float f35    = (float)m11 / (float)m32;
    printf("factor=%f - %f\n", f3, f35);

    while (1)
        ;
    return 0;
}
