# PTIT-CPP-2025-WalletManager
# Các thành viên của dự án
- Đinh Quốc Đạt - B24DTCN020
- Phan Thanh Minh Châu-B24DTCN019
- Lê Vũ Huy Trung - B24DTCN024
- Nguyễn Thế Quang - B24DTCN022


# Ví Điện Tử C++ - wallet_system.exe

Đây là ứng dụng ví điện tử cơ bản được viết bằng ngôn ngữ C++ thuần (console app). Chương trình hỗ trợ tạo tài khoản, đăng nhập, chuyển điểm, xác thực OTP, và phân quyền người dùng (admin/user).

## 🔧 Hướng dẫn chạy `wallet_system.exe`

### ⚠️ Yêu cầu môi trường:
- Windows (khuyến nghị Windows 10+)
- Cài **MinGW** nếu máy bạn chưa có (dùng để chạy chương trình C++)

✅ Hướng dẫn cài đặt MinGW trên Windows
📌 Bước 1: Tải MinGW
Truy cập link chính thức:
👉 https://osdn.net/projects/mingw/releases/

Chọn bản mingw-get-setup.exe để tải về.

📌 Bước 2: Cài đặt
Mở file mingw-get-setup.exe

Chọn vị trí cài đặt (giữ mặc định là C:\MinGW)

Khi cài xong, mở MinGW Installation Manager

📌 Bước 3: Chọn thành phần cần cài
Trong cửa sổ MinGW Installation Manager, chọn:

mingw32-base ✅

mingw32-gcc-g++ ✅ (bắt buộc cho C++)

mingw32-gcc-objc ❌ (không cần)

msys-base (tùy chọn nếu muốn command line giống Unix)

➡ Bấm chuột phải → chọn Mark for Installation

📌 Bước 4: Cài đặt
Trên menu: Installation > Apply Changes

Chọn Apply → MinGW sẽ tải và cài đặt.

📌 Bước 5: Cấu hình biến môi trường (PATH)
Vào Start → gõ "Environment variables" → chọn Edit the system environment variables

Bấm Environment Variables...

Trong phần System variables, chọn Path → Edit

Bấm New, thêm đường dẫn sau:
 C:\MinGW\bin
Bấm OK để lưu lại.

📌 Bước 6: Kiểm tra
Mở cmd hoặc PowerShell
Gõ lệnh:
bash g++ --version
✅ Nếu hiện phiên bản G++, bạn đã cài đặt thành công.

# 🧠 Mô tả chức năng
👥 Quản lý người dùng
Đăng ký tài khoản

Mỗi user mới được admin cấp 100 điểm

Nếu ví admin < 100 điểm → không thể đăng ký

Đăng nhập tài khoản

Quên mật khẩu

Xác thực bằng mã OTP

Nhập mật khẩu mới

💸 Chuyển điểm
Người dùng có thể chuyển điểm cho nhau

Cần xác thực bằng mã OTP

Lưu lịch sử giao dịch

🛠️ Quản trị viên (admin)
Tạo user mới thủ công

Xem danh sách user

Xoá user

Điểm của user sẽ chuyển về ví admin

Không thể xoá tài khoản có vai trò admin

Phân biệt chức năng qua role (admin / user)

## Tài khoản admin
username: admin
password: 123456
