# Complexité Algorithmique : 
Dans l'exemple : utilisation de Windows avec CodeBlocks
* Complexité temporelle (combien de temps)
Evaluation réelle de complexité temporelle en C (en ms) :
``` C
#include <windows.h>
#include <stdio.h>

int main() {
    LARGE_INTEGER frequence; // fréquence du compteur haute précision
    LARGE_INTEGER debut, fin;
    double temps_ms;

    // Obtenir la fréquence
    QueryPerformanceFrequency(&frequence);

    // Prendre le temps au début
    QueryPerformanceCounter(&debut);

    // --------- La boucle à mesurer ---------
    for (int i = 0; i < 1000000; i++) {
        // Travail simulé
    }
    // ----------------------------------------

    // Prendre le temps à la fin
    QueryPerformanceCounter(&fin);

    // Calculer le temps en millisecondes
    temps_ms = (double)(fin.QuadPart - debut.QuadPart) * 1000.0 / frequence.QuadPart;

    printf("Temps de boucle : %.6f millisecondes\n", temps_ms);

    return 0;
}
```

* Complexité spaciale (combien de mémoire)
Ajouter l'option de lien -lpsapi dans Code::Blocks </br>
Ouvre ton projet dans Code::Blocks </br>
Va dans : </br>
Project → Build Options (pas Settings !) </br>
Sélectionne ton projet à gauche (pas juste "Debug" ou "Release", choisis tout en haut le projet complet) </br>
Clique sur l'onglet Linker Settings </br>
Dans "Link libraries" clique sur Add et tape : </br>
```
psapi
```
(sans le lib ni .a, juste psapi) </br>
Clique sur OK. </br>
Complexité spatiale d'un tableau statique, pile, dynamique
```C

#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "psapi.lib")

#define TAILLE_STATIQUE 1000000   // 1 million
#define TAILLE_PILE 10000         // 10 000 (attention pile limitée)
#define TAILLE_TAS 1000000        // 1 million

SIZE_T obtenirMemoireUtilisee() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    return memInfo.WorkingSetSize;
}

int main() {
    SIZE_T memAvant, memApres, memDifference;

    printf("Démarrage du programme...\n");

    memAvant = obtenirMemoireUtilisee();
    printf("Mémoire avant toute action : %zu Ko\n\n", memAvant / 1024);

    // 1. Tableau statique LOCAL à main()
    static int tableauStatique[TAILLE_STATIQUE];

    // IMPORTANT : même si le tableau statique est réservé au lancement,
    // la mémoire physique réelle n'est pas allouée tant qu'on ne lit/écrit pas dedans.
    // => On initialise explicitement pour forcer son allocation réelle en RAM
    for (int i = 0; i < TAILLE_STATIQUE; i++) {
        tableauStatique[i] = i;
    }

    memApres = obtenirMemoireUtilisee();
    memDifference = memApres - memAvant;
    printf("Après initialisation du tableau statique :\n");
    printf("Mémoire utilisée +%zu Ko\n\n", memDifference / 1024);

    // 2. Tableau sur la pile
    int tableauPile[TAILLE_PILE];

    for (int i = 0; i < TAILLE_PILE; i++) {
        tableauPile[i] = i;
    }

    memAvant = memApres;
    memApres = obtenirMemoireUtilisee();
    memDifference = memApres - memAvant;
    printf("Après initialisation du tableau pile :\n");
    printf("Mémoire utilisée +%zu Ko\n\n", memDifference / 1024);

    // 3. Tableau sur le tas
    int* tableauTas = (int*)malloc(TAILLE_TAS * sizeof(int));
    if (tableauTas == NULL) {
        printf("Erreur d'allocation du tas !\n");
        return 1;
    }

    // Même chose ici : initialiser pour forcer la RAM physique
    for (int i = 0; i < TAILLE_TAS; i++) {
        tableauTas[i] = i;
    }

    memAvant = memApres;
    memApres = obtenirMemoireUtilisee();
    memDifference = memApres - memAvant;
    printf("Après initialisation du tableau tas :\n");
    printf("Mémoire utilisée +%zu Ko\n\n", memDifference / 1024);

    // Libérer la mémoire du tas
    free(tableauTas);

    return 0;
}
```
Example 2
```C
#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "psapi.lib")

SIZE_T obtenirMemoireUtilisee() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    return memInfo.WorkingSetSize;
}

SIZE_T obtenirPicMemoire() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    return memInfo.PeakWorkingSetSize; // Mémoire maximale utilisée pendant l'exécution
}

int main() {
    SIZE_T memAvant, memApres, memDifference, memPic;

    // Avant allocation
    memAvant = obtenirMemoireUtilisee();
    printf("Mémoire avant allocation : %zu Ko\n", memAvant / 1024);

    int *grandTableau = (int*)malloc(1000000 * sizeof(int));

    if (grandTableau == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return 1;
    }

    // Initialiser pour forcer l'allocation réelle
    for (int i = 0; i < 1000000; i++) {
        grandTableau[i] = i;
    }

    // Après allocation
    memApres = obtenirMemoireUtilisee();
    printf("Mémoire après allocation et initialisation : %zu Ko\n", memApres / 1024);

    // Calcul de la différence de mémoire
    memDifference = memApres - memAvant;
    printf("Mémoire utilisée par l'allocation : %zu Ko\n", memDifference / 1024);

    // Vérification du pic mémoire utilisé
    memPic = obtenirPicMemoire();
    printf("Pic de mémoire utilisée pendant l'exécution : %zu Ko\n", memPic / 1024);

    // Libérer la mémoire
    free(grandTableau);

    return 0;
}
```

