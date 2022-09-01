/*---------------------------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN
* Autor: Diego Alejandro Morales Escobar
* Curso:       CC3086 - Programación de microprocesadores     Ciclo II - 2022
------------------------------------------------------------------------------*/

#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <iostream>

void *serie(void *arg){
    float *total = (float *)malloc(sizeof(float));
    float resultado = 0.0; 
    float *n = (float *)arg;
    float n_sum = *n; 
    resultado = (n_sum)*(n_sum+1);
    *total = 1/resultado;
    //imprime el n y el resultado de la serie con mensaje: Cuando n es: el resultado es:
    printf("Cuando n es: %.0f el resultado es: %.5f\n", *n, *total);
    return (void *)total;   

}
using namespace std;
int main(void) { 
    int valor_n; 
    float total = 0; 
    pthread_t threads;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    printf("Ingrese el numero maximo: ");
    scanf("%d", &valor_n);
    //imprime valor n
    printf("Valor n: %d\n", valor_n);
    void *exit_value;
    int i;
    for(i = 1; i <= valor_n; i++){
        float j = (float)i;
        pthread_create(&threads, &attr, serie, (void *)&j);
        pthread_join(threads, &exit_value);
        float *resultado = (float *)exit_value;
        total = total + *resultado;
        free(exit_value); 
    }
    printf("El resultado de la serie es: %.5f\n", total);
    pthread_attr_destroy(&attr);
	pthread_exit(NULL);
    return 0;
}