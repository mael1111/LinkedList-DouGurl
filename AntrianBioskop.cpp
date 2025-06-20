#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>  // Untuk setw dan setfill
using namespace std;

// untuk menampilkan garis pembatas 
void garis(char karakter, int panjang) {
    cout << setfill(karakter) << setw(panjang) << "" << setfill(' ') << endl;
}

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

        cout << "\n✅ Pembeli '" << nama << "' masuk antrian untuk film '" << film
             << "' pada jam " << jadwal << " (" << jumlahTiket << " tiket)." << endl;
    }

    void layaniPembeli() {
        if (head == nullptr) {
            cout << "Antrian kosong. Tidak ada pembeli yang bisa dilayani." << endl;
            return;
        }

        Node* temp = head;
        garis('=', 40);
        cout << "🎟  MELAYANI PEMBELI" << endl;
        garis('=', 40);
        cout << left << setw(15) << "Nama" << ": " << temp->nama << endl;
        cout << left << setw(15) << "Film" << ": " << temp->film << endl;
        cout << left << setw(15) << "Jadwal" << ": " << temp->jadwal << endl;
        cout << left << setw(15) << "Jumlah Tiket" << ": " << temp->jumlahTiket << endl;
        garis('-', 40);
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

        garis('=', 50);
        cout << "📋 DAFTAR ANTRIAN TIKET BIOSKOP" << endl;
        garis('=', 50);
        cout << left << setw(5) << "No" 
             << setw(20) << "Nama Pembeli" 
             << setw(20) << "Film" 
             << setw(10) << "Jadwal" 
             << setw(10) << "Tiket" << endl;
        garis('-', 50);

        Node* saatIni = head;
        int nomor = 1;
        while (saatIni != nullptr) {
            cout << left << setw(5) << nomor++ 
                 << setw(20) << saatIni->nama 
                 << setw(20) << saatIni->film 
                 << setw(10) << saatIni->jadwal 
                 << setw(10) << saatIni->jumlahTiket << endl;
            saatIni = saatIni->next;
        }
        garis('=', 50);
    }

    void hapusPembeli(string nama) {
        if (head == nullptr) {
            cout << "\nAntrian kosong. Tidak ada pembeli yang bisa dihapus." << endl;
            return;
        }

        Node* temp = head;
        Node* prev = nullptr;

        while (temp != nullptr && temp->nama != nama) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "\n⚠ Pembeli dengan nama '" << nama << "' tidak ditemukan." << endl;
            return;
        }

        if (prev == nullptr) {
            head = head->next;
        } else {
            prev->next = temp->next;
        }

        if (temp == tail) {
            tail = prev;
        }

        cout << "\n✅ Pembeli '" << temp->nama << "' berhasil dihapus dari antrian." << endl;
        delete temp;
    }

    void insertPembeliAtPosition(string nama, string film, string jadwal, int jumlahTiket, int posisi) {
        Node* baru = new Node;
        baru->nama = nama;
        baru->film = film;
        baru->jadwal = jadwal;
        baru->jumlahTiket = jumlahTiket;

        if (posisi <= 1) {
            baru->next = head;
            head = baru;
            if (tail == nullptr) {
                tail = baru;
            }
            cout << "\n✅ Pembeli '" << nama << "' berhasil ditambahkan di posisi 1." << endl;
            return;
        }

        Node* saatIni = head;
        int i;
        for (i = 1; saatIni != nullptr && i < posisi - 1; i++) {
            saatIni = saatIni->next;
        }

        if (saatIni == nullptr) {
            baru->next = nullptr;
            tail->next = baru;
            tail = baru;
            cout << "\n⚠ Posisi " << posisi << " terlalu besar. Pembeli ditambahkan di akhir antrian." << endl;
        } else {
            baru->next = saatIni->next;
            saatIni->next = baru;
            if (baru->next == nullptr) {
                tail = baru;
            }
            cout << "\n✅ Pembeli '" << nama << "' berhasil ditambahkan di posisi " << posisi << "." << endl;
        }
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
        default: 
            cout << "Pilihan tidak valid. Default ke jam 13:00" << endl;
            jadwal = "13:00"; break;
    }

    return jadwal;
}

void displayHeader(const string& bioskop) {
    cout << "\n\n";
    garis('*', 60);
    cout << setw(30) << right << "BIOSKOP " << bioskop << endl;
    garis('*', 60);
}

void menu() {
    const string NAMA_BIOSKOP = "DouGurl";
    AntrianTiket antrian;
    int pilihan;
    string nama, film, jadwal;
    int tiket, posisi;

    displayHeader(NAMA_BIOSKOP);

    do {
        garis('-', 40);
        cout << "🎬 MENU UTAMA" << endl;
        garis('-', 40);
        cout << "1. Tambah Pembeli" << endl;
        cout << "2. Layani Pembeli" << endl;
        cout << "3. Tampilkan Antrian" << endl;
        cout << "4. Hapus Pembeli" << endl;
        cout << "5. Insert Pembeli di Posisi Tertentu" << endl;
        cout << "6. Keluar" << endl;
        garis('-', 40);
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "\n━━━━ TAMBAH PEMBELI ━━━━" << endl;
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
                cout << "\n━━━━ HAPUS PEMBELI ━━━━" << endl;
                cout << "Masukkan nama pembeli yang ingin dihapus: ";
                getline(cin, nama);
                antrian.hapusPembeli(nama);
                break;
            case 5:
                cout << "\n━━━━ INSERT PEMBELI ━━━━" << endl;
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
                cout << "\nTerima kasih telah menggunakan layanan Bioskop " << NAMA_BIOSKOP << "!" << endl;
                break;
            default:
                cout << "\n⚠ Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 6);
}

int main() {
    system("cls");  
    menu();
    return 0;
}