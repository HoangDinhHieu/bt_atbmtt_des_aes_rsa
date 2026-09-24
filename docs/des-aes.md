# DES (Data Encryption Standard)

## Tên gọi
DES - thuật toán mã hoá đối xứng theo khối (block cipher), ra đời 1977, chuẩn của NIST.

## Mô tả thuật toán
- Khối dữ liệu: 64 bit. Khoá: 56 bit hiệu dụng (64 bit gồm 8 bit parity).
- Cấu trúc Feistel: chia khối 64 bit thành 2 nửa L và R, lặp qua 16 vòng (round).
- Mỗi vòng dùng 1 khoá con (subkey) 48 bit sinh ra từ khoá gốc qua thuật toán sinh khoá (key schedule).

## Quy trình mã hoá
1. Hoán vị khởi tạo (Initial Permutation - IP) trên khối 64 bit.
2. Qua 16 vòng Feistel: R_i = L_{i-1} XOR F(R_{i-1}, K_i); L_i = R_{i-1}.
3. Hàm F gồm: mở rộng (Expansion) 32->48 bit, XOR với subkey, thay thế qua 8 hộp S-box (S-box) 6->4 bit, hoán vị P.
4. Hoán vị đảo (Final Permutation - IP^-1) cho ra bản mã.

## Quy trình giải mã
Giống hệt mã hoá nhưng dùng thứ tự subkey ngược lại (K16 -> K1).

## Nhận xét
DES hiện không còn an toàn do khoá 56 bit quá ngắn, dễ bị brute-force với máy tính hiện đại.
Ngày nay dùng AES thay thế.

---

# AES (Advanced Encryption Standard)

## Tên gọi
AES - chuẩn mã hoá đối xứng hiện đại, NIST công bố 2001, dựa trên thuật toán Rijndael.

## Mô tả thuật toán
- Khối dữ liệu cố định: 128 bit (16 byte), tổ chức thành ma trận trạng thái (state) 4x4 byte.
- Độ dài khoá: 128 / 192 / 256 bit tương ứng 10 / 12 / 14 vòng lặp (round).
- Cấu trúc SPN (Substitution-Permutation Network), không phải Feistel như DES.

## Quy trình mã hoá (mỗi round, trừ round cuối bớt MixColumns)
1. **AddRoundKey**: XOR state với round key.
2. **SubBytes**: thay từng byte qua hộp thế S-box (dựa trên nghịch đảo trong GF(2^8)).
3. **ShiftRows**: dịch vòng trái các hàng của ma trận state (hàng i dịch i byte).
4. **MixColumns**: trộn dữ liệu theo cột bằng phép nhân ma trận trong GF(2^8).
5. Lặp lại đủ số round, round cuối cùng bỏ bước MixColumns.

## Quy trình giải mã
Làm ngược lại theo thứ tự round key ngược, dùng các phép nghịch đảo:
InvShiftRows, InvSubBytes, AddRoundKey, InvMixColumns.

## Nhận xét
AES nhanh, an toàn, không có tấn công thực tế nào phá được AES-128 trở lên tính đến nay.
