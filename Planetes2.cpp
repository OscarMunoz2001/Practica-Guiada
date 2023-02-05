#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define M 9 //El nombre de cossos que simularem sera 9, des del Sol fins a Neptú

int main(){

int i, j, k, l, N;
double dt, T_nep;

//Aquí fiquem totes les constants que necessitem per al problema

dt=0.00056; //el pas de temps més petit que podem agafar sense que el metode divergeixi, equival a 33,71 dies terrestres
T_nep=1; // periode orbital de Neptú normalitzat
N = T_nep/dt;

//printf("%d", N);

double x[N][M], y[N][M], v_x[N][M], v_y[N][M], x_2[N][M], x_3[N][M], x_4[N][M], y_2[N][M], y_3[N][M], y_4[N][M];
double v_x_2[N][M], v_x_3[N][M], v_x_4[N][M], v_y_2[N][M], v_y_3[N][M], v_y_4[N][M];
double k1_x[M], k2_x[M], k3_x[M], k4_x[M], k1_y[M], k2_y[M], k3_y[M], k4_y[M];
double l1_x[M], l2_x[M], l3_x[M], l4_x[M], l1_y[M], l2_y[M], l3_y[M], l4_y[M];
double l1_x_old[M], l2_x_old[M], l3_x_old[M], l4_x_old[M], l1_y_old[M], l2_y_old[M], l3_y_old[M], l4_y_old[M];

double a[M] = {0.0, 0.012867, 0.024, 0.03311, 0.05067, 0.17289, 0.3178, 0.6378, 1};
double b[M] = {0.0, 0.05652977778, 0.04046755556, 0.03441244444, 0.02781422222, 0.01508, 0.01113955556, 0.00786933333, 0.00627466666};

double m[M]={39.21390206, 0.00000649604, 0.00009565815, 0.0001184339, 0.0000126752, 0.03762950198, 0.01184339062, 0.00171709359, 0.0020795251};

for(j=0; j<M; j++){
	x[0][j]=0;
	y[0][j]=a[j];
	v_x[0][j]=b[j];
	v_y[0][j]=0;
}

for(i=0; i<N; i++){
	for(j=0; j<M; j++){
		k1_x[j]=v_x[i][j];
		k1_y[j]=v_y[i][j];
		
		for(k=0; k<M; k++){
			if(k!=j){
				l1_x_old[k]=(m[k]*(x[i][k]-x[i][j]))/(pow((pow(x[i][j]-x[i][k], 2)+ pow(y[i][j]-y[i][k], 2)), 1.5));
				l1_y_old[k]=(m[k]*(y[i][k]+y[i][j]))/(pow((pow(x[i][j]-x[i][k], 2)+ pow(y[i][j]-y[i][k], 2)), 1.5));
				
				if(k==0){
					l1_x[k]=l1_x_old[k];
					l1_y[k]=l1_y_old[k];
				}
				else{
					l1_x[k]=l1_x[k-1] + l1_x_old[k];
					l1_y[k]=l1_y[k-1] + l1_y_old[k];
				}
			}
			else{
			}
		}
	}
	
	for(j=0; j<M; j++){
		
		k2_x[j]=v_x[i][j]+0.5*dt*l1_x[8];
		k2_y[j]=v_y[i][j]+0.5*dt*l1_y[8];

		
		for(l=0; l<M; l++){
			if(l!=j){
				//printf("%lf \t %d\n", x[i][j], l);
				l2_x_old[l]=(m[l]*(x[i][l]+0.5*dt*k1_x[l]-(x[i][j]+0.5*dt*k1_x[j])))/(pow((pow(x[i][j]+0.5*dt*k1_x[j]-(x[i][l]+0.5*dt*k1_x[l]), 2)+ pow(y[i][j]+0.5*dt*k1_y[j]-(y[i][l]+0.5*dt*k1_y[l]), 2)), 1.5));
				l2_y_old[l]=(m[l]*(y[i][l]+0.5*dt*k1_y[l]-(y[i][j]+0.5*dt*k1_y[j])))/(pow((pow(x[i][j]+0.5*dt*k1_x[j]-(x[i][l]+0.5*dt*k1_x[l]), 2)+ pow(y[i][j]+0.5*dt*k1_y[j]-(y[i][l]+0.5*dt*k1_y[l]), 2)), 1.5));
				//printf("%lf \t %d \t %d \t %d \t %lf \t %lf \n", l2_x_old[j], i, j, l, x_2[i][j], x_2[i][l]);
				
				if(l==0){
					l2_x[l]=l2_x_old[l];
					l2_y[l]=l2_y_old[l];
				}
				else{
					l2_x[l]=l2_x[l-1] + l2_x_old[l];
					l2_y[l]=l2_y[l-1] + l2_y_old[l];
				}
			}
			else{
			}
		//printf("%lf \t %lf \t %d\n", l2_x[8], l2_y[8], j);
		}
	}
		
for(j=0; j<M; j++){
		
		k3_x[j]=v_x[i][j]+0.5*dt*l2_x[8];
		k3_y[j]=v_y[i][j]+0.5*dt*l2_y[8];

		
		for(l=0; l<M; l++){
			if(l!=j){
				//printf("%lf \t %d\n", x[i][j], l);
				l3_x_old[l]=(m[l]*(x[i][l]+0.5*dt*k2_x[l]-(x[i][j]+0.5*dt*k2_x[j])))/(pow((pow(x[i][j]+0.5*dt*k2_x[j]-(x[i][l]+0.5*dt*k2_x[l]), 2)+ pow(y[i][j]+0.5*dt*k2_y[j]-(y[i][l]+0.5*dt*k2_y[l]), 2)), 1.5));
				l3_y_old[l]=(m[l]*(y[i][l]+0.5*dt*k2_y[l]-(y[i][j]+0.5*dt*k2_y[j])))/(pow((pow(x[i][j]+0.5*dt*k2_x[j]-(x[i][l]+0.5*dt*k2_x[l]), 2)+ pow(y[i][j]+0.5*dt*k2_y[j]-(y[i][l]+0.5*dt*k2_y[l]), 2)), 1.5));
				//printf("%lf \t %d \t %d \t %d \t %lf \t %lf \n", l2_x_old[j], i, j, l, x_2[i][j], x_2[i][l]);
				
				if(l==0){
					l3_x[l]=l3_x_old[l];
					l3_y[l]=l3_y_old[l];
				}
				else{
					l3_x[l]=l3_x[l-1] + l3_x_old[l];
					l3_y[l]=l3_y[l-1] + l3_y_old[l];
				}
			}
			else{
			}
		//printf("%lf \t %lf \t %d\n", l2_x[8], l2_y[8], j);
		}
	}
		
for(j=0; j<M; j++){
		
		k4_x[j]=v_x[i][j]+dt*l3_x[8];
		k4_y[j]=v_y[i][j]+dt*l3_y[8];

		
		for(l=0; l<M; l++){
			if(l!=j){
				//printf("%lf \t %d\n", x[i][j], l);
				l4_x_old[l]=(m[l]*(x[i][l]+0.5*dt*k3_x[l]-(x[i][j]+0.5*dt*k3_x[j])))/(pow((pow(x[i][j]+0.5*dt*k3_x[j]-(x[i][l]+0.5*dt*k3_x[l]), 2)+ pow(y[i][j]+0.5*dt*k3_y[j]-(y[i][l]+0.5*dt*k3_y[l]), 2)), 1.5));
				l4_y_old[l]=(m[l]*(y[i][l]+0.5*dt*k3_y[l]-(y[i][j]+0.5*dt*k3_y[j])))/(pow((pow(x[i][j]+0.5*dt*k3_x[j]-(x[i][l]+0.5*dt*k3_x[l]), 2)+ pow(y[i][j]+0.5*dt*k3_y[j]-(y[i][l]+0.5*dt*k3_y[l]), 2)), 1.5));
				//printf("%lf \t %d \t %d \t %d \t %lf \t %lf \n", l2_x_old[j], i, j, l, x_2[i][j], x_2[i][l]);
				
				if(l==0){
					l4_x[l]=l4_x_old[l];
					l4_y[l]=l4_y_old[l];
				}
				else{
					l4_x[l]=l4_x[l-1] + l4_x_old[l];
					l4_y[l]=l4_y[l-1] + l4_y_old[l];
				}
			}
			else{
			}
		//printf("%lf \t %lf \t %d\n", l2_x[8], l2_y[8], j);
		}
		
		x[i+1][j]=x[i][j]+(dt/6)*(k1_x[j]+2*k2_x[j]+2*k3_x[j]+k4_x[j]);
		y[i+1][j]=y[i][j]+(dt/6)*(k1_y[j]+2*k2_y[j]+2*k3_y[j]+k4_y[j]);
		v_x[i+1][j]=v_x[i][j]+(dt/6)*(l1_x[8]+2*l2_x[8]+2*l3_x[8]+l4_x[8]);
		v_y[i+1][j]=v_y[i][j]+(dt/6)*(l1_y[8]+2*l2_y[8]+2*l3_y[8]+l4_y[8]);

		
	}
//printf("\n");
printf("%lf \t %lf \t %lf \t %lf \t %d\n", x[i][1], y[i][1], v_x[i][1], v_y[i][1], i);

}
return 0;
}

