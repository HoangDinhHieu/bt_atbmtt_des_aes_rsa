#include <iostream>
#include <cstring>
#include <chrono>
extern "C" {
    #include "aes.h"
}

void in_hex(const char* label, const uint8_t* data, size_t len) {
    std::cout << label << ": ";
    for (size_t i = 0; i < len; i++) printf("%02x", data[i]);
    std::cout << std::endl;
}

int main() {
    // Khoa AES-128 (16 byte) va IV (16 byte) - vi du hoc tap, thuc te phai random
    uint8_t key[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
                        0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
    uint8_t iv[16]  = {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
                        0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f};

    char plaintext_str[] = "AN TOAN BAO MAT!"; // du 16 byte cho 1 block
    uint8_t buf[16];
    memcpy(buf, plaintext_str, 16);

    std::cout << "Ban ro: " << plaintext_str << std::endl;
    in_hex("Plaintext (hex)", buf, 16);

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key, iv);

    auto t1 = std::chrono::high_resolution_clock::now();
    AES_CBC_encrypt_buffer(&ctx, buf, 16);
    auto t2 = std::chrono::high_resolution_clock::now();

    in_hex("Ban ma (hex)", buf, 16);
    std::cout << "Thoi gian ma hoa: "
              << std::chrono::duration<double, std::micro>(t2 - t1).count()
              << " microseconds" << std::endl;

    // Giai ma - phai khoi tao lai ctx voi cung IV
    AES_init_ctx_iv(&ctx, key, iv);
    auto t3 = std::chrono::high_resolution_clock::now();
    AES_CBC_decrypt_buffer(&ctx, buf, 16);
    auto t4 = std::chrono::high_resolution_clock::now();

    std::cout << "Ban ro sau giai ma: " << std::string((char*)buf, 16) << std::endl;
    std::cout << "Thoi gian giai ma: "
              << std::chrono::duration<double, std::micro>(t4 - t3).count()
              << " microseconds" << std::endl;

    return 0;
}
