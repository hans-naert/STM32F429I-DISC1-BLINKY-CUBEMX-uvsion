#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oefening9.h"

typedef struct {
    char naam[50];
    float cijfer;
} Student;

// 1. Vergelijker voor cijfers (float, aflopend: Groot -> Klein)
static int compare_cijfers(const void *a, const void *b) {
    // Cast de void pointers naar Student pointers
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    
    // Vergelijk de floats (aflopend: hogere cijfers eerst)
    if (s1->cijfer < s2->cijfer) return 1;   // s1 is kleiner, dus komt later
    if (s1->cijfer > s2->cijfer) return -1;  // s1 is groter, dus komt eerder
    return 0;
}

// 2. Vergelijker voor namen (alfabetisch)
static int compare_namen(const void *a, const void *b) {
    // Cast naar Student pointers
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    
    // Gebruik strcmp voor alfabetische vergelijking
    return strcmp(s1->naam, s2->naam);
}

// 3. Vergelijker voor bsearch: zoekt een string in Student array
static int compare_naam_key(const void *key, const void *element) {
    // key is een char*, element is een Student*
    const char *zoek_naam = (const char *)key;
    const Student *student = (const Student *)element;
    
    return strcmp(zoek_naam, student->naam);
}

static void print_studenten(Student *lijst, int aantal) {
    for (int i = 0; i < aantal; i++) {
        printf("%-10s: %.1f\n", (lijst + i)->naam, (lijst + i)->cijfer);
    }
}

void oefening9(void) {
    Student klas[5] = {
        {"Alice", 8.5},
        {"Bob", 6.0},
        {"Charlie", 7.2},
        {"David", 9.1},
        {"Eva", 6.8}
    };
    int n = 5;

    // --- STAP 1: SORTEREN OP CIJFER ---
    printf("Klas gesorteerd op cijfer (hoog naar laag):\n");
    qsort(klas, n, sizeof(Student), compare_cijfers);
    
    print_studenten(klas, n);

    // --- STAP 2: ZOEKEN OP NAAM ---
    // Belangrijk: Voor bsearch op naam moet de lijst eerst alfabetisch gesorteerd zijn!
    printf("\nKlas her-sorteren op naam voor zoekfunctie...\n");
    qsort(klas, n, sizeof(Student), compare_namen);
    
    printf("Alfabetisch gesorteerd:\n");
    print_studenten(klas, n);
    
    char zoek_naam[] = "Charlie";
    printf("\nZoeken naar '%s'...\n", zoek_naam);
    
    // Gebruik bsearch met de speciale compare functie
    // key = zoek_naam (de string), array = klas, compare = compare_naam_key
    Student *gevonden = (Student *)bsearch(zoek_naam, klas, n, sizeof(Student), compare_naam_key);

    if (gevonden != NULL) {
        printf("Gevonden! %s heeft een %.1f\n", gevonden->naam, gevonden->cijfer);
    } else {
        printf("Student %s niet gevonden.\n", zoek_naam);
    }
}
