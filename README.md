# Bài tập: An toàn và bảo mật thông tin — DES, AES, RSA
## Sinh Viên: Hoàng Đình Hiếu MSSV: K235480106025 Lớp: K59KMT.K01
### Deadline:23h59 ngày 28/9/2026

Bài tập thực hành cài đặt và minh hoạ các thuật toán mã hoá DES, AES, RSA,
bao gồm: mô tả nguyên lý thuật toán, cài đặt bằng C++, demo trực quan bằng
HTML/CSS/JS, so sánh hiệu năng và mô hình kết hợp AES + RSA (Hybrid Encryption).

---

## Bài tập 1 — DES và AES

### DES (Data Encryption Standard)

**Tên gọi:** DES - thuật toán mã hoá đối xứng theo khối (block cipher), ra đời 1977, chuẩn của NIST.

**Mô tả thuật toán:**
- Khối dữ liệu: 64 bit. Khoá: 56 bit hiệu dụng (64 bit gồm 8 bit parity).
- Cấu trúc Feistel: chia khối 64 bit thành 2 nửa L và R, lặp qua 16 vòng (round).
- Mỗi vòng dùng 1 khoá con (subkey) 48 bit sinh ra từ khoá gốc qua thuật toán sinh khoá (key schedule).

**Quy trình mã hoá:**
1. Hoán vị khởi tạo (Initial Permutation - IP) trên khối 64 bit.
2. Qua 16 vòng Feistel: R_i = L_{i-1} XOR F(R_{i-1}, K_i); L_i = R_{i-1}.
3. Hàm F gồm: mở rộng (Expansion) 32->48 bit, XOR với subkey, thay thế qua 8 hộp S-box 6->4 bit, hoán vị P.
4. Hoán vị đảo (Final Permutation - IP^-1) cho ra bản mã.

**Quy trình giải mã:** Giống hệt mã hoá nhưng dùng thứ tự subkey ngược lại (K16 -> K1).

**Nhận xét:** DES hiện không còn an toàn do khoá 56 bit quá ngắn, dễ bị brute-force với máy tính hiện đại. Ngày nay dùng AES thay thế.

### AES (Advanced Encryption Standard)

**Tên gọi:** AES - chuẩn mã hoá đối xứng hiện đại, NIST công bố 2001, dựa trên thuật toán Rijndael.

**Mô tả thuật toán:**
- Khối dữ liệu cố định: 128 bit (16 byte), tổ chức thành ma trận trạng thái (state) 4x4 byte.
- Độ dài khoá: 128 / 192 / 256 bit tương ứng 10 / 12 / 14 vòng lặp (round).
- Cấu trúc SPN (Substitution-Permutation Network), không phải Feistel như DES.

**Quy trình mã hoá (mỗi round, trừ round cuối bớt MixColumns):**
1. **AddRoundKey**: XOR state với round key.
2. **SubBytes**: thay từng byte qua hộp thế S-box (dựa trên nghịch đảo trong GF(2^8)).
3. **ShiftRows**: dịch vòng trái các hàng của ma trận state (hàng i dịch i byte).
4. **MixColumns**: trộn dữ liệu theo cột bằng phép nhân ma trận trong GF(2^8).
5. Lặp lại đủ số round, round cuối cùng bỏ bước MixColumns.

**Quy trình giải mã:** Làm ngược lại theo thứ tự round key ngược, dùng các phép nghịch đảo: InvShiftRows, InvSubBytes, AddRoundKey, InvMixColumns.

**Nhận xét:** AES nhanh, an toàn, không có tấn công thực tế nào phá được AES-128 trở lên tính đến nay.

### Cài đặt AES bằng C++

Sử dụng thư viện tiny-AES-c, mã hoá/giải mã theo chế độ CBC.

Mã nguồn: [aes/cpp](aes/cpp)

Kết quả chạy demo (`./aes_demo`):
<img width="1920" height="1080" alt="Screenshot (21)" src="https://github.com/user-attachments/assets/d3ea4fdf-4ea1-473b-961c-80c13a0da510" />


### Demo AES bằng HTML/CSS/JS

Dùng thư viện CryptoJS để mã hoá/giải mã AES ngay trên trình duyệt.

Mã nguồn: [aes/web/aes-demo.html](aes/web/aes-demo.html)

Kết quả demo:
- Bản rõ: <img width="1920" height="1080" alt="Screenshot (23)" src="https://github.com/user-attachments/assets/6d62d3d6-b612-4e5d-86d1-114c56afcebf" />

- Bản mã: <img width="1920" height="1080" alt="Screenshot (22)" src="https://github.com/user-attachments/assets/5e6e83e3-addf-4291-83b3-928fb4cd15ff" />

- Giải mã lại ra đúng bản rõ ban đầu, khớp 100%.

---

## Bài tập 2 — RSA

