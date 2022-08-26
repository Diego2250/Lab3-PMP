#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

using namespace std;

int size, half;
int *array=new int[size];

int* createArray(int size){
    int* array = new int[size];
    return array;
}
//struct para pasar argumentos a la subrutina con maximo y cantidad de hilos
struct args{
    int limite_inf;
    int limite_sup;
};



//subrutina paca calcular numeros primos entre un limite inferior y superior
void *calcular_primos(void *arg){
    struct args *arguments = (struct args *)arg;
    int limite_inf = arguments->limite_inf;
    int limite_sup = arguments->limite_sup;
    int i;
    int j;
    int k;
    int contador = 0;
    int numero_primo;
    for(i = limite_inf; i <= limite_sup; i++){
        for(j = 1; j <= i; j++){
            if(i % j == 0){
                contador++;
            }
        }
        if(contador == 2){
            numero_primo = i;
            printf("%d\n", numero_primo);
        } 
        contador = 0;
    }
    pthread_exit(NULL);
}

int main(void) { 
    //pedir numero maximo y guardarlo
    int max;
    printf("Ingrese el numero maximo: ");
    scanf("%d", &max);
    //pedir numero de hilos y guardarlo
    int num_hilos;
    printf("Ingrese el numero de hilos: ");
    scanf("%d", &num_hilos);
    int n;
    n = max / num_hilos;

}