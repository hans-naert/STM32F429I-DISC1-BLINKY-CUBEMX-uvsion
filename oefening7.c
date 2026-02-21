#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "oefening7.h"

static void add_log(char **matrix, int index, const char *format, ...) {
    char temp_buffer[256]; // Tijdelijke buffer voor de bewerking
    
    // Schrijf de prefix direct in de buffer
    int prefix_len = snprintf(temp_buffer, sizeof(temp_buffer), "[LOG]: ");
    
    va_list args;
    va_start(args, format);

    // 1. Gebruik vsnprintf om het bericht te formateren in temp_buffer (na de prefix)
    // We schrijven vanaf positie prefix_len, met de resterende buffergrootte
    int len = prefix_len + vsnprintf(temp_buffer + prefix_len, 
                                      sizeof(temp_buffer) - prefix_len, 
                                      format, args);
    
    va_end(args);

    // 2. Reserveer exact genoeg geheugen voor matrix[index] met malloc
    // Tip: de lengte van het bericht + 1 voor de \0
    matrix[index] = (char *)malloc((len + 1) * sizeof(char));

    // 3. Kopieer de inhoud van temp_buffer naar de nieuwe plek
    if (matrix[index] != NULL) {
        snprintf(matrix[index], len + 1, "%s", temp_buffer);
    }
}

void oefening7(void) {
    int aantal_logs = 3;
    
    // STAP A: Gebruik calloc om een array van 3 char-pointers te maken
    char **log_matrix = (char **)calloc(aantal_logs, sizeof(char *));

    // STAP B: Voeg logs toe
    add_log(log_matrix, 0, "Systeem gestart");
    add_log(log_matrix, 1, "Gebruiker %s ingelogd", "Admin");
    add_log(log_matrix, 2, "Foutcode: %d", 404);

    // STAP C: Print de jagged array (de log-matrix)
    printf("Inhoud van de Log-Matrix:\n");
    for (int i = 0; i < aantal_logs; i++) {
        if (log_matrix[i] != NULL) {
            printf("Regel %d: %s\n", i, log_matrix[i]);
        }
    }

    // STAP D: Geheugen vrijgeven (The Cleanup)
    // Denk aan de volgorde: eerst de rijen, dan de matrix!
    for (int i = 0; i < aantal_logs; i++) {
        free(log_matrix[i]);
    }
    free(log_matrix);
}
