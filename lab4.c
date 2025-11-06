/*
 * Pontificia Universidad Javeriana
 *
 * Autor: Santiago Bautista Velasquez
 * Fecha: 05/11/25
 * Tema: OpenMP
 *
 * Descripción:
 *   - Cálculo de la sumatoria de la función SENO en paralelo con OpenMP.
 *   - Se fija el número de hilos desde la línea de comandos.
 *   - Se mide el tiempo total de ejecución con gettimeofday().
 *
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define MIN(x,y) (((x) < (y)) ? (x) : (y))

/* ---- Cronometraje con gettimeofday (μs) ---- */
static struct timeval inicio, fin;

static inline void InicioMuestra(void) {
    gettimeofday(&inicio, NULL);
}

static inline double FinMuestra(void) {
    gettimeofday(&fin, NULL);
    long sec  = fin.tv_sec  - inicio.tv_sec;
    long usec = fin.tv_usec - inicio.tv_usec;
    long total_us = sec * 1000000L + usec;
    return (double) total_us;  /* microsegundos */
}

/* ---- Función objetivo: suma de senos en un rango dependiente de i ----
   Nota: Mantengo tu definición original:
         inicio = i*(i+4)/2
         final  = inicio + i
         Se acumula sin(j) para j = [inicio, final)
*/
double funcion(int i) {
    long long inicio = (long long)i * (i + 4) / 2;
    long long final  = inicio + i;
    double valor = 0.0;
    for (long long j = inicio; j < final; ++j) {
        valor += sin((double)j);
    }
    return valor;
}

int main(int argc, char *argv[]) {
    /* ---------- Validación de argumentos ---------- */
    if (argc != 2) {
        fprintf(stderr, "Uso:\n\t%s <num_hilos>\n", argv[0]);
        return 1;
    }

    int numHilos = atoi(argv[1]);
    if (numHilos < 1) {
        fprintf(stderr, "Error: <num_hilos> debe ser >= 1\n");
        return 1;
    }

    /* ---------- Parámetros del cálculo ---------- */
    const int N = 30000;     /* cantidad de iteraciones */
    double sumatoria = 0.0;  /* acumulador global (double) */

    /* ---------- Info de entorno ---------- */
    printf("Solicitados %d hilos | Máx. disponibles: %d\n",
           numHilos, omp_get_max_threads());

    /* Fijar número de hilos */
    omp_set_num_threads(numHilos);

    /* ---------- Cálculo paralelo + medición ---------- */
    InicioMuestra();

    #pragma omp parallel
    {
        /* Solo el hilo maestro informa hilos efectivos */
        #pragma omp master
        {
            printf("Hilos efectivos OpenMP: %d\n", omp_get_num_threads());
        }

        /* Bucle paralelo con reducción para evitar data races */
        #pragma omp for reduction(+:sumatoria) schedule(static)
        for (int i = 0; i < N; ++i) {
            /* Uso ilustrativo de MIN, no afecta la lógica original */
            int idx = MIN(i, N);
            sumatoria += funcion(idx);
        }
    }

    double tiempo_us = FinMuestra();

    /* ---------- Resultados ---------- */
    printf("Sumatoria SENO = %.12f\n", sumatoria);
    printf("Tiempo total: %.0f microsegundos (%.6f s)\n",
           tiempo_us, tiempo_us / 1e6);

    return 0;
}
