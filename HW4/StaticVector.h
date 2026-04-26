//
// Created by Mohammed RHAZI on 25/04/2026.
//

#ifndef HW4_STATICVECTOR_H
#define HW4_STATICVECTOR_H

template<typename T, std::size_t N>
class StaticVector {
    T data[N];
    std::size_t s = 0;

public:
    constexpr std::size_t size() const { return s;}
    constexpr std::size_t capacity() const {return N;}
    constexpr bool empty() const {return s==0;}

    //access
    T& operator[](std::size_t i) const {
        return data[i];
    }
    //push_back
    void push_back(const T& value) {
        if (s>=N) {
            throw std::out_of_range("capacity exceeded");
        }
        data[s++] = value;
    }
    //iterators
    T* begin() { return data;}
    T* end() {return data + s;}
};

#endif //HW4_STATICVECTOR_H