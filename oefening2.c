/*
 * Oefening 2: De Grote Matrix Wissel
 * 
 * Dit programma demonstreert twee verschillende strategieën voor het
 * wisselen van rijen in datastructuren:
 * 1. Multidimensionale array (vaste 3x3): element-per-element swap
 * 2. Jagged array: pointer swap (efficiënter)
 */

#include <stdio.h>
#include <stdlib.h>
#include "oefening2.h"

/**
 * @brief Wisselt twee rijen in een vaste 3x3 matrix
 * @param matrix De 3x3 matrix
 * @param r1 Index van de eerste rij
 * @param r2 Index van de tweede rij
 * 
 * Deze functie kopieert de elementen één voor één met behulp van
 * een for-loop en een tijdelijke variabele.
 */
void swapMulti(int matrix[3][3], int r1, int r2) {
    // Wissel elk element van rij r1 met het overeenkomstige element van rij r2
    for (int i = 0; i < 3; i++) {
        int temp = matrix[r1][i];      // Bewaar element tijdelijk
        matrix[r1][i] = matrix[r2][i]; // Kopieer van r2 naar r1
        matrix[r2][i] = temp;           // Kopieer van temp naar r2
    }
}

/**
 * @brief Wisselt twee rijen in een jagged array door pointers te herschikken
 * @param jagged Array van pointers naar rijen van verschillende lengtes
 * @param metadata Array met de lengte van elke rij
 * @param r1 Index van de eerste rij
 * @param r2 Index van de tweede rij
 * 
 * Deze functie wisselt enkel de pointers, zonder de eigenlijke data
 * te kopiëren. Dit is veel efficiënter dan element-per-element kopiëren.
 */
void swapJagged(int* jagged[], int metadata[], int r1, int r2) {
    // Wissel de pointers in de jagged array
    int* tempPtr = jagged[r1];
    jagged[r1] = jagged[r2];
    jagged[r2] = tempPtr;
    
    // Wissel ook de metadata (lengtes van de rijen)
    int tempLen = metadata[r1];
    metadata[r1] = metadata[r2];
    metadata[r2] = tempLen;
}

/**
 * @brief Print een 3x3 matrix naar de console
 */
static void printMatrix(int matrix[3][3]) {
    for (int i = 0; i < 3; i++) {
        printf("  Rij %d: [", i);
        for (int j = 0; j < 3; j++) {
            printf("%d", matrix[i][j]);
            if (j < 2) printf(", ");
        }
        printf("]\n");
    }
}

/**
 * @brief Print een jagged array naar de console
 */
static void printJagged(int* jagged[], int metadata[], int numRows) {
    for (int i = 0; i < numRows; i++) {
        printf("  Rij %d (lengte %d): [", i, metadata[i]);
        for (int j = 0; j < metadata[i]; j++) {
            printf("%d", jagged[i][j]);
            if (j < metadata[i] - 1) printf(", ");
        }
        printf("]\n");
    }
}

void oefening2(void) {
    printf("=== De Grote Matrix Wissel ===\n\n");
    
    // ========== TEST 1: Multidimensionale 3x3 Matrix ==========
    printf("TEST 1: Multidimensionale 3x3 Matrix\n");
    printf("----------------------------------------\n");
    
    // Initialisatie: vaste 3x3 matrix
    int matrix[3][3] = {
        {1, 1, 1},
        {2, 2, 2},
        {3, 3, 3}
    };
    
    printf("Voor swap (rij 0 en rij 2):\n");
    printMatrix(matrix);
    
    // Wissel rij 0 en rij 2
    swapMulti(matrix, 0, 2);
    
    printf("\nNa swapMulti(matrix, 0, 2):\n");
    printMatrix(matrix);
    
    // Verificatie
    if (matrix[0][0] == 3 && matrix[2][0] == 1) {
        printf("\n✓ Swap succesvol! Rijen zijn correct gewisseld.\n");
    } else {
        printf("\n✗ Fout: Rijen zijn niet correct gewisseld.\n");
    }
    
    printf("\n\n");
    
    // ========== TEST 2: Jagged Array ==========
    printf("TEST 2: Jagged Array (gekartelde dataset)\n");
    printf("----------------------------------------\n");
    
    // Initialisatie: jagged array met rijen van verschillende lengtes
    int row0[] = {10, 10};           // lengte 2
    int row1[] = {20, 20, 20};       // lengte 3
    
    int* jagged[] = {row0, row1};    // Array van pointers
    int metadata[] = {2, 3};         // Lengtes van elke rij
    
    printf("Voor swap (rij 0 en rij 1):\n");
    printJagged(jagged, metadata, 2);
    
    // Bewaar originele pointers voor verificatie
    int* originalRow0 = jagged[0];
    int* originalRow1 = jagged[1];
    
    // Wissel rij 0 en rij 1
    swapJagged(jagged, metadata, 0, 1);
    
    printf("\nNa swapJagged(jagged, metadata, 0, 1):\n");
    printJagged(jagged, metadata, 2);
    
    // Verificatie: controleer of de pointers zijn gewisseld
    if (jagged[0] == originalRow1 && jagged[1] == originalRow0 &&
        metadata[0] == 3 && metadata[1] == 2) {
        printf("\n✓ Swap succesvol! Pointers zijn correct herschikt.\n");
        printf("  De eigenlijke data is NIET verplaatst of gekopieerd.\n");
    } else {
        printf("\n✗ Fout: Pointers zijn niet correct herschikt.\n");
    }
}

