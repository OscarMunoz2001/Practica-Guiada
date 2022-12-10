#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define N 101


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
dt=0.49*dz*dz;
M=t_a/dt + 1.0;
T_c=(kappa/P_ext)*(36.5+273.15); 

printf("%d", M);

double T[N][M];

/*Definició de condicions de contorn*/

for(i=0; i<N; i++){
	T[i][0]=T_c;
}

for(j=0; j<M; j++){
	T[0][j]=T_c;
	T[100][j]=T_c;
}

for(j=1; j<M; j++){
	for(i=1; i<N-1; i++){
		T[i][j]=(dt/(dz*dz))*(T[i+1][j-1]-2*T[i][j-1]+T[i-1][j-1])+dt+T[i][j-1];
	}
}

FILE* output3;

output3=fopen("explicit049.dat", "w");

for(i=0; i<N; i++){
	fprintf(output3, "%lf \t %lf\n", i*dz, T[i][M-1]*(P_ext/kappa)-273.15);
}

fclose(output3);

FILE* output;

output=fopen("dataexplicit2.dat", "w");

for(j=0; j<M; j++){
	for(i=0; i<N; i++){
		fprintf(output,"%lf \t %lf\n", i*dz, T[i][j]*(P_ext/kappa)-273.15);
	}
	fprintf(output, "\n");
	fprintf(output, "\n");
}

fclose(output);

FILE* output2;

output2=fopen("dataexplicit_t.dat", "w");

for(i=0; i<N; i++){
	for(j=0; j<M; j++){
		fprintf(output2,"%lf \t %lf\n", i*dz*100, T[i][j]*(P_ext/kappa)-273.15);
	}
	fprintf(output2, "\n");
	fprintf(output2, "\n");
}

fclose(output2);

/*

FILE *files[N];
for (i = 0; i < N; i++)
{
    char filename[20];
    sprintf(filename, "euler_explicit%d.dat", i+1);
    files[i] = fopen(filename, "w");
    fprintf(files[i], "Temps \t Temperatura\n");
    for(j=0; j<M; j++){
    	fprintf(files[i], "%lf \t %lf\n", (j*dt)*((0.02*0.02*3686*1081)/(kappa)), T[i][j]*(P_ext/kappa)-273.15);
	}
	fclose(files[i]);
    
}

*/

}


