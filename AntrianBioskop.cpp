#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    string nama;
    string film;
    string jadwal;
    int jumlahTiket;
    Node* next;
};

class AntrianTiket {
private:
    Node* head;
    Node* tail;

public:
    AntrianTiket() {
        head = nullptr;
        tail = nullptr;
    }

    void tambahPembeli(string nama, string film, string jadwal, int jumlahTiket) {
        Node* baru = new Node;
        baru->nama = nama;
        baru->film = film;
        baru->jadwal = jadwal;
        baru->jumlahTiket = jumlahTiket;
        baru->next = nullptr;

        if (tail == nullptr) {
            head = tail = baru;
        } else {
            tail->next = baru;
            tail = baru;
        }

        cout << "✅ Pembeli '" << nama << "' masuk antrian untuk film '" << film
             << "' pada jam " << jadwal << " (" << jumlahTiket << " tiket)." << endl;
    }

    void layaniPembeli() {
        if (head == nullptr) {
            cout << "Antrian kosong. Tidak ada pembeli yang bisa dilayani." << endl;
            return;
        }

        Node* temp = head;
        cout << "\n🎟  Melayani pembeli..." << endl;
        cout << "-----------------------------" << endl;
        cout << "Nama      : " << temp->nama << endl;
        cout << "Film      : " << temp->film << endl;
        cout << "Jadwal    : " << temp->jadwal << endl;
        cout << "Jumlah    : " << temp->jumlahTiket << " tiket" << endl;
        cout << "-----------------------------" << endl;
        cout << "🎫 Tiket berhasil dicetak!" << endl;

        ofstream file("riwayat_pembeli.txt", ios::app);
        if (file.is_open()) {
            file << temp->nama << "," << temp->film << "," << temp->jadwal
                 << "," << temp->jumlahTiket << "\n";
            file.close();
        }

        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
    }

    void tampilkanAntrian() {
        if (head == nullptr) {
            cout << "Antrian kosong." << endl;
            return;
        }

        cout << "\n📋 Daftar Antrian Tiket:" << endl;
        Node* saatIni = head;
        int nomor = 1;
        while (saatIni != nullptr) {
            cout << nomor++ << ". " << saatIni->nama
                 << " | Film: " << saatIni->film
                 << " | Jam: " << saatIni->jadwal
                 << " | Tiket: " << saatIni->jumlahTiket << endl;
            saatIni = saatIni->next;
        }
    }

    void hapusPembeli(string nama) {
        if (head == nullptr) {
            cout << "Antrian kosong. Tidak ada pembeli yang bisa dihapus." << endl;
            return;
        }

        Node* temp = head;
        Node* prev = nullptr;

        while (temp != nullptr && temp->nama != nama) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Pembeli dengan nama '" << nama << "' tidak ditemukan." << endl;
            return;
        }

        if (prev == nullptr) {
            head = head->next; // Hapus head
        } else {
            prev->next = temp->next; // Hapus node di tengah atau akhir
        }

        if (temp == tail) {
            tail = prev; // Update tail jika perlu
        }

        delete temp;
        cout << "✅ Pembeli '" << nama << "' berhasil dihapus dari antrian." << endl;
    }

    void insertPembeliAtPosition(string nama, string film, string jadwal, int jumlahTiket, int posisi) {
        Node* baru = new Node;
        baru->nama = nama;
        baru->film = film;
        baru->jadwal = jadwal;
        baru->jumlahTiket = jumlahTiket;
        baru->next = nullptr;

        if (posisi == 1) {
            baru->next = head;
            head = baru;
            if (tail == nullptr) {
                tail = baru;
            }
            cout << "✅ Pembeli '" << nama << "' berhasil ditambahkan di posisi " << posisi << "." << endl;
            return;
        }

        Node* saatIni = head;
        for (int i = 1; saatIni != nullptr && i < posisi - 1; i++) {
            saatIni = saatIni->next;
        }

        if (saatIni == nullptr) {
            cout << "Posisi " << posisi << " tidak valid. Pembeli tidak ditambahkan." << endl;
            delete baru;
            return;
        }

        baru->next = saatIni->next;
        saatIni->next = baru;

        if (baru->next == nullptr) {
            tail = baru; // Update tail jika baru ditambahkan di akhir
        }

        cout << "✅ Pembeli '" << nama << "' berhasil ditambahkan di posisi " << posisi << "." << endl;
    }

    ~AntrianTiket() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

string pilihJadwal() {
    int pilihan;
    string jadwal;
    cout << "\nPilih Jadwal Film:" << endl;
    cout << "1. 13:00" << endl;
    cout << "2. 16:00" << endl;
    cout << "3. 19:00" << endl;
    cout << "Pilih jadwal (1-3): ";
    cin >> pilihan;

    switch (pilihan) {
        case 1: jadwal = "13:00"; break;
        case 2: jadwal = "16:00"; break;
        case 3: jadwal = "19:00"; break;
        default: jadwal = "Tidak diketahui"; break;
    }

    return jadwal;
}

void menu() {
    AntrianTiket antrian;
    int pilihan;
    string nama, film, jadwal;
    int tiket, posisi;

    do {
        cout << "\n🎬=== MENU ANTRIAN BIOSKOP ===🎬" << endl;
        cout << "1. Tambah Pembeli" << endl;
        cout << "2. Layani Pembeli" << endl;
        cout << "3. Tampilkan Antrian" << endl;
        cout << "4. Hapus Pembeli" << endl;
        cout << "5. Insert Pembeli di Posisi Tertentu" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Masukkan nama pembeli: ";
                getline(cin, nama);
                cout << "Masukkan nama film: ";
                getline(cin, film);
                jadwal = pilihJadwal();
                cout << "Jumlah tiket: ";
                cin >> tiket;
                cin.ignore();
                antrian.tambahPembeli(nama, film, jadwal, tiket);
                break;
            case 2:
                antrian.layaniPembeli();
                break;
            case 3:
                antrian.tampilkanAntrian();
                break;
            case 4:
                cout << "Masukkan nama pembeli yang ingin dihapus: ";
                getline(cin, nama);
                antrian.hapusPembeli(nama);
                break;
            case 5:
                cout << "Masukkan nama pembeli: ";
                getline(cin, nama);
                cout << "Masukkan nama film: ";
                getline(cin, film);
                jadwal = pilihJadwal();
                cout << "Jumlah tiket: ";
                cin >> tiket;
                cout << "Masukkan posisi untuk menambahkan pembeli: ";
                cin >> posisi;
                cin.ignore();
                antrian.insertPembeliAtPosition(nama, film, jadwal, tiket, posisi);
                break;
            case 6:
                cout << "Program selesai. Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 6);
}

int main() {
    menu();
    return 0;
}