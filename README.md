Simple Shell – Projet de Shell Unix en C
Introduction

Ce projet consiste à développer un interpréteur de commandes simple (une shell Unix) en langage C, reprenant les fonctionnalités de base de sh (le shell Bourne). Un shell est un programme qui lit les commandes saisies par l’utilisateur et les exécute en interagissant avec le système d’exploitation

. Le tout premier shell Unix, appelé Thompson Shell, a été inventé par Ken Thompson en 1971 aux laboratoires Bell
megasun.bch.umontreal.ca
. Ken Thompson est un pionnier de l’informatique (co-concepteur d’Unix et du langage B, prédécesseur du C)
. Ce projet de Shell simple a pour but de recréer une version minimale d’un tel interpréteur, afin de comprendre comment fonctionne un shell et de maîtriser des concepts clés du système Unix.

Fonctionnement d’un Shell Unix

Un shell typique fonctionne en boucle : il affiche un prompt (invite), attend l’entrée de l’utilisateur, analyse la commande puis crée un nouveau processus pour exécuter le programme demandé

. Plus précisément :

Le shell lit la ligne de commande saisie (par exemple via getline). S’il s’agit de la fin de fichier (EOF, End-Of-File), le shell doit détecter cette condition – indiquant qu’aucune donnée supplémentaire ne peut être lue
csdb.dk
 – et en général terminer proprement (par exemple, en mode interactif, Ctrl+D en début de ligne envoie un EOF pour quitter le shell).

Le shell découpe la ligne en arguments (nom de commande et éventuels paramètres) à l’aide d’un tokenizer (par ex. strtok). Le programme recherché est ensuite localisé en utilisant la variable d’environnement PATH : si le nom de commande saisi ne contient pas de '/', le shell parcourt chaque dossier listé dans PATH pour voir si un exécutable du nom correspondant s’y trouve
docs.oracle.com
. Cela permet de trouver, par exemple, la commande ls dans des répertoires standard comme /bin ou /usr/bin sans avoir à saisir son chemin complet.

Une fois le chemin du programme déterminé, le shell crée un processus enfant en appelant la fonction système fork() (le processus appelant est le père, le nouveau process est le fils). Le PID (Process ID) est un identifiant numérique unique attribué à chaque processus

, et le PPID (Parent Process ID) est l’identifiant du processus parent (celui qui a engendré le nouveau processus)

.

Dans le processus fils, le shell appelle la fonction système execve() pour exécuter le nouveau programme choisi

. L’appel système execve remplace l’image du processus courant par le programme spécifié, en lui passant les arguments et un tableau de variables d’environnement

. (Le shell utilise ici un appel système : à la différence d’un simple appel de fonction interne, un appel système entraîne un basculement en mode noyau pour effectuer une opération privilégiée
techno-science.net
.) Si execve réussit, le nouveau programme démarre et ne retourne pas dans le code du shell appelant

 (le processus fils n’exécute plus le code du shell mais celui du programme lancé).

Pendant ce temps, le processus père (le shell original) peut soit continuer à accepter d’autres commandes (s’il est configuré pour une exécution en arrière-plan), soit plus généralement attendre la fin du processus fils. Pour cela, le shell utilise wait() ou waitpid(), qui suspend l’exécution du processus parent jusqu’à la terminaison de l’un de ses processus fils

. Une fois le processus fils terminé, wait() renvoie son PID au parent, permettant au shell de récupérer le statut de sortie du programme exécuté. Le shell retourne alors à l’affichage du prompt et attend la commande suivante (boucle).

En résumé, la shell implémente un cycle Lecture – Parse – fork – exec – wait en boucle. Certains programmes ne nécessitent pas de créer de nouveau processus (par exemple les built-in internes au shell), et dans ces cas le shell traite la commande lui-même sans fork. Par ailleurs, le shell peut manipuler ou utiliser l’environnement du processus courant : par exemple, il peut accéder aux variables d’environnement via l’externe environ ou via getenv, et modifier l’environnement (avec setenv, unsetenv) si nécessaire pour des commandes internes. Notamment, la variable PATH mentionnée plus haut fait partie de l’environnement du shell et peut être modifiée par l’utilisateur pour influencer la recherche des exécutables.

