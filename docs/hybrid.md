# Kết hợp AES + RSA (Hybrid Encryption)

## Vấn đề
- AES nhanh nhưng là mã hoá đối xứng: 2 bên phải có chung 1 khoá bí mật -> khó trao đổi khoá an toàn qua kênh không tin cậy.
- RSA giải quyết được bài toán trao đổi khoá (bất đối xứng) nhưng lại rất chậm với dữ liệu lớn.

## Giải pháp: Hybrid Encryption
Kết hợp điểm mạnh của cả 2:

1. Bên gửi tạo ngẫu nhiên 1 khoá AES (gọi là "session key"), dùng khoá này
   mã hoá TOÀN BỘ dữ liệu thật (nhanh, vì là AES).
2. Bên gửi mã hoá khoá AES đó (chỉ vài chục byte) bằng KHOÁ CÔNG KHAI RSA
   của người nhận (chậm nhưng dữ liệu rất nhỏ nên không đáng kể).
3. Gửi đi: [dữ liệu đã mã hoá AES] + [khoá AES đã mã hoá bằng RSA].
4. Bên nhận: dùng khoá bí mật RSA của mình giải mã ra khoá AES gốc,
   rồi dùng khoá AES đó giải mã dữ liệu thật.

## Sơ đồ
Ben gui: Du lieu goc --AES.encrypt(session_key)--> Du lieu mahoa session_key --RSA.encrypt(public_key_B)--> session_key_mahoa Gui: [Du lieu mahoa] + [session_key_mahoa]

Ben nhan (B): session_key_mahoa --RSA.decrypt(private_key_B)--> session_key Du lieu mahoa --AES.decrypt(session_key)--> Du lieu goc
## Ứng dụng thực tế
Đây chính là nguyên lý dùng trong **TLS/SSL (HTTPS)**, **PGP/GPG (mã hoá email)**:
RSA (hoặc ECC) dùng để trao đổi khoá phiên an toàn lúc bắt đầu kết nối,
sau đó toàn bộ dữ liệu truyền đi được mã hoá bằng AES vì tốc độ nhanh hơn nhiều lần.
