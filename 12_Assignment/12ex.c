/*
Zur Abgabe einen branch `iprg-b12` erstellen und pushen, in dem als einzige Datei die `12ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 12ex_test.c -o 12ex_test.o -lm && ./12ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 12ex_test.c -o 12ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./12ex_test.o
*/

#include "height_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

size_t height_or_zero(HeightTreeNode *t) {
    if (t == NULL) {
        return 0;
    } else {
        return t->height;
    }
}

/*
Aufgabe 1a:

Führen Sie eine Rechtsrotation auf dem gegebenen Baum durch, und geben Sie einen Pointer auf
die Wurzel des neuen Baumes zurück.
Der Baum ist nichtleer, und die Wurzel hat einen nichtleeren linken Teilbaum.

Denken Sie daran, auch die Höhen und die Elternpointer anzupassen.

Die Baumausgabe im Terminal enthält in jedem Knoten erst das Item, dann die Höhe, und zuletzt
das Item des Elternkotens (oder NULL für die Wurzel).

Die Baumausgabe nimmt den zurückgegebenen Knoten als Wurzel. Sollte die Baumausgabe komplett
überraschend aussehen, könnte das gut an einer falsch zurückgegebenen Wurzel liegen.
*/

int child_height(HeightTreeNode *t) {
    int max = 0;
    // check left child 
    if (t->left != NULL) {
        max = t->left->height;
        } 
    // check right child
    if (t->right != NULL) {
        max = (max < t->right->height) ? t->right->height : max;

    }

    return max;


}

HeightTreeNode *rotate_right(HeightTreeNode *t) {
    if (t == NULL && t->left == NULL) return NULL; // safety check
    // check for almost AVL?


    // swap parent with the left child
    HeightTreeNode *new_parent = t->left; // store the child// = (HeightTreeNode*)malloc(sizeof(HeightTreeNode)); // temp pointer
    
    // if (new_parent->right != NULL) {
    HeightTreeNode *child = new_parent->right; // store the child
    t->left = child;
    if (child != NULL) {
        child->parent = t;
    } 

    t->parent = new_parent; 

    new_parent->right = t;

    new_parent->parent = NULL;
    
    new_parent->right->height = child_height(new_parent->right) + 1;
    new_parent->height = child_height(new_parent) + 1;

    return new_parent;
}

/*
Die vier möglichen Sequenzen von Rotationen, um einen Beinahe-AVL-Baum in einen AVL-Baum zu überführen.
*/
typedef enum Rotations_ {
    Left, /* eine Linksrotation */
    Right, /* eine Rechtsrotation */
    DoubleRotationLeftRight, /* Doppelrotation: erst Linksrotation, dann Rechtsrotation */
    DoubleRotationRightLeft, /* Doppelrotation: erst Rechtsrotation, dann Linksrotation */
} Rotations;

/*
Aufgabe 2:

Gegeben ein Beinahe-AVL-Baum mit korrekten Höhenwerten, geben Sie zurück, welche Rotationen ihn zu einem AVL-Baum machen.
*/
int determine_height(HeightTreeNode *t) {
    if (t == NULL) return 0;
    return t->height;
}



Rotations determine_rotations(HeightTreeNode *t) {


    if (determine_height(t->left) - determine_height(t->right) > 1) {
        if (determine_height(t->left->left) >= determine_height(t->left->right)) 
        {
            return Right;
        } else return DoubleRotationLeftRight;
    } else if (determine_height(t->right) - determine_height(t->left) > 1) {
        if (determine_height(t->right->right) >= determine_height(t->right->left)) 
        {
            return Left;
        } else return DoubleRotationRightLeft;
    }



    return 0;
}