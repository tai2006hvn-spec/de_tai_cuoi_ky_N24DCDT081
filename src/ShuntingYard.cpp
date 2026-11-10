#include "ShuntingYard.hpp"
#include <cctype>
#include <algorithm>

namespace Phan1 {

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

bool la_so_nguyen_hop_le(const std::string& token, int& gia_tri) {
    if (token.empty()) return false;
    for (char c : token) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    try {
        long long val = std::stoll(token);
        if (val < 0 || val > 100) return false;
        gia_tri = static_cast<int>(val);
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

        char c = bieu_thuc[i];
        if (la_toan_tu(c) || c == '(' || c == ')') {
            tokens.push_back(std::string(1, c));
            i++;
            continue;
        }

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
        thong_bao_loi = "Lỗi quy cách: Vượt quá giới hạn tối đa 50 token (hiện có " +
                        std::to_string(tokens.size()) + " token).";
        return false;
    }

    int dem_ngoac = 0;
    bool cho_phep_toan_hang = true;
    int gia_tri = 0;

    for (size_t i = 0; i < tokens.size(); i++) {
        const std::string& t = tokens[i];

        if (t.length() == 1 && (t[0] == '(' || t[0] == ')')) {

        } else if (t.length() == 1 && la_toan_tu(t[0])) {

        } else if (la_so_nguyen_hop_le(t, gia_tri)) {

        } else {

            if (t.length() > 0 && t[0] == '-') {
                thong_bao_loi = "Lỗi cú pháp: Không hỗ trợ dấu âm đơn ngôi ('" + t + "') theo yêu cầu đề bài.";
            } else {
                thong_bao_loi = "Lỗi dữ liệu: Token '" + t + "' không hợp lệ (phải là số nguyên 0..100 hoặc toán tử +,-,*,/,^,()).";
            }
            return false;
        }

        if (t == "(") {
            dem_ngoac++;
            if (!cho_phep_toan_hang) {
                thong_bao_loi = "Lỗi cú pháp: Thiếu toán tử trước dấu ngoặc mở '(' tại vị trí token " + std::to_string(i + 1) + ".";
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
                thong_bao_loi = "Lỗi cú pháp: Thừa dấu ngoặc đóng ')' tại vị trí token " + std::to_string(i + 1) + ".";
                return false;
            }
            if (cho_phep_toan_hang) {
                thong_bao_loi = "Lỗi cú pháp: Dấu ngoặc đóng đứng ngay sau toán tử tại vị trí token " + std::to_string(i + 1) + ".";
                return false;
            }
            cho_phep_toan_hang = false;
        } else if (t.length() == 1 && la_toan_tu(t[0])) {
            if (cho_phep_toan_hang) {
                if (t == "-") {
                    thong_bao_loi = "Lỗi cú pháp: Không hỗ trợ dấu âm đơn ngôi ('-') theo yêu cầu đề bài.";
                } else {
                    thong_bao_loi = "Lỗi cú pháp: Toán tử nhị phân '" + t + "' không có toán hạng trước tại vị trí token " + std::to_string(i + 1) + ".";
                }
                return false;
            }
            cho_phep_toan_hang = true;
        } else {

            if (!cho_phep_toan_hang) {
                thong_bao_loi = "Lỗi cú pháp: Hai toán hạng liên tiếp thiếu toán tử ('" + t + "') tại vị trí token " + std::to_string(i + 1) + ".";
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

static std::string snapshot_stack(const std::vector<char>& st) {
    if (st.empty()) return "[ rỗng ]";
    std::string s = "[ ";
    for (char c : st) {
        s += c;
        s += " ";
    }
    s += "]";
    return s;
}

ConversionResult trung_to_sang_hau_to(const std::string& bieu_thuc, bool ghi_vet) {
    ConversionResult res;
    res.thanh_cong = false;
    res.bieu_thuc_hau_to = "";
    res.thong_bao_loi = "";
    res.so_token = 0;
    res.so_lan_day_stack = 0;
    res.so_lan_lay_stack = 0;

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
        TraceStep step;
        step.buoc = buoc++;
        step.token = token;

        int val = 0;
        if (la_so_nguyen_hop_le(token, val)) {
            step.loai_token = "Toán hạng";
            hau_to_tokens.push_back(token);
            step.hanh_dong = "Xuất '" + token + "' ra hậu tố";
        } else if (token == "(") {
            step.loai_token = "Ngoặc mở";
            ngan_xep.push_back('(');
            res.so_lan_day_stack++;
            step.hanh_dong = "Đẩy '(' vào ngăn xếp";
        } else if (token == ")") {
            step.loai_token = "Ngoặc đóng";
            std::string popped_ops = "";
            while (!ngan_xep.empty() && ngan_xep.back() != '(') {
                char op = ngan_xep.back();
                ngan_xep.pop_back();
                res.so_lan_lay_stack++;
                hau_to_tokens.push_back(std::string(1, op));
                if (!popped_ops.empty()) popped_ops += ", ";
                popped_ops += op;
            }
            if (!ngan_xep.empty() && ngan_xep.back() == '(') {
                ngan_xep.pop_back();
                res.so_lan_lay_stack++;
            }
            step.hanh_dong = "Pop (" + (popped_ops.empty() ? "không" : popped_ops) + ") và hủy ngoặc '()'";
        } else if (token.length() == 1 && la_toan_tu(token[0])) {
            char op1 = token[0];
            step.loai_token = "Toán tử";
            std::string popped_ops = "";

            while (!ngan_xep.empty() && ngan_xep.back() != '(') {
                char op2 = ngan_xep.back();
                int u1 = uu_tien(op1);
                int u2 = uu_tien(op2);

                if (u2 > u1 || (u2 == u1 && !ket_hop_phai(op1))) {
                    ngan_xep.pop_back();
                    res.so_lan_lay_stack++;
                    hau_to_tokens.push_back(std::string(1, op2));
                    if (!popped_ops.empty()) popped_ops += ", ";
                    popped_ops += op2;
                } else {
                    break;
                }
            }

            ngan_xep.push_back(op1);
            res.so_lan_day_stack++;

            if (popped_ops.empty()) {
                if (ket_hop_phai(op1)) {
                    step.hanh_dong = "'^' kết hợp phải: đẩy vào stack";
                } else {
                    step.hanh_dong = "Đẩy toán tử '" + token + "' vào stack";
                }
            } else {
                step.hanh_dong = "Pop (" + popped_ops + ") ra hậu tố, đẩy '" + token + "' vào stack";
            }
        }

        step.ngan_xep = snapshot_stack(ngan_xep);
        std::string ht_str = "";
        for (size_t k = 0; k < hau_to_tokens.size(); k++) {
            if (k > 0) ht_str += " ";
            ht_str += hau_to_tokens[k];
        }
        step.hau_to = ht_str.empty() ? "(chưa có)" : ht_str;

        if (ghi_vet) {
            res.bang_vet.push_back(step);
        }
    }

    if (!ngan_xep.empty()) {
        TraceStep final_step;
        final_step.buoc = buoc++;
        final_step.token = "<KẾT THÚC>";
        final_step.loai_token = "Hết chuỗi";

        std::string popped_ops = "";
        while (!ngan_xep.empty()) {
            char op = ngan_xep.back();
            ngan_xep.pop_back();
            res.so_lan_lay_stack++;
            if (op == '(') {
                res.thong_bao_loi = "Lỗi cú pháp: Dấu ngoặc mở '(' chưa đóng.";
                return res;
            }
            hau_to_tokens.push_back(std::string(1, op));
            if (!popped_ops.empty()) popped_ops += ", ";
            popped_ops += op;
        }

        final_step.hanh_dong = "Vét (" + popped_ops + ") từ stack ra hậu tố";
        final_step.ngan_xep = snapshot_stack(ngan_xep);

        std::string ht_str = "";
        for (size_t k = 0; k < hau_to_tokens.size(); k++) {
            if (k > 0) ht_str += " ";
            ht_str += hau_to_tokens[k];
        }
        final_step.hau_to = ht_str;

        if (ghi_vet) {
            res.bang_vet.push_back(final_step);
        }
    }

    std::string ket_qua = "";
    for (size_t k = 0; k < hau_to_tokens.size(); k++) {
        if (k > 0) ket_qua += " ";
        ket_qua += hau_to_tokens[k];
    }

    res.bieu_thuc_hau_to = ket_qua;
    res.thanh_cong = true;
    return res;
}

void in_bang_lan_vet(const std::vector<TraceStep>& bang_vet) {
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

}
