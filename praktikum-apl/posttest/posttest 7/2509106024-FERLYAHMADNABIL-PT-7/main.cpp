#include "auth.h"
#include "menu.h"
PemainMU daftarPemain[MAKS_PEMAIN];
Akun     databaseAkun[MAKS_AKUN];
int      jumlahPemain = 0, jumlahAkun = 0;
int main() {
    databaseAkun[jumlahAkun++] = {"nabil","024","admin"};
    databaseAkun[jumlahAkun++] = {"ewok", "024","user"};
    daftarPemain[jumlahPemain++] = {"Bryan Mbeumo",   "Brentford",    "Kamerun",  {0,70000000LL,0,0}};
    daftarPemain[jumlahPemain++] = {"Matheus Cunha",  "Watford",      "Brasil",   {0,62000000LL,0,0}};
    daftarPemain[jumlahPemain++] = {"Benjamin Sesko", "RB Leipzig",   "Slovenia", {0,75000000LL,0,0}};
    daftarPemain[jumlahPemain++] = {"Senne Lammens",  "Royal Antwerp","Belgia",   {0,18000000LL,0,0}};
    daftarPemain[jumlahPemain++] = {"Casemiro",       "Real Madrid",  "Brasil",   {0,22000000LL,0,0}};
    while (true) {
        layarBersih();
        Tabel::cetakBanner("MANCHESTER UNITED MANAGER SYSTEM  v8.0");
        cout << "\n"
             << "  " << Warna::MERAH_T << "1." << Warna::RESET << " Login\n"
             << "  " << Warna::MERAH_T << "2." << Warna::RESET << " Registrasi\n"
             << "  " << Warna::MERAH_T << "3." << Warna::RESET << " Keluar\n\n";
        int p;
        try { p = Validasi::bacaInt("  Pilihan : ", 1, 3); }
        catch (const exception& e) { Validasi::tanganiException(e); tekanEnter(); continue; }
        if (p == 2) { menuRegistrasi(); continue; }
        if (p == 3) { layarBersih(); Tabel::cetakBanner("GLORY GLORY MAN UNITED!"); cout << "\n"; break; }
        Akun sesi;
        try { sesi = prosesLogin(); }
        catch (const exception& e) {
            layarBersih(); Tabel::cetakBanner("AKSES DITOLAK");
            Validasi::tanganiException(e); tekanEnter(); break;
        }
        bool diMenu = true;
        while (diMenu) {
            layarBersih();
            bool isAdmin = (sesi.peran == "admin");
            Tabel::cetakBanner(isAdmin ? "DASHBOARD ADMIN" : "DASHBOARD SUPPORTER");
            cout << Warna::DIM << "\n  User: " << Warna::RESET
                 << Warna::CYAN_T << sesi.username << " "
                 << (isAdmin ? Warna::MERAH_T + "[ADMIN]" : Warna::HIJAU_T + "[SUPPORTER]")
                 << Warna::RESET << "\n\n";
            int menu, maks;
            if (isAdmin) {
                cout << "  " << Warna::MERAH_T << "1." << Warna::RESET << " Rekrut Pemain\n"
                     << "  " << Warna::MERAH_T << "2." << Warna::RESET << " Lihat Skuad\n"
                     << "  " << Warna::MERAH_T << "3." << Warna::RESET << " Update Harga\n"
                     << "  " << Warna::MERAH_T << "4." << Warna::RESET << " Update Rating\n"
                     << "  " << Warna::MERAH_T << "5." << Warna::RESET << " Jual Pemain\n"
                     << "  " << Warna::MERAH_T << "6." << Warna::RESET << " Sorting\n"
                     << "  " << Warna::MERAH_T << "7." << Warna::RESET << " Searching\n"
                     << "  " << Warna::MERAH_T << "8." << Warna::RESET << " Logout\n\n";
                maks = 8;
            } else {
                cout << "  " << Warna::MERAH_T << "1." << Warna::RESET << " Lihat Skuad\n"
                     << "  " << Warna::MERAH_T << "2." << Warna::RESET << " Beri Rating\n"
                     << "  " << Warna::MERAH_T << "3." << Warna::RESET << " Searching\n"
                     << "  " << Warna::MERAH_T << "4." << Warna::RESET << " Logout\n\n";
                maks = 4;
            }
            try { menu = Validasi::bacaInt("  Pilih : ", 1, maks); }
            catch (const exception& e) { Validasi::tanganiException(e); tekanEnter(); continue; }
            if (isAdmin) {
                switch(menu) {
                    case 1: menuRekrut();            break;
                    case 2: menuLihatSkuad(true);    break;
                    case 3: menuUpdateHarga();       break;
                    case 4: menuUpdateRating(true);  break;
                    case 5: menuJual();              break;
                    case 6: menuSorting();           break;
                    case 7: menuSearching(true);     break;
                    case 8: diMenu = false;          break;
                }
            } else {
                switch(menu) {
                    case 1: menuLihatSkuad(false);   break;
                    case 2: menuUpdateRating(false); break;
                    case 3: menuSearching(false);    break;
                    case 4: diMenu = false;          break;
                }
            }
        }
    }
    return 0;
}