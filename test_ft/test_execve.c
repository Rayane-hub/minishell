#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

    // Exécution du programme avec execve  
	
    char *program_path = "/bin/cat";// Chemin vers le programme à exécuter
    char *args[] = { "cat", "infile", "-ed", NULL };// Arguments de la cmd (y compris le nom du la cmd elle-même)
    
	if (execve(program_path, args, NULL) == -1) {
        perror("execve");  // En cas d'erreur
        exit(EXIT_FAILURE);
    }

    // Cette ligne ne sera jamais atteinte si execve réussit
    printf("Cette ligne ne sera jamais atteinte\n");

    return 0;
}
