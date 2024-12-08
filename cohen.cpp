#include <iostream>
using namespace std;

// Definisi kode wilayah untuk algoritma Cohen-Sutherland
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Definisi area tampilan
const int x_min = 10, y_min = 10, x_max = 200, y_max = 200;

// Fungsi untuk menghitung kode wilayah
int computeCode(int x, int y) {
    int code = INSIDE;
    if (x < x_min)       code |= LEFT;
    else if (x > x_max)  code |= RIGHT;
    if (y < y_min)       code |= BOTTOM;
    else if (y > y_max)  code |= TOP;
    return code;
}

// Fungsi untuk melakukan Cohen-Sutherland Line Clipping
void cohenSutherlandClip(int x1, int y1, int x2, int y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // Kedua titik berada di dalam area tampilan
            accept = true;
            break;
        } else if (code1 & code2) {
            // Kedua titik berada di luar area tampilan pada wilayah yang sama
            break;
        } else {
            // Setidaknya satu titik berada di luar area tampilan
            int code_out;
            int x, y;

            // Tentukan titik di luar area tampilan
            if (code1 != 0) code_out = code1;
            else            code_out = code2;

            // Hitung titik potong
            if (code_out & TOP) {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (code_out & BOTTOM) {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (code_out & RIGHT) {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (code_out & LEFT) {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Ganti titik di luar area tampilan dengan titik potong
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        cout << "Garis setelah clipping: (" << x1 << ", " << y1
             << ") ke (" << x2 << ", " << y2 << ")" << endl;
    } else {
        cout << "Garis berada di luar area tampilan." << endl;
    }
}

// Fungsi utama
int main() {
    int x1, y1, x2, y2;
    cout << "Masukkan koordinat titik awal (x1, y1): ";
    cin >> x1 >> y1;
    cout << "Masukkan koordinat titik akhir (x2, y2): ";
    cin >> x2 >> y2;

    cohenSutherlandClip(x1, y1, x2, y2);

    return 0;
}