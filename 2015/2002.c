#include<stdio.h>
#include<stdlib.h>

#define PRESENTS 33100000
#define WEIGHT_1 10
#define WEIGHT_2 11
#define MAX_VISITS 50

// The Elf with number PRESENTS/10 will deliver
// exactly PRESENTS to his first house, thus this is
// the upper bound 
#define RANGE PRESENTS/WEIGHT_1


void clear(int *houses) {
    int i;
    // Set all houses to 0
    for (i = 0; i < RANGE; i++) {
        houses[i] = 0;
    }
    return;
}

void part1(int *houses) {
    int i,j;
    // Deliver presents
    for (i = 1; i < RANGE; i++) { // Elves (Elf 1, Elf 2, ...)
        for (j = i; j < RANGE; j += i) { // Houses visited (Step by Elf number)
            houses[j] += i * WEIGHT_1; // Add presents to the house
        }
    }
    // Find the first house with more presents than the required value
    for (i = 0; i < RANGE; i++) {
        if (houses[i] >= PRESENTS) {
            printf("PART ONE - SOLUTION: %d\n", i);
            return;
        }
    }
}

void part2(int *houses) {
    int i,j;
    // Deliver presents
    for (i = 1; i < RANGE; i++) { // Elves (Elf 1, Elf 2, ...)
        for (j = i; j < MAX_VISITS * i; j += i) { // This time only visit the first 50 houses
            if (j > RANGE) { // This Elf arrived at a house outside the array, ignore it
                break;       // and proceed to the next Elf.
            }
            houses[j] += i * WEIGHT_2; // Add presents to the house
        }
    }
    // Find the first house with more presents than the required value
    for (i = 0; i < RANGE; i++) {
        if (houses[i] >= PRESENTS) {
            printf("PART TWO - SOLUTION: %d\n", i);
            return;
        }
    }
}

int main() {
    int *houses;
    // Allocate the array of RANGE houses
    houses = malloc(RANGE * sizeof(int));
    clear(houses);
    part1(houses);
    clear(houses);
    part2(houses);
    return 0;
}
