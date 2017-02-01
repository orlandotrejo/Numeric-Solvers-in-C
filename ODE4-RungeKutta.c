// Numeric solver Runge Kutta 4th order. The example to be solved is (dy/dx = 2x), the result is x^2.
#include <stdio.h>
#include <math.h>
 
void ode45(int NUM, float *yout,float t0,float tfinal,float *x0,
           void (*objetivo)(float *,float *));
void (*objetivo)(float, float) = NULL; //Entrada y Salida
void cuadrado (float *X, float *Y);
 
float x[]={0},y[]={0};
float t1=0.0;
 
int main()
{
    int i;
 
    for(i=0;i<=1000;i++){
 
        t1=t1+0.02;
        ode45(1,y,0,1e-4,x,cuadrado);
        x[0] = y[0];
        printf("%f\r\n",x[0]*0.02/0.0001);
 
    }
 
    return 0;
}
 
void ode45(int NUM, float *yout,float t0,float tfinal,float *x0,
           void (*objetivo)(float *,float *))
{
    //INTEGRADOR PARA RESOLUCION DE ECUACIONES DIFERENCIALES
    //ENTRADAS: NUM de variables, *resultado, t_inicio, t_fin, *cond.inicial,
    //          paso de int, apuntador a la funcion objetivo
    //SALIDAS: ninguna, se pasan parametros por referencia en *yout
    //LIMITANTES: Runge Kutta de 4to orden con error de 5to orden
    //            el *objetivo debe tener parametros consistentes in-out
 
    int i;
    float t,h;
    float s1[NUM],s2[NUM],s3[NUM],s4[NUM],xt[NUM];
 
    t = t0;
    h = (tfinal - t);
 
    objetivo(x0,s1);
    for(i=0;i<NUM;i++) xt[i]=x0[i]+h*s1[i]/2.0;
 
    objetivo(xt,s2);
    for(i=0;i<NUM;i++) xt[i]=x0[i]+h*s2[i]/2.0;
 
    objetivo(xt,s3);
    for(i=0;i<NUM;i++) xt[i]=x0[i]+h*s3[i];
 
    objetivo(xt,s4);
    for(i=0;i<NUM;i++) yout[i]=x0[i]+h*(s1[i]+2.0*s2[i]+2.0*s3[i]+s4[i])/6.0;
}
 
void cuadrado (float *X, float *Y)
{
    Y[0]=t1*2;
}
