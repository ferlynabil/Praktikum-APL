#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <cctype>

using namespace std;

struct DataTeknis {
    float     ratingPemain;
    long long hargaPasarUSD;
    int       jumlahPenilai;
    float     totalSkorRating;
};

struct PemainMU {
    string    namaLengkap;
    string    klubAsal;
    string    negaraAsal;
    DataTeknis performa;
};

struct AkunPengguna {
    string username;
    string password;
    string peran;
};

const int MAKSIMAL_DATA = 100;
const int MAKSIMAL_AKUN = 50;

PemainMU     daftarPemain[MAKSIMAL_DATA];
AkunPengguna databaseAkun[MAKSIMAL_AKUN];
int jumlahDataPemain = 0;
int jumlahAkun       = 0;

void cetakGaris(char karakter, int lebar) {
    cout << setfill(karakter) << setw(lebar) << karakter << setfill(' ') << endl;
}

PemainMU* getPemainByIndex(PemainMU daftarPemain[], int jumlahPemain, int indeks) {
    if (indeks < 0 || indeks >= jumlahPemain) return nullptr;
    return &daftarPemain[indeks];
}

void terapkanHargaBaru(long long *hargaPasarTarget, long long hargaBaru) {
    cout << "\n  [Pointer] Alamat memori harga asli : " << hargaPasarTarget << endl;
    *hargaPasarTarget = hargaBaru;
    cout << "  [Pointer] Harga berhasil diubah via dereference ke: $" << *hargaPasarTarget << endl;
}

void hitungUlangRating(float *totalSkorTarget,
                       int   *jumlahPenilaiTarget,
                       float *ratingPemainTarget,
                       float  skorBaru) {
    *totalSkorTarget     += skorBaru;
    *jumlahPenilaiTarget += 1;
    *ratingPemainTarget   = *totalSkorTarget / (float)(*jumlahPenilaiTarget);
}

void bubbleSortNamaDescending(PemainMU daftarPemain[], int jumlahPemain) {
    bool adaPertukaran;
    for (int lintasan = 0; lintasan < jumlahPemain - 1; lintasan++) {
        adaPertukaran = false;
        for (int posisi = 0; posisi < jumlahPemain - lintasan - 1; posisi++) {
            if (daftarPemain[posisi].namaLengkap < daftarPemain[posisi + 1].namaLengkap) {
                PemainMU pemainSementara    = daftarPemain[posisi];
                daftarPemain[posisi]        = daftarPemain[posisi + 1];
                daftarPemain[posisi + 1]    = pemainSementara;
                adaPertukaran = true;
            }
        }
        if (adaPertukaran == false) break;
    }
}

void selectionSortHargaAscending(PemainMU daftarPemain[], int jumlahPemain) {
    for (int posisiAwal = 0; posisiAwal < jumlahPemain - 1; posisiAwal++) {
        int indeksHargaTerkecil = posisiAwal;
        for (int pembanding = posisiAwal + 1; pembanding < jumlahPemain; pembanding++) {
            if (daftarPemain[pembanding].performa.hargaPasarUSD <
                daftarPemain[indeksHargaTerkecil].performa.hargaPasarUSD) {
                indeksHargaTerkecil = pembanding;
            }
        }
        if (indeksHargaTerkecil != posisiAwal) {
            PemainMU pemainSementara           = daftarPemain[posisiAwal];
            daftarPemain[posisiAwal]           = daftarPemain[indeksHargaTerkecil];
            daftarPemain[indeksHargaTerkecil]  = pemainSementara;
        }
    }
}

void insertionSortRatingDescending(PemainMU daftarPemain[], int jumlahPemain) {
    for (int indeksKunci = 1; indeksKunci < jumlahPemain; indeksKunci++) {
        PemainMU pemainKunci = daftarPemain[indeksKunci];
        int posisiGeser      = indeksKunci - 1;
        while (posisiGeser >= 0 &&
               daftarPemain[posisiGeser].performa.ratingPemain < pemainKunci.performa.ratingPemain) {
            daftarPemain[posisiGeser + 1] = daftarPemain[posisiGeser];
            posisiGeser--;
        }
        daftarPemain[posisiGeser + 1] = pemainKunci;
    }
}

