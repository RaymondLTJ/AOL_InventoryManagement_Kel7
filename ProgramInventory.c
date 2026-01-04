#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// untuk keperluan clear console log dengan system(CLEAR) (agar screen tidak bloated) 
#ifdef _WIN32
	#define CLEAR "cls"
	#include <windows.h>
#else
	#define CLEAR "clear"
	#include <unistd.h>
#endif

//inisialisasi fungsi
void enterContinue();
int numValidation (char *str);
void showMenu();
int cariBarang(char nama[]);
void simpanData();
void muatData();
void tambahItem();
void hapusItem();
void editStok();
void lihatReport();
void urutDesc();
void urutAsc();
void exitProgram ();
void errMessage();

/* membuat struct untuk setiap barang (nama dan jumlah stok) */
typedef struct itemList {
    char nama[22]; //maks karakter = 20
    long long jumlah; // stok
} Item;

Item inv[100]; //jumlah item yang disimpan di inventory bisa sampai 100
int totalIndex = 0;

//fungsi pencet enter untuk lanjut
void enterContinue(){
    int halo;
    while ((halo = getchar()) != '\n' && halo != EOF);
}
//fungsi pengecekan string untuk mencegah input string setelah angka tetap valid (misal 1abc, 2nde, dll)
int numValidation (char *str){
	if (str[0] == '\0') return 0;
	
	for (int i = 0; str[i] != '\0'; i++){
        if (str[i] < '0' || str[i] > '9') return 0;
	}
	return 1;
}

/* searching barang dengan Linear Search (untuk keperluan  */
int cariBarang(char nama[]) {
    for (int i = 0; i < totalIndex; i++) {
        if (strcmp(inv[i].nama, nama) == 0) {
            return i; 
        }
    }
    return -1; 
}

/* kalo milih 5 (fitur sorting dengan menggunakan Bubble Sort (descending)) */
void urutDesc() {
	system(CLEAR);
	
	if (totalIndex == 0) {
		printf("-----------------------------------");
		printf("\nTidak ada data yang bisa diurutkan!");
		printf("\n-----------------------------------\n");	
        return;
	}
    for (int i = 0; i < totalIndex - 1; i++) {
        for (int j = 0; j < totalIndex - i - 1; j++) {
            if (inv[j].jumlah < inv[j+1].jumlah) {
                Item temp = inv[j];
                inv[j] = inv[j+1];
                inv[j+1] = temp;
            }
        }
    }
    printf("---------------------------------------");
	printf("\n[Sukses] Data diurutkan (High to Low)!!");
	printf("\n---------------------------------------\n");	
}

/* kalo milih 6 (fitur sorting dengan menggunakan Bubble Sort (ascending)) */
void urutAsc() {
	system(CLEAR);
	if (totalIndex == 0) {
		printf("-----------------------------------");
		printf("\nTidak ada data yang bisa diurutkan!");
		printf("\n-----------------------------------\n");	
		return;
	}
    for (int i = 0; i < totalIndex - 1; i++) {
        for (int j = 0; j < totalIndex - i - 1; j++) {
            if (inv[j].jumlah > inv[j+1].jumlah) {
                Item temp = inv[j];
                inv[j] = inv[j+1];
                inv[j+1] = temp;
            }
        }
    }
	printf("--------------------------------------");
	printf("\n[Sukses] Data diurutkan (Low to High)!");
	printf("\n--------------------------------------\n");
}

/* tulis ke file data.txt (write file)*/
void simpanData() {
    FILE *f = fopen("data.txt", "w");
    if (f == NULL) return;
    for (int i = 0; i < totalIndex; i++) {
        fprintf(f, "%s %lld\n", inv[i].nama, inv[i].jumlah);
    }
    fclose(f);
}

/* membaca file data.txt (read file) */
void muatData() {
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) return;
    while (totalIndex < 100 && fscanf(f, "%21s %lld", inv[totalIndex].nama, &inv[totalIndex].jumlah) == 2) { //validasi data (total index di bawah 100 dan 2 data terbaca (nama dan jumlah)
        totalIndex++;
    }
    fclose(f);
}

