#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ecriture.h"

int calcPoids(long conv_nbrColis, double *multiplier)
{
    int tranchePoids = 0;
    char longu[1], larg[1], haut[1], poids[1];
    long conv_longu = 0, conv_larg = 0, conv_haut = 0, conv_poids = 0, compteur = 1;
    double poidsVolume = 0, poidsReel = 0, tempPoids = 0;
    do
    {
        if (conv_nbrColis > 1)
        {
            printf("\nColis %ld\n", compteur);
        }
        printf("Longueur (cm) : ");
        conv_longu = lire(longu, 4, 2);
        printf("Largeur (cm) : ");
        conv_larg = lire(larg, 4, 2);
        printf("Hauteur (cm) : ");
        conv_haut = lire(haut, 4, 2);
        printf("Poids (kg) : ");
        conv_poids = lire(poids, 5, 2);
        compteur++;
        poidsVolume = (((conv_longu/100.00)*(conv_larg/100.00)*(conv_haut/100.00))*250.00);
        if (conv_poids < poidsVolume)
        {
            poidsReel += poidsVolume;
        }
        else
        {
            poidsReel += conv_poids;
        }
    } while (conv_nbrColis >= compteur);


    if (poidsReel > 100)
    {
      tempPoids = ceil(poidsReel / 10.00);
      poidsReel = tempPoids * 10;
      *multiplier =  tempPoids / 10.00;
    }
    else
    {
      poidsReel = ceil(poidsReel);
      *multiplier = 1;
    }

    // Definition de la tranche de poids
    if (poidsReel >= 0 && poidsReel <= 9)
    {
        tranchePoids = 0;
    }
    else if (poidsReel > 9 && poidsReel <= 19)
    {
        tranchePoids = 1;
    }
    else if (poidsReel > 19 && poidsReel <= 29)
    {
        tranchePoids = 2;
    }
    else if (poidsReel > 29 && poidsReel <= 39)
    {
        tranchePoids = 3;
    }
    else if (poidsReel > 39 && poidsReel <= 49)
    {
        tranchePoids = 4;
    }
    else if (poidsReel > 49 && poidsReel <= 59)
    {
        tranchePoids = 5;
    }
    else if (poidsReel > 59 && poidsReel <= 69)
    {
        tranchePoids = 6;
    }
    else if (poidsReel > 69 && poidsReel <= 79)
    {
        tranchePoids = 7;
    }
    else if (poidsReel > 79 && poidsReel <= 89)
    {
        tranchePoids = 8;
    }
    else if (poidsReel > 89 && poidsReel <= 99)
    {
        tranchePoids = 9;
    }
    else if (poidsReel > 99 && poidsReel <= 200)
    {
        tranchePoids = 10;
    }
    else if (poidsReel > 200 && poidsReel <= 300)
    {
        tranchePoids = 11;
    }
    else if (poidsReel > 300 && poidsReel <= 400)
    {
        tranchePoids = 12;
    }
    else if (poidsReel > 400 && poidsReel <= 500)
    {
        tranchePoids = 13;
    }
    else if (poidsReel > 500 && poidsReel <= 1000)
    {
        tranchePoids = 14;
    }
    else if (poidsReel > 1000 && poidsReel <= 2000)
    {
        tranchePoids = 15;
    }
    else if (poidsReel > 2000)
    {
        tranchePoids = 16;
    }
    else
    {
        printf("Erreur sur le poids.\n");
        return 0;
    }
    return tranchePoids;
}

int calcZone(char pays[1][0])
{
  int zone = -1;
  int i = 0;
  const char *zonePays[33] = { "ALL", "AND", "AUT", "BEL", "BOS", "BUL", "CRO", "DAN", "ESP", "EST", "FIN", "HON", "IRL", "ITA", "KOS", "LET", "LIE", "LIT", "LUX", "MAC", "MON", "NOR", "PAY", "POL", "POR", "REP", "ROU", "ANG", "ECO", "SER", "SLO", "SUE", "SUI" };
  for (i = 0; i < 32; i++)
  {
    if (strncmp(pays[0], zonePays[i], 3) == 0)
    {
      zone = i;
    }
  }
  if (zone <= -1)
  {
    printf("Erreur dans la saisie, veuillez saisir les 3 premieres lettres du pays.\n");
  }
  return zone;
}

