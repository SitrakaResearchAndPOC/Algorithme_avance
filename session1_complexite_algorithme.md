# Algorithme 
* Complexité temporelle (combien de temps)
* Complexité spaciale (combien de mémoire)
* Exactitude (est ce que l'algorithme donne toujours des resultats exacts -> série de test)
* Déterministe ou probabiliste
(déterministe : la sortie c'est toujours vrai, en executant deux fois les mêmes input -> output ne change pas) </br>
(probabiliste : la sortie est un approximatif, en executant deux fois les mêmes input -> output change un peu, output probable) </br>
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
2- Préparer la pâte : </br>
Mélanger farine + levure + sel </br>
Ajouter eau tiède + huile </br>
Pétrir 5–10 minutes </br>
Laisser reposer 1 heure (que ça gonfle) </br>
3- Préparer les garnitures : </br>
Sauce tomate </br>
Fromage râpé (mozzarella, emmental…) </br>
Ingrédients au choix : jambon, champignons, légumes, pepperoni, etc. </br>
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
Les instructions peuvent être des déclarations, des groupes des déclarations de type different ou structure, des groupes de déclaration de même type ou tableau, des appels et/ou déclaration de fonction, des directifs de préprocesseurs
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


* déclaratif : 
 
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
