# Numerical Integration Methods (C++)

Repository ini berisi implementasi sederhana beberapa metode numerik untuk menghitung integral tertentu menggunakan C++:

- `adaptive.cpp` — Adaptive Simpson (rekursif) untuk integrasi adaptif.
- `gaussian.cpp` — Gaussian quadrature (Gauss–Legendre) dengan 3 titik.
- `Romberg.cpp` (atau `romberg.cpp`) — Metode Romberg dengan tabel ekstrapolasi Richardson.

## Ringkasan metode

- Adaptive Simpson (`adaptive.cpp`)

  - Menggunakan aturan Simpson pada interval, membagi interval jika estimasi galat terlalu besar, dan memakai koreksi Richardson.
  - Fungsi utama: `double adaptiveIntegrate(double (*f)(double), double a, double b, double tol=1e-6)`

- Gaussian Quadrature (`gaussian.cpp`)

  - Implementasi Gauss–Legendre 3-titik (degree 5 exact untuk polinomial sampai 5).
  - Fungsi utama: `double gaussianQuadrature(double (*f)(double), double a, double b)`

- Romberg (`Romberg.cpp` / `romberg.cpp`)
  - Membangun tabel Romberg (trapezoid + ekstrapolasi Richardson) hingga N langkah.
  - Fungsi utama: `double romberg(double (*f)(double), double a, double b, int n, double table[6][6])`

## Format input yang didukung

Semua program membaca batas bawah dan batas atas integrasi lewat input terminal. Mereka menggunakan fungsi `parseInput` yang menerima format berikut:

- Angka desimal biasa, mis. `0`, `1.25`, `-2`
- `pi` atau `-pi` untuk nilai π dan -π
- Pecahan yang melibatkan angka atau `pi`, mis. `pi/2`, `-pi/4`, `3/4`

Contoh yang valid: `-pi`, `pi/2`, `0`, `1`, `3/4`.

## Cara build (Windows — PowerShell)

Jika Anda menggunakan MinGW / g++ di Windows, jalankan di PowerShell dari root repo (folder yang berisi file `.cpp`):

```powershell
g++ -std=c++11 -O2 -o adaptive.exe adaptive.cpp
g++ -std=c++11 -O2 -o gaussian.exe gaussian.cpp
# Jika file di repo bernama "Romberg.cpp" (besar R):
g++ -std=c++11 -O2 -o romberg.exe Romberg.cpp
# Jika file bernama "romberg.cpp" (kecil r):
g++ -std=c++11 -O2 -o romberg.exe romberg.cpp
```

Catatan: pada beberapa toolchain, `M_PI` (konstanta π) adalah ekstensi. Dengan g++/MinGW biasanya tersedia; jika compiler menolak `M_PI`, Anda dapat mengganti pemakaian `M_PI` dengan literal `3.14159265358979323846` atau tambahkan definisi sebelum include math (pada MSVC diperlukan define khusus).

## Cara menjalankan

Setiap executable akan meminta dua input (batas bawah lalu batas atas) untuk masing-masing soal (a. cos(x) dan b. x^2). Contoh menjalankan `adaptive.exe`:

```powershell
.\adaptive.exe
# Program akan menanyakan batas bawah lalu batas atas (format contoh: -pi, pi/2, 0, 1, 3/4)
```

Untuk `gaussian.exe` dan `romberg.exe` jalankan serupa:

```powershell
.\gaussian.exe
.\romberg.exe
```

`Romberg` selain menampilkan nilai akhir juga mencetak tabel Romberg (segitiga) untuk nilai intermediate.

## Contoh sesi singkat

Jika ingin mengintegralkan `cos(x)` dari `-pi` ke `pi` dan `x^2` dari `0` ke `1`:

- Saat diminta batas bawah: masukkan `-pi`
- Saat diminta batas atas: masukkan `pi`
- Untuk soal kedua masukkan `0` lalu `1`

Output (pendek) akan menampilkan hasil integrasi untuk kedua fungsi.

## Catatan implementasi & batasan

- Semua program menggunakan fungsi C-style `double f(double)` untuk merepresentasikan fungsi yang diintegralkan. Jika Anda ingin mengubah fungsi, edit definisi `f_1` dan `f_2` di masing-masing file.
- Toleransi default untuk integrasi adaptif adalah `1e-6` (dapat diubah di pemanggilan `adaptiveIntegrate`).
- Gaussian yang dipakai adalah aturan 3-titik (kuadratur Gauss-Legendre 3-node); hasilnya sangat baik untuk polinomial hingga derajat 5.
- Romberg mengisi tabel hingga N = 5 (di kode); Anda dapat mengubah `N` untuk presisi/biaya yang berbeda.

## Troubleshooting

- Jika Anda tidak memiliki `g++` di PATH, install MinGW-w64 atau gunakan WSL (Windows Subsystem for Linux) lalu compile di sana.
- Jika ada error nama file `Romberg.cpp` vs `romberg.cpp`, sesuaikan nama file pada perintah compile dengan nama yang ada di filesystem (Windows filesystem biasanya case-insensitive, tapi build scripts / tools linting di sistem lain bisa sensitif).

## Lisensi

Proyek ini adalah contoh pendidikan; tambahkan lisensi sesuai kebutuhan (mis. MIT) bila ingin membagikan publik.

---

Jika mau, saya bisa:

- Menambahkan contoh run yang direkam (sesi input/output lengkap).
- Menambahkan test unit kecil (mis. perbandingan hasil numerik dengan solusi analitik untuk fungsi sederhana).

Beritahu saya fitur tambahan mana yang Anda mau.
