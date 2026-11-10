#include "src/ShuntingYardAdvanced.hpp"
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace Phan2;

void chay_demo_nang_cao(int stt, const std::string& tieu_de, const std::string& infix,
                         const std::map<std::string, long long>& bien, long long exp_val, bool check_exp = true) {
    std::cout << "\n========================================================================================\n";
    if (stt > 0) {
        std::cout << "[MỞ RỘNG " << stt << "] " << tieu_de << "\n";
    } else {
        std::cout << "[THỰC THI MỞ RỘNG] " << tieu_de << "\n";
    }
    std::cout << "Biểu thức trung tố     : " << infix << "\n";
    std::cout << "Bảng giá trị biến      : ";
    if (bien.empty()) {
        std::cout << "(không có biến)";
    } else {
        for (auto it = bien.begin(); it != bien.end(); ++it) {
            if (it != bien.begin()) std::cout << ", ";
            std::cout << it->first << " = " << it->second;
        }
    }
    std::cout << "\n----------------------------------------------------------------------------------------\n";

    AdvancedConversionResult c_res = trung_to_sang_hau_to(infix, true);
    if (!c_res.thanh_cong) {
        std::cout << ">> LỖI CHUYỂN ĐỔI: " << c_res.thong_bao_loi << "\n";
        return;
    }

    std::cout << ">> BƯỚC 1: BẢNG LẦN VẾT CHUYỂN TRUNG TỐ SANG HẬU TỐ:\n";
    in_bang_lan_vet_chuyen_doi(c_res.bang_vet);
    std::cout << ">> Chuỗi hậu tố thu được: " << c_res.bieu_thuc_hau_to << "\n";

    EvalResult e_res = tinh_gia_tri_hau_to(c_res.bieu_thuc_hau_to, bien, true);
    if (!e_res.thanh_cong) {
        std::cout << ">> LỖI TÍNH TOÁN: " << e_res.thong_bao_loi << "\n";
        return;
    }

    std::cout << "\n>> BƯỚC 2: BẢNG LẦN VẾT TÍNH GIÁ TRỊ HẬU TỐ (EVALUATOR):\n";
    in_bang_lan_vet_tinh_toan(e_res.bang_vet);
    std::cout << ">> KẾT QUẢ TÍNH TOÁN THỰC TẾ: " << e_res.gia_tri << "\n";
    if (check_exp) {
        std::cout << ">> KẾT QUẢ KỲ VỌNG          : " << exp_val << "\n";
        std::cout << ">> ĐÁNH GIÁ                  : " << (e_res.gia_tri == exp_val ? "[ PASS - CHÍNH XÁC ]" : "[ FAIL - SAI KHÁC ]") << "\n";
    }
}

int main(int argc, char* argv[]) {
    system("chcp 65001 > nul");

    std::cout << "========================================================================================\n";
    std::cout << "       HỌC VIỆN CÔNG NGHỆ BƯU CHÍNH VIỄN THÔNG - CƠ SỞ TẠI TP. HỒ CHÍ MINH\n";
    std::cout << "       BÁO CÁO ĐỒ ÁN CTDL&GT (INT13185) - PHẦN 2: MỞ RỘNG BIẾN VÀ TÍNH GIÁ TRỊ\n";
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << " Sinh viên thực hiện : Phạm Anh Tài - MSSV: N24DCDT081 - Lớp: D24CQDT01-N\n";
    std::cout << " Mã đề tài           : DT066 - Chuyển biểu thức trung tố sang hậu tố\n";
    std::cout << "========================================================================================\n";

    std::map<std::string, long long> vars1 = {{"a", 5}, {"b", 6}, {"c", 2}, {"d", 12}, {"e", 4}};
    chay_demo_nang_cao(1, "Biểu thức biến chữ cái tương ứng Ví dụ 1",
                       "a * ( b + c ) - d / e", vars1, 37, true);

    std::map<std::string, long long> vars2 = {{"x", 2}, {"y", 3}, {"z", 2}};
    chay_demo_nang_cao(2, "Lũy thừa kết hợp phải: x ^ y ^ z",
                       "x ^ y ^ z", vars2, 512, true);

    if (argc >= 2 && std::string(argv[1]) == "--sample") {
        return 0;
    }

    std::cout << "\n========================================================================================\n";
    std::cout << "[CHẾ ĐỘ TƯƠNG TÁC MỞ RỘNG - NHẬP BIỂU THỨC CÓ BIẾN VÀ TÍNH GIÁ TRỊ]\n";
    std::cout << "Nhập biểu thức trung tố mới (hoặc gõ '0' / 'exit' để kết thúc):\n";

    std::string input;
    while (true) {
        std::cout << "\n>> Nhập biểu thức (ví dụ a + b * 2): ";
        if (!std::getline(std::cin, input) || input == "exit" || input == "quit" || input == "0") {
            break;
        }
        if (input.empty()) continue;

        std::vector<std::string> tokens = tach_token(input);
        std::set<std::string> vars;
        for (const auto& t : tokens) {
            if (la_bien_hop_le(t)) vars.insert(t);
        }

        std::map<std::string, long long> bang_bien;
        for (const auto& v : vars) {
            std::cout << "   -> Nhập giá trị nguyên cho biến '" << v << "': ";
            long long val = 0;
            if (!(std::cin >> val)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                break;
            }
            bang_bien[v] = val;
        }
        if (!vars.empty()) {
            std::cin.ignore(10000, '\n');
        }

        chay_demo_nang_cao(0, "Biểu thức do người dùng nhập", input, bang_bien, 0, false);
    }

    std::cout << "\nChương trình mở rộng kết thúc.\n";
    return 0;
}
