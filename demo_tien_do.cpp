#include "src/ShuntingYard.hpp"
#include <iostream>
#include <string>

using namespace Phan1;

void chay_vi_du(int stt, const std::string& tieu_de, const std::string& input, const std::string& expected, const std::string& giai_thich) {
    std::cout << "\n========================================================================================\n";
    std::cout << "[VÍ DỤ " << stt << "] " << tieu_de << "\n";
    std::cout << "Dữ liệu vào (Input)   : " << input << "\n";
    std::cout << "Kỳ vọng (Expected)    : " << expected << "\n";
    std::cout << "Ghi chú giải thích    : " << giai_thich << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";

    ConversionResult res = trung_to_sang_hau_to(input, true);

    if (res.thanh_cong) {
        std::cout << ">> BẢNG LẦN VẾT (TRACE STACK & OUTPUT TỪNG TOKEN):\n";
        in_bang_lan_vet(res.bang_vet);
        std::cout << ">> KẾT QUẢ THỰC TẾ (Actual Output) : " << res.bieu_thuc_hau_to << "\n";
        std::cout << ">> ĐÁNH GIÁ : " << (res.bieu_thuc_hau_to == expected ? "[ PASS - ĐẠT KỲ VỌNG ]" : "[ FAIL - SAI KHÁC ]") << "\n";
        std::cout << ">> Thống kê: " << res.so_token << " token | "
                  << res.so_lan_day_stack << " lần push stack | "
                  << res.so_lan_lay_stack << " lần pop stack.\n";
    } else {
        std::cout << ">> LỖI: " << res.thong_bao_loi << "\n";
    }
}

int main() {

    system("chcp 65001 > nul");

    std::cout << "========================================================================================\n";
    std::cout << "       HỌC VIỆN CÔNG NGHỆ BƯU CHÍNH VIỄN THÔNG - CƠ SỞ TẠI TP. HỒ CHÍ MINH\n";
    std::cout << "          BÁO CÁO ĐỒ ÁN HỌC PHẦN: CẤU TRÚC DỮ LIỆU VÀ GIẢI THUẬT (INT13185)\n";
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << " Sinh viên thực hiện : Phạm Anh Tài\n";
    std::cout << " Mã số sinh viên     : N24DCDT081\n";
    std::cout << " Lớp sinh hoạt       : D24CQDT01-N\n";
    std::cout << " Mã đề tài           : DT066\n";
    std::cout << " Tên đề tài          : Chuyển biểu thức trung tố sang hậu tố (Thuật toán Sân ga)\n";
    std::cout << " Giảng viên HD       : ThS. Hồ Nhựt Minh\n";
    std::cout << "========================================================================================\n";

    chay_vi_du(1, "Biểu thức có ngoặc và thứ tự ưu tiên cơ bản",
               "5 * ( 6 + 2 ) - 12 / 4",
               "5 6 2 + * 12 4 / -",
               "Ngoặc buộc cộng trước nhân; phép chia được xuất trước phép trừ vì ưu tiên cao hơn.");

    chay_vi_du(2, "Quy tắc lũy thừa ^ kết hợp phải (right-associative)",
               "2 ^ 3 ^ 2",
               "2 3 2 ^ ^",
               "Lũy thừa kết hợp phải nên toán tử ^ trước không bị lấy ra khi gặp một ^ mới cùng ưu tiên.");

    std::cout << "\n========================================================================================\n";
    std::cout << "[CHẾ ĐỘ TƯƠNG TÁC NHẬP BÀN PHÍM]\n";
    std::cout << "Nhập biểu thức trung tố mới (hoặc gõ 'exit' để kết thúc):\n";

    std::string input;
    while (true) {
        std::cout << "\n>> Nhập biểu thức: ";
        if (!std::getline(std::cin, input) || input == "exit" || input == "quit") {
            break;
        }
        if (input.empty()) continue;

        ConversionResult res = trung_to_sang_hau_to(input, true);
        if (res.thanh_cong) {
            std::cout << ">> Bảng lần vết chi tiết:\n";
            in_bang_lan_vet(res.bang_vet);
            std::cout << ">> Kết quả biểu thức hậu tố: " << res.bieu_thuc_hau_to << "\n";
            std::cout << ">> Thống kê: " << res.so_token << " token | "
                      << res.so_lan_day_stack << " lần push | "
                      << res.so_lan_lay_stack << " lần pop.\n";
        } else {
            std::cout << ">> THÔNG BÁO LỖI: " << res.thong_bao_loi << "\n";
        }
    }

    std::cout << "\nChương trình kết thúc. Cảm ơn!\n";
    return 0;
}
