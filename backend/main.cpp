#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;


struct Destinasi {
    string nama;
    string lokasi;
    int harga;
};

vector<Destinasi> daftarDestinasi;
const string filePath = "../public/data.json"; // folder public berada di luar backend
void simpanKeJSON();

void tampilkanDaftarDenganNomor() {
    if (daftarDestinasi.empty()) {
        cout << "\n⚠️ Belum ada destinasi yang ditambahkan.\n";
        return;
    }
    cout << "\n===== Daftar Destinasi Wisata =====\n";
    for (int i = 0; i < daftarDestinasi.size(); i++) {
        cout << i + 1 << ". " << daftarDestinasi[i].nama << endl;
        cout << "   Lokasi: " << daftarDestinasi[i].lokasi << endl;
        cout << "   Harga Tiket: Rp" << daftarDestinasi[i].harga << endl;
        cout << "--------------------------\n";
    }
}


void tambahDestinasi(){
    Destinasi d;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // pastikan buffer bersih
    cout << "\nMasukkan nama destinasi: ";
    getline(cin, d.nama);
    cout << "Masukkan lokasi: ";
    getline(cin, d.lokasi);
    cout << "Masukkan harga tiket (Rp): ";
    cin >> d.harga;
    daftarDestinasi.push_back(d);
    cout << " Destinasi berhasil ditambahkan!\n";
}


void modifikasiDestinasi() {
    if (daftarDestinasi.empty()) {
        cout << "\n Belum ada destinasi yang ditambahkan.\n";
        return;
    }
    tampilkanDaftarDenganNomor();
    
    int nomor;
    cout << "Masukkan nomor destinasi yang ingin dimodifikasi (1-" << daftarDestinasi.size() << "): ";
    cin >> nomor;

    if (cin.fail() || nomor < 1 || nomor > daftarDestinasi.size()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << " Nomor tidak valid!\n";
        return;
    }

    int indexDestinasi = nomor - 1;
    int pilihModif;

    do {
        cout << "\n--- Modifikasi Destinasi: " << daftarDestinasi[indexDestinasi].nama << " ---\n";
        cout << "1. Ubah Nama\n";
        cout << "2. Ubah Lokasi\n";
        cout << "3. Ubah Harga Tiket\n";
        cout << "4. Selesai Modifikasi\n";
        cout << "Pilih yang ingin diubah: ";
        cin >> pilihModif;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (pilihModif) {
            case 1: {
                cout << "Nama saat ini: " << daftarDestinasi[indexDestinasi].nama << endl;
                cout << "Masukkan nama baru: ";
                getline(cin, daftarDestinasi[indexDestinasi].nama);
                cout << " Nama berhasil diubah!\n";
                break;
            }
            case 2: {
                cout << "Lokasi saat ini: " << daftarDestinasi[indexDestinasi].lokasi << endl;
                cout << "Masukkan lokasi baru: ";
                getline(cin, daftarDestinasi[indexDestinasi].lokasi);
                cout << " Lokasi berhasil diubah!\n";
                break;
            }
            case 3: {
                cout << "Harga saat ini: Rp" << daftarDestinasi[indexDestinasi].harga << endl;
                cout << "Masukkan harga baru (Rp): ";
                cin >> daftarDestinasi[indexDestinasi].harga;
                cout << " Harga berhasil diubah!\n";
                break;
            }
            case 4:
                cout << "💾 Menyimpan perubahan ke JSON...\n";
                simpanKeJSON();
                cout << " Modifikasi selesai!\n";
                break;
            default:
                cout << " Pilihan tidak valid.\n";
        }
    } while (pilihModif != 4);
}


void hapusDestinasi() {
    if (daftarDestinasi.empty()) {
        cout << "\n Belum ada destinasi yang ditambahkan.\n";
        return;
    }
    tampilkanDaftarDenganNomor();
    
    int nomor;
    cout << "Masukkan nomor destinasi yang ingin dihapus (1-" << daftarDestinasi.size() << "): ";
    cin >> nomor;

    if (cin.fail() || nomor < 1 || nomor > daftarDestinasi.size()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << " Nomor tidak valid!\n";
        return;
    }
    string konfirmasi;
    cout << "Apakah Anda yakin ingin menghapus destinasi \"" << daftarDestinasi[nomor-1].nama << "\"? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi == "y" || konfirmasi == "Y") {
        daftarDestinasi.erase(daftarDestinasi.begin() + nomor - 1);
        cout << " Destinasi berhasil dihapus!\n";
        simpanKeJSON(); // Simpan perubahan langsung ke JSON
    } else {
        cout << " Penghapusan dibatalkan.\n";
    }
}



