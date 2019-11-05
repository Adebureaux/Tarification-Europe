#ifndef CALCU_H_INCLUDED
#define CALCU_H_INCLUDED

int calcPoids(long conv_nbrColis, double *multiplier);
int calcZone(char pays[1][0]);
double calcTarif(int poidsTranche, int zone, double multiplier);

#endif // CALCU_H_INCLUDED
