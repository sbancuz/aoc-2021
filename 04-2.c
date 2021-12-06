#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LEN 500
#define GRID_SIZE 5

void write_off(int64_t grid[GRID_SIZE][GRID_SIZE], int64_t num);
int64_t sum_unmarked(int64_t grid[GRID_SIZE][GRID_SIZE]);
bool check_win(int64_t grid[GRID_SIZE][GRID_SIZE]);
// void print_mat(int64_t grid[GRID_SIZE][GRID_SIZE]);

int main(void)
{
    int64_t called_num[MAX_LEN], (*grids)[GRID_SIZE][GRID_SIZE], sum;
    uint64_t len, grid_count, bytes, loser_number, loser_grid, win_count = 0;
    bool *winners;
    char *strin, *tmp;
    FILE *fin;

    if ((fin = fopen("04-input.txt", "r")))
    {
        if ((strin = (char *)malloc(sizeof(char) * (MAX_LEN + 1))) &&
            (tmp = (char *)malloc(sizeof(char) * 10)))
        {
            getline(&strin, &bytes, fin);
            tmp = strtok(strin, ",");
            for (len = 0; tmp != NULL; ++len)
            {
                called_num[len] = atoi(tmp);
                tmp = strtok(NULL, ",");
            }

            grid_count = 0;
            while (getline(&strin, &bytes, fin) != EOF)
                if (strcmp(strin, "\n") == 0)
                    ++grid_count;
            fseek(fin, 2, SEEK_SET);

            if ((grids = (int64_t(*)[GRID_SIZE][GRID_SIZE])malloc(sizeof(*grids) * len)) &&
                (winners = (bool *) malloc(sizeof(bool) * len)))
            {
                uint64_t grid = 0;
                while (getline(&strin, &bytes, fin) != EOF)
                {
                    if (strcmp(strin, "\n") == 0)
                    {
                        for (uint64_t j = 0; j < GRID_SIZE; ++j)
                        {
                            getline(&strin, &bytes, fin);
                            tmp = strtok(strin, " ");
                            for (uint64_t k = 0; k < GRID_SIZE; ++k)
                            {
                                grids[grid][j][k] = atoi(tmp);
                                tmp = strtok(NULL, " ");
                            }
                        }
                        ++grid;
                    }
                }

                for (uint64_t i = 0; i < len && win_count != grid_count; ++i)
                {
                    for (uint64_t j = 0; j < grid_count && win_count != grid_count; ++j)
                    {
                        write_off(grids[j], called_num[i]);
                        if (!winners[j] && check_win(grids[j]))
                        {
                            winners[j] = true;
                            win_count++;
                            loser_grid = j;
                            loser_number = called_num[i];
                        }
                    }
                }
                sum = sum_unmarked(grids[loser_grid]);
                printf("%ld * %ld = %ld\n", sum, loser_number, sum * loser_number);
            }
            else
                printf("Cannot allocate memory for the grids\n");
        }
        else
            printf("Malloc fails\n");
        fclose(fin);
    }
    else
    {
        printf("Can't open the file\n");
    }
    return 0;
}

void write_off(int64_t grid[GRID_SIZE][GRID_SIZE], int64_t num)
{
    for (uint64_t i = 0; i < GRID_SIZE; ++i)
        for (uint64_t j = 0; j < GRID_SIZE; ++j)
            if (grid[i][j] == num)
                grid[i][j] = -1;
}

bool check_win(int64_t grid[GRID_SIZE][GRID_SIZE])
{
    int64_t row_count, col_count;
    for (uint64_t i = 0; i < GRID_SIZE; ++i)
    {
        row_count = 0;
        col_count = 0;
        for (uint64_t j = 0; j < GRID_SIZE; ++j)
        {
            if (grid[i][j] == -1)
                row_count++;

            if (grid[j][i] == -1)
                col_count++;
        }
        if (row_count == 5 || col_count == 5)
            return true;
    }
    return false;
}

int64_t sum_unmarked(int64_t grid[GRID_SIZE][GRID_SIZE])
{
    int64_t sum = 0;
    for (uint64_t i = 0; i < GRID_SIZE; ++i)
        for (uint64_t j = 0; j < GRID_SIZE; ++j)
            if (grid[i][j] != -1)
                sum += grid[i][j];
    return sum;
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