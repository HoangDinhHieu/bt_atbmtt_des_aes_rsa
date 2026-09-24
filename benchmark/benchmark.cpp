#include <iostream>
#include <chrono>
#include <cstring>

extern "C" {
    #include "aes.h"
}

using namespace std;

// ===== HÀM BỔ TRỢ CHO RSA =====
long long modpow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (__int128)result * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return result;
}

long long modinv(long long e, long long phi) {
    long long a = e, b = phi, x0 = 0, x1 = 1;
    while (a > 1) {
        long long q = a / b;
        long long t = b; b = a % b; a = t;
        t = x0; x0 = x1 - q * x0; x1 = t;
    }
    if (x1 < 0) x1 += phi;
    return x1;
}

int main() {
    const int SO_LAN = 1000;

    // -------------------------------------------------------------
    // 1. BENCHMARK AES-128 (CBC Mode)
    // -------------------------------------------------------------
    uint8_t key[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                        0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
    uint8_t iv[16]  = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
    uint8_t buf[16];
    memcpy(buf, "AN TOAN BAO MAT!", 16); // Dùng memcpy để lấy chuẩn 16 byte

    struct AES_ctx ctx;

    // Đo thời gian mã hóa AES
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < SO_LAN; i++) {
        AES_init_ctx_iv(&ctx, key, iv);
        AES_CBC_encrypt_buffer(&ctx, buf, 16);
    }
    auto t2 = chrono::high_resolution_clock::now();
    double aes_encrypt_us = chrono::duration<double, micro>(t2 - t1).count() / SO_LAN;

    // Đo thời gian giải mã AES
    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < SO_LAN; i++) {
        AES_init_ctx_iv(&ctx, key, iv);
        AES_CBC_decrypt_buffer(&ctx, buf, 16);
    }
    t2 = chrono::high_resolution_clock::now();
    double aes_decrypt_us = chrono::duration<double, micro>(t2 - t1).count() / SO_LAN;

    // -------------------------------------------------------------
    // 2. BENCHMARK RSA
    // -------------------------------------------------------------
    long long p = 61, q = 53;
    long long n = p * q; // n = 3233
    long long phi = (p - 1) * (q - 1);
    long long e = 17;
    long long d = modinv(e, phi);
    long long M = 65;
    long long C = 0;

    // Đo thời gian mã hóa RSA
    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < SO_LAN; i++) {
        C = modpow(M, e, n);
    }
    t2 = chrono::high_resolution_clock::now();
    double rsa_encrypt_us = chrono::duration<double, micro>(t2 - t1).count() / SO_LAN;

    // Đo thời gian giải mã RSA
    t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < SO_LAN; i++) {
        volatile long long M2 = modpow(C, d, n);
    }
    t2 = chrono::high_resolution_clock::now();
    double rsa_decrypt_us = chrono::duration<double, micro>(t2 - t1).count() / SO_LAN;

    // -------------------------------------------------------------
    // 3. IN KẾT QUẢ SO SÁNH
    // -------------------------------------------------------------
    cout << "=========================================================" << endl;
    cout << "  SO SANH THOI GIAN THUC THI CHUAN (Trung binh " << SO_LAN << " lan)" << endl;
    cout << "=========================================================" << endl;
    cout << " Thuat toan | Thoi gian Ma hoa (us) | Thoi gian Giai ma (us)" << endl;
    cout << "-----------|------------------------|-----------------------" << endl;
    cout << " AES-128   | " << aes_encrypt_us << " us\t\t| " << aes_decrypt_us << " us" << endl;
    cout << " RSA       | " << rsa_encrypt_us << " us\t\t| " << rsa_decrypt_us << " us" << endl;
    cout << "=========================================================" << endl << endl;

    cout << "--> NHAN XET:" << endl;
    cout << "1. AES nhanh hon RSA rat nhieu do AES chi gom cac phep XOR, hoan vi va thay the don gian." << endl;
    cout << "2. RSA giai ma (voi d lon) cham hon ma hoa (voi e nho) do phep tinh luy thua modulo voi so mu lon." << endl;

    return 0;
}
