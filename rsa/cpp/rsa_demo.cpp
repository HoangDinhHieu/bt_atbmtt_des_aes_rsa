#include <iostream>
#include <chrono>
using namespace std;

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

long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }

long long modinv(long long e, long long phi) {
    // Mo rong Euclid de tim nghich dao modulo
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
    // Vi du minh hoa - so nguyen to NHO, KHONG dung cho du lieu that
    long long p = 61, q = 53;      // so nguyen to vi du (RSA that dung so hang tram chu so)
    long long n = p * q;           // n = 3233
    long long phi = (p - 1) * (q - 1);
    long long e = 17;              // gcd(e, phi) = 1
    long long d = modinv(e, phi);  // khoa bi mat

    cout << "p=" << p << " q=" << q << " n=" << n << " phi=" << phi << endl;
    cout << "Khoa cong khai (e,n) = (" << e << "," << n << ")" << endl;
    cout << "Khoa bi mat   (d,n) = (" << d << "," << n << ")" << endl;

    long long M = 65; // ban ro dang so (< n), vd ma ASCII cua 1 ky tu
    cout << "Ban ro M = " << M << endl;

    auto t1 = chrono::high_resolution_clock::now();
    long long C = modpow(M, e, n); // ma hoa bang khoa cong khai
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Ban ma C = " << C << endl;
    cout << "Thoi gian ma hoa: "
         << chrono::duration<double, micro>(t2 - t1).count() << " us" << endl;

    auto t3 = chrono::high_resolution_clock::now();
    long long M2 = modpow(C, d, n); // giai ma bang khoa bi mat
    auto t4 = chrono::high_resolution_clock::now();
    cout << "Ban ro sau giai ma = " << M2 << endl;
    cout << "Thoi gian giai ma: "
         << chrono::duration<double, micro>(t4 - t3).count() << " us" << endl;

    return 0;
}
