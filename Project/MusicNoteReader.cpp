#include "MusicNoteReader.h"

MusicNoteReader::MusicNoteReader(const std::string& filename) : filename(filename) {}

std::vector<float> MusicNoteReader::readNumbers() {
    std::vector<float> numbers;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Tidak dapat membuka file: " << filename << std::endl;
        // Mengembalikan array kosong jika file gagal dibuka
        return numbers; 
    }

    float number;
    while (file >> number) {
        // Jika vektor numbers tidak kosong, periksa selisih dengan angka terakhir
        if (!numbers.empty() && (number - numbers.back() < 200)) {
            continue; // Lewati angka jika selisihnya kurang dari 200
        }
        numbers.push_back(number);
    }

    file.close();
    return numbers;
}
