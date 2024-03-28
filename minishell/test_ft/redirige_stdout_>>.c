#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

	//Open du outfile
	int fd_outfile = open("outfile", O_CREAT | O_RDWR | O_APPEND, 0777);
    if (fd_outfile == -1) {
        perror("Erreur lors de la création du fichier");
        exit(EXIT_FAILURE);
    }
	//redirection de stdout vers le fd d"outfile
	if (dup2(fd_outfile, 1) == -1)
	{
        perror("Erreur lors de la duplication du fichier");
        exit(EXIT_FAILURE);
    }
    // Exécution du programme avec execve  
	
    char *program_path = "/bin/ls";// Chemin vers le programme à exécuter
    char *args[] = { "ls", NULL };// Arguments de la cmd (y compris le nom du la cmd elle-même)
    
	if (execve(program_path, args, NULL) == -1) {
        perror("execve");  // En cas d'erreur
        exit(EXIT_FAILURE);
    }

    // Cette ligne ne sera jamais atteinte si execve réussit
    printf("Cette ligne ne sera jamais atteinte\n");

    return 0;
}
