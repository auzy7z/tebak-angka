#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <string>

// Fungsi untuk login user
bool loginUser(sql::Connection *conn, std::string &username) {
    std::string password, input_password;

    std::cout << "=== LOGIN ===\n";
    std::cout << "Username: ";
    std::cin >> username;

    sql::PreparedStatement *pstmt;
    pstmt = conn->prepareStatement("SELECT password FROM users WHERE username = ?");
    pstmt->setString(1, username);
    
    sql::ResultSet *res = pstmt->executeQuery();

    if (res->next()) {
        password = res->getString("password");
        std::cout << "Password: ";
        std::cin >> input_password;

        if (input_password == password) {
            std::cout << "Login berhasil!\n";
            delete res;
            delete pstmt;
            return true;
        } else {
            std::cout << "Password salah!\n";
        }
    } else {
        std::cout << "Username tidak ditemukan di dalam database, mungkin kamu salah mengeja atau username belum terdaftar.\n";
    }

    delete res;
    delete pstmt;
    return false;
}

// Fungsi untuk mendaftarkan user baru
void registerUser(sql::Connection *conn) {
    std::string username, password;

    std::cout << "=== REGISTRASI ===\n";
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    sql::PreparedStatement *pstmt;
    pstmt = conn->prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");

    pstmt->setString(1, username);
    pstmt->setString(2, password);

    try {
        pstmt->execute();
        std::cout << "Registrasi berhasil! Silakan login.\n";
    } catch (sql::SQLException &e) {
        std::cerr << "Error: Username sudah digunakan.\n";
    }

    delete pstmt;
}

// Fungsi untuk memberikan kode redeem
std::string getRedeemCode(sql::Connection *conn) {
    sql::PreparedStatement *pstmt;
    pstmt = conn->prepareStatement("SELECT code FROM redeem_codes LIMIT 1");

    sql::ResultSet *res = pstmt->executeQuery();

    if (res->next()) {
        std::string code = res->getString("code");

        // Hapus kode dari database setelah digunakan
        sql::PreparedStatement *delstmt;
        delstmt = conn->prepareStatement("DELETE FROM redeem_codes WHERE code = ?");
        delstmt->setString(1, code);
        delstmt->execute();
        delete delstmt;

        delete res;
        delete pstmt;
        return code;
    } else {
        return "No codes available!";
    }
}

// Fungsi untuk permainan tebak angka
void playGame(sql::Connection *conn, const std::string &username) {
    std::cout << "=== Selamat Datang di Permainan Tebak Angka! ===\n";
    std::cout << "Saya telah memilih angka rahasia antara 1 dan 100.\n";

    std::srand(std::time(0));
    int angkaRahasia = std::rand() % 100 + 1;
    int tebakan;
    int percobaan = 0;

    do {
        std::cout << "Masukkan tebakanmu: ";
        std::cin >> tebakan;
        percobaan++;

        if (tebakan > angkaRahasia) {
            std::cout << "Terlalu besar! Coba angka yang lebih kecil.\n";
        } else if (tebakan < angkaRahasia) {
            std::cout << "Terlalu kecil! Coba angka yang lebih besar.\n";
        } else {
            std::cout << "Selamat! Kamu menebak angka dalam " << percobaan << " percobaan!\n";
            std::string code = getRedeemCode(conn);
            std::cout << "Karena kamu berhasil menebaknya, kamu mendapatkan 1 kode untuk redeem: " << code 
                      << ". Redeem code di https://apps.auzy7z.id/redeem\n";
        }
    } while (tebakan != angkaRahasia);
}

int main() {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *conn;

    driver = sql::mysql::get_mysql_driver_instance();
    conn = driver->connect("tcp://127.0.0.1:3306", "root", "password");
    conn->setSchema("game_db");

    std::string username;
    int choice;

    do {
        std::cout << "1. Register\n2. Login\nPilih: ";
        std::cin >> choice;

        if (choice == 1) {
            registerUser(conn);
        } else if (choice == 2) {
            if (loginUser(conn, username)) {
                playGame(conn, username);
                break;
            }
        } else {
            std::cout << "Pilihan tidak valid.\n";
        }
    } while (true);

    delete conn;
    return 0;
}
