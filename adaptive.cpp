#include <iostream>
#include <cmath>
#include <string>

// Fungsi ini memungkinkan pengguna untuk memasukkan input seperti "pi", "-pi", "pi/2", "3/4", dll
double parseInput(const std::string& x) {
    if(x=="pi") return M_PI;
    if(x=="-pi") return -M_PI;
    if(x.find('/')!=std::string::npos) {
        size_t pos = x.find('/');
        std::string num = x.substr(0, pos);
        std::string den = x.substr(pos+1);
        double pembilang = (num=="pi" || num=="-pi") ? (num=="pi" ? M_PI : -M_PI) : std::stod(num);
        double penyebut = (den=="pi" || den=="-pi") ? (den=="pi" ? M_PI : -M_PI) : std::stod(den);
        return pembilang/penyebut;
    }
    return std::stod(x);
}

// Soal pertama: cos(x)
double f_1(double x) {
    return cos(x);
}

// Soal kedua: x^2
double f_2(double x) {
    return x*x;
}

// Simpson's Rule untuk menghitung integral pada satu interval [a, b]
// dengan c adalah titik tengah interval [a, b]
double simpson(double (*f)(double), double a, double b) {
    double c = (a+b)/2;
    return (b-a)/6*(f(a)+4*f(c)+f(b));
}

// Membagi interval menjadi dua bagian dan membandingkan hasilnya
// Jika error cukup kecil, kembalikan hasil. Jika tidak, rekursi ke sub-interval yang lebih kecil
double adaptiveRec(double (*f)(double), double a, double b, double eps, double S) {
    double c = (a+b)/2;
    // Hitung integral pada sub-interval kiri [a, c] dan kanan [c, b]
    double left = simpson(f, a, c);
    double right = simpson(f, c, b);
    // Jika error estimasi (|left+right-S|) <= 15*eps, interval sudah cukup akurat
    if(fabs(left+right-S) <= 15*eps)
        // Kembalikan hasil dengan koreksi error (Richardson extrapolation)
        return left+right+(left+right-S)/15;
    // Jika belum cukup akurat, rekursi ke sub-interval dengan toleransi yang lebih ketat (eps/2)
    return adaptiveRec(f, a, c, eps/2, left) + adaptiveRec(f, c, b, eps/2, right);
}

// Menghitung integral pada seluruh interval, lalu memanggil fungsi rekursif
double adaptiveIntegrate(double (*f)(double), double a, double b, double tol=1e-6) {
    double whole = simpson(f, a, b);
    return adaptiveRec(f, a, b, tol, whole);
}

int main() {
    std::string in;
    double a1, b1, a2, b2;
    
    std::cout << "a. cos(x)" << std::endl;
    std::cout << "- batas bawah: "; std::cin >> in; a1 = parseInput(in);
    std::cout << "- batas atas: "; std::cin >> in; b1 = parseInput(in);
    
    std::cout << "b. x^2" << std::endl;
    std::cout << "- batas bawah: "; std::cin >> in; a2 = parseInput(in);
    std::cout << "- batas atas: "; std::cin >> in; b2 = parseInput(in);

    std::cout << "\nHasil integrasi menggunakan metode adaptive integration : " << std::endl;
    std::cout << "a. cos(x) : " << adaptiveIntegrate(f_1, a1, b1) << std::endl;
    std::cout << "b. x^2 : " << adaptiveIntegrate(f_2, a2, b2) << std::endl;
    
    return 0;
}