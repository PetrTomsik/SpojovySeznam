/**
 * @file list.c
 * @author Petr Tomsik
 * @brief Soubor s cvičnou implementací jednosměrně zřetězeného spojového seznamu.
 * @version 1.0
 * @date 2021-19-10
 *
 *
 * Program můžete zkontrolovat pomocí nástroje Valgrind následovně:
 *     gcc list.c -o list -Wall -Wextra -pedantic -ansi -g
 *     valgrind --leak-check=full ./list
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PERSON_NAME_LENGTH 64

/**
 * @brief Struktura představující jednoho člověka, u kterého sledujeme jeho jméno, věk a velikost bot.
 */
typedef struct _person {
    char name[PERSON_NAME_LENGTH];
    unsigned int age, shoesize;
} person;

/**
 * @brief Implementace spojového seznamu instancí struktury person.
 */
typedef struct _person_list_node {
    person data;
    struct _person_list_node *next;
} person_list_node;

/**
 * @brief Funkce přidá novou instanci struktury person na začátek zadaného spojového seznamu.
 *
 * @param list Spojový seznam, kam bude prvek přidán.
 * @param name Jméno nové osoby.
 * @param age Věk nové osoby.
 * @param shoesize Velikost bot nové osoby.
 * @return int 1 pokud funkce dokončí své konání v pořádku, jinak 0.
 */
int personll_add(person_list_node **list, const char *name, const unsigned int age, const unsigned int shoesize) {
    person_list_node *temp;

    if (!list || !name)    /* Tady nesmí být !*list. V mainu jej máš na NULL sám nastaven! */
        return 0;

    temp = (person_list_node *)malloc(sizeof(person_list_node));
    if (!temp)
        return 0;   /* Funkce malloc vrátila hodnotu NULL. Co to znamená? */

    strncpy(temp->data.name, name, PERSON_NAME_LENGTH);
    temp->data.age = age;
    temp->data.shoesize = shoesize;

    temp->next = *list;
    *list = temp;

    return 1;
}

/**
 * @brief Funkce slouží k vypsání spojového seznamu s prvky typu person_list_node.
 * @param list Ukazatel na spojový seznam, jehož prvky mají být vypsány.
 */
void personll_print(const person_list_node *list) {
    while (list != NULL)
    {
        printf("Jmeno: %s Vek: %d Velikost nohy: %d\n",(list)->data.name,(list)->data.age,(list)->data.shoesize);
        list = (list)->next;
    }

}

/**
 * @brief Funkce sloužící k uvolnění spojového seznamu s prvky typu person_list_node.
 * @param list Ukazatel na ukazatel na spojový seznam, který má být uvolněn.
 */
void personll_free(person_list_node **list) {  /* Proč zde předáváme ukazatel na ukazatel. */
    person_list_node *next;

    while (*list) {
        next = (*list)->next;
        free(*list);
        *list = next;
    }

    *list = NULL;
}

/**
 * @brief Hlavní přístupový bod aplikace. Obsahuje definici spojového seznamu head, jeho naplnění, vypsání a uvolnění.
 * @return int Funkce vždy vrací hodnotu EXIT_SUCCESS.
 */
int main() {
    person_list_node *head = NULL;
    /**printf("%d\n",&head);*/
    personll_add(&head, "Vlastislav Cepicka", 26, 35);
    personll_add(&head, "Robert Cepicka", 34, 47);
    personll_add(&head, "Karel Cepicka", 56, 45);
    personll_add(&head, "Branka Cepicka", 14, 39);

    personll_print(head);

    personll_free(&head); /* Zkuste si zakomentovat tento řádek a sledujte co na to řekne Valgrind. */
    return EXIT_SUCCESS;
}
