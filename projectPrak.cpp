#include <iostream>
#include <fstream>
using namespace std;
//struct
struct mahasiswa{
    string nama, nim, jurusan;
};
struct dosen{
    string nama, nip, prodi;
};
struct matkul{
    string nama, kode;
    int sks;
};
struct nilai{
    string nim, mataKuliah;
    float nilai;
};
//deklarasi array
mahasiswa daftarMahasiswa[100];
dosen daftarDosen[100];
matkul daftarMatkul[100];
nilai daftarNilai[100];
//variabel untuk jumlah data
int jumlahMahasiswa = 0;
int jumlahDosen = 0;
int jumlahMatkul = 0;
int jumlahNilai = 0;
//function
//login
bool login(string& username, string& password, string& role) {
    cout << "\n======= LOGIN =======\n";
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;
    ifstream file("user.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file user.txt\n";
        return false;
    }
    string user, pass, r;
    while (file >> user >> pass >> r) {
        if (user == username && pass == password) {
            role = r;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
//signup
void signup() {
    string newUser, newPass, newRole;
    cout << "\n======= SIGN UP =======\n";
    cout << "Masukkan username: "; cin >> newUser;
    cout << "Masukkan password: "; cin >> newPass;
    do {
        cout << "Masukkan role (mahasiswa/dosen): "; cin >> newRole;
        if (newRole != "mahasiswa" && newRole != "dosen") {
            cout << "Role tidak valid. Masukkan 'mahasiswa' atau 'dosen'.\n";
        }
    } while (newRole != "mahasiswa" && newRole != "dosen");
    // membaca semua data dari file
    ifstream inFile("user.txt");
    if (!inFile.is_open()) {
        cout << "Gagal membuka file.\n";
        return;
    }
    // mengecek apakah username sudah ada
    string semuaData = ""; //variabel untuk menyimpan data
    string user, pass, role;
    bool userSudahAda = false; // mengecek ussername sudah digunakan/tidak
    while (inFile >> user >> pass >> role) {
        if (user == newUser) { // jika ditemukan username yg sama
            userSudahAda = true;
        }
        semuaData += user + " " + pass + " " + role + "\n";
    }
    inFile.close();
    if (userSudahAda) {
        cout << "Username sudah digunakan! Masukkan username lain.\n";
        return;
    }
    // menambahkan user baru ke data
    semuaData += newUser + " " + newPass + " " + newRole + "\n";
    // menulis ulang ke file
    ofstream outFile("user.txt");
    if (!outFile.is_open()) {
        cout << "Gagal membuka file.\n";
        return;
    }
    outFile << semuaData;
    outFile.close();
    cout << "User berhasil ditambahkan!\n";
}
void menuInputData();
void menuTampilData();
void menuHapusData();
void menuCariData();
void menuSortingData();
void simpanKeFile();
void loadDariFile();
//menu utama
int main() {
    string username, password, role;
    int pilih;
    while (true) {
        system("cls");
        cout << "======= MENU =======\n";
        cout << "[1] Login\n";
        cout << "[2] Sign Up\n";
        cout << "[3] Exit\n";
        cout << "Pilih menu: "; cin >> pilih;
        if (pilih == 1) {
            if (login(username, password, role)) {
                system("cls");
                cout << "\nLogin berhasil sebagai: " << role << endl;
                loadDariFile(); //memuat data dari file sebelum akses
                if (role == "mahasiswa") {
                    cout << "Selamat datang, Mahasiswa!\n";
                    do{
                        cout << "+==========================+" << endl;
                        cout << "|       PILIHAN MENU       |" << endl;
                        cout << "+==========================+" << endl;
                        cout << "[1] Tampil Data" << endl;
                        cout << "[2] Cari Data" << endl;
                        cout << "[3] Sorting Data" << endl;
                        cout << "[4] Logout" << endl;
                        cout << "============================" << endl;
                        cout << "Pilih Menu : "; cin >> pilih; cin.ignore();
                        if (pilih < 1 || pilih > 4){
                            cout << "Maaf menu tidak tersedia, silahkan pilih ulang!" << endl;
                        }else{
                            switch (pilih){
                                case 1:
                                    menuTampilData();
                                    break;
                                case 2:
                                    menuCariData();
                                    break;
                                case 3:
                                    menuSortingData();
                                    break;
                                case 4:
                                    cout << "Terima kasih telah menggunakan program ini!" << endl;
                                    break;
                                default:
                                    cout << "Pilihan menu tidak tersedia, silahkan pilih ulang!" << endl;
                                    break;
                            }
                        }
                    } while (pilih != 4);
                } else if (role == "dosen") {
                    cout << "Selamat datang, Dosen!\n";
                    do{
                        cout << "+==========================+" << endl;
                        cout << "|       PILIHAN MENU       |" << endl;
                        cout << "+==========================+" << endl;
                        cout << "[1] Input Data" << endl;
                        cout << "[2] Tampil Data" << endl;
                        cout << "[3] Hapus Data" << endl;
                        cout << "[4] Cari Data" << endl;
                        cout << "[5] Sorting Data" << endl;
                        cout << "[6] Logout" << endl;
                        cout << "============================" << endl;
                        cout << "Pilih Menu : "; cin >> pilih; cin.ignore();
                        if (pilih < 1 || pilih > 6){
                            cout << "Maaf menu tidak tersedia, silahkan pilih ulang!" << endl;
                        } else {
                            switch (pilih){
                                case 1:
                                    menuInputData();
                                    break;
                                case 2:
                                    menuTampilData();
                                    break;
                                case 3:
                                    menuHapusData();
                                    break;
                                case 4:
                                    menuCariData();
                                    break;
                                case 5:
                                    menuSortingData();
                                    break;
                                case 6:
                                    cout << "Terima kasih telah menggunakan program ini!" << endl;
                                    break;
                                default:
                                    cout << "Pilihan menu tidak tersedia, silahkan pilih ulang!" << endl;
                                    break;
                            }
                        }
                    } while (pilih != 6);
                }
            } else {
                cout << "\nLogin gagal. Username atau password salah.\n";
            }
            system("pause");
        } else if (pilih == 2) {
            signup();
            system("pause");
        } else if (pilih == 3) {
            cout << "Keluar dari program.\n";
            break;
        } else {
            cout << "pilihan tidak valid!\n";
            system("pause");
        }
    }
    return 0;
}
//deklarasi function
void menuInputData(){
    system("cls");
    loadDariFile();
    int pilih, i, j, input;
    do {
        cout << "\n+===========================+" << endl;
        cout << "|       Input Data          |" << endl;
        cout << "+===========================+" << endl;
        cout << "[1] Input Data Mahasiswa" << endl;
        cout << "[2] Input Data Dosen" << endl;
        cout << "[3] Input Data Mata Kuliah" << endl;
        cout << "[4] Input Data Nilai" << endl;
        cout << "[5] Kembali ke Menu Utama" << endl;
        cout << "============================" << endl;
        cout << "Pilih Menu : "; cin >> pilih; cin.ignore();
        switch (pilih) {
            case 1:
                cout << "\nMasukkan jumlah data mahasiswa yang ingin di input : "; cin >> input;
                cin.ignore();
                if (input + jumlahMahasiswa <= 100) {
                    for (i = 0; i < input; i++){
                        mahasiswa mhs;
                        cout << "\nInput Data Mahasiswa ke-" << i + 1 << endl;
                        cout << "Nama\t: "; getline(cin, mhs.nama);
                        bool nimValid = false;
                        do {
                            cout << "NIM\t: "; getline(cin, mhs.nim);
                            nimValid = true;
                            for (int k = 0; k < mhs.nim.length(); k++) {
                                if (mhs.nim[k] < '0' || mhs.nim[k] > '9') {
                                    nimValid = false;
                                    cout << "NIM hanya boleh terdiri dari angka! Input ulang.\n";
                                    break;
                                }
                            }
                        } while (!nimValid);
                        cout << "Jurusan\t: "; getline(cin, mhs.jurusan);
                        bool nimUnik = false;
                        for (j = 0; j < jumlahMahasiswa; j++) {
                            if (daftarMahasiswa[j].nim == mhs.nim) {
                                nimUnik = true;
                                break;
                            }
                        }
                        if (nimUnik) {
                            cout << "NIM sudah terdaftar! Masukkan NIM yang berbeda.\n";
                            i--; // supaya tetap menginput ulang mahasiswa ke-i
                            continue;
                        }
                        daftarMahasiswa[jumlahMahasiswa++] = mhs;
                    } 
                    cout << "Data Mahasiswa berhasil ditambahkan!" << endl;
                    simpanKeFile();
                    break;
                } else {
                    cout << "Data mahasiswa sudah mencapai batas maksimum!" << endl;
                }
                break;
            case 2:
                cout << "\nMasukkan jumlah data dosen yang ingin di input : "; cin >> input; cin.ignore();
                if (input + jumlahDosen <= 100) {
                    for (i = 0; i < input; i++) {
                        dosen dsn;
                        cout << "\nInput Data Dosen ke-" << i + 1 << endl;
                        cout << "Nama\t: "; getline(cin, dsn.nama);
                        bool nipValid = false;
                        do {
                            cout << "NIP\t: "; getline(cin, dsn.nip);
                            nipValid = true;
                            for (int k = 0; k < dsn.nip.length(); k++) {
                                if (dsn.nip[k] < '0' || dsn.nip[k] > '9') {
                                    nipValid= false;
                                    cout << "NIP hanya boleh terdiri dari angka! Input ulang.\n";
                                    break;
                                }
                            }
                        } while (!nipValid);
                        cout << "Prodi\t: "; getline(cin, dsn.prodi);
                        bool nipUnik = false;
                        for (j = 0; j < jumlahDosen; j++) {
                            if (daftarDosen[j].nip == dsn.nip) {
                                nipUnik = true;
                                break;
                            }
                        }
                        if (nipUnik) {
                            cout << "NIP sudah terdaftar! Masukkan NIP yang berbeda.\n";
                            i--; // supaya tetap menginput ulang mahasiswa ke-i
                            continue;
                        }
                        daftarDosen[jumlahDosen++] = dsn;
                    }
                    cout << "Data Dosen berhasil ditambahkan!" << endl;
                    simpanKeFile();
                } else {
                    cout << "Data dosen sudah mencapai batas maksimum!" << endl;
                }
                break;
            case 3:
                cout << "\nMasukkan jumlah data mata kuliah yang ingin di input : "; cin >> input; cin.ignore();
                if (input + jumlahMatkul <= 100) {
                    for (i = 0; i < input; i++){
                        matkul mtk;
                        cout << "\nInput Data Mata Kuliah ke-" << i + 1 << endl;
                        cout << "Nama Mata Kuliah\t: "; getline(cin, mtk.nama);
                        bool kodeValid = false;
                        do {
                            cout << "Kode:\t: "; getline(cin, mtk.kode);
                            kodeValid = true;
                            for (int k = 0; k < mtk.kode.length(); k++) {
                                if (mtk.kode[k] < '0' || mtk.kode[k] > '9') {
                                    kodeValid = false;
                                    cout << "Kode hanya boleh terdiri dari angka! Input ulang.\n";
                                    break;
                                }
                            }
                        } while (!kodeValid);
                        cout << "SKS\t\t\t: "; cin >> mtk.sks; cin.ignore();
                        bool kodeUnik = false;
                        for (j = 0; j < jumlahMatkul; j++) {
                            if (daftarMatkul[j].kode == mtk.kode) {
                                kodeUnik = true;
                                break;
                            }
                        }
                        if (kodeUnik) {
                            cout << "Kode sudah terdaftar! Masukkan kode yang berbeda.\n";
                            i--; // supaya tetap menginput ulang mahasiswa ke-i
                            continue;
                        }
                        daftarMatkul[jumlahMatkul++] = mtk;
                    }
                    cout << "Data Mata Kuliah berhasil ditambahkan!" << endl;
                    simpanKeFile();
                } else {
                    cout << "Data mata kuliah sudah mencapai batas maksimum!" << endl;
                }
                break;
            case 4:
                cout << "\nMasukkan jumlah data nilai yang ingin di input : "; cin >> input; cin.ignore();
                if (input + jumlahNilai <= 100) {
                    for (i = 0; i < input; i++){
                        nilai nl;
                        cout << "\nInput Data Nilai ke-" << i + 1 << endl;
                        bool nimValid = false;
                        do {
                            cout << "NIM\t: "; getline(cin, nl.nim);
                            nimValid = true;
                            for (int k = 0; k < nl.nim.length(); k++) {
                                if (nl.nim[k] < '0' || nl.nim[k] > '9') {
                                    nimValid = false;
                                    cout << "NIM hanya boleh terdiri dari angka! Input ulang.\n";
                                    break;
                                }
                            }
                        } while (!nimValid);
                        cout << "Mata Kuliah\t: "; getline(cin, nl.mataKuliah);
                        cout << "Nilai\t\t: "; cin >> nl.nilai; cin.ignore();
                        daftarNilai[jumlahNilai++] = nl;
                    }
                    cout << "Data Nilai berhasil ditambahkan!" << endl;
                    simpanKeFile();
                } else {
                    cout << "Data nilai sudah mencapai batas maksimum!" << endl;
                }
                break;
            case 5:
                cout << "Kembali ke menu utama..." << endl << endl;
                break;
            default:
                cout << "Pilihan menu tidak tersedia!" << endl;
                break;
         }
    } while (pilih != 5);
}     
void menuTampilData(){
    system("cls");
    int pilih, i;
    do {
        cout << "\n+===========================+" << endl;
        cout << "|        Tampil Data        |" << endl;
        cout << "+===========================+" << endl;
        cout << "[1] Tampil Data Mahasiswa" << endl;
        cout << "[2] Tampil Data Dosen" << endl;
        cout << "[3] Tampil Data Mata Kuliah" << endl;
        cout << "[4] Tampil Data Nilai" << endl;
        cout << "[5] Menu Utama" << endl;
        cout << "============================" << endl;
        cout << "Pilih Menu : "; cin >> pilih; cin.ignore();
        switch (pilih) {
            case 1:
                if (jumlahMahasiswa == 0) {
                    cout << "Belum ada data mahasiswa!" << endl;
                } else {
                    cout << "\nData Mahasiswa:" << endl;
                    for (i = 0; i < jumlahMahasiswa; i++) {
                        cout << "Nama\t: " << daftarMahasiswa[i].nama << endl;
                        cout << "NIM\t: " << daftarMahasiswa[i].nim << endl;
                        cout << "Jurusan\t: " << daftarMahasiswa[i].jurusan << endl;
                        cout << "----------------------------" << endl;
                    }
                }
                break;
            case 2:
                if (jumlahDosen == 0){
                    cout << "Belum ada data dosen!" << endl;
                } else {
                    cout << "\nData Dosen:" << endl;
                    for (i = 0; i < jumlahDosen; i++){
                        cout << "Nama\t: " << daftarDosen[i].nama << endl;
                        cout << "NIP\t: " << daftarDosen[i].nip << endl;
                        cout << "Prodi\t: " << daftarDosen[i].prodi << endl;
                        cout << "----------------------------" << endl;
                    }
                }
                break;
            case 3:
                if (jumlahMatkul == 0) {
                    cout << "Belum ada data mata kuliah!" << endl;
                } else {
                    cout << "\nData Mata Kuliah:" << endl;
                    for (i = 0; i < jumlahMatkul; i++) {
                        cout << "Nama\t: " << daftarMatkul[i].nama << endl;
                        cout << "Kode\t: " << daftarMatkul[i].kode << endl;
                        cout << "SKS\t: " << daftarMatkul[i].sks << endl;
                        cout << "----------------------------" << endl;
                    }
                }
                break;
            case 4:
                if (jumlahNilai == 0) {
                    cout << "Belum ada data nilai!" << endl;
                } else {
                    cout << "\nData Nilai:" << endl;
                    for (i = 0; i < jumlahNilai; i++) {
                        cout << "NIM\t\t: " << daftarNilai[i].nim << endl;
                        cout << "Mata Kuliah\t: " << daftarNilai[i].mataKuliah << endl;
                        cout << "Nilai\t\t: " << daftarNilai[i].nilai << endl;
                        cout << "----------------------------" << endl;
                    }
                }
                break;
            case 5:
                cout << "Kembali ke menu utama..." << endl << endl;
                break;
            default:
                cout << "Pilihan menu tidak tersedia!" << endl;
                break;
        }
    } while (pilih != 5); 
}
void menuHapusData(){
    int pilih;
    string nim, nip, kodeMatkul;
    system("cls");
    cout << "\n+==========================+" << endl;
    cout << "|       Hapus Data         |" << endl;
    cout << "+==========================+" << endl;
    cout << "[1] Hapus Data Mahasiswa" << endl;
    cout << "[2] Hapus Data Dosen" << endl;
    cout << "[3] Hapus Data Mata Kuliah" << endl;
    cout << "[4] Hapus Data Nilai" << endl;
    cout << "[5] Kembali ke Menu Utama" << endl;
    cout << "============================" << endl;
    cout << "Pilih Menu : "; cin >> pilih; cin.ignore();
    switch (pilih) {
        case 1:
            cout << "\nMasukkan NIM Mahasiswa yang ingin dihapus: ";
            getline(cin, nim);
            for (int i = 0; i < jumlahMahasiswa; i++) {
                if (daftarMahasiswa[i].nim == nim) {
                    // menggeser elemen setelahnya untuk menghapus data
                    for (int j = i; j < jumlahMahasiswa - 1; j++) {
                        daftarMahasiswa[j] = daftarMahasiswa[j + 1];
                    }
                    jumlahMahasiswa--;  // mengurangi jumlah data
                    simpanKeFile(); // menyimpan perubahan ke file
                    cout << "Data Mahasiswa dengan NIM " << nim << " berhasil dihapus!" << endl << endl;
                    return;
                }
            }
            cout << "Data Mahasiswa dengan NIM " << nim << " tidak ditemukan!" << endl << endl;
            break;
        case 2:
            cout << "\nMasukkan NIP Dosen yang ingin dihapus: ";
            getline(cin, nip);
            for (int i = 0; i < jumlahDosen; i++) {
                if (daftarDosen[i].nip == nip) {
                    // menggeser elemen setelahnya untuk menghapus data
                    for (int j = i; j < jumlahDosen - 1; j++) {
                        daftarDosen[j] = daftarDosen[j + 1];
                    }
                    jumlahDosen--;  // mengurangi jumlah data
                    simpanKeFile(); // menyimpan perubahan ke file
                    cout << "Data Dosen dengan NIP " << nip << " berhasil dihapus!" << endl << endl;
                    return;
                }
            }
            cout << "Data Dosen dengan NIP " << nip << " tidak ditemukan!" << endl << endl;
            break;
        case 3:
            cout << "\nMasukkan Kode Mata Kuliah yang ingin dihapus: ";
            getline(cin, kodeMatkul);
            for (int i = 0; i < jumlahMatkul; i++) {
                if (daftarMatkul[i].kode == kodeMatkul) {
                    // menggeser elemen setelahnya untuk menghapus data
                    for (int j = i; j < jumlahMatkul - 1; j++) {
                        daftarMatkul[j] = daftarMatkul[j + 1];
                    }
                    jumlahMatkul--;  // mengurangi jumlah data
                    simpanKeFile(); // menyimpan perubahan ke file
                    cout << "Data Mata Kuliah dengan Kode " << kodeMatkul << " berhasil dihapus!" << endl << endl;
                    return;
                }
            }
            cout << "Data Mata Kuliah dengan Kode " << kodeMatkul << " tidak ditemukan!" << endl << endl;
            break;
        case 4:
            cout << "\nMasukkan NIM Mahasiswa yang ingin dihapus data nilainya: ";
            getline(cin, nim);
            cout << "Masukkan Mata Kuliah yang ingin dihapus nilainya: ";
            getline(cin, kodeMatkul);
            for (int i = 0; i < jumlahNilai; i++) {
                if (daftarNilai[i].nim == nim && daftarNilai[i].mataKuliah == kodeMatkul) {
                    // menggeser elemen setelahnya untuk menghapus data
                    for (int j = i; j < jumlahNilai - 1; j++) {
                        daftarNilai[j] = daftarNilai[j + 1];
                    }
                    jumlahNilai--;  // mengurangi jumlah data
                    simpanKeFile(); // menyimpan perubahan ke file
                    cout << "Data Nilai untuk NIM " << nim << " dan Mata Kuliah " << kodeMatkul << " berhasil dihapus!" << endl << endl;
                    return;
                }
            }
            cout << "Data Nilai untuk NIM " << nim << " dan Mata Kuliah " << kodeMatkul << " tidak ditemukan!" << endl << endl;
            break;
        case 5:
            cout << "Kembali ke menu utama..." << endl << endl;
            break;
        default:
            cout << "Pilihan menu tidak tersedia!" << endl;
            break;
    }
}
void menuCariData() {
    system("cls");
    int pilih, tipeCari;
    do {
        cout << "\n+==========================+" << endl;
        cout << "|     Metode Pencarian     |" << endl;
        cout << "+==========================+" << endl;
        cout << "[1] Sequential Search" << endl;
        cout << "[2] Binary Search" << endl;
        cout << "[3] Menu Utama" << endl;
        cout << "============================" << endl;
        cout << "Pilih Menu : "; cin >> pilih; cin.ignore();
        if (pilih == 1 || pilih == 2) {
            cout << "\n+=============================+" << endl;
            cout << "|      Kategori Pencarian     |" << endl;
            cout << "+=============================+" << endl;
            cout << "[1] Mahasiswa" << endl;
            cout << "[2] Dosen" << endl;
            cout << "[3] Mata Kuliah" << endl;
            cout << "[4] Nilai Mahasiswa" << endl;
            cout << "===============================" << endl;
            cout << "Pilih Menu: "; cin >> tipeCari; cin.ignore();
            system("cls");
            int i, low, high, mid;
            string y;
            bool found = false;
            if (tipeCari == 1) {
                cout << "\nMasukkan NIM Mahasiswa yang ingin dicari: ";
                getline(cin, y);
                if (pilih == 1) {
                    for (i = 0; i < jumlahMahasiswa; i++) {
                        if (daftarMahasiswa[i].nim == y) {
                            found = true;
                            cout << "Data Mahasiswa ditemukan:\n";
                            cout << "Nama\t: " << daftarMahasiswa[i].nama << endl;
                            cout << "NIM\t: " << daftarMahasiswa[i].nim << endl;
                            cout << "Jurusan\t: " << daftarMahasiswa[i].jurusan << endl;
                            break;
                        }
                    }
                } else {
                    low = 0; high = jumlahMahasiswa - 1;
                    while (low <= high) {
                        mid = (low + high) / 2;
                        if (daftarMahasiswa[mid].nim == y) {
                            found = true;
                            cout << "Data Mahasiswa ditemukan:\n";
                            cout << "Nama\t: " << daftarMahasiswa[mid].nama << endl;
                            cout << "NIM\t: " << daftarMahasiswa[mid].nim << endl;
                            cout << "Jurusan\t: " << daftarMahasiswa[mid].jurusan << endl;
                            break;
                        } else if (daftarMahasiswa[mid].nim < y) {
                            low = mid + 1;
                        } else {
                            high = mid - 1;
                        }
                    }
                }
                if (!found) {
                    cout << "Data Mahasiswa dengan NIM " << y << " tidak ditemukan!\n";
                }
            } else if (tipeCari == 2) {
                cout << "\nMasukkan NIP Dosen yang ingin dicari: ";
                getline(cin, y);
                if (pilih == 1) {
                    for (i = 0; i < jumlahDosen; i++) {
                        if (daftarDosen[i].nip == y) {
                            found = true;
                            cout << "Data Dosen ditemukan:\n";
                            cout << "Nama\t: " << daftarDosen[i].nama << endl;
                            cout << "NIP\t: " << daftarDosen[i].nip << endl;
                            cout << "Fakultas: " << daftarDosen[i].prodi << endl;
                            break;
                        }
                    }
                } else {
                    low = 0; high = jumlahDosen - 1;
                    while (low <= high) {
                        mid = (low + high) / 2;
                        if (daftarDosen[mid].nip == y) {
                            found = true;
                            cout << "Data Dosen ditemukan:\n";
                            cout << "Nama\t: " << daftarDosen[mid].nama << endl;
                            cout << "NIP\t: " << daftarDosen[mid].nip << endl;
                            cout << "Fakultas: " << daftarDosen[mid].prodi << endl;
                            break;
                        } else if (daftarDosen[mid].nip < y) {
                            low = mid + 1;
                        } else {
                            high = mid - 1;
                        }
                    }
                }
                if (!found) {
                    cout << "Data Dosen dengan NIP " << y << " tidak ditemukan!\n";
                }
            } else if (tipeCari == 3) {
                cout << "\nMasukkan Kode Mata Kuliah yang ingin dicari: ";
                getline(cin, y);
                if (pilih == 1) {
                    for (i = 0; i < jumlahMatkul; i++) {
                        if (daftarMatkul[i].kode == y) {
                            found = true;
                            cout << "Data Mata Kuliah ditemukan:\n";
                            cout << "Kode\t: " << daftarMatkul[i].kode << endl;
                            cout << "Nama\t: " << daftarMatkul[i].nama << endl;
                            cout << "SKS\t: " << daftarMatkul[i].sks << endl;
                            break;
                        }
                    }
                } else {
                    low = 0; high = jumlahMatkul - 1;
                    while (low <= high) {
                        mid = (low + high) / 2;
                        if (daftarMatkul[mid].kode == y) {
                            found = true;
                            cout << "Data Mata Kuliah ditemukan:\n";
                            cout << "Kode\t: " << daftarMatkul[mid].kode << endl;
                            cout << "Nama\t: " << daftarMatkul[mid].nama << endl;
                            cout << "SKS\t: " << daftarMatkul[mid].sks << endl;
                            break;
                        } else if (daftarMatkul[mid].kode < y) {
                            low = mid + 1;
                        } else {
                            high = mid - 1;
                        }
                    }
                }
                if (!found) {
                    cout << "Mata Kuliah dengan kode " << y << " tidak ditemukan!\n";
                }
            } else if (tipeCari == 4) {
                cout << "\nMasukkan NIM Mahasiswa yang nilainya ingin dicari: ";
                getline(cin, y);

                if (pilih == 1) {
                    for (i = 0; i < jumlahNilai; i++) {
                        if (daftarNilai[i].nim == y) {
                            found = true;
                            cout << "NIM\t\t: " << daftarNilai[i].nim << endl;
                            cout << "Mata Kuliah\t: " << daftarNilai[i].mataKuliah << endl;
                            cout << "Nilai\t\t: " << daftarNilai[i].nilai << endl;
                            cout << "------------------------------\n";
                        }
                    }
                } else {
                    low = 0; high = jumlahNilai - 1;
                    while (low <= high) {
                        mid = (low + high) / 2;
                        if (daftarNilai[mid].nim == y) {
                            found = true;
                            cout << "NIM\t\t: " << daftarNilai[mid].nim << endl;
                            cout << "Mata Kuliah\t: " << daftarNilai[mid].mataKuliah << endl;
                            cout << "Nilai\t\t: " << daftarNilai[mid].nilai << endl;
                            cout << "--------------------------------\n";
                            int kiri = mid - 1;
                            while (kiri >= 0 && daftarNilai[kiri].nim == y) {
                                cout << "NIM\t\t: " << daftarNilai[kiri].nim << endl;
                                cout << "Mata Kuliah\t: " << daftarNilai[kiri].mataKuliah << endl;
                                cout << "Nilai\t\t: " << daftarNilai[kiri].nilai << endl;
                                cout << "--------------------------------\n";
                                kiri--;
                            }
                            int kanan = mid + 1;
                            while (kanan < jumlahNilai && daftarNilai[kanan].nim == y) {
                                cout << "NIM\t\t: " << daftarNilai[kanan].nim << endl;
                                cout << "Mata Kuliah\t: " << daftarNilai[kanan].mataKuliah << endl;
                                cout << "Nilai\t\t: " << daftarNilai[kanan].nilai << endl;
                                cout << "--------------------------------\n";
                                kanan++;
                            }
                            break;
                        } else if (daftarNilai[mid].nim < y) {
                            low = mid + 1;
                        } else {
                            high = mid - 1;
                        }
                    }
                }
                if (!found) {
                    cout << "Data Nilai dengan NIM " << y << " tidak ditemukan!\n";
                }
            } else {
                cout << "Pilihan tidak tersedia!\n";
            }
        } else if (pilih == 3) {
            cout << "Kembali ke menu utama...\n\n";
            return;
        } else {
            cout << "Pilihan tidak tersedia!\n";
        }
    } while (pilih != 3);
}
void menuSortingData() {
    int pilih, pilihSort, urutan, lanjut;
    bool ulangSort = true;
    while (ulangSort) {
        system("cls");
        cout << "\n+=================================+" << endl;
        cout << "|        Pilih Data Sorting       |" << endl;
        cout << "+=================================+" << endl;
        cout << "[1] Mahasiswa" << endl;
        cout << "[2] Dosen" << endl;
        cout << "[3] Mata Kuliah" << endl;
        cout << "[4] Nilai Mahasiswa" << endl;
        cout << "[5] Menu Utama" << endl;
        cout << "===================================" << endl;
        cout << "Pilih Menu: "; cin >> pilihSort;
        if (pilihSort == 5) {
            cout << "Kembali ke menu utama..." << endl;
            return;
        }
        if (pilihSort < 1 || pilihSort > 5) {
            cout << "Pilihan tidak tersedia!" << endl;
            continue;
        }
        while (ulangSort) {
            system("cls");
            cout << "\n+==========================+" << endl;
            cout << "|        Sorting Data      |" << endl;
            cout << "+==========================+" << endl;
            cout << "[1] Bubble Sort" << endl;
            cout << "[2] Selection Sort" << endl;
            cout << "[3] Insertion Sort" << endl;
            cout << "[4] Kembali ke Pilih Data" << endl;
            cout << "============================" << endl;
            cout << "Pilih Menu: "; cin >> pilih;
            if (pilih == 4) break;
            cout << "\n+==========================+" << endl;
            cout << "|      Urutan Sorting      |" << endl;
            cout << "+==========================+" << endl;
            cout << "[1] Ascending (0-9)" << endl;
            cout << "[2] Descending (9-0)" << endl;
            cout << "============================" << endl;
            cout << "Pilih Urutan: "; cin >> urutan;
            bool ascending = (urutan == 1); //validasi urutan
            FILE* file = fopen("sorting.txt", "w");
            switch (pilihSort) {
                case 1: // Mahasiswa
                    switch (pilih) {
                        case 1: // Bubble
                            for (int i = 0; i < jumlahMahasiswa - 1; i++) {
                                for (int j = 0; j < jumlahMahasiswa - i - 1; j++) {
                                    if ((ascending&&daftarMahasiswa[j].nim > daftarMahasiswa[j + 1].nim)||(!ascending&&daftarMahasiswa[j].nim < daftarMahasiswa[j + 1].nim)) {
                                        swap(daftarMahasiswa[j], daftarMahasiswa[j + 1]);
                                    }
                                }
                            }
                            break;
                        case 2: // Selection
                            for (int i = 0; i < jumlahMahasiswa - 1; i++) {
                                int idx = i;
                                for (int j = i + 1; j < jumlahMahasiswa; j++) {
                                    if ((ascending&&daftarMahasiswa[j].nim < daftarMahasiswa[idx].nim)||(!ascending&&daftarMahasiswa[j].nim > daftarMahasiswa[idx].nim)) {
                                        idx = j;
                                    }
                                }
                                swap(daftarMahasiswa[i], daftarMahasiswa[idx]);
                            }
                            break;
                        case 3: // Insertion
                            for (int i = 1; i < jumlahMahasiswa; i++) {
                                mahasiswa key = daftarMahasiswa[i];
                                int j = i - 1;
                                while (j >= 0 && ((ascending&&daftarMahasiswa[j].nim > key.nim)||(!ascending&&daftarMahasiswa[j].nim < key.nim))) {
                                    daftarMahasiswa[j + 1] = daftarMahasiswa[j];
                                    j--;
                                }
                                daftarMahasiswa[j + 1] = key;
                            }
                            break;
                        default:
                            cout << "Pilihan tidak tersedia!" << endl;
                            continue;
                    }
                    cout << "\nData Mahasiswa setelah sorting:\n";
                    for (int i = 0; i < jumlahMahasiswa; i++) {
                        cout << daftarMahasiswa[i].nim << " \t| " << daftarMahasiswa[i].nama
                             << " \t| " << daftarMahasiswa[i].jurusan << endl;
                        if (file) {
                            fprintf(file, "%s\t%s\t%s\n", daftarMahasiswa[i].nim, daftarMahasiswa[i].nama, daftarMahasiswa[i].jurusan);
                        }
                    }
                    break;
                case 2: // Dosen
                    switch (pilih) {
                        case 1: // Bubble
                            for (int i = 0; i < jumlahDosen - 1; i++) {
                                for (int j = 0; j < jumlahDosen - i - 1; j++) {
                                    if ((ascending && daftarDosen[j].nip > daftarDosen[j + 1].nip)||(!ascending&&daftarDosen[j].nip < daftarDosen[j + 1].nip)) {
                                        swap(daftarDosen[j], daftarDosen[j + 1]);
                                    }
                                }
                            }
                            break;
                        case 2: // Selection
                            for (int i = 0; i < jumlahDosen - 1; i++) {
                                int idx = i;
                                for (int j = i + 1; j < jumlahDosen; j++) {
                                    if ((ascending&&daftarDosen[j].nip < daftarDosen[idx].nip)||(!ascending&&daftarDosen[j].nip > daftarDosen[idx].nip)) {
                                        idx = j;
                                    }
                                }
                                swap(daftarDosen[i], daftarDosen[idx]);
                            }
                            break;
                        case 3: // Insertion
                            for (int i = 1; i < jumlahDosen; i++) {
                                dosen key = daftarDosen[i];
                                int j = i - 1;
                                while (j >= 0 && ((ascending&&daftarDosen[j].nip > key.nip)||(!ascending&&daftarDosen[j].nip < key.nip))) {
                                    daftarDosen[j + 1] = daftarDosen[j];
                                    j--;
                                }
                                daftarDosen[j + 1] = key;
                            }
                            break;
                        default:
                            cout << "Pilihan tidak tersedia!" << endl;
                            continue;
                    }
                    cout << "\nData Dosen setelah sorting:\n";
                    for (int i = 0; i < jumlahDosen; i++) {
                        cout << daftarDosen[i].nip << " \t| " << daftarDosen[i].nama
                             << " \t| " << daftarDosen[i].prodi << endl;
                        if (file) {
                            fprintf(file, "%s\t%s\t%s\n", daftarDosen[i].nip, daftarDosen[i].nama, daftarDosen[i].prodi);
                        }
                    }
                    break;
                case 3: // Mata Kuliah
                    switch (pilih) {
                        case 1:
                            for (int i = 0; i < jumlahMatkul - 1; i++) {
                                for (int j = 0; j < jumlahMatkul - i - 1; j++) {
                                    if ((ascending&&daftarMatkul[j].kode > daftarMatkul[j + 1].kode)||(!ascending&&daftarMatkul[j].kode < daftarMatkul[j + 1].kode)) {
                                        swap(daftarMatkul[j], daftarMatkul[j + 1]);
                                    }
                                }
                            }
                            break;
                        case 2:
                            for (int i = 0; i < jumlahMatkul - 1; i++) {
                                int idx = i;
                                for (int j = i + 1; j < jumlahMatkul; j++) {
                                    if ((ascending&&daftarMatkul[j].kode < daftarMatkul[idx].kode)||(!ascending&&daftarMatkul[j].kode > daftarMatkul[idx].kode)) {
                                        idx = j;
                                    }
                                }
                                swap(daftarMatkul[i], daftarMatkul[idx]);
                            }
                            break;
                        case 3:
                            for (int i = 1; i < jumlahMatkul; i++) {
                                matkul key = daftarMatkul[i];
                                int j = i - 1;
                                while (j >= 0 &&((ascending&&daftarMatkul[j].kode > key.kode)||(!ascending&&daftarMatkul[j].kode < key.kode))) {
                                    daftarMatkul[j + 1] = daftarMatkul[j];
                                    j--;
                                }
                                daftarMatkul[j + 1] = key;
                            }
                            break;
                        default:
                            cout << "Pilihan tidak tersedia!" << endl;
                            continue;
                    }
                    cout << "\nData Mata Kuliah setelah sorting:\n";
                    for (int i = 0; i < jumlahMatkul; i++) {
                        cout << daftarMatkul[i].kode << " \t| " << daftarMatkul[i].nama
                             << " \t| " << daftarMatkul[i].sks << endl;
                        if (file) {
                            fprintf(file, "%s\t%s\t%d\n", daftarMatkul[i].kode, daftarMatkul[i].nama, daftarMatkul[i].sks);
                        }
                    }
                    break;
                case 4: // Nilai Mahasiswa
                    switch (pilih) {
                        case 1:
                            for (int i = 0; i < jumlahNilai - 1; i++) {
                                for (int j = 0; j < jumlahNilai - i - 1; j++) {
                                    if ((ascending&&daftarNilai[j].nim > daftarNilai[j + 1].nim)||(!ascending&&daftarNilai[j].nim < daftarNilai[j + 1].nim)) {
                                        swap(daftarNilai[j], daftarNilai[j + 1]);
                                    }
                                }
                            }
                            break;
                        case 2:
                            for (int i = 0; i < jumlahNilai - 1; i++) {
                                int idx = i;
                                for (int j = i + 1; j < jumlahNilai; j++) {
                                    if ((ascending&&daftarNilai[j].nim < daftarNilai[idx].nim)||(!ascending&&daftarNilai[j].nim > daftarNilai[idx].nim)) {
                                        idx = j;
                                    }
                                }
                                swap(daftarNilai[i], daftarNilai[idx]);
                            }
                            break;
                        case 3:
                            for (int i = 1; i < jumlahNilai; i++) {
                                nilai key = daftarNilai[i];
                                int j = i - 1;
                                while (j >= 0 && ((ascending&&daftarNilai[j].nim > key.nim)||(!ascending&&daftarNilai[j].nim < key.nim))) {
                                    daftarNilai[j + 1] = daftarNilai[j];
                                    j--;
                                }
                                daftarNilai[j + 1] = key;
                            }
                            break;
                        default:
                            cout << "Pilihan tidak tersedia!" << endl;
                            continue;
                    }
                    cout << "\nData Nilai Mahasiswa setelah sorting:\n";
                    for (int i = 0; i < jumlahNilai; i++) {
                        cout << daftarNilai[i].nim << " \t| " << daftarNilai[i].mataKuliah
                             << " \t| " << daftarNilai[i].nilai << endl;
                        if (file) {
                            fprintf(file, "%s\t%s\t%d\n", daftarNilai[i].nim, daftarNilai[i].mataKuliah, daftarNilai[i].nilai);
                        }
                    }
                    break;
            }
            if (file) {
                fclose(file);
                cout << "\nHasil sorting disimpan ke file 'sorting.txt'.\n";
            }
            cout << "\nApakah Anda ingin memilih metode sorting lagi?" << endl;
            cout << "[1] Ya" << endl;
            cout << "[2] Pilih Data Baru" << endl;
            cout << "[3] Menu Utama" << endl;
            cout << "Pilihan: "; cin >> lanjut;
            if (lanjut == 2) break;
            if (lanjut == 3) return;
        }
    }
}
void simpanKeFile() {
    ofstream fileMHS("data_mahasiswa.txt");
    bool sukses = true;
    if (fileMHS.is_open()) {
        for (int i = 0; i < jumlahMahasiswa; i++) {
            fileMHS << daftarMahasiswa[i].nama << " "
                    << daftarMahasiswa[i].nim << " "
                    << daftarMahasiswa[i].jurusan << endl;
        }
        fileMHS.close();
    } else {
        cout << "Gagal membuka file data_mahasiswa.txt\n";
        sukses = false;
    }
    ofstream fileDSN("data_dosen.txt");
    if (fileDSN.is_open()) {
        for (int i = 0; i < jumlahDosen; i++) {
            fileDSN << daftarDosen[i].nama << " "
                    << daftarDosen[i].nip << " "
                    << daftarDosen[i].prodi << endl;
        }
        fileDSN.close();
    } else {
        cout << "Gagal membuka file data_dosen.txt\n";
        sukses = false;
    }
    ofstream fileMK("data_matkul.txt");
    if (fileMK.is_open()) {
        for (int i = 0; i < jumlahMatkul; i++) {
            fileMK << daftarMatkul[i].nama << " "
                   << daftarMatkul[i].kode << " "
                   << daftarMatkul[i].sks << endl;
        }
        fileMK.close();
    } else {
        cout << "Gagal membuka file data_matkul.txt\n";
        sukses = false;
    }
    ofstream fileNL("data_nilai.txt");
    if (fileNL.is_open()) {
        for (int i = 0; i < jumlahNilai; i++) {
            fileNL << daftarNilai[i].nim << " "
                   << daftarNilai[i].mataKuliah << " "
                   << daftarNilai[i].nilai << endl;
        }
        fileNL.close();
    } else {
        cout << "Gagal membuka file data_nilai.txt\n";
        sukses = false;
    }
}
void loadDariFile() {
    jumlahMahasiswa = jumlahDosen = jumlahMatkul = jumlahNilai = 0;
    ifstream fileMHS("data_mahasiswa.txt");
    while (fileMHS >> daftarMahasiswa[jumlahMahasiswa].nama
                  >> daftarMahasiswa[jumlahMahasiswa].nim
                  >> daftarMahasiswa[jumlahMahasiswa].jurusan){
        jumlahMahasiswa++;
    }
    fileMHS.close();
    ifstream fileDSN("data_dosen.txt");
    while (fileDSN >> daftarDosen[jumlahDosen].nama
                  >> daftarDosen[jumlahDosen].nip
                  >> daftarDosen[jumlahDosen].prodi) {
        jumlahDosen++;
    }
    fileDSN.close();
    ifstream fileMK("data_matkul.txt");
    while (fileMK >> daftarMatkul[jumlahMatkul].nama
                 >> daftarMatkul[jumlahMatkul].kode
                 >> daftarMatkul[jumlahMatkul].sks) {
        jumlahMatkul++;
    }
    fileMK.close();
    ifstream fileNL("data_nilai.txt");
    while (fileNL >> daftarNilai[jumlahNilai].nim
                 >> daftarNilai[jumlahNilai].mataKuliah
                 >> daftarNilai[jumlahNilai].nilai) {
        jumlahNilai++;
    }
    fileNL.close();
}