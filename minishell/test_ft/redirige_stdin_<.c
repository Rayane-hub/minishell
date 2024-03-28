#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

	//Open du outfile
	int fd_infile = open("infile", O_RDONLY, 0777);
    if (fd_infile == -1) {
        perror("Erreur lors de la l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
	//redirection de stdin vers le fd d'infile
	if (dup2(fd_infile, 0) == -1)
	{  
        perror("Erreur lors de la duplication du fichier");
        exit(EXIT_FAILURE);
    }

	//------------------Exécution du programme avec execve-----------------------------------------------------------------------------  

	// Chemin vers le programme à exécuter
    char *program_path = "/bin/cat";
	// Arguments de la cmd (y compris le nom du la cmd elle-même)
    char *args[] = { "cat", NULL };

	if (execve(program_path, args, NULL) == -1) {
        perror("execve");  // En cas d'erreur
        exit(EXIT_FAILURE);
    }

    // Cette ligne ne sera jamais atteinte si execve réussit
    printf("Cette ligne ne sera jamais atteinte\n");

    return 0;
}
