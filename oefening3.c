/*
 * Oefening 3: The Buffer Overflow Trap
 * 
 * Dit programma demonstreert het gevaar van onvoldoende null-terminatie
 * bij het gebruik van strncpy() en toont twee oplossingsmethoden.
 */

#include <stdio.h>
#include <string.h>
#include "oefening3.h"

/**
 * @brief Demonstreert het PROBLEEM: strncpy zonder null-terminatie
 */
void demo_probleem(void) {
    printf("=== PROBLEEM: Zonder null-terminatie ===\n\n");
    
    char source[] = "SUPERGEBRUIKER";  // 14 tekens
    char dest[9];  // Geschikt voor 8 tekens plus '\0'
    
    printf("Source string: '%s' (lengte: %d)\n", source, (int)strlen(source));
    printf("Dest buffer:   %d bytes\n\n", (int)sizeof(dest));
    
    // FOUT: strncpy vult geen '\0' toe als de bron te lang is
    strncpy(dest, source, sizeof(dest) - 1);
    
    printf("Na strncpy(dest, source, %d):\n", (int)(sizeof(dest) - 1));
    printf("  dest bevat: '");
    
    // Toon byte-per-byte wat er in dest zit
    for (int i = 0; i < (int)sizeof(dest); i++) {
        if (dest[i] == '\0') {
            printf("\\0");
        } else {
            printf("%c", dest[i]);
        }
    }
    printf("'\n\n");
    
    // GEVAAR: printf("%s") leest tot een '\0' - maar die is er niet!
    printf("⚠ GEVAAR: printf(\"%%s\", dest) leest voorbij de buffer!\n");
    printf("  Dit kan leiden tot:\n");
    printf("  - Vreemde tekens\n");
    printf("  - Crashes\n");
    printf("  - Lekken van gevoelige data\n\n");
}

/**
 * @brief Demonstreert OPLOSSING A: Handmatige null-terminatie
 */
void demo_oplossing_a(void) {
    printf("=== OPLOSSING A: Handmatige afsluiting ===\n\n");
    
    char source[] = "SUPERGEBRUIKER";
    char dest[9];
    
    printf("Strategie: Expliciet een '\\0' plaatsen na strncpy\n\n");
    
    strncpy(dest, source, sizeof(dest) - 1);
    dest[sizeof(dest) - 1] = '\0';  // ✓ Handmatig afsluiten!
    
    printf("Code:\n");
    printf("  strncpy(dest, source, sizeof(dest) - 1);\n");
    printf("  dest[sizeof(dest) - 1] = '\\0';  // Expliciet afsluiten\n\n");
    
    printf("Resultaat:\n");
    printf("  Source: %s\n", source);
    printf("  Dest:   %s\n", dest);
    printf("  Dest lengte: %d bytes\n\n", (int)strlen(dest));
    
    printf("✓ Veilig: dest is correct afgesloten met '\\0'\n\n");
}

/**
 * @brief Demonstreert OPLOSSING B: Buffer vooraf initialiseren
 */
void demo_oplossing_b(void) {
    printf("=== OPLOSSING B: Buffer vooraf initialiseren ===\n\n");
    
    char source[] = "SUPERGEBRUIKER";
    char dest[9] = {0};  // ✓ Alle bytes op '\0' gezet!
    
    printf("Strategie: Buffer met nullen initialiseren\n\n");
    
    printf("Code:\n");
    printf("  char dest[9] = {0};  // Alle bytes zijn '\\0'\n");
    printf("  strncpy(dest, source, sizeof(dest) - 1);\n\n");
    
    strncpy(dest, source, sizeof(dest) - 1);
    // Laatste byte blijft '\0' omdat deze niet overschreven wordt
    
    printf("Resultaat:\n");
    printf("  Source: %s\n", source);
    printf("  Dest:   %s\n", dest);
    printf("  Dest lengte: %d bytes\n\n", (int)strlen(dest));
    
    printf("✓ Veilig: laatste byte blijft '\\0' door initialisatie\n\n");
}

/**
 * @brief Demonstreert het verschil met een korte string
 */
