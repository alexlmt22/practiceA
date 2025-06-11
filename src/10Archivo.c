#include <stdio.h>
#include "../lib/utility.h"
const int ERR = -1, OK = 1;

int escribirArchivo(const char *pathFile, const char *contenido) {
    FILE *f = fopen(pathFile, "a+"); // Abrir en modo append
    if (f == NULL)
        return ERR;

    fprintf(f, "%s\n", contenido);
    fclose(f);
    return OK;
}

void leerArchivo(const char *pathFile) {
    FILE *archivo = fopen(pathFile, "r");
    if (archivo == NULL)  
        return; // Error al abrir el archivo
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        printf("%s", buffer);
    }
    
    fclose(archivo);
}

int eliminarArchivo(const char *pathFile) {
    if (remove(pathFile) != 0) 
        return ERR; // Error al eliminar el archivo
    return OK; // Archivo eliminado exitosamente
}

int main() {
    const char *pathFile = "../../datafile/Alumnos.txt";
    
    if (escribirArchivo(pathFile, "Hola, a todos ....!")== OK) {
        leerArchivo(pathFile);
        printf("Archivo '%s' creado y contenido escrito correctamente.\n", pathFile);
    } else {
        printf("Error al escribir en el archivo '%s'.\n", pathFile);
        return ERR;
    }
    return 0;
}