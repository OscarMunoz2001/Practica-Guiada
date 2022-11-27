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
T_c=(kappa/P_ext)*(36.5+273.15); /*CAMBIAR*/

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
/*
for(i=0; i<N; i++){
	for(j=0; j<M; j++){
		printf("%lf \t", T[i][j]);
	}
}
*/
for(j=0; j<M; j++){

	printf("%lf \t", T[55][j]);
}

FILE* output;

output=fopen("temperatura.txt","w");

for(i=0; i<N; i++){
	for(j=0; j<M; j++){
		fprintf(output, "%lf \t", T[i][j]);
	}
}
	
fclose(output);

FILE* vector_final;

vector_final=fopen("t_final.dat", "w");

fprintf(vector_final, "Espai \t Temperatura\n");

for(i=0; i<N; i++){
	for(j=0; j<M; j++){
		fprintf(vector_final, "%lf\n",T[i][j]);
	}
}

fclose(vector_final);


return 0;

}

