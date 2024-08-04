/*
Zur Abgabe einen branch `iprg-b11` erstellen und pushen, in dem als einzige Datei die `11ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 11ex_test.c -o 11ex_test.o -lm && ./11ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 11ex_test.c -o 11ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./11ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:
Implementieren Sie folgenden Algorithmus, um ein Array zu partitionieren:

- die `pivot_position` ist initial die letzte Stelle im Array
- der Wert an der `pivot_position` ist das `pivot` Element
- solange es links der `pivot_position` Elemente gibt, die größer oder gleich `pivot` sind:
    - sei `i` die Position des linkesten solchen Elements
    - rotiere die Werte an den Positionen `i`, `pivot_position - 1` und `pivot_position` nach links (siehe Testoutput)
    - dekrementiere die `pivot_position`

Nutzen Sie die `visualizer_append_array` Funktion (siehe `array_visualizer.h` bzw das sechste Semesteraufgabenblatt 06) um den Algorithmus zu visualisieren. Und nutzen Sie die vom Testrunner erstellten Bilder zum Debuggen, und falls Ihnen das zu erwartende Verhalten unklar ist.

Imaginäre Bonuspunkte, wenn Ihre Implementierung in linearzeit läuft.

Tipp: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void visualize_partition(Visualizer *v, uint8_t *arr, size_t len) {

    visualizer_append_array(v, arr);
    
    if (len < 2) return; // edge case: array i smaller than 2 elements
    else {

    // partition
    size_t pivot_index = len-1; // define pivote position element as the last one
    size_t leftmost = 0;
    uint8_t temp_pivot; // declaration of a temp variable to hold pivot value
    // loop for partitioning
    while (pivot_index > 0 && leftmost < pivot_index) {  // check if there is an element on the left
        if (arr[leftmost] > arr[pivot_index]) { // check if the leftmost non-partitioned element is larger than pivot
            if (leftmost == pivot_index-1) { // closest neighbour -> half rotation
                temp_pivot = arr[pivot_index];
                arr[pivot_index] = arr[leftmost];
                arr[leftmost] = temp_pivot;
            } else { //full ring rotation
                temp_pivot = arr[pivot_index];
                arr[pivot_index] = arr[leftmost];
                arr[leftmost] = arr[pivot_index-1];
                arr[pivot_index-1] = temp_pivot;
            }
            pivot_index--;
            visualizer_append_array(v, arr); // visualize after one rotation increment is done 
        } else if (arr[leftmost] == arr[pivot_index]) {
            leftmost++;
            visualizer_append_array(v, arr); // visualize after one rotation increment is done 
        } else { // increment leftmost
            leftmost++;
        }
    }
    }
    return;
}

/*
Aufgabe 2:
Implementieren Sie Quicksort rekursiv, und visualisieren Sie den Algorithmus wie von den Tests verlangt.

Wählen Sie als Pivotelement stets das letzte Element eines Teilarrays, und partitionieren Sie mit dem in Aufgabe 1 beschriebenen Algorithmus.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
Tipp 2: Visualisieren Sie außerdem das Array immer nachdem Sie ein Teilarray der Größe mindestens zwei partitioniert haben.
Tipp 3: Diese Funktion selbst lässt sich nicht sinnvoll rekursiv aufrufen. Schreiben Sie eine geeignete Funktion, und rufen Sie sie in `sort_quickly` auf.
*/
size_t partition(uint8_t *arr, size_t start_index, size_t len) {
    size_t pivot_index = start_index + len-1; // define pivot position element as the last one
    if (len < 2) return 0; // exit condition: array is smaller than 2 elements
    else {

    // partition

    size_t leftmost = start_index;
    uint8_t temp_pivot; // declaration of a temp variable to hold pivot value
    // loop for partitioning
    while (pivot_index > 0 && leftmost < pivot_index) {  // check if there is an element on the left
        if (arr[leftmost] > arr[pivot_index]) { // check if the leftmost non-partitioned element is larger than pivot
            if (leftmost == pivot_index-1) { // closest neighbour -> half rotation
                temp_pivot = arr[pivot_index];
                arr[pivot_index] = arr[leftmost];
                arr[leftmost] = temp_pivot;
            } else { //full ring rotation
                temp_pivot = arr[pivot_index];
                arr[pivot_index] = arr[leftmost];
                arr[leftmost] = arr[pivot_index-1];
                arr[pivot_index-1] = temp_pivot;
            }
            pivot_index--;

        } else if (arr[leftmost] == arr[pivot_index]) {
            leftmost++;

        } else { // increment leftmost
            leftmost++;
        }
    }
    }
    return pivot_index;
}

void _sort_quickly(Visualizer *v, uint8_t *arr, size_t start_index, size_t len) {
    if (len < 2) return; // exit condition (if the array is smaller than 2)

    size_t pivot_index; // define pivote position element as the last one

    pivot_index = partition(arr, start_index, len);
    visualizer_append_array(v, arr);

    size_t left_len = (pivot_index > 0) ? (pivot_index - start_index) : 0; // calculating the left part length
    size_t right_len = (pivot_index + 1 < start_index + len) ? (start_index + len - pivot_index - 1) : 0; // calculating the right part length

    if (left_len > 0) _sort_quickly(v, arr, start_index, left_len); // recursively calling for left part

    if (right_len > 0) _sort_quickly(v, arr, pivot_index + 1, right_len); // recursively calling for right part



}

void sort_quickly(Visualizer *v, uint8_t *arr, size_t len) {
    visualizer_append_array(v, arr);
    size_t start = 0;
    _sort_quickly(v, arr, start, len);
    return;
}
