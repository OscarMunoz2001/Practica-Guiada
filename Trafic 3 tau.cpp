#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define M 5

int main(){

double tau, m, C, v_eq, L, dt, d, t, o, w;

int i, j, N, t_c, n;

dt = 0.001;
L = 4;
d = 26/L;
n = 20;
C = 20000;
m = 1500;
t = 20;
tau = ((C)/(m*L))*n*dt;
N = t/dt;
v_eq = (m/C)*(120/3.6);
t_c = ((C)/m*L)*2;
o=M*d+(M+1);
//printf("%lf", v_eq);
w=3;
//printf("%lf", o);

printf("hola");

double x[N][M];
double v[N][M];
double k1[M];
double k2[M];
double k3[M];
double k4[M];
double l1[M];
double l2[M];
double l3[M];
double l4[M];


/* Bucle condiciones iniciales */

for(i=0; i<t_c; i++){
	for(j=0; j<M; j++){
		x[0][j]=(M-1-j)*d+M-1-j;
		v[0][j]=v_eq;
		//printf("%lf \t %lf\n", x[0][j], v[0][j]);
	}
}

/*Bucle lineal */

for(i=1; i<t_c; i++){
	for(j=0; j<M; j++){
		x[i][j]=x[i-1][j]+v_eq*dt;
	}
//printf("%lf \t %lf \t %lf \t %lf \t %lf\n", x[i][0],x[i][1],x[i][2],x[i][3],x[i][4]);
}

/*Bucle no lineal*/

//Bucle para el primer coche y definiciones de k_0 y l_0

for(i=t_c; i<N; i++){
	x[i][0]=x[i-1][0]+v_eq*dt*(1-0.8*sin(dt*w*(i-t_c)));
	v[i][0]=v_eq*(1-0.8*sin(dt*w*(i-t_c)));
	//printf("%lf\n", x[i][0]);
}

//printf("%lf", v_eq*dt*(1-(t_c*dt-t_c)*exp(1-(t_c*dt-t_c))));

k1[0]=k2[0]=k3[0]=k4[0]=0;
l1[0]=0.2*v_eq;
l2[0]=0.2*v_eq+0.5*dt*l1[0];
l3[0]=0.2*v_eq+0.5*dt*l2[0];
l4[0]=0.2*v_eq+dt*l3[0];

//Bucle para el resto de coches

for(j=1; j<M; j++){
	x[t_c][j]=x[t_c-1][j]+v_eq*dt;
	v[t_c][j]=v_eq;
}

for(i=t_c; i<N; i++){
	for(j=1; j<M; j++){
		k1[j]=v[i][j];
		l1[j]=-((v[i][j]-v[i-n][j-1])/fabs(x[i][j]-x[i-n][j-1]));
	}
	for(j=1; j<M; j++){
		k2[j]=v[i][j]+0.5*dt*l1[j];
		l2[j]=-(((v[i][j]+0.5*dt*l1[j])-(v[i-n][j-1]+0.5*dt*l1[j-1]))/fabs(((x[i][j]+0.5*dt*k1[j])-(x[i-n][j-1]))));
	}
	for(j=1; j<M; j++){
		k3[j]=v[i][j]+0.5*dt*l2[j];
		l3[j]=-(((v[i][j]+0.5*dt*l2[j])-(v[i-n][j-1]+0.5*dt*l2[j-1]))/fabs((x[i][j]+0.5*dt*k2[j])-(x[i-n][j-1])));
	}
	for(j=1; j<M; j++){
		k4[j]=v[i][j]+dt*l3[j];
		l4[j]=-(((v[i][j]+dt*l3[j])-(v[i-n][j-1]+dt*l3[j-1]))/fabs((x[i][j]+dt*k3[j])-(x[i-n][j-1])));
	}
	for(j=1; j<M; j++){
		x[i+1][j]=x[i][j]+(dt/6)*(k1[j]+2*k2[j]+2*k3[j]+k4[j]);
		v[i+1][j]=v[i][j]+(dt/6)*(l1[j]+2*l2[j]+2*l3[j]+l4[j]);
	}	
}

for(i=t_c; i<N; i++){
	printf("%lf \t %lf \t %lf \t %lf \t %lf\n", x[i][0],x[i][1],x[i][2],x[i][3],x[i][4]);
	printf("%lf \t %lf \t %lf \t %lf \t %lf\n", v[i][0],v[i][1],v[i][2],v[i][3],v[i][4]);
}

FILE* output1;

output1=fopen("Trafic3 tau posicions", "w");

fprintf(output1, "Coche 1 \t Coche 2 \t Coche 3 \t Coche 4 \t Coche 5");

for(i=t_c; i<N; i++){
	fprintf(output1,"%lf \t %lf \t %lf \t %lf \t %lf\n", x[i][0],x[i][1],x[i][2],x[i][3],x[i][4]);
}

fclose(output1);

FILE* output2;

output2=fopen("Trafic3 tau velocitats", "w");

fprintf(output2, "Coche 1 \t Coche 2 \t Coche 3 \t Coche 4 \t Coche 5");

for(i=t_c; i<N; i++){
	fprintf(output2,"%lf \t %lf \t %lf \t %lf \t %lf\n", v[i][0],v[i][1],v[i][2],v[i][3],v[i][4]);
}

fclose(output2);

}
