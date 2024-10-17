# Permainan Tebak Angka dengan Pendaftaran dan Kode Redeem

Program ini adalah permainan tebak angka sederhana yang memungkinkan pengguna untuk mendaftar, login, dan berkompetisi untuk menebak angka yang dihasilkan secara acak. Jika pengguna berhasil menebak dengan benar, mereka akan mendapatkan kode redeem sebagai hadiah.

## Fitur
- **Pendaftaran Pengguna**: Pengguna dapat membuat akun baru dengan username dan password.
- **Login Pengguna**: Pengguna dapat masuk dengan username dan password yang telah didaftarkan.
- **Permainan Tebak Angka**: Setelah login, pengguna dapat menebak angka yang dihasilkan secara acak antara 1 dan 100.
- **Kode Redeem**: Setelah berhasil menebak angka, pengguna akan menerima kode redeem yang dapat digunakan di platform tertentu.

## Prerequisites
Sebelum menjalankan program ini, pastikan memiliki hal berikut:
- **MySQL**: Pastikan MySQL terinstal dan berjalan di sistem.
- **MySQL Connector/C++**: Library ini diperlukan untuk menghubungkan program C++ dengan database MySQL.

## Instalasi

1. **Kloning Repositori**
   ```bash
   git clone https://github.com/auzy7z/tebak-angka.git
   cd tebak-angka

## Kompilasi Program
Pastikan Anda telah menginstal MySQL Connector/C++. Gunakan perintah berikut untuk mengkompilasi:
```bash
   g++ -o tebak_angka main.cpp -lmysqlcppconn
```

## Run program
```bash
   ./tebak_angka
