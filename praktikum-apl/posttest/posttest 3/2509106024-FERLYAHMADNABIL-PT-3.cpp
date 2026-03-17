#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct DataTeknis {
    float ratingPemain;
    long long hargaPasarUSD;
    int jumlahPenilai;
    float totalSkorRating;
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
const int MAKSIMAL_AKUN  = 50;

PemainMU    daftarPemain[MAKSIMAL_DATA];
AkunPengguna databaseAkun[MAKSIMAL_AKUN];
int jumlahDataPemain = 0;
int jumlahAkun       = 0;

void cetakGaris(char karakter, int lebar) {
    cout << setfill(karakter) << setw(lebar) << karakter << setfill(' ') << endl;
}

void tampilkanMenuAdmin() {
    cout << "1. Rekrut Pemain Baru"  << endl;
    cout << "2. Lihat Daftar Skuad"  << endl;
    cout << "3. Update Harga"        << endl;
    cout << "4. Update Rating"       << endl;
    cout << "5. Jual Pemain"         << endl;
    cout << "6. Logout"              << endl;
}

void tampilkanMenuUser() {
    cout << "1. Lihat Daftar Skuad"    << endl;
    cout << "2. Berikan Rating Pemain" << endl;
    cout << "3. Logout"               << endl;
}

void cetakBarisPemainAdmin(PemainMU pemain[], int index, int total) {
    if (index >= total) return;
    cout << setfill(' ') << left
         << setw(4)  << index + 1
         << setw(22) << pemain[index].namaLengkap
         << setw(18) << pemain[index].klubAsal
         << setw(10) << fixed << setprecision(1) << pemain[index].performa.ratingPemain
         << "$" << pemain[index].performa.hargaPasarUSD << endl;
    cetakBarisPemainAdmin(pemain, index + 1, total);
}

void cetakBarisPemainUser(PemainMU pemain[], int index, int total) {
    if (index >= total) return;
    cout << setfill(' ') << left
         << setw(4)  << index + 1
         << setw(25) << pemain[index].namaLengkap
         << setw(12) << fixed << setprecision(1) << pemain[index].performa.ratingPemain
         << setw(15) << pemain[index].negaraAsal << endl;
    cetakBarisPemainUser(pemain, index + 1, total);
}

