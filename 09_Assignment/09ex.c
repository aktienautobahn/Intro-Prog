/*
Zur Abgabe einen branch `iprg-b09` erstellen und pushen, in dem als einzige Datei die `09ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && ./09ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./09ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tree.h"
#include "array.h"

/*
Aufgabe 1:

Gegeben ein Array `arr`, geben Sie zurück, ob der zugehörige linksvollständige Binärbaum
die max-heap Eigenschaft erfüllt.
*/
// helper function for recursive calls
bool is_max_heap_helper(Array arr, int i) {

    // left child index
    int left = i * 2 + 1;
    // right child index
    int right = i * 2 + 2;

    // check if there are children?
        if (left < arr.len && arr.arr[left] > arr.arr[i]) { // left heap
            return false; // max heap property is violated

        }

        if (right < arr.len && arr.arr[right] > arr.arr[i]) { // right heap
            return false; // max heap property is violated

        }
    // recursive call for left heap
    if (left < arr.len) {
        if (!is_max_heap_helper(arr, left)) return false; // propagate false upwards
    }
    if (right < arr.len) {
        if (!is_max_heap_helper(arr, right)) return false; // propagate false upwards
    }

    // if no violations found , return true.
    return true;
}

bool is_max_heap(Array arr) {
    int i = 0;
    if (arr.len < 2) return true; // condition satisfied, if the heap is smaller than 2
    if (arr.len > 1 && is_max_heap_helper(arr, i)) return true; // call the helper 
    return false;
}

/*
Aufgabe 2:

Gegeben ein linksvollständiger Binärbaum, tragen Sie im Array `arr` dessen Arrayrepräsentation ein.

Tipp 1: Wie so häufig bei Bäumen, bietet sich hier eine rekursive Lösung an.
Tipp 2: Diese Funktion selbst ist allerdings nur so mäßig gut für rekursive Aufrufe geeignet, eventuell sollten Sie sich eine (rekursive) Hilfsfunktion schreiben.
Tipp 3: Die Position eines Knotens im Array lässt sich relativ leicht bestimmen, wenn man die Position vom Elternknoten weiß, und, ob es sich um ein linkes oder ein rechtes Kind handelt.
Tipp 4: Ja, das sind also sinnvolle Argumente für die Hilfsfunktion.
Tipp 5: Regelmäßig zähneputzen und genug bewegen.
*/
void tree_to_array_helper(TreeNode *t, Array arr, int i) { // recursive helper function for array populating 
    // left heap
    int left = 2 * i + 1;
    // right heap
    int right = 2 * i + 2;

    // store item in array
    arr.arr[i] = t->item;

    // if there is left child 
    if (t->left != NULL && left < arr.len) {
        // recursively call for the left heap
        tree_to_array_helper(t->left, arr, left); 
    }
    // if there is right child 
    if (t->right != NULL && right < arr.len) {
        // recursively call for the right heap
        tree_to_array_helper(t->right, arr, right); 
    }

}

void tree_to_array(TreeNode *t, Array arr) {
    if (is_max_heap(arr)) {
        if (arr.len > 0) { // if the array is bigger than 0
            if (arr.len == 1) { // edge case , array = 1
                arr.arr[0] = t->item;
            } else {
                int i = 0;
                tree_to_array_helper(t, arr, i);
            }
        }
    }

}
