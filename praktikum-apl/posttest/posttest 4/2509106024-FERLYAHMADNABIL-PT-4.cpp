#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct DataTeknis {
    float  ratingPemain;
    long long hargaPasarUSD;
    int    jumlahPenilai;
    float  totalSkorRating;
};

struct PemainMU {
    string namaLengkap;
    string klubAsal;
    string negaraAsal;
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
    *totalSkorTarget    += skorBaru;
    *jumlahPenilaiTarget += 1;
    *ratingPemainTarget  = *totalSkorTarget / (float)(*jumlahPenilaiTarget);
}

void rekrutPemain(PemainMU daftarPemain[], int &jumlahPemain) {
    system("cls");
    cin.ignore();
    string namaLengkap, klubAsal, negaraAsal;
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

    PemainMU *pemainBaru = &daftarPemain[jumlahPemain];
    pemainBaru->namaLengkap              = namaLengkap;
    pemainBaru->klubAsal                 = klubAsal;
    pemainBaru->negaraAsal               = negaraAsal;
    pemainBaru->performa.hargaPasarUSD   = hargaPasarUSD;
    pemainBaru->performa.ratingPemain    = 0.0f;
    pemainBaru->performa.jumlahPenilai   = 0;
    pemainBaru->performa.totalSkorRating = 0.0f;

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
        cout << setfill(' ') << left << setw(4) << i + 1
             << setw(28) << pemainPtr->namaLengkap
             << "$"      << pemainPtr->performa.hargaPasarUSD << endl;
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
        cout << setfill(' ') << left << setw(4) << i + 1
             << setw(28) << pemainPtr->namaLengkap
             << "$"      << pemainPtr->performa.hargaPasarUSD << endl;
    }
    cetakGaris('-', 55);

    int nomorPemain;
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
        cout << setfill(' ') << left << setw(4) << i + 1
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
        cout << setfill(' ') << left << setw(4) << i + 1
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
    cout << setfill(' ') << left
         << setw(4)  << indeks + 1
         << setw(22) << pemainPtr->namaLengkap
         << setw(18) << pemainPtr->klubAsal
         << setw(10) << fixed << setprecision(1) << pemainPtr->performa.ratingPemain
         << "$"      << pemainPtr->performa.hargaPasarUSD << endl;
    cetakBarisPemainAdmin(daftarPemain, indeks + 1, totalPemain);
}

void cetakBarisPemainUser(PemainMU daftarPemain[], int indeks, int totalPemain) {
    if (indeks >= totalPemain) return;
    PemainMU *pemainPtr = getPemainByIndex(daftarPemain, totalPemain, indeks);
    cout << setfill(' ') << left
         << setw(4)  << indeks + 1
         << setw(25) << pemainPtr->namaLengkap
         << setw(12) << fixed << setprecision(1) << pemainPtr->performa.ratingPemain
         << setw(15) << pemainPtr->negaraAsal << endl;
    cetakBarisPemainUser(daftarPemain, indeks + 1, totalPemain);
}

void tampilkanSkuad(PemainMU daftarPemain[], int jumlahPemain) {
    system("cls");
    cout << "--- DAFTAR SKUAD (VIEW ONLY) ---" << endl;
    cetakGaris('=', 60);
    cout << setfill(' ') << left
         << setw(4)  << "No"
         << setw(25) << "Nama"
         << setw(12) << "Rating"
         << setw(15) << "Negara" << endl;
    cetakGaris('-', 60);
    cetakBarisPemainUser(daftarPemain, 0, jumlahPemain);
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void tampilkanSkuad(PemainMU daftarPemain[], int jumlahPemain, bool tampilHarga) {
    system("cls");
    cout << "--- DAFTAR SKUAD MANCHESTER UNITED ---" << endl;
    cetakGaris('=', 80);
    cout << setfill(' ') << left
         << setw(4)  << "No"
         << setw(22) << "Nama"
         << setw(18) << "Asal Klub"
         << setw(10) << "Rating"
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
    int jumlahPercobaan = 0;

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
    cout << "1. Rekrut Pemain Baru" << endl;
    cout << "2. Lihat Daftar Skuad" << endl;
    cout << "3. Update Harga"       << endl;
    cout << "4. Update Rating"      << endl;
    cout << "5. Jual Pemain"        << endl;
    cout << "6. Logout"             << endl;
}

void tampilkanMenuUser() {
    cout << "1. Lihat Daftar Skuad"    << endl;
    cout << "2. Berikan Rating Pemain" << endl;
    cout << "3. Logout"               << endl;
}

int main() {
    databaseAkun[jumlahAkun++] = {"nabil", "024", "admin"};
    databaseAkun[jumlahAkun++] = {"ewok",  "024", "user"};

    AkunPengguna sesiLogin;
    bool programBerjalan = true;

    while (programBerjalan) {
        system("cls");
        int pilihanLayarAwal;
        cout << "========================================" << endl;
        cout << "    MANCHESTER UNITED MANAGER SYSTEM    " << endl;
        cout << "========================================" << endl;
        cout << "1. Login ke Sistem"                 << endl;
        cout << "2. Registrasi Akun Baru (User Only)" << endl;
        cout << "3. Tutup Program"                   << endl;
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
                cout << "Program dihentikan karena terlalu banyak" << endl;
                cout << "percobaan login yang gagal."             << endl;
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
                    if      (pilihanMenu == 1) rekrutPemain(daftarPemain, jumlahDataPemain);   // [&]
                    else if (pilihanMenu == 2) tampilkanSkuad(daftarPemain, jumlahDataPemain, true);
                    else if (pilihanMenu == 3) updateHarga(daftarPemain, jumlahDataPemain);    // [*]
                    else if (pilihanMenu == 4) updateRatingAdmin(daftarPemain, jumlahDataPemain); // [*]
                    else if (pilihanMenu == 5) jualPemain(daftarPemain, jumlahDataPemain);     // [&]
                    else if (pilihanMenu == 6) tetapDiMenu = false;
                } else {
                    if      (pilihanMenu == 1) tampilkanSkuad(daftarPemain, jumlahDataPemain);
                    else if (pilihanMenu == 2) berikanRatingUser(daftarPemain, jumlahDataPemain); // [*]
                    else if (pilihanMenu == 3) tetapDiMenu = false;
                }
            }
        }
    }
    return 0;
}