void demo_korte_string(void) {
    printf("=== BONUS: Korte string (past in buffer) ===\n\n");
    
    char source[] = "JAN";  // 3 tekens
    char dest_a[9] = {0};
    char dest_b[9] = {0};
    
    printf("Source string: '%s' (lengte: %d)\n", source, (int)strlen(source));
    printf("Dest buffer:   %d bytes\n\n", (int)sizeof(dest_a));
    
    // Test met strncpy
    strncpy(dest_a, source, sizeof(dest_a) - 1);
    
    printf("Na strncpy:\n");
    printf("  Dest bevat: '%s'\n", dest_a);
    printf("  ✓ strncpy vult WEL '\\0' toe als de bron korter is\n\n");
    
    // Vergelijk met strcpy (onveilig bij lange strings!)
    strcpy(dest_b, source);
    
    printf("Vergelijking met strcpy:\n");
    printf("  strcpy resultaat: '%s'\n", dest_b);
    printf("  ⚠ strcpy checkt NIET de buffergrootte!\n");
    printf("  → Gebruik altijd strncpy voor veiligheid\n\n");
}

/**
 * @brief Hoofdfunctie voor oefening 3
 */
void oefening3(void) {
    printf("=== The Buffer Overflow Trap ===\n\n");
    printf("String buffers in C zijn kwetsbaar voor overflows.\n");
    printf("Deze oefening toont het gevaar van strncpy() en de oplossingen.\n\n");
    
    printf("Press ENTER to continue...\n");
    getchar();
    printf("\n");
    
    // Toon het probleem
    demo_probleem();
    printf("Press ENTER to continue...\n");
    getchar();
    printf("\n");
    
    // Toon oplossing A
    demo_oplossing_a();
    printf("Press ENTER to continue...\n");
    getchar();
    printf("\n");
    
    // Toon oplossing B
    demo_oplossing_b();
    printf("Press ENTER to continue...\n");
    getchar();
    printf("\n");
    
    // Bonus: korte string
    demo_korte_string();
}

/*
 * BELANGRIJKE LESSEN
 * ====================
 * 
 * 1. strncpy() VULT GEEN '\0' TOE als de bron >= n karakters is!
 *    - strncpy(dest, src, n) kopieert maximaal n karakters
 *    - Als strlen(src) >= n, wordt GEEN '\0' toegevoegd
 *    - Dit kan leiden tot buffer overruns bij printf("%s", dest)
 * 
 * 2. ALTIJD EEN VAN DE VOLGENDE DOEN:
 *    A) Handmatig null-termineren:
 *       strncpy(dest, src, n);
 *       dest[n-1] = '\0';
 *    
 *    B) Buffer vooraf initialiseren:
 *       char dest[n] = {0};
 *       strncpy(dest, src, n-1);
 * 
 * 3. WAAROM sizeof(dest) - 1?
 *    - Een buffer van 9 bytes kan 8 tekens + '\0' bevatten
 *    - We kopiëren dus maximaal 8 tekens (sizeof(dest) - 1)
 *    - De laatste byte reserveren we voor '\0'
 * 
 * 4. ALTERNATIEF: strncpy_s() (C11)
 *    - strncpy_s() voegt ALTIJD een '\0' toe
 *    - Niet overal beschikbaar (platform-afhankelijk)
 *    - Handmatige methodes werken overal
 * 
 * 5. BUFFER OVERFLOW GEVOLGEN:
 *    - Undefined behavior (crashes, vreemde output)
 *    - Security risico's (data lekkage, code injection)
 *    - Moeilijk te debuggen (symptomen variëren)
 * 
 * 6. BEST PRACTICES:
 *    - Gebruik altijd strncpy() of snprintf() ipv strcpy()
 *    - Initialiseer buffers altijd: char buf[N] = {0};
 *    - Check altijd dat N > strlen(src) voor volledige kopie
 *    - Test met edge cases (lege string, maximale lengte, te lang)
 * 
 * 7. MODERNE ALTERNATIEVEN:
 *    - snprintf(): geeft lengte terug, veilig
 *    - strlcpy(): BSD-functie (niet standaard C)
 *    - std::string in C++ (automatisch geheugenbeheer)
 */
