# Shell Simple

## Description

Ce projet est une implémentation simple d'un interpréteur de ligne de commande UNIX écrit en C. Le shell lit les lignes depuis l'entrée standard (mode interactif) ou depuis un fichier/tube (mode non interactif), puis analyse et exécute les commandes. Il imite le comportement de base du shell Bourne (`sh`).

**Fonctionnalités implémentées (Shell Simple 0.1 & 0.2) :**

* Affiche une invite (`#cisfun$ `) et attend l'entrée de l'utilisateur en mode interactif.
* Exécute **une commande par ligne** avec des arguments donnés (pas de point-virgule `;`, pas de redirection ou de tubes à ce stade).
* Prend en charge les arguments en ligne de commande : l'utilisateur peut saisir des commandes avec des options ou des fichiers, ex : `/bin/ls -l /home`.
* Exécute les commandes via le **chemin absolu uniquement**. (Le shell ne recherche **pas encore** dans le PATH. Il faut fournir le chemin complet).
* Gère les erreurs proprement : si une commande n'est pas trouvée ou ne peut pas être exécutée, un message d'erreur est affiché dans le même format que `/bin/sh`.
* Gère la fin de fichier (Ctrl+D) : quitte proprement le shell en cas de EOF (un retour à la ligne est affiché en mode interactif).
* Fonctionne en **mode non interactif** : si des commandes sont redirigées vers le shell, elles sont exécutées ligne par ligne et le shell quitte ensuite.

**Limitations :**

* Aucune commande interne n'est encore gérée (ex : `exit`, `cd`, `env` ne sont pas encore interprétées par le shell lui-même).
* Pas d'historique de commande, d'édition de ligne, ou de caractères spéciaux gérés (hors du champ de ce projet pour l'instant).
* Ne gère pas les jokers (`*`) ni les guillemets, etc.

## Prérequis

* Ubuntu 20.04 LTS, compilateur GCC avec les options : `-Wall -Werror -Wextra -pedantic -std=gnu89`
* Le code respecte les règles de style **Betty**.
* Aucune fuite mémoire (vérifié avec Valgrind).
* Seuls les appels systèmes autorisés peuvent être utilisés (ex : `read`, `write`, `fork`, `execve`, `wait`, `getline`, etc.)

## Compilation

Compiler tous les fichiers `.c` avec la commande :

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Utilisation

**Mode interactif :**
Lancer le shell en exécutant le fichier compilé `hsh` :

```bash
$ ./hsh
#cisfun$ /bin/pwd
/home/utilisateur/shell_demo
#cisfun$ /bin/ls -l
```

**Remarque :** Si vous tapez une commande sans chemin absolu (comme `ls`), le shell essaiera d'exécuter un fichier du répertoire courant. Comme la recherche dans le PATH n'est pas encore implémentée, cela échouera souvent.

**Mode non interactif :**
Vous pouvez passer des commandes via un tube ou un fichier :

```bash
$ echo "/bin/echo Bonjour Shell" | ./hsh
Bonjour Shell
$ cat commandes.txt | ./hsh
```

## Exemple

Session interactive :

```bash
$ ./hsh
#cisfun$ ls
./hsh: 1: ls: not found
#cisfun$ /bin/ls
fichier1.c  fichier2.c  hsh  main.c  shell.h
#cisfun$ /bin/ls -l /tmp
drwxrwxrwt 14 root root 4096 janv.  1 12:00 .
drwxr-xr-x 23 root root 4096 janv.  1 08:30 ..
#cisfun$ ^D
$
```

Dans l'exemple ci-dessus :

* La commande `ls` a échoué car le shell n'utilise pas encore PATH.
* `/bin/ls` a réussi car le chemin absolu a été fourni.
* Ctrl+D (`^D`) a été utilisé pour quitter la session proprement.

## Fichiers

* **shell.h :** Fichier d'en-tête avec les prototypes et les variables globales.
* **main.c :** Fichier source principal avec la boucle du shell et les fonctions d'exécution de base.
  (*D'autres fichiers seront ajoutés dans les tâches suivantes*)

## Auteurs

Projet réalisé dans le cadre du cursus Holberton School.
**Lucas & Ryan**
