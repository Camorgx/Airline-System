#ifndef Vector_hpp
#define Vector_hpp

#include <stdexcept>
#include <initializer_list>

class VectorError : public std::runtime_error {
public:
    explicit VectorError(const std::string& information) : runtime_error(information) {}
    const char* what() const noexcept override { return runtime_error::what(); }
};

template<typename DataType>
class Vector {
    DataType* dat = new DataType[8];
    //Actual size of the space allocated.
    size_t actual_size = 0;
    //Size of the dynamic array.
    size_t array_size = 0;
public:
    Vector() = default;
    Vector(Vector<DataType>&& b) noexcept = default;
    Vector(const Vector<DataType>& b) { *this = b; }
    Vector(std::initializer_list<DataType> initializerList) {
        array_size = initializerList.size();
        for (int i = 0; i < array_size; ++i)
            dat[i] = std::move(initializerList[i]);
    }
    ~Vector() { delete[] dat; }

    Vector<DataType>& operator=(Vector<DataType>&& b) noexcept = default;
    Vector<DataType>& operator=(const Vector<DataType>& b) {
        if (this == &b) return *this;
        dat = new DataType[actual_size = b.actual_size];
        array_size = b.array_size;
        for (int i = 0; i < b.actual_size; ++i) dat[i] = b[i];
        return *this;
    }
    bool operator==(const Vector<DataType>& b) const {
        if (dat == b.dat) return true;
        if (array_size != b.array_size) return false;
        for (int i = 0; i < array_size; ++i)
            if (dat[i] != b.dat[i]) return false;
        return true;
    }
    DataType& operator[](const int id) const {
        if (id >= 0 && id < array_size) return dat[id];
        else throw VectorError("Array out of bounds.");
    }

    size_t size() const { return array_size; }
    DataType* begin() const { return dat; }
    DataType* end() const { return dat + array_size; }
    void push_back(const DataType& x) {
        if (array_size >= actual_size) {
            try {
                auto* tmp = new DataType[actual_size * 2];
                for (int i = 0; i < actual_size; ++i)
                    tmp[i] = std::move(dat[i]);
                actual_size *= 2;
            }
            catch (std::bad_alloc&) {
                throw VectorError("Failed to allocate memory.");
            }
        }
        dat[array_size++] = x;
    }
    void pop_back() {
        if (!array_size) --array_size;
        else throw VectorError("Array already empty.");
    }
};

#endif // !Vector_hpp
