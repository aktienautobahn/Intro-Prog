/*
Willkommen zum achten Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um Pointer und Arrays.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "turtlecanvas.h"

/*
Aufgabe 1a:
Lesen Sie das Headerfile `turtlecanvas.h`. Diese Funktion soll die Turtle `d` Schritte vorwärts machen lassen.
*/
void turtle_advance_by(TurtleCanvas *c, uint32_t d) {
    for (int i = 0 ; i < d; i++  ) {
    turtle_advance(c);
    }
    return;
}

/*
Aufgabe 1b:
Füllen Sie die Turtlecanvas mit horizontalen, abwechselnd schwarzen und weißen Linien (die unterste Zeile soll
schwarz gefärbt werden). Die Turtle ist anfangs an Position (0, 0), ist nach rechts orientiert, und zeichnet schwarz.
*/
void turtle_stripes(TurtleCanvas *c) {

    for (int y = 0; y < turtle_canvas_height(c); y++) {

    turtle_advance_by(c, turtle_canvas_width(c));
    turtle_rotate_left(c);
    turtle_advance(c);
    turtle_toggle_color(c);
    turtle_rotate_left(c);
    turtle_rotate_right(c);
    turtle_advance(c);
    turtle_toggle_color(c);
    turtle_rotate_right(c);

    }

    return;
}

/*
Aufgabe 1c:
Lesen Sie die Implementierungen der Turtlecanvas-Funktionen weiter unten in der "turtlecanvas.h".
Der Quellcode sollte vollständig verständlich und unüberraschend sein.
Hinweis: Diese Aufgabe wird nicht bewertet.
*/

/*
Aufgabe 2a:
Geben Sie einen Pointer auf das erste Vorkommen der größten Zahl im Eingabearray zurück.
*/
uint16_t *find_maximal_number(uint16_t numbers[], size_t numbers_len) {
    // declaration of helper variables
    uint16_t *ptr = numbers;
    uint16_t max_value = 0;
    uint16_t *max_value_ptr = &max_value;

    // loop for comparing current ptr value with the max one 
    for (int i = 0; i < numbers_len; i++) 
    {  
        // printf("max value address:  %p with value %d\n", ptr, *ptr);
 
        if (*ptr > *max_value_ptr) {
            // printf("max value is %d\n", *ptr);
            // assign new maximum value address
            max_value_ptr = ptr;
        }
        ptr++;
                

    }

    return max_value_ptr;
}

/*
Aufgabe 2b:
Geben Sie (einen Pointer auf) das Teilarray zurück, welches ab dem ersten Vorkommen der größten Zahl im Eingabearray beginnt.
*/
uint16_t *find_subarray_starting_at_maximal_number(uint16_t numbers[], size_t numbers_len) {
    numbers = find_maximal_number(numbers, numbers_len);
    return numbers;
}

/*
Aufgabe 2c:
Geben Sie die größtmögliche Distanz zwischen zwei Zahlenwerten aus dem Array `numbers` zurück.
Beispiel: Im Array {1, 3, 7, 4} ist die größte Distanz die zwischen 1 und 7, und beträgt damit `6`.
*/
uint16_t find_maximum_distance(uint16_t numbers[], size_t numbers_len) {
    int max = 0;
    int min = 0;
    // find maximum
    for (int i = 0; i < numbers_len; i++) {
        if (numbers[i]>max) max = numbers[i];
    }
    // find minimum
    min = max;
    for (int i = 0; i < numbers_len; i++) {
        if (numbers[i]<min) min = numbers[i];
    }
 
    // calculate difference between max and min and return it 
    return max-min;
}

/*
Aufgabe 2d:
Geben Sie die kleinstmögliche Distanz zwischen zwei Zahlenwerten aus dem Array `numbers` zurück.
Beispiel: Im Array {1, 3, 7, 4} ist die kleinste Distanz die zwischen 3 und 4, und beträgt damit `1`.
*/
void sort_ascending(uint16_t in[], uint16_t out[], size_t len);


uint16_t find_minimum_distance(uint16_t numbers[], size_t numbers_len) {
    // variables declaration
    int current_min_distance = 0;
    uint16_t out[numbers_len];
    // sort the array
    sort_ascending(numbers, out, numbers_len);

    // init first min distance (out of the substrucion of the second and the first element of the sorted array)
    current_min_distance = out[1] - out[0];
    // loop through sorted array and find minimum distance
    for (int i = 2; i< numbers_len; i++) {
        if (out[i] - out[i-1] < current_min_distance) {
            current_min_distance = out[i] - out[i-1]; 
        };
        

    }
    return current_min_distance;
}

/*
Aufgabe 2e:
Schreiben Sie die ersten `numbers_len` Quadratzahlen aufsteigend in das gegebene Array `numbers`.
Hinweis: Wir starten bei `1`. Sollte numbers_len also `5` sein, sind die ersten 5 Quadratzahlen bis
einschließlich die von 5 gemeint: 1, 4, 9, 16, 25.
*/
void square_ascending(uint16_t numbers[], size_t numbers_len) {
    uint16_t *ptr = numbers;
    
    // int last_element = numbers_len + 1;
    *ptr = 1;
    for (int i = 1; i < numbers_len; i++) {
        // assign new value (square ) to the array
        *(ptr+i) = (i+1) * (i+1);
    } 
    return;
}

/*
Aufgabe 2f:
Füllen Sie das Array `out` mit den aufsteigend sortierten Zahlen aus dem `in` Array. Beide Arrays haben die Länge `len`.
Beispiel: Ist `in` {1, 4, 3, 7, 4}, so soll `out` am Ende {1, 3, 4, 4, 7} sein.
*/
void sort_ascending(uint16_t in[], uint16_t out[], size_t len) {
    // declaration of variables

    uint16_t temp = 0;
    int i=0;


    // insersion sort algorithm

    for (int j = 1; j < len; j++ ) {
        temp = in[j];
        i = j-1;
        while (i>=0 && in[i]>temp) {
            in[i+1] = in[i];
            i--;
        }
        in[i+1] = temp;

    }
    // writing sorted numbers into the proper "out" array

    i = 0;
    while (i < len) {
        out[i] = in[i];
        i++;
    }    
    return;
}
