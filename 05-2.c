#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define GRID_SIZE 1000
// void print_mat(int64_t grid[GRID_SIZE][GRID_SIZE]);

int main(void)
{
    FILE *fin;
    int64_t grid[GRID_SIZE][GRID_SIZE] = {0};
    int64_t x_begin, x_end, y_begin, y_end, tmp, count = 0;

    if ((fin = fopen("05-input.txt", "r")))
    {
        while (fscanf(fin, "%ld,%ld -> %ld,%ld", &x_begin, &y_begin, &x_end, &y_end) != EOF)
        {
            if (x_begin == x_end)
            {
                if (y_end < y_begin)
                {
                    tmp = y_end;
                    y_end = y_begin;
                    y_begin = tmp;
                }

                for (int64_t i = y_begin; i <= y_end; ++i)
                    grid[i][x_begin]++;
            }
            else if (y_begin == y_end)
            {
                if (x_end < x_begin)
                {
                    tmp = x_end;
                    x_end = x_begin;
                    x_begin = tmp;
                }
                for (int64_t i = x_begin; i <= x_end; ++i)
                    grid[y_begin][i]++;
            }
            else
            {
                if (x_end > x_begin)     
                    if (y_end > y_begin) 
                        for (int64_t x = x_begin, y = y_begin; x <= x_end && y <= y_end; ++x, ++y)
                            grid[y][x]++;
                    else 
                        for (int64_t x = x_begin, y = y_begin; x <= x_end && y >= y_end; ++x, --y)
                            grid[y][x]++;
                else   
                    if (y_end > y_begin) 
                        for (int64_t x = x_begin, y = y_begin; x >= x_end && y <= y_end; --x, ++y)
                            grid[y][x]++;
                    else 
                        for (int64_t x = x_begin, y = y_begin; x >= x_end && y >= y_end; --x, --y)
                            grid[y][x]++;
            }
        }
        for (uint64_t i = 0; i < GRID_SIZE; ++i)
        {
            for (uint64_t j = 0; j < GRID_SIZE; ++j)
            {
                if (grid[i][j] >= 2)
                    count++;
            }
        }
        // print_mat(grid);
        printf("%ld\n", count);
    }
    else
    {
        printf("Can't open the file\n");
    }
}

// void print_mat(int64_t grid[GRID_SIZE][GRID_SIZE])
// {
//     for (uint64_t i = 0; i < GRID_SIZE; ++i)
//     {
//         for (uint64_t j = 0; j < GRID_SIZE; ++j)
//         {
//             printf("%ld ", grid[i][j]);
//         }
//         printf("\n");
//     }
// }
