# Création et gestion du dictionnaire

Construire un ensemble de fonctions permettant de :

- Créer un fichier dictionnaire
- Utiliser un dictionnaire existant
- Fabriquer un dictionnaire à partir d'un fichier texte
- Détruire un fichier dictionnaire
- Insérer un mot dans un dictionnaire
- Rechercher un mot dans un dictionnaire

Ces fonctions devront être construites dans le fichier appelé _gestbib.c_ et testées dans un programme appelé _main1.c_

# Recherche avancée

Construire un ensemble de fonctions permettant de :

- Proposer à l'utilisateur une liste de mots proches de celui qu'il utilise. (Levenshtein)
- Fonctions permettant de rechercher et d'afficher une liste de mots proches d'un mot fourni par l'utilisateur.
- Le seuil de proximité doit être choisi par l'utilisateur.

Ces fonctions devront être construites dans le fichier appelé _gestrech.c_ et testées dans un programme appelé _main2.c_

# Proposition de correction

Construire une liste de fonctions permettant de lire un fichier texte, et effectuant le travail suivant :

- Afficher la liste des mots du fichier n'existant pas dans le dictionnaire, ainsi que la ligne du fichier où ils sont utilisés
- Afficher la liste des mots n'existant pas dans le dictionnaire et proposer une liste de mots proches (seuil deux lettres maximum) pour chacun d'entre eux
- Construire automatiquement un fichier corrigé, en remplaçant les mots erronés par la première suggestion de la liste (seuil une lettre maximum)

Ces fonctions devront être construites dans le fichier appelé _gestorth.c_ et testées dans un programme appelé _main3.c_

# Recherche par expression régulière

Construire maintenant un ensemble de fonctions permettant de déclencher une recherche de mots dans le dictionnaire au travers d'une expression régulière. Le jeu d'expressions devra être un sous-ensemble de l'ensemble normalisé de ces expressions comme fourni en annexe.

Ces fonctions devront être construites dans le fichier appelé _gestexpr.c_ et testées dans un programme appelé _main4.c_

_BIEN EVIDEMMENT L'UTILISATION DE BIBLIOTHÈQUES DE MANIPULATION D'EXPRESSIONS RÉGULIERES EST INTERDITE, TOUT DEVANT ETRE DÉVELOPPÉ COMPLÈTEMENT._