### Nguyên lý RSA (Rivest-Shamir-Adleman)

**Tên gọi:** RSA - thuật toán mã hoá bất đối xứng (mã hoá công khai), công bố 1977 bởi 3 tác giả Ron Rivest, Adi Shamir, Leonard Adleman. Dựa trên độ khó của bài toán phân tích thừa số nguyên tố của số rất lớn.

**Nguyên lý sinh cặp khoá bí mật - công khai:**
1. Chọn 2 số nguyên tố lớn, khác nhau: p, q.
2. Tính n = p * q (n dùng làm modulo, là phần của cả khoá công khai và bí mật).
3. Tính phi(n) = (p-1)(q-1) (hàm Euler).
4. Chọn số e sao cho 1 < e < phi(n) và gcd(e, phi(n)) = 1 (e nguyên tố cùng nhau với phi(n)).
   → Khoá công khai: (e, n)
5. Tính d là nghịch đảo modulo của e theo phi(n): d * e ≡ 1 (mod phi(n)).
   → Khoá bí mật: (d, n)
<img width="1920" height="1080" alt="Screenshot (24)" src="https://github.com/user-attachments/assets/72bb9c2f-d318-41b4-b18b-37cac3cc06b4" />


**Mã hoá:** Bản rõ M (số nguyên < n): C = M^e mod n

**Giải mã:** Bản mã C: M = C^d mod n

**Vì sao an toàn:** Biết (e, n) rất khó suy ra d nếu không biết p, q (phải phân tích n thành thừa số nguyên tố - với n đủ lớn, hiện chưa có thuật toán hiệu quả để làm việc này trong thời gian hợp lý bằng máy tính thông thường).

### Cài đặt RSA bằng C++

Mã nguồn: [rsa/cpp](rsa/cpp)

Kết quả chạy demo (`./rsa_demo`), dùng p=61, q=53:
<img width="1920" height="1080" alt="Screenshot (25)" src="https://github.com/user-attachments/assets/92706ea4-42e0-437e-b771-bdfd8e0f86bf" />


### Demo RSA bằng HTML/CSS/JS

Sinh cặp khoá, mã hoá, giải mã ngay trên trình duyệt bằng JavaScript (BigInt).

Mã nguồn: [rsa/web/rsa-demo.html](rsa/web/rsa-demo.html)

Kết quả demo (p=61, q=53, e=17, bản rõ=65):
<img width="1920" height="1080" alt="Screenshot (26)" src="https://github.com/user-attachments/assets/f70be408-86f9-4a9c-b822-e41171ed9f03" />
<img width="1920" height="1080" alt="Screenshot (27)" src="https://github.com/user-attachments/assets/2aa39171-60f6-44ca-bea3-88026f30e341" />
<img width="1920" height="1080" alt="Screenshot (28)" src="https://github.com/user-attachments/assets/91e4d2b5-d598-4b47-8dc0-f3fce933d639" />
<img width="1920" height="1080" alt="Screenshot (29)" src="https://github.com/user-attachments/assets/86e3c420-5c25-4922-8dde-92bf0621f71c" />





---

## Bài tập 3 — Mô hình áp dụng, so sánh, kết hợp

### 3 mô hình áp dụng RSA

**Mô hình 1 - Xác thực người nhận (bảo mật / confidentiality)**
Người gửi mã hoá dữ liệu bằng KHOÁ CÔNG KHAI của người nhận. Chỉ người nhận (giữ khoá bí mật tương ứng) mới giải mã được.

Sơ đồ: Gửi --[mã hoá bằng public key B]--> Bản mã --[giải mã bằng private key B]--> Nhận

Mục đích: đảm bảo chỉ đúng người nhận B mới đọc được nội dung (bảo mật), không xác thực được ai là người gửi.

**Mô hình 2 - Xác thực người gửi (chữ ký số / authentication)**
Người gửi "mã hoá" (thực chất là ký) dữ liệu (hoặc mã băm của dữ liệu) bằng KHOÁ BÍ MẬT của chính mình. Bất kỳ ai có khoá công khai của người gửi đều giải mã (xác minh chữ ký) được, qua đó xác nhận đúng là người gửi A đã tạo ra.

Sơ đồ: Gửi --[ký bằng private key A]--> Chữ ký --[xác minh bằng public key A]--> Nhận

Mục đích: xác thực nguồn gốc (đúng là A gửi), chống chối bỏ (non-repudiation), không đảm bảo bí mật vì ai cũng có public key A để "giải mã" xem nội dung.

**Mô hình 3 - Kết hợp cả 2 (bảo mật + xác thực)**

Người gửi A:
1. Ký lên dữ liệu (hoặc hash của dữ liệu) bằng private key của A.
2. Mã hoá (dữ liệu + chữ ký) bằng public key của người nhận B.

