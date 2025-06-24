#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

// Struktur untuk menyimpan data paket kursus
struct Course {
    string package_name;
    string type; // Privat atau Kelas
    int meetings;
    int session_duration; // Dalam menit
    double price_per_meeting;
    int registered_students;
    string payment_status;
};

// Vector untuk menyimpan semua paket kursus
vector<Course> courses;

// === Commit 1: Struktur dasar dan input data paket kursus ===
void addCourse() {
    Course newCourse;
    cout << "\nMasukkan nama paket kursus: ";
    cin.ignore();
    getline(cin, newCourse.package_name);
    cout << "Pilih tipe paket (1: Privat, 2: Kelas): ";
    int typeChoice;
    cin >> typeChoice;
    newCourse.type = (typeChoice == 1) ? "Privat" : "Kelas";
    cout << "Masukkan jumlah pertemuan: ";
    cin >> newCourse.meetings;
    cout << "Masukkan durasi per sesi (menit): ";
    cin >> newCourse.session_duration;
    cout << "Masukkan harga per pertemuan: ";
    cin >> newCourse.price_per_meeting;
    newCourse.registered_students = 0;
    newCourse.payment_status = "Belum Dibayar";
    courses.push_back(newCourse);
    cout << "Paket kursus berhasil ditambahkan!\n";
}

// === Commit 2: Fungsi tampilkan daftar paket kursus ===
void displayCourses() {
    if (courses.empty()) {
        cout << "\nTidak ada paket kursus!\n";
        return;
    }
    cout << "\nDaftar Paket Kursus:\n";
    cout << setw(20) << left << "Nama Paket" 
         << setw(10) << "Tipe" 
         << setw(15) << "Pertemuan" 
         << setw(15) << "Durasi (mnt)" 
         << setw(15) << "Harga/Pertemuan" << endl;
    cout << string(75, '-') << endl;
    for (const auto& course : courses) {
        cout << setw(20) << left << course.package_name 
             << setw(10) << course.type 
             << setw(15) << course.meetings 
             << setw(15) << course.session_duration 
             << setw(15) << course.price_per_meeting << endl;
    }
}

// === Commit 3: Fitur pendaftaran siswa ===
void registerStudent() {
    string packageName;
    int qty;
    cout << "\nMasukkan nama paket kursus: ";
    cin.ignore();
    getline(cin, packageName);
    cout << "Masukkan jumlah siswa yang mendaftar: ";
    cin >> qty;
    
    for (auto& course : courses) {
        if (course.package_name == packageName) {
            course.registered_students += qty;
            cout << "Pendaftaran berhasil! " << qty << " siswa terdaftar untuk " << packageName << ".\n";
            return;
        }
    }
    cout << "Paket kursus tidak ditemukan!\n";
}

// === Commit 4: Status pembayaran cicilan ===
void updatePaymentStatus() {
    string packageName;
    cout << "\nMasukkan nama paket kursus untuk update status pembayaran: ";
    cin.ignore();
    getline(cin, packageName);
    
    for (auto& course : courses) {
        if (course.package_name == packageName && course.registered_students > 0) {
            cout << "Pilih status pembayaran (1: Lunas, 2: Cicilan, 3: Belum Dibayar): ";
            int choice;
            cin >> choice;
            if (choice == 1) course.payment_status = "Lunas";
            else if (choice == 2) course.payment_status = "Cicilan";
            else course.payment_status = "Belum Dibayar";
            cout << "Status pembayaran berhasil diperbarui!\n";
            return;
        }
    }
    cout << "Paket kursus tidak ditemukan atau belum ada pendaftar!\n";
}


// === Commit 5: Edit dan hapus paket ===
void editCourse() {
    string packageName;
    cout << "\nMasukkan nama paket kursus yang akan diedit: ";
    cin.ignore();
    getline(cin, packageName);
    
    for (auto& course : courses) {
        if (course.package_name == packageName) {
            cout << "Masukkan nama paket baru (kosongkan jika tidak diubah): ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) course.package_name = newName;
            
            cout << "Pilih tipe paket baru (0: Tidak diubah, 1: Privat, 2: Kelas): ";
            int typeChoice;
            cin >> typeChoice;
            if (typeChoice == 1) course.type = "Privat";
            else if (typeChoice == 2) course.type = "Kelas";
            
            cout << "Masukkan jumlah pertemuan baru (0 jika tidak diubah): ";
            int newMeetings;
            cin >> newMeetings;
            if (newMeetings > 0) course.meetings = newMeetings;
            
            cout << "Masukkan durasi per sesi baru (0 jika tidak diubah): ";
            int newDuration;
            cin >> newDuration;
            if (newDuration > 0) course.session_duration = newDuration;
            
            cout << "Masukkan harga per pertemuan baru (0 jika tidak diubah): ";
            double newPrice;
            cin >> newPrice;
            if (newPrice > 0) course.price_per_meeting = newPrice;
            
            cout << "Data paket kursus berhasil diperbarui!\n";
            return;
        }
    }
    cout << "Paket kursus tidak ditemukan!\n";
}

void deleteCourse() {
    string packageName;
    cout << "\nMasukkan nama paket kursus yang akan dihapus: ";
    cin.ignore();
    getline(cin, packageName);
    
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        if (it->package_name == packageName) {
            courses.erase(it);
            cout << "Paket kursus berhasil dihapus!\n";
            return;
        }
    }
    cout << "Paket kursus tidak ditemukan!\n";
}


