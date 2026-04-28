#ifndef TABEL_H
#define TABEL_H
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "warna.h"
using namespace std;
namespace Tabel {
    const int W_NO     = 4;
    const int W_NAMA   = 22;
    const int W_KLUB   = 18;
    const int W_NEGARA = 12;
    const int W_RATING = 9;
    const int W_HARGA  = 16;
    const int W_TOTAL  = W_NO + W_NAMA + W_KLUB + W_NEGARA + W_RATING + W_HARGA + 2;

    inline void garis(char c, int lebar, const string& warna) {
        cout << warna;
        for (int i = 0; i < lebar; i++) cout << c;
        cout << Warna::RESET << "\n";
    }

    inline void headerPemain(bool showHarga = true) {
        garis('=', W_TOTAL, Warna::MERAH);
        cout << Warna::BOLD << Warna::BG_MERAH << Warna::PUTIH_T
             << left << setw(W_NO) << " No" << setw(W_NAMA) << " Nama Pemain"
             << setw(W_KLUB) << " Klub Asal" << setw(W_NEGARA) << " Negara"
             << setw(W_RATING) << " Rating";
        if (showHarga) cout << setw(W_HARGA) << " Harga (USD)";
        cout << Warna::RESET << "\n";
        garis('-', W_TOTAL, Warna::MERAH);
    }

    inline void barisPemain(int no, const string& nama, const string& klub,
                             const string& negara, float rating, long long harga,
                             bool showHarga = true) {
        string wR = (rating >= 7.0f) ? Warna::HIJAU_T : (rating >= 5.0f) ? Warna::KUNING_T : Warna::MERAH_T;
        ostringstream rs, hs;
        rs << fixed << setprecision(1) << rating;
        hs << " $" << harga;
        cout << Warna::PUTIH_T  << left << setw(W_NO)     << (" " + to_string(no))
             << Warna::CYAN_T           << setw(W_NAMA)   << (" " + nama)
             << Warna::DIM              << setw(W_KLUB)   << (" " + klub)
             << Warna::RESET
             << Warna::PUTIH_T          << setw(W_NEGARA) << (" " + negara)
             << Warna::BOLD << wR       << setw(W_RATING) << (" " + rs.str())
             << Warna::RESET;
        if (showHarga) cout << Warna::KUNING_T << setw(W_HARGA) << hs.str();
        cout << Warna::RESET << "\n";
    }

    inline void footerTabel(int n, bool ok = true) {
        garis('=', W_TOTAL, Warna::MERAH);
        if (ok) cout << Warna::BOLD << Warna::HIJAU_T << " [OK] Total: " << n << " pemain" << Warna::RESET << "\n";
        else    cout << Warna::BOLD << Warna::MERAH_T << " [--] Tidak ada data"              << Warna::RESET << "\n";
    }

    inline void cetakBanner(const string& judul, int lebar = W_TOTAL) {
        garis('=', lebar, Warna::MERAH);
        int pad = (lebar - (int)judul.size()) / 2;
        cout << Warna::BOLD << Warna::BG_MERAH << Warna::PUTIH_T
             << string(pad, ' ') << judul << string(lebar - pad - (int)judul.size(), ' ')
             << Warna::RESET << "\n";
        garis('=', lebar, Warna::MERAH);
    }

    inline void pesanOK(const string& p)       { cout << Warna::BOLD << Warna::HIJAU_T << " [OK] " << Warna::RESET << Warna::HIJAU_T  << p << Warna::RESET << "\n"; }
    inline void pesanError(const string& p)    { cout << Warna::BOLD << Warna::MERAH_T << " [!!] " << Warna::RESET << Warna::MERAH_T  << p << Warna::RESET << "\n"; }
    inline void pesanInfo(const string& p)     { cout << Warna::BOLD << Warna::BIRU_T  << " [--] " << Warna::RESET << Warna::BIRU_T   << p << Warna::RESET << "\n"; }
    inline void pesanPeringatan(const string& p){ cout << Warna::BOLD << Warna::KUNING_T<< " [**] " << Warna::RESET << Warna::KUNING_T << p << Warna::RESET << "\n"; }
}
#endif