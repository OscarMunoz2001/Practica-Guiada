#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define N 100


int main(){

/*Definició de variables*/

double T[N][M];

double dt, dz,T_c,t_a,M;
int i,j,M;

t_a=0.025
dz=0.02
dt=0.51*dz*dz
M=t_a/dt + 1
T_c=1 /*CAMBIAR*/

/*Definició de condicions de contorn*/

for(i=0; i<N; i++){
	T[i][0]=T_c;
}

for(j=0; j<M; j++){
	T[0][j]=T_c;
	T[99][j]=T_c;
}

for(j=1; j<M; j++){
	for(i=1; i<N-1; i++){
		T[i][j]=(dt/(dz*dz))*(T[i+1][j]-2T[i][j]+T[i-1][j])+dt+T[i][j]
	}
}

}
