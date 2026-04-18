#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

/* * Macro de test : compare la sortie et la valeur de retour.
 * Utilise ##__VA_ARGS__ pour gérer les arguments variables.
 */
#define TEST_PRINTF(format, ...) \
    do { \
        int ret_std, ret_ft; \
        printf("\033[36m=== Test: [%s] ===\033[0m\n", format); \
        printf("std: "); \
        fflush(stdout); \
        ret_std = printf(format, ##__VA_ARGS__); \
        printf("\nft_: "); \
        fflush(stdout); \
        ret_ft = ft_printf(format, ##__VA_ARGS__); \
        printf("\n"); \
        if (ret_std == ret_ft) { \
            printf("\033[32m[OK]\033[0m Ret std: %d | Ret ft: %d\n\n", ret_std, ret_ft); \
        } else { \
            printf("\033[31m[KO]\033[0m Ret std: %d | Ret ft: %d\n\n", ret_std, ret_ft); \
        } \
    } while (0)

int main(void)
{
    /* Variables pour contourner l'analyse statique stricte de GCC */
    char *null_str = NULL;
    int min_int = -2147483648LL; /* Le cast implicite supprime le warning */

    printf("========== TESTS STRINGS & CHARS (%%c, %%s, %%%%) ==========\n");
    TEST_PRINTF("Un caractere : %c", 'a');
    TEST_PRINTF("Caractere non imprimable : %c", 0);
    TEST_PRINTF("Une chaine : %s", "Hello World");
    TEST_PRINTF("Chaine vide : %s", "");
    
    /* Utilisation de la variable pour tromper l'analyseur GCC sur le NULL */
    TEST_PRINTF("Chaine NULL : %s", null_str); 
    
    TEST_PRINTF("Pourcentage : %%");
    TEST_PRINTF("Multiples : %%%% %% %%%%");

    printf("\n========== TESTS POINTEURS (%%p) ==========\n");
    int a = 42;
    TEST_PRINTF("Pointeur basique : %p", &a);
    TEST_PRINTF("Pointeur NULL : %p", NULL);
    TEST_PRINTF("Pointeur cast (void *)0 : %p", (void *)0);

    printf("\n========== TESTS ENTIERS (%%d, %%i) ==========\n");
    TEST_PRINTF("Entier positif : %d", 42);
    TEST_PRINTF("Entier negatif : %d", -42);
    TEST_PRINTF("Zero : %d", 0);
    TEST_PRINTF("INT_MAX : %d", INT_MAX);
    TEST_PRINTF("INT_MIN : %d", INT_MIN);
    
    /* Utilisation de la variable ou directement INT_MIN pour eviter le long int */
    TEST_PRINTF("Avec %%i : %i", min_int);

    printf("\n========== TESTS UNSIGNED (%%u) ==========\n");
    TEST_PRINTF("Unsigned positif : %u", 42);
    TEST_PRINTF("Unsigned zero : %u", 0);
    TEST_PRINTF("Unsigned max : %u", UINT_MAX);
    TEST_PRINTF("Unsigned avec nombre negatif (cast) : %u", -1);

    printf("\n========== TESTS HEXADECIMAUX (%%x, %%X) ==========\n");
    TEST_PRINTF("Hexa min : %x", 42);
    TEST_PRINTF("Hexa MAJ : %X", 42);
    TEST_PRINTF("Hexa zero : %x", 0);
    TEST_PRINTF("Hexa UINT_MAX : %x", UINT_MAX);
    TEST_PRINTF("Hexa negatif min : %x", -1);
    TEST_PRINTF("Hexa negatif MAJ : %X", -1);

    printf("\n========== TESTS MIXTES & COMPLEXES ==========\n");
    TEST_PRINTF("Mixte 1 : %c, %s, %p, %d, %i, %u, %x, %X, %%", 'Z', "Test", &a, 123, -456, 789, 255, 255);
    TEST_PRINTF("Sans arguments variables");
    TEST_PRINTF("%s%s%s%s", "Un", "Deux", "Trois", "Quatre");

    return (0);
}