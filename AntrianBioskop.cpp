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
   