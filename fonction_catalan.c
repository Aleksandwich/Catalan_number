#include "fonction_catalan.h"
#include <string.h>

#define SAFE_FREE(p)                                                           \
  do {                                                                         \
    free(p);                                                                   \
    (p) = NULL;                                                                \
  } while (0)

ulli catalan_recursif(ulli n) {
  if (n == 0)
    return 1;
  ulli sum = 0;
  for (ulli i = 0; i < n; i++) {
    sum += catalan_recursif(i) * catalan_recursif(n - i - 1);
  }
  return sum;
}

ulli catalan_number_iterative(int n) {
  ulli catalan[n + 1];
  catalan[0] = 1;
  for (ulli i = 1; i <= n; i++) {
    catalan[i] = 0;
    for (ulli j = 0; j < i; j++) {
      catalan[i] += catalan[j] * catalan[i - j - 1];
    }
  }
  return catalan[n];
}

ulli catalan_binomial(int n) {
  ulli c = 1;
  for (int i = 0; i < n; i++) {
    c = c * 2 * (2 * i + 1);
    c = c / (i + 2);
  }
  return c;
}

ulli catalan_multiplicatif(int n) {
  if (n == 0)
    return 1;
  double res = 1.0; // Utiliser double pour plus de précision

  // Calculer (2n)!/(n!n!) en alternant multiplications et divisions
  for (int i = 0; i < n; i++) {
    res *= (2.0 * n - i); // Multiplication par les grands nombres
    res /= (i + 1);       // Division par les petits nombres
  }

  // Diviser par (n+1) à la fin
  res /= (n + 1);

  return (ulli)res;
}

unsigned long long catalan_vecteur(int n) {
  unsigned long long *vecteur = calloc(n + 1, sizeof(unsigned long long));
  vecteur[0] = 1;
  for (int i = 1; i <= n; i++) {
    unsigned long long temp = 0;
    for (int j = 0; j < i; j++) {
      temp += vecteur[j] * vecteur[i - j - 1];
    }
    vecteur[i] = temp;
  }
  unsigned long long resultat = vecteur[n];
  free(vecteur);
  return resultat;
}

Vector *vector_create(size_t size) {
  Vector *vec = malloc(sizeof(Vector));
  vec->ligne_actuelle = malloc(size * sizeof(ulli));
  vec->size = size;
  return vec;
}

void vector_free(Vector *vec) {
  free(vec->ligne_actuelle);
  free(vec);
}

Vector *catalan_suiv(Vector *prev_line, int n) {
  Vector *nouvel_ligne = vector_create(n + 1);
  nouvel_ligne->ligne_actuelle[0] = 1;
  for (int i = 1; i <= n; i++) {
    ulli c = 0;
    for (int j = 0; j < i; j++) {
      c += prev_line->ligne_actuelle[j] * prev_line->ligne_actuelle[i - j - 1];
    }
    nouvel_ligne->ligne_actuelle[i] = c;
  }
  return nouvel_ligne;
}

void print_catalan(int n) {
  Vector *line = vector_create(1);
  line->ligne_actuelle[0] = 1;
  for (int i = 0; i <= n; i++) {
    Vector *next = catalan_suiv(line, i);
    vector_free(line);
    line = next;
    printf("%llu ", line->ligne_actuelle[i]);
  }
  vector_free(line);
}