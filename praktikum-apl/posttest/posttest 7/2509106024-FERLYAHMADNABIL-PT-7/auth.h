#ifndef AUTH_H
#define AUTH_H
#include <iostream>
#include <string>
#include "fungsi.h"
using namespace std;
void menuRegistrasi() {
    layarBersih(); Tabel::cetakBanner("REGISTRASI AKUN BARU");
    try {
        Validasi::validasiKapasitas(jumlahAkun, MAKS_AKUN, "akun");
        cin.ignore();
        string u = Validasi::bacaString("  Username : ");
        for (int i = 0; i < jumlahAkun; i++)
            if (databaseAkun[i].username == u)
                throw Validasi::DataDuplikat("Username \"" + u + "\" sudah digunakan!");
        string pw = Validasi::bacaString("  Password : ");
        databaseAkun[jumlahAkun++] = {u, pw, "user"};
        Tabel::pesanOK("Registrasi berhasil!");
    } catch (const exception& e) { Validasi::tanganiException(e); }
    tekanEnter();
}
Akun prosesLogin() {
    for (int coba = 0; coba < 3; coba++) {
        layarBersih(); Tabel::cetakBanner("LOGIN");
        cout << Warna::DIM << "  Percobaan " << coba+1 << "/3\n\n" << Warna::RESET;
        string u, pw;
        cout << Warna::CYAN_T << "  Username : " << Warna::RESET; cin >> u;
        cout << Warna::CYAN_T << "  Password : " << Warna::RESET; cin >> pw;
        for (int i = 0; i < jumlahAkun; i++)
            if (databaseAkun[i].username == u && databaseAkun[i].password == pw) {
                Tabel::pesanOK("Selamat datang, " + u + "!"); tekanEnter();
                return databaseAkun[i];
            }
        Tabel::pesanError("Username/password salah.");
        if (coba < 2) tekanEnter();
    }
    throw Validasi::GagalLogin("3x percobaan gagal. Akses ditolak!");
}
#endif