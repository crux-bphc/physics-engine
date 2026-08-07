#pragma once

#include <array>
#include <cstddef>

namespace math {

template <size_t _rows, size_t _cols, typename T>

class Matrix {
    static_assert(sizeof(T) == 4, "Matrix has not been implemented for non 4-byte types yet!");
    private:
    std::array<T, _rows * _cols> data;

    public:
    Matrix() {
        data.fill(T{});
    }

    inline T& operator()(size_t row, size_t col) {
        return data[row * _cols + col];
    }

    inline const T& operator()(size_t row, size_t col) const {
        return data[row * _cols + col];
    }
    
    inline T& operator[](size_t index) {
        return data[index];
    }

    inline const T& operator[](size_t index) const {
        return data[index];
    }
};

template <size_t R1, size_t C1R2, size_t C2, typename T>
Matrix<R1, C2, T> matmul(const Matrix<R1, C1R2, T>& m1, const Matrix<C1R2, C2, T>& m2) {
    Matrix<R1, C2, T> res;
    for(size_t i = 0; i < R1; i++) {
        for(size_t j = 0; j < C2; j++) {
            for(size_t k = 0; k < C1R2; k++) {
                res(i, j) += m1(i, k) * m2(k, j);
            }
        }
    }

    return res;
}  
}