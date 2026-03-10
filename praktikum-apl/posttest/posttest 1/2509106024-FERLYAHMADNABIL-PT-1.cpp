#include <iostream>
using namespace std;

int main() {
    string namaUser, passwordUser;
    int percobaanLogin = 0;
    int pilihanMenu;
    bool loginBerhasil = false;
    
    double nilaiMeter, nilaiKilometer, nilaiCentimeter;
    double hasilMeter, hasilKilometer, hasilCentimeter;

    cout << "====== SISTEM KONVERSI PANJANG =======\n";

    while (percobaanLogin < 3 && !loginBerhasil) {
        cout << "\n===== LOGIN =====\n";
        cout << "Masukkan Nama     : ";
        cin >> namaUser;
        cout << "Masukkan Password : ";
        cin >> passwordUser;

        if (namaUser == "nabil" && passwordUser == "024") {
            cout << "\nLogin Berhasil!\n";
            loginBerhasil = true;
        } else {
            percobaanLogin++;
            cout << "Login Gagal! Percobaan ke-" << percobaanLogin << endl;
        }
    }

    if (!loginBerhasil) {
        cout << "\nAkses Ditolak! Program Berhenti.\n";
        return 0;
    }

    do {
        cout << "\n============MENU UTAMA============\n";
        cout << "1. Meter ke Kilometer dan Centimeter\n";
        cout << "2. Kilometer ke Meter dan Centimeter\n";
        cout << "3. Centimeter ke Meter dan Kilometer\n";
        cout << "4. Keluar\n";
        cout << "Pilih Menu (1-4): ";
        cin >> pilihanMenu;

        if (pilihanMenu == 1) {
            cout << "\nMasukkan nilai dalam Meter: ";
            cin >> nilaiMeter;
            hasilKilometer = nilaiMeter / 1000;
            hasilCentimeter = nilaiMeter * 100;
            cout << "Hasil: " << hasilKilometer << " km dan "
                 << hasilCentimeter << " cm\n";
        }
        else if (pilihanMenu == 2) {
            cout << "\nMasukkan nilai dalam Kilometer: ";
            cin >> nilaiKilometer;
            hasilMeter = nilaiKilometer * 1000;
            hasilCentimeter = nilaiKilometer * 100000;
            cout << "Hasil: " << hasilMeter << " m dan "
                 << hasilCentimeter << " cm\n";
        }
        else if (pilihanMenu == 3) {
            cout << "\nMasukkan nilai dalam Centimeter: ";
            cin >> nilaiCentimeter;
            hasilMeter = nilaiCentimeter / 100;
            hasilKilometer = nilaiCentimeter / 100000;
            cout << "Hasil: " << hasilMeter << " m dan "
                 << hasilKilometer << " km\n";
        }
        else if (pilihanMenu == 4) {
            cout << "\nTerima kasih telah menggunakan program.\n";
        }
        else {
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihanMenu != 4);

    return 0;
}