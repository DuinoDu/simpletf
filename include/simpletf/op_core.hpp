#pragma once

#include <string>
#include <vector>
#include "simpletf/graph.hpp"
#include "simpletf/tensor.hpp"
#include "absl/strings/str_cat.h"

namespace simpletf {

class Output;

class Operation {
public:
  Operation() : node_(nullptr) {}
  explicit Operation(Node* n);

  int num_inputs() const { return node_->num_inputs(); }
  DataType input_type(int o) const { return node_->input_type(o); }
  Output input(int i) const;

  int num_outputs() const { return node_->num_outputs(); }
  DataType output_type(int o) const { return node_->output_type(o); }
  Output output(int i) const;

  Node* node() const { return node_; }

  // uint64 hash(int index) const;

  bool operator==(const Operation& other) const { return node_ == other.node_; }

private:
  typedef std::vector<std::pair<Node*, int>> Inputs;
  static Inputs GetInputs(Node* node);

  Inputs inputs_;
  Node* node_;
};

class Output {
public:
    Output() = default;
    explicit Output(Node* n) : op_(n) {}
    Output(Node* n, int index) : op_(n), index_(index) {}
    Output(const Operation& op, int index) : op_(op), index_(index) {}

    Operation op() const { return op_; }
    Node* node() const { return op_.node(); }
    int index() const { return index_; }
    DataType type() const { return op_.output_type(index_); }
    std::string name() const { return absl::StrCat(node()->name(), ":", index()); }
    bool operator==(const Output& other) const { 
        return op_ == other.op_ && index_ == other.index_; 
    }

private:
    Operation op_ = Operation(nullptr);
    int index_ = 0;
};

class Input {
public:
    struct Initializer {
        Status status;
        Tensor tensor;

        // TODO
        template <typename T, typename = typename std::enable_if<
                              std::is_arithmetic<T>::value ||
                              std::is_convertible<T, std::string>::value>::type>
        Initializer(const T& v) {
            // typedef typename RealType<T>::type RealT;
            // Tensor t(DataTypeToEnum<RealT>::v(), TensorShape());

            // Tensor t(DataTypeToEnum<RealT>::v(), {1});
            // t.flat<RealT>().at(0) = RealT(v);
            Tensor t({1}, DataType::String);
            tensor = t;
        }

        Initializer(const Tensor& t) : tensor(t) {}  

        template <typename T, bool = std::is_convertible<T, std::string>::value>
        struct RealType {
            typedef T type;
        };

        template <typename T>
        struct RealType<T, false> {
            typedef T type;
        };
    };

    Input(const Output& o) : output_(o) {}

    Input(const Initializer& init) : tensor_(init.tensor), status_(init.status) {}

    template <typename T, typename = typename std::enable_if<
                              std::is_arithmetic<T>::value ||
                              std::is_convertible<T, std::string>::value>::type>
    Input(const T& v) : Input(Initializer(v)) {}

    Input(const Tensor& t) : tensor_(t), status_(absl::OkStatus()) {}

    Input(const std::string& node_name, int index, DataType data_type)
        : node_name_(node_name), index_(index), data_type_(data_type) {}

    Status status() const { return status_; }
    const Output& output() const { return output_; }
    const Tensor& tensor() const { return tensor_; }
    const std::string& node_name() const { return node_name_; }
    int index() const { return index_; }
    DataType data_type() const { return data_type_; }

private:
    Status status_;
    Output output_ = Output(Operation(nullptr), 0);
    Tensor tensor_;
    const std::string node_name_ = "";
    int index_ = 0;
    DataType data_type_ = DataType::Invalid;
};

typedef std::vector<Output> OutputList;

class InputList {
public:
    InputList(const OutputList& out) {
        for (const auto& x : out) {
            inputs_.emplace_back(x);
        }
    }
private:
    std::vector<Input> inputs_;
};

}