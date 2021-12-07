#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define HEADS_NUM 500
#define END_DAY 80

typedef struct list_s
{
    int8_t count;
    struct list_s **branches;
} list;

list * init_node(int8_t val);
void print_list(list *head);
int count_branches(list * head);
void update(list * head);

int days_left = END_DAY;

int main(void)
{
    list *heads[HEADS_NUM] = {NULL};
    int64_t count = 0, day;
    FILE * fin;
    char line[701], *tmp;
    if ((fin = fopen("06-input.txt", "r")))
    {
        fscanf(fin, "%700s", line);
        tmp = malloc(sizeof(char) * 10);
        tmp = strtok(line, ",");
        for (int32_t i = 0; tmp != NULL; ++i)
        {
            heads[i] = init_node(atoi(tmp));
            tmp = strtok(NULL, ",");
        }

        for (day = 0; day < END_DAY; ++day)
        {
            printf("Day %ld : ", day + 1);
            for (int32_t i = 0; heads[i] != NULL; ++i)
            {
               update(heads[i]);
               print_list(heads[i]);
               
            }
            printf("\n");
            days_left--;
        }
        for (int32_t i = 0; heads[i] != NULL; ++i)
        {
           count += count_branches(heads[i]);
        }
        printf("%ld\n", count);
    } else {
        printf("Cannot open input file\n");
    }
    
    return 0;
}

list * init_node(int8_t val)
{
    assert(val);
    list * branch = NULL;
    if ((branch = (list *) malloc(sizeof(list))))
    {
        branch->count = val;
        branch->branches = (list ** )malloc(sizeof(list) * (days_left / 8 + 1));
    } else {
        printf("Could not allocate memory for %d\n", val);
        exit(1);
    }

    return branch;
}

void print_list(list *head)
{
    printf("%d ", head->count);
    for (int8_t i = 0; head->branches[i] != NULL; ++i)
        print_list(head->branches[i]);   
}

int count_branches(list * head)
{
    int64_t counter = 1;
    for (int8_t i = 0; head->branches[i] != NULL; ++i)
    {
        counter += count_branches(head->branches[i]);
    }

    return counter;
}

void update(list * head)
{
    head->count--;
    for (int8_t i = 0; head->branches[i] != NULL; ++i)
        update(head->branches[i]);
    
    if (head->count < 0)
    {
        head->count = 6;
        int8_t index;
        for (index = 0; head->branches[index] != NULL; ++index)
            ;
        head->branches[index] = init_node(8);
    }

}