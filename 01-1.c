#include <stdio.h>
#include <string.h>
#include <inttypes.h>

int main (void)
{
    FILE * fin;
    int64_t new = -1, old = -1, count = 0;

    if ((fin = fopen("01-input.txt", "r"))){
        fscanf(fin, "%ld", &new);
        printf("%ld (N/A - no previous measurement)\n", new);
        old = new;
        while (fscanf(fin, "%ld", &new) != EOF){
            if (old > new)
                printf("%ld (decreased)\n", new);
            else if(new > old){
                printf("%ld (increased)\n", new);
                count++;
            }
            else
                printf("%ld (same)\n", new);
            old = new;
        }
        printf("The sea level has increased %ld times!\n", count);
        fclose(fin);
    }else{
        printf("Can't open the file\n");
    }
}