/*
 * Oefening 4: Variadische functies
 * 
 * Dit programma demonstreert het gebruik van variadische functies in C
 * met behulp van va_list, va_start, va_arg en va_end uit <stdarg.h>
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include "oefening4.h"

/* ============================================
 * 4.1 Som van integers
 * ============================================ */

/**
 * @brief Berekent de som van een variabel aantal integers
 * @param count Aantal integers die volgen
 * @param ... Variabel aantal integer argumenten
 * @return Som van alle integers
 */
int sum(int count, ...) {
    va_list args;           // Declareer argumentenlijst
    va_start(args, count);  // Initialiseer vanaf laatste vaste parameter
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int);  // Haal volgende int argument op
        total += value;
    }
    
    va_end(args);  // Cleanup
    return total;
}

/* ============================================
 * 4.2 Grootste waarde
 * ============================================ */

/**
 * @brief Zoekt de grootste waarde uit een variabel aantal integers
 * @param count Aantal integers die volgen
 * @param ... Variabel aantal integer argumenten
 * @return De grootste waarde
 */
int max_of(int count, ...) {
    if (count <= 0) {
        return INT_MIN;  // Return minimum waarde als er geen argumenten zijn
    }
    
    va_list args;
    va_start(args, count);
    
    int max = va_arg(args, int);  // Eerste waarde als initiële max
    
    for (int i = 1; i < count; i++) {
        int value = va_arg(args, int);
        if (value > max) {
            max = value;
        }
    }
    
    va_end(args);
    return max;
}

/* ============================================
 * 4.3 Gemiddelde van doubles
 * ============================================ */

/**
 * @brief Berekent het gemiddelde van een variabel aantal doubles
 * @param count Aantal doubles die volgen
 * @param ... Variabel aantal double argumenten
 * @return Gemiddelde als double
 */
double average(int count, ...) {
    if (count <= 0) {
        return 0.0;
    }
    
    va_list args;
    va_start(args, count);
    
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        double value = va_arg(args, double);
        total += value;
    }
    
    va_end(args);
    return total / count;
}

/* ============================================
 * 4.4 Veilige Logger
 * ============================================ */

/**
 * @brief Veilige logger die een prefix toevoegt en buffer overflow voorkomt
 * @param dest Doelbuffer
 * @param dest_size Grootte van doelbuffer
 * @param format Format string (printf-stijl)
 * @param ... Variabel aantal argumenten voor format string
 */
void my_logger(char *dest, int dest_size, const char *format, ...) {
    // 1. Declareer de variabele argumentenlijst
    va_list args;
    
    // 2. Start de argumentenlijst
    va_start(args, format);
    
    // 3. Plaats eerst de prefix "[LOG]: " in de buffer
    const char *prefix = "[LOG]: ";
    int prefix_len = snprintf(dest, dest_size, "%s", prefix);
    
    // Check of er nog ruimte over is na de prefix
    if (prefix_len >= 0 && prefix_len < dest_size) {
        // 4. Gebruik vsnprintf om het geformatteerde bericht toe te voegen
        // Schrijf naar dest + prefix_len (na de prefix)
        // Resterende ruimte: dest_size - prefix_len
        vsnprintf(dest + prefix_len, dest_size - prefix_len, format, args);
    }
    
    // 5. Sluit de argumentenlijst af
    va_end(args);
}

/* ============================================
 * Demo functies
 * ============================================ */

void demo_sum(void) {
    printf("=== 4.1 Som van integers ===\n\n");
    
    printf("Functie: int sum(int count, ...);\n\n");
    
    // Test 1
    int s1 = sum(4, 10, 20, 5, 3);
    printf("sum(4, 10, 20, 5, 3) = %d\n", s1);
    printf("  Verwacht: 38\n");
    printf("  %s\n\n", s1 == 38 ? "✓ Correct!" : "✗ Fout!");
    
    // Test 2
    int s2 = sum(6, 1, 2, 3, 4, 5, 6);
    printf("sum(6, 1, 2, 3, 4, 5, 6) = %d\n", s2);
    printf("  Verwacht: 21\n");
    printf("  %s\n\n", s2 == 21 ? "✓ Correct!" : "✗ Fout!");
    
    // Test 3
    int s3 = sum(1, 100);
    printf("sum(1, 100) = %d\n", s3);
    printf("  Verwacht: 100\n");
    printf("  %s\n\n", s3 == 100 ? "✓ Correct!" : "✗ Fout!");
}

