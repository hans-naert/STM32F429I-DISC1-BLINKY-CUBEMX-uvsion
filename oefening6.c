#include <stdio.h>
#include "oefening6.h"

// 1. DE SET_BIT MACRO
// Gebruik de bitwise OR (|) en de left-shift (<<) operator.
#define SET_BIT(val, pos) ((val) | (1 << (pos)))

void oefening6(void) {
    unsigned char register_waarde = 0x00; // Binair: 0000 0000

    // Test: Bit manipulatie
    // We zetten de 3e bit aan (pos 3). 0000 0000 -> 0000 1000 (decimaal 8)
    register_waarde = SET_BIT(register_waarde, 3);
    printf("Waarde na set_bit op positie 3: %d\n", register_waarde);
}
