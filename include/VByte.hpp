#include <vector>
#pragma once

namespace pfp {

template <class dtype>

class VByte {
    public:
        std::vector<dtype> bytestream;
        dtype blocksize;

        VByte(dtype block) {
            blocksize = (2 << (block-1));
        }

    void VBEncodeNumber(dtype n) {
        std::vector<dtype> temporary;
        while (true) {
            temporary.insert(temporary.begin(), n%blocksize);
            if (n < blocksize) {
                break;
            }
            n = n / blocksize;
        }
        temporary[temporary.size()-1] += blocksize;

        bytestream.insert(bytestream.end(), temporary.begin(), temporary.end());
    }




    std::vector<dtype> VBDecode() {
        std::vector<dtype> result;
        uint64_t n = 0;
        uint64_t b = 0;
        for (uint64_t i = 0; i < bytestream.size(); i++) {
            b = bytestream[i];
            if (b < blocksize) {
                n = blocksize * n + b;
            } else {
                n = blocksize * n + b - blocksize;
                result.push_back(n);
                n = 0;
            }
        }
        return result;
    }
};
} // namespace pfp