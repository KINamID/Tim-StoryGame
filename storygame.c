#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define MAX_CLUE 10
#define MAX_LEN  120

char playerName[50];
char clues[MAX_CLUE][MAX_LEN];
int clueCount = 0;
int solved = 0;
int failed = 0;
int totalPuzzles = 3;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void setColor(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    printf("\033[0;%dm", color);
#endif
}

void resetColor() {
#ifdef _WIN32
    setColor(7);
#else
    printf("\033[0m");
#endif
}

void slowPrint(const char *text, int delayMs) {
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
#ifdef _WIN32
        Sleep(delayMs);
#else
        usleep(delayMs * 1000);
#endif
    }
}

void addClue(const char *text) {
    if (clueCount < MAX_CLUE) {
        strncpy(clues[clueCount], text, MAX_LEN - 1);
        clues[clueCount][MAX_LEN - 1] = '\0';
        clueCount++;
    }
}

void showClue() {
    setColor(11);
    printf("\n========== CLUE YANG SUDAH DIDAPAT ==========\n");
    resetColor();
    if (clueCount == 0) {
        printf("Belum ada clue yang kamu kumpulkan.\n");
    } else {
        for (int i = 0; i < clueCount; i++) {
            printf("%d. %s\n", i + 1, clues[i]);
        }
    }
    printf("=============================================\n\n");
}

void inputNama() {
    setColor(10);
    printf("Masukkan nama detektifmu: ");
    resetColor();
    fgets(playerName, sizeof(playerName), stdin);
    size_t len = strlen(playerName);
    if (len > 0 && playerName[len - 1] == '\n') {
        playerName[len - 1] = '\0';
    }
}

int puzzle(int id) {
    int jawabanAngka;
    char jawabanText[50];

    switch (id) {
        case 1:
            slowPrint("\n[Puzzle 1] Johan meninggalkan kode angka di dinding:\n", 20);
            slowPrint("  3  6  9  12  ?\n", 40);
            printf("Tebak angka berikutnya: ");
            scanf("%d", &jawabanAngka);
            clearInputBuffer();
            if (jawabanAngka == 15) {
                setColor(10);
                printf("Benar! Kamu menyadari itu adalah deret kelipatan 3.\n");
                resetColor();
                addClue("Deret angka -> Johan suka pola matematika sederhana namun menipu.");
                solved++;
                return 1;
            } else {
                setColor(12);
                printf("Salah. Johan mengirim pesan:\n");
                resetColor();
                slowPrint("\"Bahkan kakakmu pun bisa melakukannya lebih baik.\"\n", 25);
                failed++;
                return 0;
            }

        case 2:
            slowPrint("\n[Puzzle 2] Di salah satu lokasi, kamu menemukan laptop terkunci.\n", 20);
            slowPrint("Petunjuk di layar: 'Orang yang selalu kau cari'.\n", 20);
            printf("Masukkan password (nama, huruf besar-kecil tidak masalah): ");
            fgets(jawabanText, sizeof(jawabanText), stdin);
            {
                size_t len = strlen(jawabanText);
                if (len > 0 && jawabanText[len - 1] == '\n') jawabanText[len - 1] = '\0';
            }
            for (int i = 0; jawabanText[i]; i++) {
                if (jawabanText[i] >= 'a' && jawabanText[i] <= 'z')
                    jawabanText[i] = jawabanText[i] - 'a' + 'A';
            }
            if (strcmp(jawabanText, "NINA") == 0) {
                setColor(10);
                printf("Password benar. File rahasia terbuka...\n");
                resetColor();
                addClue("Nama 'Nina Fort' terus muncul di setiap berkas Johan.");
                solved++;
                return 1;
            } else {
                setColor(12);
                printf("Password salah. File terhapus otomatis.\n");
                resetColor();
                failed++;
                return 0;
            }

        case 3:
            slowPrint("\n[Puzzle 3] Kamu dan Michael mengejar Johan menuju stasiun Graybridge.\n", 20);
            slowPrint("Di tembok, ada pesan: 'Tiga jalan, hanya satu yang selamat.'\n", 20);
            printf("Pilih jalur:\n");
            printf("1. Lorong kiri yang gelap\n");
            printf("2. Tangga menuju atap\n");
            printf("3. Terowongan service sempit\n");
            printf("Pilihanmu (1/2/3): ");
            scanf("%d", &jawabanAngka);
            clearInputBuffer();
            if (jawabanAngka == 2) {
                setColor(10);
                printf("Kamu memilih atap. Dari sana kamu melihat pola lampu yang membentuk koordinat.\n");
                resetColor();
                addClue("Koordinat persembunyian Johan terlihat dari atap stasiun.");
                solved++;
                return 1;
            } else {
                setColor(12);
                printf("Pilihanmu membuat pengejaran melambat. Johan semakin jauh.\n");
                resetColor();
                failed++;
                return 0;
            }

        default:
            return 0;
    }
}

