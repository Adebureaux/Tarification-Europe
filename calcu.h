#ifndef CALCU_H_INCLUDED
#define CALCU_H_INCLUDED

int calcPoids(long conv_nbrColis, long *poidsSup);
int calcZone(char *pays[1]);
double calcTarif(int poidsTranche, long poidsSup, int zone, long nbrColis, int fraisDossier);

#endif // CALCU_H_INCLUDED
