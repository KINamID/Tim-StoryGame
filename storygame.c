#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

void slowPrint(const char *text){
    while(*text){
        printf("%c", *text);
        fflush(stdout);
        Sleep(25);
        text++;
    }
}

void setColor(int c){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main(){
    int choice;

//CHAPTER 21
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

return 0;
}