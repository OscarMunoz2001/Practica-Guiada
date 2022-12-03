#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define N 100


int main(){

/*Definició de variables*/

double dt, dz, T_c, t_a, sigma, kappa, P_ext, V;
int i, j, M;

sigma=0.472;
kappa=0.56;
V=40;
P_ext=0.5*sigma*V*V;
t_a=0.025;
dz=0.02;
dt=0.25*dz*dz;
M=t_a/dt + 1.0;
T_c=(kappa/P_ext)*(36.5+273.15); 

double T[N][M];

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
		T[i][j]=(dt/(dz*dz))*(T[i+1][j-1]-2*T[i][j-1]+T[i-1][j-1])+dt+T[i][j-1];
	}
}

FILE *files[N];
for (i = 0; i < N; i++)
{
    char filename[20];
    sprintf(filename, "euler_explicit%d.dat", i+1);
    files[i] = fopen(filename, "w");
    fprintf(files[i], "Temps \t Temperatura\n");
    for(j=0; j<M; j++){
    	fprintf(files[i], "%lf \t %lf\n", j*dt, T[i][j]);
	}
	fclose(files[i]);
    
}

}


