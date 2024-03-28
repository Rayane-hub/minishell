#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {//cat f1 f2  -e > f3

	//Open du outfile
	int fd_outfile = open("f3", O_CREAT | O_RDWR, 0777);
    if (fd_outfile == -1) {
        perror("Erreur lors de la création du fichier");
        exit(EXIT_FAILURE);
    }
	//rediriction de stdout vers le fd d"outfile
	if (dup2(fd_outfile, 1) == -1)
	{
        perror("Erreur lors de la duplication du fichier");
        exit(EXIT_FAILURE);
    }
    // Exécution du programme avec execve  
	
    char *program_path = "/bin/cat";// Chemin vers le programme à exécuter
    char *args[] = { "cat", "f1", "f2", "-e", NULL };// Arguments de la cmd (y compris le nom du la cmd elle-même)
    
	if (execve(program_path, args, NULL) == -1) {
        perror("execve");  // En cas d'erreur
        exit(EXIT_FAILURE);
    }

    // Cette ligne ne sera jamais atteinte si execve réussit
    printf("Cette ligne ne sera jamais atteinte\n");

    return 0;
}
