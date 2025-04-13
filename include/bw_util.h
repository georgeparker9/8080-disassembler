#include <iostream>
#include <cmath>

namespace bwu {
class byte{
public:
    unsigned char val;

    byte(unsigned char num = 0) {
        val = num;
    }
};

class bytearray{

};

class bitvector{
public:
    unsigned int val;

    bitvector(unsigned int num = 0) {
        val = num;
    }

    unsigned int getbit(unsigned int index) {
        return (val >> index)%2;
    }

    unsigned int getrange(unsigned int start, unsigned int end) {
        unsigned int len = end-start;
        return (val >> start)%(static_cast<int>(std::pow(2,len)));
    }

    unsigned int poprange(unsigned int start, unsigned int end) {
        unsigned int tail = val%(static_cast<int>(std::pow(2,start)));
        unsigned int result = val >> end;
        result <<= start;
        result += tail;
        return result;
    }

    operator unsigned int() const {
        return val;
    }
};

};