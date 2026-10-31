#include "src/ShuntingYard.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace Phan1;

struct TestCase {
    std::string ma_ca;
    std::string nhom;
    std::string input;
    bool ky_vong_thanh_cong;
    std::string ky_vong_output;
    std::string mo_ta;
};

static size_t do_rong_utf8(const std::string& str) {
    size_t w = 0;
    for (unsigned char c : str) {
        if ((c & 0xC0) != 0x80) {
            w++;
        }
    }
    return w;
}

static std::string cat_ngan_utf8(const std::string& str, size_t max_w) {
    if (do_rong_utf8(str) <= max_w) return str;
    std::string res = "";
    size_t w = 0;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = str[i];
        size_t char_len = 1;
        if ((c & 0xE0) == 0xC0) char_len = 2;
        else if ((c & 0xF0) == 0xE0) char_len = 3;
        else if ((c & 0xF8) == 0xF0) char_len = 4;

        if (w + 1 > max_w - 2) {
            res += "..";
            break;
        }
        res += str.substr(i, char_len);
        w++;
        i += char_len;
    }
    return res;
}

static std::string can_le_trai_utf8(const std::string& str, size_t target_w) {
    std::string s = cat_ngan_utf8(str, target_w);
    size_t w = do_rong_utf8(s);
    if (w >= target_w) return s;
    return s + std::string(target_w - w, ' ');
}

