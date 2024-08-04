/*
Zur Abgabe einen branch `iprg-b08` erstellen und pushen, in dem als einzige Datei die `08ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./08ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Ein Array zusammen mit seiner Länge. */
typedef struct ArrayWithLength_ {
    uint16_t *arr;
    size_t len;
} ArrayWithLength;

/*
Bei merge sort werden häufiger mal *zwei* vorsortierte Arrays kombiniert. Auf diesem Blatt
kombinieren wir effizient *beliebig viele* vorsortierte Arrays mit einem divide-and-conquer Algorithmus.
*/
void merge(ArrayWithLength arr1, ArrayWithLength arr2, ArrayWithLength ret) { // hilfsfunktion for iterative merge sort 

        size_t new_size = arr1.len + arr2.len;
        if (new_size >= 1) {
        ret.arr = (uint16_t *) realloc(ret.arr, sizeof(uint16_t) * new_size); // resize array
        if (ret.arr == NULL) { // check if memory was allocated correctly
            fprintf(stderr, "Fatal: failed to reallocate %zu bytes.\n", sizeof(uint16_t) * new_size);
            abort();
        }
        size_t start1 = 0;
        size_t start2 = 0;
        size_t end1;
        size_t end2;
        if (arr1.len > 0) {
            end1 = arr1.len-1;
        } else end1 = 0;
        if (arr2.len > 0) {
            end2 = arr2.len-1;
        } else end2 = 0;
        
        size_t i = 0;
        // iterate through two arr starting with start up to mid and compare with mid+1 up to end

        if (arr1.len > 0 && arr2.len > 0) {
        while (start1 <= end1 && start2  <=  end2) { // check if there are elements in both parts to compare
            if (arr1.arr[start1] >= arr2.arr[start2]) {
                ret.arr[i] = arr1.arr[start1];
                i++;
                start1++;

            } else {
                ret.arr[i] = arr2.arr[start2];
                i++;
                start2++;
            }
        }
        }
       
        if (arr2.len > 0) {
        while (start2 <= end2){ // cehck if there are elements in the second part left
            ret.arr[i] = arr2.arr[start2];
            i++;
            start2++;
        }
        }
        
        if (arr1.len > 0) {
        while (start1 <= end1) { // check if there are elements in the first part left
            ret.arr[i] = arr1.arr[start1];
            i++;
            start1++;
        }
        }
        }

 
}

/*
Aufgabe 1a:

Gegeben ein absteigend sortiertes Array, geben Sie ein absteigend sortiertes Array
mit den gleichen Elementen zurück.
Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.

Tipp: Ja, es ist wirklich so banal wie es klingt. Das haben base-cases bei divide-and-conquer
Algorithmen häufig so an sich.
*/
ArrayWithLength base_case(ArrayWithLength arr) {
    ArrayWithLength ret;

    ret.arr = (uint16_t *) malloc(sizeof(uint16_t) * 0);
    ret.len = 0;
    ret.len = arr.len;
    if (ret.len > 0) {
    ret.arr = (uint16_t *) realloc(ret.arr, sizeof(uint16_t) * ret.len); // resize the memory block pointed to by ret.arr that was previously allocated with a call to malloc.
    if (ret.arr == NULL) { // check if memory was allocated correctly
        fprintf(stderr, "Fatal: failed to reallocate %zu bytes.\n", sizeof(uint16_t) * ret.len);
        abort();
    }

    // iterate copying all elements from arr to the ret
    for (int i = 0; i < arr.len; i++) {
        ret.arr[i] = arr.arr[i];
    }
        }
    return ret;
}

/*
Aufgabe 1b:

Gegeben zwei absteigend sortierte Arrays der Längen len1 und len2,
geben Sie ein absteigend sortiertes Array zurück,
welches die Elemente beider Eingabearrays enthält. Die Funktion soll in O(len1 + len2) laufen.
Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.
*/
ArrayWithLength combine(ArrayWithLength arr1, ArrayWithLength arr2) {
    ArrayWithLength ret;
    
    ret.arr = (uint16_t *) malloc(sizeof(uint16_t) * 0);
    ret.len = 0;
    if (ret.arr == NULL) { // check if memory was allocated correctly
        fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", sizeof(uint16_t) * ret.len);
        abort();
    }
    // i need to pass 3 arguments , arr1, arr 2 and ret
    ret.len = arr1.len + arr2.len;
    merge(arr1, arr2, ret);

    return ret;
}

/*
Aufgabe 1c:

Gegeben ein nichtleeres Array `arrs` aus `count` vielen absteigend sortierten Arrays, geben Sie ein absteigend sortiertes Array
zurück, welches die Elemente aller Eingabearrays enthält. Ihre Lösung soll in O(n * log(count)) laufen, wobei `n` die
Gesamtzahl an Elementen in allen Arrays ist. Dazu müssen sie clever dive-and-conquern.

Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.
*/
ArrayWithLength merge_k(ArrayWithLength *arrs, size_t count) {
    ArrayWithLength ret;
    ret.arr = NULL; 
    ret.len = 0;
    if (count < 1) return ret; // special case
    else if (count == 1) { // special case
        ret.len = arrs->len;
        ret.arr = (uint16_t *) malloc(sizeof(uint16_t) * ret.len); // resize the memory block pointed to by ret.arr that was previously allocated with a call to malloc.
        if (ret.arr == NULL) { // error handling
            fprintf(stderr, "Fatal: failed to reallocate %zu bytes.\n", sizeof(uint16_t) * ret.len);
            abort();
        }
        // iterate copying all elements from arr to the ret
        for (int i = 0; i < arrs->len; i++) {
            ret.arr[i] = arrs->arr[i];
        }
    } else {


        int a = 0;

        // ArrayWithLength temp_array; // declare a temp array struct
        // merge the arrays iteratevely
        while (a < count) {

            ret = combine(ret, arrs[a]);
            a++;

        }

    }

        return ret;
    }



       