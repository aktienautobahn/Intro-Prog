#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "introprog_sortierte_buecherliste.h"
#include "introprog_structs_lists_input.h"

/* HIER struct _element implementieren. */
typedef struct _element element;
struct _element {
    char title[256];
    char author[256];
    uint32_t year;
    uint64_t isbn;
    element* next;
};

/* Fuege ein Element in die Liste ein, sodass die Liste aufsteigend
 * nach ISBN sortiert ist.  Dafür muss das erste Element ermittelt
 * werden, das in der bisher sortierten Liste eine ISBN besitzt,
 * die größer ist als die des neuen Elements.  Wenn die Liste leer
 * ist, soll das Element direkt an den Anfang platziert werden.
 *
 * first    - Pointer auf das erste Element (bzw. Anfang) der Liste
 * new_elem - Pointer auf das neues Element das in die Liste
 * eingefuegt werden soll
 *
 * Gib einen Pointer auf den neuen oder alten Anfang der Liste
 * zurueck.
 */
element* insert_sorted(element* first, element* new_elem) {
    // if first element , then put in the beginning
    if (first == NULL) {
    // return pointer to the first (either new or old)
        return new_elem;
    }

    // loop through the list
    element* current = first;
    element* previous = first;
    while(current != NULL) {
    // and check if the ISBN greater than the ISBN of new_elem. 
        if (current->isbn > new_elem->isbn) {
            //swap current with new (insering it before)
            if (current != previous) {
                new_elem->next = current; // linking new to next
                // link previous to new_elem
                previous->next = new_elem; // linking previous to new
                // return first
             
            } else {
                new_elem->next = current; // linking new to next
                return new_elem;
            }

            return first;
        } else if (current->next == NULL) {
            current->next = new_elem; //put at the end of the list
            return first;
        } else {
            // next step 
            previous = current; // current -> previous
            current = current->next; // next -> current
        }
    }
    return first;
    // return pointer to the beginning of the linked list
}

/* Lese die Datei ein und fuege neue Elemente in die Liste ein 
 * _Soll nicht angepasst werden_
 */
void read_list_sorted(char* filename, list *alist) {
    element* new_elem;
    char* new_title;
    char* new_author;
    uint32_t new_year;
    uint64_t new_isbn;
    read_line_context ctx;
    open_file(&ctx, filename);
    while(read_line(&ctx, &new_title, &new_author, &new_year, &new_isbn) == 0) {
        new_elem = construct_element(new_title, new_author, new_year, new_isbn);
        alist->first = insert_sorted(alist->first, new_elem);
        alist->count++;
    }
}