#ifndef VALIDASI_H
#define VALIDASI_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <sstream>
#include "warna.h"
using namespace std;
namespace Validasi {
    class InputTidakValid : public invalid_argument {
    public:
        explicit InputTidakValid(const string& pesan)
            : invalid_argument("[InputTidakValid] " + pesan) {}
    };
    class IndeksLuarBatas : public out_of_range {
    public:
        explicit IndeksLuarBatas(const string& pesan)
            : out_of_range("[IndeksLuarBatas] " + pesan) {}
    };
    class KapasitasPenuh : public length_error {
    public:
        explicit KapasitasPenuh(const string& pesan)
            : length_error("[KapasitasPenuh] " + pesan) {}
    };
    class DataDuplikat : public logic_error {
    public:
        explicit DataDuplikat(const string& pesan)
            : logic_error("[DataDuplikat] " + pesan) {}
    };
    class GagalLogin : public runtime_error {
    public:
        explicit GagalLogin(const string& pesan)
            : runtime_error("[GagalLogin] " + pesan) {}
    };
    inline void bersihkanCin() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    inline int bacaInt(const string& prompt, int minVal, int maxVal) {
        int nilai;
        while (true) {
            cout << Warna::CYAN_T << prompt << Warna::RESET;
            if (cin >> nilai && nilai >= minVal && nilai <= maxVal) {
                return nilai;
            }
            bersihkanCin();
            throw InputTidakValid(
                "Input harus angka antara " + to_string(minVal) +
                " dan " + to_string(maxVal) + "!"
            );
        }
    }
    inline float bacaFloat(const string& prompt, float minVal, float maxVal) {
        float nilai;
        cout << Warna::CYAN_T << prompt << Warna::RESET;
        if (!(cin >> nilai)) {
            bersihkanCin();
            throw InputTidakValid("Input harus berupa angka desimal!");
        }
        if (nilai < minVal || nilai > maxVal) {
            throw InputTidakValid(
                "Nilai harus antara " + to_string((int)minVal) +
                " dan " + to_string((int)maxVal) + "!"
            );
        }
        return nilai;
    }
    inline long long bacaLongLong(const string& prompt, long long minVal) {
        long long nilai;
        cout << Warna::CYAN_T << prompt << Warna::RESET;
        if (!(cin >> nilai)) {
            bersihkanCin();
            throw InputTidakValid("Input harus berupa angka bulat (integer)!");
        }
        if (nilai < minVal) {
            throw InputTidakValid(
                "Nilai tidak boleh kurang dari " + to_string(minVal) + "!"
            );
        }
        return nilai;
    }
    inline string bacaString(const string& prompt) {
        string nilai;
        cout << Warna::CYAN_T << prompt << Warna::RESET;
        getline(cin, nilai);
        size_t start = nilai.find_first_not_of(" \t");
        if (start == string::npos || nilai.empty()) {
            throw InputTidakValid("Input tidak boleh kosong!");
        }
        return nilai.substr(start);
    }
    inline void validasiIndeks(int indeks, int jumlah, const string& konteks = "data") {
        if (indeks < 0 || indeks >= jumlah) {
            throw IndeksLuarBatas(
                "Nomor " + konteks + " tidak valid! "
                "Harus antara 1 dan " + to_string(jumlah) + "."
            );
        }
    }
    inline void validasiKapasitas(int jumlahSaatIni, int maksimal, const string& konteks = "data") {
        if (jumlahSaatIni >= maksimal) {
            throw KapasitasPenuh(
                "Database " + konteks + " sudah penuh! "
                "Kapasitas maksimal: " + to_string(maksimal) + "."
            );
        }
    }
    inline void tanganiException(const exception& e) {
        string pesan = e.what();
        if (pesan.find("[InputTidakValid]") != string::npos) {
            cout << Warna::BOLD << Warna::MERAH_T
                 << "\n  ✗ INPUT ERROR  : " << Warna::RESET
                 << Warna::MERAH_T << pesan.substr(18) << Warna::RESET << "\n";
        } else if (pesan.find("[IndeksLuarBatas]") != string::npos) {
            cout << Warna::BOLD << Warna::KUNING_T
                 << "\n  ✗ RANGE ERROR  : " << Warna::RESET
                 << Warna::KUNING_T << pesan.substr(18) << Warna::RESET << "\n";
        } else if (pesan.find("[KapasitasPenuh]") != string::npos) {
            cout << Warna::BOLD << Warna::MAGENTA_T
                 << "\n  ✗ KAPASITAS    : " << Warna::RESET
                 << Warna::MAGENTA_T << pesan.substr(17) << Warna::RESET << "\n";
        } else if (pesan.find("[DataDuplikat]") != string::npos) {
            cout << Warna::BOLD << Warna::KUNING_T
                 << "\n  ✗ DUPLIKAT     : " << Warna::RESET
                 << Warna::KUNING_T << pesan.substr(15) << Warna::RESET << "\n";
        } else if (pesan.find("[GagalLogin]") != string::npos) {
            cout << Warna::BOLD << Warna::MERAH_T
                 << "\n  ✗ LOGIN GAGAL  : " << Warna::RESET
                 << Warna::MERAH_T << pesan.substr(13) << Warna::RESET << "\n";
        } else {
            cout << Warna::BOLD << Warna::MERAH_T
                 << "\n  ✗ ERROR        : " << Warna::RESET
                 << Warna::MERAH_T << pesan << Warna::RESET << "\n";
        }
    }
}
#endif