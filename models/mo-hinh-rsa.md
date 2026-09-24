# 3 mô hình áp dụng RSA

## Mô hình 1 - Xác thực người nhận (bảo mật / confidentiality)
Người gửi mã hoá dữ liệu bằng KHOÁ CÔNG KHAI của người nhận.
Chỉ người nhận (giữ khoá bí mật tương ứng) mới giải mã được.

Sơ đồ: Gửi --[mã hoá bằng public key B]--> Bản mã --[giải mã bằng private key B]--> Nhận

Mục đích: đảm bảo chỉ đúng người nhận B mới đọc được nội dung (bảo mật),
không xác thực được ai là người gửi.

## Mô hình 2 - Xác thực người gửi (chữ ký số / authentication)
Người gửi "mã hoá" (thực chất là ký) dữ liệu (hoặc mã băm của dữ liệu) bằng
KHOÁ BÍ MẬT của chính mình. Bất kỳ ai có khoá công khai của người gửi đều
giải mã (xác minh chữ ký) được, qua đó xác nhận đúng là người gửi A đã tạo ra.

Sơ đồ: Gửi --[ky bang private key A]--> Chu ky --[xac minh bang public key A]--> Nhan

Mục đích: xác thực nguồn gốc (đúng là A gửi), chống chối bỏ (non-repudiation),
không đảm bảo bí mật vì ai cũng có public key A để "giải mã" xem nội dung.

## Mô hình 3 - Kết hợp cả 2 (bảo mật + xác thực)
Người gửi A: 
1. Ký lên dữ liệu (hoặc hash của dữ liệu) bằng private key của A.
2. Mã hoá (dữ liệu + chữ ký) bằng public key của người nhận B.

Người nhận B:
1. Giải mã bằng private key của B -> lấy lại (dữ liệu + chữ ký).
2. Xác minh chữ ký bằng public key của A -> xác nhận đúng A gửi và dữ liệu không bị sửa.

Mục đích: vừa đảm bảo bí mật (chỉ B đọc được), vừa xác thực người gửi (chắc chắn là A).
Đây là mô hình dùng phổ biến trong thực tế (email ký số + mã hoá, HTTPS/TLS...).
