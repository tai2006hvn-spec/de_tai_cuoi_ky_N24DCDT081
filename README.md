# ĐỒ ÁN HỌC PHẦN: CẤU TRÚC DỮ LIỆU VÀ GIẢI THUẬT (INT13185 — NHÓM 03)
## ĐỀ TÀI CÁ NHÂN DT066 — HOÀN THIỆN 100%

- **Họ và tên sinh viên**: Phạm Anh Tài
- **Mã số sinh viên**: N24DCDT081
- **Lớp sinh hoạt**: D24CQDT01-N
- **Mã đề tài**: DT066
- **Tên đề tài**: Chuyển biểu thức trung tố sang hậu tố (Thuật toán Sân ga Shunting Yard)
- **Giảng viên hướng dẫn**: ThS. Hồ Nhựt Minh
- **Ngôn ngữ lập trình**: C++ (Chuẩn C++17)
- **Trình biên dịch**: `g++ 16.2.0 (MSYS2 MinGW-w64 UCRT64)`
- **GitHub Repository**: https://github.com/tai2006hvn-spec/de_tai_cuoi_ky_N24DCDT081

---

### 1. Cấu trúc mã nguồn hoàn chỉnh 100%

```text
de_tai_cuoi_ky_N24DCDT081/
├── src/                                   # Phần 1: Cài đặt chuẩn theo phiếu DT066
│   ├── ShuntingYard.hpp                   # Khai báo ngăn xếp, độ ưu tiên và thuật toán Shunting Yard
│   └── ShuntingYard.cpp                   # Cài đặt chi tiết chuyển đổi số nguyên [0..100] & in bảng vết
├── demo_tien_do.cpp                       # Chương trình chạy 2 ví dụ phiếu, chế độ --expr và nhập bàn phím
├── test.cpp                               # Bộ kiểm thử độc lập 15 ca (A01 - A15) đạt 100% PASS
├── mo_rong/                               # Phần 2: Mở rộng biến chữ cái & Tính giá trị biểu thức hậu tố
│   ├── src/
│   │   ├── ShuntingYardAdvanced.hpp       # Khai báo mở rộng hỗ trợ biến chữ cái & bộ tính giá trị (Evaluator)
│   │   └── ShuntingYardAdvanced.cpp       # Hiện thực chuyển đổi + ngăn xếp toán hạng tính giá trị + bảng vết
│   ├── demo_advanced.cpp                  # Demo minh họa chuyển đổi và tính giá trị biểu thức có biến
│   └── test_advanced.cpp                  # Bộ kiểm thử độc lập 10 ca mở rộng (ADV01 - ADV10) đạt 100% PASS
├── docs/anh_ket_qua/                      # Lưu trữ 11 ảnh kết quả thật (A01 - A11) và sơ đồ minh họa
├── BaoCao/                                # Báo cáo đồ án hoàn chỉnh định dạng Word (.docx) và PDF (.pdf)
├── build.bat                              # Script tự động biên dịch cả Phần 1 & Phần 2 bằng g++
├── run_demo.bat                           # Script chạy nhanh demo Phần 1
├── run_test.bat                           # Script chạy nhanh 15 ca kiểm thử Phần 1
├── run_advanced.bat                       # Script chạy nhanh bộ test & demo Phần 2 Mở rộng
└── README.md                              # Tài liệu hướng dẫn chi tiết
```

---

### 2. Hướng dẫn biên dịch và chạy

Mở PowerShell hoặc Terminal tại thư mục gốc của mã nguồn:

#### 2.1. Kiểm tra trình biên dịch
```powershell
g++ --version
```

#### 2.2. Biên dịch toàn bộ (Phần 1 Cơ bản & Phần 2 Mở rộng)
```powershell
g++ -std=c++17 -Wall -Wextra -static src/ShuntingYard.cpp demo_tien_do.cpp -o demo_tien_do.exe
g++ -std=c++17 -Wall -Wextra -static src/ShuntingYard.cpp test.cpp -o test.exe
g++ -std=c++17 -Wall -Wextra -static mo_rong/src/ShuntingYardAdvanced.cpp mo_rong/demo_advanced.cpp -o mo_rong/demo_advanced.exe
g++ -std=c++17 -Wall -Wextra -static mo_rong/src/ShuntingYardAdvanced.cpp mo_rong/test_advanced.cpp -o mo_rong/test_advanced.exe
```
*(Hoặc chạy tệp `.\build.bat` để tự động biên dịch tất cả).*

#### 2.3. Chạy chương trình Phần 1 (Theo phiếu giao DT066)
* Chạy 2 ví dụ chuẩn trên phiếu + nhập biểu thức mới:
  ```powershell
  .\demo_tien_do.exe
  ```
* Chạy nhanh 2 ví dụ mẫu không dừng chờ nhập:
  ```powershell
  .\demo_tien_do.exe --sample
  ```
* Chạy bộ kiểm thử 15 ca độc lập:
  ```powershell
  .\test.exe
  ```

#### 2.4. Chạy chương trình Phần 2 (Mở rộng biến & Tính giá trị hậu tố)
* Chạy bộ kiểm thử mở rộng 10 ca độc lập:
  ```powershell
  .\mo_rong\test_advanced.exe
  ```
* Chạy demo chuyển đổi & tính giá trị có bảng lần vết chi tiết:
  ```powershell
  .\mo_rong\demo_advanced.exe
  ```

---

### 3. Tổng kết kết quả kiểm thử (100% PASS)
* **Phần 1 Cơ bản (`test.exe`)**: Đạt **15 / 15 ca kiểm thử độc lập (100% PASS)** bao gồm 2 ví dụ mẫu trên phiếu, 5 ca bắt buộc, ca tự thiết kế lũy thừa đa tầng (`2 ^ 2 ^ 3 ^ 2`), khảo sát 3 quy mô (5, 15, 41 token) và các ca kiểm tra từ chối cú pháp/miền giá trị lỗi.
* **Phần 2 Mở rộng (`mo_rong/test_advanced.exe`)**: Đạt **10 / 10 ca kiểm thử độc lập (100% PASS)** bao gồm hỗ trợ biến ký tự `a..z`, tính toán giá trị biểu thức hậu tố bằng ngăn xếp toán hạng và bắt lỗi thiếu biến/chia cho 0.
