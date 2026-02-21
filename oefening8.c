#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "oefening8.h"

void oefening8(void) {
    char data[] = "0x1A:0xFF:invalid:0x02:0x4B:0x7FFFFFFFFFFFFFFF";
    int resultaten[10];
    int teller = 0;

    printf("Start analyse van sensorstring...\n");

    // 2. OPDRACHT: Start de eerste tokenisatie
    char *token = strtok(data, ":");

    while (token != NULL) {
        char *endptr;
        errno = 0; // Cruciaal voor overflow check

        // 3. OPDRACHT: Converteer token naar long (hexadecimaal)
        long waarde = strtol(token, &endptr, 16);

        // 4. OPDRACHT: Implementeer de validatie-logica
        if (endptr == token) {
            printf("Negeren (geen data): %s\n", token);
        } 
        else if (errno == ERANGE) {
            // OVERFLOW HANDLING: Print de gevraagde foutmelding
            printf("[OVERFLOW] Waarde te groot: %s\n", token);
        } 
        else {
            resultaten[teller++] = (int)waarde;
            printf("Geaddeerd: %ld\n", waarde);
        }

        // Volgende token...
        token = strtok(NULL, ":");
    }

    // Toon de finale resultaten
    printf("\n--- Finale Resultaten ---\n");
    printf("Aantal geldige waarden: %d\n", teller);
    for (int i = 0; i < teller; i++) {
        printf("resultaten[%d] = 0x%X (%d)\n", i, resultaten[i], resultaten[i]);
    }
}
