/*
Zur Abgabe einen branch `iprg-b06` erstellen und pushen, in dem als einzige Datei die `06ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && ./06ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./06ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:
Machen Sie sich in dieser Aufgabe mit dem `Visualizer` (siehe array_visualizer.h) vertraut.
Nutzen Sie die `visualizer_append_array` Funktion damit die Tests durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void warmup(Visualizer *v, uint8_t *arr, size_t len) {

    uint8_t temp;     // temp helper variable

    for (int i = 0; i < len; i++) {     // loop 'len' times

    visualizer_append_array(v, arr); // visualize

    // shift the numbers in array to the left

        // take the first number into the temp
        temp = arr[0];
        // shift the second to the first 'len-1' times
        for (int a = 0; a < len-1; a++ ) {
            arr[a] = arr[a+1];
        }
        arr[len-1] = temp; // put the number from the temp back

    }
}

/*
Aufgabe 2:
Bringen Sie die Tests zum durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
Tipp 2: Es handelt sich um eine Abwandlung von iterativem Mergesort.
Tipp 3: `len` ist immer eine Dreierpotenz, damit Sie sich nicht mit Rundungsdetails herumschlagen brauchen.
*/

void merge(uint8_t *arr, size_t start, size_t mid, size_t end) { // hilfsfunktion for iterative merge sort (array, p, m, len) [1, 2, 3, 4, 5, 6, 7, 8]
        size_t n1 = mid - start + 1;  // Number of elements in the first sub-array
        size_t n2 = end - mid;  // Number of elements in the second sub-array
        uint8_t *temp_arr = (uint8_t*) malloc(n1 + n2); // allocate memory for a temp_arr, sizeof arr len.
        if (temp_arr == NULL) { // check if memory was allocated correctly
            fprintf(stderr, "Fatal: failed to allocate %s bytes.\n", temp_arr);
            abort();
        }
        size_t origin_start = start;
        size_t origin_mid = mid;

        size_t i = 0;
        // iterate through two arr starting with start up to mid and compare with mid+1 up to end

        while (start < origin_mid + 1 && mid  <  end) { // check if there are elements in both parts to compare
            if (arr[start] <= arr[mid+1]) {
                temp_arr[i] = arr[start];
                i++;
                start++;
            } else {
                temp_arr[i] = arr[mid+1];
                i++;
                mid++;
            }
        } 
        while (start < origin_mid + 1) { // check if there are elements in the first part left
            temp_arr[i] = arr[start];
            i++;
            start++;
        }

        while (mid < end + 1){ // cehck if there are elements in the second part left
            temp_arr[i] = arr[mid+1];
            i++;
            mid++;
        }
        
        // rewrite sorted values from the temp_arr into the origin array arr
        size_t y = 0;
        for (i = origin_start; i < end+1; i++) {
            arr[i] = temp_arr[y];
            y++;
        }

        free(temp_arr); // memory deallocation
}


size_t minimum(size_t first, size_t second) {
    if (first < second) return first;
    else return second;
}

void sort_it(Visualizer *v, uint8_t *arr, size_t len) {
    if (len <= 1) { // check on array <= 1
        visualizer_append_array(v, arr);
    } else {
    visualizer_append_array(v, arr);


    for (size_t group_size = 1; group_size < len; group_size *= 3 ) {
        for (size_t start = 0; start < len; start += 3*group_size) {

            size_t mid1 = minimum(start + group_size, len); // calculate first mid
            size_t mid2 = minimum(start + group_size*2, len); // calculate second mid
            size_t end = minimum(start + group_size*3, len); // calculate end

            // merge two-step process
            merge(arr, start, mid1-1, mid2-1); // merge first and second part (start till mid 1 , and mid 1 till mid 2)
            merge(arr, start, mid2-1, end-1); // merge merged parts with the third part (start till mid 2, and mid2 till end)
            visualizer_append_array(v, arr);
        }

    }




    }





}


