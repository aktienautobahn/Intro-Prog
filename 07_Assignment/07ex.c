/*
Zur Abgabe einen branch `iprg-b07` erstellen und pushen, in dem als einzige Datei die `07ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && ./07ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./07ex_test.o
*/

#include "sphinx.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:

Da spaziert man entspannt durch Theben, und plötzlich kommt eine Sphinx angeflogen
und spricht: "Ich habe mir ein Array mit n absteigend sortierten Zahlen überlegt (Zahlen
können mehrfach vorkommen). Du darfst mich nach dem Wert an 1 + log2(n) (aufgerundet) vielen
Positionen fragen. Und wenn du mir danach nicht sagen kannst, ob das Array die Zahl 12345
enthält, dann fresse ich dich.".

Geben Sie zurück, ob das Array der Sphinx die Zahl 12345 enthält. Um den Wert an Position `i`
zu erfragen, rufen Sie `sphinx_ask(s, ix)` auf. Aber Achtung: Wenn Sie diese Funktion mehr als
1 + log2(n) (aufgerundet) mal aufrufen, stürzt das Programm fehlerhaft ab.
*/
bool descending_sphinx(Sphinx *s, size_t n) {

    int low = 0;
    int high = n-1;
    int mid;
    int answer;
    bool found = false;

    // edge case
    if (n < 1) return false;
    else if (n == 1) {
       if (12345 == sphinx_ask(s, 0)) found = true; 
    } else {
    while (high >= low) {
        if (high != low) {
        mid = low + (high - low) / 2;
        } else {
            mid = high;
        }
        answer = sphinx_ask(s, mid);

        // case found
        if (answer == 12345) 
        {   
            found = true;
            break;
        } else if (answer > 12345) // go right
        {
            low = mid + 1;
        } else  // go left
        {  
            high = mid - 1;
        }


    }

}

    return found;


}
