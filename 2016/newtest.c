#include <stdio.h>
#include <stdlib.h>

typedef struct elf {
    int id;
    struct elf *next;
    struct elf **pprev;
} elf_t;

int main(void)
{
    int elf_population = 3005290;
    int i;
    // Construct linked list of elf IDs
    elf_t *elf = calloc(sizeof(*elf), elf_population), *e = elf;
    for (i = 1; i < elf_population; i++, e++) {
        e->id = i;
        e->next = e + 1;
        e->next->pprev = &e->next;
    }

    // Make it circular
    e->id = elf_population;
    e->next = elf;
    e->next->pprev = &e->next;

    e = elf;
    elf_t *a;
    for (a = elf + elf_population / 2; e != e->next; e = e->next) {
        // Who cares about presents?  Annihilate the elf across the table
        a->id = 0x1deade1f;
        a = *(a->next->pprev = a->pprev) = a->next;
        // Update elf population; optionally grant a stay of execution
        if (elf_population-- & 1) {
            a = a->next;
        }
    }

    // There can be only one
    printf("Part 2: %d\n", e->id);

    // Leave no survivors
    e->id = 0x1deade1f;
    elf_population = 0;
    free(elf);

    return 0;
}
