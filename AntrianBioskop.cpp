   #include <iostream>
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
   };

   struct Node {
    string nama;
    string film;
    string jadwal;
    int jumlahTiket;
    Node* next;
};

Node* head = nullptr;
Node* tail = nullptr;
   
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
       cout << "🎟  MELAYANI PEMBELI" << endl;
       cout << "Nama: " << temp->nama << endl;
       cout << "Film: " << temp->film << endl;
       cout << "Jadwal: " << temp->jadwal << endl;
       cout << "Jumlah Tiket: " << temp->jumlahTiket << endl;

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

       cout << "📋 DAFTAR ANTRIAN TIKET BIOSKOP" << endl;
       Node* saatIni = head;
       int nomor = 1;
       while (saatIni != nullptr) {
           cout << nomor++ << ". " << saatIni->nama << " - " << saatIni->film << endl;
           saatIni = saatIni->next;
       }
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
       for (int i = 1; saatIni != nullptr && i < posisi - 1; i++) {
           saatIni = saatIni->next;
       }

       if (saatIni == nullptr) {
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

   void menu() {
       const string NAMA_BIOSKOP = "DouGurl";
       AntrianTiket antrian;
       int pilihan;
       string nama, film, jadwal;
       int tiket, posisi;

       do {
           cout << "🎬 MENU UTAMA" << endl;
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
                   // Tambah pembeli
                   break;
               case 2:
                   antrian.layaniPembeli();
                   break;
               case 3:
                   antrian.tampilkanAntrian();
                   break;
               case 4:
                   // Hapus pembeli
                   break;
               case 5:
                   // Insert pembeli
                   break;
               case 6:
                   cout << "Terima kasih!" << endl;
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
   