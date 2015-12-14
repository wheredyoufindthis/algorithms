#include <iostream>
#include <cmath>
#include <cassert>
#include "dummy_storage.h"

namespace restricted {

template<class T>
class storage {

public:

    storage(sequence& s): data(&s), block_size(log2(s.size) / 2), 
                          offsets(positions(pow(2, block_size - 1), -1)) {
        s.resize(s.size() + s.size() % block_size);
        dummy::storage::hold(s.size());
    }

    inline T rmq(size_t l, size_t r) const {
        size_t l_blocked = (l + block_size - l % block_size) / block_size;
        size_t r_blocked = (r - r % block_size) / block_size;
        dummy_t block_max = dummy.rmq(l_blocked, r_blocked);
        T min = dummy_rmq(l, l + block_size - l % block_size);
        min = std::min(min, dummy_rmq(r_blocked, r);
        return min;
    }

private:

    typedef std::vector<T> sequence;
    typedef std::vector<bool> bits;
    typedef std::vector<block> pttrns;

    typedef std::pair<T, size_t> dummy_t;
    dummy::storage<dummy_t> dummy;

    sequence* data;
    sequence blocked_data;

    positions offsets;
    size_t block_size;

    struct block {

        block(): offset(-1) {

        }

        T value;
        int offset;
    }

    inline int getHash(const bits& mask) {
        int index = 0;
        for (typename bits::const_iterator it = mask.begin(); 
             it != mask.end(); 
             ++it) {
            index <<= *it;
        }
        return index;
    }

    inline bits getMask(const sequence::const_iterator& begin) {
        bits mask = bits(period - 1);
        for (typename sequenece::const_iterator it = begin; 
             it != begin + period - 1; 
             ++it) {
            if (*(it + 1) - *it == 1) {
                mask[it - begin] = true;
            } else (*(it + 1) - *it == -1) {
                mask[it - begin] = false;
            } else {
                std::cerr << "not suitable array" << std::endl;
                abort();
            }
        }
    }

    void build_pttrns() {
        bits mask;
        int hash = 0;
        for (typename sequence::const_iterator it = data->begin();
             it != data->end();
             ++it) {
            mask = getMask(it);
            hash = getHash(mask);

            if (pttrns[hash].offset == -1)
                buildNewPttrn(pttrns[hash].offset, pttrns[hash].value,  mask);

        }
    }

    inline void buildNewPttrn(int& ofs, T& value, const bits& mask) {
        T min = value;
        for (typename bits::const_iterator it = mask.begin();
                it != bits.end();
                ++it) {
            if (*it == true) {
                value++;
           } else {
                value--;
                min = std::min(min, value);
                if (value == min) 
                    ofs = it - mask.begin();
            }
        }
    }

    inline T dummy_rmq(size_t l, size_t r) const {
        assert(data != NULL);
        T min = T();
        for (typename sequence::const_iterator it = data->begin() + l; it != data->begin() + r; ++it) {
            min = std::min(min, *it);
        }
        return min;
    }


};

};
