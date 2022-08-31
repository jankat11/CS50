#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
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
    //geçici değer atama için üç boyutlu matris (0 = green, 1 = red, 2 = blue)
    BYTE temp[height][width][3];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //üst kenar (6 piksel ortalaması)
            if (i == 0 && (j != 0 && j != width - 1))
            {
                temp[i][j][0] = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                       image[i + 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.00);

                temp[i][j][1] = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                                       image[i + 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.00);

                temp[i][j][2] = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                       image[i + 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.00);
            }
            //alt kenar (6 piksel ortalaması)
            else if (i == height - 1 && (j != 0 && j != width - 1))
            {
                temp[i][j][0] = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                       image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6.00);

                temp[i][j][1] = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                                       image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6.00);

                temp[i][j][2] = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                       image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6.00);
            }
            //sol kenar (6 piksel ortalaması)
            else if (j == 0 && (i != 0 && i != height - 1))
            {
                temp[i][j][0] = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                       image[i - 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.00);

                temp[i][j][1] = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed +
                                       image[i - 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.00);

                temp[i][j][2] = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                       image[i - 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.00);
            }
            //sağ  kenar (6 piksel ortalaması)
            else if (j == width - 1 && (i != 0 && i != height - 1))
            {
                temp[i][j][0] = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                       image[i - 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.00);

                temp[i][j][1] = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                       image[i - 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.00);

                temp[i][j][2] = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                       image[i - 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.00);
            }
            //sol üst köşe (4 piksel ortalaması)
            else if (i == 0 && j == 0)
            {
                temp[i][j][0] = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                       image[i + 1][j].rgbtGreen) / 4.00);

                temp[i][j][1] = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                       image[i + 1][j].rgbtRed) / 4.00);

                temp[i][j][2] = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                       image[i + 1][j].rgbtBlue) / 4.00);
            }
            //sağ üst  köşe (4 piksel ortalaması)
            else if (i == 0 && j == width - 1)
            {
                temp[i][j][0] = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                       image[i + 1][j - 1].rgbtGreen) / 4.00);

                temp[i][j][1] = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                       image[i + 1][j - 1].rgbtRed) / 4.00);

                temp[i][j][2] = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                       image[i + 1][j - 1].rgbtBlue) / 4.00);
            }
            //sol alt  köşe (4 piksel ortalaması)
            else if (i == height - 1 && j == 0)
            {
                temp[i][j][0] = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                       image[i - 1][j + 1].rgbtGreen) / 4.00);

                temp[i][j][1] = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed +
                                       image[i - 1][j + 1].rgbtRed) / 4.00);

                temp[i][j][2] = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                       image[i - 1][j + 1].rgbtBlue) / 4.00);
            }
            //sağ alt  köşe (4 piksel ortalaması)
            else if (i == height - 1 && j == width - 1)
            {
                temp[i][j][0] = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                       image[i - 1][j - 1].rgbtGreen) / 4.00);

                temp[i][j][1] = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                                       image[i - 1][j - 1].rgbtRed) / 4.00);

                temp[i][j][2] = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                       image[i - 1][j - 1].rgbtBlue) / 4.00);
            }

            //geriye kalan pikseller (dokuz pikselin ortalaması)
            else if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {

                temp[i][j][0] = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                                       image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                       image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 9.00);

                temp[i][j][1] = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed +
                                       image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                       image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 9.00);

                temp[i][j][2] = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                                       image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                       image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 9.00);
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtGreen = temp[i][j][0];
            image[i][j].rgbtRed = temp[i][j][1];
            image[i][j].rgbtBlue = temp[i][j][2];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //R, G, B  ELEMANLI, KERNEL SON DEĞERLİ 3 BOYUTLU MATRİS ( ..[0] = GREEN, ..[1] = RED, ..[2] = BLUE )
    int temp[height][width][3];

    int Gx; //Gx KERNEL DEĞERİ
    int Gy; //Gy KERNEL DEĞERİ

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int ax, bx, cx, dx, ex, fx;
            ax = (j - 1 < 0) ? 0 : image[i][j - 1].rgbtGreen;
            bx = (j + 1 == width) ? 0 : image[i][j + 1].rgbtGreen;
            cx = (i - 1 < 0 || j - 1 < 0) ? 0 : image[i - 1][j - 1].rgbtGreen;
            dx = (i - 1 < 0 || j + 1 == width) ? 0 : image[i - 1][j + 1].rgbtGreen;
            ex = (i + 1 == height || j - 1 < 0) ? 0 : image[i + 1][j - 1].rgbtGreen;
            fx = (i + 1 == height || j + 1 == width) ? 0 : image[i + 1][j + 1].rgbtGreen;

            int ay, by, cy, dy, ey, fy;
            ay = (i - 1 < 0) ? 0 : image[i - 1][j].rgbtGreen;
            by = (i + 1 == height) ? 0 : image[i + 1][j].rgbtGreen;
            cy = (i - 1 < 0 || j - 1 < 0) ? 0 : image[i - 1][j - 1].rgbtGreen;
            dy = (i + 1 == height || j - 1 < 0) ? 0 : image[i + 1][j - 1].rgbtGreen;
            ey = (i - 1 < 0 || j + 1 == width) ? 0 : image[i - 1][j + 1].rgbtGreen;
            fy = (i + 1 == height || j + 1 == width) ? 0 : image[i + 1][j + 1].rgbtGreen;

            //green gx
            Gx = - 2 * ax + 2 * bx - cx + dx - ex + fx;

            //green gy
            Gy = - 2 * ay + 2 * by - cy + dy - ey + fy;

            //green gx ve gy işlenmiş son hali
            temp[i][j][0] = round(sqrt(Gx * Gx + Gy * Gy));
            if (temp[i][j][0] > 255)
            {
                temp[i][j][0] = 255;
            }

            ax = (j - 1 < 0) ? 0 : image[i][j - 1].rgbtRed;
            bx = (j + 1 == width) ? 0 : image[i][j + 1].rgbtRed;
            cx = (i - 1 < 0 || j - 1 < 0) ? 0 : image[i - 1][j - 1].rgbtRed;
            dx = (i - 1 < 0 || j + 1 == width) ? 0 : image[i - 1][j + 1].rgbtRed;
            ex = (i + 1 == height || j - 1 < 0) ? 0 : image[i + 1][j - 1].rgbtRed;
            fx = (i + 1 == height || j + 1 == width) ? 0 : image[i + 1][j + 1].rgbtRed;

            ay = (i - 1 < 0) ? 0 : image[i - 1][j].rgbtRed;
            by = (i + 1 == height) ? 0 : image[i + 1][j].rgbtRed;
            cy = (i - 1 < 0 || j - 1 < 0) ? 0 : image[i - 1][j - 1].rgbtRed;
            dy = (i + 1 == height || j - 1 < 0) ? 0 : image[i + 1][j - 1].rgbtRed;
            ey = (i - 1 < 0 || j + 1 == width) ? 0 : image[i - 1][j + 1].rgbtRed;
            fy = (i + 1 == height || j + 1 == width) ? 0 : image[i + 1][j + 1].rgbtRed;

            //red gx
            Gx = -2 * ax + 2 * bx - cx + dx - ex + fx;

            //red gy
            Gy = -2 * ay + 2 * by - cy + dy - ey + fy;


            //red gx ve gy işlenmiş son hali
            temp[i][j][1] = round(sqrt(Gx * Gx + Gy * Gy));
            if (temp[i][j][1] > 255)
            {
                temp[i][j][1] = 255;
            }

            ax = (j - 1 < 0) ? 0 : image[i][j - 1].rgbtBlue;
            bx = (j + 1 == width) ? 0 : image[i][j + 1].rgbtBlue;
            cx = (i - 1 < 0 || j - 1 < 0) ? 0 : image[i - 1][j - 1].rgbtBlue;
            dx = (i - 1 < 0 || j + 1 == width) ? 0 : image[i - 1][j + 1].rgbtBlue;
            ex = (i + 1 == height || j - 1 < 0) ? 0 : image[i + 1][j - 1].rgbtBlue;
            fx = (i + 1 == height || j + 1 == width) ? 0 : image[i + 1][j + 1].rgbtBlue;

            ay = (i - 1 < 0) ? 0 : image[i - 1][j].rgbtBlue;
            by = (i + 1 == height) ? 0 : image[i + 1][j].rgbtBlue;
            cy = (i - 1 < 0 || j - 1 < 0) ? 0 : image[i - 1][j - 1].rgbtBlue;
            dy = (i + 1 == height || j - 1 < 0) ? 0 : image[i + 1][j - 1].rgbtBlue;
            ey = (i - 1 < 0 || j + 1 == width) ? 0 : image[i - 1][j + 1].rgbtBlue;
            fy = (i + 1 == height || j + 1 == width) ? 0 : image[i + 1][j + 1].rgbtBlue;

            //blue gx
            Gx = - 2 * ax + 2 * bx - cx + dx - ex + fx;

            //blue gy
            Gy = - 2 * ay + 2 * by - cy + dy - ey + fy;

            //blue gx ve gy işlenmiş son hali
            temp[i][j][2] = round(sqrt(Gx * Gx + Gy * Gy));
            if (temp[i][j][2] > 255)
            {
                temp[i][j][2] = 255;
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtGreen = temp[i][j][0];
            image[i][j].rgbtRed = temp[i][j][1];
            image[i][j].rgbtBlue = temp[i][j][2];
        }
    }

    return;
}
