#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "introprog_buecherliste.h"
#include "introprog_structs_lists_input.h"

/* Fuege ein Element am Anfang der Liste an, sodass das neue
 * Element immer das erste Element der Liste ist.  Wenn die Liste
 * leer ist, soll das Element direkt an den Anfang platziert
 * werden.
 *
 * first    - Pointer auf das erste Element (bzw. Anfang) der
 * Liste
 * new_elem - Pointer auf das neues Element das in die Liste
 * eingefuegt werden soll
 *
 * Gib einen Pointer auf den neuen Anfang der Liste zurueck.
 */
element* insert_at_begin(element* first, element* new_element) {
    if (new_element == NULL) {
        return NULL;
    }

    new_element->next = first;
    return new_element;

}

/* Kreiere ein neues Element mit dynamischem Speicher.
 *
 * title  - Titel des Buches
 * author - Autor des Buches
 * year   - Erscheinungsjahr des Buches
 * isbn   - ISBN des Buches
 *
 * Gib einen Pointer auf das neue Element zurueck.
 */
element *construct_element(char* title, char* author, uint32_t year, uint64_t isbn) {
    // allocate memory for the element
    element *newElement = (element*)malloc(sizeof(element));
    if (newElement == NULL) {
        return NULL;
    }

    //create author and copy the author
    newElement->author = malloc(strlen(author)+1);
    // allocation error handling
    if (newElement->author == NULL) {
        free(newElement); // free allocated memory for newElement
        return NULL;
    }
    strcopy(newElement->author, author);

    //create title and copy the title
    newElement->title = malloc(strlen(title)+1);
    // allocation error handling
    if (newElement->title == NULL) {
        free(newElement->author);
        free(newElement);
        return NULL;
    }
    strcopy(newElement->title, title);

    // just copy integers
    newElement->year = year;
    newElement->isbn = isbn;

    return newElement;
}

/* Gib den der Liste und all ihrer Elemente zugewiesenen
 * Speicher frei.
 */
void free_list(list* /* Variable benennen */) {
    /* HIER implementieren. */
}

/* Lese die Datei ein und fuege neue Elemente in die Liste ein 
 * _Soll nicht angepasst werden_
 */
void read_list(char* filename, list* alist) {
    element* new_elem;

    char* new_title;
    char* new_author;
    uint32_t new_year;
    uint64_t new_isbn;
    read_line_context ctx;
    open_file(&ctx, filename);
    while(read_line(&ctx, &new_title, &new_author, &new_year, &new_isbn) == 0) {
        new_elem = construct_element(new_title, new_author, new_year, new_isbn);
        alist->first = insert_at_begin(alist->first, new_elem);
        alist->count++;
    }
}

/* Erstelle die Liste:
 *  - Weise ihr dynamischen Speicher zu 
 *  - Initialisiere die enthaltenen Variablen
 * _Soll nicht angepasst werden_
 */
list* construct_list() {
    list *alist = malloc(sizeof(list));
    alist->first = NULL;
    alist->count = 0;
    return alist;
}