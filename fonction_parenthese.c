#include "fonction_parenthese.h"
#include "fonction_catalan.h"

typedef unsigned long long (*CatalanFunction)(int);

unsigned long long n_Combinaisons = 0;

// Fonction modifiée pour compter sans afficher
void compter_parentheses_rec(char *chaine, int position, int n, int ouvrantes,
                             int fermantes) {
  if (position == 2 * n) {
    n_Combinaisons++;
    return;
  }
  if (ouvrantes < n) {
    chaine[position] = '(';
    compter_parentheses_rec(chaine, position + 1, n, ouvrantes + 1, fermantes);
  }
  if (fermantes < ouvrantes) {
    chaine[position] = ')';
    compter_parentheses_rec(chaine, position + 1, n, ouvrantes, fermantes + 1);
  }
}

// Fonction originale qui affiche les combinaisons
void afficher_parentheses_rec(char *chaine, int position, int n, int ouvrantes,
                              int fermantes) {
  if (position == 2 * n) {
    printf("%s\n", chaine);
    return;
  }
  if (ouvrantes < n) {
    chaine[position] = '(';
    afficher_parentheses_rec(chaine, position + 1, n, ouvrantes + 1, fermantes);
  }
  if (fermantes < ouvrantes) {
    chaine[position] = ')';
    afficher_parentheses_rec(chaine, position + 1, n, ouvrantes, fermantes + 1);
  }
}

void mesure_temps_parentheses(int n, CatalanFunction catalanFunc) {
  if (n <= 0) {
    printf("Le nombre doit être positif\n");
    return;
  }

  char *chaine = (char *)malloc((2 * n + 1) * sizeof(char));
  if (chaine == NULL) {
    printf("Erreur d'allocation mémoire\n");
    return;
  }
  chaine[2 * n] = '\0';

  // Mesure du temps pour le calcul du nombre de Catalan
  clock_t start_catalan, end_catalan;
  start_catalan = clock();
  unsigned long long nombreCatalan = catalanFunc(n);
  end_catalan = clock();
  double temps_catalan =
      ((double)(end_catalan - start_catalan)) / CLOCKS_PER_SEC;

  // Mesure du temps pour la génération sans affichage
  clock_t start_gen, end_gen;
  n_Combinaisons = 0;
  start_gen = clock();
  compter_parentheses_rec(chaine, 0, n, 0, 0);
  end_gen = clock();
  double temps_gen_sans_affichage =
      ((double)(end_gen - start_gen)) / CLOCKS_PER_SEC;

  // Mesure du temps pour la génération avec affichage
  clock_t start_affichage, end_affichage;
  /*  start_affichage = clock();
   afficher_parentheses_rec(chaine, 0, n, 0, 0);
   end_affichage = clock(); */
  double temps_gen_avec_affichage =
      ((double)(end_affichage - start_affichage)) / CLOCKS_PER_SEC;

  printf("\nRésultats pour n = %d :\n", n);
  printf("Nombre de Catalan calculé : %llu\n", nombreCatalan);
  printf("Nombre de combinaisons générées : %llu\n", n_Combinaisons);
  printf("Temps de calcul du nombre de Catalan : %.6f secondes\n",
         temps_catalan);
  printf("Temps de génération sans affichage : %.6f secondes\n",
         temps_gen_sans_affichage);
  /*  printf("Temps de génération avec affichage : %.6f secondes\n",
          temps_gen_avec_affichage); */
  /* l'affichage prend beaucoup de temps en méthode récursive donc je l'ai mis
   * en commentaire */

  free(chaine);
}