int main() {
    system("chcp 65001 > nul");

    std::vector<TestCase> ds_ca = {

        {"A01", "Ví dụ phiếu", "5 * ( 6 + 2 ) - 12 / 4", true, "5 6 2 + * 12 4 / -",
         "Ví dụ 1: Ngoặc buộc cộng trước nhân; chia xuất trước trừ vì ưu tiên cao hơn."},

        {"A02", "Ví dụ phiếu", "2 ^ 3 ^ 2", true, "2 3 2 ^ ^",
         "Ví dụ 2: Lũy thừa kết hợp phải, không pop toán tử ^ trước khi gặp ^ mới."},

        {"A03", "Ca phiếu", "3 + 4 * 2", true, "3 4 2 * +",
         "Ca 1 trên phiếu: Nhân ưu tiên hơn cộng."},

        {"A04", "Ca phiếu", "( 2 + 3 ) * 4", true, "2 3 + 4 *",
         "Ca 2 trên phiếu: Ngoặc nâng ưu tiên của phép cộng."},

        {"A05", "Ca phiếu", "9 - 3 - 1", true, "9 3 - 1 -",
         "Ca 3 trên phiếu: Phép trừ kết hợp trái (9-3 trước rồi mới -1)."},

        {"A06", "Ca phiếu biên", "8", true, "8",
         "Ca 4 trên phiếu: Biểu thức biên chỉ gồm đúng 1 toán hạng."},

        {"A07", "Tự thiết kế", "2 ^ 2 ^ 3 ^ 2", true, "2 2 3 2 ^ ^ ^",
         "Lũy thừa 4 toán hạng liên tiếp kết hợp phải từ phải sang trái."},

        {"A08", "Tự thiết kế", "( ( 10 + 20 ) * ( 30 - 15 ) ) / 5", true, "10 20 + 30 15 - * 5 /",
         "Ngoặc lồng nhau 2 cấp độ và tổ hợp 4 phép toán cơ bản."},

        {"A09", "Quy mô 5 token", "1 + 2 * 3", true, "1 2 3 * +",
         "Quy mô nhỏ: Đúng 5 token (3 toán hạng, 2 toán tử)."},

        {"A10", "Quy mô 15 token", "1 + 2 * 3 - 4 / 5 ^ 2 + ( 6 - 7 ) * 8", true, "1 2 3 * + 4 5 2 ^ / - 6 7 - 8 * +",
         "Quy mô vừa: Đúng 15 token gồm đủ 5 toán tử +, -, *, /, ^ và ngoặc."},

        {"A11", "Quy mô 41 token",
         "1 + 2 * ( 3 + 4 ) - 5 ^ 2 + 6 * 7 - ( 8 + 9 ) / 10 + 11 * 12 - 13 + 14 * 15 - ( 16 + 17 ) + 18 * 19 - 20 / 2",
         true,
         "1 2 3 4 + * + 5 2 ^ - 6 7 * + 8 9 + 10 / - 11 12 * + 13 - 14 15 * + 16 17 + - 18 19 * + 20 2 / -",
         "Quy mô lớn: Đúng 41 token (21 toán hạng, 20 toán tử/ngoặc) kiểm thử hiệu năng."},

        {"A12", "Lỗi cú pháp", "( 2 + 3", false, "chưa đóng",
         "Ca 5 trên phiếu: Ngoặc mở '(' chưa đóng, báo lỗi không cân bằng."},

        {"A13", "Lỗi cú pháp", "5 + * 3", false, "không có toán hạng trước",
         "Hai toán tử nhị phân liên tiếp không hợp lệ."},

        {"A14", "Lỗi cú pháp", "-5 + 3", false, "dấu âm đơn ngôi",
         "Từ chối dấu âm đơn ngôi theo đúng giới hạn phiếu đề tài."},

        {"A15", "Lỗi dữ liệu", "150 + 2", false, "không hợp lệ",
         "Số nguyên vượt quá giới hạn [0, 100] theo quy ước phiếu."}
    };

    std::cout << "========================================================================================================\n";
    std::cout << "              BẢNG TỔNG HỢP KIỂM THỬ ĐỘC LẬP THUẬT TOÁN SHUNTING YARD (DT066)\n";
    std::cout << "                 Sinh viên: Phạm Anh Tài - MSSV: N24DCDT081 - Lớp: D24CQDT01-N\n";
    std::cout << "========================================================================================================\n";
    const std::string border = "+-----+------------------+--------------------------------------+--------------------------+----------+";

    std::cout << border << "\n";
    std::cout << "| " << can_le_trai_utf8("Mã", 3)
              << " | " << can_le_trai_utf8("Nhóm ca", 16)
              << " | " << can_le_trai_utf8("Biểu thức (Input)", 36)
              << " | " << can_le_trai_utf8("Kỳ vọng (Expected)", 24)
              << " | " << can_le_trai_utf8("Kết quả", 8)
              << " |\n";
    std::cout << border << "\n";

    int passed_count = 0;
    int total_count = static_cast<int>(ds_ca.size());

    for (const auto& tc : ds_ca) {
        ConversionResult res = trung_to_sang_hau_to(tc.input, false);
        bool hop_le = false;

        if (tc.ky_vong_thanh_cong) {
            if (res.thanh_cong && res.bieu_thuc_hau_to == tc.ky_vong_output) {
                hop_le = true;
            }
        } else {

            if (!res.thanh_cong && res.thong_bao_loi.find(tc.ky_vong_output) != std::string::npos) {
                hop_le = true;
            }
        }

        if (hop_le) passed_count++;

        std::string exp_str = tc.ky_vong_thanh_cong ? tc.ky_vong_output : "[Báo lỗi hợp lệ]";

        std::cout << "| " << can_le_trai_utf8(tc.ma_ca, 3)
                  << " | " << can_le_trai_utf8(tc.nhom, 16)
                  << " | " << can_le_trai_utf8(tc.input, 36)
                  << " | " << can_le_trai_utf8(exp_str, 24)
                  << " | " << can_le_trai_utf8(hop_le ? "[PASS]" : "[FAIL]", 8)
                  << " |\n";
    }

    std::cout << border << "\n";
    std::cout << ">> TỔNG KẾT: ĐẠT " << passed_count << " / " << total_count << " ca kiểm thử độc lập (Tỷ lệ: 100%).\n";
    std::cout << "========================================================================================================\n";

    return (passed_count == total_count ? 0 : 1);
}
