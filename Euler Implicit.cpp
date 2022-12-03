#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define N 100

int main(){
	
double dt, dz, T_c, t_a, sigma, kappa, P_ext, V, gamma;
int i, j, k, M;

sigma=0.472;
kappa=0.56;
V=40;
P_ext=0.5*sigma*V*V;
t_a=0.025;
dz=0.02;
dt=0.005*dz;
M=t_a/dt + 1.0;
T_c=(kappa/P_ext)*(36.5+273.15); 
gamma=dt/(dz*dz);

double T[N][M];
double T_old[N][M];
double T_new[N];
double T_guess[N];


for(i=0; i<N; i++){
	T_old[i][0]=T_c;

}

for(j=0; j<M; j++){
	T_old[0][j]=T_c;
	T_old[99][j]=T_c;
}



for(j=0; j<M; j++){
	//printf("%d", j);
}

for(j=1; j<M; j++){
	
	
	for (i = 0; i < N; i++){
		T_guess[i]=T_old[i][j-1];
	}
	
	
	for(k=1; k<4000; k++){	
		for(i=1; i<N-1; i++){
			T_new[i]=(1/(1+2*gamma))*((T_guess[i-1]+T_guess[i+1])*gamma+dt+T_old[i][j-1]);
			}
			
		for(i=1; i<N-1; i++){	
			T_guess[i]=T_new[i];
			}
		}
		
	for(i=1; i<N-1; i++){
		T_old[i][j]=T_new[i];
			}
	}	

	for(j=0; j<M;j++){
		printf("%lf \t %\lf \n", T_old[55][j], T_old[90][j]);
	 }

FILE *files[N];
for (i = 0; i < N; i++)
{
    char filename[20];
    sprintf(filename, "euler_implicit%d.dat", i+1);
    files[i] = fopen(filename, "w");
    fprintf(files[i], "Temps \t Temperatura\n");
    for(j=0; j<M; j++){
    	fprintf(files[i], "%lf \t %lf\n", j*dt, T_old[i][j]);
	}
	fclose(files[i]);
    
}

return 0;	
}
