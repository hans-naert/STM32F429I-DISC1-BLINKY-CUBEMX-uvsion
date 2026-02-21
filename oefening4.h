/*
 * Header file voor Oefening 4: Variadische functies
 */

#ifndef OEFENING4_H
#define OEFENING4_H

/**
 * @brief Voert oefening 4 uit: Variadische functies demonstratie
 */
void oefening4(void);

/**
 * @brief Berekent de som van een variabel aantal integers
 * @param count Aantal integers die volgen
 * @param ... Variabel aantal integer argumenten
 * @return Som van alle integers
 */
int sum(int count, ...);

/**
 * @brief Zoekt de grootste waarde uit een variabel aantal integers
 * @param count Aantal integers die volgen
 * @param ... Variabel aantal integer argumenten
 * @return De grootste waarde
 */
int max_of(int count, ...);

/**
 * @brief Berekent het gemiddelde van een variabel aantal doubles
 * @param count Aantal doubles die volgen
 * @param ... Variabel aantal double argumenten
 * @return Gemiddelde als double
 */
double average(int count, ...);

/**
 * @brief Veilige logger die een prefix toevoegt en buffer overflow voorkomt
 * @param dest Doelbuffer
 * @param dest_size Grootte van doelbuffer
 * @param format Format string (printf-stijl)
 * @param ... Variabel aantal argumenten voor format string
 */
void my_logger(char *dest, int dest_size, const char *format, ...);

/**
 * @brief Demonstreert de sum functie
 */
void demo_sum(void);

/**
 * @brief Demonstreert de max_of functie
 */
void demo_max(void);

/**
 * @brief Demonstreert de average functie
 */
void demo_average(void);

/**
 * @brief Demonstreert de my_logger functie
 */
void demo_logger(void);

#endif /* OEFENING4_H */
