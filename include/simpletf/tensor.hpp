#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include "simpletf/base.h"

namespace simpletf {

// TODO: Add TensorShape class to manage tensor shape

template <typename T>
class Flat {
public:
    Flat(T* data, size_t size) : data_(data), size_(size) {}

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    size_t size() const {
        return size_;
    }

private:
    T* data_;
    size_t size_;
};

class Tensor {
public:

    enum class DataType {
        Float = 0,
        Int = 1,
        String = 2,
        Bool = 3,
        Double = 4,
        Long = 5,
        Invalid = 6,
    };

    Tensor() : data_(nullptr), size_(0), dtype_(DataType::Invalid) {}

    // 构造函数
    Tensor(const std::vector<int>& shape, DataType dtype)
        : shape_(shape), size_(CalculateSize(shape)), dtype_(dtype) {
        switch (dtype_) {
            case DataType::Float:
                data_ = new float[size_];
                break;
            case DataType::Int:
                data_ = new int[size_];
                break;
            case DataType::String:
                data_ = new std::string[size_];
                break;
            case DataType::Bool:
                data_ = new bool[size_];
                break;
            case DataType::Double:
                data_ = new double[size_];
                break;
            case DataType::Long:
                data_ = new long[size_];
                break;
            default:
                throw std::invalid_argument("Unsupported data type");
        }
    }

    // 析构函数
    ~Tensor() {
        if (data_ == nullptr) return;
        switch (dtype_) {
            case DataType::Float:
                delete[] static_cast<float*>(data_);
                break;
            case DataType::Int:
                delete[] static_cast<int*>(data_);
                break;
            case DataType::String:
                delete[] static_cast<std::string*>(data_);
                break;
            case DataType::Bool:
                delete[] static_cast<bool*>(data_);
                break;
            case DataType::Double:
                delete[] static_cast<double*>(data_);
                break;
            case DataType::Long:
                delete[] static_cast<long*>(data_);
                break;
            default:
                break;
        }
    }

    // 获取形状
    const std::vector<int>& shape() const {
        return shape_;
    } 

    const DataType& dtype() const {
        return dtype_;
    }

    // 获取数据
    template <typename T>
    T& at(size_t index){
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        if constexpr (std::is_same_v<T, float>) {
            if (dtype_ != DataType::Float) throw std::bad_variant_access();
            return *(static_cast<float*>(data_) + index);
        } else if constexpr (std::is_same_v<T, int>) {
            if (dtype_ != DataType::Int) throw std::bad_variant_access();
            return *(static_cast<int*>(data_) + index);
        } else if constexpr (std::is_same_v<T, std::string>) {
            if (dtype_ != DataType::String) throw std::bad_variant_access();
            return *(static_cast<std::string*>(data_) + index);
        } else if constexpr (std::is_same_v<T, bool>) {
            if (dtype_ != DataType::Bool) throw std::bad_variant_access();
            return *(static_cast<bool*>(data_) + index);
        } else if constexpr (std::is_same_v<T, double>) {
            if (dtype_ != DataType::Double) throw std::bad_variant_access();
            return *(static_cast<double*>(data_) + index);
        } else if constexpr (std::is_same_v<T, long>) {
            if (dtype_ != DataType::Long) throw std::bad_variant_access();
            return *(static_cast<long*>(data_) + index);
        } else {
            throw std::invalid_argument("Unsupported data type");
        }
    }