Fonctionnalités implémentées

Le shell développé dans ce projet, nommé hsh, prend en charge les fonctionnalités de base suivantes :

Exécution de commandes du système : le shell permet de lancer des programmes en invoquant leur nom (avec arguments éventuels). Il recherche le binaire correspondant via PATH et utilise fork + execve pour exécuter le programme. Par exemple, lancer ls -l /tmp affichera la liste du répertoire /tmp en passant par l’exécution du binaire /bin/ls. Si la commande entrée est un chemin complet ou relatif (contenant ‘/’), le shell exécute directement le fichier indiqué sans chercher dans PATH.

Prompt interactif : en mode interactif (lancé sans redirection), le shell affiche un prompt personnalisé ($) invitant l’utilisateur à entrer une commande. Ce prompt est affiché de manière répétée tant que l’utilisateur n’a pas quitté le shell. Le shell détecte également l’entrée interactive ; ainsi, si l’entrée standard n’est pas un terminal (mode non-interactif, voir ci-dessous), le prompt n’est pas affiché.

Modes interactif et non-interactif : Le programme fonctionne aussi bien en mode interactif (l’utilisateur tape commande après commande, avec un prompt) qu’en mode non-interactif en lisant l’entrée sur stdin. Par exemple, on peut canaliser un fichier de commandes ou une séquence de commandes dans le shell. Dans ce mode, le shell lit jusqu’à l’EOF puis se termine automatiquement.

Gestion des erreurs : Si l’utilisateur entre une commande introuvable, le shell imprime un message d’erreur approprié sur la sortie d’erreur standard (stderr). Le format de sortie d’erreur respecte celui du shell /bin/sh. Par exemple, pour une commande inexistante “qwerty”, le shell affichera :

./hsh: 1: qwerty: not found


Le préfixe (./hsh ici) correspond au nom de l’exécutable du shell tel qu’invoqué (argv[0]), et 1 est le numéro de ligne ou d’invocation de commande. Le shell gère ainsi les erreurs de commande non trouvée, ainsi que d’autres erreurs d’exécution (par exemple, permission refusée) en affichant perror ou un message dédié.

Commandes intégrées (built-ins) : Le shell implémente quelques commandes internes sans lancer de nouveau processus. Notamment:

La commande exit pour quitter le shell. Taper exit provoque la fin du shell (en retournant éventuellement le code de sortie donné en argument). Le shell gère aussi la fin de fichier (EOF) comme un signal de sortie : en mode interactif, presser Ctrl+D à une invite vide cause la sortie du shell.

La commande env pour afficher les variables d’environnement. Lorsque l’utilisateur tape env, le shell imprime la liste complète de son environnement (toutes les paires VARIABLE=valeur).
(D’autres built-ins classiques comme cd ou setenv/unsetenv peuvent être implémentés en bonus – dans la version de base de ce projet, cd n’est pas obligatoirement inclus.)

Aucun leak mémoire : Une attention particulière a été portée à la gestion dynamique de la mémoire. Toute allocation effectuée (par exemple lors du parsing avec malloc/strdup) est libérée avant la fin du programme afin d’éviter les fuites de mémoire. Le shell tient compte également de la libération des processus zombies via wait.

En outre, le shell désactive certains comportements par défaut pour améliorer l’expérience interactive, par exemple en ignorant le signal SIGINT (Ctrl+C) lorsqu’il est saisi à la prompt – de manière à ne pas quitter brutalement le shell lui-même. Ainsi, Ctrl+C interrompt uniquement les processus lancés par le shell, pas le shell lui-même (comportement similaire à /bin/sh).

Techniquement, ce shell utilise uniquement les appels systèmes et fonctions autorisés (tels que listés dans le sujet). Par exemple, pour les E/S et la manipulation de fichiers : read, write, getline, etc., pour les processus : fork, execve, wait, kill, pour les signaux : signal, pour l’environnement : getenv/environ, etc. Aucune fonction non autorisée n’a été utilisée, conformément aux exigences du projet.