void chapter1() {
    setColor(11);
    printf("\n============== CHAPTER 1: AWAL MISTERI ELOK ==============\n");
    resetColor();
    slowPrint("Kota Graybridge sedang merayakan ulang tahun ke-20 Akademi Kepolisian.\n", 15);
    slowPrint("Namun di tengah keramaian, sebuah pesan misterius muncul di kantor polisi...\n\n", 15);

    slowPrint("\"Waktu kalian hampir habis. Selesaikan teka-teki ini, atau Graybridge kehilangan nyawanya.\"\n", 20);
    slowPrint("Pesan itu ditandatangani oleh seseorang bernama sandi: 'Johan'.\n\n", 20);

    slowPrint("Kamu, detektif baru bernama ", 15);
    slowPrint(playerName, 15);
    slowPrint(", dipanggil bersama partner-mu, Michael.\n\n", 15);

    slowPrint("Michael: \"Kelihatannya si Johan ini bukan orang biasa. Lihat kodenya di TKP pertama.\"\n", 15);

    puzzle(1);

    char lihat;
    printf("\nIngin melihat semua clue yang sudah kamu kumpulkan? (y/n): ");
    scanf(" %c", &lihat);
    clearInputBuffer();
    if (lihat == 'y' || lihat == 'Y') {
        showClue();
    }
}

void chapter2() {
    int pilihan;
    setColor(11);
    printf("\n============== CHAPTER 2: PETUNJUK MASA LALU ==============\n");
    resetColor();

    slowPrint("Beberapa hari kemudian, Johan mulai menyebut nama yang sangat kamu kenal...\n", 15);
    slowPrint("\"Nina Fort\" - nama kakakmu yang hilang 10 tahun lalu.\n\n", 20);

    slowPrint("Michael: \"Kenapa dia tahu soal Nina? Ini sudah pribadi, ", 15);
    slowPrint(playerName, 15);
    slowPrint(".\"\n\n", 15);

    slowPrint("Kamu dan Michael memutuskan untuk menyelidiki beberapa lokasi:\n", 15);
    printf("1. Gudang tua di pinggir kota\n");
    printf("2. Perpustakaan Universitas Graybridge\n");
    printf("3. Lorong bawah tanah stasiun Graybridge\n");
    printf("Pilih lokasi pertama yang ingin kamu datangi (1-3): ");
    scanf("%d", &pilihan);
    clearInputBuffer();

    switch (pilihan) {
        case 1:
            slowPrint("\nKamu memasuki gudang tua yang berdebu.\n", 15);
            slowPrint("Di sudut ruangan, ada papan tulis penuh angka dan nama 'Nina'.\n", 15);
            break;
        case 2:
            slowPrint("\nDi perpustakaan, kamu menemukan rak khusus tentang kriptografi dan kode rahasia.\n", 15);
            slowPrint("Sebuah buku terbuka dengan catatan tangan bertuliskan 'Fort Project'.\n", 15);
            break;
        case 3:
        default:
            slowPrint("\nLorong bawah tanah dipenuhi suara langkah bergema.\n", 15);
            slowPrint("Di dinding, ada poster lama Akademi Kepolisian dengan tanda silang pada foto angkatan Nina.\n", 15);
            break;
    }

    puzzle(2);

    char lihat;
    printf("\nIngin melihat semua clue lagi? (y/n): ");
    scanf(" %c", &lihat);
    clearInputBuffer();
    if (lihat == 'y' || lihat == 'Y') {
        showClue();
    }
}