/* fungsi untuk menu awal (input pilihan */
void showMenu(){
	char input[3];
	while(1){ //pengulangan menu sampai keluar (input 7)
	    printf("===================================");
        printf("\n       INVENTORY MANAGEMENT   ");
        printf("\n===================================");
        printf("\n1. Tambah Barang");
        printf("\n2. Hapus Barang");
        printf("\n3. Edit Stok Barang");
        printf("\n4. Lihat Laporan Barang");
        printf("\n5. Urutkan Stok Barang (High to low)");
        printf("\n6. Urutkan Stok Barang (Low to high)");
        printf("\n7. Simpan & Keluar");
        printf("\n-----------------------------------");
        printf("\nPilih menu: ");
        //membaca input pilihan dalam bentuk string lalu diubah ke int
        scanf (" %2s", input);
        while (getchar() != '\n');
        
		if (!numValidation(input)) {
    		errMessage();
    		continue;
		}
		int pilihan = atoi(input);
		
        if (pilihan == 1) {
       		tambahItem(); //manggil function untuk tambah barang
        } 
        else if (pilihan == 2) {    	
			hapusItem(); //manggil function untuk hapus barang
        } 
        else if (pilihan == 3) {    	
			editStok(); //manggil function untuk edit stok
        } 
        else if (pilihan == 4) {    	
			lihatReport(); //manggil function untuk lihat report barang
        } 
        else if (pilihan == 5) { 
            urutDesc(); //manggil function untuk sort secara descending
        } 
        else if (pilihan == 6) {
            urutAsc(); //manggil function untuk sort secara ascnding
        } 
        else if (pilihan == 7) {
			exitProgram(); //manggil function untuk simpan data dan keluar
            return;
        } 
        else {
            errMessage(); //manggil function untuk show error message
        }
    }
}

/* kalo milih 1 (fitur tambah barang (nama dan jumlah stok barang))*/
void tambahItem(){
	// jika jumlah item di inventory mencapai 100 (maksimal), kembali ke menu awal	
	if (totalIndex == 100){
		printf ("\nBarang sudah mencapai batas maksimum");
		printf("\n-----------------------------------");
        printf ("\nTekan enter untuk coba lagi\n");
        	
        enterContinue();
        system(CLEAR);
        return;
	}
    	
		//input barang dan jumlah (minimal 1 dan angka)
    while(1){
        system(CLEAR);
		printf("===================================");
    	printf("\n       INVENTORY MANAGEMENT   ");
    	printf("\n===================================");
		printf("\nNama Barang (tanpa spasi dan maks 20 karakter) : "); scanf(" %21s", inv[totalIndex].nama); while(getchar() != '\n');
			
    	if (strlen(inv[totalIndex].nama) > 20) { // validasi jumlah karakter
        	printf ("\nNama barang terlalu panjang, coba lagi");
        	printf("\n-----------------------------------");
       		printf ("\nTekan enter untuk coba lagi\n");
       		 	
        	enterContinue();
        	continue;
		}
		break;
	}
		
	while(1){
        system(CLEAR);
		printf("===================================");
    	printf("\n       INVENTORY MANAGEMENT   ");
    	printf("\n===================================");
    	printf("\nNama Barang (tanpa spasi dan maks 20 karakter) : %s", inv[totalIndex].nama);
    		
        char jumlahStok[12];
        int index = cariBarang(inv[totalIndex].nama);
        printf("\nStok Barang (1-1.000.000.000 buah)             : "); scanf("%11s", jumlahStok); while(getchar() != '\n'); 
       	inv[totalIndex].jumlah = atoll(jumlahStok);
       		
	   	if (!numValidation(jumlahStok) || inv[totalIndex].jumlah < 1 || inv[totalIndex].jumlah > 1000000000) { //validasi jumlah stok
        	printf ("\nStok barang harus berupa angka di antara 1 sampai 1.000.000.000, coba lagi");
        	printf("\n-----------------------------------");
        	printf ("\nTekan enter untuk coba lagi\n");
        	
        	enterContinue();
        	continue;
		}
			
		//jika barang sudah ada, stok ditambahkan ke barang yang sudah ada (syarat dan ketentuan berlaku (jumlah stok))
		if (index == -1){
        	totalIndex++;
        	simpanData(); 	
        	printf("\n[Sukses] Data berhasil ditambah!");
        	printf("\n-----------------------------------");
        	printf ("\nTekan enter untuk kembali\n");
        	
			enterContinue();
			system(CLEAR);	
			break;
		}
		else if (inv[index].jumlah + inv[totalIndex].jumlah > 1000000000) {
    		printf("\nBarang sudah ada dan stok tidak bisa ditambahkan lagi, coba lagi");
    		printf("\n-----------------------------------");
        	printf ("\nTekan enter untuk coba lagi\n");
        			
    		enterContinue();	
    		continue;
		}
							
		else{
			inv[index].jumlah += inv[totalIndex].jumlah;
            printf("\nBarang sudah ada, stok ditambahkan ke barang tersebut");
        	printf("\n-----------------------------------");
        	printf ("\nTekan enter untuk kembali\n");
        		
			enterContinue();
			system(CLEAR);	
		}
		break;
	}
}

