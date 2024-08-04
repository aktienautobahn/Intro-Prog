#include <stdlib.h>
#include <string.h>
#include <math.h>  // definiert den speziellen Wert NaN für floats
#include "introprog_stacks-rpn.h"
#include "introprog_input_stacks-rpn.h"

/* 
 * Füge Element am Anfang des Stacks ein
 *
 * char* - Ein Pointer auf den Stack.
 * float - Zahl, die als neues Element auf den Stack gelegt
 *         werden soll.
 */
void stack_push(stack* root, float number)
{
    // check if stack root is empty
    if (root->top == NULL) {
        stack_element* newStackElement = (stack_element*) malloc(sizeof(stack_element));
        if (newStackElement != NULL) {
            newStackElement->value = number;
            newStackElement->next = NULL;
            root->top = newStackElement;
        }
    } else {
        // add element on top
        // allocate memory for the new element.
        stack_element* newStackElement = (stack_element*) malloc(sizeof(stack_element));
        if (newStackElement != NULL) {
        newStackElement->value = number;            // assign number to new stack element
        newStackElement->next = root->top;         // push top element down by assigning the address of top element
        
        root->top = newStackElement;   // make new element to the root element
        }           
        // free(temp);

    }

}

/* 
 * Nehme das letzte eingefügte Element vom Anfang des Stacks
 * Gebe NaN zurück, wenn keine Element vorhanden ist.
 *
 * stack* - Ein Pointer auf den Stack
 *
 * Gebe die im Element enthaltenen Zahl zurück
 */
float stack_pop(stack* root)
{
    if (root->top == NULL) { // no elements in stack?
        return NAN;
    }

    float poppedValue = root->top->value;     // extract the value from the top element 

    stack_element* temp = root->top;     // safe the popped element in the temp
    root->top = root->top->next; // assign the next to the new top
    free(temp); // free the popped element
    

    return poppedValue;

}

/*
 * Führt abhängig von dem Token eine entsprechende Operation auf
 * dem Stack aus.  Wenn es sich bei dem Token um
 *  -> eine Zahl handelt, dann konvertiere die Zahl mithilfe von
 *     atof() zu einem float und lege sie auf den Stack.
 *  -> einen Operator handelt, dann nehme zwei Zahlen vom Stack,
 *     führe die Operation aus und lege das Resultat auf den Stack.
 *  -> eine nichterkennbare Zeichenkette handelt, dann tue nichts.
 *
 * stack*  - Ein Pointer auf den Stack
 * char*  - Eine Zeichenkette
 */
void process(stack* root, char* token)
{ if (root != NULL && token != NULL) {
    if (is_add(token)) {
        // pop two last variables from stack , add them, then push back the result
            float top_variable = stack_pop(root);
            float second_variable = stack_pop(root);
            float result = top_variable + second_variable;
            stack_push(root, result); // push the result to the stack back}
    } else if (is_sub(token)) {
        // pop two last variables from stack , substruct first from the second them, then push back the result
            float top_variable = stack_pop(root);
            float second_variable = stack_pop(root);
            float result = second_variable - top_variable;
            stack_push(root, result); // push the result to the stack back
    } else if (is_mult(token)) {
        // pop two last variables from stack , add them, then push back the result
            float top_variable = stack_pop(root);
            float second_variable = stack_pop(root);
            float result = second_variable * top_variable;
            stack_push(root, result); // push the result to the stack back
    } else if (is_number(token)) {
        // push number to the stack
        stack_push(root, atof(token));
    } else {
        // printf("\n<Logik fehlt!>\n");
        // do nothing
    }
    }
    /* Du kannst zur Erkennung der Token folgende Hilfsfunktionen
     * benutzen:
     *
     * Funktion          Rückgabewert von 1 bedeutet
     * ---------------------------------------------
     * is_add(token)     Token ist ein Pluszeichen
     * is_sub(token)     Token ist ein Minuszeichen
     * is_mult(token)    Token ist ein Multiplikationszeichen
     * is_number(token)  Token ist eine Zahl
     */

}

/* 
 * Erstelle einen Stack mit dynamischem Speicher.
 * Initialisiere die enthaltenen Variablen.
 *
 * Gebe einen Pointer auf den Stack zurück.
 */
stack* stack_erstellen() {
    stack* Stack = (stack*) malloc(sizeof(stack)); // allocate memory

    if (Stack == NULL) {
        return NULL;
    }

    // stack_element* stackElement = (stack_element*) malloc(sizeof(stack_element));
    Stack->top = NULL; // init top as NULL 
    // Stack->top = stackElement; // initialize empty stack
    
    return Stack;
}