#include <iostream>
#include <cassert>
#include <string>
#include <fstream>

#include "include/VByte.hpp"

void read_unsorted(std::FILE* in, uint64_t block) {

    uint64_t n = 0;
    uint64_t m = 0;
    uint64_t read = std::fread(&n, sizeof(uint64_t), 1, in);
    assert(read == 1);
    const constexpr uint64_t buf_size = 512; 
    uint64_t* buffer = (uint64_t*)malloc(sizeof(uint64_t) * buf_size);
    uint64_t to_read = n; 
    pfp::VByte<uint64_t, uint8_t> vb(block);
    
    while (to_read > buf_size) {
        read = std::fread(buffer, sizeof(uint64_t), buf_size, in);
        assert(read == buf_size);

        for (uint64_t i = 0; i < buf_size; i++) {
            vb.VBencode(buffer[i]);
        }
        to_read -= buf_size;
    }

    read = std::fread(buffer, sizeof(uint64_t), to_read, in);
    assert(read == to_read);
    
    for (size_t i = 0; i < to_read; i++) {
        // std::cout << buffer[i] << "\n";
        vb.VBencode(buffer[i]);
       
    }
    free(buffer);
    std::cerr << vb.bytestream.size() << "\n";
    
}
void read_sorted(std::ifstream& in, uint64_t block) {
    uint64_t first, second;
    
    pfp::VByte<uint64_t, uint8_t> vbyte(block);
    if (in)
    {
        in.read(reinterpret_cast<char*>(&first), sizeof(first));
        in.read(reinterpret_cast<char*>(&first), sizeof(first));
        vbyte.VBencode(first);
        while (in.read(reinterpret_cast<char*>(&second), sizeof(second))) {
            vbyte.VBencode(second-first);
            first = second;
        
        }
        std::cerr << vbyte.bytestream.size() << "\n";
        vbyte.VBDecode_sum();
    }
    
}

int main(int argc, char const *argv[]) {
    int file_index = 1;
    int i = 1;
    
    bool sorted = false;
    uint64_t block = 7; // default blocksize is 7 bits
    
    while (i < argc) {
        std::string s(argv[i++]);
            
        if (s.compare("-s") == 0) {
            sorted = true;
        }
        else if (s.compare("-k") == 0) {
            std::string numero(argv[i]);
            block = std::stoi(numero);
        } else {
            file_index = i - 1;
        }
    }

    if (sorted == false) {
        read_unsorted(std::fopen(argv[file_index], "rb"), block);
    } else
    {
        std::ifstream in(argv[file_index], std::ifstream::binary);
        read_sorted(in, block);
    }
    
}


