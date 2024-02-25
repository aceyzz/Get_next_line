<img src="utils/gnl_banner.png" style="width: 100%">
<img src="utils/gnl_logo.png" style="width: 100%">

[ENGLISH VERSION](#english-version)

## Index

1. [Sujet](#sujet)
2. [Descriptif - Partie obligatoire](#descriptif---partie-obligatoire) > [get_next_line.c](#get_next_linec) > [get_next_line_utils.c](#get_next_line_utilsc) > [get_next_line.h](#get_next_lineh)
3. [Descriptif - Partie bonus](#descriptif---partie-bonus) > [get_next_line_bonus.c](#get_next_line_bonusc)
4. [Résultat des tests](#résultats-des-tests)

# Sujet
La fonction [get_next_line](#get_next_linec) permet de lire à partir d'un fichier donné, une ligne à la fois, sans perdre la position actuelle dans le fichier. Elle retourne ```1``` si une ligne a été lue avec succès, ```0``` si la fin du fichier a été atteinte et ```-1``` en cas d'erreur.

### Partie obligatoire
- Lire un fichier ligne par ligne.
- Retourner la ligne lue ou ```NULL``` en cas d'erreur ou s'il n'y a plus rien à lire.
- Fonctionner correctement pour la lecture de fichiers ou de l'entrée standard.
- Doit être suivie d'un ```\n```, sauf en fin de fichier sans ```\n```.
- ***get_next_line.h*** doit contenir au moins le prototype de la fonction.
- ***get_next_line_utils.c*** peut contenir des fonctions auxiliaires nécessaires.
- Compilez le programme avec l'option ```-D BUFFER_SIZE=n``` pour spécifier la taille du buffer à utiliser avec read().
- Un ```BUFFER_SIZE``` doit être défini par défaut le cas échéant.
- Le comportement est indéterminé si le fichier a été modifié entre deux appels sans avoir été lu entièrement.
- Bibliothèque ```libft``` interdite.
- Fonction ```lseek()``` interdite.
- Variables globales interdites.

### Partie bonus
- Gérer plusieurs descripteurs de fichier simultanément.
- Lire chacun des fichiers sans perdre les contenus lus.
- ***get_next_line*** doit pouvoir afficher le ```fd``` 3, puis le 4, le 5, puis à nouveau le 3, à nouveau le 4, etc.
- 3 fichiers à ajouter (en + de la partie obligatoire) :
	- **get_next_line_bonus.c**
	- **get_next_line_bonus.h**
	- **get_next_line_utils_bonus.c**

<br>

## Descriptif - Partie obligatoire

#### **[get_next_line.c](./get_next_line.c)**

1. **Inclusion des fichiers nécessaires** :
   - La fonction commence par inclure le fichier d'en-tête **get_next_line.h***, qui contient le prototype de la fonction.
   - Si la macro `BUFFER_SIZE` n'est pas définie, on lui fixe une valeur par défaut de 42 (personnalisable).

2. **Fonction `line_reader`** :
   - Cette fonction est responsable de la lecture du contenu du fichier associé au descripteur de fichier (`fd`) et de la construction de la ligne lue.
   - Un tampon temporaire (`temp`) de la taille `BUFFER_SIZE + 1` est alloué en mémoire.
   - La lecture du fichier se poursuit tant que la ligne actuelle ne contient pas de caractère de nouvelle ligne (`'\n'`) et que la fonction `read` renvoie des octets valides (`bytes > 0`).
   - Les données lues sont stockées dans `temp`, et `temp` est joint à la fin de la ligne actuelle (`line`).

3. **Fonction `line_extractor`** :
   - Cette fonction extrait la première ligne de `line`, y compris le caractère de nouvelle ligne (`'\n'`) s'il est présent.
   - Elle alloue un nouvel espace en mémoire pour stocker la ligne extraite.
   - La ligne extraite est ensuite retournée.

4. **Fonction `line_remover`** :
   - Cette fonction supprime la première ligne (y compris le caractère de nouvelle ligne) de `line`.
   - Elle alloue un nouvel espace en mémoire pour stocker la ligne restante.
   - La ligne restante est retournée.

5. **Fonction `get_next_line`** :
   - Donction principale qui coordonne les étapes précédentes pour lire une ligne depuis le descripteur de fichier (`fd`).
   - Elle vérifie d'abord que `fd` est valide et que `BUFFER_SIZE` est correctement défini.
   - Elle utilise `read(fd, 0, 0)` pour vérifier que le descripteur de fichier est prêt à être lu.
   - Elle appelle `line_reader` pour lire et construire la ligne actuelle dans `current_line`.
   - Ensuite, elle utilise `line_extractor` pour extraire la première ligne de `current_line` et la stocke dans `dest`.
   - Enfin, elle utilise `line_remover` pour supprimer la ligne extraite de `current_line`.

<br>

#### **[get_next_line_utils.c](./get_next_line_utils.c)**
1. **`ft_strlen`** (Calcul de la longueur d'une chaîne de caractères)
2. **`ft_strchr`** (Recherche d'un caractère dans une chaîne de caractères)
3. **`ft_strjoin`** (Concaténation de deux chaînes de caractères)

<br>

#### **[get_next_line.h](./get_next_line.h)**
- Header regroupant les prototypes de chaque fonctions.

<br>

## Descriptif - Partie bonus
#### **[get_next_line_bonus.c](./get_next_line_bonus.c)**
1. **Gestion de plusieurs descripteurs de fichiers (fd)** :
   - La fonction `get_next_line_bonus` prend un descripteur de fichier (`fd`) en argument, ce qui lui permet de gérer plusieurs fichiers simultanément. Elle maintient un tableau `current_line` pour stocker les lignes en cours de lecture pour chaque descripteur de fichier.

2. **`static char *current_line[OPEN_MAX]`** :
   - Au lieu d'utiliser une seule variable statique pour stocker la ligne en cours de lecture, on utilise un tableau de pointeurs pour gérer les lignes de plusieurs descripteurs de fichier.

3. **Utilisation de `OPEN_MAX`** :
   - `OPEN_MAX` est une constante système qui représente le nombre maximal de descripteurs de fichiers ouverts simultanément. Cette constante est utilisée pour dimensionner le tableau `current_line` et permettre la gestion de plusieurs descripteurs de fichier.

4. **Appel avec le descripteur de fichier spécifique** :
   - Vous devez appeler `get_next_line_bonus` avec le descripteur de fichier que vous souhaitez lire. Par exemple, `get_next_line_bonus(fd1)` pour le premier fichier, `get_next_line_bonus(fd2)` pour le deuxième fichier, et ainsi de suite.

5. **Stockage séparé pour chaque descripteur de fichier** :
   - Chaque descripteur de fichier a sa propre ligne en cours de lecture stockée dans `current_line[fd]`. Cela garantit que la lecture des différents fichiers n'interfère pas les uns avec les autres.


###### ***Les autres fonctions restent inchangées.***

<br>

## Résultats des tests
#### [gnlTester by Tripouille](https://github.com/Tripouille/gnlTester)
<img src="utils/obligatoire1.png" alt="gnlTester" style="width: 100%">
<img src="utils/obligatoire2.png" alt="gnlTester" style="width: 100%">
<img src="utils/bonus1.png" alt="gnlTester" style="width: 100%">
<img src="utils/bonus2.png" alt="gnlTester" style="width: 100%">


## Résultats de Moulinette

|          Note          |          Tests          |
|:----------------------:|:-----------------------:|
| ![](./utils/grade.png) | ![](./utils/detail.png) |

---

# ENGLISH VERSION

## Index

1. [Topic](#topic)
2. [Description - Mandatory Part](#description---mandatory-part) > [get_next_line.c](#get_next_linec) > [get_next_line_utils.c](#get_next_line_utilsc) > [get_next_line.h](#get_next_lineh)
3. [Description - Bonus Part](#description---bonus-part) > [get_next_line_bonus.c](#get_next_line_bonusc)
4. [Test Results](#test-results)

# Topic
The function [get_next_line](#get_next_linec) allows reading from a given file, one line at a time, without losing the current position in the file. It returns ```1``` if a line has been successfully read, ```0``` if the end of the file has been reached, and ```-1``` in case of an error.

### Mandatory Part
- Read a file line by line.
- Return the read line or ```NULL``` in case of error or if there is nothing more to read.
- Work correctly for reading files or from standard input.
- Must be followed by a ```\n```, except at the end of the file without ```\n```.
- ***get_next_line.h*** must contain at least the prototype of the function.
- ***get_next_line_utils.c*** can contain necessary auxiliary functions.
- Compile the program with the option ```-D BUFFER_SIZE=n``` to specify the buffer size to use with read().
- A ```BUFFER_SIZE``` must be defined by default if applicable.
- Behavior is undefined if the file has been modified between two calls without being fully read.
- Library ```libft``` is forbidden.
- Function ```lseek()``` is forbidden.
- Global variables are forbidden.

### Bonus Part
- Manage multiple file descriptors simultaneously.
- Read each of the files without losing the read contents.
- ***get_next_line*** must be able to display the ```fd``` 3, then 4, 5, then again 3, again 4, etc.
- 3 files to add (in addition to the mandatory part) :
	- **get_next_line_bonus.c**
	- **get_next_line_bonus.h**
	- **get_next_line_utils_bonus.c**

<br>

## Description - Mandatory Part

#### **[get_next_line.c](./get_next_line.c)**

1. **Including necessary files** :
   - The function begins by including the header file **get_next_line.h***, which contains the prototype of the function.
   - If the macro `BUFFER_SIZE` is not defined, it is set to a default value of 42 (customizable).

2. **Function `line_reader`** :
   - This function is responsible for reading the content of the file associated with the file descriptor (`fd`) and constructing the read line.
   - A temporary buffer (`temp`) of size `BUFFER_SIZE + 1` is allocated in memory.
   - Reading from the file continues as long as the current line does not contain a newline character (`'\n'`) and the `read` function returns valid bytes (`bytes > 0`).
   - Read data is stored in `temp`, and `temp` is joined to the end of the current line (`line`).

3. **Function `line_extractor`** :
   - This function extracts the first line from `line`, including the newline character (`'\n'`) if present.
   - It allocates new memory space to store the extracted line.
   - The extracted line is then returned.

4. **Function `line_remover`** :
   - This function removes the first line (including the newline character) from `line`.
   - It allocates new memory space to store the remaining line.
   - The remaining line is returned.

5. **Function `get_next_line`** :
   - The main function that coordinates the previous steps to read a line from the file descriptor (`fd`).
   - It first checks that `fd` is valid and that `BUFFER_SIZE` is correctly defined.
   - It uses `read(fd, 0, 0)` to check that the file descriptor is ready to be read.
   - It calls `line_reader` to read and construct the current line in `current_line`.
   - Then, it uses `line_extractor` to extract the first line from `current_line` and stores it in `dest`.
   - Finally, it uses `line_remover` to remove the extracted line from `current_line`.

<br>

#### **[get_next_line_utils.c](./get_next_line_utils.c)**
1. **`ft_strlen`** (Calculating the length of a string)
2. **`ft_strchr`** (Searching for a character in a string)
3. **`ft_strjoin`** (Concatenating two strings)

<br>

#### **[get_next_line.h](./get_next_line.h)**
- Header gathering the prototypes of each function.

<br>

## Description - Bonus Part
#### **[get_next_line_bonus.c](./get_next_line_bonus.c)**
1. **Managing multiple file descriptors (fd)** :
   - The function `get_next_line_bonus` takes a file descriptor (`fd`) as an argument, allowing it to manage multiple files simultaneously. It maintains a `current_line` array to store the lines currently being read for each file descriptor.

2. **`static char *current_line[OPEN_MAX]`** :
   - Instead of using a single static variable to store the current reading line, an array of pointers is used to manage lines from multiple file descriptors.

3. **Using `OPEN_MAX`** :
   - `OPEN_MAX` is a system constant representing the maximum number of file descriptors that can be opened simultaneously. This constant is used to size the `current_line` array and allow managing multiple file descriptors.

4. **Call with the specific file descriptor** :
   - You need to call `get_next_line_bonus` with the file descriptor you wish to read. For example, `get_next_line_bonus(fd1)` for the first file, `get_next_line_bonus(fd2)` for the second file, and so on.

5. **Separate storage for each file descriptor** :
   - Each file descriptor has its own current reading line stored in `current_line[fd]`. This ensures that reading different files does not interfere with each other.


###### ***The other functions remain unchanged.***

<br>

## Test Results
#### [gnlTester by Tripouille](https://github.com/Tripouille/gnlTester)
<img src="utils/obligatoire1.png" alt="gnlTester" style="width: 100%">
<img src="utils/obligatoire2.png" alt="gnlTester" style="width: 100%">
<img src="utils/bonus1.png" alt="gnlTester" style="width: 100%">
<img src="utils/bonus2.png" alt="gnlTester" style="width: 100%">


## Moulinette Results

|          Grade          |          Tests          |
|:----------------------:|:-----------------------:|
| ![](./utils/grade.png) | ![](./utils/detail.png) |


## License
This work is published under the terms of **[42 Unlicense](./LICENSE)**.
