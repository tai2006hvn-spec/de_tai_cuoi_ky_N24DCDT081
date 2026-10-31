#pragma once

#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace Phan1 {

struct TraceStep {
    int buoc;
    std::string token;
    std::string loai_token;
    std::string hanh_dong;
    std::string ngan_xep;
    std::string hau_to;
};

struct ConversionResult {
    bool thanh_cong;
    std::string bieu_thuc_hau_to;
    std::string thong_bao_loi;
    std::vector<TraceStep> bang_vet;
    int so_token;
    int so_lan_day_stack;
    int so_lan_lay_stack;
};

int uu_tien(char op);

bool ket_hop_phai(char op);

bool la_toan_tu(char c);

bool la_so_nguyen_hop_le(const std::string& token, int& gia_tri);

std::vector<std::string> tach_token(const std::string& bieu_thuc);

bool kiem_tra_token(const std::vector<std::string>& tokens, std::string& thong_bao_loi);

ConversionResult trung_to_sang_hau_to(const std::string& bieu_thuc, bool ghi_vet = true);

void in_bang_lan_vet(const std::vector<TraceStep>& bang_vet);

}
