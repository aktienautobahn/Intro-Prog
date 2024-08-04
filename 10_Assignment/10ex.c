/*
Zur Abgabe einen branch `iprg-b10` erstellen und pushen, in dem als einzige Datei die `10ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 10ex_test.c -o 10ex_test.o -lm && ./10ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 10ex_test.c -o 10ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./10ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tree.h"
#include "array.h"

/*
Aufgabe 1:

Implementieren Sie min-heapify auf Bäumen: gegeben ein nichtleerer, linksvollständiger Baum `t`, dessen
Kinder der Wurzel die min-heap Eigenschaft erfüllen, lassen Sie den Wert in der Wurzel so lange
"hinuntersinken", bis `t` die min-heap Eigenschaft erfüllt.

Da "hinuntersinken" nicht gerade präzise formuliert ist, müssen Sie unter Umständen Ihre Implementierung
an die Testfälle anpassen. Aber wenn Sie der Intuition der Vorlesungsfolien folgen, sollte das keine Probleme bereiten.

Werte kommen in `t` niemals mehrfach vor.
*/
void heapify_tree(TreeNode *t) {
    if (t == NULL) return; // If the node is null, do nothing

    TreeNode *smallest = t;

    // left heap
    if (t->left != NULL && t->left->item < smallest->item) { // check if there is left node and 
        smallest = t->left;
    }
    // right heap
    if (t->right != NULL && t->right->item < smallest->item) {
        smallest = t->right;
    } 
    // if the smallest node is not the current node, swap and continue to heapify
    if (smallest != t) {
        // swap values
        uint16_t temp = smallest->item;
        smallest->item = t->item;
        t->item = temp;
        // recursively repeat
        heapify_tree(smallest);
    }
    
}

/*
Aufgabe 2:

Implementieren Sie min-heapify auf Arrays: gegeben ein nichtleeres Array und eine Position `i` innerhalb des Arrays,
sodass die Kinder vom Knoten der zum Element an Position `i` gehört min-heaps sind, lassen Sie den Wert an Position `i`
solange hinuntersinken, wie nötig, um die min-heap Eigenschaft für den Teilbaum ab Position `i` wiederherzustellen.

Oder knapper: Implementieren Sie den heapify Algorithmus aus der Vorlesung, aber für min-heaps.

Werte kommen im Array niemals mehrfach vor.
*/
void heapify_array(Array arr, size_t i) {
    // normal case i > 1, else do nothing
    if (arr.len > 1) {

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int smallest;

    // left heap
    if (left <= arr.len && arr.arr[left] < arr.arr[i]) {
        smallest = left;
    } else {
        smallest = i;
    }
    // right heap
    if (right <= arr.len && arr.arr[right] < arr.arr[smallest]) {
        smallest = right;
    } 

    if (smallest != i) {
        // swap values
        uint16_t temp = arr.arr[i];
        arr.arr[i] = arr.arr[smallest];
        arr.arr[smallest] = temp;
        // recursively repeat
        heapify_array(arr, smallest);
    }
    }
}
