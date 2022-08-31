#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //ödenecek para üstünü sor
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    //dolar cinsinden parayı cent'e çevir
    int cents = round(change * 100);

    //25 cent'ten kullanmaya başla artanı aşağıdan devam et
    int start = 0;
    int yirmibeş = 0;

    while (cents > start)
    {
        start = start + 25;
        if (cents >= start)
        {
            yirmibeş++;
        }
    }
    //10 cent'ten kullanmaya başla artanı aşağıdan devam et
    int startiki = 0;
    int on = 0;
    int centsiki = cents - yirmibeş * 25;

    while (centsiki > startiki)
    {
        startiki = startiki + 10;
        if (centsiki >= startiki)
        {
            on++;
        }
    }

    //5 cent'ten kullanmaya başla artanı aşağıdan devam et
    int startüç = 0;
    int beş = 0;
    int centsüç = centsiki - on * 10;

    while (centsüç > startüç)
    {
        startüç = startüç + 5;
        if (centsüç >= startüç)
        {
            beş++;
        }
    }

    //1 cent'ten kullanmaya başla ve bitir
    int startdört = 0;
    int bir = 0;
    int centsdört = centsüç - beş * 5;

    while (centsdört > startdört)
    {
        startdört = startdört + 1;
        if (centsdört >= startdört)
        {
            bir++;
        }
    }
    //para miktarlarını toplayıp ver
    printf("%d\n", yirmibeş + on + beş + bir);

}