double calcTarif(int poidsTranche, int zone, double multiplier)
{
    const double tgo = 1.13;
    double prixBase = 0;
    const double tablePrix[33][17] = {
    { 43.77, 47.04, 50.30, 53.57, 56.82, 60.09, 63.36, 66.61, 69.88, 76.69, 76.69, 66.47, 59.90, 54.96, 54.61, 47.83, 41.40 },
    { 36.59, 46.76, 57.60, 67.13, 76.06, 80.34, 94.69, 103.51, 113.21, 125.51, 115.85, 104.45, 97.40, 93.59, 88.56, 76.79, 73.20},
    { 60.15, 71.05, 81.94, 92.83, 103.72, 114.59, 125.48, 136.37, 147.27, 158.16, 143.58, 121.55, 111.56, 105.63, 94.93, 79.06, 75.12 },
    { 32.32, 36.54, 40.76, 44.98, 49.20, 53.43, 57.66, 61.89, 66.11, 70.32, 60.39, 50.77, 43.08, 37.63, 35.56, 30.59, 26.02 },
    { 126.50, 127.93, 130.42, 132.47, 134.31, 168.55, 169.58, 170.59, 171.62, 172.54, 181.95, 152.50, 137.57, 127.70, 110.20, 99.42, 99.36 },
    { 130.06, 132.92, 135.52, 138.63, 141.98, 158.64, 161.39, 164.11, 166.86, 169.64, 163.30, 137.97, 121.31, 111.57, 93.51, 82.64, 82.60 },
    { 105.42, 106.61, 108.68, 110.38, 111.91, 140.47, 141.33, 142.17, 143.02, 143.79, 151.62, 127.08, 114.65, 106.42, 91.85, 82.86, 82.80 },
    { 68.90, 74.29, 79.21, 82.69, 87.30, 100.33, 104.36, 108.25, 111.98, 115.55, 104.22, 98.94, 85.11, 80.30, 73.23, 64.52, 62.47 },
    { 46.76, 52.80, 58.84, 64.88, 70.93, 76.97, 83.00, 89.05, 95.08, 101.13, 93.73, 81.24, 71.07, 63.96, 62.36, 53.64, 45.58 },
    { 130.56, 135.84, 140.50, 149.20, 153.72, 162.12, 166.14, 170.05, 173.75, 177.32, 169.95, 143.79, 130.46, 121.10, 103.36, 86.50, 81.22 },
    { 91.97, 97.24, 102.02, 104.44, 108.96, 113.32, 117.44, 121.45, 125.28, 128.93, 141.54, 118.06, 104.60, 96.09, 85.94, 73.11, 70.77 },
    { 86.11, 86.90, 88.37, 89.58, 90.66, 112.79, 113.37, 113.92, 114.48, 114.98, 122.34, 102.74, 92.80, 86.19, 74.52, 66.97, 66.94 },
    { 90.03, 98.15, 106.28, 114.43, 122.59, 130.73, 138.90, 147.09, 155.27, 163.45, 147.93, 128.20, 112.18, 100.95, 98.43, 84.65, 71.97 },
    { 45.42, 49.89, 54.36, 58.82, 63.28, 67.74, 72.21, 76.67, 81.14, 84.14, 84.98, 74.38, 65.74, 59.72, 58.80, 51.03, 43.80 },
    { 287.51, 290.40, 295.68, 299.96, 303.84, 379.88, 381.98, 384.01, 386.08, 387.94, 411.08, 344.95, 311.41, 289.16, 249.85, 224.98, 224.81 },
    { 112.94, 118.66, 123.70, 132.80, 137.67, 142.30, 146.77, 151.05, 155.15, 159.09, 145.64, 117.08, 104.17, 95.65, 85.08, 77.00, 74.87 },
    { 60.69, 67.56, 74.43, 81.30, 88.15, 95.03, 101.89, 108.76, 115.63, 122.50, 105.40, 94.10, 84.80, 78.61, 78.95, 67.90, 57.71 },
    { 100.37, 106.37, 111.69, 119.50, 124.68, 141.31, 145.79, 150.09, 154.22, 158.17, 142.75, 115.88, 103.32, 94.88, 82.65, 73.06, 70.26 },
    { 34.49, 38.99, 43.50, 48.00, 52.51, 57.03, 61.54, 66.06, 70.56, 75.05, 65.10, 55.25, 47.36, 41.76, 39.86, 34.59, 29.70 },
    { 273.33, 276.60, 280.71, 284.59, 288.36, 297.95, 301.46, 304.93, 308.45, 311.93, 318.91, 277.59, 248.01, 231.58, 202.48, 186.09, 178.58 },
    { 314.31, 318.09, 322.83, 327.26, 331.61, 342.66, 346.66, 350.66, 354.70, 358.71, 366.75, 319.24, 285.21, 266.30, 232.85, 213.99, 205.36 },
    { 71.43, 76.51, 105.68, 134.80, 138.02, 141.13, 144.07, 146.92, 170.90, 173.07, 187.78, 165.19, 151.14, 142.38, 125.87, 117.73, 118.58 },
    { 35.94, 40.22, 44.53, 48.82, 53.08, 57.39, 61.66, 65.97, 70.25, 74.54, 70.72, 58.21, 49.30, 42.95, 40.52, 35.48, 30.69 },
    { 51.61, 58.85, 65.36, 70.32, 76.50, 89.82, 95.33, 100.61, 105.67, 110.53, 113.42, 97.07, 91.01, 84.74, 78.67, 73.06, 71.49 },
    { 48.34, 55.18, 62.02, 68.86, 75.70, 82.55, 89.39, 96.24, 103.09, 109.93, 106.94, 92.68, 81.10, 72.98, 71.16, 61.20, 52.01 },
    { 70.98, 73.98, 77.66, 79.92, 82.19, 89.06, 95.85, 98.24, 103.45, 110.91, 102.37, 96.32, 91.44, 85.69, 82.92, 80.55, 76.55 },
    { 200.57, 202.75, 205.50, 208.08, 210.61, 215.34, 217.66, 219.97, 222.33, 224.63, 224.61, 192.89, 170.93, 158.73, 137.54, 125.86, 120.78 },
    { 38.05, 43.36, 48.66, 53.98, 59.27, 64.58, 69.88, 75.19, 80.50, 85.81, 76.59, 67.04, 59.24, 53.81, 50.99, 45.93, 39.41 },
    { 70.99, 80.89, 90.79, 100.72, 110.61, 120.52, 130.41, 140.31, 150.22, 160.12, 142.92, 125.09, 110.53, 100.45, 94.17, 85.60, 73.45 },
    { 139.17, 140.72, 143.45, 145.70, 147.73, 185.40, 186.56, 187.65, 188.78, 189.78, 200.15, 167.75, 151.32, 140.47, 121.24, 109.36, 109.30 },
    { 79.35, 83.08, 87.78, 90.45, 93.09, 106.62, 108.99, 111.41, 113.83, 122.09, 122.91, 107.77, 98.00, 91.37, 83.15, 78.83, 75.76 },
    { 66.64, 71.95, 88.16, 90.68, 95.00, 127.56, 130.91, 153.99, 156.69, 159.23, 158.21, 128.79, 112.46, 105.43, 94.64, 84.14, 81.29 },
    { 67.15, 74.75, 82.36, 89.97, 97.55, 105.15, 112.76, 120.36, 127.96, 135.56, 116.65, 104.13, 93.86, 87.00, 87.36, 75.13, 63.86 }
    };

    prixBase = (tablePrix[zone][poidsTranche] * multiplier + 0.99) * tgo;

    return prixBase;
}
