// fonction_parenthese.h
#ifndef FONCTION_PARENTHESE_H
#define FONCTION_PARENTHESE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long long (*CatalanFunction)(int);

void compter_parentheses_rec(char *chaine, int position, int n, int ouvrantes, int fermantes);
void afficher_parentheses_rec(char *chaine, int position, int n, int ouvrantes, int fermantes);
void mesure_temps_parentheses(int n, CatalanFunction catalanFunc);

#endif