/* kalo milih 2 (fitur hapus barang dari data) */
void hapusItem() {
	while(1){
		system(CLEAR);
    	if (totalIndex == 0) {
		printf("-----------------------------------");
		printf("\n      Inventory masih kosong!");
		printf("\n-----------------------------------\n");	
        return;
    	}

    	char n[5];
		
		//menampilkan daftar barang
    	printf("===================================");
    	printf("\n       INVENTORY MANAGEMENT   ");
    	printf("\n===================================\n");
    	printf ("------------------------------------------------------");
    	printf("\n%-13s | %-20s | %-6s", "NO (MAKS 100)", "NAMA BARANG", "STOK");
    	printf("\n------------------------------------------------------");
    	for (int i = 0; i < totalIndex; i++) {
        	printf("\n%-13d | %-20s | %-6lld", i+1, inv[i].nama, inv[i].jumlah);
    	}
    	printf("\n------------------------------------------------------\n");
    	printf("Pilih nomor barang ('k' untuk kembali): ");
    	scanf(" %4s", n);
    	while(getchar() != '\n');
    	
    	//jika input 'k', maka kembali ke menu awal
    	if (strcmp(n,"k") == 0){
    		system(CLEAR);
    		return;	
		}
		
		int num = atoi(n);
		//jika barang tidak ada
		if (!numValidation(n) || num < 1 || num > totalIndex) {
    		printf("\nBarang tidak ditemukan, coba lagi");
       		printf("\n-----------------------------------");
        	printf ("\nTekan enter untuk coba lagi\n");
    		
    		enterContinue();
        	system(CLEAR);        	
    		continue;
		}

    	//geser data ke kiri
    	for (int i = num - 1; i < totalIndex - 1; i++) {
        	inv[i] = inv[i + 1];
    	}
    	
    	totalIndex--;
    	simpanData();
    	
    	printf("\n[Sukses] Barang berhasil dihapus!");
    	printf("\n-----------------------------------");
    	printf ("\nTekan enter untuk kembali\n");
    	
    	enterContinue();
    	system(CLEAR);
    	break;
		}
}