void linearSearchNama(PemainMU *daftarPemain, int *jumlahPemain, string keyword) {
    
    string keyLower = keyword;
    for (char &c : keyLower) c = (char)tolower((unsigned char)c);

    cout << "\n  [*] Alamat pointer daftarPemain  : " << daftarPemain << endl;
    cout << "  [*] Alamat pointer jumlahPemain  : " << jumlahPemain  << endl;
    cout << "  [*] Nilai jumlahPemain via deref : " << *jumlahPemain << " pemain" << endl;

    cout << "\n--- HASIL LINEAR SEARCH ---" << endl;
    cout << "Kata kunci : \"" << keyword << "\"" << endl;
    cout << "Proses     : Menelusuri setiap data satu per satu..." << endl;
    cetakGaris('=', 78);
    cout << left << setw(5)  << "No"
         << setw(5)  << "Idx"
         << setw(26) << "Nama Pemain"
         << setw(20) << "Klub Asal"
         << setw(10) << "Rating"
         << setw(12) << "Harga (USD)" << endl;
    cetakGaris('-', 78);

    int jumlahHasil = 0;
    for (int i = 0; i < *jumlahPemain; i++) {
        
        PemainMU *pemainPtr = (daftarPemain + i);

        string namaLower = pemainPtr->namaLengkap;
        for (char &c : namaLower) c = (char)tolower((unsigned char)c);

        
        if (namaLower.find(keyLower) != string::npos) {
            jumlahHasil++;
            cout << left << setw(5)  << jumlahHasil
                 << setw(5)  << i
                 << setw(26) << pemainPtr->namaLengkap
                 << setw(20) << pemainPtr->klubAsal
                 << setw(10) << fixed << setprecision(1)
                 << pemainPtr->performa.ratingPemain
                 << "$" << pemainPtr->performa.hargaPasarUSD << endl;
        }
    }

    cetakGaris('=', 78);
    if (jumlahHasil == 0) {
        cout << "  [!] Tidak ada pemain dengan nama yang mengandung \""
             << keyword << "\"" << endl;
    } else {
        cout << "  [OK] Ditemukan " << jumlahHasil << " pemain." << endl;
    }
}

int binarySearchHarga(PemainMU *sortedArr, int *jumlahPemain, long long *targetHarga) {
    int low  = 0;
    int high = *jumlahPemain - 1;
    int iterasi = 0;

    cout << "\n  [*] Alamat pointer sortedArr     : " << sortedArr    << endl;
    cout << "  [*] Alamat pointer jumlahPemain  : " << jumlahPemain  << endl;
    cout << "  [*] Alamat pointer targetHarga   : " << targetHarga   << endl;
    cout << "  [*] Nilai targetHarga via deref  : $" << *targetHarga << endl;

    cout << "\nProses Binary Search (divide and conquer):" << endl;
    cetakGaris('-', 50);

    while (low <= high) {
        int mid = low + (high - low) / 2;
        iterasi++;

        cout << "  Iterasi " << iterasi
             << " | low=" << low << " mid=" << mid << " high=" << high
             << " | Cek: $" << (sortedArr + mid)->performa.hargaPasarUSD << endl;

        if ((sortedArr + mid)->performa.hargaPasarUSD == *targetHarga) {
            cout << "  >> MATCH ditemukan di indeks " << mid << "!" << endl;
            return mid;
        } else if ((sortedArr + mid)->performa.hargaPasarUSD < *targetHarga) {
            low = mid + 1;
            cout << "  >> Target lebih besar, geser ke kanan (low = " << low << ")" << endl;
        } else {
            high = mid - 1;
            cout << "  >> Target lebih kecil, geser ke kiri (high = " << high << ")" << endl;
        }
    }
    return -1; 
}

