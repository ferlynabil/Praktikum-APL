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
const int MAKSIMAL_AKUN = 50; 
PemainMU daftarPemain[MAKSIMAL_DATA];
AkunPengguna databaseAkun[MAKSIMAL_AKUN];

int jumlahDataPemain = 0;
int jumlahAkun = 0; 

int main() {
    databaseAkun[jumlahAkun++] = {"nabil", "024", "admin"};
    databaseAkun[jumlahAkun++] = {"ewok", "024", "user"};
    
    AkunPengguna sesiLogin;
    bool programJalan = true;

    while (programJalan) {
        system("cls");
        int pilihanLayarAwal;

        cout << "========================================" << endl;
        cout << "    MANCHESTER UNITED MANAGER SYSTEM    " << endl;
        cout << "========================================" << endl;
        cout << "1. Login ke Sistem" << endl;
        cout << "2. Registrasi Akun Baru (User Only)" << endl;
        cout << "3. Tutup Program" << endl;
        cout << "Pilihan: "; cin >> pilihanLayarAwal;

        if (pilihanLayarAwal == 2) {
            system("cls");
            if (jumlahAkun < MAKSIMAL_AKUN) {
                string uBaru, pBaru;
                cout << "--- REGISTRASI USER BARU ---" << endl;
                do {
                    cout << "Username : "; cin >> uBaru;
                    if (uBaru.empty()) cout << "Username tidak boleh kosong!\n";
                } while (uBaru.empty());
                
                bool duplikat = false;
                for(int i=0; i < jumlahAkun; i++) {
                    if(databaseAkun[i].username == uBaru) {
                        duplikat = true; break;
                    }
                }

                if(duplikat) {
                    cout << "\nError: Username sudah terdaftar!" << endl;
                } else {
                    do {
                        cout << "Password : "; cin >> pBaru;
                        if (pBaru.empty()) cout << "Password tidak boleh kosong!\n";
                    } while (pBaru.empty());
                    databaseAkun[jumlahAkun].username = uBaru;
                    databaseAkun[jumlahAkun].password = pBaru;
                    databaseAkun[jumlahAkun].peran = "user";
                    jumlahAkun++;
                    cout << "\nRegistrasi Berhasil! Silakan Login." << endl;
                }
            } else {
                cout << "Database penuh!" << endl;
            }
            cout << "\nTekan Enter untuk kembali..."; cin.ignore(); cin.get();
            continue;
        }

        if (pilihanLayarAwal == 3) {
            system("cls");
            cout << "Program dihentikan. Glory Glory Man United!" << endl;
            programJalan = false;
            break;
        }

        if (pilihanLayarAwal == 1) {
            string inputUser, inputPass;
            bool statusLogin = false;
            int batasPercobaan = 0;

            while (batasPercobaan < 3) {
                system("cls");
                cout << "--- FORM LOGIN (Percobaan: " << batasPercobaan + 1 << "/3) ---" << endl;
                cout << "Username : "; cin >> inputUser;
                cout << "Password : "; cin >> inputPass;

                for (int i = 0; i < jumlahAkun; i++) {
                    if (inputUser == databaseAkun[i].username && inputPass == databaseAkun[i].password) {
                        sesiLogin = databaseAkun[i];
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
                    if(batasPercobaan < 3) {
                        cout << "\nLogin Gagal! Username/Password salah.";
                        cin.ignore(); cin.get();
                    }
                }
            }

            if (!statusLogin) {
                system("cls");
                cout << "========================================" << endl;
                cout << "   AKSES DITOLAK! 3x Percobaan Gagal   " << endl;
                cout << "========================================" << endl;
                cout << "Program dihentikan karena terlalu banyak" << endl;
                cout << "percobaan login yang gagal." << endl;
                cout << "========================================" << endl;
                programJalan = false;
                break;
            }

            bool tetapDiMenu = true;
            while (tetapDiMenu) {
                system("cls");
                cout << "=== DASHBOARD " << (sesiLogin.peran == "admin" ? "OFFICIAL ADMIN" : "SUPPORTER ZONE") << " ===" << endl;
                cout << "User Aktif: " << sesiLogin.username << endl;
                cout << "----------------------------------------" << endl;
                
                if (sesiLogin.peran == "admin") {
                    cout << "1. Rekrut Pemain Baru\n2. Lihat Daftar Skuad\n3. Update Harga\n4. Update Rating\n5. Jual Pemain\n6. Logout" << endl;
                } else {
                    cout << "1. Lihat Daftar Skuad\n2. Berikan Rating Pemain\n3. Logout" << endl;
                }
                
                int pilihanMenu;
                cout << "\nPilih Opsi: "; cin >> pilihanMenu;

                if (sesiLogin.peran == "admin") {
                    if (pilihanMenu == 1) {
                        system("cls");
                        cin.ignore();
                        string n, k, neg; long long h;
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

                        daftarPemain[jumlahDataPemain].namaLengkap = n;
                        daftarPemain[jumlahDataPemain].klubAsal = k;
                        daftarPemain[jumlahDataPemain].negaraAsal = neg;
                        daftarPemain[jumlahDataPemain].performa.hargaPasarUSD = h;
                        daftarPemain[jumlahDataPemain].performa.ratingPemain = 0;
                        daftarPemain[jumlahDataPemain].performa.jumlahPenilai = 0;
                        daftarPemain[jumlahDataPemain].performa.totalSkorRating = 0;
                        jumlahDataPemain++;
                        cout << "\nBerhasil Rekrut! Tekan Enter..."; cin.ignore(); cin.get();
                    }
                    else if (pilihanMenu == 2) { 
                        system("cls");
                        cout << "--- DAFTAR SKUAD MANCHESTER UNITED ---" << endl;
                        cout << setfill('=') << setw(80) << "=" << endl;
                        cout << setfill(' ') << left << setw(4) << "No" << setw(20) << "Nama" << setw(15) << "Asal" << setw(10) << "Rating" << setw(15) << "Harga" << endl;
                        cout << setfill('-') << setw(80) << "-" << endl;
                        for(int i=0; i<jumlahDataPemain; i++) {
                            cout << setfill(' ') << left << setw(4) << i+1 << setw(20) << daftarPemain[i].namaLengkap 
                                 << setw(15) << daftarPemain[i].klubAsal << setw(10) << fixed << setprecision(1) << daftarPemain[i].performa.ratingPemain 
                                 << "$" << setw(14) << daftarPemain[i].performa.hargaPasarUSD << endl;
                        }
                        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
                    }
                    else if (pilihanMenu == 3) { 
                        system("cls");
                        cout << "--- UPDATE HARGA PEMAIN ---" << endl;
                        if (jumlahDataPemain == 0) {
                            cout << "Belum ada pemain di skuad." << endl;
                        } else {
                            cout << setfill('=') << setw(50) << "=" << endl;
                            for(int i=0; i<jumlahDataPemain; i++) {
                                cout << setfill(' ') << left << setw(4) << i+1 
                                     << setw(25) << daftarPemain[i].namaLengkap 
                                     << "$" << daftarPemain[i].performa.hargaPasarUSD << endl;
                            }
                            cout << setfill('-') << setw(50) << "-" << endl;
                            int idx; long long hargaBaru;
                            cout << "Pilih nomor pemain: "; cin >> idx;
                            if (idx >= 1 && idx <= jumlahDataPemain) {
                                cout << "Harga baru (USD)  : "; cin >> hargaBaru;
                                daftarPemain[idx-1].performa.hargaPasarUSD = hargaBaru;
                                cout << "\nHarga berhasil diupdate!" << endl;
                            } else {
                                cout << "\nNomor pemain tidak valid!" << endl;
                            }
                        }
                        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
                    }
                    else if (pilihanMenu == 4) { 
                        system("cls");
                        cout << "--- UPDATE RATING PEMAIN (ADMIN) ---" << endl;
                        if (jumlahDataPemain == 0) {
                            cout << "Belum ada pemain di skuad." << endl;
                        } else {
                            cout << setfill('=') << setw(50) << "=" << endl;
                            for(int i=0; i<jumlahDataPemain; i++) {
                                cout << setfill(' ') << left << setw(4) << i+1 
                                     << setw(25) << daftarPemain[i].namaLengkap 
                                     << "Rating: " << fixed << setprecision(1) << daftarPemain[i].performa.ratingPemain << endl;
                            }
                            cout << setfill('-') << setw(50) << "-" << endl;
                            int idx; float ratingBaru;
                            cout << "Pilih nomor pemain : "; cin >> idx;
                            if (idx >= 1 && idx <= jumlahDataPemain) {
                                cout << "Rating baru (0-10) : "; cin >> ratingBaru;
                                if (ratingBaru >= 0 && ratingBaru <= 10) {
                                    daftarPemain[idx-1].performa.ratingPemain = ratingBaru;
                                    daftarPemain[idx-1].performa.totalSkorRating = ratingBaru;
                                    daftarPemain[idx-1].performa.jumlahPenilai = 1;
                                    cout << "\nRating berhasil diupdate!" << endl;
                                } else {
                                    cout << "\nRating harus antara 0 - 10!" << endl;
                                }
                            } else {
                                cout << "\nNomor pemain tidak valid!" << endl;
                            }
                        }
                        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
                    }
                    else if (pilihanMenu == 5) { 
                        system("cls");
                        cout << "--- JUAL / HAPUS PEMAIN ---" << endl;
                        if (jumlahDataPemain == 0) {
                            cout << "Belum ada pemain di skuad." << endl;
                        } else {
                            cout << setfill('=') << setw(50) << "=" << endl;
                            for(int i=0; i<jumlahDataPemain; i++) {
                                cout << setfill(' ') << left << setw(4) << i+1 
                                     << setw(25) << daftarPemain[i].namaLengkap 
                                     << "$" << daftarPemain[i].performa.hargaPasarUSD << endl;
                            }
                            cout << setfill('-') << setw(50) << "-" << endl;
                            int idx;
                            cout << "Pilih nomor pemain yang dijual: "; cin >> idx;
                            if (idx >= 1 && idx <= jumlahDataPemain) {
                                string konfirmasi;
                                cout << "Yakin ingin menjual " << daftarPemain[idx-1].namaLengkap << "? (ya/tidak): ";
                                cin >> konfirmasi;
                                if (konfirmasi == "ya" || konfirmasi == "Ya" || konfirmasi == "YA") {
                                    string namaTerjual = daftarPemain[idx-1].namaLengkap;
                                    for (int i = idx-1; i < jumlahDataPemain-1; i++) {
                                        daftarPemain[i] = daftarPemain[i+1];
                                    }
                                    jumlahDataPemain--;
                                    cout << "\n" << namaTerjual << " berhasil dijual!" << endl;
                                } else {
                                    cout << "\nPenjualan dibatalkan." << endl;
                                }
                            } else {
                                cout << "\nNomor pemain tidak valid!" << endl;
                            }
                        }
                        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
                    }
                    else if (pilihanMenu == 6) tetapDiMenu = false;
                } 
                else { // Menu User
                    if (pilihanMenu == 1) {
                        system("cls");
                        cout << "--- DAFTAR SKUAD (VIEW ONLY) ---" << endl;
                        cout << setfill('=') << setw(60) << "=" << endl;
                        cout << setfill(' ') << left << setw(4) << "No" << setw(25) << "Nama" << setw(15) << "Rating" << setw(15) << "Negara" << endl;
                        for(int i=0; i<jumlahDataPemain; i++) {
                            cout << setfill(' ') << left << setw(4) << i+1 << setw(25) << daftarPemain[i].namaLengkap 
                                 << setw(15) << fixed << setprecision(1) << daftarPemain[i].performa.ratingPemain 
                                 << setw(15) << daftarPemain[i].negaraAsal << endl;
                        }
                        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
                    }
                    else if (pilihanMenu == 2) { 
                        system("cls");
                        cout << "--- BERIKAN RATING PEMAIN ---" << endl;
                        if (jumlahDataPemain == 0) {
                            cout << "Belum ada pemain di skuad." << endl;
                        } else {
                            cout << setfill('=') << setw(60) << "=" << endl;
                            for(int i=0; i<jumlahDataPemain; i++) {
                                cout << setfill(' ') << left << setw(4) << i+1 
                                     << setw(25) << daftarPemain[i].namaLengkap 
                                     << "Rating saat ini: " << fixed << setprecision(1) << daftarPemain[i].performa.ratingPemain 
                                     << " (" << daftarPemain[i].performa.jumlahPenilai << " penilai)" << endl;
                            }
                            cout << setfill('-') << setw(60) << "-" << endl;
                            int idx; float skorUser;
                            cout << "Pilih nomor pemain : "; cin >> idx;
                            if (idx >= 1 && idx <= jumlahDataPemain) {
                                cout << "Beri rating (0-10): "; cin >> skorUser;
                                if (skorUser >= 0 && skorUser <= 10) {
                                    daftarPemain[idx-1].performa.totalSkorRating += skorUser;
                                    daftarPemain[idx-1].performa.jumlahPenilai++;
                                    daftarPemain[idx-1].performa.ratingPemain = 
                                        daftarPemain[idx-1].performa.totalSkorRating / daftarPemain[idx-1].performa.jumlahPenilai;
                                    cout << "\nTerima kasih! Rating " << daftarPemain[idx-1].namaLengkap 
                                         << " sekarang: " << fixed << setprecision(1) << daftarPemain[idx-1].performa.ratingPemain << endl;
                                } else {
                                    cout << "\nRating harus antara 0 - 10!" << endl;
                                }
                            } else {
                                cout << "\nNomor pemain tidak valid!" << endl;
                            }
                        }
                        cout << "\nTekan Enter..."; cin.ignore(); cin.get();
                    }
                    else if (pilihanMenu == 3) tetapDiMenu = false;
                }
            }
        }
    }
    return 0;
}