/* kalo milih 3 (fitur untuk edit jumlah stok barang di data) */
void editStok() {
    while (1) {
		system(CLEAR);
    	if (totalIndex == 0) {
		printf("-----------------------------------");
		printf("\n      Inventory masih kosong!");
		printf("\n-----------------------------------\n");	
        return;
    	}

        char n[5];
	
		//menampilkan daftar barang
        printf("===================================");
        printf("\n       INVENTORY MANAGEMENT   ");
        printf("\n===================================");
        printf("\n------------------------------------------------------");
        printf("\n%-13s | %-20s | %-6s", "NO (MAKS 100)", "NAMA BARANG", "STOK");
        printf("\n------------------------------------------------------");

        for (int i = 0; i < totalIndex; i++) {
            printf("\n%-13d | %-20s | %-6lld", i + 1, inv[i].nama, inv[i].jumlah);
        }	
        
		//input barang yang ingin diedit stoknya
        printf("\n------------------------------------------------------\n");
        printf("Pilih nomor barang ('k' untuk kembali): ");
        scanf(" %4s", n);
        while (getchar() != '\n');
        
		//jika input 'k', maka kembali ke menu awal
        if (strcmp(n, "k") == 0) {
            system(CLEAR);
            return;
        }
        
		int num = atoi(n);
		//jika barang tidak ada, coba lagi
		if (!numValidation(n) || num < 1 || num > totalIndex) {
    		printf("\nBarang tidak ditemukan, coba lagi");
       		printf("\n-----------------------------------");
        	printf ("\nTekan enter untuk coba lagi\n");
        	
    		enterContinue();
        	system(CLEAR);        	
    		continue;
		}
		
        char stokBaru[20];
        printf("\nMasukkan stok baru untuk %s: ", inv[num - 1].nama);
        scanf(" %19s", stokBaru);
        while(getchar() != '\n');
        
        if (!numValidation(stokBaru)) {
    		printf("\nStok harus berupa angka, coba lagi");
       		printf("\n-----------------------------------");
        	printf ("\nTekan enter untuk coba lagi\n");
    		
    		enterContinue();
        	system(CLEAR);        	
    		continue;
		}
		
		long long num2 = atoll(stokBaru);
        if (num2 < 1 || num2 > 1000000000) {
            printf("\nJumlah stok harus di antara 1 sampai 1.000.000.000, coba lagi");
            printf("\n-------------------------------------------------------------");
            printf("\nTekan enter untuk coba lagi\n");
            
			enterContinue();
            system(CLEAR);            
            continue;
        }
		
        inv[num - 1].jumlah = num2;
        simpanData();
	
        printf("\n[Sukses] Stok berhasil diperbarui!");
        printf("\n-----------------------------------");
        printf("\nTekan enter untuk kembali\n");
        
        enterContinue();
        system(CLEAR);
        break;
    }
}

/* kalo milih 4 (fitur lihat report yang terdiri dari list barang, stok, dan total barang (secara stok dan jenis) */
void lihatReport(){
		system(CLEAR);
    	if (totalIndex == 0) {
		printf("-----------------------------------");
		printf("\n      Inventory masih kosong!");
		printf("\n-----------------------------------\n");	
        return;
    	}
    	
		long long totalStok = 0;
		for (int i = 0; i < totalIndex; i++){
			totalStok+=inv[i].jumlah;
		}

		printf("===================================");
        printf("\n   INVENTORY MANAGEMENT   ");
        printf("\n===================================\n");
        printf ("------------------------------------------------------");
        printf("\n%-13s | %-20s | %-6s", "NO (MAKS 100)", "NAMA BARANG", "STOK");
        printf("\n------------------------------------------------------");
        for (int i = 0; i < totalIndex; i++) {
            printf("\n%-13d | %-20s | %-6lld", i+1, inv[i].nama, inv[i].jumlah);
        }
        printf("\n------------------------------------------------------");
        printf("\nSUMMARY:\n");
        printf("\nTotal Jenis Barang: %d", totalIndex);
        printf ("\nTotal Stok Barang: %lld", totalStok);
        printf("\n------------------------------------------------------");
		printf ("\nTekan enter untuk kembali\n");
		
		enterContinue();
		system(CLEAR);	
		return;
}

/*kalo milih 7 (fitur simpan dan keluar dari program)*/
void exitProgram (){
	simpanData(); /* manggil function untuk simpan data ke data.txt*/
	printf("\nData tersimpan. Have a great day!\n");
}

void errMessage(){
	system(CLEAR);
	printf("-----------------------------------");
	printf("\n   Pilihan tidak valid, coba lagi");
	printf("\n-----------------------------------\n");
}

int main() {
    muatData(); /* manggil function untuk load data dari data.tx ke program*/

	showMenu(); /*manggil function untuk show menu awal */
    return 0;
}
