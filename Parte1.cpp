#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <iostream>

using namespace std;

int size, half;
int *array=new int[size];

int* createArray(int size){
    int* array = new int[size];
    return array;
}
//struct para pasar argumentos a la subrutina con maximo y cantidad de hilos
struct args{
    int n; 
    int limite_sup;
    int id;
    int resultado;
    int cantidad_hilos;

};



//subrutina paca calcular numeros primos entre un limite inferior y superior
void *calcular_primos(void *arg){
    struct args *arguments = (struct args *)arg;
    int limite_inf = (arguments->id)*(arguments->n);
    int limite_sup = limite_inf + ((arguments->n)-1);
    int suma = 0;
    int i;
    int j;
    int k;
    int contador = 0;
    int numero_primo;  
    cout<<"---Hilo "<<arguments->id<<"---\n"; 
    if(arguments->id == (arguments -> cantidad_hilos)-1){
        limite_sup = limite_sup + 1 + (arguments->limite_sup)%(arguments->n);
        cout<<"Minimo: " << limite_inf<< " Maximo: " << limite_sup << "\n";
        printf("Numeros primos: "); 
        for(i = limite_inf; i <= limite_sup; i++){
            for(j = 1; j <= i; j++){
                if(i % j == 0){
                    contador++;
                }
            }
            if(contador == 2){
                numero_primo = i;
                suma = suma + numero_primo;
                printf("%d ", numero_primo);
            } 
            contador = 0;
        }
    }
    else{
        cout<<"Minimo: " << limite_inf<< " Maximo: " << limite_sup << "\n";
        printf("Numeros primos: "); 
        for(i = limite_inf; i <= limite_sup; i++){
            for(j = 1; j <= i; j++){
                if(i % j == 0){
                    contador++;
                }
            }
            if(contador == 2){
                numero_primo = i;
                suma = suma + numero_primo;
                printf("%d ", numero_primo);
            } 
            contador = 0;
        }
    }
    printf("\n");
    cout<<"Suma: " << suma << "\n";
    arguments->resultado = suma;
    
    pthread_exit(NULL);
}

int main(void) { 
    //pedir numero maximo y guardarlo
    int max;
    int suma; 
    pthread_t threads;
    printf("Ingrese el numero maximo: ");
    cin>>max;
    //pedir numero de hilos y guardarlo
    int num_hilos;
    printf("Ingrese el numero de hilos: ");
    cin>>num_hilos;
    int n;
    n = max / num_hilos;
    args args; 
    args.n=n;
    args.limite_sup=max; 
    args.cantidad_hilos=num_hilos;
    for (int i = 0; i < args.cantidad_hilos; i++)
    {
        args.id = i;
        pthread_create(&threads, NULL, calcular_primos, (void *)&args);
        pthread_join(threads, NULL);
        suma = suma + args.resultado;
    }
    printf("La suma de los numeros primos es: %d\n", suma);
    return 0;
    
}