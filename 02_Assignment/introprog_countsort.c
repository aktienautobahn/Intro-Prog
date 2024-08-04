#include <stdio.h>
#include <string.h>
#include "introprog_countsort.h"
#include "arrayio.h"

// calculate max value of array
int _find_max(int input_array[], int len) {
    int max = input_array[0];
    for (int i = 1; i < len; i++) {
        if (input_array[i] > max) {
            max = input_array[i];
        }
    }
    return max;
}

/* Ab hier Funktion count_sort_calculate_counts implementieren */

void count_sort_calculate_counts(int input_array[], int len, int count_array[]) {
    // calculate frequency of each value and assign it to it's index
    for (int i = 0; i < len; i++) {
    count_array[input_array[i]]++;
    }

    
}


/* Ab hier Funktion count_sort_write_output_array implementieren */
void count_sort_write_output_array(int output_array[], int count_array[], SortDirection order) {
    int k = 0;

if (order == ASCENDING || order == NOTDEFINED) {
    // ascending sorting
    // calculate position of each value in the output array
    for (int j=0; j < MAX_VALUE+1; j++) {
            for (int i = 0; i < count_array[j]; i++) {
            output_array[k] = j;
            k++;
            }
        }

    

} else {
    // descending sorting
    // calculate position of each value in the output array
    for (int j=MAX_VALUE+1; j > 0; j--) {
            for (int i = 0; i < count_array[j]; i++) {
            output_array[k] = j;
            k++;
            }
        }
}

}
/* Ab hier Funktion extract_order_direction implementieren */
SortDirection extract_order_direction(char *order) {
    char asc[4] = "asc";
    char desc[5] = "desc";
    if (strcmp(asc, order) == 0) return ASCENDING;
    else if (strcmp(desc, order) == 0) return DESCENDING;
    else return NOTDEFINED;
    
}

/* Ab hier Funktion count_sort implementieren und entsprechende Funktionsaufrufe einfügen */
void count_sort(int input_array[], int len, int output_array[], SortDirection order) {

    
// find length of array based on max value + 1
    // int count_array_len = _find_max(input_array, len)+1;
    int count_array[MAX_VALUE+1];
    // set all bytes of array to zero
    memset(count_array, 0, sizeof(count_array));

    // fill count array
    count_sort_calculate_counts(input_array, len, count_array);

    // fill output array
    count_sort_write_output_array(output_array, count_array, order);
}


int main(int argc, char *argv[]) {

    if (argc < 3){
        printf("Aufruf: %s <Dateiname> asc|desc\n", argv[0]);
        printf("Beispiel: %s zahlen.txt asc\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    

    /*
     * Hier die Sortierrichtung einlesen und einer Variablen
     * des Datentypes SortDirection (siehe h-Datei) verwenden.
     * 
     * Beenden des Programmes mit derselben Ausgabe der Hilfe 
     * (siehe Anfang main-Funktion)
     * 
     * Implementieren Sie zur Umwandlung die Funktion 
     * extract_order_direction und verwenden Sie, wenn kein 
     * gültiger Parameter gefunden wurde, NOTDEFINED.
     * 
     * Hinweis: Die extract_order_direction soll auch mit dieser
     * SortDirection auch ein Standardverhalten implementieren, 
     * die nicht mit einem Fehler terminiert.
     * 
     * Das Hauptprogramm main hingegen, darf auf unkorrekte Eingaben
     * reagieren und auch entsprechend Ausgaben erzeugen oder mit Fehler
     * beenden.
     */




    int input_array[MAX_LAENGE];
    int len = read_array_from_file(input_array, MAX_LAENGE, filename);
    int output_array[len];

    //extract order direction asc, desc, undefined
    SortDirection order = extract_order_direction(argv[2]);


    
    printf("Unsortiertes Array:");
    print_array(input_array, len);

    /*
     * Hier count_sort aufrufen und alle nötigen Deklarationen einfügen!
     */
    count_sort(input_array, len, output_array, order);
    printf("Sortiertes Array:");

    /* Folgende Zeile einkommentieren, um das Array auszugeben! */
    print_array(output_array, len);

    return 0;
}
