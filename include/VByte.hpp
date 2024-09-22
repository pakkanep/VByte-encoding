#include <iostream>
#include <deque>

#pragma once
namespace pfp {

template<class dtype, class dtype2>
class VByte {
    public:
        std::deque<dtype2> bytestream;
        dtype chunk, blocksize;

        VByte(dtype block) {
            chunk = block;
            blocksize = (2 << (block-1));
        }

        void VBencode(dtype val) {
            dtype vbyte = (val & (blocksize - 1)) | blocksize;
            val = (val >> chunk);
            int vbyte_len = 1;
            while (val > 0) {
                vbyte = (vbyte << (chunk + 1)) | (val & (blocksize-1));
                val = (val >> chunk);
                vbyte_len = vbyte_len + 1;
            }

            while (vbyte_len > 0) {
                bytestream.push_back(vbyte & ((2 << chunk)-1));
                vbyte = (vbyte >> (chunk+1));
                vbyte_len = vbyte_len - 1;
            }

        }

    void VBDecode_sum() {
        std::ios_base::sync_with_stdio(0);
        std::cin.tie(0);
        uint64_t summa = 0;
        uint64_t n = 0;
        uint64_t b = 0;
        int size = bytestream.size();
        for (int i = 0; i < size; i++) {
            b = *bytestream.begin(); 
            
            bytestream.pop_front();
            if (b < blocksize) {
                n = (n << chunk) + b;
            } else {
                n = (n << chunk) + b - blocksize;
                summa += n;
                std::cout << (summa) << "\n";
                n = 0;
            }
        }
    
    }


    void VBDecode() {
        std::ios_base::sync_with_stdio(0);
        std::cin.tie(0);
        uint64_t n = 0;
        uint64_t b = 0;
        int size = bytestream.size();
        for (int i = 0; i < size; i++) {
            b = *bytestream.begin(); 
            bytestream.pop_front();
            if (b < (blocksize)) {
                n = (n << chunk) + b;
            } else {
                n = (n << chunk) + b - (blocksize);
                std::cout << (n) << "\n";
                n = 0;
            }
        }
    
    }
};
}
