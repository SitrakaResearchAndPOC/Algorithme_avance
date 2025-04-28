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

L'algorithme classique est écrit sous forme d'étape par étape !! </br>


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
        
        printf("bonjour les amis\n");
        printf("bonjour les amis\n");

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
    for (int i = 0; i < N; i++){
        printf("le nombre de cout");
    }
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
    for (int i = 0; i < N; i+=2){
        printf("le nombre de cout");
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
        printf("le nombre de cout");
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
