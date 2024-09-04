#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "include/VByte.hpp"

int main(int argc, char const *argv[])
{   

    int x = 1;
    bool sorted = false;
    int input_file = 1;
    uint64_t block = 7;
    

    while (x < argc) {
        std::string s(argv[x++]);
        if (s.compare("-s") == 0) {
            sorted = true;
            input_file = 2;
        }
        else if (s.compare("-k") == 0) {
            std::string numero(argv[x]);
            block = std::stoi(numero);
        } else {
            input_file = x - 1;
        }
    }
    pfp::VByte<uint64_t> VByte(block);
    if (sorted == true) {
        uint64_t b;
        std::fstream in;
        in.open(argv[input_file], std::ios::in | std::ios::binary);
        if (in) {
            in.read(reinterpret_cast<char*>(&b), sizeof(b));
            uint64_t table[b];
            in.read(reinterpret_cast<char*>(table), sizeof(table));
            in.close();
            VByte.VBEncodeNumber(table[0]);
            for (uint64_t i = 0; i < b-1; i++) {
                uint64_t difference = table[i+1] - table[i]; 
                VByte.VBEncodeNumber(difference);
                
                
            }
            
            uint64_t blocks = VByte.bytestream.size();
            std::cout << blocks << "\n";
            auto result = VByte.VBDecode();
            uint64_t summa = 0;
            for (u_int64_t i = 0; i < result.size(); i++) {
                summa += result[i];
                std::cout << summa << "\n";
            }
        }
    } else {
        uint64_t b;
        std::fstream in;
        in.open(argv[input_file], std::ios::in | std::ios::binary);
        if (in)
        {
            in.read(reinterpret_cast<char*>(&b), sizeof(b));
            uint64_t table[b];
            in.read(reinterpret_cast<char*>(table), sizeof(table));
            in.close();

            for (uint64_t i = 0; i < b; i++) {
                VByte.VBEncodeNumber(table[i]);
            }
            
            uint64_t blocks = VByte.bytestream.size();
            std::cout << blocks << "\n";
            auto result = VByte.VBDecode();
        
            for (u_int64_t i = 0; i < result.size(); i++) {
                std::cout << result[i] << "\n";
        }
        }
    }
    
    
    return 0;
    
}
