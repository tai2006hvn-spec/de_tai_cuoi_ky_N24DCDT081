#include "ShuntingYardAdvanced.hpp"
#include <cctype>
#include <cmath>
#include <algorithm>

namespace Phan2 {

int uu_tien(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        case '(': return 0;
        default:  return -1;
    }
}

bool ket_hop_phai(char op) {
    return (op == '^');
}

bool la_toan_tu(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool la_bien_hop_le(const std::string& token) {
    if (token.empty()) return false;
    for (char c : token) {
        if (!std::isalpha(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

bool la_so_nguyen(const std::string& token, long long& val) {
    if (token.empty()) return false;
    for (char c : token) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    try {
        val = std::stoll(token);
        return true;
    } catch (...) {
        return false;
    }
}

std::vector<std::string> tach_token(const std::string& bieu_thuc) {
    std::vector<std::string> tokens;
    int n = static_cast<int>(bieu_thuc.length());
    int i = 0;

    while (i < n) {
        if (std::isspace(static_cast<unsigned char>(bieu_thuc[i]))) {
            i++;
            continue;
        }

        if (std::isdigit(static_cast<unsigned char>(bieu_thuc[i]))) {
            std::string num = "";
            while (i < n && std::isdigit(static_cast<unsigned char>(bieu_thuc[i]))) {
                num += bieu_thuc[i++];
            }
            tokens.push_back(num);
            continue;
        }

        if (std::isalpha(static_cast<unsigned char>(bieu_thuc[i]))) {
            std::string var = "";
            while (i < n && std::isalpha(static_cast<unsigned char>(bieu_thuc[i]))) {
                var += bieu_thuc[i++];
            }
            tokens.push_back(var);
            continue;
        }

        char c = bieu_thuc[i];
        tokens.push_back(std::string(1, c));
        i++;
    }
    return tokens;
}

bool kiem_tra_token(const std::vector<std::string>& tokens, std::string& thong_bao_loi) {
    if (tokens.empty()) {
        thong_bao_loi = "Lỗi cú pháp: Biểu thức rỗng.";
        return false;
    }

    if (tokens.size() > 50) {
        thong_bao_loi = "Lỗi quy cách: Vượt quá giới hạn tối đa 50 token.";
        return false;
    }

    int dem_ngoac = 0;
    bool cho_phep_toan_hang = true;
    long long val = 0;

    for (size_t i = 0; i < tokens.size(); i++) {
        const std::string& t = tokens[i];

        if (t == "(" || t == ")") {
        } else if (t.length() == 1 && la_toan_tu(t[0])) {
        } else if (la_bien_hop_le(t)) {
        } else if (la_so_nguyen(t, val)) {
            if (val < 0 || val > 100) {
                thong_bao_loi = "Lỗi dữ liệu: Số nguyên '" + t + "' vượt quá miền [0..100].";
                return false;
            }
        } else {
            thong_bao_loi = "Lỗi cú pháp: Token '" + t + "' không hợp lệ.";
            return false;
        }

        if (t == "(") {
            dem_ngoac++;
            if (!cho_phep_toan_hang) {
                thong_bao_loi = "Lỗi cú pháp: Thiếu toán tử trước dấu ngoặc mở '(' tại vị trí " + std::to_string(i + 1) + ".";
                return false;
            }
            if (i + 1 < tokens.size() && tokens[i + 1] == ")") {
                thong_bao_loi = "Lỗi cú pháp: Cặp ngoặc rỗng '()' không hợp lệ.";
                return false;
            }
            cho_phep_toan_hang = true;
        } else if (t == ")") {
            dem_ngoac--;
            if (dem_ngoac < 0) {
                thong_bao_loi = "Lỗi cú pháp: Thừa dấu ngoặc đóng ')' tại vị trí " + std::to_string(i + 1) + ".";
                return false;
            }
            if (cho_phep_toan_hang) {
                thong_bao_loi = "Lỗi cú pháp: Dấu ngoặc đóng đứng ngay sau toán tử.";
                return false;
            }
            cho_phep_toan_hang = false;
        } else if (t.length() == 1 && la_toan_tu(t[0])) {
            if (cho_phep_toan_hang) {
                if (t == "-") {
                    thong_bao_loi = "Lỗi cú pháp: Không hỗ trợ dấu âm đơn ngôi ('-').";
                } else {
                    thong_bao_loi = "Lỗi cú pháp: Toán tử nhị phân '" + t + "' không có toán hạng trước.";
                }
                return false;
            }
            cho_phep_toan_hang = true;
        } else {
            if (!cho_phep_toan_hang) {
                thong_bao_loi = "Lỗi cú pháp: Hai toán hạng liên tiếp thiếu toán tử ('" + t + "').";
                return false;
            }
            cho_phep_toan_hang = false;
        }
    }

    if (dem_ngoac != 0) {
        thong_bao_loi = "Lỗi cú pháp: Dấu ngoặc không cân bằng (ngoặc mở '(' chưa đóng).";
        return false;
    }

    if (cho_phep_toan_hang) {
        thong_bao_loi = "Lỗi cú pháp: Biểu thức kết thúc bằng một toán tử chưa hoàn chỉnh.";
        return false;
    }

    return true;
}

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

static std::string snapshot_op_stack(const std::vector<char>& st) {
    if (st.empty()) return "[ rỗng ]";
    std::string s = "[ ";
    for (char c : st) { s += c; s += " "; }
    s += "]";
    return s;
}

static std::string snapshot_val_stack(const std::vector<long long>& st) {
    if (st.empty()) return "[ rỗng ]";
    std::string s = "[ ";
    for (long long v : st) { s += std::to_string(v) + " "; }
    s += "]";
    return s;
}

AdvancedConversionResult trung_to_sang_hau_to(const std::string& bieu_thuc, bool ghi_vet) {
    AdvancedConversionResult res;
    res.thanh_cong = false;
    res.bieu_thuc_hau_to = "";
    res.thong_bao_loi = "";

    std::vector<std::string> tokens = tach_token(bieu_thuc);
    res.so_token = static_cast<int>(tokens.size());

    std::string err;
    if (!kiem_tra_token(tokens, err)) {
        res.thong_bao_loi = err;
        return res;
    }

    std::vector<char> ngan_xep;
    std::vector<std::string> hau_to_tokens;
    int buoc = 1;

    for (const std::string& token : tokens) {
        ConversionTraceStep step;
        step.buoc = buoc++;
        step.token = token;

        long long val = 0;
        if (la_so_nguyen(token, val) || la_bien_hop_le(token)) {
            step.loai_token = la_bien_hop_le(token) ? "Biến" : "Số nguyên";
            hau_to_tokens.push_back(token);
            step.hanh_dong = "Xuất toán hạng '" + token + "' ra hậu tố";
        } else if (token == "(") {
            step.loai_token = "Ngoặc mở";
            ngan_xep.push_back('(');
            step.hanh_dong = "Đẩy '(' vào stack";
        } else if (token == ")") {
            step.loai_token = "Ngoặc đóng";
            std::string popped = "";
            while (!ngan_xep.empty() && ngan_xep.back() != '(') {
                char op = ngan_xep.back();
                ngan_xep.pop_back();
                hau_to_tokens.push_back(std::string(1, op));
                if (!popped.empty()) popped += ", ";
                popped += op;
            }
            if (!ngan_xep.empty() && ngan_xep.back() == '(') {
                ngan_xep.pop_back();
            }
            step.hanh_dong = "Pop (" + (popped.empty() ? "rỗng" : popped) + "), hủy ngoặc";
        } else if (token.length() == 1 && la_toan_tu(token[0])) {
            char op1 = token[0];
            step.loai_token = "Toán tử";
            std::string popped = "";

            while (!ngan_xep.empty() && ngan_xep.back() != '(') {
                char op2 = ngan_xep.back();
                int u1 = uu_tien(op1);
                int u2 = uu_tien(op2);

                if (u2 > u1 || (u2 == u1 && !ket_hop_phai(op1))) {
                    ngan_xep.pop_back();
                    hau_to_tokens.push_back(std::string(1, op2));
                    if (!popped.empty()) popped += ", ";
                    popped += op2;
                } else {
                    break;
                }
            }

            ngan_xep.push_back(op1);
            if (popped.empty()) {
                if (ket_hop_phai(op1)) {
                    step.hanh_dong = "Kết hợp phải: đẩy '" + token + "' vào stack";
                } else {
                    step.hanh_dong = "Đẩy '" + token + "' vào stack";
                }
            } else {
                step.hanh_dong = "Pop (" + popped + ") ra hậu tố, đẩy '" + token + "'";
            }
        }

        step.ngan_xep = snapshot_op_stack(ngan_xep);
        std::string ht_str = "";
        for (size_t k = 0; k < hau_to_tokens.size(); k++) {
            if (k > 0) ht_str += " ";
            ht_str += hau_to_tokens[k];
        }
        step.hau_to = ht_str.empty() ? "(chưa có)" : ht_str;
        if (ghi_vet) res.bang_vet.push_back(step);
    }

    if (!ngan_xep.empty()) {
        ConversionTraceStep final_step;
        final_step.buoc = buoc++;
        final_step.token = "<END>";
        final_step.loai_token = "Hết chuỗi";
        std::string popped = "";
        while (!ngan_xep.empty()) {
            char op = ngan_xep.back();
            ngan_xep.pop_back();
            hau_to_tokens.push_back(std::string(1, op));
            if (!popped.empty()) popped += ", ";
            popped += op;
        }
        final_step.hanh_dong = "Vét (" + popped + ") từ stack ra hậu tố";
        final_step.ngan_xep = snapshot_op_stack(ngan_xep);

        std::string ht_str = "";
        for (size_t k = 0; k < hau_to_tokens.size(); k++) {
            if (k > 0) ht_str += " ";
            ht_str += hau_to_tokens[k];
        }
        final_step.hau_to = ht_str;
        if (ghi_vet) res.bang_vet.push_back(final_step);
    }

    std::string res_str = "";
    for (size_t k = 0; k < hau_to_tokens.size(); k++) {
        if (k > 0) res_str += " ";
        res_str += hau_to_tokens[k];
    }
    res.bieu_thuc_hau_to = res_str;
    res.thanh_cong = true;
    return res;
}

static long long luy_thua_nguyen(long long co_so, long long so_mu) {
    if (so_mu < 0) return 0;
    long long kq = 1;
    long long a = co_so;
    long long b = so_mu;
    while (b > 0) {
        if (b & 1) kq *= a;
        a *= a;
        b >>= 1;
    }
    return kq;
}

EvalResult tinh_gia_tri_hau_to(const std::string& hau_to, const std::map<std::string, long long>& bang_bien, bool ghi_vet) {
    EvalResult res;
    res.thanh_cong = false;
    res.gia_tri = 0;
    res.thong_bao_loi = "";

    std::vector<std::string> tokens = tach_token(hau_to);
    if (tokens.empty()) {
        res.thong_bao_loi = "Lỗi: Biểu thức hậu tố rỗng.";
        return res;
    }

    std::vector<long long> val_stack;
    int buoc = 1;

    for (const std::string& token : tokens) {
        EvalTraceStep step;
        step.buoc = buoc++;
        step.token = token;

        long long num = 0;
        if (la_so_nguyen(token, num)) {
            step.loai_token = "Số nguyên";
            val_stack.push_back(num);
            step.toan_hang_a = "-";
            step.toan_tu = "-";
            step.toan_hang_b = "-";
            step.phep_tinh = "Đẩy " + token + " vào stack";
            step.ket_qua_tam = std::to_string(num);
        } else if (la_bien_hop_le(token)) {
            step.loai_token = "Biến";
            auto it = bang_bien.find(token);
            if (it == bang_bien.end()) {
                res.thong_bao_loi = "Lỗi dữ liệu: Biến '" + token + "' chưa được gán giá trị.";
                return res;
            }
            long long val = it->second;
            val_stack.push_back(val);
            step.toan_hang_a = "-";
            step.toan_tu = "-";
            step.toan_hang_b = "-";
            step.phep_tinh = "Tra " + token + " = " + std::to_string(val);
            step.ket_qua_tam = std::to_string(val);
        } else if (token.length() == 1 && la_toan_tu(token[0])) {
            step.loai_token = "Toán tử";
            char op = token[0];

            if (val_stack.size() < 2) {
                res.thong_bao_loi = "Lỗi cấu trúc: Không đủ toán hạng cho toán tử '" + token + "'.";
                return res;
            }

            long long b = val_stack.back(); val_stack.pop_back();
            long long a = val_stack.back(); val_stack.pop_back();

            step.toan_hang_a = std::to_string(a);
            step.toan_tu = std::string(1, op);
            step.toan_hang_b = std::to_string(b);

            long long c = 0;
            switch (op) {
                case '+': c = a + b; break;
                case '-': c = a - b; break;
                case '*': c = a * b; break;
                case '/':
                    if (b == 0) {
                        res.thong_bao_loi = "Lỗi toán học: Phép chia cho 0 (" + std::to_string(a) + " / 0).";
                        return res;
                    }
                    c = a / b;
                    break;
                case '^':
                    if (b < 0) {
                        res.thong_bao_loi = "Lỗi toán học: Số mũ âm (" + std::to_string(b) + ") không hỗ trợ.";
                        return res;
                    }
                    c = luy_thua_nguyen(a, b);
                    break;
            }

            val_stack.push_back(c);
            step.phep_tinh = std::to_string(a) + " " + op + " " + std::to_string(b);
            step.ket_qua_tam = std::to_string(c);
        } else {
            res.thong_bao_loi = "Lỗi token: Token '" + token + "' không nhận dạng được.";
            return res;
        }

        step.ngan_xep_gia_tri = snapshot_val_stack(val_stack);
        if (ghi_vet) res.bang_vet.push_back(step);
    }

    if (val_stack.size() != 1) {
        res.thong_bao_loi = "Lỗi cấu trúc: Biểu thức hậu tố không hợp lệ (thừa toán hạng).";
        return res;
    }

    res.gia_tri = val_stack.back();
    res.thanh_cong = true;
    return res;
}

void in_bang_lan_vet_chuyen_doi(const std::vector<ConversionTraceStep>& bang_vet) {
    const std::string duong_vien = "+------+------------+------------+--------------------------------------------+------------------+----------------------------+";
    std::cout << "\n" << duong_vien << "\n";
    std::cout << "| " << can_le_trai_utf8("Bước", 4)
              << " | " << can_le_trai_utf8("Token", 10)
              << " | " << can_le_trai_utf8("Loại token", 10)
              << " | " << can_le_trai_utf8("Hành động xử lý", 42)
              << " | " << can_le_trai_utf8("Stack", 16)
              << " | " << can_le_trai_utf8("Hậu tố (Output)", 26)
              << " |\n";
    std::cout << duong_vien << "\n";

    for (const auto& s : bang_vet) {
        std::cout << "| " << can_le_trai_utf8(std::to_string(s.buoc), 4)
                  << " | " << can_le_trai_utf8(s.token, 10)
                  << " | " << can_le_trai_utf8(s.loai_token, 10)
                  << " | " << can_le_trai_utf8(s.hanh_dong, 42)
                  << " | " << can_le_trai_utf8(s.ngan_xep, 16)
                  << " | " << can_le_trai_utf8(s.hau_to, 26)
                  << " |\n";
    }
    std::cout << duong_vien << "\n";
}

void in_bang_lan_vet_tinh_toan(const std::vector<EvalTraceStep>& bang_vet) {
    const std::string duong_vien = "+------+--------+------------+------------+------+------------+-----------------------+------------+------------------------+";
    std::cout << "\n" << duong_vien << "\n";
    std::cout << "| " << can_le_trai_utf8("Bước", 4)
              << " | " << can_le_trai_utf8("Token", 6)
              << " | " << can_le_trai_utf8("Loại token", 10)
              << " | " << can_le_trai_utf8("Toán hạngA", 10)
              << " | " << can_le_trai_utf8("Phép", 4)
              << " | " << can_le_trai_utf8("Toán hạngB", 10)
              << " | " << can_le_trai_utf8("Phép tính thực hiện", 21)
              << " | " << can_le_trai_utf8("Kết quả", 10)
              << " | " << can_le_trai_utf8("Ngăn xếp giá trị", 22)
              << " |\n";
    std::cout << duong_vien << "\n";

    for (const auto& s : bang_vet) {
        std::cout << "| " << can_le_trai_utf8(std::to_string(s.buoc), 4)
                  << " | " << can_le_trai_utf8(s.token, 6)
                  << " | " << can_le_trai_utf8(s.loai_token, 10)
                  << " | " << can_le_trai_utf8(s.toan_hang_a, 10)
                  << " | " << can_le_trai_utf8(s.toan_tu, 4)
                  << " | " << can_le_trai_utf8(s.toan_hang_b, 10)
                  << " | " << can_le_trai_utf8(s.phep_tinh, 21)
                  << " | " << can_le_trai_utf8(s.ket_qua_tam, 10)
                  << " | " << can_le_trai_utf8(s.ngan_xep_gia_tri, 22)
                  << " |\n";
    }
    std::cout << duong_vien << "\n";
}

}
