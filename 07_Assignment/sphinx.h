#ifndef SPHINX_H
#define SPHINX_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Ein Visualizer sammelt Arrays vom Typ unit8_t, die bei einem nicht erfolgreichen Test visualisiert werden.
*/
typedef struct Sphinx_ Sphinx;

/*
Gibt den Wert an Stelle `i` im Array der Sphinx zurück.
*/
uint16_t sphinx_ask(Sphinx *s, size_t i);





/*
Implementation details below.
*/

struct Sphinx_ {
    uint16_t *arr;
    size_t arr_len;
    size_t max_questions;
    size_t questions_so_far;
    size_t *questions;
};

Sphinx new_sphinx(uint16_t *arr, size_t arr_len, size_t max_questions) {
    Sphinx s;
    s.arr = arr;
    s.arr_len = arr_len;
    s.max_questions = max_questions;
    s.questions_so_far = 0;
    s.questions = (size_t *) malloc(sizeof(size_t) * max_questions);

    return s;
}

void free_sphinx(Sphinx s) {
    free(s.questions);
}

uint16_t print_failure(Sphinx *s, size_t question) {
    fprintf(stderr, "Das Array der Sphinx war:\n");
        fprintf(stderr, "[");
        for (size_t i = 0; i < s->arr_len; i++) {
            fprintf(stderr, "%d", s->arr[i]);
            if (i < s->arr_len - 1) {
                fprintf(stderr, ", ");
            }
        }
        fprintf(stderr, "]\n\n");
        fprintf(stderr, "Ihre Fragen waren:\n");
        for (size_t i = 0; i < s->questions_so_far; i++) {
            fprintf(stderr, "  Frage: % 3ld, Antwort: %d\n", s->questions[i], s->arr[s->questions[i]]);
        }
        fprintf(stderr, "  Frage: % 3ld, Antwort: %s\n", question, "Omnomnom");

        abort();
}

uint16_t sphinx_ask(Sphinx *s, size_t question) {
    if (s->questions_so_far < s->max_questions) {
        if (question >= s->arr_len) {
            fprintf(stderr, "Nach Position %ld in einem Array der Länge %ld zu fragen, war keine gute Idee.\n\n", question, s->arr_len);
            return print_failure(s, question);
        } else {
            s->questions[s->questions_so_far] = question;
            s->questions_so_far += 1;
            return s->arr[question];
        }
    } else {
        fprintf(stderr, "In einem Array der Länge %ld nach %ld Positionen zu fragen, war ein mal zu viel.\n\n", s->arr_len, s->questions_so_far + 1);

        return print_failure(s, question);
    }
}

#endif