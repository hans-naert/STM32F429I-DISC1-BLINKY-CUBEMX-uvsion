# Modern C - Oefeningen voor STM32F429I-DISC1

Dit project bevat 9 praktische oefeningen die moderne C-concepten demonstreren op een STM32F429I-DISC1 development board met CMSIS-RTOS2.

## Inhoudsopgave
1. [XOR Swap Functie](#1-xor-swap-functie)
2. [Matrix Wissel - Multidimensioneel vs Jagged Arrays](#2-matrix-wissel---multidimensioneel-vs-jagged-arrays)
3. [Buffer Overflow Trap](#3-buffer-overflow-trap)
4. [Variadische Functies](#4-variadische-functies)
5. [Studentenbeheer Systeem](#5-studentenbeheer-systeem)
6. [Bit Manipulatie Macro](#6-bit-manipulatie-macro)
7. [Dynamische Log-Matrix](#7-dynamische-log-matrix)
8. [Robuuste Sensor-Data Parser](#8-robuuste-sensor-data-parser)
9. [Studenten Ranking & Search](#9-studenten-ranking--search)

## Hardware Setup
- **Board:** STM32F429I-DISC1
- **UART:** USART1 op 115200 baud (stdio retargeted)
- **IDE:** Keil uVision (MDK-ARM)

## Gebruik

1. Open `blinky-cubemx.uvprojx` in Keil uVision
2. Build en flash het project (Ctrl+F7, dan F8)
3. Open een serial terminal op 115200 baud
4. Kies een oefening uit het menu (1-9)

---

## 1. XOR Swap Functie

**Bestand:** [oefening1.c](oefening1.c), [oefening1.h](oefening1.h)

### Doel
Demonstratie van **call by address** (pointers) en de XOR-operator voor het wisselen van twee integer waarden zonder tijdelijke variabele.

### Kernconcepten
- **Pointers:** Call by address met `&` (address-of) en `*` (dereference)
- **XOR-eigenschappen:**
  - `A ^ A = 0`
  - `A ^ 0 = A`
  - `A ^ B ^ B = A`
- **In-place swap:** Geen extra geheugen nodig

### Code Snippet
```c
void swap(int *a, int *b) {
    *a = *a ^ *b;  // a bevat nu a XOR b
    *b = *a ^ *b;  // b wordt originele a
    *a = *a ^ *b;  // a wordt originele b
}
```

---

## 2. Matrix Wissel - Multidimensioneel vs Jagged Arrays

**Bestand:** [oefening2.c](oefening2.c), [oefening2.h](oefening2.h)

### Doel
Vergelijk twee strategieën voor het wisselen van rijen in datastructuren.

### Multidimensionele Array (3x3)
- **Structuur:** Continu geheugenblok
- **Swap methode:** Element-per-element kopiëren
- **Gebruik:** Vaste grootte, homogene data

```c
void swapMulti(int matrix[3][3], int r1, int r2) {
    for (int i = 0; i < 3; i++) {
        int temp = matrix[r1][i];
        matrix[r1][i] = matrix[r2][i];
        matrix[r2][i] = temp;
    }
}
```

### Jagged Array
- **Structuur:** Array van pointers (rijen met verschillende lengtes)
- **Swap methode:** Pointer herschikking (O(1))
- **Gebruik:** Variabele rijlengtes, efficiënte swaps

```c
void swapJagged(int* jagged[], int metadata[], int r1, int r2) {
    // Wissel pointers
    int* tempPtr = jagged[r1];
    jagged[r1] = jagged[r2];
    jagged[r2] = tempPtr;
    
    // Wissel metadata
    int tempLen = metadata[r1];
    metadata[r1] = metadata[r2];
    metadata[r2] = tempLen;
}
```

---

## 3. Buffer Overflow Trap

**Bestand:** [oefening3.c](oefening3.c), [oefening3.h](oefening3.h)

### Doel
Demonstratie van gevaren bij `strncpy()` en veilige string handling.

### Het Probleem
`strncpy()` voegt **geen null-terminator** toe als de bron te lang is:
```c
char dest[9];
strncpy(dest, "SUPERGEBRUIKER", 8);  // Geen '\0' toegevoegd!
printf("%s", dest);  // GEVAARLIJK: leest voorbij buffer
```

### Oplossing A: Handmatige Null-Terminatie
```c
strncpy(dest, source, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';  // Forceer null-terminator
```

### Oplossing B: snprintf (Aanbevolen)
```c
snprintf(dest, sizeof(dest), "%s", source);  // Altijd null-terminated
```

---

## 4. Variadische Functies

**Bestand:** [oefening4.c](oefening4.c), [oefening4.h](oefening4.h)

### Doel
Gebruik van variabel aantal argumenten met `<stdarg.h>`.

### Kernfuncties
| Functie | Beschrijving |
|---------|--------------|
| `va_list args` | Declareer argumentenlijst |
| `va_start(args, last_param)` | Initialiseer vanaf laatste vaste parameter |
| `va_arg(args, type)` | Haal volgende argument op |
| `va_end(args)` | Cleanup |

### Voorbeelden

**Som van integers:**
```c
int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}
// Gebruik: sum(3, 10, 20, 30) → 60
```

**Veilige logger met prefix:**
```c
void my_logger(char *dest, int dest_size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int written = snprintf(dest, dest_size, "[LOG]: ");
    vsnprintf(dest + written, dest_size - written, format, args);
    va_end(args);
}
```

---

## 5. Studentenbeheer Systeem

**Bestand:** [oefening5.c](oefening5.c), [oefening5.h](oefening5.h)

### Doel
Werken met structs, pointers en de `->` operator.

### Struct Definitie
```c
typedef struct {
    char naam[50];
    float cijfer;
} Student;
```

### Pointer Arithmetiek
```c
void print_studenten(Student *lijst, int aantal) {
    for (int i = 0; i < aantal; i++) {
        printf("%s: %.1f\n", (lijst + i)->naam, (lijst + i)->cijfer);
    }
}
```

### Pijl-operator vs Punt
- `(*ptr).member` ≡ `ptr->member`
- `->` is syntactic sugar voor pointer dereference + member access

---

## 6. Bit Manipulatie Macro

**Bestand:** [oefening6.c](oefening6.c), [oefening6.h](oefening6.h)

### Doel
Macro voor register-level bit manipulatie.

### Implementatie
```c
#define SET_BIT(val, pos) ((val) | (1 << (pos)))
```

### Gebruik
```c
unsigned char reg = 0x00;  // 0000 0000
reg = SET_BIT(reg, 3);     // 0000 1000 (bit 3 gezet)
```

### Werking
1. `1 << pos` → Creëer bitmask met alleen bit `pos` gezet
2. `val | mask` → OR operatie zet de bit zonder andere bits te beïnvloeden

---

## 7. Dynamische Log-Matrix

**Bestand:** [oefening7.c](oefening7.c), [oefening7.h](oefening7.h)

### Doel
Dynamische geheugenallocatie met `malloc`/`calloc` en variadische functies.

### Architectuur
```c
char **log_matrix;  // Array van pointers naar strings (jagged array)
```

### Allocatie
```c
// Hoofdarray van pointers (geïnitialiseerd naar NULL)
log_matrix = (char **)calloc(aantal_logs, sizeof(char *));

// Elke log krijgt exact genoeg geheugen
matrix[index] = (char *)malloc((len + 1) * sizeof(char));
```

### Variadische Log Functie
```c
void add_log(char **matrix, int index, const char *format, ...) {
    char temp_buffer[256];
    
    // Schrijf prefix
    int prefix_len = snprintf(temp_buffer, sizeof(temp_buffer), "[LOG]: ");
    
    // Voeg variadic content toe
    va_list args;
    va_start(args, format);
    int len = prefix_len + vsnprintf(temp_buffer + prefix_len, 
                                      sizeof(temp_buffer) - prefix_len, 
                                      format, args);
    va_end(args);
    
    // Alloceer exact genoeg geheugen
    matrix[index] = (char *)malloc((len + 1) * sizeof(char));
    snprintf(matrix[index], len + 1, "%s", temp_buffer);
}
```

### Cleanup
```c
// Eerst de rijen, dan de matrix!
for (int i = 0; i < aantal_logs; i++) {
    free(log_matrix[i]);
}
free(log_matrix);
```

---

## 8. Robuuste Sensor-Data Parser

**Bestand:** [oefening8.c](oefening8.c), [oefening8.h](oefening8.h)

### Doel
String parsing met `strtok` en `strtol` met foutafhandeling.

### Input Formaat
```
"0x1A:0xFF:invalid:0x02:0x4B:0x7FFFFFFFFFFFFFFF"
```

### Parsing Strategie
```c
char *token = strtok(data, ":");
while (token != NULL) {
    char *endptr;
    errno = 0;  // Reset voor overflow detectie
    
    long waarde = strtol(token, &endptr, 16);  // Hexadecimaal
    
    if (endptr == token) {
        printf("Negeren (geen data): %s\n", token);
    } 
    else if (errno == ERANGE) {
        printf("[OVERFLOW] Waarde te groot: %s\n", token);
    } 
    else {
        resultaten[teller++] = (int)waarde;
    }
    
    token = strtok(NULL, ":");
}
```

### Validatie Levels
1. **Geen data:** `endptr == token` → niet-numeriek
2. **Overflow:** `errno == ERANGE` → groter dan `LONG_MAX`
3. **Geldig:** Waarde binnen bereik

---

## 9. Studenten Ranking & Search

**Bestand:** [oefening9.c](oefening9.c), [oefening9.h](oefening9.h)

### Doel
Gebruik van `qsort()` en `bsearch()` met custom comparators.

### Comparator voor Cijfers (Aflopend)
```c
int compare_cijfers(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    
    if (s1->cijfer < s2->cijfer) return 1;   // Hogere cijfers eerst
    if (s1->cijfer > s2->cijfer) return -1;
    return 0;
}
```

### Comparator voor Namen (Alfabetisch)
```c
int compare_namen(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    return strcmp(s1->naam, s2->naam);
}
```

### Zoeken met bsearch
```c
// Eerst sorteren op naam
qsort(klas, n, sizeof(Student), compare_namen);

// Zoek specifieke student
char zoek_naam[] = "Charlie";
Student *gevonden = (Student *)bsearch(zoek_naam, klas, n, 
                                        sizeof(Student), compare_naam_key);
```

### Key Comparator voor bsearch
```c
int compare_naam_key(const void *key, const void *element) {
    const char *zoek_naam = (const char *)key;
    const Student *student = (const Student *)element;
    return strcmp(zoek_naam, student->naam);
}
```

---

## Best Practices

### Memory Management
- Altijd `free()` na `malloc()`/`calloc()`
- Free in omgekeerde volgorde van allocatie
- Check pointer op `NULL` na allocatie

### String Handling
- Gebruik `snprintf()` in plaats van `sprintf()`
- Forceer null-terminatie na `strncpy()`
- Vertrouw nooit op ongevalideerde input

### Function Pointers
- Type-safe declaraties met `typedef`
- Static functies voor interne helpers (voorkom linker conflicts)
- Gebruik voor dispatch tables en callbacks

### Bitwise Operations
- Altijd haakjes in macro's: `#define MACRO(x) ((x) ...)
- Test edge cases (bit 0, bit 31)
- Gebruik unsigned types voor bit manipulatie

---

## Compileren

Het project gebruikt een function pointer array voor efficiënte dispatch:

```c
typedef void (*OefeningFunc)(void);
static const OefeningFunc oefeningen[] = {
    oefening1, oefening2, oefening3, oefening4, oefening5,
    oefening6, oefening7, oefening8, oefening9
};
```

Nieuwe oefeningen toevoegen:
1. Maak `oefeningX.c` en `oefeningX.h`
2. Implementeer `void oefeningX(void)`
3. Voeg toe aan array in `main.c`
4. Update menu in `toon_menu()`

---

## Licentie

Gebaseerd op STM32CubeMX project voor STM32F429I-DISC1.
Educational purposes only.
