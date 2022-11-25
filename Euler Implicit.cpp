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
dt=0.5*dz;
M=t_a/dt + 1.0;
T_c=(kappa/P_ext)*(36.5+273.15); 
gamma=dt/(dz*dz);

double T[N][M];
double T_old[N][M];
double T_new[N];
double T_guess[M];

T_guess[0]=T_c;


for(i=0; i<N; i++){
	T_old[i][0]=T_c;
}

for(j=0; j<M; j++){
	T_old[0][j]=T_c;
	T_old[99][j]=T_c;
}


for(j=1; j<M; j++){
	
	for (i = 0; i < N; i++){
		
		T_guess[i]=T_old[i][j-1];
	}
	for(k=1; k<400; k++){	
		for(i=1; i<N-1; i++){
			T_new[i]=(1/(1+2*gamma))*((T_guess[i-1]+T_guess[i+1])*gamma+dt+T_old[i][j-1]);
			}
			
		for(i=1; i<N-1; i++){	
			T_guess[i]=T_new[i];
			}
		}
		
	for(i=1; i<N; i++){
		T_old[i][j]=T_new[i];
			}
	}	

for(i=0; i<N; i++){
	for(j=0; j<N;j++){
		printf("%lf", T_old[i][j]);
		}
		
}


return 0;	
}
