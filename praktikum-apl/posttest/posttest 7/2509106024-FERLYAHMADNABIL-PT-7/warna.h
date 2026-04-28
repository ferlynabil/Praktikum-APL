#ifndef WARNA_H
#define WARNA_H
#include <string>
#include <iostream>
using namespace std;
namespace Warna {
    const string RESET   = "\033[0m";
    const string BOLD    = "\033[1m";
    const string DIM     = "\033[2m";
    const string MERAH   = "\033[31m";
    const string HIJAU   = "\033[32m";
    const string KUNING  = "\033[33m";
    const string BIRU    = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN    = "\033[36m";
    const string PUTIH   = "\033[37m";
    const string MERAH_T   = "\033[91m";
    const string HIJAU_T   = "\033[92m";
    const string KUNING_T  = "\033[93m";
    const string BIRU_T    = "\033[94m";
    const string MAGENTA_T = "\033[95m";
    const string CYAN_T    = "\033[96m";
    const string PUTIH_T   = "\033[97m";
    const string BG_MERAH   = "\033[41m";
    const string BG_HIJAU   = "\033[42m";
    const string BG_KUNING  = "\033[43m";
    const string BG_BIRU    = "\033[44m";
    const string BG_MAGENTA = "\033[45m";
    const string BG_CYAN    = "\033[46m";
    const string BG_PUTIH   = "\033[47m";
    const string BG_HITAM   = "\033[40m";
    inline void cetakWarna(const string& teks, const string& warna, bool newline = true) {
        cout << warna << teks << RESET;
        if (newline) cout << "\n";
    }
    inline void cetakBold(const string& teks, const string& warna = PUTIH_T, bool newline = true) {
        cout << BOLD << warna << teks << RESET;
        if (newline) cout << "\n";
    }
    inline string beri(const string& teks, const string& warna) {
        return warna + teks + RESET;
    }
    inline string beriBold(const string& teks, const string& warna) {
        return BOLD + warna + teks + RESET;
    }
}
#endif