# cub3d

Exemple pour expliquer le fonctionnement du programme (Test shadowcasting)
- Shadowcasting -> changement des donnes de la map
- "Video" de lancement du jeu
- Menu du jeu (Jouer - Jouer en local ? - Options - Credit)
- Lancement du choix selectionne dans le menu

Tout ce qui suit en bas concerne le shadowcasting

## 3d visual front view

Toutes les cases de notre map font 1 de largeur, 1 longueur et 1 hauteur
La lumiere sera toujours "place" au coin inferieur gauche de la map
Les ombres prendront auront toujours un ratio de 0.5 par rapport aux cases

![Shadowcast](https://user-images.githubusercontent.com/59654989/161366776-bbd7334f-4beb-4127-8500-6eedc2a9808c.png)

## 2d upview

Visuel vu du haut de la map d'exemple

![upview](https://user-images.githubusercontent.com/59654989/161366904-b528fea2-bc7f-425f-a3bb-c81396023b60.png)

## 2d upview walls

Tout les murs commencent en etant des 1
Le soucis c'est que sur l'image de 3d visual front view
C'est qu'on remarque qu'un des murs se retrouvent avec une partie de sa face
recouverte par le mur qui se trouve en bas a gauche de lui

Par defaut avec l'angle de notre lumiere les cotes bas et gauche doivent etre lumineux
et les cotes haut et droit doivent etre complement ombree.
Mais dans ce cas precis avec le mur cache par un autre le cote bas du mur se retrouve a etre
1/4 ombree. On remplace le 1 par un 2 pour indiquer cela.

![upviewwalls](https://user-images.githubusercontent.com/59654989/161366913-3babb6cc-e52d-41a0-bab5-c519f4ea4414.png)

## 2d upview possibilites

Concernant les sols maintenant, il existe 7 etats de sol differents 

- Sol classique sans ombre
- A -> semi ombre sur la gauche
- B -> 3/4 ombre
- C -> semi ombre sur le bas
- D -> 3/8 ombre sur la gauche
- E -> 1/4 ombre
- F -> 3/8 ombre sur le bas

On les notes pas pour le moment c'est juste a titre d'exemple pour montrer les differents cas possible

![upviewpossibilites](https://user-images.githubusercontent.com/59654989/161367419-76ea6a7e-6fb7-4c1b-9b6a-72abe66bca6f.png)

## 2d upview ground

Maintenant on va modifier les valeurs des sols pour savoir quel ombrage applique dessus
La technique pour recuperer la nouvelle valeur du sol est simple a mettre en place
On va juste se placer sur notre case de sol et regarder :
- La case a gauche
- La case en bas a gauche
- La case en bas

Apres verification on donnera la valeur a notre sol tel que :
- -1 | Sol choisi
- -2 | -4
 
![image](https://user-images.githubusercontent.com/59654989/161367719-1fdddb3f-572e-4c36-a7cf-f787bf110a9f.png)

Les donnees choisis (-1 / -2 / -4) sont calques sur le fonctionnement d'attribution des droits de chmod
On peut donc avoir toutes les combinaisons possible donnant une valeur de 0 a -7

![upviewground](https://user-images.githubusercontent.com/59654989/161367816-47056c3e-d5a4-44b7-a623-bb370682466c.png)

## Implementation

Quand on enverra nos rayons avec le raycasting et que notre rayon s'arretera a un mur
On verifie de quel cote on tape le mur (haut / bas / gauche / droite)
(par defaut sur mur 1 haut et droite ombree, gauche et bas lumineux)
Ensuite on verifie si on tape un mur de valeur 1 ou 2
(valeur 2 se retrouve avec les bas ombree a 1/4 (le reste ne change pas)
On applique ensuite la texture mais en appliquant un calcul sur l'intensite de la couleur de chaque pixel concerne

#### Exemple mur unicolor BLEU
Chaque pixel du mur sur les faces clair aura une intensite de 1
On se retrouve alors avec la valeur RGB : 
- 0 * 1, 98 * 1, 255 * 1 (0, 98, 255)

![image](https://user-images.githubusercontent.com/59654989/161368079-a1b61e6e-6cbf-4a69-8cda-3ecd71c15b1b.png)

Sur les pixels de mur avec face sombre on aura une intensite de 0.5
On se retrouve alors avec la valeur RGB : 
- 0 * 0.5, 98 * 0.5, 255 * 0.5 (0, 49, 127)

![image](https://user-images.githubusercontent.com/59654989/161368181-6f99a2d8-57bf-410c-befa-3414e442bbab.png)

On voit bien que je suis exactement sur la meme couleur mais avec une intensite plus faible, qui donne donc
une couleur plus sombre.
______________________________

#### Exemple sur sol

Sur le sol c'est plus technique parce que les ombres peuvent etre dans differentes zones selon les cas
On va implementer une fonction par type de sol
Etant donne que chaque case de notre map fait du 1 pour 1
On peut choisir manuellement la taille de ses cases en pixel, donc on connait deja a l'avance le x et le y
de chaque case.
Si je suis l'exemple de la case sol ombree a moitie sur la gauche (voir UPVIEW POSSIBILITIES A)
j'applique l'intensite 0.5 aux 32 premiers pixel de chaque lignes et je laisse les autres a intensite 1

Je me retrouve avec 

![image](https://user-images.githubusercontent.com/59654989/161368378-aba5d5d5-af50-435a-92ea-9e8d9886597c.png)

Maintenant que mon rayon de raycasting c'est arrete sur un mur et que j'ai modelise la ligne de mur
je check aussi la ligne de sol traverse par le meme rayon et selon la valeur du sol j'appelle la fonction adequate
pour modeliser mes ombres correctement

_____________________________

On peut faire le changement des d'intensite pendant le raycasting ou directement pendant le shadowcasting initial
et creer des FD avec les valeurs de chaque texture mais modifie selon les cas
- Texture_A
- Texture_B
- etc ...

#### Exemple fichier texture

Le fichier de texture ressemblera a ca
chaque pixel a son code couleur R, G et B.
Donc 3 lignes par pixels.
Sur la texture d'exemple (dans l'image en bas) on est en 32x32.
Ca nous donne 32 * 32 * 3 lignes

![image](https://user-images.githubusercontent.com/59654989/161369556-1c6fcea8-4e7a-4fd9-9aae-f5318d576b37.png)
