#define  _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    FILE *fin;
    char *val;
    int64_t gamma = 0, epsilon = 0, len;
    int64_t *counters;
    uint64_t bytes;

    if ((fin = fopen("03-input.txt", "r")))
    {
        len = getline(&val, &bytes, fin) - 1;
        if ((counters = malloc(sizeof(int64_t) * len)))
        {
            do
            {
                for (uint8_t i = 0; val[i] != '\0'; ++i)
                    counters[i] += (val[i] * 2) - (('0' * 2) + 1);

            } while (getline(&val, &bytes, fin) != -1);

            for (int8_t i = 0; i < len; ++i)
            {
                gamma   += ((counters[i] > 0) << (len - i - 1));
                epsilon += ((counters[i] < 0) << (len - i - 1));
            }

            printf("%ld\n", gamma * epsilon);            
        }

        fclose(fin);
    }
    else
    {
        printf("Can't open the file\n");
    }
}