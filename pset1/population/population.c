#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size

    // TODO: Prompt for end size

    // TODO: Calculate number of years until we reach threshold

    // TODO: Print number of years

    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);
    
    
    int year = 0;

    while (start < end)
    {
        start = start + start / 3 - start / 4;
        year++;
       
    }
 
    printf("Years: %i\n", year);

}