void chapter3() {
    setColor(11);
    printf("\n============== CHAPTER 3: KONFRONTASI ==============\n");
    resetColor();

    slowPrint("Dari semua petunjuk, kamu menyatukan pola yang Johan tinggalkan.\n", 15);
    slowPrint("Deret angka, nama Nina, dan koordinat tersembunyi di lampu-lampu kota.\n", 15);

    slowPrint("Akhirnya, kamu menemukan sebuah kode besar yang mengarah ke satu titik: persembunyian Johan.\n\n", 15);

    puzzle(3);

    slowPrint("\nKamu dan Michael bergegas menuju lokasi yang ditunjukkan koordinat.\n", 15);
    slowPrint("Namun saat tiba, ruangan itu kosong.\n", 15);
    slowPrint("Yang tersisa hanya sebuah rekaman suara dan foto lama.\n\n", 15);

    slowPrint("Rekaman Johan: \"Kebenaran selalu dekat denganmu, ", 20);
    slowPrint(playerName, 20);
    slowPrint(". Kau hanya belum melihatnya.\"\n", 20);

    slowPrint("Kamu menemukan foto dirimu dan Nina saat kecil...\n", 15);
    slowPrint("Di belakang foto, ada tanda tangan: 'Johan'.\n\n", 15);
    addClue("Foto masa kecil dengan tanda tangan 'Johan' -> identitas Johan terkait langsung dengan Nina.");
}

void endingTrue() {
    setColor(10);
    printf("\n============== TRUE ENDING: 'THE GENIUS' ==============\n");
    resetColor();

    slowPrint("Di ruangan tersembunyi berikutnya, kamu akhirnya bertemu sosok di balik nama 'Johan'.\n", 15);
    slowPrint("Saat ia menoleh, jantungmu berhenti sejenak.\n", 15);
    slowPrint("Itu adalah... Nina Fort, kakakmu sendiri.\n\n", 20);

    slowPrint("Nina: \"Butuh waktu lama juga ya, ", 20);
    slowPrint(playerName, 20);
    slowPrint(".\"\n", 20);

    slowPrint("Nina menjelaskan bahwa ia tidak mati.\n", 15);
    slowPrint("Ia menghilang karena terlibat dalam eksperimen rahasia pemerintah di Graybridge.\n", 15);
    slowPrint("Menggunakan nama sandi 'Johan', ia menciptakan rangkaian puzzle untuk menguji kejeniusannmu.\n\n", 15);

    slowPrint("\"Aku tidak ingin kau mati sebelum siap.\"\n", 20);
    slowPrint("\"Semua ini hanya latihan sebelum kita membuka konspirasi yang jauh lebih besar.\"\n\n", 20);

    slowPrint("Kamu menatap cahaya di ujung koridor, menyadari bahwa ini baru awal.\n", 15);
    slowPrint("== TO BE CONTINUED ==\n", 40);
}

void endingFalse() {
    setColor(12);
    printf("\n============== FALSE ENDING: 'NOT ENOUGH' ==============\n");
    resetColor();

    slowPrint("Kamu kembali ke ruangan persembunyian itu beberapa jam terlambat.\n", 15);
    slowPrint("Ruangan sudah kosong. Tak ada rekaman, tak ada jejak.\n\n", 15);

    slowPrint("Di tengah ruangan hanya ada sebuah surat.\n\n", 15);
    slowPrint("\"Sayang sekali. Kau tidak cukup layak. Graybridge butuh detektif yang lebih baik.\"\n", 20);
    slowPrint("\"Jangan khawatir, permainan belum berakhir. Hanya saja bukan untukmu.\"\n\n", 20);

    slowPrint("Johan menghilang. Kasus-kasus aneh tetap bermunculan di Graybridge.\n", 15);
    slowPrint("Kamu gagal... dan rasa bersalah itu menghantuimu.\n\n", 15);

    slowPrint("== BAD ENDING ==\n", 40);
}

int main() {
    setColor(11);
    printf("=====================================================\n");
    printf("                 THE GENIUS - TEXT GAME              \n");
    printf("            Tugas UAS Dasar-Dasar Pemrograman        \n");
    printf("=====================================================\n\n");
    resetColor();

    inputNama();

    slowPrint("\nSelamat datang di Graybridge, ", 15);
    slowPrint(playerName, 15);
    slowPrint(".\n", 15);
    slowPrint("Kamu adalah detektif baru dengan masa lalu yang kelam...\n", 15);

    printf("\nTekan ENTER untuk memulai cerita...");
    getchar();

    chapter1();
    chapter2();
    chapter3();

    printf("\n================= RANGKUMAN PERFORMA =================\n");
    printf("Puzzle terpecahkan : %d\n", solved);
    printf("Puzzle gagal       : %d\n", failed);
    printf("======================================================\n");

    if (solved == totalPuzzles) {
        endingTrue();
    } else {
        endingFalse();
    }

    printf("\nTerima kasih sudah memainkan 'The Genius'.\n");
    return 0;
}
