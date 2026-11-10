@echo off
chcp 65001 > nul
echo Dang bien dich toan bo chuong trinh C++17 (Phan 1 Co ban & Phan 2 Mo rong)...
g++ -std=c++17 -Wall -Wextra -static src\ShuntingYard.cpp demo_tien_do.cpp -o demo_tien_do.exe
g++ -std=c++17 -Wall -Wextra -static src\ShuntingYard.cpp test.cpp -o test.exe
g++ -std=c++17 -Wall -Wextra -static mo_rong\src\ShuntingYardAdvanced.cpp mo_rong\demo_advanced.cpp -o mo_rong\demo_advanced.exe
g++ -std=c++17 -Wall -Wextra -static mo_rong\src\ShuntingYardAdvanced.cpp mo_rong\test_advanced.cpp -o mo_rong\test_advanced.exe
if %ERRORLEVEL% EQU 0 (
    echo [THANH CONG] Bien dich hoan tat 100%% (Phan 1 & Phan 2 Mo rong)!
) else (
    echo [THAT BAI] Co loi bien dich!
)
pause
