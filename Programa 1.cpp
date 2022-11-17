#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define N 300000

double Preses[N], Depredadors[N];

int main(){
	
	double dt, k2;
	
	Preses[0] = 0.5;
	Depredadors[0] = 0.9;
	
	dt = 0.0001;
	k2 = 1.0;
	
	Preses[1] = Preses[0] + dt*Preses[0]*(1-Depredadors[0]);
	Depredadors[1] = Depredadors[0] + dt*Depredadors[0]*(Preses[0]-k2);
	
	printf("Preses[1] = %lf \t Depredadors[1] = %lf \n", Preses[1], Depredadors[1]);
	
	int i;
	
	for(i=1; i<N; i++){
		Preses[i] = Preses[i-1] + dt*Preses[i-1]*(1-Depredadors[i-1]);
		Depredadors[i] = Depredadors[i-1] + dt*Depredadors[i-1]*(Preses[i-1]-k2);
		printf("Preses: %lf \t Depredadors: %lf \n", Preses[i], Depredadors[i]);
	}
	
	FILE* output;
	
	output = fopen("poblacions.txt", "w");
	
	fprintf(output, "time \t Preses \t Depredadors\n");
	
	for(i=0; i<N; i++){
		fprintf(output, "%lf \t %lf \t %lf\n", i*dt, Preses[i], Depredadors[i]);
	
	}

	fclose(output);
	
	return 0;
}
