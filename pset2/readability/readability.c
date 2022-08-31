#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //CÜMLEYİ SOR
    //HARF KELİME CÜMLE SAYILARINI BUL
    //İNDEXİ BUL
    //GRADE'İ BUL
    string s = get_string("Text: ");

    int Letter = 0;
    int Word = 0;
    int Sentence = 0;

    //SIRAYLA HARF KELİME VE CÜMLE UZUNLUKLARINI HESAPLA:
    for (int i = 0, n = strlen(s); i < n + 1; i++)
    {
        if (islower(s[i]) || isupper(s[i]))
        {
            Letter++;
        }
        if ((int) s[i] == 32 || (int) s[i] == 0)
        {
            Word++;
        }
        if ((int) s[i] == 33 || (int) s[i] == 46 || (int) s[i] == 63)
        {
            Sentence++;
        }
    }
            // L ve S ENDEKSLERİNİ HESAPLA
    float L = (Letter / (float) Word) * 100;
    float S = (Sentence / (float) Word) * 100;

    //GRADE'İ BUL
    float index = 0.0588 * L - 0.296 * S - 15.8;

    int grade = (int) index;

    if (index - (int) index > 0.50)
    {
        grade = (int) index + 1;
    }

    //GRADE KOŞULLARINI YAZ
    if (index < 16 && index >= 1)
    {
        printf("Grade %i\n", grade);
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }

}