void urutkanDestinasi() {
    for (int i = 0; i < daftarDestinasi.size() - 1; i++) {
        for (int j = 0; j < daftarDestinasi.size() - i - 1; j++) {
            if (daftarDestinasi[j].harga > daftarDestinasi[j + 1].harga) {
                swap(daftarDestinasi[j], daftarDestinasi[j + 1]);
            }
        }
    }
    cout << " Destinasi berhasil diurutkan berdasarkan harga!\n";
}
string toLowercase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}



void cariDestinasi() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string namaCari;
    cout << "\nMasukkan nama destinasi yang dicari: ";
    getline(cin, namaCari);
    
    if (namaCari.empty()) {
        cout << " Nama pencarian tidak boleh kosong.\n";
        return;
    }
    string namaCariLower = toLowercase(namaCari);
    bool ditemukan = false;
    cout << "\n Hasil Pencarian:\n";
    for (auto &d : daftarDestinasi) {
        if (toLowercase(d.nama).find(namaCariLower) != string::npos) {
            cout << " " << d.nama << endl;
            cout << "   Lokasi: " << d.lokasi << endl;
            cout << "   Harga Tiket: Rp" << d.harga << endl;
            cout << "--------------------------\n";
            ditemukan = true;
        }
    }
    if (!ditemukan) {
        cout << " Destinasi tidak ditemukan.\n";
    }
}

int totalBiaya(int index) {
    if (index == daftarDestinasi.size()) return 0;
    return daftarDestinasi[index].harga + totalBiaya(index + 1);
}

// Tampilkan daftar
void tampilkanDaftar() {
    if (daftarDestinasi.empty()) {
        cout << "\n Belum ada destinasi yang ditambahkan.\n";
        return;
    }

    cout << "\n===== Daftar Destinasi Wisata =====\n";
    for (auto &d : daftarDestinasi) {
        cout << "Nama: " << d.nama << endl;
        cout << "Lokasi: " << d.lokasi << endl;
        cout << "Harga Tiket: Rp" << d.harga << endl;
        cout << "--------------------------\n";
    }
    cout << "Total Biaya Semua Destinasi (rekursif): Rp" << totalBiaya(0) << endl;
}

// Fungsi Simpan ke JSON
void simpanKeJSON() {
    json j;
    for (auto &d : daftarDestinasi) {
        j["destinasi"].push_back({
            {"nama", d.nama},
            {"lokasi", d.lokasi},
            {"harga", d.harga}
        });
    }
    ofstream file(filePath);
    if (!file.is_open()) {
        cout << " Gagal menyimpan ke " << filePath << endl;
        return;
    }
    file << j.dump(4);
    file.close();
    cout << " Data berhasil disimpan ke " << filePath << endl;
}

// Fungsi Muat dari JSON
void muatDariJSON() {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << " File " << filePath << " belum ada, mulai dengan data kosong.\n";
        return;
    }

    json j;
    file >> j;
    file.close();

    daftarDestinasi.clear();

    for (auto &item : j["destinasi"]) {
        Destinasi d;
        d.nama = item["nama"];
        d.lokasi = item["lokasi"];
        d.harga = item["harga"];
        daftarDestinasi.push_back(d);
    }

    cout << " Data berhasil dimuat dari " << filePath 
         << " (" << daftarDestinasi.size() << " destinasi)\n";
}

int main() {
    int pilihan;

    // Muat data JSON di awal
    muatDariJSON();

    do {
        cout << "\n========== TRAVEL PLANNER ==========\n";
        cout << "1. Tambah Destinasi\n";
        cout << "2. Tampilkan & Urutkan Destinasi\n";
        cout << "3. Cari Destinasi\n";
        cout << "4. Modifikasi Destinasi\n";
        cout << "5. Hitung Total Biaya (rekursif)\n";
        cout << "6. Hapus Destinasi\n";
        cout << "7. Simpan ke JSON\n";
        cout << "8. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahDestinasi(); break;
            case 2: urutkanDestinasi(); tampilkanDaftar(); break;
            case 3: cariDestinasi(); break;
            case 4: modifikasiDestinasi(); break;
            case 5: cout << "\nTotal biaya semua destinasi: Rp" << totalBiaya(0) << endl; break;
            case 6: hapusDestinasi(); break;
            case 7: simpanKeJSON(); break;
            case 8: 
                simpanKeJSON();
                cout << "\nTerima kasih telah menggunakan Travel Planner!\n"; 
                break;
            default: 
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\n Pilihan tidak valid.\n";
        }
    } while (pilihan != 8);

    return 0;
}