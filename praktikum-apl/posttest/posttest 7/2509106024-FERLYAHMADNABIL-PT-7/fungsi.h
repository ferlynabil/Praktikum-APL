#ifndef FUNGSI_H
#define FUNGSI_H
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include "data.h"
#include "warna.h"
#include "tabel.h"
#include "validasi.h"
using namespace std;
inline void layarBersih() { system("clear"); }
inline void tekanEnter()  {
    cout << Warna::DIM << "\n  Tekan Enter..." << Warna::RESET;
    cin.ignore(); cin.get();
}
inline PemainMU* getPemain(int idx) {
    if (idx < 0 || idx >= jumlahPemain) return nullptr;
    return &daftarPemain[idx];
}
inline void cetakDaftarPemain(bool showHarga) {
    Tabel::headerPemain(showHarga);
    for (int i = 0; i < jumlahPemain; i++) {
        auto* p = getPemain(i);
        Tabel::barisPemain(i+1, p->namaLengkap, p->klubAsal,
                           p->negaraAsal, p->performa.ratingPemain,
                           p->performa.hargaPasarUSD, showHarga);
    }
    Tabel::footerTabel(jumlahPemain, jumlahPemain > 0);
}
inline void hitungRating(PemainMU* p, float skor, bool reset = false) {
    if (reset) { p->performa.totalSkorRating = 0; p->performa.jumlahPenilai = 0; }
    p->performa.totalSkorRating += skor;
    p->performa.jumlahPenilai   += 1;
    p->performa.ratingPemain     = p->performa.totalSkorRating / p->performa.jumlahPenilai;
}
inline PemainMU* pilihPemain(bool showHarga = false) {
    if (jumlahPemain == 0) throw runtime_error("Skuad kosong!");
    cetakDaftarPemain(showHarga);
    int no = Validasi::bacaInt("\n  Pilih nomor pemain : ", 1, jumlahPemain);
    PemainMU* p = getPemain(no - 1);
    if (!p) throw Validasi::IndeksLuarBatas("Nomor tidak valid!");
    return p;
}
inline void bubbleSort() {
    for (int i = 0; i < jumlahPemain-1; i++)
        for (int j = 0; j < jumlahPemain-i-1; j++)
            if (daftarPemain[j].namaLengkap < daftarPemain[j+1].namaLengkap)
                swap(daftarPemain[j], daftarPemain[j+1]);
}
inline void selectionSort() {
    for (int i = 0; i < jumlahPemain-1; i++) {
        int m = i;
        for (int j = i+1; j < jumlahPemain; j++)
            if (daftarPemain[j].performa.hargaPasarUSD < daftarPemain[m].performa.hargaPasarUSD) m = j;
        if (m != i) swap(daftarPemain[i], daftarPemain[m]);
    }
}
inline void insertionSort() {
    for (int i = 1; i < jumlahPemain; i++) {
        PemainMU k = daftarPemain[i]; int j = i-1;
        while (j >= 0 && daftarPemain[j].performa.ratingPemain < k.performa.ratingPemain)
            { daftarPemain[j+1] = daftarPemain[j]; j--; }
        daftarPemain[j+1] = k;
    }
}
inline void linearSearch(const string& keyword) {
    string kw = keyword;
    transform(kw.begin(), kw.end(), kw.begin(), [](unsigned char c){ return tolower(c); });
    Tabel::cetakBanner("LINEAR SEARCH – O(n)");
    Tabel::headerPemain(true);
    int found = 0;
    for (int i = 0; i < jumlahPemain; i++) {
        string nl = daftarPemain[i].namaLengkap;
        transform(nl.begin(), nl.end(), nl.begin(), [](unsigned char c){ return tolower(c); });
        if (nl.find(kw) != string::npos) {
            found++;
            auto* p = &daftarPemain[i];
            Tabel::barisPemain(found, p->namaLengkap, p->klubAsal,
                               p->negaraAsal, p->performa.ratingPemain, p->performa.hargaPasarUSD);
        }
    }
    Tabel::footerTabel(found, found > 0);
    found > 0 ? Tabel::pesanOK("Ditemukan " + to_string(found) + " pemain.")
              : Tabel::pesanError("Tidak ada pemain dengan nama \"" + keyword + "\"");
}
inline void binarySearch(long long target) {
    PemainMU sorted[MAKS_PEMAIN];
    for (int i = 0; i < jumlahPemain; i++) sorted[i] = daftarPemain[i];
    for (int i = 0; i < jumlahPemain-1; i++) {
        int m = i;
        for (int j = i+1; j < jumlahPemain; j++)
            if (sorted[j].performa.hargaPasarUSD < sorted[m].performa.hargaPasarUSD) m = j;
        if (m != i) swap(sorted[i], sorted[m]);
    }
    Tabel::cetakBanner("BINARY SEARCH – O(log n)");
    cout << Warna::BIRU_T << "  Target: $" << target << "\n" << Warna::RESET;
    int lo = 0, hi = jumlahPemain-1, hasil = -1;
    while (lo <= hi) {
        int mid = lo + (hi-lo)/2;
        cout << Warna::DIM << "  lo=" << lo << " mid=" << mid << " hi=" << hi
             << " | cek $" << sorted[mid].performa.hargaPasarUSD << Warna::RESET << "\n";
        if      (sorted[mid].performa.hargaPasarUSD == target) { hasil = mid; break; }
        else if (sorted[mid].performa.hargaPasarUSD  < target)   lo = mid+1;
        else                                                       hi = mid-1;
    }
    Tabel::headerPemain(true);
    int found = 0;
    for (int i = 0; i < jumlahPemain; i++)
        if (sorted[i].performa.hargaPasarUSD == target) {
            found++;
            Tabel::barisPemain(found, sorted[i].namaLengkap, sorted[i].klubAsal,
                               sorted[i].negaraAsal, sorted[i].performa.ratingPemain, sorted[i].performa.hargaPasarUSD);
        }
    Tabel::footerTabel(found, found > 0);
    hasil != -1 ? Tabel::pesanOK("Ditemukan " + to_string(found) + " pemain.")
                : Tabel::pesanError("Tidak ada pemain dengan harga $" + to_string(target));
}
#endif