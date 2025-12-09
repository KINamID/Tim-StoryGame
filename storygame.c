#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

void slowPrint(const char *text){
    while(*text){
        printf("%c", *text);
        fflush(stdout);
        Sleep(25);
        text++;
    }
}

void clearScreen(){
    system("cls");
}

void setColor(int c){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void puzzleGudang(){
    int pass;

    setColor(14);
    slowPrint("\nSebuah gembok tua tergantung...\n");
    slowPrint("Tertulis: 'Jumlah sisi pada dua benda yang identik'\n");
    slowPrint("Hint: Dadu?\n");

    setColor(15);
    printf("Masukkan password: ");
    scanf("%d", &pass);

    if(pass == 12) {
        setColor(10);
        slowPrint("Gembok terbuka!\n");
    } else {
        setColor(12);
        slowPrint("Password salah. Kamu gagal membuka gembok.\n");
    }
}

void puzzlePerpus(){
    int pass;

    setColor(14);
    slowPrint("\nDi rak buku, kamu menemukan sebuah soal matematika:\n");
    slowPrint("Diketahui:\n");
    slowPrint("f(x) = 2x + 8\n");
    slowPrint("g(x) = 4x - 8\n");
    slowPrint("Tentukan nilai dari (f o g)(3)\n");
    slowPrint("Hint: f(g(x))\n");

    setColor(15);
    printf("Masukkan Jawaban (angka): ");
    scanf("%d", &pass);

    if(pass == 16){   
        setColor(10);
        slowPrint("Rak bergerak terbuka...\n");
    } else {
        setColor(12);
        slowPrint("Jawaban salah.\n");
    }
}


void puzzleLorong() {
    char w1[10], w2[10], w3[10];

    // Jawaban benar
    char *c1 = "RED";
    char *c2 = "BLUE";
    char *c3 = "YELLOW";

    setColor(14);
    slowPrint("\nKamu melihat seseorang berlari ke lorong gelap...\n");
    slowPrint("Tiba-tiba tulisan samar muncul di dinding!\n\n");

    // Tampilkan kalimat dengan warna disisipkan
    setColor(15);
    slowPrint("\"Dia menuju ");
    setColor(12); slowPrint("RED");
    setColor(15); slowPrint(" ke arah utara lalu ");
    setColor(9);  slowPrint("BLUE");
    setColor(15); slowPrint(" menghilang ke tikungan ");
    setColor(14); slowPrint("YELLOW");
    setColor(15); slowPrint("...\"\n");

    Sleep(2200); // tampil 2 detik
    clearScreen(); // hilangkan petunjuk

    setColor(14);
    slowPrint("Tulisan itu menghilang...\n");
    slowPrint("Apa tiga warna yang kamu lihat?\n");
    slowPrint("Masukkan berurutan\n");

    setColor(15);
    printf("> ");
    scanf("%s %s %s", w1, w2, w3);

    if(strcmp(w1, c1) == 0 &&
       strcmp(w2, c2) == 0 &&
       strcmp(w3, c3) == 0)
    {
        setColor(10);
        slowPrint("\nBenar! Pintu listrik terbuka perlahan...\n");
    }
    else {
        setColor(12);
        slowPrint("\nSalah! Kamu tidak mengingatnya dengan benar.\n");
    }
}



int main(){
    int choice;

//CHAPTER 2
setColor(15);
slowPrint("Johan menyebut nama kakak pemain, Nina Fort\n");
setColor(15);
slowPrint("Pemain curiga bahwa Johan punya hubungan dengan keluarganya\n");

setColor(14);
slowPrint("\nMuncul beberapa lokasi investigasi:\n");
setColor(10);
slowPrint("1. Gudang Tua\n");
slowPrint("2. Perpustakaan Universitas\n");
slowPrint("3. Lorong bawah tanah stasiun Graybridge\n");

setColor(15);
 printf("\nYour choice: ");
 scanf("%d", &choice);
 clearScreen();

 switch(choice){
        case 1:
            puzzleGudang();
            break;

        case 2:
            puzzlePerpus();
            break;

        case 3:
            puzzleLorong();
            break;

        default:
            slowPrint("Pilihan tidak valid.\n");
    }
return 0;
}