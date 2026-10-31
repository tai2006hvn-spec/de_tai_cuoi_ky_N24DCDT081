@echo off
chcp 65001 > nul
echo Dang bien dich chuong trinh C++17 bang g++...
g++ -std=c++17 -Wall -Wextra -static src\ShuntingYard.cpp demo_tien_do.cpp -o demo_tien_do.exe
g++ -std=c++17 -Wall -Wextra -static src\ShuntingYard.cpp test.cpp -o test.exe
if %ERRORLEVEL% EQU 0 (
    echo [THANH CONG] Bien dich thanh cong demo_tien_do.exe va test.exe!
) else (
    echo [THAT BAI] Co loi bien dich!
)
pause
