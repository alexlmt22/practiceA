#include <stdio.h>

const int  e = -1;
enum {H0=0, H1, H2, H3} state = H0;
const char alphabet[]= "cnxyza \n";
const int  mt[4][8]  = {//  c n x y z a  \n
                         {  1,0,2,2,2,e,e,e}    // H0
                        ,{  1,e,e,e,e,3,H1,H1}  // H1
                        ,{  e,e,2,2,2,e,e,e}    // H2
                        ,{  e,e,e,e,e,3,H3,H3}  // H3
                       };

int searchAlphabet(char c) {
    for (int i = 0; alphabet[i] != '\0';i++) 
        if (alphabet[i] == c) 
            return i;
    return e; 
}

void processInput(char w[]) {
    int col = 0, q = H0;
    
    for (int i = 0; w[i] != '\n'; i++) {
        if (w[i] == ' ') continue;
        printf("%c", w[i]);
        col = searchAlphabet(w[i]);
        if (col == e) {
            printf("Condicion no existe: %c\n", w[i]);
            return;
        }
        q = mt[q][col];
        if (q == e) {
            printf("\nError de transicion\n");
            return;
        }
    }
    switch (q) 
    {
        case H1: printf("\n Soy Hormiga soldado\n"); break;
        case H3: printf("\n Soy Super Hormiga soldado\n"); break;
        default: printf("\n No es una Hormiga soldado\n"); break;
    }
}

int main()
{
    char input[] = "ccc ccc\n";
    processInput(input);
    return 0;
}