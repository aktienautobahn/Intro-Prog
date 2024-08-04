/*
Willkommen zum fünften Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um Rekursion.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o
*/

#include "05_canvas.h"
#include <stdio.h>
#include <math.h>

/*
Aufgabe 1a:
Zeichnen Sie eine horizontale Linie der Länge `width`, deren am weitesten links liegender Pixel bei `(x, y)` ist.

_Benutzen Sie keine Schleifen - Die Aufgabe soll über Rekursion gelöst werden!_

*/
Canvas recursive_line(Canvas c, int x, int y, int width) {

    if (width == 0) return c; // Abbruch beim Erreichen der Länge
    if (x > canvas_width(c)-1) return c; // Abbruch beim Erreichen der Canvas Width
    if (x < 0) return recursive_line(c, x+1, y, width-1); // Aufrufen der Recursion ohne zu zeichnen
    // Zeichenen, wenn alle Bevorstehenden Abbruchbedingungen nicht erfüllt sind.

    c = canvas_set_black(c, x, y);

    return recursive_line(c, x+1, y, width-1);

}

/*
Aufgabe 1b:
Zeichnen Sie ein Rechteck mit der Breite `width` und der Höhe `height`. Der Pixel der linken unteren Ecke liegt bei `(x, y)`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
Canvas recursive_rectangle(Canvas c, int x, int y, int width, int height) {


    // Prüfung Out of Canvas:
    if (height == 0) return c;
    if (y > canvas_height(c)-1) return c; // Abbruch beim Erreichen der Canvas Width
    if (y < 0) return recursive_rectangle(c, x, y+1, width, height-1); // Aufrufen der Recursion ohne zu zeichnen
    // draw line function call
    c = recursive_line(c, x, y, width);

    return recursive_rectangle(c, x, y+1, width, height-1);
}

/*
Aufgabe 2:
Der *Sierpinski Carpet der Ordnung 0* ist ein einzelnes schwarzes Pixel.
Der *Sierpinski Carpet der Ordnung n+1* besteht aus acht Sierpinski Carpets der Ordnung n, angeordnet als drei-mal-drei
Quadrat dessen Mittelstück fehlt.

Beispiele (`X` stellt schwarze Pixel dar)
=========================================

Ordnung 0:

X

Ordnung 1:

XXX
X X
XXX

Ordnung 2:

XXXXXXXXX
X XX XX X
XXXXXXXXX
XXX   XXX
X X   X X
XXX   XXX
XXXXXXXXX
X XX XX X
XXXXXXXXX

Siehe auch die Datei `05sierpinski.jpg`

Aufgabe 2a:
Um in der nächsten Aufgabe den Sierpinski-Carpet auf die Canvas zeichnen zu können müssen Potenzen berechnet werden.
Implementieren Sie die Berechnung der Potenz einer nicht-negativen, ganzzahligen Basis `b` mit einem
nicht-negativen, ganzzahligen Exponenten `exp`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
int power(int b, int exp){
    if (exp == 0) return 1;
    else return (b * power(b, exp-1));
}

/*
Aufgabe 2b:
Diese Funktion soll den Sierpinski Carpet der Ordnung `n` auf die Canvas zeichnen, mit unterer linker Ecke an Koordinate `(x, y)`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/


// Forward delaration of the function
Canvas sierpinski_carpet(Canvas c, int n, int x, int y);


Canvas sierpinski_carpet(Canvas c, int n, int x, int y) {
    // define the dimensions of square


    // check if depth 0 is reached
    if (n == 0) 
    {
        // if so, draw a black rectangle
        if (x < canvas_width(c) && y < canvas_height(c)) {
        c = canvas_set_black(c, x, y);
        }
        return c;
    }
    // calculate offset size
    int offset = canvas_width(c) / power(3, n);
    /// setzt man den nächsten 
    c = sierpinski_carpet(c, n-1, x, y); // left square
    c = sierpinski_carpet(c, n-1, x+offset, y); // middle square
    c = sierpinski_carpet(c, n-1, x+(offset*2), y); // right square
    
    // draw middle row
    c = sierpinski_carpet(c, n-1, x, y+offset); // left square 
    // middle square (white one! --> don't draw)
    c = sierpinski_carpet(c, n-1, x+(offset*2), y+offset); // left square

    // draw upper row
    c = sierpinski_carpet(c, n-1, x, y+(offset*2)); // left square   
    c = sierpinski_carpet(c, n-1, x+offset, y+(offset*2)); // left square   
    c = sierpinski_carpet(c, n-1, x+(offset*2), y+(offset*2)); // left square     

    return c;

}

/*
Aufgabe 3:
Implementieren Sie einen schwarzen Fülleimer. Gegeben eine Koordinate `(x, y)` auf einer (bereits bemalten) Canvas, soll die komplette
zusammenhängende Fläche aller Pixel der selben Farbe (schwarz oder weiß) schwarz gefärbt werden.
Zwei Pixel sind Teil der selben Fläche wenn sie die selbe Farbe haben und direkt benachbart sind. Jeder Pixel hat bis
zu vier direkte Nachbarn - die Diagonalen zählen nicht.

Funktionen, um die Farbe eines Pixels auf der Canvas zu bestimmen, sind im Headerfile der Canvas dokumentiert.
*/
Canvas bucket_fill(Canvas c, int x, int y) {
    // check if the pixel inside canvas area (if yes, just return canvas)
    if (x < 0 || y < 0 || x >= canvas_width(c) || y >= canvas_height(c)) {
        return c;
    }
    // check if the pixel has the same color (if yes, just return canvas)
    if (pixel_is_black(c, x, y)) {
        return c;
    }
    // painting target pixel
    c = canvas_set_black(c, x, y);

    // coloring neighboring pixels (flood filling in four direction recursively)
    c = bucket_fill(c, x+1, y);
    c = bucket_fill(c, x, y+1);
    c = bucket_fill(c, x-1, y);
    c = bucket_fill(c, x, y-1);

    return c;
}
