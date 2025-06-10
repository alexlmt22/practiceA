#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int e = -1;
enum {Q0 = 1, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, 
      Q11, Q12, Q13, Q14, Q15, Q16, Q17, Q18, Q19, Q20} state = Q0;

const char laMonedas[] = "ctvfd \n";  // c=5¢, t=10¢, v=25¢, f=50¢, d=100¢, espacio, \n

const int laMt[21][7] = {
    // c(5¢) t(10¢) v(25¢) f(50¢) d(100¢) ' '  \n
    {Q1,    Q2,    Q5,    Q10,   Q20,    e,  e},   // Q0 (0¢)
    {Q2,    Q3,    Q6,    Q11,   e,      Q1, Q1},  // Q1 (5¢)
    {Q3,    Q4,    Q7,    Q12,   e,      Q2, Q2},  // Q2 (10¢)
    {Q4,    Q5,    Q8,    Q13,   e,      Q3, Q3},  // Q3 (15¢)
    {Q5,    Q6,    Q9,    Q14,   e,      Q4, Q4},  // Q4 (20¢)
    {Q6,    Q7,    Q10,   Q15,   e,      Q5, Q5},  // Q5 (25¢)
    {Q7,    Q8,    Q11,   Q16,   e,      Q6, Q6},  // Q6 (30¢)
    {Q8,    Q9,    Q12,   Q17,   e,      Q7, Q7},  // Q7 (35¢)
    {Q9,    Q10,   Q13,   Q18,   e,      Q8, Q8},  // Q8 (40¢)
    {Q10,   Q11,   Q14,   Q19,   e,      Q9, Q9},  // Q9 (45¢)
    {Q11,   Q12,   Q15,   Q20,   e,      Q10,Q10}, // Q10 (50¢)
    {Q12,   Q13,   Q16,   e,     e,      Q11,Q11}, // Q11 (55¢)
    {Q13,   Q14,   Q17,   e,     e,      Q12,Q12}, // Q12 (60¢)
    {Q14,   Q15,   Q18,   e,     e,      Q13,Q13}, // Q13 (65¢)
    {Q15,   Q16,   Q19,   e,     e,      Q14,Q14}, // Q14 (70¢)
    {Q16,   Q17,   Q20,   e,     e,      Q15,Q15}, // Q15 (75¢)
    {Q17,   Q18,   e,     e,     e,      Q16,Q16}, // Q16 (80¢)
    {Q18,   Q19,   e,     e,     e,      Q17,Q17}, // Q17 (85¢)
    {Q19,   Q20,   e,     e,     e,      Q18,Q18}, // Q18 (90¢)
    {Q20,   e,     e,     e,     e,      Q19,Q19}, // Q19 (95¢)
    {e,     e,     e,     e,     e,      Q20,Q20}  // Q20 (100¢)
};

int laBuscarMoneda(char c) {
    for (int i = 0; laMonedas[i] != '\0'; i++) {
        if (laMonedas[i] == c) return i;
    }
    return e;
}

int esCadenaValida(const char *cadena) {
    int laCol = 0, laNextMoneda = Q0;
    
    for (int i = 0; cadena[i] != '\0' && cadena[i] != '\n'; i++) {
        if (cadena[i] == ' ') continue;
        laCol = laBuscarMoneda(cadena[i]);
        if (laCol == e) return 0; // Moneda no aceptada
        
        laNextMoneda = laMt[laNextMoneda-1][laCol];
        if (laNextMoneda == e) return 0; // Saldo insuficiente
    }
    
    // Solo consideramos válidos los estados que corresponden a productos
    return (laNextMoneda == Q5 || laNextMoneda == Q10 || 
            laNextMoneda == Q15 || laNextMoneda == Q20);
}

const char* obtenerProducto(int estado) {
    switch(estado) {
        case Q5:  return "chicle ";
        case Q10: return "helado ";
        case Q15: return "gaseosa ";
        case Q20: return "salchipapa ";
        default:  return NULL;
    }
}

void procesarArchivo(const char *nombreEntrada, const char *nombreSalida) {
    FILE *entrada = fopen(nombreEntrada, "r");
    FILE *salida = fopen(nombreSalida, "w");
    
    if (!entrada || !salida) {
        printf("Error al abrir los archivos\n");
        if (entrada) fclose(entrada);
        if (salida) fclose(salida);
        return;
    }
    
    fprintf(salida, "--- Cadenas válidas encontradas ---\n");
    
    char linea[256];
    while (fgets(linea, sizeof(linea), entrada)) {
        // Eliminar el salto de línea
        linea[strcspn(linea, "\n")] = '\0';
        
        if (strlen(linea) > 0 && esCadenaValida(linea)) {
            // Procesar para obtener el producto exacto
            int laCol = 0, laNextMoneda = Q0;
            for (int i = 0; linea[i] != '\0'; i++) {
                if (linea[i] == ' ') continue;
                laCol = laBuscarMoneda(linea[i]);
                laNextMoneda = laMt[laNextMoneda-1][laCol];
            }
            
            const char *producto = obtenerProducto(laNextMoneda);
            if (producto) {
                fprintf(salida, "%s -> %s\n", linea, producto);
            }
        }
    }
    
    fclose(entrada);
    fclose(salida);
    
    printf("Procesamiento completado. Resultados en el archivo %s\n", nombreSalida);
}

int main() {

    procesarArchivo("entradas.txt", "resultados.txt");
    
    return 0;
}