void demo_max(void) {
    printf("=== 4.2 Grootste waarde ===\n\n");
    
    printf("Functie: int max_of(int count, ...);\n\n");
    
    // Test 1
    int m1 = max_of(5, 4, 99, 12, 3, 50);
    printf("max_of(5, 4, 99, 12, 3, 50) = %d\n", m1);
    printf("  Verwacht: 99\n");
    printf("  %s\n\n", m1 == 99 ? "✓ Correct!" : "✗ Fout!");
    
    // Test 2
    int m2 = max_of(7, 5, -10, 42, 0, 100, 50, 99);
    printf("max_of(7, 5, -10, 42, 0, 100, 50, 99) = %d\n", m2);
    printf("  Verwacht: 100\n");
    printf("  %s\n\n", m2 == 100 ? "✓ Correct!" : "✗ Fout!");
    
    // Test 3 - negatieve getallen
    int m3 = max_of(4, -5, -10, -1, -20);
    printf("max_of(4, -5, -10, -1, -20) = %d\n", m3);
    printf("  Verwacht: -1\n");
    printf("  %s\n\n", m3 == -1 ? "✓ Correct!" : "✗ Fout!");
}

void demo_average(void) {
    printf("=== 4.3 Gemiddelde van doubles ===\n\n");
    
    printf("Functie: double average(int count, ...);\n\n");
    
    // Test 1
    double g1 = average(3, 1.5, 2.5, 4.0);
    printf("average(3, 1.5, 2.5, 4.0) = %.3f\n", g1);
    printf("  Verwacht: 2.667\n");
    printf("  %s\n\n", (g1 >= 2.66 && g1 <= 2.67) ? "✓ Correct!" : "✗ Fout!");
    
    // Test 2
    double g2 = average(5, 10.0, 20.0, 30.0, 40.0, 50.0);
    printf("average(5, 10.0, 20.0, 30.0, 40.0, 50.0) = %.1f\n", g2);
    printf("  Verwacht: 30.0\n");
    printf("  %s\n\n", g2 == 30.0 ? "✓ Correct!" : "✗ Fout!");
    
    // Test 3
    double g3 = average(4, 2.5, 3.5, 4.5, 5.5);
    printf("average(4, 2.5, 3.5, 4.5, 5.5) = %.1f\n", g3);
    printf("  Verwacht: 4.0\n");
    printf("  %s\n\n", g3 == 4.0 ? "✓ Correct!" : "✗ Fout!");
}

void demo_logger(void) {
    printf("=== 4.4 Veilige Logger ===\n\n");
    
    printf("Functie: void my_logger(char *dest, int dest_size,\n");
    printf("                        const char *format, ...);\n\n");
    
    char log_buffer[100];
    
    // Test 1
    printf("Test 1: Simpele integer\n");
    int code = 404;
    my_logger(log_buffer, sizeof(log_buffer), "Pagina niet gevonden (Fout: %d)", code);
    printf("  my_logger(..., \"Pagina niet gevonden (Fout: %%d)\", 404)\n");
    printf("  Resultaat: %s\n", log_buffer);
    printf("  %s\n\n", strstr(log_buffer, "[LOG]:") != NULL ? "✓ Prefix aanwezig!" : "✗ Geen prefix!");
    
    // Test 2
    printf("Test 2: Meerdere argumenten\n");
    my_logger(log_buffer, sizeof(log_buffer), 
              "Gebruiker %s heeft %d berichten (Temp: %.1f°C)", 
              "Jan", 42, 23.5);
    printf("  Resultaat: %s\n", log_buffer);
    printf("  %s\n\n", strstr(log_buffer, "Jan") != NULL ? "✓ Correct!" : "✗ Fout!");
    
    // Test 3 - Buffer overflow preventie
    printf("Test 3: Buffer overflow preventie\n");
    char small_buffer[20];
    my_logger(small_buffer, sizeof(small_buffer), 
              "Dit is een zeer lang bericht dat niet in de buffer past");
    printf("  Buffer size: %d bytes\n", (int)sizeof(small_buffer));
    printf("  Resultaat: %s\n", small_buffer);
    printf("  String lengte: %d bytes\n", (int)strlen(small_buffer));
    printf("  %s\n\n", strlen(small_buffer) < sizeof(small_buffer) ? "✓ Veilig!" : "✗ Overflow!");
}

