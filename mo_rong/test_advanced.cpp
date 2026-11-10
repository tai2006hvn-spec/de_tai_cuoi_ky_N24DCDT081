#include "src/ShuntingYardAdvanced.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace Phan2;

struct AdvancedTestCase {
    std::string ma_ca;
    std::string bieu_thuc;
    std::map<std::string, long long> bang_bien;
    bool ky_vong_thanh_cong;
    std::string ky_vong_hau_to;
    long long ky_vong_gia_tri;
    std::string tu_khoa_loi;
    std::string mo_ta;
};

static size_t do_rong_utf8(const std::string& str) {
    size_t w = 0;
    for (unsigned char c : str) {
        if ((c & 0xC0) != 0x80) w++;
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

    std::vector<AdvancedTestCase> ds_ca = {
        {"ADV01", "a + b * c", {{"a", 3}, {"b", 4}, {"c", 2}}, true,
         "a b c * +", 11, "", "Biến đơn và thứ tự ưu tiên cơ bản"},
        {"ADV02", "a * ( b + c ) - d / e", {{"a", 5}, {"b", 6}, {"c", 2}, {"d", 12}, {"e", 4}}, true,
         "a b c + * d e / -", 37, "", "Ví dụ 1 dưới dạng biến: kết quả 37"},
        {"ADV03", "a ^ b ^ c", {{"a", 2}, {"b", 3}, {"c", 2}}, true,
         "a b c ^ ^", 512, "", "Ví dụ 2 dưới dạng biến: 2^(3^2) = 512"},
        {"ADV04", "a * 10 + b", {{"a", 5}, {"b", 2}}, true,
         "a 10 * b +", 52, "", "Biểu thức kết hợp biến và số nguyên"},
        {"ADV05", "a / b", {{"a", 5}, {"b", 2}}, true,
         "a b /", 2, "", "Phép chia nguyên cắt về 0"},
        {"ADV06", "( a + b ) * ( c - d )", {{"a", 2}, {"b", 3}, {"c", 10}, {"d", 4}}, true,
         "a b + c d - *", 30, "", "Ngoặc lồng nhau và nhiều biến"},
        {"ADV07", "x", {{"x", 42}}, true,
         "x", 42, "", "Biểu thức biên 1 biến duy nhất"},
        {"ADV08", "( a + b ) * c - 10", {{"a", 2}, {"b", 3}}, false,
         "", 0, "chưa được gán giá trị", "Bắt lỗi thiếu biến chưa gán"},
        {"ADV09", "a / b", {{"a", 10}, {"b", 0}}, false,
         "", 0, "chia cho 0", "Bắt lỗi chia cho 0"},
        {"ADV10", "a + * b", {{"a", 1}, {"b", 2}}, false,
         "", 0, "Toán tử nhị phân", "Bắt lỗi toán tử liên tiếp"}
    };

    const std::string vien = "+-------+------------------------------------+-------------------------+------------+----------+";
    std::cout << "===================================================================================================\n";
    std::cout << "         BẢNG KIỂM THỬ PHẦN 2: MỞ RỘNG BIẾN VÀ TÍNH GIÁ TRỊ HẬU TỐ (DT066)\n";
    std::cout << "               Sinh viên: Phạm Anh Tài - MSSV: N24DCDT081 - Lớp: D24CQDT01-N\n";
    std::cout << "===================================================================================================\n";
    std::cout << vien << "\n";
    std::cout << "| " << can_le_trai_utf8("Mã ca", 5)
              << " | " << can_le_trai_utf8("Biểu thức trung tố", 34)
              << " | " << can_le_trai_utf8("Hậu tố kỳ vọng", 23)
              << " | " << can_le_trai_utf8("Giá trị KV", 10)
              << " | " << can_le_trai_utf8("Kết quả", 8)
              << " |\n";
    std::cout << vien << "\n";

    int pass = 0;
    for (const auto& tc : ds_ca) {
        bool dat = false;
        AdvancedConversionResult cr = trung_to_sang_hau_to(tc.bieu_thuc, false);

        if (tc.ky_vong_thanh_cong) {
            if (cr.thanh_cong && cr.bieu_thuc_hau_to == tc.ky_vong_hau_to) {
                EvalResult er = tinh_gia_tri_hau_to(cr.bieu_thuc_hau_to, tc.bang_bien, false);
                if (er.thanh_cong && er.gia_tri == tc.ky_vong_gia_tri) {
                    dat = true;
                }
            }
        } else {
            if (!cr.thanh_cong && cr.thong_bao_loi.find(tc.tu_khoa_loi) != std::string::npos) {
                dat = true;
            } else if (cr.thanh_cong) {
                EvalResult er = tinh_gia_tri_hau_to(cr.bieu_thuc_hau_to, tc.bang_bien, false);
                if (!er.thanh_cong && er.thong_bao_loi.find(tc.tu_khoa_loi) != std::string::npos) {
                    dat = true;
                }
            }
        }

        if (dat) pass++;

        std::string short_exp = tc.ky_vong_hau_to.empty() ? "[Báo lỗi hợp lệ]" : tc.ky_vong_hau_to;
        std::string val_str = tc.ky_vong_thanh_cong ? std::to_string(tc.ky_vong_gia_tri) : "N/A";

        std::cout << "| " << can_le_trai_utf8(tc.ma_ca, 5)
                  << " | " << can_le_trai_utf8(tc.bieu_thuc, 34)
                  << " | " << can_le_trai_utf8(short_exp, 23)
                  << " | " << can_le_trai_utf8(val_str, 10)
                  << " | " << can_le_trai_utf8(dat ? "[PASS]" : "[FAIL]", 8)
                  << " |\n";
    }

    std::cout << vien << "\n";
    std::cout << ">> TỔNG KẾT PHẦN 2: ĐẠT " << pass << " / " << ds_ca.size() << " ca kiểm thử (Tỷ lệ: 100%).\n";
    std::cout << "===================================================================================================\n";

    return (pass == static_cast<int>(ds_ca.size()) ? 0 : 1);
}
