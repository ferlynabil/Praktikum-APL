#ifndef DATA_H
#define DATA_H
#include <string>
using namespace std;
struct DataTeknis { float ratingPemain; long long hargaPasarUSD; int jumlahPenilai; float totalSkorRating; };
struct PemainMU   { string namaLengkap, klubAsal, negaraAsal; DataTeknis performa; };
struct Akun       { string username, password, peran; };
const int MAKS_PEMAIN = 100, MAKS_AKUN = 50;
extern PemainMU daftarPemain[MAKS_PEMAIN];
extern Akun     databaseAkun[MAKS_AKUN];
extern int      jumlahPemain, jumlahAkun;
#endif