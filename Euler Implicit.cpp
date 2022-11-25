#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define N 100

int main(){
	
double dt, dz, T_c, t_a, sigma, kappa, P_ext, V, gamma;
int i, j, M;

sigma=0.472;
kappa=0.56;
V=40;
P_ext=0.5*sigma*V*V;
t_a=0.025;
dz=0.02;
dt=0.5*dz;
M=t_a/dt + 1.0;
T_c=(kappa/P_ext)*(36.5+273.15); 
gamma=dt/(dz*dz);

double T[N][M];
double T_old[N][M];
double T_new[N][M];


for(i=0; i<N; i++){
	T_old[i][0]=T_c;
}

for(j=0; j<M; j++){
	T_old[0][j]=T_c;
	T_old[99][j]=T_c;
}


for(j=1; j<M; j++){

	for(i=1; i<N-1; i++){
		T_new[i][j]=(1/(1+2*gamma))*((T_old[i-1][j]+T_old[i][j])*gamma+dt+T_old[i][j-1]);
		printf("%lf", T_new[i][j]);
		}
	
		for(i=1; i<N; i++){
			T_old[i][j]=T_new[i][j];
		}
	}	



return 0;	
}
