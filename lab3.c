/***********************************************
*
*	Autor: Santiago Bautista Velásquez
*	Programa: lab4.c
*	Fecha: 5 de Noviembre
*	Temas: Programación Paralela - OpenMP (Uso de variables private)
*
*--------------------------------------------------
*==================================================
*Resumen:
*Este programa demuestra el uso de la directiva
*`#pragma omp parallel for` de OpenMP para ejecutar un bucle
*en paralelo y analizar el efecto de declarar las variables
*como privadas (`private`). Se observa cómo esta configuración
*influye en los resultados finales de las variables fuera del
*bloque paralelo.
*
*************************************************/

#include <omp.h>     // Biblioteca principal de OpenMP: permite la creación y gestión de hilos
#include <stdio.h>   // Biblioteca estándar para entrada/salida (printf)
#include <stdlib.h>  // Biblioteca estándar (en este ejemplo no se utiliza directamente)

int main(){

	int i;
	const int N = 1000;
	int a = 50
	int b = 0;         o

	//=========================================================
	// Directiva OpenMP: parallel for
	//---------------------------------------------------------
	// La siguiente directiva indica que el bucle "for" se ejecutará
	// de manera paralela, distribuyendo sus iteraciones entre los
	// hilos disponibles del procesador.
	//
	//   - private(i): cada hilo tiene su propia copia de 'i'.
	//   - private(a): cada hilo tiene su propia copia de 'a', sin heredar
	//                 el valor 50 del ámbito exterior.
	//   - private(b): cada hilo tiene su propia copia de 'b', independiente
	//                 del resto y de la variable global 'b'.
	//
	// Esto significa que las variables 'a' y 'b' dentro del bloque
	// paralelo NO son las mismas que las declaradas fuera de él.
	// Cada hilo modifica sus propias copias, y al finalizar el bucle
	// estas copias privadas se destruyen, sin alterar los valores
	// globales originales.
	//=========================================================
	#pragma omp parallel for private(i) private(a) private(b)
	for(int i = 0; i < N; i++)
	{
		// Cada hilo ejecuta un subconjunto de iteraciones de manera concurrente.
		// Dentro del hilo, 'a' y 'b' son variables locales (privadas).
		// Por tanto, cada hilo calcula un valor de b = a + i,
		// pero estos valores no afectan la variable 'b' global.
		b = a + i;
	}

	//=========================================================
	// Impresión de resultados
	//---------------------------------------------------------
	// Fuera del bloque paralelo, las variables 'a' y 'b' conservan
	// los valores originales del ámbito principal:
	//     a = 50
	//     b = 0
	//
	// Esto sucede porque, al ser privadas, las copias locales
	// de 'a' y 'b' desaparecen al salir del bloque paralelo.
	//
	//=========================================================
	printf("a = %d b = %d (se espera a = 50 b = 1049)\n", a, b);

	return 0; // Fin normal del programa
}

