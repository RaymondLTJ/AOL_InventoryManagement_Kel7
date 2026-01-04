#include <stdio.h>

int main() {
    char teks[128];
    int geser, i;

    printf("Masukkan string: ");
    scanf(" %[^\n]", teks);

    printf("Masukkan shift : ");
    scanf("%d", &geser);

    /* mastikan shift nggak overflow dan handle nilai yang negatif */
    geser = (geser % 26 + 26) % 26;

    for (i = 0; teks[i] != '\0'; i++) {
        char c = teks[i];
        
        /* cek apakah karakter itu huruf */
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            /* tentukan titik awal (A atau a) */
            char start = (c >= 'a') ? 'a' : 'A';
            /* geser karakter */
            teks[i] = (c - start + geser) % 26 + start;
        }
    }

    printf("Hasil enkripsi : %s\n", teks);

    return 0;
}