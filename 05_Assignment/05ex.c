/*
Zur Abgabe einen branch `iprg-b05` erstellen und pushen, in dem als einzige Datei die `05ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./05ex_test.o
*/

#include "search_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:

Fügen Sie den Wert `x` als Blatt so in den nicht-leeren Suchbaum `t` ein, dass `t` hinterher
wieder ein Suchbaum ist. Falls `x` bereits in `t` vorkam, soll `t` stattdessen
unverändert bleiben.
Geben Sie zurück, ob der Baum modifiziert wurde.

Nutzen Sie `malloc`, um das neue Blatt zu erstellen. Der Testrunner wird das Blatt wieder `free`n,
darum brauchen Sie sich nicht zu kümmern.
*/


bool search_tree_insert(TreeNode *t, uint16_t x) {
    // search for x in t
    if (t->item == x) return false; // element = x
   
    if (t->item > x) {  // t->item > x , lookup in the left tree
        if (t->left != NULL) { // check if it has left child
            if (search_tree_insert(t->left, x) == true) return true; // recuresively call the function on a left node
            
            } else {
                TreeNode *newNode = (TreeNode*) malloc(sizeof(TreeNode));// allocate memory
                if (newNode == NULL) return NULL;
                newNode->item = x; // assign x to the new Node
                newNode->left = NULL; // initialize empty left branch
                newNode->right = NULL; // initialize empty right branch
                t->left = newNode; // put element as child  (no direct child use case)

                return true;
                }
            
    } else { // x > t->item : lookup in the right tree
        if (t->right != NULL) {
            if (search_tree_insert(t->right, x) == true) return true; // recuresively call the function on a right node 
        } else {
            TreeNode *newNode = (TreeNode*) malloc(sizeof(TreeNode));// allocate memory
            if (newNode == NULL) return NULL;
            newNode->item = x; // assign x to the new Node
            newNode->left = NULL; // initialize empty left branch
            newNode->right = NULL; // initialize empty right branch
            t->right = newNode; // put element as child  (no direct child use case)

            return true;
        }
        }
    return false;
}

/*
Aufgabe 2:
Geben Sie die kleinste Zahl im Suchbaum `t` zurück, welche echt größer als `x` ist.
Falls keine solche Zahl existiert, geben Sie stattdessen `x` zurück. Die Laufzeit Ihrer Lösung soll
proportional zur Höhe des Baumes sein, aber unabhängig von der Gesamtzahl an Knoten. 
*/
uint16_t search_tree_get_greater_than(TreeNode *t, uint16_t x) {

    if (t != NULL) {
        if (t->item <= x) { // t->item < x
        // look up in the right tree branch
        if (t->right != NULL) {
            uint16_t temp = search_tree_get_greater_than(t->right, x);
            if (temp != 0) {
                if (temp > x) return temp;
            };
        } else return x;
        
        } else if (t->item > x)  {
            // look up in the left tree branch
            if (t->left != NULL) {
                uint16_t temp = search_tree_get_greater_than(t->left, x);
                if (temp != 0) {
                    // here i should compare temp with t->left and with x

                    if (temp > x) return temp;
                    else if (t->item > x) return t->item;
                    else return x;
                }
            } else return t->item;
        }
    }
    return x;


}
