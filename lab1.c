/***********************************************
*
*	Autor: Santiago Bautista Velasquez
*	Programa: lab1.c
*	Fecha: 05/11/25
*	Temas: Programación Paralela - Introducción a OpenMP
*
*--------------------------------------------------
*==================================================
*Resumen:
*El programa demuestra el uso básico de la librería OpenMP
*para crear hilos (threads) paralelos en un sistema
*multiprocesador. Cada hilo imprime un mensaje indicando
*su número identificador dentro del grupo de ejecución.
*
*************************************************/

#include <omp.h>     // Biblioteca principal de OpenMP, necesaria para manejar directivas de paralelismo
#include <stdio.h>   // Biblioteca estándar de entrada/salida (para printf)
#include <stdlib.h>  // Biblioteca estándar (en este caso, no usada, pero útil para futuras ampliaciones)

int main (int argc, char *argv[]){
    // Mensaje inicial que indica el número máximo de hilos disponibles.
    // La función omp_get_max_threads() devuelve cuántos hilos puede usar
    // el programa de forma predeterminada, basado en los núcleos del procesador.
    printf("OpenMP ejecutando con %d hilos\n", omp_get_max_threads());

    // Directiva de compilación de OpenMP que indica que el siguiente bloque
    // de código debe ejecutarse en paralelo. 
    // Cada hilo creado ejecutará el mismo código dentro del bloque.
    #pragma omp parallel 
    {
        // Dentro del bloque paralelo, cada hilo obtiene su identificador único
        // con omp_get_thread_num(), que va desde 0 hasta N-1, donde N es el número de hilos.
        // Cada hilo imprime un mensaje independiente.
        printf("Hello world desde el thread %d\n", omp_get_thread_num());
    }

    // Retorno estándar del programa indicando que todo se ejecutó correctamente.
    return 0;
}

