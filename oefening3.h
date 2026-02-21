/*
 * Header file voor Oefening 3: The Buffer Overflow Trap
 */

#ifndef OEFENING3_H
#define OEFENING3_H

/**
 * @brief Voert oefening 3 uit: Buffer Overflow Trap demonstratie
 */
void oefening3(void);

/**
 * @brief Demonstreert het probleem met strncpy zonder null-terminatie
 */
void demo_probleem(void);

/**
 * @brief Demonstreert oplossing A: handmatige null-terminatie
 */
void demo_oplossing_a(void);

/**
 * @brief Demonstreert oplossing B: buffer vooraf initialiseren
 */
void demo_oplossing_b(void);

/**
 * @brief Demonstreert het gedrag met een korte string
 */
void demo_korte_string(void);

#endif /* OEFENING3_H */
