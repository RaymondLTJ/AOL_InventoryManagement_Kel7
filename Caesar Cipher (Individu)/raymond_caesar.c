#include <stdio.h>
#include <string.h>
#ifdef _WIN32
	#define CLEAR "cls"
	#include <windows.h>
#else
	#define CLEAR "clear"
	#include <unistd.h>
#endif

//fungsi proses shifting string
void shiftStr(char str[], int shift){
    for (int i = 0; str[i] != '\0'; i++) {
        char cek = str[i];

        if (cek >= 'a' && cek <= 'z') {
            str[i] = (cek - 'a' + shift) % 26 + 'a';
        }
        else if (cek >= 'A' && cek <= 'Z') {
            str[i] = (cek - 'A' + shift) % 26 + 'A';
        }
    }	
}

//fungsi mengembalikan true/false kalau mau coba lagi/tidak
int cobaLagi(char *mode){
	while(1){
		printf ("Mau coba %s lagi? (Y/N): ", mode);
		char pilihan;
		scanf (" %c", &pilihan);
		if (pilihan == 'Y' || pilihan == 'y'){
			return 1;
		}
		else if (pilihan == 'N' || pilihan == 'n'){
			return 0;
		}	
		else{
			printf ("Input invalid!\n");
			continue;
		}	
	}
}

void enterContinue(){
    int halo;
    while ((halo = getchar()) != '\n' && halo != EOF);
}

//fungsi untuk enkripsi string tergantung shift (+ atau -)
void encryption (){
	system(CLEAR);
	while(1){
		char str[101];
    	int shift;	
    	printf ("\nCAESAR CIPHER PROGRAM (ENCRYPTION MODE)\n\n");
    	
		printf("Ketik string: ");
    	scanf (" %[^\n]", str);
    	while(getchar() != '\n');
    	
    	if (strlen(str) < 5){
			printf ("String kurang dari 5 karakter. Coba lagi\n");
			printf ("Enter untuk lanjut\n");
			enterContinue();
			system(CLEAR);
			continue;
		}
		else if (strlen(str) > 100){
			printf ("String lebih dari 100 karakter. Coba lagi\n");
			printf ("Enter untuk lanjut\n");
			enterContinue();
			system(CLEAR);
			continue;
		}

    	printf("Ketik shift: ");
    	scanf("%d", &shift);
    	shift = (shift % 26 + 26) % 26; //shift selalu di 0 - 25 (termasuk negatif)
	
		shiftStr(str, shift); //enkripsi

    	printf("String akhir: %s\n", str);
    
		if (!cobaLagi("encrypt")){
			system(CLEAR);
			break;
		}
		else system(CLEAR);
	}
}

//fungsi untuk dekripsi string tergantung shift (+ atau -)
void decryption(){
	system(CLEAR);
    while (1){
        char str[101];
        int shift;
        printf ("\nCAESAR CIPHER PROGRAM (DECRYPTION MODE)\n\n");

        printf("Ketik string terenkripsi: ");
        scanf(" %[^\n]", str);
        while(getchar() != '\n');
        
        if (strlen(str) < 5){
			printf ("String kurang dari 5 karakter. Coba lagi\n");
			printf ("Enter untuk lanjut\n");
			enterContinue();
			system(CLEAR);
			continue;
		}
		else if (strlen(str) > 100){
			printf ("String lebih dari 100 karakter. Coba lagi\n");
			printf ("Enter untuk lanjut\n");
			enterContinue();
			system(CLEAR);
			continue;
		}

        printf("Ketik shift: ");
        scanf("%d", &shift);
        shift = (shift % 26 + 26) % 26; //shift selalu di 0 - 25 (termasuk negatif)
        shiftStr(str, 26 - shift); //dekripsi
        
        printf("Hasil dekripsi: %s\n", str);

        if (!cobaLagi("decrypt")){
        	system(CLEAR);
        	break;
		}
		else system(CLEAR);
    }
}



int main() {
    int pilihan;

    while (1) {
    	system(CLEAR);
        printf ("\nCAESAR CIPHER PROGRAM\n\n");
        printf ("Pilih 1-3!\n");
        printf ("1. Encryption\n");
        printf ("2. Decryption\n");
        printf ("3. Exit Program\n");
        printf ("Pilihan: ");
 		scanf  ("%d", &pilihan);
 		while (getchar() != '\n');

        switch (pilihan){
            case 1:
                encryption();
                break;
            case 2:
                decryption();
                break;
            case 3:
                printf ("\nSelamat tinggal!\n");
                return 0;
            default:
                printf ("Input invalid! Enter untuk coba lagi\n");
                enterContinue();
                
        }
    }

    return 0;
}

