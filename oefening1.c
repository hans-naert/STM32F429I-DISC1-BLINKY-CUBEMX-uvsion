/*
 * Oefening 1: Swap functie met XOR operator
 * 
 * Dit programma demonstreert hoe twee gehele getallen van waarde kunnen 
 * wisselen via pointers (call by address) en de XOR-operator, zonder 
 * gebruik van een tijdelijke variabele.
 */

#include <stdio.h>
#include "oefening1.h"

/**
 * @brief Wisselt de waarden van twee integers met behulp van XOR
 * @param a Pointer naar het eerste getal
 * @param b Pointer naar het tweede getal
 * 
 * Deze functie gebruikt call by address (pointers) om de originele
 * waarden rechtstreeks in het geheugen te wijzigen.
 */
void swap(int *a, int *b) {
    // XOR-swap algoritme in 3 stappen:
    *a = *a ^ *b;  // Stap 1: a bevat nu a XOR b
    *b = *a ^ *b;  // Stap 2: b bevat nu (a XOR b) XOR b = a (originele waarde)
    *a = *a ^ *b;  // Stap 3: a bevat nu (a XOR b) XOR a = b (originele waarde)
}

void oefening1(void) {
    // Gegeven waarden
    int a = 15;
    int b = 27;
    
    printf("=== XOR Swap Demonstratie ===\n\n");
    printf("Voor swap:\n");
    printf("  a = %d\n", a);
    printf("  b = %d\n\n", b);
    
    // Roep swap aan met adressen (call by address)
    swap(&a, &b);
    
    printf("Na swap(&a, &b):\n");
    printf("  a = %d\n", a);
    printf("  b = %d\n\n", b);
    
    // Verificatie
    if (a == 27 && b == 15) {
        printf("✓ Swap succesvol! De waarden zijn correct omgewisseld.\n");
    } else {
        printf("✗ Fout: De waarden zijn niet correct omgewisseld.\n");
    }
}

/*
 * UITLEG: Waarom werkt deze aanpak?
 * ==================================
 * 
 * 1. XOR-eigenschappen:
 *    - XOR is commutatief: A ^ B = B ^ A
 *    - XOR is associatief: (A ^ B) ^ C = A ^ (B ^ C)
 *    - Elke waarde XOR met zichzelf = 0: A ^ A = 0
 *    - Elke waarde XOR met 0 = die waarde: A ^ 0 = A
 * 
 * 2. Stapsgewijze analyse (stel a=15, b=27):
 *    
 *    Initieel:
 *    - a = 15 (binair: 00001111)
 *    - b = 27 (binair: 00011011)
 *    
 *    Stap 1: *a = *a ^ *b
 *    - a wordt: 15 ^ 27 = 00001111 ^ 00011011 = 00010100 (20 in decimaal)
 *    - b blijft: 27
 *    
 *    Stap 2: *b = *a ^ *b
 *    - b wordt: 20 ^ 27 = (15 ^ 27) ^ 27 = 15 ^ (27 ^ 27) = 15 ^ 0 = 15
 *    - a blijft: 20 (nog steeds 15 ^ 27)
 *    
 *    Stap 3: *a = *a ^ *b
 *    - a wordt: 20 ^ 15 = (15 ^ 27) ^ 15 = (15 ^ 15) ^ 27 = 0 ^ 27 = 27
 *    - b blijft: 15
 *    
 *    Resultaat: a = 27, b = 15 ✓
 * 
 * 3. Call by address (pointers):
 *    - Door pointers (*a en *b) te gebruiken, wijzigen we de waarden
 *      op de ORIGINELE geheugenlocaties van a en b in main().
 *    - De & operator in swap(&a, &b) geeft de adressen door.
 *    - De * operator (dereference) in de functie gebruikt deze adressen
 *      om de waarden rechtstreeks in het geheugen te wijzigen.
 *    - Zonder pointers (call by value) zouden alleen lokale kopieën
 *      worden gewisseld, en zouden a en b onveranderd blijven in main().
 * 
 * 4. Voordelen XOR-swap:
 *    - Geen extra geheugen nodig (geen tijdelijke variabele)
 *    - Elegant en compact
 * 
 * 5. Nadelen/beperkingen:
 *    - Minder leesbaar dan traditionele swap met tijdelijke variabele
 *    - Werkt NIET als a en b naar hetzelfde geheugenadres verwijzen
 *      (dan wordt de waarde 0!)
 *    - In moderne compilers is een traditionele swap vaak even snel
 *      (compilers optimaliseren dit weg via registerswaps)
 */