/* ============================================
 * Hoofdfunctie voor oefening 4
 * ============================================ */

void oefening4(void) {
    printf("=== Variadische functies ===\n\n");
    printf("Variadische functies kunnen een variabel aantal argumenten accepteren.\n");
    printf("We gebruiken <stdarg.h> met va_list, va_start, va_arg en va_end.\n\n");
    
    // Demo 1: Sum
    demo_sum();
    printf("Druk op ENTER om verder te gaan...\n");
    getchar();
    printf("\n");
    
    // Demo 2: Max
    demo_max();
    printf("Druk op ENTER om verder te gaan...\n");
    getchar();
    printf("\n");
    
    // Demo 3: Average
    demo_average();
    printf("Druk op ENTER om verder te gaan...\n");
    getchar();
    printf("\n");
    
    // Demo 4: Logger
    demo_logger();
}

/*
 * UITLEG: Variadische functies in C
 * ===================================
 * 
 * 1. BIBLIOTHEEK: <stdarg.h>
 *    - va_list: Type voor de argumentenlijst
 *    - va_start(ap, last): Initialiseer ap na laatste vaste parameter
 *    - va_arg(ap, type): Haal volgende argument op van gegeven type
 *    - va_end(ap): Cleanup de argumentenlijst
 * 
 * 2. FUNCTIE DECLARATIE:
 *    return_type function_name(vaste_params, ...);
 *    - Minimaal 1 vaste parameter nodig (vaak een count)
 *    - De "..." geeft variadische argumenten aan
 * 
 * 3. IMPLEMENTATIE PATTERN:
 *    int sum(int count, ...) {
 *        va_list args;           // Declareer lijst
 *        va_start(args, count);  // Initialiseer na 'count'
 *        
 *        for (int i = 0; i < count; i++) {
 *            int val = va_arg(args, int);  // Haal int op
 *            // Verwerk val...
 *        }
 *        
 *        va_end(args);  // Cleanup
 *        return result;
 *    }
 * 
 * 4. TYPE PROMOTIE:
 *    - char en short worden gepromoveerd naar int
 *    - float wordt gepromoveerd naar double
 *    - Gebruik va_arg(args, int) voor char/short
 *    - Gebruik va_arg(args, double) voor float/double
 * 
 * 5. VSNPRINTF:
 *    - int vsnprintf(char *str, size_t size, const char *fmt, va_list ap);
 *    - Printf-achtige functie die een va_list accepteert
 *    - Veilig: schrijft maximaal (size-1) karakters + '\0'
 *    - Return waarde: aantal karakters dat geschreven zou worden
 * 
 * 6. VEELVOORKOMENDE FOUTEN:
 *    - Vergeten va_end() aan te roepen (memory leak)
 *    - Verkeerd type in va_arg() (undefined behavior)
 *    - Te weinig of te veel argumenten lezen
 *    - Geen count parameter (hoe weet je wanneer te stoppen?)
 * 
 * 7. BEST PRACTICES:
 *    - Altijd een mechanisme om aantal args te weten (count of sentinel)
 *    - Documenteer duidelijk welke types verwacht worden
 *    - Gebruik va_copy() als je de lijst meerdere keren moet doorlopen
 *    - Check altijd voor edge cases (count = 0, NULL pointers)
 * 
 * 8. VOORBEELDEN IN DE STANDAARD BIBLIOTHEEK:
 *    - printf(const char *format, ...);
 *    - sprintf(char *str, const char *format, ...);
 *    - fprintf(FILE *stream, const char *format, ...);
 * 
 * 9. ALTERNATIEVEN:
 *    - Array parameters: void func(int *arr, int size);
 *    - Struct parameters: void func(struct args *a);
 *    - C++: Templates en parameter packs
 * 
 * 10. SECURITY:
 *     - Format string vulnerabilities bij printf-achtige functies
 *     - Altijd buffer sizes checken (zoals in my_logger)
 *     - Valideer count parameter om buffer overruns te voorkomen
 */