void tampilkanSkuad(PemainMU pemain[], int jumlah) {
    system("cls");
    cout << "--- DAFTAR SKUAD (VIEW ONLY) ---" << endl;
    cetakGaris('=', 60);
    cout << setfill(' ') << left
         << setw(4)  << "No"
         << setw(25) << "Nama"
         << setw(12) << "Rating"
         << setw(15) << "Negara" << endl;
    cetakGaris('-', 60);
    cetakBarisPemainUser(pemain, 0, jumlah);
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void tampilkanSkuad(PemainMU pemain[], int jumlah, bool tampilHarga) {
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
    cetakBarisPemainAdmin(pemain, 0, jumlah);
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

bool cekDuplikatUsername(AkunPengguna akun[], int jumlah, string username) {
    for (int i = 0; i < jumlah; i++) {
        if (akun[i].username == username) return true;
    }
    return false;
}

void registrasiAkun(AkunPengguna akun[], int &jumlah) {
    system("cls");
    cout << "--- REGISTRASI USER BARU ---" << endl;
    if (jumlah >= MAKSIMAL_AKUN) {
        cout << "Database akun penuh!" << endl;
        cout << "\nTekan Enter untuk kembali..."; cin.ignore(); cin.get();
        return;
    }
    string uBaru, pBaru;
    do {
        cout << "Username : "; cin >> uBaru;
        if (uBaru.empty()) cout << "Username tidak boleh kosong!\n";
    } while (uBaru.empty());

    if (cekDuplikatUsername(akun, jumlah, uBaru)) {
        cout << "\nError: Username sudah terdaftar!" << endl;
    } else {
        do {
            cout << "Password : "; cin >> pBaru;
            if (pBaru.empty()) cout << "Password tidak boleh kosong!\n";
        } while (pBaru.empty());
        akun[jumlah].username = uBaru;
        akun[jumlah].password = pBaru;
        akun[jumlah].peran    = "user";
        jumlah++;
        cout << "\nRegistrasi Berhasil! Silakan Login." << endl;
    }
    cout << "\nTekan Enter untuk kembali..."; cin.ignore(); cin.get();
}

AkunPengguna prosesLogin(AkunPengguna akun[], int jumlah, bool &statusLogin) {
    AkunPengguna sesi;
    int batasPercobaan = 0;
    while (batasPercobaan < 3) {
        system("cls");
        string inputUser, inputPass;
        cout << "--- FORM LOGIN (Percobaan: " << batasPercobaan + 1 << "/3) ---" << endl;
        cout << "Username : "; cin >> inputUser;
        cout << "Password : "; cin >> inputPass;

        for (int i = 0; i < jumlah; i++) {
            if (inputUser == akun[i].username && inputPass == akun[i].password) {
                sesi        = akun[i];
                statusLogin = true;
                break;
            }
        }
        if (statusLogin) {
            cout << "\nLogin Berhasil! Tekan Enter...";
            cin.ignore(); cin.get();
            break;
        } else {
            batasPercobaan++;
            if (batasPercobaan < 3) {
                cout << "\nLogin Gagal! Username/Password salah.";
                cin.ignore(); cin.get();
            }
        }
    }
    return sesi;
}

void rekrutPemain(PemainMU pemain[], int &jumlah) {
    system("cls");
    cin.ignore();
    string n, k, neg;
    long long h;
    cout << "--- FORM REKRUTMEN ---" << endl;
    do {
        cout << "Nama Lengkap: "; getline(cin, n);
        if (n.empty()) cout << "Nama tidak boleh kosong!\n";
    } while (n.empty());
    do {
        cout << "Klub Asal   : "; getline(cin, k);
        if (k.empty()) cout << "Klub tidak boleh kosong!\n";
    } while (k.empty());
    do {
        cout << "Negara      : "; cin >> neg;
        if (neg.empty()) cout << "Negara tidak boleh kosong!\n";
    } while (neg.empty());
    cout << "Harga (USD) : "; cin >> h;

    pemain[jumlah].namaLengkap                = n;
    pemain[jumlah].klubAsal                   = k;
    pemain[jumlah].negaraAsal                 = neg;
    pemain[jumlah].performa.hargaPasarUSD     = h;
    pemain[jumlah].performa.ratingPemain      = 0;
    pemain[jumlah].performa.jumlahPenilai     = 0;
    pemain[jumlah].performa.totalSkorRating   = 0;
    jumlah++;
    cout << "\nBerhasil Rekrut! Tekan Enter..."; cin.ignore(); cin.get();
}

void updateHarga(PemainMU pemain[], int jumlah) {
    system("cls");
    cout << "--- UPDATE HARGA PEMAIN ---" << endl;
    if (jumlah == 0) {
        cout << "Belum ada pemain di skuad." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }
    cetakGaris('=', 55);
    for (int i = 0; i < jumlah; i++) {
        cout << setfill(' ') << left << setw(4) << i + 1
             << setw(28) << pemain[i].namaLengkap
             << "$" << pemain[i].performa.hargaPasarUSD << endl;
    }
    cetakGaris('-', 55);
    int idx; long long hargaBaru;
    cout << "Pilih nomor pemain: "; cin >> idx;
    if (idx >= 1 && idx <= jumlah) {
        cout << "Harga baru (USD)  : "; cin >> hargaBaru;
        pemain[idx - 1].performa.hargaPasarUSD = hargaBaru;
        cout << "\nHarga berhasil diupdate!" << endl;
    } else {
        cout << "\nNomor pemain tidak valid!" << endl;
    }
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void updateRatingAdmin(PemainMU pemain[], int jumlah) {
    system("cls");
    cout << "--- UPDATE RATING PEMAIN (ADMIN) ---" << endl;
    if (jumlah == 0) {
        cout << "Belum ada pemain di skuad." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }
    cetakGaris('=', 55);
    for (int i = 0; i < jumlah; i++) {
        cout << setfill(' ') << left << setw(4) << i + 1
             << setw(28) << pemain[i].namaLengkap
             << "Rating: " << fixed << setprecision(1) << pemain[i].performa.ratingPemain << endl;
    }
    cetakGaris('-', 55);
    int idx; float ratingBaru;
    cout << "Pilih nomor pemain : "; cin >> idx;
    if (idx >= 1 && idx <= jumlah) {
        cout << "Rating baru (0-10) : "; cin >> ratingBaru;
        if (ratingBaru >= 0 && ratingBaru <= 10) {
            pemain[idx - 1].performa.ratingPemain    = ratingBaru;
            pemain[idx - 1].performa.totalSkorRating = ratingBaru;
            pemain[idx - 1].performa.jumlahPenilai   = 1;
            cout << "\nRating berhasil diupdate!" << endl;
        } else {
            cout << "\nRating harus antara 0 - 10!" << endl;
        }
    } else {
        cout << "\nNomor pemain tidak valid!" << endl;
    }
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void jualPemain(PemainMU pemain[], int &jumlah) {
    system("cls");
    cout << "--- JUAL / HAPUS PEMAIN ---" << endl;
    if (jumlah == 0) {
        cout << "Belum ada pemain di skuad." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }
    cetakGaris('=', 55);
    for (int i = 0; i < jumlah; i++) {
        cout << setfill(' ') << left << setw(4) << i + 1
             << setw(28) << pemain[i].namaLengkap
             << "$" << pemain[i].performa.hargaPasarUSD << endl;
    }
    cetakGaris('-', 55);
    int idx;
    cout << "Pilih nomor pemain yang dijual: "; cin >> idx;
    if (idx >= 1 && idx <= jumlah) {
        string konfirmasi;
        cout << "Yakin ingin menjual " << pemain[idx - 1].namaLengkap << "? (ya/tidak): ";
        cin >> konfirmasi;
        if (konfirmasi == "ya" || konfirmasi == "Ya" || konfirmasi == "YA") {
            string namaTerjual = pemain[idx - 1].namaLengkap;
            for (int i = idx - 1; i < jumlah - 1; i++) {
                pemain[i] = pemain[i + 1];
            }
            jumlah--;
            cout << "\n" << namaTerjual << " berhasil dijual!" << endl;
        } else {
            cout << "\nPenjualan dibatalkan." << endl;
        }
    } else {
        cout << "\nNomor pemain tidak valid!" << endl;
    }
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

void berikanRatingUser(PemainMU pemain[], int jumlah) {
    system("cls");
    cout << "--- BERIKAN RATING PEMAIN ---" << endl;
    if (jumlah == 0) {
        cout << "Belum ada pemain di skuad." << endl;
        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
        return;
    }
    cetakGaris('=', 65);
    for (int i = 0; i < jumlah; i++) {
        cout << setfill(' ') << left << setw(4) << i + 1
             << setw(28) << pemain[i].namaLengkap
             << "Rating: " << fixed << setprecision(1) << pemain[i].performa.ratingPemain
             << " (" << pemain[i].performa.jumlahPenilai << " penilai)" << endl;
    }
    cetakGaris('-', 65);
    int idx; float skorUser;
    cout << "Pilih nomor pemain : "; cin >> idx;
    if (idx >= 1 && idx <= jumlah) {
        cout << "Beri rating (0-10): "; cin >> skorUser;
        if (skorUser >= 0 && skorUser <= 10) {
            pemain[idx - 1].performa.totalSkorRating += skorUser;
            pemain[idx - 1].performa.jumlahPenilai++;
            pemain[idx - 1].performa.ratingPemain =
                pemain[idx - 1].performa.totalSkorRating / pemain[idx - 1].performa.jumlahPenilai;
            cout << "\nTerima kasih! Rating " << pemain[idx - 1].namaLengkap
                 << " sekarang: " << fixed << setprecision(1) << pemain[idx - 1].performa.ratingPemain << endl;
        } else {
            cout << "\nRating harus antara 0 - 10!" << endl;
        }
    } else {
        cout << "\nNomor pemain tidak valid!" << endl;
    }
    cout << "\nTekan Enter..."; cin.ignore(); cin.get();
}

int main() {
    databaseAkun[jumlahAkun++] = {"nabil", "024", "admin"};
    databaseAkun[jumlahAkun++] = {"ewok",  "024", "user"};

    AkunPengguna sesiLogin;
    bool programJalan = true;

    while (programJalan) {
        system("cls");
        int pilihanLayarAwal;
        cout << "========================================" << endl;
        cout << "    MANCHESTER UNITED MANAGER SYSTEM    " << endl;
        cout << "========================================" << endl;
        cout << "1. Login ke Sistem"              << endl;
        cout << "2. Registrasi Akun Baru (User Only)" << endl;
        cout << "3. Tutup Program"                << endl;
        cout << "Pilihan: "; cin >> pilihanLayarAwal;

        if (pilihanLayarAwal == 2) {
            registrasiAkun(databaseAkun, jumlahAkun);
            continue;
        }

        if (pilihanLayarAwal == 3) {
            system("cls");
            cout << "Program dihentikan. Glory Glory Man United!" << endl;
            programJalan = false;
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
                programJalan = false;
                break;
            }

            bool tetapDiMenu = true;
            while (tetapDiMenu) {
                system("cls");
                cout << "=== DASHBOARD "
                     << (sesiLogin.peran == "admin" ? "OFFICIAL ADMIN" : "SUPPORTER ZONE")
                     << " ===" << endl;
                cout << "User Aktif: " << sesiLogin.username << endl;
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
                    else if (pilihanMenu == 6) tetapDiMenu = false;
                } else {
                    if      (pilihanMenu == 1) tampilkanSkuad(daftarPemain, jumlahDataPemain);
                    else if (pilihanMenu == 2) berikanRatingUser(daftarPemain, jumlahDataPemain);
                    else if (pilihanMenu == 3) tetapDiMenu = false;
                }
            }
        }
    }
    return 0;
}