* Exactitude (est ce que l'algorithme donne toujours des resultats exacts -> série de test)

La somme avec overflow : 
```
#include <stdio.h>
#include <limits.h> // Pour les limites des types de données

// Fonction pour additionner deux entiers signés
int somme_entier(int a, int b) {
    // Vérifier si la somme dépasse la capacité maximale (overflow)
    if ((b > 0) && (a > INT_MAX - b)) {
        printf("Overflow détecté pour les entiers signés !\n");    }
    if ((b < 0) && (a < INT_MIN - b)) {
        printf("Overflow détecté pour les entiers signés !\n");
    }
    return a + b;
}

// Fonction pour additionner deux entiers non signés
unsigned int somme_entier_non_signe(unsigned int a, unsigned int b) {
    // Vérifier si la somme dépasse la capacité maximale pour les entiers non signés
    if (a > UINT_MAX - b) {
        printf("Overflow détecté pour les entiers non signés !\n");

    }
    return a + b;
}

int main() {
    // Séries de tests pour les entiers signés (avec et sans overflow)
    int a1 = 1000, b1 = 2000; // Sans overflow
    int a2 = INT_MAX - 1, b2 = 2; // Avec overflow (INT_MAX)
    int a3 = -1000, b3 = -2000; // Sans overflow
    int a4 = INT_MIN + 1, b4 = -2; // Avec overflow (INT_MIN)

    printf("Test 1 (Sans overflow) : %d + %d = %d\n", a1, b1, somme_entier(a1, b1));
    printf("Test 2 (Avec overflow) : %d + %d = %d\n", a2, b2, somme_entier(a2, b2));
    printf("Test 3 (Sans overflow) : %d + %d = %d\n", a3, b3, somme_entier(a3, b3));
    printf("Test 4 (Avec overflow) : %d + %d = %d\n", a4, b4, somme_entier(a4, b4));

    // Séries de tests pour les entiers non signés (avec et sans overflow)
    unsigned int c1 = 1000, d1 = 2000; // Sans overflow
    unsigned int c2 = UINT_MAX - 1, d2 = 2; // Avec overflow (UINT_MAX)
    unsigned int c3 = 3000, d3 = 4000; // Sans overflow
    unsigned int c4 = UINT_MAX - 1, d4 = 3; // Maintenant, avec overflow (UINT_MAX)

    printf("Test 5 (Sans overflow) : %u + %u = %u\n", c1, d1, somme_entier_non_signe(c1, d1));
    printf("Test 6 (Avec overflow) : %u + %u = %u\n", c2, d2, somme_entier_non_signe(c2, d2));
    printf("Test 7 (Sans overflow) : %u + %u = %u\n", c3, d3, somme_entier_non_signe(c3, d3));
    printf("Test 8 (Avec overflow) : %u + %u = %u\n", c4, d4, somme_entier_non_signe(c4, d4));

    return 0;
}
```
Essayer aussi pour l'incrementation
Flottant avec overflow : 
```
#include <stdio.h>
#include <math.h>

int main() {
    float x;

    // Demander la valeur de x à l'utilisateur
    printf("Entrez une valeur pour x : ");
    scanf("%f", &x);

    // Vérifier si x est égal à 0.000007
    if (x == 0.000007) {  // Tolérance d'égalité pour float
        printf("OK\n");
    } else {
        printf("NON OK\n");
    }

    return 0;
}
```
Solution : gérer avec if ou bien utiliser du calcul symbolique

* Déterministe ou probabiliste + Optimisation algorithmique

IL FAUT GERER AUSSI LES TESTS ET SURTOUT DES METHODES DE CHOIX DE TEST) </br>
TESTER DES CAS POSSIBLE </br>
TESTER DES CAS IMPOSSIBLE </br>
TESTER DES CAS AUX EXTREMITES </br>
TESTER DES CAS CRITIQUE :  EXAMPLE POUR LE CAS DE NOMBRE PREMIER , C'EST MIEUX D'UTILISER LES NOMBRES DE CARMICHAEL ( DES NOMBRES PSEUDO-REMIER QUI SONT COMPOSITE CAD NON PREMIER MAIS QUI SONT TRES DIFFICLE A TESTER PAR DES ALGORITHMES) </br>

