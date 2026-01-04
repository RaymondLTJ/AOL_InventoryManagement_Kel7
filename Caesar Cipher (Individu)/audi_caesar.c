#include <stdio.h>


void shiftStr(char str[], int shift) {
    // Implementasi sama
}

int main() {
    FILE *input, *output;
    char str[1000]; // Buffer lebih besar
    int shift;
    
    printf("Nama file input: ");
    char filename[100];
    scanf("%s", filename);
    
    input = fopen(filename, "r");
    output = fopen("output.txt", "w");
    
    if (!input || !output) {
        printf("Error membuka file!\n");
        return 1;
    }
    
    printf("Ketik shift: ");
    scanf("%d", &shift);
    
    while (fgets(str, sizeof(str), input)) {
        shiftStr(str, shift);
        fputs(str, output);
    }
    
    fclose(input);
    fclose(output);
    printf("File berhasil diproses!\n");
    
    return 0;
}