/*
 * UITLEG: Twee Verschillende Strategieën
 * ========================================
 * 
 * 1. MULTIDIMENSIONALE ARRAY (swapMulti):
 *    ---------------------------------------
 *    - Datastructuur: int matrix[3][3]
 *    - Een continu blok geheugen: 9 integers achter elkaar
 *    - Rijen zijn GEEN aparte pointers, maar berekenbare offsets
 *    - Rij-swap vereist het kopiëren van alle elementen één voor één
 * 
 *    Geheugenlay-out:
 *    [1][1][1] [2][2][2] [3][3][3]
 *     ←-rij 0-→ ←-rij 1-→ ←-rij 2-→
 * 
 *    Bij swapMulti(matrix, 0, 2):
 *    - Loop 3x: wissel matrix[0][i] met matrix[2][i]
 *    - Totaal: 3 lees-, 3 schrijfoperaties + tijdelijke opslag
 *    - Tijdscomplexiteit: O(n) waarbij n = aantal kolommen
 * 
 * 
 * 2. JAGGED ARRAY (swapJagged):
 *    ----------------------------
 *    - Datastructuur: int* jagged[]
 *    - Een array van POINTERS naar aparte geheugenblocken
 *    - Elke rij kan een verschillende lengte hebben
 *    - Rij-swap vereist alleen het herschikken van 2 pointers
 * 
 *    Geheugenlay-out:
 *    jagged[0] ──→ [10][10]         (lengte 2)
 *    jagged[1] ──→ [20][20][20]     (lengte 3)
 * 
 *    Bij swapJagged(jagged, metadata, 0, 1):
 *    - Wissel alleen de pointer-waarden in jagged[]
 *    - De eigenlijke data {10,10} en {20,20,20} blijft ongewijzigd
 *    - Tijdscomplexiteit: O(1) - constant, onafhankelijk van rijlengte
 * 
 * 
 * VERGELIJKING:
 * -------------
 * Multidimensionale array (swapMulti):
 *   ✓ Eenvoudige datastructuur
 *   ✓ Continu geheugen (cache-vriendelijk)
 *   ✗ Rij-swap is traag voor grote arrays (O(n))
 *   ✗ Alle rijen moeten dezelfde lengte hebben
 * 
 * Jagged array (swapJagged):
 *   ✓ Zeer snelle rij-swap (O(1))
 *   ✓ Flexibele rijlengtes
 *   ✓ Efficiënt voor dynamische data
 *   ✗ Extra geheugen voor pointers
 *   ✗ Minder cache-vriendelijk (indirectie)
 * 
 * 
 * CONCLUSIE:
 * ----------
 * Kies swapMulti wanneer:
 * - Je vaste, kleine matrices hebt
 * - Cache-localiteit belangrijk is
 * - Je simpele code prefereert
 * 
 * Kies swapJagged wanneer:
 * - Je vaak rijen moet wisselen
 * - Rijen verschillende lengtes hebben
 * - Prestaties bij grote datasets cruciaal zijn
 */
