#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

// Fungsi ini memungkinkan pengguna untuk memasukkan input seperti "pi", "-pi", "pi/2", "3/4", dll
double parseInput(const std::string& x) {
    if(x == "pi") return M_PI;
    if(x == "-pi") return -M_PI;
    
    if(x.find('/') != std::string::npos) {
        size_t pos = x.find('/');
        std::string num = x.substr(0, pos);
        std::string den = x.substr(pos+1);
        double pembilang, penyebut;

        if(num == "pi" || num == "-pi") 
            pembilang = (num == "pi" ? M_PI : -M_PI);
        else 
            pembilang = std::stod(num);

        if(den == "pi" || den == "-pi")
            penyebut = (den == "pi" ? M_PI : -M_PI);
        else
            penyebut = std::stod(den);

        return pembilang / penyebut;
    }
    
    return std::stod(x);
}

// Soal pertama: cos(x)
double f_1(double x) {
    return cos(x);
}

// Soal kedua: x^2
double f_2(double x) {
    return x * x;
}

double romberg(double (*f)(double), double a, double b, int n, double table[6][6]) {
    int NMAX = n;
    double h = b - a;
    
    // Langkah 1: Hitung R(0,0) menggunakan aturan trapezoidal dengan 1 interval
    table[0][0] = 0.5 * h * (f(a) + f(b));
    
    // Langkah 2: Hitung kolom pertama (R(i,0)) menggunakan aturan trapezoidal
    for(int i = 1; i <= NMAX; ++i) {
        h /= 2;
        double sum = 0;
        int maxj = 1 << (i-1);

        for(int k = 1; k <= maxj; ++k) {
            sum += f(a + (2*k-1)*h);
        }

        // Formula rekursif untuk aturan trapezoidal dengan subdivisi
        table[i][0] = 0.5 * table[i-1][0] + h * sum;
    }
    
    // Langkah 3: Hitung elemen-elemen lainnya menggunakan ekstrapolasi Richardson
    for(int j = 1; j <= NMAX; ++j) {
        for(int i = j; i <= NMAX; ++i) {
            table[i][j] = table[i][j-1] + (table[i][j-1] - table[i-1][j-1]) / (pow(4,j)-1);
        }
    }
    return table[NMAX][NMAX];
}

// Mencetak tabel Romberg dalam format segitiga
void printTable(double table[6][6], int n) {
    for(int i=0; i<=n; ++i) {
        for(int j=0; j<=i; ++j) {
            std::cout << std::fixed << std::setprecision(5) << table[i][j];
            if(j<i) std::cout << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string in;
    double a1, b1, a2, b2;
    int N = 5;
    double table1[6][6] = {0};
    double table2[6][6] = {0};

    std::cout << "a. cos(x):" << std::endl;
    std::cout << " - Batas bawah: "; std::cin >> in; a1 = parseInput(in);
    std::cout << " - Batas atas: "; std::cin >> in; b1 = parseInput(in);

    std::cout << "b. x^2:" << std::endl;
    std::cout << " - Batas bawah: "; std::cin >> in; a2 = parseInput(in);
    std::cout << " - Batas atas: "; std::cin >> in; b2 = parseInput(in);

    double result1 = romberg(f_1, a1, b1, N, table1);
    double result2 = romberg(f_2, a2, b2, N, table2);

    std::cout << "\nHasil integrasi menggunakan metode romberg :" << std::endl;
    
    std::cout << "a. cos(x) : " << result1 << std::endl;
    std::cout << "Tabel Romberg untuk cos(x):" << std::endl;
    printTable(table1, N);

    std::cout << "\nb. x^2 : " << result2 << std::endl;
    std::cout << "Tabel Romberg untuk x^2:" << std::endl;
    printTable(table2, N);

    return 0;
}