Compilation et utilisation

Pour compiler le shell, assurez-vous d’être sous Ubuntu 20.04 LTS avec le compilateur gcc. Toutes les sources .c et les fichiers d’en-tête nécessaires doivent être dans le même répertoire. Utilisez la commande de compilation suivante (options strictes de Holberton School) :

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh


Cette commande produit un exécutable nommé hsh. Vous pouvez ensuite lancer le shell de deux manières :

Mode interactif: en lançant ./hsh sans argument. Vous devriez alors voir apparaître le prompt custom (par exemple ($) ). Vous pouvez entrer des commandes comme vous le feriez dans un shell normal.

Mode non-interactif: en fournissant des commandes via l’entrée standard. Par exemple, en échoant une commande dans un tube vers hsh, ou en redirigeant un fichier :

echo "ls -l" | ./hsh


Dans ce cas, le shell exécutera la commande ls -l puis se fermera une fois l’EOF atteint en entrée. De même, cat script.txt | ./hsh exécutera toutes les commandes listées dans script.txt puis terminera.

Exemples d’utilisation

1. Mode interactif :

$ ./hsh
($) /bin/ls
README.md  main.c  shell.c  hsh
($) pwd
/home/user/simple_shell
($) env
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/bin
HOME=/home/user
...  # (autres variables d’environnement)
($) exit
$


Dans cet exemple, ./hsh est lancé, le prompt ($) apparaît. La commande /bin/ls liste le contenu du répertoire courant, la commande pwd affiche le chemin courant, env liste les variables d’environnement, puis exit quitte le shell interactif.

2. Mode non-interactif :

$ echo "echo Hello" | ./hsh
Hello
$
$ cat commands.txt
/bin/echo "Holberton"
/bin/ls /nonexistent
/bin/pwd
$ cat commands.txt | ./hsh
Holberton
./hsh: 1: /bin/ls: not found
/home/user/simple_shell
$


Dans le premier cas, la chaîne echo Hello est envoyée au shell, qui exécute la commande echo pour afficher “Hello”. Dans le second cas, un fichier commands.txt contenant plusieurs lignes de commandes est passé en entrée du shell. Le shell exécute tour à tour chaque commande. On voit qu’il affiche “Holberton” pour la première commande, un message d’erreur pour la deuxième (/nonexistent n’existe pas, le shell indique donc que /bin/ls n’a pas trouvé le fichier, avec le format d’erreur approprié contenant le numéro de ligne), puis le répertoire courant pour la troisième commande pwd. Après la fin du fichier, le shell sort.

Détails d’implémentation

Internement, le code du shell est organisé autour de la fonction main(int argc, char **argv, char **envp). À noter qu’en C, la fonction main peut avoir trois prototypes standards : int main(void), int main(int argc, char *argv[]), ou (selon l’implémentation) int main(int argc, char *argv[], char *envp[])
en.cppreference.com
. Ici le troisième paramètre envp (ou l’utilisation de la variable globale environ) permet d’accéder aux variables d’environnement du processus. Le shell utilise cet environnement initial (reçu de son parent, typiquement le terminal ou processus appelant) pour des opérations comme la recherche dans PATH ou l’affichage via env.

Plusieurs appels système et fonctions de la librairie C sont utilisés pour construire ce shell, parmi lesquels : fork pour créer des processus, execve pour lancer les programmes (remplaçant le code du processus fils)
man7.org
, wait/waitpid pour attendre la fin des processus enfants
fr.scribd.com
, isatty pour détecter le mode interactif (terminal ou non), getline pour la lecture de commande, strtok pour parser la ligne de commande en tokens, ainsi que des fonctions utilitaires de string (voir la liste complète autorisée plus loin). Le shell utilise également signal(SIGINT, handler) pour redéfinir le comportement à Ctrl+C (le handler est souvent défini pour renvoyer au prompt au lieu de quitter le programme).

