#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define VALUES 1000
char *strrev(char *str);
void printb(int64_t num);

int main(void)
{
    FILE *fin;
    char val[20];
    int64_t values_o2[VALUES] = {0}, values_co2[VALUES] = {0};
    int64_t co2 = 0, o2 = 0, len = 0, count = 0, remaining_o2 = 0, remaining_co2 = 0;
    int64_t most_common, least_common;

    if ((fin = fopen("03-input.txt", "r")))
    {
        fscanf(fin, "%20s", val);
        for (len = 0; val[len] != '\0'; ++len)
            ;

        do
        {
            for (uint8_t i = 0; val[i] != '\0'; ++i)
            {
                values_o2[count] += (val[i] - '0') << (len - i - 1);
                values_co2[count] = values_o2[count];
            }
            count++;

        } while (fscanf(fin, "%20s", val) != EOF);
        remaining_o2 = VALUES;
        remaining_co2 = VALUES;
        for (uint8_t i = 0; i < len; ++i)
        {
            most_common = 0;
            least_common = 0;

            for (uint32_t j = 0; j < VALUES; ++j)
            {
                if (values_o2[j] > 0)
                {
                    if ((values_o2[j] & (1 << (len - i - 1))) > 0)
                        most_common++;
                    else
                        most_common--;
                }
                if (values_co2[j] > 0)
                {
                    if ((values_co2[j] & (1 << (len - i - 1))) > 0)
                        least_common++;
                    else
                        least_common--;
                }
            }

            most_common = most_common >= 0 ? 1 : -1;
            least_common = least_common <= 0 ? -1 : 1;

            for (uint32_t j = 0; j < VALUES; ++j)
            {

                if (remaining_o2 > 1 && values_o2[j] > 0 && !((values_o2[j] * most_common) & 1 << (len - i - 1)))
                {
                    values_o2[j] = -1;
                    remaining_o2--;
                }
                if (remaining_co2 > 1 && values_co2[j] > 0 && ((values_co2[j] * least_common) & 1 << (len - i - 1)))
                {
                    values_co2[j] = -1;
                    remaining_co2--;
                }
                // if (values_o2[j] > 0 && pass == 5)
                //     printb(values_o2[j]);
            }

            // if (pass == 5)
            //     return 0;
            // pass++;
        }

        for (uint32_t j = 0; j < VALUES; ++j)
        {
            if (values_o2[j] > 0)
                o2 = values_o2[j];
            if (values_co2[j] > 0)
                co2 = values_co2[j];
        }
        printf("%ld * %ld = %ld\n", co2, o2, co2 * o2);

        fclose(fin);
    }
    else
    {
        printf("Can't open the file\n");
    }
}

void printb(int64_t num)
{
    char buf[64];
    int a = 0;
    while (num > 0)
    {
        buf[a] = num % 2 + '0';
        num /= 2;
        a++;
    }
    strrev(buf);
    printf("%s\n", buf);
}

char *strrev(char *str)
{
    char *p1, *p2;

    if (!str || !*str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}
