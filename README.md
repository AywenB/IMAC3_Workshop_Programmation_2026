# Aywen Bouyer : Rapport IMAC3 Workshop Programmation 2026

- [Aywen Bouyer : Rapport IMAC3 Workshop Programmation 2026](#aywen-bouyer--rapport-imac3-workshop-programmation-2026)
  - [Exercice 1: Ne garder que le vert](#exercice-1-ne-garder-que-le-vert)
  - [Exercice 2: Échanger les canaux (ici le rouge et le bleu)](#exercice-2-échanger-les-canaux-ici-le-rouge-et-le-bleu)
  - [Exercice 3: Noir \& Blanc](#exercice-3-noir--blanc)
  - [Exercice 4: Négatif](#exercice-4-négatif)
  - [Exercice 5: Dégradé (du noir vers le blanc)](#exercice-5-dégradé-du-noir-vers-le-blanc)
  - [Exercice 6: Miroir](#exercice-6-miroir)
  - [Exercice 7: Image bruitée](#exercice-7-image-bruitée)
  - [Exercice 8: Rotation de 90°](#exercice-8-rotation-de-90)
    - [Rotation vers la droite](#rotation-vers-la-droite)
    - [Rotation vers la gauche](#rotation-vers-la-gauche)
  - [Exercice 9: RGB split](#exercice-9-rgb-split)
  - [Exercice 10: luminosité](#exercice-10-luminosité)
    - [Éclaircir](#éclaircir)
    - [Assombrir](#assombrir)
  - [Exercice 11: Disque blanc](#exercice-11-disque-blanc)
  - [Exercice 12: Cercle](#exercice-12-cercle)
  - [Exercice 13: Animation](#exercice-13-animation)
  - [Exercice 14: Rosace](#exercice-14-rosace)
  - [Exercice 15: Mosaïque](#exercice-15-mosaïque)
  - [Exercice 16: Mosaïque miroir](#exercice-16-mosaïque-miroir)
  - [Exercice 17: Glitch](#exercice-17-glitch)
  - [Exercice 18: Tri de pixel](#exercice-18-tri-de-pixel)
    - [Tri de tous les pixels](#tri-de-tous-les-pixels)
    - [Tri des pixels par ligne](#tri-des-pixels-par-ligne)
    - [Tri des pixels de manière aléatoire](#tri-des-pixels-de-manière-aléatoire)
  - [Exercice 19: Fractale de Mandelbrot](#exercice-19-fractale-de-mandelbrot)
  - [Exercice 20: Dégradés dans l'espace de couleur Lab](#exercice-20-dégradés-dans-lespace-de-couleur-lab)
    - [Dégradé de couleur dans sRGB](#dégradé-de-couleur-dans-srgb)
    - [Dégradé de couleur dans Lab](#dégradé-de-couleur-dans-lab)
  - [Exercice 23: Vortex](#exercice-23-vortex)
  - [Exercice 24: Convolution](#exercice-24-convolution)
  - [Exercice 25: Netteté, Contours, etc.](#exercice-25-netteté-contours-etc)
    - [Emboss](#emboss)
    - [Outline](#outline)
    - [Sharpen](#sharpen)
  - [Exercice 30: Diamond Square](#exercice-30-diamond-square)


## Exercice 1: Ne garder que le vert

![](./output/keep_green_only.png)

## Exercice 2: Échanger les canaux (ici le rouge et le bleu)

![](./output/swap_canal_red_and_blue.png)

## Exercice 3: Noir & Blanc

![](./output/black_and_white.png)

## Exercice 4: Négatif

![](./output/negative.png)

## Exercice 5: Dégradé (du noir vers le blanc)

![](./output/gradient.png)

## Exercice 6: Miroir

![](./output/mirrorside.png)

## Exercice 7: Image bruitée

![](./output/noise.png)

## Exercice 8: Rotation de 90°
### Rotation vers la droite
![](./output/turning_90_degrees_right.png)
### Rotation vers la gauche
![](./output/turning_90_degrees_left.png)

## Exercice 9: RGB split

![](./output/rgb_split.png)

## Exercice 10: luminosité

### Éclaircir
![](./output/brightening.png)
### Assombrir
![](./output/darkening.png)

## Exercice 11: Disque blanc

![](./output/create_a_circle.png)

## Exercice 12: Cercle

![](./output/create_border_circle.png)

## Exercice 13: Animation

![frame 1](./output/animation/0.png)
![frame 2](./output/animation/1.png)
![frame 3](./output/animation/2.png)
![frame 4](./output/animation/3.png)
![frame 5](./output/animation/4.png)

## Exercice 14: Rosace

![](./output/rosace.png)

## Exercice 15: Mosaïque

![](./output/mosaique.png)

J'ai eu beaucoup de mal avec celui-là parce que je n'utilisais pas % et je tombais tout le temps en dehors de l'image.

## Exercice 16: Mosaïque miroir

![](./output/mosaique_mirroir.png)

Pour inverser, j'ai fait en sorte d'avoir 2 templates (1 avec le logo normal, 1 avec le logo en miroir). Lorsque le programme finissait 1 ligne du logo, il venait prendre l'autre template. Et lorsque le programme finissait une colonne du logo, il venait renverser les templates. 

## Exercice 17: Glitch

![](./output/glitch.png)


## Exercice 18: Tri de pixel

### Tri de tous les pixels
![](./output/sorting_all_pixels.png)
### Tri des pixels par ligne
![](./output/sorting_pixels_line_by_line.png)
### Tri des pixels de manière aléatoire
![](./output/sorting_pixels_randomly.png)

Pour le dernier je ne sais pas pourquoi mais le tri ne se fait qu'en bas de l'image. 

## Exercice 19: Fractale de Mandelbrot

![](./output/fractale_de_mandelbrot.png)

Changement de la formule avec : sqrt(z)*z+c

![](./output/fractale.png)

Au début j'avais oublié de mettre mes données en float, ce qui donnait un gros pâté blanc :

![](./output/fractale_de_mandelbrot_moche.png)

## Exercice 20: Dégradés dans l'espace de couleur Lab

### Dégradé de couleur dans sRGB
![](./output/gradient_between_two_colors.png)
### Dégradé de couleur dans Lab
![](./output/gradient_oklab_between_two_colors.png)

## Exercice 23: Vortex

![](./output/vortex.png)

Voici d'autres résultats marrants que j'ai obtenus :

![](./output/bricbrac.png)

J'ai juste échangé les pixels en fonction de la rotation sans avoir d'images en backup pour accueillir le rendu.

![](./output/oeil_terrifiant.png)

Ici j'ai juste mis l'effet très fort.

## Exercice 24: Convolution

![](./output/blur.png)

J'ai voulu changer la formule pour faire en sorte que en fonction de la position du pixel sa couleur impacte plus ou moins l'image finale, mais j'ai mal calculé mes divisions et ai obtenu un effet néon à la place :

![](./output/blur_2.png)
![](./output/neon.png)

## Exercice 25: Netteté, Contours, etc.

### Emboss
![](./output/embross.png)
### Outline
![](./output/outline.png)
### Sharpen
![](./output/sharpen.png)

## Exercice 30: Diamond Square
![](./output/diamond_square.png)

J'ai voulu créer un algorithme qui, qu'importe la taille de la carte, va créer l'image.
Déjà, j'ai commencé par définir les couleurs des coins.
Puis j'ai défini 2 actions différentes à répéter :
- Définir le pixel central
- Définir les pixels sur les côtés

Comme j'ai voulu tout automatiser, j'ai décidé de répéter ces actions dans 3 boucles différentes :
- Une première boucle pour dire à quel niveau de rétrécissement on en est pour l'application du diamant (ex: on a une image qu'on divise en 4 zones égales, puis chacune de ces zones est divisée en 4 zones égales etc.)
- Deux autres boucles pour parcourir les sous-divisions de l'image.

Exemple : 
Nous avons une image. Au premier tour, le programme n'a pas de sous-division et va donc appliquer les actions sur toute l'image. Au second tour, l'image est divisée en quatre : Le programme va alors parcourir les 4 carrés et appliquer les actions dans chacun de ces carrés.
Et ainsi de suite.

J'ai eu beaucoup de difficultés pour celui-là, notamment pour connaître la position des pixels en fonction du niveau de rétrécissement en cours.