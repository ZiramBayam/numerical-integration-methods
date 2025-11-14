#include <iostream>
#include <cmath>
#include <string>

const double PI = 3.14159265358979323846;

// Fungsi ini memungkinkan pengguna untuk memasukkan input seperti "pi", "-pi", "pi/2", "3/4", dll
double parseInput(const std::string& x) {
    if(x == "pi") return PI;
    if(x == "-pi") return -PI;
    
    size_t pos = x.find('/');
    if(pos != std::string::npos) {
        std::string num = x.substr(0, pos);
        std::string den = x.substr(pos+1);
        double pembilang = (num == "pi") ? PI : (num == "-pi") ? -PI : std::stod(num);
        double penyebut = (den == "pi") ? PI : (den == "-pi") ? -PI : std::stod(den);
        return pembilang / penyebut;
    }
    return std::stod(x);
}

// Soal pertama: cos(x)
double f_1(double x) { return cos(x); }

// Soal kedua: x^2
double f_2(double x) { return x * x; }

// Gaussian Quadrature dengan 3 titik (Gauss-Legendre)
double gaussianQuadrature(double (*f)(double), double a, double b) {
    double nodes[3] = {-sqrt(3.0/5.0), 0.0, sqrt(3.0/5.0)};
    double weights[3] = {5.0/9.0, 8.0/9.0, 5.0/9.0};
    double mid = (a + b) / 2.0;
    double half_length = (b - a) / 2.0;
    double sum = 0.0;
    
    for(int i = 0; i < 3; i++)
        sum += weights[i] * f(mid + half_length * nodes[i]);
    
    return half_length * sum;
}

int main() {
    std::string in;
    double a1, b1, a2, b2;

    std::cout << "\na. cos(x):" << std::endl;
    std::cout << "- Batas bawah: "; std::cin >> in; a1 = parseInput(in);
    std::cout << "- Batas atas: "; std::cin >> in; b1 = parseInput(in);
    
    std::cout << "\nb. x^2:" << std::endl;
    std::cout << "- Batas bawah: "; std::cin >> in; a2 = parseInput(in);
    std::cout << "- Batas atas: "; std::cin >> in; b2 = parseInput(in);
    
    std::cout << "\nHasil Gaussian Quadrature:" << std::endl;
    std::cout << "a. cos(x): " << gaussianQuadrature(f_1, a1, b1) << std::endl;
    std::cout << "b. x^2: " << gaussianQuadrature(f_2, a2, b2) << std::endl;
    
    return 0;
}