Gestion des erreurs et codes de sortie : Le shell renvoie un code de sortie 0 en cas de succès (ou le code d’erreur s’il se termine sur une condition d’erreur interne). Les commandes exécutées renvoient leur propre code d’état, que le shell peut récupérer via wait. En cas d’erreur d’exécution (par exemple, si execve échoue parce que le fichier n’est pas exécutable ou n’existe pas), le shell imprime un message d’erreur comme illustré plus haut, et continue le cycle en repassant en mode lecture de nouvelles commandes. Le shell gère également correctement l’allocation/libération de mémoire à chaque itération pour éviter toute fuite, et se termine en libérant toutes les ressources allouées.

Restrictions et spécifications du projet

Ce projet suit des exigences strictes de style et de portée : le code est conforme au style Betty (norme de style C de Holberton), et aucune fonction de la libc non autorisée n’est utilisée. Par exemple, toute impression sur sortie est faite via printf, fprintf ou write (pas de puts non autorisé), les allocations via malloc ont leur pendant free, etc. Seules les fonctions système autorisées dans l’énoncé peuvent être utilisées – par exemple, pour vérifier l’accès à un fichier, on utilise access()
fr.wikipedia.org
, pour changer de répertoire chdir(), etc., en évitant tout appel inutile au noyau (on utilise les appels systèmes uniquement quand c’est nécessaire, car ils induisent une transition en mode noyau plus coûteuse qu’un appel de fonction normal
techno-science.net
).

Voici la liste des fonctions système et libc autorisées et utilisées dans ce projet :

Fonctions de la librairie standard C (string.h…) pour la gestion de chaînes, mémoire et I/O de base : malloc, free, write, read, getline, printf, perror, strtok, strcpy, strcmp, etc.

Appels systèmes Unix : fork (création de processus)
fr.wikipedia.org
, execve (chargement d’un binaire dans un processus)
fr.wikipedia.org
, _exit/exit (terminaison de processus), wait/waitpid (attente de fin de processus enfant)
fr.wikipedia.org
, kill/signal (gestion de signaux), chdir (changement de répertoire courant), stat/lstat (informations de fichiers), open/close (gestion de fichiers), opendir/readdir/closedir (parcours de répertoires), etc.

Variables globales et appels liés à l’environnement : environ (variable globale contenant l’environnement du processus), getenv (lecture d’une variable d’environnement), etc., ainsi que des appels comme isatty (pour savoir si l’entrée est un terminal).

Le code source est divisé en plusieurs fichiers pour respecter la limite de 5 fonctions par fichier, et tous les fichiers d’en-tête ont des include guards. Le projet inclut également une page de manuel écrite pour la commande hsh (fichier man_1_simple_shell), documentant l’utilisation du shell, ainsi qu’un fichier AUTHORS listant les contributeurs du projet.

Compilation et tests automatisés

Après compilation, vous pouvez lancer le programme manuellement comme illustré ci-dessus. Il est également possible d’écrire des tests automatiques en batch en alimentant le shell avec des commandes prédéfinies et en comparant la sortie attendue. Le comportement de hsh doit être identique à /bin/sh pour la plupart des cas d’utilisation normaux, mis à part le nom du programme dans les messages d’erreur. Le projet a été validé à l’aide d’un ensemble de tests couvrant des cas classiques et des cas aux limites (commandes valides, commandes invalides, arguments spéciaux, très longues lignes, caractères spéciaux, etc.).

Enfin, un Checker automatisé a pu être utilisé pour évaluer le projet – cependant, la compréhension et les tests manuels approfondis pendant le développement étaient essentiels. Ce projet constitue une excellente introduction à la programmation système bas-niveau sur Unix, illustrant des notions de processus, d’appel système, de gestion de la mémoire et d’environnement, ainsi que la construction d’une interface en ligne de commande robuste.

Auteurs

Ce shell a été implémenté dans le cadre du programme Holberton School par :

LUCAS et RAYAN.
