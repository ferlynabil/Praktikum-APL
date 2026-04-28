#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "fungsi.h"
using namespace std;
void menuRekrut() {
    layarBersih(); Tabel::cetakBanner("REKRUTMEN PEMAIN BARU");
    try {
        Validasi::validasiKapasitas(jumlahPemain, MAKS_PEMAIN, "pemain");
        cin.ignore();
        string nama = Validasi::bacaString("  Nama Lengkap : ");
        for (int i = 0; i < jumlahPemain; i++)
            if (daftarPemain[i].namaLengkap == nama)
                throw Validasi::DataDuplikat("Pemain \"" + nama + "\" sudah ada!");
        string klub   = Validasi::bacaString("  Klub Asal    : ");
        string negara = Validasi::bacaString("  Negara Asal  : ");
        long long h   = Validasi::bacaLongLong("  Harga (USD) $: ", 0LL);
        daftarPemain[jumlahPemain++] = {nama, klub, negara, {0, h, 0, 0}};
        Tabel::pesanOK("Pemain \"" + nama + "\" berhasil direkrut!");
    } catch (const exception& e) { Validasi::tanganiException(e); }
    tekanEnter();
}
void menuLihatSkuad(bool showHarga) {
    layarBersih();
    Tabel::cetakBanner(showHarga ? "SKUAD – ADMIN VIEW" : "SKUAD – SUPPORTER VIEW");
    cetakDaftarPemain(showHarga);
    tekanEnter();
}
void menuUpdateHarga() {
    layarBersih(); Tabel::cetakBanner("UPDATE HARGA PEMAIN");
    try {
        auto* p = pilihPemain(true);
        long long h = Validasi::bacaLongLong("  Harga baru $: ", 0LL);
        p->performa.hargaPasarUSD = h;
        Tabel::pesanOK("Harga " + p->namaLengkap + " -> $" + to_string(h));
    } catch (const exception& e) { Validasi::tanganiException(e); }
    tekanEnter();
}
void menuUpdateRating(bool isAdmin) {
    layarBersih(); Tabel::cetakBanner(isAdmin ? "UPDATE RATING – ADMIN" : "BERI RATING – SUPPORTER");
    try {
        auto* p   = pilihPemain(false);
        float s   = Validasi::bacaFloat("  Rating (0-10) : ", 0.0f, 10.0f);
        hitungRating(p, s, isAdmin);
        ostringstream ss; ss << fixed << setprecision(1) << p->performa.ratingPemain;
        Tabel::pesanOK("Rating " + p->namaLengkap + " -> " + ss.str());
    } catch (const exception& e) { Validasi::tanganiException(e); }
    tekanEnter();
}
void menuJual() {
    layarBersih(); Tabel::cetakBanner("JUAL PEMAIN");
    try {
        auto* p = pilihPemain(true);
        cout << "  Jual " << Warna::CYAN_T << p->namaLengkap << Warna::RESET << "? (ya/tidak): ";
        string k; cin >> k;
        transform(k.begin(), k.end(), k.begin(), [](unsigned char c){ return tolower(c); });
        if (k == "ya") {
            string nama = p->namaLengkap;
            int idx = (int)(p - daftarPemain);
            for (int i = idx; i < jumlahPemain-1; i++) daftarPemain[i] = daftarPemain[i+1];
            jumlahPemain--;
            Tabel::pesanOK(nama + " berhasil dijual!");
        } else Tabel::pesanInfo("Penjualan dibatalkan.");
    } catch (const exception& e) { Validasi::tanganiException(e); }
    tekanEnter();
}
void menuSorting() {
    layarBersih(); Tabel::cetakBanner("SORTING DATA PEMAIN");
    try {
        if (jumlahPemain == 0) throw runtime_error("Skuad kosong!");
        cout << "\n  " << Warna::MERAH_T << "1." << Warna::RESET << " Bubble Sort    – Nama (Z->A)\n"
             << "  " << Warna::MERAH_T << "2." << Warna::RESET << " Selection Sort – Harga (naik)\n"
             << "  " << Warna::MERAH_T << "3." << Warna::RESET << " Insertion Sort – Rating (turun)\n"
             << "  " << Warna::MERAH_T << "4." << Warna::RESET << " Kembali\n\n";
        int p = Validasi::bacaInt("  Pilih : ", 1, 4);
        if (p == 4) return;
        cout << Warna::KUNING_T << "\n  SEBELUM:\n" << Warna::RESET; cetakDaftarPemain(true);
        if      (p == 1) bubbleSort();
        else if (p == 2) selectionSort();
        else             insertionSort();
        cout << Warna::HIJAU_T << "\n  SESUDAH:\n" << Warna::RESET; cetakDaftarPemain(true);
        Tabel::pesanOK("Data berhasil diurutkan!");
    } catch (const exception& e) { Validasi::tanganiException(e); }
    tekanEnter();
}
void menuSearching(bool isAdmin) {
    layarBersih(); Tabel::cetakBanner("SEARCHING DATA PEMAIN");
    try {
        if (jumlahPemain == 0) throw runtime_error("Skuad kosong!");
        cout << "\n  " << Warna::MERAH_T << "1." << Warna::RESET << " Linear Search – Nama\n";
        if (isAdmin) cout << "  " << Warna::MERAH_T << "2." << Warna::RESET << " Binary Search – Harga\n";
        int maks = isAdmin ? 3 : 2;
        cout << "  " << Warna::MERAH_T << maks << "." << Warna::RESET << " Kembali\n\n";
        int p = Validasi::bacaInt("  Pilih : ", 1, maks);
        if (p == maks) return;
        layarBersih();
        if (p == 1) { cin.ignore(); string kw = Validasi::bacaString("  Kata kunci : "); linearSearch(kw); }
        else        { long long h = Validasi::bacaLongLong("  Target harga $: ", 0LL); binarySearch(h); }
    } catch (const exception& e) { Validasi::tanganiException(e); }
    tekanEnter();
}
#endif