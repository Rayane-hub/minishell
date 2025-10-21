
# 🐚 Minishell

**Projet 42 - École 42 Lyon**  
Recréation d’un **shell UNIX minimaliste** en C, capable d’interpréter et d’exécuter des commandes utilisateur dans un environnement contrôlé.  
L’objectif principal est de comprendre le fonctionnement interne d’un shell (bash/zsh), la gestion des processus et la communication entre eux.

---

## 🧠 Description

Le programme lit les commandes saisies par l’utilisateur, les parse, puis exécute les instructions correspondantes via des appels système UNIX.  
Il gère les **pipes**, **redirections**, **variables d’environnement**, et la **création de processus enfants**.  

---

## ⚙️ Fonctionnalités principales

- Exécution des commandes du système (ex: `ls`, `cat`, `grep`, etc.)  
- Gestion des **pipes** (`|`) et **redirections** (`>`, `>>`, `<`)  
- Implémentation des **builtins** (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)  
- Gestion des **variables d’environnement**  
- Traitement des **signaux** (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)  
- Gestion fine de la mémoire et des processus enfants  
- Support partiel du comportement de Bash  

---

## 🧰 Compétences développées

- Programmation système en C  
- Manipulation des **processus** et **pipes**  
- Gestion de la mémoire et des **descripteurs de fichiers**  
- Parsing lexical et syntaxique  
- Gestion des erreurs et des signaux UNIX  
- Travail collaboratif et rigueur dans les projets complexes  

---

## 🛠️ Compilation

Utilisez le **Makefile** :
```bash
make
```

Cela génère l’exécutable :
```bash
./minishell
```

---

## 🚀 Exemple d’exécution

```bash
$ ./minishell
minishell$ ls -la | grep main
-rw-r--r-- 1 rayane 42  3888 Oct 21 19:21 main.c
minishell$ echo "Hello World"
Hello World
```

---

## 📸 Aperçu visuel

L’image ci-dessous montre l’exécution du shell, la compilation avec `make re`, et l’affichage du répertoire via les commandes internes et externes.  

