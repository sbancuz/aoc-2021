#include <stdio.h>
#include <string.h>
#include <inttypes.h>

int main (void)
{
    FILE * fin;
    int64_t in = -1, count = 0, clock = 0;
    int64_t window [3] = {0, 0, 0};

    if ((fin = fopen("01-input.txt", "r"))){
        fscanf(fin, "%ld", &in);
        window[clock] = in;
        clock++;
        fscanf(fin, "%ld", &in);
        window[clock] = in;
        clock++;
        fscanf(fin, "%ld", &in);
        window[clock] = in;
        clock++;
        printf("%ld (N/A - no previous sum)\n", window[0] + window[1] + window[2]);    
        while (fscanf(fin, "%ld", &in) != EOF){
            if (in < window[clock % 3]){
                window[clock % 3] = in;
                printf("%ld (decreased)\n", window[0] + window[1] + window[2]);
            }
            else if(in > window[clock % 3]){
                window[clock % 3] = in;
                printf("%ld (increased)\n", window[0] + window[1] + window[2]);
                count++;
            }
            else{
                window[clock % 3] = in;
                printf("%ld (same)\n", window[0] + window[1] + window[2]);                
            }
            clock++;
        }
        printf("The sea level has increased %ld times!\n", count);
        fclose(fin);
    }else{
        printf("Can't open the file\n");
    }
}