/***********************************************
*
*	Autor: Santiago Bautista Velásquez
*	Programa: lab2.c
*	Fecha: 5 de Noviembre
*	Temas: Programación Paralela - OpenMP (variables private y shared)
*
*--------------------------------------------------
*==================================================
*Resumen:
*Este programa ilustra el comportamiento de las variables
*privadas y compartidas en OpenMP al ejecutar un bucle for
*de manera paralela. Se observa cómo los valores de las
*variables pueden o no cambiar dependiendo de su ámbito
*(private o shared) dentro del bloque paralelo.
*
*************************************************/

#include <omp.h>     // Biblioteca de OpenMP (control de hilos y funciones de entorno)
#include <stdio.h>   // Biblioteca estándar para funciones de entrada/salida
#include <stdlib.h>  // Biblioteca estándar (no utilizada directamente en este ejemplo)


int main(){

	int i;              // Variable iteradora del bucle
	const int N = 1000; // Número total de iteraciones del bucle
	int a = 50;         // Variable base con valor inicial constante
	int b = 0;          // Variable acumuladora que será modificada dentro del bucle

	//=========================================================
	// Directiva OpenMP: parallel for
	//---------------------------------------------------------
	// La directiva "#pragma omp parallel for" divide el bucle for
	// entre varios hilos (threads), de forma que cada hilo ejecuta
	// un subconjunto de las iteraciones.
	//
	// Cláusulas utilizadas:
	//   - private(i): cada hilo tiene su propia copia de 'i'.
	//   - private(a): cada hilo tiene su propia copia local de 'a'
	//                 inicializada sin valor definido (no se copia
	//                 el valor 50 automáticamente).
	//
	//   Por omisión, las variables no mencionadas en private o shared
	//   (como 'b') son compartidas entre todos los hilos.
	//=========================================================
	#pragma omp parallel for private(i) private(a)
	for(int i = 0; i < N; i++)
	{
		// Cada hilo ejecuta su conjunto de iteraciones en paralelo.
		// Dado que 'a' es privada, su valor dentro del hilo es indeterminado
		// (no hereda el valor 50 del exterior).
		// Sin embargo, 'b' es compartida, por lo que varios hilos
		// pueden modificarla simultáneamente → condición de carrera.
		b = a + i;
	}

	//=========================================================
	// Impresión de resultados
	//---------------------------------------------------------
	// Debido a que 'a' es privada, su valor global fuera del bucle
	// no cambia (sigue siendo 50).
	// En cambio, 'b' es compartida, por lo que su valor final depende
	// del último hilo que haya escrito sobre ella.
	//
	// Sin embargo, debido a la condición de carrera, el valor real
	// de 'b' puede variar entre ejecuciones.
	//=========================================================
	printf("a = %d b = %d (se espera a = 50 b = 1049)\n", a, b);

	return 0; // Fin normal del programa
}

