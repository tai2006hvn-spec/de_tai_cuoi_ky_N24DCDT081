#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace Phan2 {

struct ConversionTraceStep {
    int buoc;
    std::string token;
    std::string loai_token;
    std::string hanh_dong;
    std::string ngan_xep;
    std::string hau_to;
};

struct AdvancedConversionResult {
    bool thanh_cong;
    std::string bieu_thuc_hau_to;
    std::string thong_bao_loi;
    std::vector<ConversionTraceStep> bang_vet;
    int so_token;
};

struct EvalTraceStep {
    int buoc;
    std::string token;
    std::string loai_token;
    std::string toan_hang_a;
    std::string toan_tu;
    std::string toan_hang_b;
    std::string phep_tinh;
    std::string ket_qua_tam;
    std::string ngan_xep_gia_tri;
};

struct EvalResult {
    bool thanh_cong;
    long long gia_tri;
    std::string thong_bao_loi;
    std::vector<EvalTraceStep> bang_vet;
};

int uu_tien(char op);
bool ket_hop_phai(char op);
bool la_toan_tu(char c);
bool la_bien_hop_le(const std::string& token);
bool la_so_nguyen(const std::string& token, long long& val);

std::vector<std::string> tach_token(const std::string& bieu_thuc);
bool kiem_tra_token(const std::vector<std::string>& tokens, std::string& thong_bao_loi);

AdvancedConversionResult trung_to_sang_hau_to(const std::string& bieu_thuc, bool ghi_vet = true);
EvalResult tinh_gia_tri_hau_to(const std::string& hau_to, const std::map<std::string, long long>& bang_bien, bool ghi_vet = true);

void in_bang_lan_vet_chuyen_doi(const std::vector<ConversionTraceStep>& bang_vet);
void in_bang_lan_vet_tinh_toan(const std::vector<EvalTraceStep>& bang_vet);

}
