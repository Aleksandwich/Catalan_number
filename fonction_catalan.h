// fonction_catalan.h
#ifndef FONCTION_CATALAN_H
#define FONCTION_CATALAN_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ulli;

// Déclarations des fonctions
ulli catalan_recursif(ulli n);
ulli catalan_number_iterative(int n);
ulli catalan_binomial(int n);
ulli catalan_multiplicatif(int n);
unsigned long long catalan_vecteur(int n);
void print_catalan(int n);

typedef struct {
    ulli *ligne_actuelle;
    size_t size;
} Vector;

Vector *vector_create(size_t size);
void vector_free(Vector *vec);
Vector *catalan_next_line(Vector *prev_line, int n);

#endif