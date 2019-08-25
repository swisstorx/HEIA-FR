#include <am335x_dmtimer1.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 65536
#define LOOPS 100

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
    printf("p.05 - performance test on cortex-a8 pipeline...\n");
    printf("------------------------------------------------\n");

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
}