    // 打印张量内容
    void Print() const {
        std::cout << "Tensor shape: [";
        for (size_t i = 0; i < shape_.size(); ++i) {
            std::cout << shape_[i];
            if (i < shape_.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    template <typename T>
    Flat<T> flat() {
        if constexpr (std::is_same_v<T, float>) {
            if (dtype_ != DataType::Float) throw std::bad_variant_access();
            return Flat<T>(static_cast<float*>(data_), size_);
        } else if constexpr (std::is_same_v<T, int>) {
            if (dtype_ != DataType::Int) throw std::bad_variant_access();
            return Flat<T>(static_cast<int*>(data_), size_);
        } else if constexpr (std::is_same_v<T, std::string>) {
            if (dtype_ != DataType::String) throw std::bad_variant_access();
            return Flat<T>(static_cast<std::string*>(data_), size_);
        } else if constexpr (std::is_same_v<T, bool>) {
            if (dtype_ != DataType::Bool) throw std::bad_variant_access();
            return Flat<T>(static_cast<bool*>(data_), size_);
        } else if constexpr (std::is_same_v<T, double>) {
            if (dtype_ != DataType::Double) throw std::bad_variant_access();
            return Flat<T>(static_cast<double*>(data_), size_);
        } else if constexpr (std::is_same_v<T, long>) {
            if (dtype_ != DataType::Long) throw std::bad_variant_access();
            return Flat<T>(static_cast<long*>(data_), size_);
        } else {
            throw std::invalid_argument("Unsupported data type");
        }
    }    

private:
    std::vector<int> shape_;    // 张量的形状
    void* data_;                // 数据指针
    size_t size_;               // 数据大小
    DataType dtype_;            // 数据类型

    // 计算张量的总大小
    static size_t CalculateSize(const std::vector<int>& shape) {
        size_t size = 1;
        for (int dim : shape) {
            size *= dim;
        }
        return size;
    }
};

using DataType = Tensor::DataType;

constexpr int kDataTypeRefOffset = 100;

inline bool IsRefType(DataType dtype) {
    return static_cast<int>(dtype) > kDataTypeRefOffset;
}

inline DataType MakeRefType(DataType dtype) {
    CHECK(!IsRefType(dtype));
    return static_cast<DataType>(static_cast<int>(dtype) + kDataTypeRefOffset);
}

inline DataType RemoveRefType(DataType dtype) {
    CHECK(IsRefType(dtype));
    return static_cast<DataType>(static_cast<int>(dtype) - kDataTypeRefOffset);
}

// Validates type T for whether it is a supported DataType.
template <class T>
struct IsValidDataType;

// DataTypeToEnum<T>::v() and DataTypeToEnum<T>::value are the DataType
// constants for T, e.g. DataTypeToEnum<float>::v() is DT_FLOAT.
template <class T>
struct DataTypeToEnum {
  static_assert(IsValidDataType<T>::value, "Specified Data Type not supported");
};  // Specializations below

// EnumToDataType<VALUE>::Type is the type for DataType constant VALUE, e.g.
// EnumToDataType<DT_FLOAT>::Type is float.
template <DataType VALUE>
struct EnumToDataType {};  // Specializations below

// Template specialization for both DataTypeToEnum and EnumToDataType.
#define MATCH_TYPE_AND_ENUM(TYPE, ENUM)                 \
  template <>                                           \
  struct DataTypeToEnum<TYPE> {                         \
    static DataType v() { return ENUM; }                \
    static DataType ref() { return MakeRefType(ENUM); } \
    static constexpr DataType value = ENUM;             \
  };                                                    \
  template <>                                           \
  struct IsValidDataType<TYPE> {                        \
    static constexpr bool value = true;                 \
  };                                                    \
  template <>                                           \
  struct EnumToDataType<ENUM> {                         \
    typedef TYPE Type;                                  \
  }

MATCH_TYPE_AND_ENUM(float, Tensor::DataType::Float);
MATCH_TYPE_AND_ENUM(int, Tensor::DataType::Int);
MATCH_TYPE_AND_ENUM(std::string, Tensor::DataType::String);
MATCH_TYPE_AND_ENUM(bool, Tensor::DataType::Bool);
MATCH_TYPE_AND_ENUM(double, Tensor::DataType::Double);
MATCH_TYPE_AND_ENUM(long, Tensor::DataType::Long);

} // namespace simpletf