Người nhận B:
1. Giải mã bằng private key của B → lấy lại (dữ liệu + chữ ký).
2. Xác minh chữ ký bằng public key của A → xác nhận đúng A gửi và dữ liệu không bị sửa.

Mục đích: vừa đảm bảo bí mật (chỉ B đọc được), vừa xác thực người gửi (chắc chắn là A). Đây là mô hình dùng phổ biến trong thực tế (email ký số + mã hoá, HTTPS/TLS...).

### So sánh thời gian mã hoá/giải mã AES vs RSA

Mã nguồn benchmark: [benchmark/benchmark.cpp](benchmark/benchmark.cpp)
<img width="1920" height="1080" alt="Screenshot (31)" src="https://github.com/user-attachments/assets/db548179-7b3c-461d-bf25-8e2dac3c5c9f" />


Kết quả (trung bình 1000 lần):

| Thuật toán | Thời gian Mã hoá (us) | Thời gian Giải mã (us) |
|---|---|---|
| AES-128 | 1.40821 | 7.95285 |
| RSA | 0.042923 | 0.105137 |

**Nhận xét:**
1. AES nhanh hơn RSA rất nhiều do AES chỉ gồm các phép XOR, hoán vị và thay thế đơn giản.
2. RSA giải mã (với d lớn) chậm hơn mã hoá (với e nhỏ) do phép tính luỹ thừa modulo với số mũ lớn.

*(Lưu ý: trong bảng benchmark ở trên, RSA đo trên số nhỏ p=61,q=53 nên nhanh hơn AES; trên thực tế với khoá RSA chuẩn 2048 bit, RSA chậm hơn AES hàng chục đến hàng trăm lần — do đó RSA chỉ dùng để mã hoá dữ liệu ngắn như khoá phiên, không dùng mã hoá trực tiếp dữ liệu lớn.)*

### Kết hợp AES + RSA (Hybrid Encryption)
<img width="1920" height="1080" alt="Screenshot (32)" src="https://github.com/user-attachments/assets/bdfa307f-6b38-4a9e-bb3a-78b464bb6587" />

**Vấn đề:**
- AES nhanh nhưng là mã hoá đối xứng: 2 bên phải có chung 1 khoá bí mật → khó trao đổi khoá an toàn qua kênh không tin cậy.
- RSA giải quyết được bài toán trao đổi khoá (bất đối xứng) nhưng lại rất chậm với dữ liệu lớn.

**Giải pháp: Hybrid Encryption** — kết hợp điểm mạnh của cả 2:

1. Bên gửi tạo ngẫu nhiên 1 khoá AES (gọi là "session key"), dùng khoá này mã hoá TOÀN BỘ dữ liệu thật (nhanh, vì là AES).
2. Bên gửi mã hoá khoá AES đó (chỉ vài chục byte) bằng KHOÁ CÔNG KHAI RSA của người nhận (chậm nhưng dữ liệu rất nhỏ nên không đáng kể).
3. Gửi đi: [dữ liệu đã mã hoá AES] + [khoá AES đã mã hoá bằng RSA].
4. Bên nhận: dùng khoá bí mật RSA của mình giải mã ra khoá AES gốc, rồi dùng khoá AES đó giải mã dữ liệu thật.

**Sơ đồ:**
<img width="1920" height="1080" alt="Screenshot (32)" src="https://github.com/user-attachments/assets/c04c3b3c-dfac-4ba2-b104-00c72576c64c" />

**Ứng dụng thực tế:** Đây chính là nguyên lý dùng trong **TLS/SSL (HTTPS)**, **PGP/GPG (mã hoá email)**: RSA (hoặc ECC) dùng để trao đổi khoá phiên an toàn lúc bắt đầu kết nối, sau đó toàn bộ dữ liệu truyền đi được mã hoá bằng AES vì tốc độ nhanh hơn nhiều lần.

---

## Kết luận

- AES nhanh, phù hợp mã hoá dữ liệu lớn, nhưng phải chia sẻ khoá bí mật trước.
- RSA giải quyết bài toán trao đổi khoá an toàn nhưng chậm với dữ liệu lớn.
- Kết hợp AES + RSA (Hybrid Encryption) tận dụng ưu điểm cả hai — đây là mô hình được dùng phổ biến trong thực tế như HTTPS/TLS, PGP/GPG.

## Cấu trúc thư mục

| Thư mục | Mô tả |
|---|---|
| `aes/cpp` | Cài đặt AES bằng C++ (tiny-AES-c) |
| `aes/web` | Demo AES bằng HTML/CSS/JS (CryptoJS) |
| `rsa/cpp` | Cài đặt RSA bằng C++ |
| `rsa/web` | Demo RSA bằng HTML/CSS/JS |
| `models` | Mô hình áp dụng RSA |
| `benchmark` | So sánh thời gian AES vs RSA |
| `docs` | Tài liệu mô tả thuật toán |



