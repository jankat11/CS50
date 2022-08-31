#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //KART NUMARASINI AL
    long number = get_long("Number: ");
    long a = number;
    long b = number;
    int kalan;
    int basamak = 0;

    //BASAMAK SAYISINI HESAPLA
    while (number > 0)
    {
        kalan = kalan % 10;
        number = (number - kalan)  /  10;
        basamak++;
    }

    //CHECKSUM İÇİN HESAP YAP:
    // BASAMAKLARI SONDAN İKİ ATLAYARAK TOPLA VE İKİYLE ÇARP
    long BasToplam = 0;
    long yüzde = 10;
    int i = 0;

    while (i < basamak)
    {
        int digit = ((b % (yüzde * 10) - b % yüzde) / yüzde);
        if (digit < 5)
        {
            BasToplam = BasToplam + 2 * digit;
        }
        else
        {
            BasToplam = BasToplam + (2 * digit) % 10 + 1;
        }
        yüzde = yüzde * 100;
        i++;
    }

    // BASAMAKLARI EN SONDAN İKİ ATLAYARAK TOPLA
    long BasToplam2 = 0;
    long yüzde2 = 1;
    int j = 0;

    while (j < basamak)
    {
        int digit2 = ((b % (yüzde2  *  10) - b % yüzde2) / yüzde2);

        BasToplam2 = BasToplam2 + digit2;

        yüzde2 = yüzde2 * 100;
        j++;
    }


    //CHECKSUM'IN SON HANESİNİN 0 OLDUĞUNU TEYİT ET
    long BasToplam3 = (BasToplam + BasToplam2) % 10;

    if (BasToplam3 == 0)
    {

        //KART TİPİ TESTLERİ

        //İLK İKİ BASAMAĞI BUL
        long bölen = 1;
        for (int k = 0; k < basamak - 2; k++)
        {
            bölen = bölen * 10;
        }
        long FirstTwoDigit = a / bölen;

        // VISA TESTİ
        if ((FirstTwoDigit >= 40 && 50 > FirstTwoDigit) && (basamak == 13 || basamak == 16))
        {
            printf("VISA\n");
        }
        // MASTERCARD TESTİ
        else if ((FirstTwoDigit > 50 && 56 > FirstTwoDigit) && (basamak == 16))
        {
            printf("MASTERCARD\n");
        }
        // AMERICAN EXPRESS TESTİ
        else if ((FirstTwoDigit == 34 || FirstTwoDigit == 37) && (basamak == 15))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}










