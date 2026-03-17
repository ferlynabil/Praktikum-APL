#include <iostream>
using namespace std;

int main() {

// string buah[4] = {"Jeruk", "Mangga", "Nanas", "Apel"};

// cout << buah[1] << endl;
// return 0;

// buah[4] = "Rambutan";
// for (int i = 0; i < 5; i++) {
// cout << buah[i] << endl;
// }


// #define MAX_MAHASISWA 100 // Ukuran maksimum array


//     int panjang = 0; // Jumlah data mahasiswa saat ini
//     string mahasiswa[MAX_MAHASISWA]; // Array 1 dimensi

//     int pilihan, index;

//     do {
//         cout << "\n=== MENU PROGRAM DATA MAHASISWA ===" << endl;
//         cout << "1. Tampilkan Mahasiswa" << endl;
//         cout << "2. Tambah Mahasiswa" << endl;
//         cout << "3. Ubah Mahasiswa" << endl;
//         cout << "4. Hapus Mahasiswa" << endl;
//         cout << "5. Keluar" << endl;
//         cout << "Pilihan: ";
//         cin >> pilihan;

//         switch (pilihan) {

//         case 1: // READ
//             if (panjang == 0) {
//                 cout << "Belum ada mahasiswa." << endl;
//             } else {
//                 for (int i = 0; i < panjang; i++) {
//                     cout << "Mahasiswa ke-" << i + 1 
//                          << ": " << mahasiswa[i] << endl;
//                 }
//             }
//             break;

//         case 2: // CREATE
//             if (panjang < MAX_MAHASISWA) {
//                 cout << "Masukkan nama mahasiswa: ";
//                 cin.ignore();
//                 getline(cin, mahasiswa[panjang]);
//                 panjang++;
//                 cout << "Mahasiswa berhasil ditambahkan." << endl;
//             } else {
//                 cout << "Kapasitas penuh!" << endl;
//             }
//             break;

//         case 3: // UPDATE
//             if (panjang == 0) {
//                 cout << "Belum ada mahasiswa untuk diubah." << endl;
//             } else {
//                 for (int i = 0; i < panjang; i++) {
//                     cout << "Mahasiswa ke-" << i + 1 
//                          << ": " << mahasiswa[i] << endl;
//                 }

//                 cout << "Masukkan nomor mahasiswa yang akan diubah: ";
//                 cin >> index;

//                 if (index > 0 && index <= panjang) {
//                     cout << "Masukkan nama baru: ";
//                     cin.ignore();
//                     getline(cin, mahasiswa[index - 1]);
//                     cout << "Data berhasil diubah." << endl;
//                 } else {
//                     cout << "Nomor tidak valid." << endl;
//                 }
//             }
//             break;

//         case 4: // DELETE
//             if (panjang == 0) {
//                 cout << "Belum ada mahasiswa untuk dihapus." << endl;
//             } else {
//                 for (int i = 0; i < panjang; i++) {
//                     cout << "Mahasiswa ke-" << i + 1 
//                          << ": " << mahasiswa[i] << endl;
//                 }

//                 cout << "Masukkan nomor mahasiswa yang akan dihapus: ";
//                 cin >> index;

//                 if (index > 0 && index <= panjang) {
//                     for (int i = index - 1; i < panjang - 1; i++) {
//                         mahasiswa[i] = mahasiswa[i + 1]; 
//                     }
//                     panjang--;
//                     cout << "Mahasiswa berhasil dihapus." << endl;
//                 } else {
//                     cout << "Nomor tidak valid." << endl;
//                 }
//             }
//             break;

//         case 5:
//             cout << "Program selesai." << endl;
//             break;

//         default:
//             cout << "Pilihan tidak valid." << endl;
//         }

//     } while (pilihan != 5);

//     return 0;

int matriks[3][3] = {

{1, 2, 3}, 
{4, 5, 6},
{7, 8, 9} 

};

cout << matriks[0][1] << endl;
cout << matriks[2][0] << endl;

for (int i = 0; i < 3; i ++) { 
    for (int j = 0; j < 3; j ++) { 
        cout << matriks[i][j] << " ";
    }
    cout << endl;
}
for (auto &baris : matriks) { 
    for (auto &elemen : baris) { 
        cout << elemen << " ";
   }
   cout << endl;

        int nilai[2][2][2] = {
            { {80, 85}, {75, 90} }, 
            { {88, 92}, {70, 78} } 
        };

        cout << " = DATA NILAI MAHASISWA =\n\n";

        for (int k = 0; k < 2; k ++) {
            cout << "Kelas " << char('A' + k) << endl;
            
            for (int m = 0; m < 2; m ++) {
                cout << " Mahasiswa " << m + 1 << endl;
                cout << " UTS : " << nilai[k][m][0] << endl;
                cout << " UAS : " << nilai[k][m][1] << endl;
            }
            cout << endl;
       }
        return 0;
    }

    struct nama_struct {
        tipe_data1 elemen_struct;
        };

    struct mahasiswa {
        int nim;
        string nama;
        float ipk;

}