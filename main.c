#include "fonction_catalan.h"
#include "fonction_parenthese.h"

int main() {
  int n, choix;

  printf("Entrez le nombre de paires de parenthèses à générer : ");
  scanf("%d", &n);

  printf("Choisissez une méthode pour calculer les nombres de Catalan :\n");
  printf("1. Méthode récursive\n");
  printf("2. Méthode itérative\n");
  printf("3. Méthode binomial\n");
  printf("4. Méthode avec vecteur\n");
  printf("5. Méthode multiplicatif\n");
  printf("->  ");
  scanf("%d", &choix);

  CatalanFunction catalanFunc = NULL;

  switch (choix) {
  case 1:
    catalanFunc = catalan_recursif;
    break;
  case 2:
    catalanFunc = catalan_number_iterative;
    break;
  case 3:
    catalanFunc = catalan_binomial;
    break;
  case 4:
    catalanFunc = catalan_vecteur;
    break;
  case 5:
    catalanFunc = catalan_multiplicatif;
    break;
  default:
    printf("Choix invalide\n");
    return 1;
  }

  mesure_temps_parentheses(n, catalanFunc);

  return 0;
}