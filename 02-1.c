#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>

int main (void)
{
    FILE * fin;
    char command[8];
    int64_t depth = 0, horizontal = 0, val;

    if ((fin = fopen("02-input.txt", "r"))){
        while (fscanf(fin, "%8s %ld", command, &val) != EOF){
            if (strcmp(command, "forward") == 0)
                horizontal += val;
            else if(strcmp(command, "up") == 0){
                depth -= val;
            }
            else if(strcmp(command, "down") == 0){
                depth += val;
            }
            else
                assert(false && "Error in parsing step\n");
        }
        printf("%ld\n", depth * horizontal);
        fclose(fin);
    }else{
        printf("Can't open the file\n");
    }
}