void menuSearchingAdmin(PemainMU daftarPemain[], int jumlahPemain) {
    system("cls");
    cout << "========================================" << endl;
    cout << "       MENU SEARCHING DATA PEMAIN       " << endl;
    cout << "========================================" << endl;

    if (jumlahPemain == 0) {
        cout << "Belum ada data pemain di skuad!" << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }

    cout << "1. Linear Search   - Cari Nama Pemain (O(n))"         << endl;
    cout << "2. Binary Search   - Cari Harga Pasar USD (O(log n))" << endl;
    cout << "3. Kembali"                                            << endl;
    cout << "----------------------------------------" << endl;
    cout << "INFO: Binary Search memerlukan data terurut." << endl;
    cout << "      Salinan data akan diurutkan otomatis." << endl;
    cout << "----------------------------------------" << endl;

    int pilihanSearch;
    cout << "Pilih metode: "; cin >> pilihanSearch;

    if (pilihanSearch == 3) return;

    
    if (pilihanSearch == 1) {
        string keyword;
        cin.ignore();
        cout << "\nMasukkan nama yang dicari: ";
        getline(cin, keyword);

        system("cls");
        cout << "========================================" << endl;
        cout << "   LINEAR SEARCH - Pencarian Nama       " << endl;
        cout << "========================================" << endl;
        cout << "Algoritma : Menelusuri data satu per satu" << endl;
        cout << "Kompleksitas : O(n)" << endl;

        
        linearSearchNama(daftarPemain, &jumlahPemain, keyword);

    
    } else if (pilihanSearch == 2) {
        long long targetHarga;
        cout << "\nMasukkan harga yang dicari (USD): $";
        cin >> targetHarga;

        system("cls");
        cout << "========================================" << endl;
        cout << "  BINARY SEARCH - Pencarian Harga USD   " << endl;
        cout << "========================================" << endl;
        cout << "Algoritma    : Divide and Conquer" << endl;
        cout << "Kompleksitas : O(log n)" << endl;
        cout << "Syarat       : Data harus terurut (sorted)" << endl;

        
        PemainMU sortedPemain[MAKSIMAL_DATA];
        for (int i = 0; i < jumlahPemain; i++) {
            sortedPemain[i] = daftarPemain[i];
        }
        
        for (int i = 0; i < jumlahPemain - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < jumlahPemain; j++) {
                if (sortedPemain[j].performa.hargaPasarUSD <
                    sortedPemain[minIdx].performa.hargaPasarUSD) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                PemainMU tmp    = sortedPemain[i];
                sortedPemain[i] = sortedPemain[minIdx];
                sortedPemain[minIdx] = tmp;
            }
        }

        cout << "\n--- Data Salinan Setelah Diurutkan (Harga Ascending) ---" << endl;
        cetakGaris('=', 75);
        cout << left << setw(5)  << "Idx"
             << setw(26) << "Nama Pemain"
             << setw(20) << "Klub Asal"
             << setw(12) << "Harga (USD)" << endl;
        cetakGaris('-', 75);
        for (int i = 0; i < jumlahPemain; i++) {
            cout << left << setw(5)  << i
                 << setw(26) << sortedPemain[i].namaLengkap
                 << setw(20) << sortedPemain[i].klubAsal
                 << "$" << sortedPemain[i].performa.hargaPasarUSD << endl;
        }
        cetakGaris('=', 75);

        
        int hasil = binarySearchHarga(sortedPemain, &jumlahPemain, &targetHarga);

        cout << "\n--- HASIL BINARY SEARCH ---" << endl;
        cetakGaris('=', 78);
        if (hasil != -1) {
            
            cout << left << setw(5)  << "Idx"
                 << setw(26) << "Nama Pemain"
                 << setw(20) << "Klub Asal"
                 << setw(10) << "Rating"
                 << setw(12) << "Harga (USD)" << endl;
            cetakGaris('-', 78);
            int jumlahHasil = 0;
            for (int i = 0; i < jumlahPemain; i++) {
                if (sortedPemain[i].performa.hargaPasarUSD == targetHarga) {
                    jumlahHasil++;
                    cout << left << setw(5)  << i
                         << setw(26) << sortedPemain[i].namaLengkap
                         << setw(20) << sortedPemain[i].klubAsal
                         << setw(10) << fixed << setprecision(1)
                         << sortedPemain[i].performa.ratingPemain
                         << "$" << sortedPemain[i].performa.hargaPasarUSD << endl;
                }
            }
            cetakGaris('=', 78);
            cout << "  [OK] Ditemukan " << jumlahHasil
                 << " pemain dengan harga $" << targetHarga << endl;
        } else {
            cetakGaris('=', 78);
            cout << "  [!] Tidak ada pemain dengan harga $" << targetHarga << endl;
        }

    } else {
        cout << "\nPilihan tidak valid!" << endl;
    }

    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void menuSearchingUser(PemainMU daftarPemain[], int jumlahPemain) {
    system("cls");
    cout << "========================================" << endl;
    cout << "       MENU SEARCHING DATA PEMAIN       " << endl;
    cout << "========================================" << endl;

    if (jumlahPemain == 0) {
        cout << "Belum ada data pemain di skuad!" << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }

    cout << "1. Linear Search - Cari Nama Pemain" << endl;
    cout << "2. Kembali" << endl;
    cout << "----------------------------------------" << endl;

    int pilihan;
    cout << "Pilih: "; cin >> pilihan;

    if (pilihan == 1) {
        string keyword;
        cin.ignore();
        cout << "Masukkan nama yang dicari: ";
        getline(cin, keyword);

        system("cls");
        cout << "========================================" << endl;
        cout << "   LINEAR SEARCH - Pencarian Nama       " << endl;
        cout << "========================================" << endl;
        cout << "Algoritma    : Menelusuri data satu per satu" << endl;
        cout << "Kompleksitas : O(n)" << endl;

        linearSearchNama(daftarPemain, &jumlahPemain, keyword);
    }

    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void menuSortingAdmin(PemainMU daftarPemain[], int jumlahPemain) {
    system("cls");
    cout << "========================================" << endl;
    cout << "         MENU SORTING DATA PEMAIN       " << endl;
    cout << "========================================" << endl;

    if (jumlahPemain == 0) {
        cout << "Belum ada data pemain di skuad!" << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }

    cout << "1. Bubble Sort    - Nama Pemain (Descending / Z ke A)"          << endl;
    cout << "2. Selection Sort - Harga Pasar (Ascending / Termurah ke Termahal)" << endl;
    cout << "3. Insertion Sort - Rating Pemain (Descending / Tertinggi ke Terendah)" << endl;
    cout << "4. Kembali"                                                      << endl;
    cout << "----------------------------------------" << endl;

    int pilihanSorting;
    cout << "Pilih metode sorting: "; cin >> pilihanSorting;

    if (pilihanSorting == 4) return;

    cout << "\n--- DATA SEBELUM SORTING ---" << endl;
    cetakGaris('=', 75);
    cout << left << setw(4) << "No"
         << setw(25) << "Nama Pemain"
         << setw(20) << "Klub Asal"
         << setw(10) << "Rating"
         << setw(16) << "Harga (USD)" << endl;
    cetakGaris('-', 75);
    for (int i = 0; i < jumlahPemain; i++) {
        PemainMU *pemainPtr = getPemainByIndex(daftarPemain, jumlahPemain, i);
        cout << left << setw(4)  << i + 1
             << setw(25) << pemainPtr->namaLengkap
             << setw(20) << pemainPtr->klubAsal
             << setw(10) << fixed << setprecision(1) << pemainPtr->performa.ratingPemain
             << "$" << pemainPtr->performa.hargaPasarUSD << endl;
    }

    string namaMetode;
    string kriteriaSorting;

    if (pilihanSorting == 1) {
        bubbleSortNamaDescending(daftarPemain, jumlahPemain);
        namaMetode      = "BUBBLE SORT";
        kriteriaSorting = "Nama Pemain - Descending (Z ke A)";
    } else if (pilihanSorting == 2) {
        selectionSortHargaAscending(daftarPemain, jumlahPemain);
        namaMetode      = "SELECTION SORT";
        kriteriaSorting = "Harga Pasar - Ascending (Termurah ke Termahal)";
    } else if (pilihanSorting == 3) {
        insertionSortRatingDescending(daftarPemain, jumlahPemain);
        namaMetode      = "INSERTION SORT";
        kriteriaSorting = "Rating Pemain - Descending (Tertinggi ke Terendah)";
    } else {
        cout << "\nPilihan tidak valid!" << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }

    cout << "\n--- DATA SESUDAH SORTING [" << namaMetode << "] ---" << endl;
    cout << "Kriteria : " << kriteriaSorting << endl;
    cetakGaris('=', 75);
    cout << left << setw(4) << "No"
         << setw(25) << "Nama Pemain"
         << setw(20) << "Klub Asal"
         << setw(10) << "Rating"
         << setw(16) << "Harga (USD)" << endl;
    cetakGaris('-', 75);
    for (int i = 0; i < jumlahPemain; i++) {
        PemainMU *pemainPtr = getPemainByIndex(daftarPemain, jumlahPemain, i);
        cout << left << setw(4)  << i + 1
             << setw(25) << pemainPtr->namaLengkap
             << setw(20) << pemainPtr->klubAsal
             << setw(10) << fixed << setprecision(1) << pemainPtr->performa.ratingPemain
             << "$" << pemainPtr->performa.hargaPasarUSD << endl;
    }
    cetakGaris('=', 75);

    cout << "\n[OK] Data berhasil diurutkan menggunakan " << namaMetode << "!";
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void rekrutPemain(PemainMU daftarPemain[], int &jumlahPemain) {
    system("cls");
    cin.ignore();
    string    namaLengkap, klubAsal, negaraAsal;
    long long hargaPasarUSD;

    cout << "--- FORM REKRUTMEN ---" << endl;
    do {
        cout << "Nama Lengkap  : "; getline(cin, namaLengkap);
        if (namaLengkap.empty()) cout << "Nama tidak boleh kosong!\n";
    } while (namaLengkap.empty());
    do {
        cout << "Klub Asal     : "; getline(cin, klubAsal);
        if (klubAsal.empty()) cout << "Klub tidak boleh kosong!\n";
    } while (klubAsal.empty());
    do {
        cout << "Negara Asal   : "; cin >> negaraAsal;
        if (negaraAsal.empty()) cout << "Negara tidak boleh kosong!\n";
    } while (negaraAsal.empty());
    cout << "Harga (USD)   : $"; cin >> hargaPasarUSD;

    PemainMU *pemainBaru                      = &daftarPemain[jumlahPemain];
    pemainBaru->namaLengkap                   = namaLengkap;
    pemainBaru->klubAsal                      = klubAsal;
    pemainBaru->negaraAsal                    = negaraAsal;
    pemainBaru->performa.hargaPasarUSD        = hargaPasarUSD;
    pemainBaru->performa.ratingPemain         = 0.0f;
    pemainBaru->performa.jumlahPenilai        = 0;
    pemainBaru->performa.totalSkorRating      = 0.0f;

    jumlahPemain++;

    cout << "\n[&] Alamat jumlahPemain di rekrutPemain : " << &jumlahPemain << endl;
    cout << "Berhasil merekrut " << pemainBaru->namaLengkap << "! Tekan Enter...";
    cin.ignore(); cin.get();
}

void jualPemain(PemainMU daftarPemain[], int &jumlahPemain) {
    system("cls");
    cout << "--- JUAL / HAPUS PEMAIN ---" << endl;
    if (jumlahPemain == 0) {
        cout << "Belum ada pemain di skuad." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }

    cetakGaris('=', 55);
    for (int i = 0; i < jumlahPemain; i++) {
        PemainMU *pemainPtr = getPemainByIndex(daftarPemain, jumlahPemain, i);
        cout << left << setw(4) << i + 1
             << setw(28) << pemainPtr->namaLengkap
             << "$" << pemainPtr->performa.hargaPasarUSD << endl;
    }
    cetakGaris('-', 55);

    int nomorPemain;
    cout << "Pilih nomor pemain yang dijual: "; cin >> nomorPemain;

    if (nomorPemain >= 1 && nomorPemain <= jumlahPemain) {
        string konfirmasi;
        PemainMU *pemainTerpilih = getPemainByIndex(daftarPemain, jumlahPemain, nomorPemain - 1);
        cout << "Yakin ingin menjual " << pemainTerpilih->namaLengkap << "? (ya/tidak): ";
        cin >> konfirmasi;

        if (konfirmasi == "ya" || konfirmasi == "Ya" || konfirmasi == "YA") {
            string namaTerjual = pemainTerpilih->namaLengkap;
            for (int i = nomorPemain - 1; i < jumlahPemain - 1; i++) {
                daftarPemain[i] = daftarPemain[i + 1];
            }
            jumlahPemain--;
            cout << "\n[&] Alamat jumlahPemain di jualPemain : " << &jumlahPemain << endl;
            cout << namaTerjual << " berhasil dijual!" << endl;
        } else {
            cout << "\nPenjualan dibatalkan." << endl;
        }
    } else {
        cout << "\nNomor pemain tidak valid!" << endl;
    }
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void updateHarga(PemainMU daftarPemain[], int jumlahPemain) {
    system("cls");
    cout << "--- UPDATE HARGA PEMAIN ---" << endl;
    if (jumlahPemain == 0) {
        cout << "Belum ada pemain di skuad." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }

    cetakGaris('=', 55);
    for (int i = 0; i < jumlahPemain; i++) {
        PemainMU *pemainPtr = getPemainByIndex(daftarPemain, jumlahPemain, i);
        cout << left << setw(4) << i + 1
             << setw(28) << pemainPtr->namaLengkap
             << "$" << pemainPtr->performa.hargaPasarUSD << endl;
    }
    cetakGaris('-', 55);

    int       nomorPemain;
    long long hargaBaru;
    cout << "Pilih nomor pemain : "; cin >> nomorPemain;

    if (nomorPemain >= 1 && nomorPemain <= jumlahPemain) {
        cout << "Harga baru (USD)   : $"; cin >> hargaBaru;
        PemainMU *pemainTerpilih = getPemainByIndex(daftarPemain, jumlahPemain, nomorPemain - 1);
        terapkanHargaBaru(&pemainTerpilih->performa.hargaPasarUSD, hargaBaru);
    } else {
        cout << "\nNomor pemain tidak valid!" << endl;
    }
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void updateRatingAdmin(PemainMU daftarPemain[], int jumlahPemain) {
    system("cls");
    cout << "--- UPDATE RATING PEMAIN (ADMIN) ---" << endl;
    if (jumlahPemain == 0) {
        cout << "Belum ada pemain di skuad." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }

    cetakGaris('=', 55);
    for (int i = 0; i < jumlahPemain; i++) {
        PemainMU *pemainPtr = getPemainByIndex(daftarPemain, jumlahPemain, i);
        cout << left << setw(4)  << i + 1
             << setw(28) << pemainPtr->namaLengkap
             << "Rating: " << fixed << setprecision(1)
             << pemainPtr->performa.ratingPemain << endl;
    }
    cetakGaris('-', 55);

    int   nomorPemain;
    float ratingBaru;
    cout << "Pilih nomor pemain  : "; cin >> nomorPemain;

    if (nomorPemain >= 1 && nomorPemain <= jumlahPemain) {
        cout << "Rating baru (0-10)  : "; cin >> ratingBaru;
        if (ratingBaru >= 0 && ratingBaru <= 10) {
            PemainMU *pemainTerpilih = getPemainByIndex(daftarPemain, jumlahPemain, nomorPemain - 1);
            pemainTerpilih->performa.totalSkorRating = 0.0f;
            pemainTerpilih->performa.jumlahPenilai   = 0;
            hitungUlangRating(
                &pemainTerpilih->performa.totalSkorRating,
                &pemainTerpilih->performa.jumlahPenilai,
                &pemainTerpilih->performa.ratingPemain,
                ratingBaru
            );
            cout << "\n[*] Rating " << pemainTerpilih->namaLengkap
                 << " sekarang: " << fixed << setprecision(1)
                 << pemainTerpilih->performa.ratingPemain << endl;
        } else {
            cout << "\nRating harus antara 0 - 10!" << endl;
        }
    } else {
        cout << "\nNomor pemain tidak valid!" << endl;
    }
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void berikanRatingUser(PemainMU daftarPemain[], int jumlahPemain) {
    system("cls");
    cout << "--- BERIKAN RATING PEMAIN ---" << endl;
    if (jumlahPemain == 0) {
        cout << "Belum ada pemain di skuad." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }

    cetakGaris('=', 65);
    for (int i = 0; i < jumlahPemain; i++) {
        PemainMU *pemainPtr = getPemainByIndex(daftarPemain, jumlahPemain, i);
        cout << left << setw(4)  << i + 1
             << setw(28) << pemainPtr->namaLengkap
             << "Rating: " << fixed << setprecision(1)
             << pemainPtr->performa.ratingPemain
             << " (" << pemainPtr->performa.jumlahPenilai << " penilai)" << endl;
    }
    cetakGaris('-', 65);

    int   nomorPemain;
    float skorUser;
    cout << "Pilih nomor pemain : "; cin >> nomorPemain;

    if (nomorPemain >= 1 && nomorPemain <= jumlahPemain) {
        cout << "Beri rating (0-10) : "; cin >> skorUser;
        if (skorUser >= 0 && skorUser <= 10) {
            PemainMU *pemainTerpilih = getPemainByIndex(daftarPemain, jumlahPemain, nomorPemain - 1);
            hitungUlangRating(
                &pemainTerpilih->performa.totalSkorRating,
                &pemainTerpilih->performa.jumlahPenilai,
                &pemainTerpilih->performa.ratingPemain,
                skorUser
            );
            cout << "\nTerima kasih! Rating " << pemainTerpilih->namaLengkap
                 << " sekarang: " << fixed << setprecision(1)
                 << pemainTerpilih->performa.ratingPemain << endl;
        } else {
            cout << "\nRating harus antara 0 - 10!" << endl;
        }
    } else {
        cout << "\nNomor pemain tidak valid!" << endl;
    }
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void cetakBarisPemainAdmin(PemainMU daftarPemain[], int indeks, int totalPemain) {
    if (indeks >= totalPemain) return;
    PemainMU *pemainPtr = getPemainByIndex(daftarPemain, totalPemain, indeks);
    cout << left << setw(4)  << indeks + 1
         << setw(22) << pemainPtr->namaLengkap
         << setw(18) << pemainPtr->klubAsal
         << setw(10) << fixed << setprecision(1) << pemainPtr->performa.ratingPemain
         << "$" << pemainPtr->performa.hargaPasarUSD << endl;
    cetakBarisPemainAdmin(daftarPemain, indeks + 1, totalPemain);
}

void cetakBarisPemainUser(PemainMU daftarPemain[], int indeks, int totalPemain) {
    if (indeks >= totalPemain) return;
    PemainMU *pemainPtr = getPemainByIndex(daftarPemain, totalPemain, indeks);
    cout << left << setw(4)  << indeks + 1
         << setw(25) << pemainPtr->namaLengkap
         << setw(12) << fixed << setprecision(1) << pemainPtr->performa.ratingPemain
         << setw(15) << pemainPtr->negaraAsal << endl;
    cetakBarisPemainUser(daftarPemain, indeks + 1, totalPemain);
}

void tampilkanSkuad(PemainMU daftarPemain[], int jumlahPemain) {
    system("cls");
    cout << "--- DAFTAR SKUAD (VIEW ONLY) ---" << endl;
    cetakGaris('=', 60);
    cout << left << setw(4) << "No" << setw(25) << "Nama"
         << setw(12) << "Rating" << setw(15) << "Negara" << endl;
    cetakGaris('-', 60);
    cetakBarisPemainUser(daftarPemain, 0, jumlahPemain);
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void tampilkanSkuad(PemainMU daftarPemain[], int jumlahPemain, bool tampilHarga) {
    system("cls");
    cout << "--- DAFTAR SKUAD MANCHESTER UNITED ---" << endl;
    cetakGaris('=', 80);
    cout << left << setw(4) << "No" << setw(22) << "Nama"
         << setw(18) << "Asal Klub" << setw(10) << "Rating"
         << setw(15) << "Harga (USD)" << endl;
    cetakGaris('-', 80);
    cetakBarisPemainAdmin(daftarPemain, 0, jumlahPemain);
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

bool cekDuplikatUsername(AkunPengguna databaseAkun[], int jumlahAkun, string username) {
    for (int i = 0; i < jumlahAkun; i++) {
        if (databaseAkun[i].username == username) return true;
    }
    return false;
}

void registrasiAkun(AkunPengguna databaseAkun[], int &jumlahAkun) {
    system("cls");
    cout << "--- REGISTRASI USER BARU ---" << endl;
    if (jumlahAkun >= MAKSIMAL_AKUN) {
        cout << "Database akun penuh!" << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }

    string usernameBaru, passwordBaru;
    do {
        cout << "Username : "; cin >> usernameBaru;
        if (usernameBaru.empty()) cout << "Username tidak boleh kosong!\n";
    } while (usernameBaru.empty());

    if (cekDuplikatUsername(databaseAkun, jumlahAkun, usernameBaru)) {
        cout << "\nError: Username sudah terdaftar!" << endl;
    } else {
        do {
            cout << "Password : "; cin >> passwordBaru;
            if (passwordBaru.empty()) cout << "Password tidak boleh kosong!\n";
        } while (passwordBaru.empty());

        databaseAkun[jumlahAkun].username = usernameBaru;
        databaseAkun[jumlahAkun].password = passwordBaru;
        databaseAkun[jumlahAkun].peran    = "user";
        jumlahAkun++;

        cout << "\n[&] Alamat jumlahAkun di registrasiAkun : " << &jumlahAkun << endl;
        cout << "Registrasi Berhasil! Silakan Login." << endl;
    }
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

AkunPengguna prosesLogin(AkunPengguna databaseAkun[], int jumlahAkun, bool &statusLogin) {
    AkunPengguna sesiAktif;
    int          jumlahPercobaan = 0;

    while (jumlahPercobaan < 3) {
        system("cls");
        string inputUsername, inputPassword;
        cout << "--- FORM LOGIN (Percobaan: " << jumlahPercobaan + 1 << "/3) ---" << endl;
        cout << "Username : "; cin >> inputUsername;
        cout << "Password : "; cin >> inputPassword;

        for (int i = 0; i < jumlahAkun; i++) {
            if (inputUsername == databaseAkun[i].username &&
                inputPassword == databaseAkun[i].password) {
                sesiAktif   = databaseAkun[i];
                statusLogin = true;
                break;
            }
        }
        if (statusLogin) {
            cout << "\nLogin Berhasil! Tekan Enter...";
            cin.ignore(); cin.get();
            break;
        } else {
            jumlahPercobaan++;
            if (jumlahPercobaan < 3) {
                cout << "\nLogin Gagal! Username/Password salah.";
                cin.ignore(); cin.get();
            }
        }
    }
    return sesiAktif;
}

void tampilkanMenuAdmin() {
    cout << "1. Rekrut Pemain Baru"             << endl;
    cout << "2. Lihat Daftar Skuad"             << endl;
    cout << "3. Update Harga"                   << endl;
    cout << "4. Update Rating"                  << endl;
    cout << "5. Jual Pemain"                    << endl;
    cout << "6. Sorting Data Pemain      [MOD5]" << endl;
    cout << "7. Searching Data Pemain   [NEW]"  << endl;
    cout << "8. Logout"                         << endl;
}

void tampilkanMenuUser() {
    cout << "1. Lihat Daftar Skuad"      << endl;
    cout << "2. Berikan Rating Pemain"   << endl;
    cout << "3. Searching Data Pemain   [NEW]" << endl;
    cout << "4. Logout"                  << endl;
}

int main() {
    
    databaseAkun[jumlahAkun++] = {"nabil", "024", "admin"};
    databaseAkun[jumlahAkun++] = {"ewok",  "024", "user"};

    
    
    
    
    
    daftarPemain[jumlahDataPemain++] = {
        "Bryan Mbeumo", "Brentford", "Kamerun",
        {0.0f, 70000000LL, 0, 0.0f}
    };
    daftarPemain[jumlahDataPemain++] = {
        "Matheus Cunha", "Watford", "Brasil",
        {0.0f, 62000000LL, 0, 0.0f}
    };
    daftarPemain[jumlahDataPemain++] = {
        "Benjamin Sesko", "RB Leipzig", "Slovenia",
        {0.0f, 75000000LL, 0, 0.0f}
    };
    daftarPemain[jumlahDataPemain++] = {
        "Senne Lammens", "Royal Antwerp", "Belgia",
        {0.0f, 18000000LL, 0, 0.0f}
    };
    daftarPemain[jumlahDataPemain++] = {
        "Casemiro", "Real Madrid", "Brasil",
        {0.0f, 22000000LL, 0, 0.0f}
    };
    

    AkunPengguna sesiLogin;
    bool         programBerjalan = true;

    while (programBerjalan) {
        system("cls");
        int pilihanLayarAwal;
        cout << "========================================" << endl;
        cout << "    MANCHESTER UNITED MANAGER SYSTEM    " << endl;
        cout << "========================================" << endl;
        cout << "1. Login ke Sistem"                  << endl;
        cout << "2. Registrasi Akun Baru (User Only)" << endl;
        cout << "3. Tutup Program"                    << endl;
        cout << "Pilihan: "; cin >> pilihanLayarAwal;

        if (pilihanLayarAwal == 2) {
            registrasiAkun(databaseAkun, jumlahAkun);
            continue;
        }

        if (pilihanLayarAwal == 3) {
            system("cls");
            cout << "Program dihentikan. Glory Glory Man United!" << endl;
            programBerjalan = false;
            break;
        }

        if (pilihanLayarAwal == 1) {
            bool statusLogin = false;
            sesiLogin = prosesLogin(databaseAkun, jumlahAkun, statusLogin);

            if (!statusLogin) {
                system("cls");
                cout << "========================================" << endl;
                cout << "   AKSES DITOLAK! 3x Percobaan Gagal   " << endl;
                cout << "========================================" << endl;
                programBerjalan = false;
                break;
            }

            bool tetapDiMenu = true;
            while (tetapDiMenu) {
                system("cls");
                cout << "=== DASHBOARD "
                     << (sesiLogin.peran == "admin" ? "OFFICIAL ADMIN" : "SUPPORTER ZONE")
                     << " ===" << endl;
                cout << "User Aktif : " << sesiLogin.username << endl;
                cout << "----------------------------------------" << endl;

                if (sesiLogin.peran == "admin") {
                    tampilkanMenuAdmin();
                } else {
                    tampilkanMenuUser();
                }

                int pilihanMenu;
                cout << "\nPilih Opsi: "; cin >> pilihanMenu;

                if (sesiLogin.peran == "admin") {
                    if      (pilihanMenu == 1) rekrutPemain(daftarPemain, jumlahDataPemain);
                    else if (pilihanMenu == 2) tampilkanSkuad(daftarPemain, jumlahDataPemain, true);
                    else if (pilihanMenu == 3) updateHarga(daftarPemain, jumlahDataPemain);
                    else if (pilihanMenu == 4) updateRatingAdmin(daftarPemain, jumlahDataPemain);
                    else if (pilihanMenu == 5) jualPemain(daftarPemain, jumlahDataPemain);
                    else if (pilihanMenu == 6) menuSortingAdmin(daftarPemain, jumlahDataPemain);
                    else if (pilihanMenu == 7) menuSearchingAdmin(daftarPemain, jumlahDataPemain); 
                    else if (pilihanMenu == 8) tetapDiMenu = false;
                } else {
                    if      (pilihanMenu == 1) tampilkanSkuad(daftarPemain, jumlahDataPemain);
                    else if (pilihanMenu == 2) berikanRatingUser(daftarPemain, jumlahDataPemain);
                    else if (pilihanMenu == 3) menuSearchingUser(daftarPemain, jumlahDataPemain); 
                    else if (pilihanMenu == 4) tetapDiMenu = false;
                }
            }
        }
    }
    return 0;
}