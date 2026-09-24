# RSA (Rivest-Shamir-Adleman)

## Tên gọi
RSA - thuật toán mã hoá bất đối xứng (mã hoá công khai), công bố 1977 bởi 3 tác giả
Ron Rivest, Adi Shamir, Leonard Adleman. Dựa trên độ khó của bài toán phân tích
thừa số nguyên tố của số rất lớn.

## Nguyên lý sinh cặp khoá bí mật - công khai
1. Chọn 2 số nguyên tố lớn, khác nhau: p, q.
2. Tính n = p * q (n dùng làm modulo, la phan cua ca khoa cong khai va bi mat).
3. Tính phi(n) = (p-1)(q-1)  (ham Euler).
4. Chọn số e sao cho 1 < e < phi(n) và gcd(e, phi(n)) = 1 (e nguyên tố cùng nhau với phi(n)).
   -> Khoá công khai: (e, n)
5. Tính d là nghịch đảo modulo của e theo phi(n): d * e ≡ 1 (mod phi(n)).
   -> Khoá bí mật: (d, n)

## Mã hoá
Bản rõ M (số nguyên < n): C = M^e mod n

## Giải mã
Bản mã C: M = C^d mod n

## Vì sao an toàn
Biết (e, n) rất khó suy ra d nếu không biết p, q (phải phân tích n thành thừa số
nguyên tố - với n đủ lớn, hiện chưa có thuật toán hiệu quả để làm việc này trong
thời gian hợp lý bằng máy tính thông thường).
