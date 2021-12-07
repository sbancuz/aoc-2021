/*
/   I "could" have used the implementation for the first part but my laptop runs out of memory.....
/   Well i had fun with linked list at least. Oh well....
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define END_DAY 256
#define STATES 9

int main(void)
{
    uint64_t states[STATES + 1] = {0}, cont = 0;
    FILE * fin;
    char line[701], *tmp;

    if ((fin = fopen("06-input.txt", "r")))
    {
        fscanf(fin, "%700s", line);
        tmp = malloc(sizeof(char) * 10);
        tmp = strtok(line, ",");
        for (int32_t i = 0; tmp != NULL; ++i)
        {
            states[atoi(tmp)]++;
            tmp = strtok(NULL, ",");
        }        
        
        for (int64_t i = 0; i < END_DAY; ++i)
        {
            states[7] += states[0];
            states[9] += states[0];
            for (int64_t j = 1; j < STATES + 1; ++j)
            {
                states[j - 1] = states[j];
                states[j] = 0;
            }

            // printf("Day %ld : ", i + 1);
            // for (int64_t j = 0; j < STATES; ++j)
            //     for (uint64_t k = 0; k < states[j]; ++k)
            //         printf("%lu ", j);
            // printf("\n");
        }
        for (int64_t j = 0; j < STATES; ++j)
            cont += states[j];
        printf("%lu\n", cont);

    } else
        printf("COuld not open the file\n");
}