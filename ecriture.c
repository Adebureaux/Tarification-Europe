//
//  ecriture.c
//  Tarification-Europe
//
//  Created by Augustin Debureaux on 18/08/2019.
//  Copyright © 2019 Augustin Debureaux. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

long lire(char *chaine, int longueur, int var)
{
    char *positionEntree = NULL;
    int i = 0;
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        for (i = 0; chaine[i]; ++i) // Remplace chaque carractère miniscule par une majuscule.
            chaine[i] = (toupper(chaine[i]));

        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }

        if (var == 2) // Double
        {
          return strtod(chaine, NULL);
        }
        else if (var == 1) // Long
        {
          return strtol(chaine, NULL, 10);
        }
        else // Nothing
        {
          return 0;
        }
    }
    else
    {
        printf("Erreur buffer\n");
        viderBuffer();
        return 0;
    }
}
