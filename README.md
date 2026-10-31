# ĐỒ ÁN HỌC PHẦN: CẤU TRÚC DỮ LIỆU VÀ GIẢI THUẬT (INT13185 — NHÓM 03)
## BÁO CÁO CÁ NHÂN: ĐỀ TÀI DT066 — LẦN 1

- **Họ và tên sinh viên**: Phạm Anh Tài
- **Mã số sinh viên**: N24DCDT081
- **Lớp**: D24CQDT01-N
- **Mã đề tài**: DT066
- **Tên đề tài**: Chuyển biểu thức trung tố sang hậu tố (Thuật toán sân ga Shunting Yard)
- **Giảng viên hướng dẫn**: ThS. Hồ Nhựt Minh
- **Ngôn ngữ lập trình**: C++ (Chuẩn C++17)
- **Trình biên dịch**: `g++ 16.2.0 (MSYS2 MinGW-w64 UCRT64)`
- **Môi trường phát triển**: Windows 10/11, Visual Studio Code
- **GitHub Repository**: https://github.com/tai2006hvn-spec/de_tai_cuoi_ky_N24DCDT081

---

### 1. Cấu trúc mã nguồn Lần 1
```text
de_tai_cuoi_ky_N24DCDT081/
├── src/
│   ├── ShuntingYard.hpp       # Khai báo cấu trúc token, ngăn xếp toán tử, bảng ưu tiên và hàm chuyển đổi
│   └── ShuntingYard.cpp       # Hiện thực thuật toán sân ga (Shunting Yard), bảng vết và kiểm tra cú pháp
├── demo_tien_do.cpp           # Chương trình chạy demo hai ví dụ trên phiếu và chế độ nhập từ bàn phím
├── test.cpp                   # Bộ kiểm thử độc lập 15 ca (A01 - A15) đạt 100% PASS
├── build.bat                  # Script biên dịch tự động bằng g++ (ra file .exe chạy độc lập -static)
├── run_demo.bat               # Script chạy demo
├── run_test.bat               # Script chạy bộ kiểm thử
├── BaoCao/                    # Báo cáo cá nhân bản Word (.docx) và PDF (.pdf)
└── README.md                  # Hướng dẫn chi tiết
```

---

### 2. Hướng dẫn biên dịch và chạy

Mở PowerShell hoặc CMD tại thư mục mã nguồn:

#### 2.1. Kiểm tra trình biên dịch trên máy:
```powershell
g++ --version
# Kết quả: g++.exe (Rev4, Built by MSYS2 project) 16.2.0
```

#### 2.2. Lệnh biên dịch bằng g++ (C++17):
```powershell
g++ -std=c++17 -Wall -Wextra -static src/ShuntingYard.cpp demo_tien_do.cpp -o demo_tien_do.exe
g++ -std=c++17 -Wall -Wextra -static src/ShuntingYard.cpp test.cpp -o test.exe
```
*(Hoặc nhấp đúp vào `build.bat` để biên dịch tự động).*

#### 2.3. Lệnh chạy chương trình demo:
```powershell
.\demo_tien_do.exe
```

#### 2.4. Lệnh chạy bộ kiểm thử độc lập:
```powershell
.\test.exe
```

---

### 3. Kết quả kiểm thử Lần 1
- **Ví dụ 1 trên phiếu**: `5 * ( 6 + 2 ) - 12 / 4` => `5 6 2 + * 12 4 / -` (**PASS 100%**, có bảng vết từng bước)
- **Ví dụ 2 trên phiếu**: `2 ^ 3 ^ 2` => `2 3 2 ^ ^` (**PASS 100%**, lũy thừa kết hợp phải)
- **5 ca quy định trên phiếu**:
  1. `"3 + 4 * 2"` => `"3 4 2 * +"` (**PASS**)
  2. `"( 2 + 3 ) * 4"` => `"2 3 + 4 *"` (**PASS**)
  3. `"9 - 3 - 1"` => `"9 3 - 1 -"` (**PASS**)
  4. `"8"` => `"8"` (**PASS**)
  5. `"( 2 + 3"` => Báo lỗi ngoặc chưa đóng (**PASS**)
- **Bộ kiểm thử độc lập**: **15 / 15 ca đạt PASS (100%)**.
