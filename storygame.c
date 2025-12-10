#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define MAX_CLUE 10
#define MAX_LEN 120

// VARIABEL
char playerName[50];
char clues[MAX_CLUE][MAX_LEN];
int clueCount = 0;
int solved = 0;
int failed = 0;
int totalPuzzles = 3;

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void setColor(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clearScreen()
{
    system("cls");
}

void resetColor()
{
#ifdef _WIN32
    setColor(7);
#else
    printf("\033[0m");
#endif
}

void slowPrint(const char *text)
{
    while (*text)
    {
        printf("%c", *text);
        fflush(stdout);
        Sleep(25);
        text++;
    }
}

void addClue(const char *text)
{
    if (clueCount < MAX_CLUE)
    {
        strncpy(clues[clueCount], text, MAX_LEN - 1);
        clues[clueCount][MAX_LEN - 1] = '\0';
        clueCount++;
    }
}

void showClue()
{
    setColor(11);
    printf("\n========== CLUE YANG SUDAH DIDAPAT ==========\n");
    resetColor();
    if (clueCount == 0)
    {
        printf("Belum ada clue yang kamu kumpulkan.\n");
    }
    else
    {
        for (int i = 0; i < clueCount; i++)
        {
            printf("%d. %s\n", i + 1, clues[i]);
        }
    }
    printf("=============================================\n\n");
}

void inputNama()
{
    int valid = 0;

    while (!valid)
    {
        setColor(10);
        printf("Masukkan nama detektifmu: ");
        resetColor();

        fgets(playerName, sizeof(playerName), stdin);

        // hapus newline
        size_t len = strlen(playerName);
        if (len > 0 && playerName[len - 1] == '\n')
            playerName[len - 1] = '\0';

        // validasi: cek apakah ada angka
        valid = 1;  // anggap valid dulu
        for (int i = 0; playerName[i] != '\0'; i++)
        {
            if (playerName[i] >= '0' && playerName[i] <= '9')
            {
                setColor(12);
                printf("Nama tidak boleh mengandung angka! Coba lagi.\n\n");
                resetColor();
                valid = 0; // invalid
                break;
            }
        }

        // jika hanya enter
        if (strlen(playerName) == 0)
        {
            setColor(12);
            printf("Nama tidak boleh kosong! Coba lagi.\n\n");
            resetColor();
            valid = 0;
        }
    }
}


void puzzleGudang()
{
    int pass;

    setColor(14);
    slowPrint("\nSebuah gembok tua tergantung...\n");
    slowPrint("Tertulis: 'Jumlah sisi pada dua benda yang identik'\n");
    slowPrint("Hint: Dadu?\n");

    setColor(15);
    printf("Masukkan password: ");
    scanf("%d", &pass);

    if (pass == 12)
    {
        setColor(10);
        slowPrint("Gembok terbuka!\n");
        solved++;
    }
    else
    {
        setColor(12);
        slowPrint("Password salah. Kamu gagal membuka gembok.\n");
        failed++;
    }
}

void puzzlePerpus()
{
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

    if (pass == 16)
    {
        setColor(10);
        slowPrint("Rak bergerak terbuka...\n");
        solved++;
    }
    else
    {
        setColor(12);
        slowPrint("Jawaban salah.\n");
        failed++;
    }
}

void puzzleLorong()
{
    char w1[10], w2[10], w3[10];

    // Jawaban benar
    char *c1 = "RED";
    char *c2 = "BLUE";
    char *c3 = "YELLOW";

    setColor(15);
    slowPrint("\nKamu melihat seseorang berlari ke lorong gelap...\n");
    slowPrint("Tiba-tiba tulisan samar muncul di dinding!\n\n");

    // Tampilkan kalimat dengan warna disisipkan
    setColor(15);
    slowPrint("\"Dia menuju ");
    setColor(12);
    slowPrint("RED");
    setColor(15);
    slowPrint(" ke arah utara lalu ");
    setColor(9);
    slowPrint("BLUE");
    setColor(15);
    slowPrint(" menghilang ke tikungan ");
    setColor(14);
    slowPrint("YELLOW");
    setColor(15);
    slowPrint("...\"\n");

    Sleep(2200);   // tampil 2 detik
    clearScreen(); // hilangkan petunjuk

    setColor(14);
    slowPrint("Tulisan itu menghilang...\n");
    slowPrint("Apa tiga warna yang kamu lihat?\n");
    slowPrint("Masukkan berurutan\n");

    setColor(15);
    printf("> ");
    scanf("%s %s %s", w1, w2, w3);

    if (strcmp(w1, c1) == 0 &&
        strcmp(w2, c2) == 0 &&
        strcmp(w3, c3) == 0)
    {
        setColor(10);
        slowPrint("\nBenar! Pintu listrik terbuka perlahan...\n");
        solved++;
    }
    else
    {
        setColor(12);
        slowPrint("\nSalah! Kamu tidak mengingatnya dengan benar.\n");
        failed++;
    }
}

int puzzle(int id)
{
    int jawabanAngka;
    char jawabanText[50];

    switch (id)
    {
    case 1:
        setColor(14);
        slowPrint("\nJohan meninggalkan kode angka di dinding:\n");
        slowPrint("  3  6  9  12  ?\n");
        resetColor();
        printf("Tebak angka berikutnya: ");
        scanf("%d", &jawabanAngka);
        clearInputBuffer();
        if (jawabanAngka == 15)
        {
            setColor(10);
            printf("Benar! Kamu menyadari itu adalah deret kelipatan 3.\n");
            resetColor();
            addClue("Deret angka -> Johan suka pola matematika sederhana namun menipu.");
            solved++;
            return 1;
        }
        else
        {
            setColor(12);
            printf("Salah. Johan mengirim pesan:\n");
            resetColor();
            slowPrint("\"Bahkan kakakmu pun bisa melakukannya lebih baik.\"\n");
            failed++;
            return 0;
        }

    case 2:
        setColor(14);
        slowPrint("\nDi salah satu lokasi, kamu menemukan laptop terkunci.\n");
        slowPrint("Petunjuk di layar: 'Orang yang selalu kau cari'.\n");
        resetColor();
        printf("Masukkan password (nama, huruf besar-kecil tidak masalah): ");
        fgets(jawabanText, sizeof(jawabanText), stdin);
        // hapus newline
        {
            size_t len = strlen(jawabanText);
            if (len > 0 && jawabanText[len - 1] == '\n')
                jawabanText[len - 1] = '\0';
        }
        // ubah ke huruf besar semua utk dibandingkan
        for (int i = 0; jawabanText[i]; i++)
        {
            if (jawabanText[i] >= 'a' && jawabanText[i] <= 'z')
                jawabanText[i] = jawabanText[i] - 'a' + 'A';
        }
        if (strcmp(jawabanText, "NINA") == 0)
        {
            setColor(10);
            printf("Password benar. File rahasia terbuka...\n");
            resetColor();
            addClue("Nama 'Nina Fort' terus muncul di setiap berkas Johan.");
            solved++;
            return 1;
        }
        else
        {
            setColor(12);
            printf("Password salah. File terhapus otomatis.\n");
            resetColor();
            failed++;
            return 0;
        }

    case 3:
        slowPrint("\nKamu dan Michael mengejar Johan menuju stasiun Graybridge.\n");
        slowPrint("Di tembok, ada pesan: 'Tiga jalan, hanya satu yang selamat.'\n");
        setColor(14);
        printf("Pilih jalur:\n");
        printf("1. Lorong kiri yang gelap\n");
        printf("2. Tangga menuju atap\n");
        printf("3. Terowongan service sempit\n");
        resetColor();
        printf("Pilihanmu (1/2/3): ");
        scanf("%d", &jawabanAngka);
        clearInputBuffer();
        if (jawabanAngka == 2)
        {
            setColor(10);
            printf("Kamu memilih atap. Dari sana kamu melihat pola lampu yang membentuk koordinat.\n");
            resetColor();
            addClue("Koordinat persembunyian Johan terlihat dari atap stasiun.");
            solved++;
            return 1;
        }
        else
        {
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

void chapter1()
{
    setColor(13);
    printf("\n============== CHAPTER 1: AWAL MISTERI ==============\n");
    resetColor();
    slowPrint("Kota Graybridge sedang merayakan ulang tahun ke-20 Akademi Kepolisian.\n");
    slowPrint("Namun di tengah keramaian, sebuah pesan misterius muncul di kantor polisi...\n\n");

    slowPrint("\"Waktu kalian hampir habis. Selesaikan teka-teki ini, atau Graybridge kehilangan nyawanya.\"\n");
    slowPrint("Pesan itu ditandatangani oleh seseorang bernama sandi: 'Johan'.\n\n");

    slowPrint("Kamu detektif baru bernama ");
    slowPrint(playerName);
    slowPrint(", dipanggil bersama partner-mu Michael.\n\n");

    slowPrint("Michael: \"Kelihatannya si Johan ini bukan orang biasa. Lihat kodenya di TKP pertama.\"\n");

    puzzle(1);

    char lihat;
    printf("\nIngin melihat semua clue yang sudah kamu kumpulkan? (y/n): ");
    scanf(" %c", &lihat);
    clearInputBuffer();
    if (lihat == 'y' || lihat == 'Y')
    {
        showClue();
    }
}

void chapter2()
{
    int pilihan;
    setColor(13);
    printf("\n============== CHAPTER 2: PETUNJUK MASA LALU ==============\n");
    resetColor();

    slowPrint("Beberapa hari kemudian, Johan mulai menyebut nama yang sangat kamu kenal...\n");
    slowPrint("\"Nina Fort\" - nama kakakmu yang hilang 10 tahun lalu.\n\n");

    slowPrint("Michael: \"Kenapa dia tahu soal Nina? Ini sudah pribadi, ");
    slowPrint(playerName);
    slowPrint(".\"\n\n");

    setColor(15);
    slowPrint("\nMuncul beberapa lokasi investigasi:\n");
    setColor(14);
    slowPrint("1. Gudang Tua\n");
    slowPrint("2. Perpustakaan Universitas\n");
    slowPrint("3. Lorong bawah tanah stasiun Graybridge\n");

    setColor(15);
    printf("\nYour choice: ");
    scanf("%d", &pilihan);
    clearScreen();

    switch (pilihan)
    {
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

    char lihat;
    printf("\nIngin melihat semua clue lagi? (y/n): ");
    scanf(" %c", &lihat);
    clearInputBuffer();
    if (lihat == 'y' || lihat == 'Y')
    {
        showClue();
    }
}

void chapter3()
{
    setColor(13);
    printf("\n============== CHAPTER 3: KONFRONTASI ==============\n");
    resetColor();

    slowPrint("Dari semua petunjuk, kamu menyatukan pola yang Johan tinggalkan.\n");
    slowPrint("Deret angka, nama Nina, dan koordinat tersembunyi di lampu-lampu kota.\n");

    slowPrint("Akhirnya, kamu menemukan sebuah kode besar yang mengarah ke satu titik: persembunyian Johan.\n\n");

    puzzle(3);

    slowPrint("\nKamu dan Michael bergegas menuju lokasi yang ditunjukkan koordinat.\n");
    slowPrint("Namun saat tiba, ruangan itu kosong.\n");
    slowPrint("Yang tersisa hanya sebuah rekaman suara dan foto lama.\n\n");

    slowPrint("Rekaman Johan: \"Kebenaran selalu dekat denganmu, ");
    slowPrint(playerName);
    slowPrint(". Kau hanya belum melihatnya.\"\n");

    slowPrint("Kamu menemukan foto dirimu dan Nina saat kecil...\n");
    slowPrint("Di belakang foto, ada tanda tangan: 'Johan'.\n\n");
    addClue("Foto masa kecil dengan tanda tangan 'Johan' -> identitas Johan terkait langsung dengan Nina.");
}

void endingTrue()
{
    setColor(10);
    printf("\n============== TRUE ENDING: 'THE GENIUS' ==============\n");
    resetColor();

    slowPrint("Di ruangan tersembunyi berikutnya, kamu akhirnya bertemu sosok di balik nama 'Johan'.\n");
    slowPrint("Saat ia menoleh, jantungmu berhenti sejenak.\n");
    slowPrint("Itu adalah... Nina Fort, kakakmu sendiri.\n\n");

    slowPrint("Nina: \"Butuh waktu lama juga ya, ");
    slowPrint(playerName);
    slowPrint(".\"\n");

    slowPrint("Nina menjelaskan bahwa ia tidak mati.\n");
    slowPrint("Ia menghilang karena terlibat dalam eksperimen rahasia pemerintah di Graybridge.\n");
    slowPrint("Menggunakan nama sandi 'Johan', ia menciptakan rangkaian puzzle untuk menguji kejeniusannmu.\n\n");

    slowPrint("\"Aku tidak ingin kau mati sebelum siap.\"\n");
    slowPrint("\"Semua ini hanya latihan sebelum kita membuka konspirasi yang jauh lebih besar.\"\n\n");

    slowPrint("Kamu menatap cahaya di ujung koridor, menyadari bahwa ini baru awal.\n");
    setColor(12);
    slowPrint("== TO BE CONTINUED ==\n");
}

void endingFalse()
{
    setColor(12);
    printf("\n============== FALSE ENDING: 'NOT ENOUGH' ==============\n");
    resetColor();

    slowPrint("Kamu kembali ke ruangan persembunyian itu beberapa jam terlambat.\n");
    slowPrint("Ruangan sudah kosong. Tak ada rekaman, tak ada jejak.\n\n");

    slowPrint("Di tengah ruangan hanya ada sebuah surat.\n\n");
    slowPrint("\"Sayang sekali. Kau tidak cukup layak. Graybridge butuh detektif yang lebih baik.\"\n");
    slowPrint("\"Jangan khawatir, permainan belum berakhir. Hanya saja bukan untukmu.\"\n\n");

    slowPrint("Johan menghilang. Kasus-kasus aneh tetap bermunculan di Graybridge.\n");
    slowPrint("Kamu gagal... dan rasa bersalah itu menghantuimu.\n\n");

    setColor(12);
    slowPrint("== BAD ENDING ==\n");
}

int main()
{
    setColor(13);
    printf("=====================================================\n");
    printf("                 THE GENIUS - TEXT GAME              \n");
    printf("            Tugas UAS Dasar-Dasar Pemrograman        \n");
    printf("=====================================================\n\n");
    resetColor();

    inputNama();

    slowPrint("\nSelamat datang di Graybridge, ");
    slowPrint(playerName);
    slowPrint(".\n");
    slowPrint("Kamu adalah detektif baru dengan masa lalu yang kelam...\n");

    printf("\nTekan ENTER untuk memulai cerita...");
    getchar();
    clearScreen();

    chapter1();
    chapter2();
    chapter3();

    printf("\n================= RANGKUMAN PERFORMA =================\n");
    printf("Puzzle terpecahkan : %d\n", solved);
    printf("Puzzle gagal       : %d\n", failed);
    printf("======================================================\n");

    if (solved == totalPuzzles)
    {
        endingTrue();
    }
    else
    {
        endingFalse();
    }

    setColor(14);
    printf("\nTerima kasih sudah memainkan 'The Genius'.\n");
    return 0;
}