///// implémentation de la fonction généreration de parenthèses de manière
/// itérative
/*
typedef struct {
  char *str; // La chaîne de parenthèses
  int pos;
  int ouvrantes;
  int fermantes;
} Etat;

// Structure pour la pile
typedef struct {
  Etat *etats;
  int taille;
  int capacite;
} Pile;

// Initialiser la pile
Pile *initPile(int capacite) {
  Pile *p = (Pile *)malloc(sizeof(Pile));
  p->etats = (Etat *)malloc(capacite * sizeof(Etat));
  p->taille = 0;
  p->capacite = capacite;
  return p;
}

// Empiler un état
void empiler(Pile *p, Etat etat) {
  if (p->taille < p->capacite) {
    p->etats[p->taille++] = etat;
  }
}

// Dépiler un état
Etat depiler(Pile *p) { return p->etats[--p->taille]; }

// Copier un état
Etat copierEtat(Etat e, int n) {
  Etat nouvelle;
  nouvelle.str = (char *)malloc((2 * n + 1) * sizeof(char));
  strcpy(nouvelle.str, e.str);
  nouvelle.pos = e.pos;
  nouvelle.ouvrantes = e.ouvrantes;
  nouvelle.fermantes = e.fermantes;
  return nouvelle;
}

// Version qui compte sans afficher
unsigned long long compterParenthesesIteratif(int n) {
  unsigned long long count = 0;
  Pile *pile = initPile(4 * n);

  Etat etatInitial;
  etatInitial.str = (char *)malloc((2 * n + 1) * sizeof(char));
  etatInitial.str[0] = '\0';
  etatInitial.pos = 0;
  etatInitial.ouvrantes = 0;
  etatInitial.fermantes = 0;

  empiler(pile, etatInitial);

  while (pile->taille > 0) {
    Etat etatCourant = depiler(pile);

    if (etatCourant.pos == 2 * n) {
      count++;
      free(etatCourant.str);
      continue;
    }

    if (etatCourant.fermantes < etatCourant.ouvrantes) {
      Etat nouvelEtat = copierEtat(etatCourant, n);
      nouvelEtat.str[nouvelEtat.pos] = ')';
      nouvelEtat.str[nouvelEtat.pos + 1] = '\0';
      nouvelEtat.pos++;
      nouvelEtat.fermantes++;
      empiler(pile, nouvelEtat);
    }

    if (etatCourant.ouvrantes < n) {
      etatCourant.str[etatCourant.pos] = '(';
      etatCourant.str[etatCourant.pos + 1] = '\0';
      etatCourant.pos++;
      etatCourant.ouvrantes++;
      empiler(pile, etatCourant);
    } else {
      free(etatCourant.str);
    }
  }

  free(pile->etats);
  free(pile);
  return count;
}

// Version qui affiche
void afficherParenthesesIteratif(int n) {
  Pile *pile = initPile(4 * n);

  Etat etatInitial;
  etatInitial.str = (char *)malloc((2 * n + 1) * sizeof(char));
  etatInitial.str[0] = '\0';
  etatInitial.pos = 0;
  etatInitial.ouvrantes = 0;
  etatInitial.fermantes = 0;

  empiler(pile, etatInitial);

  while (pile->taille > 0) {
    Etat etatCourant = depiler(pile);

    if (etatCourant.pos == 2 * n) {
      printf("%s\n", etatCourant.str);
      free(etatCourant.str);
      continue;
    }

    if (etatCourant.fermantes < etatCourant.ouvrantes) {
      Etat nouvelEtat = copierEtat(etatCourant, n);
      nouvelEtat.str[nouvelEtat.pos] = ')';
      nouvelEtat.str[nouvelEtat.pos + 1] = '\0';
      nouvelEtat.pos++;
      nouvelEtat.fermantes++;
      empiler(pile, nouvelEtat);
    }

    if (etatCourant.ouvrantes < n) {
      etatCourant.str[etatCourant.pos] = '(';
      etatCourant.str[etatCourant.pos + 1] = '\0';
      etatCourant.pos++;
      etatCourant.ouvrantes++;
      empiler(pile, etatCourant);
    } else {
      free(etatCourant.str);
    }
  }

  free(pile->etats);
  free(pile);
}

void mesure_temps_parentheses(int n, CatalanFunction catalanFunc) {
  if (n <= 0) {
    printf("Le nombre doit être positif\n");
    return;
  }

  // Mesure du temps pour le calcul du nombre de Catalan
  clock_t start_catalan, end_catalan;
  start_catalan = clock();
  unsigned long long nombreCatalan = catalanFunc(n);
  end_catalan = clock();
  double temps_catalan =
      ((double)(end_catalan - start_catalan)) / CLOCKS_PER_SEC;

  // Mesure du temps pour la génération sans affichage
  clock_t start_gen, end_gen;
  start_gen = clock();
  unsigned long long nombreGenere = compterParenthesesIteratif(n);
  end_gen = clock();
  double temps_gen_sans_affichage =
      ((double)(end_gen - start_gen)) / CLOCKS_PER_SEC;

  // Mesure du temps pour la génération avec affichage
  clock_t start_affichage, end_affichage;
  start_affichage = clock();
  afficherParenthesesIteratif(n);
  end_affichage = clock();
  double temps_gen_avec_affichage =
      ((double)(end_affichage - start_affichage)) / CLOCKS_PER_SEC;

  printf("\nRésultats pour n = %d :\n", n);
  printf("Nombre de Catalan calculé : %llu\n", nombreCatalan);
  printf("Nombre de combinaisons générées : %llu\n", nombreGenere);
  printf("Temps de calcul du nombre de Catalan : %.6f secondes\n",
         temps_catalan);
  printf("Temps de génération sans affichage : %.6f secondes\n",
         temps_gen_sans_affichage);
  printf("Temps de génération avec affichage : %.10f secondes\n",
         temps_gen_avec_affichage);
}

*/