#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // ask user for height then check range of 1-8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    // loop to go down
    for (int row = 0; row < height; row++)
    {
        //loop to go right
        for (int width = 1; width < height; width++)
        {
            if (height - row > width)
            {
                printf(" ");
            }
            else 
            {
                printf("#");
            }

        }
        //space between two block
        printf("#  ");
        
        //loop for second block
        for (int i = 0; i <= row; i++)
        {
            printf("#"); 
        }
        
        printf("\n");
    
    } 

}
 