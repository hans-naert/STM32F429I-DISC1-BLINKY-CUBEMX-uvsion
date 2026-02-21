/*
 * Header file voor Oefening 2: De Grote Matrix Wissel
 */

#ifndef OEFENING2_H
#define OEFENING2_H

/**
 * @brief Voert oefening 2 uit: Matrix wissel demonstratie
 */
void oefening2(void);

/**
 * @brief Wisselt twee rijen in een vaste 3x3 matrix
 * @param matrix De 3x3 matrix
 * @param r1 Index van de eerste rij
 * @param r2 Index van de tweede rij
 */
void swapMulti(int matrix[3][3], int r1, int r2);

/**
 * @brief Wisselt twee rijen in een jagged array door pointers te herschikken
 * @param jagged Array van pointers naar rijen van verschillende lengtes
 * @param metadata Array met de lengte van elke rij
 * @param r1 Index van de eerste rij
 * @param r2 Index van de tweede rij
 */
void swapJagged(int* jagged[], int metadata[], int r1, int r2);

#endif /* OEFENING2_H */
