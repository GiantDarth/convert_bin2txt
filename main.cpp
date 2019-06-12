#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
#include <boost/dynamic_bitset.hpp>

namespace fs = std::filesystem;

void generate_word_lines(std::string &text, size_t line_size, size_t word_size) {
    for (auto iter = text.begin(); std::distance(iter, text.end()) >= line_size + (line_size / word_size); ++iter ) {
        for(size_t i = 0; i < line_size / word_size - 1; i++) {
            std::advance(iter, word_size);
            // Insert a space at the current position and update the new word position
            iter = text.insert(iter, ' ');
        }

        std::advance(iter, word_size);
        // Insert a newline at the current position and update the new line position
        iter = text.insert(iter, '\n');
    }
}

int main() {
    fs::create_directory("test/out");

    fs::path out_dir("out");

    bool format = true;

    for(const auto &entry : fs::directory_iterator("test/bin")) {
        if(std::regex_match(entry.path().filename().string(), std::regex("read[0-9]+.bin"))) {
            boost::dynamic_bitset<> data_bits(100000);

            // Set out_path to out_dir/read[0-9]+.txt based on original read number
            fs::path out_path = out_dir / entry.path().stem();
            out_path += ".txt";

            std::cout << "Converting " << entry.path() << " to " << out_path << "..." << std::endl;

//            std::ifstream ifs(entry.path(), std::ios::binary);
//            // Input read binary file to bitset
//            ifs >> data_bits;

            std::string text;
            boost::to_string(data_bits, text);

            if(format) {
                // Format the bits be separating every 8 bits with a space, and every 64 bits with a newline.
                generate_word_lines(text, 64, 8);
            }

            std::ofstream ofs(out_path, std::ios::trunc);
            // Output bitset to out_path file as ASCII 0's and 1's
            ofs << text;
        }
    }

    return 0;
}