#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{   
    BYTE average; //ortalama değeri
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //ortalama değerleri bul ve yeni değer olarak ata
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //her renk için sepia yeni değerleri
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;     
    for (int i = 0; i < height; i++) 
    { 
        for (int j = 0; j < width; j++)
        {
            //sepia için standart oranlarla eski değerleri çarp
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);  
            //yeni değerler 255'ten yani bir bayttan büyük olmamalı
            if (sepiaBlue > 255)   
            {
                sepiaBlue = 255;  
            }
            if (sepiaRed > 255) 
            {
                sepiaRed = 255;
            } 
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            } 
            //yeni değerleri ata
            image[i][j].rgbtGreen = sepiaGreen;    
            image[i][j].rgbtRed =  sepiaRed;  
            image[i][j].rgbtBlue = sepiaBlue;   
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE temp; 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= width - 1 - j; j++) 
        {   
            //resmin ortasına kadar sağdaki pikselle soldakini yer değiştir.
            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = temp;

            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = temp;

            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = temp;   
        } 
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //ortalama değerleri
    float averageG;
    float averageR;
    float averageB;
    for (int i = 0; i < height; i++)
    {  
        for (int j = 0; j < width; j++)
        {
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)   
            { 
                //ortadaki piksel için dokuz pikselin ortalamasını al 
                averageG = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + 
                                  image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                  image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 9.00);
                       
                averageR = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + 
                                  image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                  image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 9.00);           
                       
                averageB = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + 
                                  image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                  image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 9.00);           
            }           
                        
            
            image[i][j].rgbtGreen = averageG;
            image[i][j].rgbtRed = averageR;
            image[i][j].rgbtBlue = averageB;
        }
    }
    return;
}
