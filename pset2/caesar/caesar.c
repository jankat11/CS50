#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int ac, string av[])
{   
    // KOMUT SATIRINDA İKİ GİRDİ OLDUĞUNU KONTROL ET
    if (ac != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    //KOMUT SATIRINDA İKİNCİ KOMUTUN SAYI OLDUĞUNU KONTROL ET 
    //EĞER SAYIYSA STRİNGDEN TAMSAYIYA ÇEVİR VE KULLANICIDAN TEXT İSTE
    int counter = 0;
    int key = 0;
    int çarpan = 1;
    
    for (int i = strlen(av[1]); i >= 0; i--)
    {
        if (av[1][i] <= 57 && av[1][i] >= 48)
        {
            counter++;
            key = key + (av[1][i] - 48) * çarpan;
            çarpan *= 10;
        }
    }
    //EĞER SAYI İSE:
    if (counter == strlen(av[1]) && av[1][0] != 48)
    {
        string plain = get_string("plaintext: ");
         
        //GİRİLEN TEXTİ KEY İLE ENKRİPT ET
        printf("ciphertext: ");
    
        key = key % 26;
        
        for (int j = 0, n = strlen(plain); j < n; j++)
        {
            //BÜYÜK HARF KÜÇÜK HARFE GÖRE DEĞİŞTİR
            if (islower(plain[j]) || isupper(plain[j]))
            {
                
                if (islower(plain[j]) && (int) plain[j] + key <= 122)
                {
                    printf("%c", plain[j] + key);
                }
                else if (islower(plain[j]) && (int) plain[j] + key > 122)
                {
                    printf("%c", plain[j] + key - 26);
                }
                else if (isupper(plain[j]) && (int) plain[j] + key <= 90)
                {
                    printf("%c", plain[j] + key);
                }
                else if (isupper(plain[j]) && (int) plain[j] + key > 90)
                {
                    printf("%c", plain[j] + key - 26);
                }
            }
            else
            {
                printf("%c", plain[j]);
            }
    
        }    
        printf("\n");
         
    }
    //ARGÜMANDA SAYI DIŞI KARAKTER VARSA HATA VER
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

  
}

