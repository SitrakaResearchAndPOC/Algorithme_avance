# Algorithme 
* Complexité temporelle (combien de temps)
* Complexité spaciale (combien de mémoire)
* Exactitude (est ce que l'algorithme donne toujours des resultats exacts -> série de test)
* Déterministe ou probabiliste
(déterministe : la sortie c'est toujours vrai, en executant deux fois les mêmes input -> output ne change pas) </br>
(probabiliste : la sortie est un approximatif, en executant deux fois les mêmes input -> output change un peu, output probable) </br>
* Ecriture (sous forme schématique ou organigrammme, sous forme pseudo-code, sous forme de langage informatique)

# Fonction  coût 
``` C
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main()
{
        printf("bonjour les amis");

}
```
La question qui se pose est : "combien de fois bonjour les amis s'affiche" </n>
La réponse est une fois : C(n) = 1

``` C
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main()
{
        printf("bonjour les amis");
        printf("bonjour les amis");

}
```
La question qui se pose est : "combien de fois bonjour les amis s'affiche" </n>
La réponse est une fois : C(n) = 2


``` C
#include <stdio.h>
#include <stdlib.h>

#define N 100

int main()
{
    for (int i = 0; i < N; i++){
        printf("le nombre de cout");
    }
    return 0;
}
```


# Notation de Landeau


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
