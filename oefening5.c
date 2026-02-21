#include <stdio.h>
#include <string.h>
#include "oefening5.h"

// 1. DEFINIEER DE STRUCT
// Maak een struct 'Student' met: naam (char array) en cijfer (float)
typedef struct {
    char naam[50];
    float cijfer;
} Student;

// 2. PRINT FUNCTIE
// Gebruik pointer-arithmetiek (lijst + i) en de -> operator
static void print_studenten(Student *lijst, int aantal) {
    printf("\n--- Overzicht Studenten ---\n");
    for (int i = 0; i < aantal; i++) {
        // Printf van naam en cijfer via de pointer (lijst + i)
        printf("Student: %s, Cijfer: %.1f\n", (lijst + i)->naam, (lijst + i)->cijfer);
    }
}

// 3. UPDATE FUNCTIE
// Gebruik de -> operator om het cijfer van de student aan te passen
static void verhoog_cijfer(Student *s, float verhoging) {
    // Tel de verhoging op bij het bestaande cijfer
    s->cijfer += verhoging;
}

void oefening5(void) {
    // 4. INITIALISATIE
    // Maak een array 'klas' van 3 studenten met testdata
    Student klas[3] = {
        {"Alice", 8.5},
        {"Bob", 6.0},
        {"Charlie", 7.2}
    };

    // Toon de situatie vooraf
    print_studenten(klas, 3);

    // 5. DE WIJZIGING
    // Pas het cijfer van Bob (index 1) aan met een verhoging van 0.5
    // Gebruik van de adres-operator (&)
    verhoog_cijfer(&klas[1], 0.5);

    // Toon het resultaat
    print_studenten(klas, 3);
}
