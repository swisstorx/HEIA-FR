#include <stdio.h>
#include <stdlib.h>

#include "am335x_dmtimer1.h"

#include "cache.h"
#include "mmu.h"

#define SIZE 65536
#define LOOPS 4000
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

// list of memory regions in 1MiB sections with populated I/O devices and
// memories
static const struct region regions[] = {
    {"sram", 0x40200000, 0x40200000, 1, NORMAL},
    {"l3_ocmc", 0x40300000, 0x40300000, 1, NORMAL},
    {"l3f_cfg", 0x44000000, 0x44000000, 4, STRONG},
    {"l3s_cfg", 0x44800000, 0x44800000, 4, STRONG},
    {"l4_wkup", 0x44c00000, 0x44c00000, 4, STRONG},
    {"mcasp0", 0x46000000, 0x46000000, 4, STRONG},
    {"mcasp1", 0x46000000, 0x46000000, 4, STRONG},
    {"usb", 0x47400000, 0x47400000, 1, STRONG},
    {"mmchs2", 0x47800000, 0x47800000, 1, STRONG},
    {"l4_per", 0x48000000, 0x48000000, 16, STRONG},
    {"tpcc", 0x49000000, 0x49000000, 1, STRONG},
    {"tptc0", 0x49800000, 0x49800000, 1, STRONG},
    {"tptc1", 0x49900000, 0x49900000, 1, STRONG},
    {"tptc2", 0x49a00000, 0x49a00000, 1, STRONG},
    {"l4_fast", 0x4a000000, 0x4a000000, 16, STRONG},
    {"debug", 0x4b100000, 0x4b100000, 1, STRONG},
    {"emif0", 0x4c000000, 0x4c000000, 16, STRONG},
    {"gpmc", 0x50000000, 0x50000000, 16, STRONG},
    {"adc_tsc", 0x54c00000, 0x54c00000, 4, STRONG},
    {"sgx530", 0x56000000, 0x56000000, 16, STRONG},
    {"sdram", 0x80000000, 0x80000000, 512, NORMAL},
    {"duplicate", 0xfff00000, 0x80000000, 1, NORMAL},
};

static short data[SIZE];

static int compare(const void* a, const void* b)
{
    return *(short*)a - *(short*)b;
}

static long long compute()
{
    long long sum = 0;
    for (int j = 0; j < LOOPS; j++) {
        for (int i = 0; i < SIZE; i++) {
            if (data[i] >= 128) {
                sum += data[i];
            }
        }
    }
    return sum;
}

static void measure(unsigned k, const char* s)
{
    uint32_t st   = am335x_dmtimer1_get_counter();
    long long sum = compute();
    uint32_t sp   = am335x_dmtimer1_get_counter();
    uint32_t time = (sp - st) / (am335x_dmtimer1_get_frequency() / 1000);

    printf("%s-%d: time=%lums, sum=%lld\n", s, k, time, sum);
}

int main()
{
    printf("p.07 - performance test on cortex-a8 pipeline and cache...\n");
    printf("----------------------------------------------------------\n");
    mmu_init();
    mmu_configure_regions(regions, ARRAY_SIZE(regions));
    mmu_enable();
    cache_i_enable();
    cache_d_enable();

    unsigned k = 0;
    while (1) {
        // generate data
        for (int i = 0; i < SIZE; i++) {
            data[i] = rand() % 256;
        }

        measure(k, "unsorted");

        qsort(data, SIZE, sizeof(data[0]), compare);
        measure(k, "  sorted");

        k++;
    }

    return 0;
}