(déterministe : la sortie c'est toujours vrai, en executant deux fois les mêmes input -> output ne change pas) </br>
Algorithme deterministe (crible d'erastothène classique)

```c
#include <stdio.h>
#include <math.h>

// Fonction déterministe pour tester la primalité
int isPrime(int n) {
    if (n <= 1) return 0;     // pas premier
    if (n <= 3) return 1;     // 2 et 3 sont premiers

    if (n % 2 == 0 || n % 3 == 0) return 0;

    int sqrt_n = (int)sqrt((double)n);

    // On teste maintenant tous les i impairs de 5 à sqrt(n)
    for (int i = 5; i <= sqrt_n; i += 2) {
        if (n % i == 0)
            return 0;  // n divisible par i
    }

    return 1;  // n est premier
}

int main() {
    // Liste des nombres de Carmichael
    int carmichaelNumbers[] = {561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041};
    int nb = sizeof(carmichaelNumbers) / sizeof(carmichaelNumbers[0]);

    printf("Test de primalité des nombres de Carmichael (test déterministe) :\n");

    for (int i = 0; i < nb; i++) {
        int n = carmichaelNumbers[i];
        printf("%d: ", n);
        if (isPrime(n)) {
            printf("Premier\n");
        } else {
            printf("Composite\n");
        }
    }

    return 0;
}
```
Tous les cas sont testés de manière certaine </br> </br>

Algorithme deterministe (crible d'erastothène amélioré)
```
#include <stdio.h>
#include <math.h>

// Fonction déterministe pour tester la primalité
int isPrime(int n) {
    if (n <= 1) return 0; // Pas premier
    if (n <= 3) return 1; // 2 et 3 sont premiers

    if (n % 2 == 0 || n % 3 == 0) return 0;

    int sqrt_n = (int)sqrt((double)n);

    for (int i = 5; i <= sqrt_n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0; // n est divisible
    }

    return 1; // n est premier
}

int main() {
    // Liste des nombres de Carmichael
    int carmichaelNumbers[] = {561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041};
    int nb = sizeof(carmichaelNumbers) / sizeof(carmichaelNumbers[0]);

    printf("Test de primalité des nombres de Carmichael (test déterministe) :\n");

    for (int i = 0; i < nb; i++) {
        int n = carmichaelNumbers[i];
        printf("%d: ", n);
        if (isPrime(n)) {
            printf("Premier\n");
        } else {
            printf("Composite\n");
        }
    }

    return 0;
}
```


probabiliste : 

la sortie est un approximatif càd que parfois il donne des resultats fois ou des faux positifs <br>
(faux positif càd il pense que c'est vrai mais c'est faux) </br>
Parfois même non consistant : en executant deux fois les mêmes input -> output change un peu et parfois beaucoup, output probable) </br>

Algorithme non deterministe (Fermat)
```c
#include <stdio.h>

// Fonction pour effectuer l'exponentiation modulaire : calcule (base^exposant) % modulo
long long calculer_puissance_modulaire(long long base_var, unsigned int exposant, long long modulo) {
    long long resultat = 1;
    base_var %= modulo;
    while (exposant > 0) {
        if (exposant & 1)
            resultat = (resultat * base_var) % modulo;
        exposant >>= 1;
        base_var = (base_var * base_var) % modulo;
    }
    return resultat;
}

// Test de Fermat pour vérifier si n est probablement premier avec la base 2
int test_de_fermat(long long n) {
    if (n <= 1)
        return 0; // n n'est pas premier
    long long baseFixe = 2;
    if (calculer_puissance_modulaire(baseFixe, n - 1, n) != 1)
        return 0; // n est composé
    return 1;    // n est probablement premier
}

int main() {
    // Liste des nombres de Carmichael connus
    long long nombresDeCarmichael[] = {
        561, 1105, 1729, 2465, 2821,
        6601, 8911, 10585, 15841,
        29341, 41041
    };
    int nombreDeTests = sizeof(nombresDeCarmichael) / sizeof(nombresDeCarmichael[0]);

    printf("Test de Fermat avec la base 2 sur les nombres de Carmichael :\n");
    for (int i = 0; i < nombreDeTests; i++) {
        long long n = nombresDeCarmichael[i];
        printf("%lld : ", n);
        if (test_de_fermat(n))
            printf("Probablement premier (faux positif possible)\n");
        else
            printf("Composite (résultat correct)\n");
    }

    return 0;
}
```
OPTIMISATION PAR CHANGEMENT ALGORITHME (MILLER RABIN) </br>
MILLER RABIN ALGORITHME +  BASE 2 DANS L'ALGORITHME SEULEMENT </br>
```
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Fonction utilitaire pour faire l'exponentiation modulaire
int puissance(int x, unsigned int y, int p)
{
    int res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

// Fonction de test de Miller (base 2 fixée)
int testMiller(int d, int n)
{
    int a = 2;  // Base fixe 2
    //  int a = 2 + rand() % (n - 4);
    int x = puissance(a, d, n);

    if (x == 1 || x == n - 1)
        return 1;

    while (d != n - 1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)
            return 0;
        if (x == n - 1)
            return 1;
    }

    return 0;
}

// Fonction principale pour tester la primalité
int estPremier(int n, int k)
{
    if (n <= 1 || n == 4)
        return 0;
    if (n <= 3)
        return 1;

    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    for (int i = 0; i < k; i++)
        if (!testMiller(d, n))
            return 0;

    return 1;
}

int main()
{
    int k = 4;  // Nombre d'itérations

    int nombresCarmichael[] = {561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041};
    int n, i;
    int nbr = sizeof(nombresCarmichael) / sizeof(nombresCarmichael[0]);
    printf("Test des nombres de Carmichael (faux positifs) :\n");
    for (i = 0; i < nbr; i++)
    {
        n = nombresCarmichael[i];
        printf("%d: ", n);
        if (estPremier(n, k))
            printf("Probablement Premier (Faux Positif)\n");
        else
            printf("Composite (Correct)\n");
    }

    return 0;
}
```

L'algorithme probabiliste est une sorte de triche de l'algorithme deterministe.</br>
Les algorithme des IA sont des algorithmes probabilistes et parfois inconsistant </br>

AMELIORATION DE LA TRICHE : </br>
UTILISER PLUSIEURS BASES POUR L'ALGORITHME </br>
AUGMENTER LE NOMBRE D'ITERATION k </br>
cas 1 : 
```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Fonction utilitaire pour faire l'exponentiation modulaire
int puissance(int x, unsigned int y, int p)
{
    int res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

// Fonction de test de Miller (base 2 fixée)
int testMiller(int d, int n)
{
    //int a = 2;  // Base fixe 2
    int a = 2 + rand() % (n - 4);
    int x = puissance(a, d, n);

    if (x == 1 || x == n - 1)
        return 1;

    while (d != n - 1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)
            return 0;
        if (x == n - 1)
            return 1;
    }

    return 0;
}

// Fonction principale pour tester la primalité
int estPremier(int n, int k)
{
    if (n <= 1 || n == 4)
        return 0;
    if (n <= 3)
        return 1;

    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    for (int i = 0; i < k; i++)
        if (!testMiller(d, n))
            return 0;

    return 1;
}

int main()
{
    int k = 4;  // Nombre d'itérations

    int nombresCarmichael[] = {561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041};
    int n, i;
    int nbr = sizeof(nombresCarmichael) / sizeof(nombresCarmichael[0]);
    printf("Test des nombres de Carmichael (faux positifs) :\n");
    for (i = 0; i < nbr; i++)
    {
        n = nombresCarmichael[i];
        printf("%d: ", n);
        if (estPremier(n, k))
            printf("Probablement Premier (Faux Positif)\n");
        else
            printf("Composite (Correct)\n");
    }

    return 0;
}
```
cas 2 :
```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Fonction utilitaire pour faire l'exponentiation modulaire
int puissance(int x, unsigned int y, int p)
{
    int res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

// Fonction de test de Miller (base 2 fixée)
int testMiller(int d, int n)
{
    //int a = 2;  // Base fixe 2
    int a = 2 + rand() % (n - 4);
    int x = puissance(a, d, n);

    if (x == 1 || x == n - 1)
        return 1;

    while (d != n - 1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)
            return 0;
        if (x == n - 1)
            return 1;
    }

    return 0;
}

// Fonction principale pour tester la primalité
int estPremier(int n, int k)
{
    if (n <= 1 || n == 4)
        return 0;
    if (n <= 3)
        return 1;

    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    for (int i = 0; i < k; i++)
        if (!testMiller(d, n))
            return 0;

    return 1;
}

int main()
{
    int k = 10;  // Nombre d'itérations

    int nombresCarmichael[] = {561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041};
    int n, i;
    int nbr = sizeof(nombresCarmichael) / sizeof(nombresCarmichael[0]);
    printf("Test des nombres de Carmichael (faux positifs) :\n");
    for (i = 0; i < nbr; i++)
    {
        n = nombresCarmichael[i];
        printf("%d: ", n);
        if (estPremier(n, k))
            printf("Probablement Premier (Faux Positif)\n");
        else
            printf("Composite (Correct)\n");
    }

    return 0;
}
```
RQ : Essayer aussi de voir la commande diff et patch pour voir la difference entre les deux codes ??

* Ecriture (sous forme schématique ou organigrammme, sous forme pseudo-code, sous forme de langage informatique)
 </br> 
Ref : Un homme dit a son amis, je peux faire de calcul mental rapidement. </br>
Son amis réponds, calculer 12*15 </br>
L'homme reponds, c'est 124 </br>
Son amis dit, mais c'est faux </br>
L'homme répond, peut-être mais c'est rapide </br>
</br>


L'algorithme est une manière de communiquer avec des ordinateurs classique et peut être en type : impératif ou déclaratif 
L'algorithme classique est écrit sous forme d'étape par étape (impératif) </br>
Exemple : "taper etape par etape comment avoir un pizza " avec chatgpt

* Impératif : (déscription des étapes à faire : variable + fonction comme avec l'intéraction avec le clavier, les souris, les hardwares et certains software ... )

1-Ingrédients pour la pâte : </br>
250 g de farine </br>
1 sachet de levure boulangère </br>
150 ml d'eau tiède </br>
1 cuillère d'huile d'olive </br>
1 pincée de sel </br>
1 sauce tomate </br>
1 Fromage rapé qui peut être mozzarella, emmental </br>
1 ingredients composé de jambon, champigons, légumes, pepperoni </br>

2- Préparer la pâte : </br>
Mélanger farine + levure + sel </br>
Ajouter eau tiède + huile </br>
Pétrir 5–10 minutes </br>
Laisser reposer 1 heure (que ça gonfle) </br>

3- Préparer les garnitures : </br>
Sauce tomate </br>
Fromage râpé (mozzarella, emmental…) </br>
Ingrédients : jambon, champignons, légumes, pepperoni </br>

3- Assembler : </br>
Étaler la pâte au rouleau </br>
Étaler la sauce tomate </br>
Ajouter fromage + autres ingrédients </br>

4- Cuire au four :
Préchauffer le four à 220°C </br>
Cuire la pizza 10–15 minutes (jusqu’à ce qu’elle soit dorée) </br>

5-Sortir du four et manger ! </br>

</br>
Etape 1 : déclaration de variable </br>
Etape 2 - Etape 5 : liste des fonctions </br>
</br>
RQ : </br>
Les ordres sont trés importantes </br>
Les instructions peuvent être des déclarations, des groupes des déclarations de type different ou structure, des groupes de déclaration de même type ou tableau, des appels et/ou déclaration de fonction, les ennumerations, des directifs de préprocesseurs
</br>

* Déclaratif : (déclarer des ordres : requête ou interrogation comme les intéractions avec bases des données )
 Si tu veux commander une pizza : </br>
1-Appeler une pizzeria (par téléphone) ---> SGBDR </br>
2-Utiliser une application (UberEats, Deliveroo, JustEat, etc.) --> Application pour faire de la requête </br>
3-Aller directement dans une pizzeria --> aller dans menu requête SQL pour taper l'interrogation </br>
4-Choisir ta pizza préférée : --> Tapez l'interrogation </br>
Margherita, Pepperoni, 4 Fromages, Végétarienne, etc. </br>
5-Passer la commande : --> lancer la requête </br>
6-Donner ton adresse (si livraison) --> donner les conditions et paramètre de requête WHERE et HAVING </br>
7-Payer (par carte, espèces ou application)   --> donner les conditions et paramètre de requête WHERE et HAVING </br>
8-Attendre la livraison --> attendre le traitement de SGBDR (pas besoin de plusieurs minutes si c'est une requête SQL ) </br>
(environ 20–45 minutes selon l'endroit) </br>
9-Recevoir et déguster ta pizza ! --> obtenir le resultat de la requête sous forme de table </br>

</br> </br>
Algorithme est changement d'etat : etat debut vers etat fin en passant par des etats intermédiaires (c'est une manière de penser pour facilité la resolution de problème avec des algorithmes) <>


 
# Fonction  coût 
N peut-être la taille d'un tableau ou le nombre d'appel de fonction
* Example 1
``` C
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main()
{
        unsigned int cout = 0;

        printf("bonjour les amis \n");
        cout++;

        printf("cout : %u \n", cout);

}
```
La question qui se pose est : "combien de fois bonjour les amis s'affiche" </br>
La réponse est une fois : C(N) = 1

* Example 2
``` C
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main()
{
        unsigned int cout = 0;
        printf("bonjour les amis\n");
        cout++;
        printf("bonjour les amis\n");
        cout++;

        printf("cout : %u \n", cout);
}
```
La question qui se pose est : "combien de fois bonjour les amis s'affiche" </br>
La réponse est une fois : C(N) = 2

* Example 3
``` C
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main()
{
    unsigned int cout = 0;
    for (int i = 0; i < N; i++){
        printf("%d ) le nombre de cout \n", (i+1));
        cout++;
    }

    printf("cout : %u \n", cout);
    return 0;
}
```
La question qui se pose est : "combien de fois bonjour les amis s'affiche" </br>
La réponse est une fois : C(N) = N-0+1 = N+1  </br>
</br>
</br>
Formule général : </br>
c(N) = (fin-deb+1)/pas </br>
deb = 0 </br>
fin = N </br>
pas = 1 car i++ </br>
* Example 4
``` C
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main()
{
    unsigned int cout = 0;
    for (int i = 0; i < N; i+=2){
        printf("%d) le nombre de cout \n", (i+1));
    }
    return 0;
}
```
c(N) = (fin-deb+1)/pas </br>
deb = 0 </br>
fin = N </br>
pas = 2 car i++ </br>
C(N) = (N+1)/2
* Example 5
``` C
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main()
{
    for (int i = 1; i <= N; i*=2){
        printf("%d) le nombre de cout\n", (i+1));
    }
    return 0;
}
```
si N = 1 : répetition une fois, i valide = 1 </br>
Si N = 2 : répetition 2 fois, i valide = 1, 2 </br>
Si N = 3 : répetition 2 fois, i valide = 1, 2</br>
Si N = 4 : répetition 3 fois, i valide = 1, 2, 4 </br>
Si N = 5 : répetition 3 fois, i valide = 1, 2, 4 </br>
Si N = 6 : répetition 3 fois, i valide = 1, 2, 4 </br>
Si N = 7 : répetition 3 fois, i valide = 1, 2, 4 </br>
Si N = 8 : répetition 4 fois, i valide = 1, 2, 4, 8 </br>

Donc si N = 2^k   , répetion (k+1)-fois

donc C(N) = k+1 or N = 2^k donc k = log2(N) + 1 = (log(N)/log(2))+1 = (ln(N)/ln(2))+1

```
* Example 6


# Notation de Landeau


Vision complexité selon la base :
si binaire ou base dix


La notation de landeau est un critère de performance issue d'une approximation de la fonction coût quand N tends vers infini </br>
Pourquoi infini? </br>
Pour tester si une lampe est performant, il est possible d'imaginer que si la lampe est allumée plusieurs fois, comment est l'état de la lampe?
Mathématiquement parlant : si la lampe est allumée infinie de fois comment le système réagit 

# Complexité temporelle

L'algorithme se repète combien de fois
``` C
// Complexité logarithmique : O(log n)
void logarithmique(int n) {
    while (n > 1) {
        n = n / 2;
    }
}
```
