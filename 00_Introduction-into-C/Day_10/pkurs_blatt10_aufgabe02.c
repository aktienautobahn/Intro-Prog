// Bibiotheken I/O, string und stdlib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* prepare_repeated_message(char* message, int repeat){
    int length = strlen(message);
    char *var = (char*)malloc((length + 2) * repeat + 1);
    // check if memory is allocated
    if (var == NULL) {
        //memory is not allocated
        return NULL;
    }

    var[0] = '\0';
    char* newliner = "\n";
    // loop for string concatenation
    for (int i = 0; i < repeat; i++) {
        strcat(var, message);
        strcat(var, newliner);

    }

    return var;
}

// Einsprungspunkt 'main' in das Programm definieren
int main() {
    // Text hier ohne Umbruch ausgeben, 
    // da die Umbrüche in der Funktion generiert werden sollen
    char* o = prepare_repeated_message("Hallo Osiris!", 3);

    if (o != NULL) {

    printf("%s", o);
    free(o);
    }

    // Rückgabe von 0 zur Signalisierung, dass kein Fehler aufgetreten ist
    return 0;
}

// clang -std=c11 -Wall -g pkurs_blatt10_aufgabe02.c -o pkurs_blatt10_aufgabe02