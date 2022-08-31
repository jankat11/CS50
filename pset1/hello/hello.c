#include <stdio.h>
#include <cs50.h>

//for asking user's name.s
int main(void)
{
    string name = get_string("what is your name?\n");

    printf("hello, %s\n", name);
}
..