// === Commit 6: Perhitungan total biaya dan diskon ===
double calculateTotal() {
    double total = 0;
    for (const auto& course : courses) {
        double subtotal = course.registered_students * course.meetings * course.price_per_meeting;
        // Diskon 15% jika lebih dari 5 siswa untuk paket Kelas
        if (course.type == "Kelas" && course.registered_students > 5) {
            subtotal *= 0.85;
        }
        total += subtotal;
    }
    return total;
}

void displayCourseSummary() {
    cout << "\nRingkasan Pendaftaran Kursus:\n";
    cout << setw(20) << left << "Nama Paket" 
         << setw(10) << "Tipe" 
         << setw(15) << "Pendaftar" 
         << setw(15) << "Total Sesi" 
         << setw(15) << "Status Bayar" 
         << setw(15) << "Subtotal" << endl;
    cout << string(90, '-') << endl;
    
    double grandTotal = 0;
    for (const auto& course : courses) {
        if (course.registered_students > 0) {
            double subtotal = course.registered_students * course.meetings * course.price_per_meeting;
            if (course.type == "Kelas" && course.registered_students > 5) subtotal *= 0.85;
            grandTotal += subtotal;
            cout << setw(20) << left << course.package_name 
                 << setw(10) << course.type 
                 << setw(15) << course.registered_students 
                 << setw(15) << course.meetings 
                 << setw(15) << course.payment_status 
                 << setw(15) << subtotal << endl;
        }
    }
    cout << "\nTotal Biaya: " << grandTotal << endl;
}

// === Commit 7: Penyimpanan ke file ===
void saveToFile() {
    ofstream outFile("courses.txt");
    if (!outFile) {
        cout << "Gagal membuka file untuk penyimpanan!\n";
        return;
    }
    
    for (const auto& course : courses) {
        outFile << course.package_name << "|" 
                << course.type << "|" 
                << course.meetings << "|" 
                << course.session_duration << "|" 
                << course.price_per_meeting << "|" 
                << course.registered_students << "|" 
                << course.payment_status << endl;
    }
    outFile.close();
    cout << "Data berhasil disimpan ke file!\n";
}

void loadFromFile() {
    ifstream inFile("courses.txt");
    if (!inFile) {
        cout << "File courses tidak ditemukan!\n";
        return;
    }
    
    courses.clear();
    string line;
    while (getline(inFile, line)) {
        Course course;
        size_t pos = 0;
        string token;
        int field = 0;
        
        while ((pos = line.find("|")) != string::npos) {
            token = line.substr(0, pos);
            if (field == 0) course.package_name = token;
            else if (field == 1) course.type = token;
            else if (field == 2) course.meetings = stoi(token);
            else if (field == 3) course.session_duration = stoi(token);
            else if (field == 4) course.price_per_meeting = stod(token);
            else if (field == 5) course.registered_students = stoi(token);
            else if (field == 6) course.payment_status = token;
            line.erase(0, pos + 1);
            field++;
        }
        courses.push_back(course);
    }
    inFile.close();
    cout << "Data berhasil dimuat dari file!\n";
}
// === Commit 7: Penyimpanan ke file ===
void saveToFile() {
    ofstream outFile("courses.txt");
    if (!outFile) {
        cout << "Gagal membuka file untuk penyimpanan!\n";
        return;
    }
    
    for (const auto& course : courses) {
        outFile << course.package_name << "|" 
                << course.type << "|" 
                << course.meetings << "|" 
                << course.session_duration << "|" 
                << course.price_per_meeting << "|" 
                << course.registered_students << "|" 
                << course.payment_status << endl;
    }
    outFile.close();
    cout << "Data berhasil disimpan ke file!\n";
}

void loadFromFile() {
    ifstream inFile("courses.txt");
    if (!inFile) {
        cout << "File courses tidak ditemukan!\n";
        return;
    }
    
    courses.clear();
    string line;
    while (getline(inFile, line)) {
        Course course;
        size_t pos = 0;
        string token;
        int field = 0;
        
        while ((pos = line.find("|")) != string::npos) {
            token = line.substr(0, pos);
            if (field == 0) course.package_name = token;
            else if (field == 1) course.type = token;
            else if (field == 2) course.meetings = stoi(token);
            else if (field == 3) course.session_duration = stoi(token);
            else if (field == 4) course.price_per_meeting = stod(token);
            else if (field == 5) course.registered_students = stoi(token);
            else if (field == 6) course.payment_status = token;
            line.erase(0, pos + 1);
            field++;
        }
        courses.push_back(course);
    }
    inFile.close();
    cout << "Data berhasil dimuat dari file!\n";
}
// == commit 8: Fungsi menu utama ==
void displayMenu() {
    cout << "\nSistem Administrasi Lembaga Kursus\n";
    cout << "1. Tambah Paket Kursus\n";
    cout << "2. Tampilkan Daftar Paket\n";
    cout << "3. Daftarkan Siswa\n";
    cout << "4. Update Status Pembayaran\n";
    cout << "5. Edit Paket Kursus\n";
    cout << "6. Hapus Paket Kursus\n";
    cout << "7. Tampilkan Ringkasan Pendaftaran\n";
    cout << "8. Simpan ke File\n";
    cout << "9. Muat dari File\n";
    cout << "0. Keluar\n";
    cout << "Pilih opsi: ";
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: addCourse(); break;
            case 2: displayCourses(); break;
            case 3: registerStudent(); break;
            case 4: updatePaymentStatus(); break;
            case 5: editCourse(); break;
            case 6: deleteCourse(); break;
            case 7: displayCourseSummary(); break;
            case 8: saveToFile(); break;
            case 9: loadFromFile(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (choice != 0);

    return 0;
}
