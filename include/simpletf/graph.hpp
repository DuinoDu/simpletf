#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "simpletf/tensor.hpp"
#include "simpletf/op_core.hpp"

namespace simpletf {

class OpRegistry;
class NodeDef;
class Graph;

/* 
   AttrValue is used to store attribute values in a node.
   It has a type, and a value of the corresponding type.
*/
class AttrValue
{
public:
   enum class Type {
      None,
      Int,
      Float,
      String,
      Tensor,
      Bool,
      DataType,
   };

   AttrValue() : type_(Type::None) {}
   Type type() const { return type_; }
   int int_value() const { return int_value_; }
   float float_value() const { return float_value_; }
   std::string string_value() const { return string_value_; }
   Tensor tensor_value() const { return tensor_value_; }
   bool bool_value() const { return bool_value_; }
   DataType dtype_value() const { return dtype_value_; }

private:
   Type type_;
   int int_value_;
   float float_value_;
   std::string string_value_;
   Tensor tensor_value_;
   bool bool_value_;
   DataType dtype_value_;

   template <typename T>
   friend void SetAttrValue(AttrValue& attr_value, const T& value);
};

template <typename T>
void SetAttrValue(AttrValue& attr_value, const T& value);

/* 
   Node is a basic unit of computation in a graph.
   It has a name, an operation type, and a list of input and output names.
   It also has a graph pointer to the graph it belongs to.
*/
class Node
{
public:
    Node(const std::string& name, const std::string& op_type, const std::vector<std::string>& input_names, const std::vector<std::string>& output_names);
    ~Node() {};

    const std::string& name() const;
    const std::string& op_type() const;

    const std::vector<std::string>& input_names() const;
    const std::vector<std::string>& output_names() const;

    std::vector<Node*>& inputs();
    const std::unordered_map<std::string, Node*>& input_nodes() const;
    const std::unordered_map<std::string, Node*>& output_nodes() const;

    int num_inputs() const;
    int num_outputs() const;

    DataType input_type(int i) const;
    DataType output_type(int i) const;

    Graph* graph() const;
    void SetGraph(Graph* graph) { graph_ = graph; }

    void SetAttr(const std::string& name, const AttrValue& value);

    void AddOutputNode(const std::string& output_name, Node* node);

private:
    std::string name_;
    std::string op_type_;
    std::vector<std::string> input_names_;
    std::vector<std::string> output_names_;
    std::unordered_map<std::string, Node*> input_nodes_;
    std::unordered_map<std::string, Node*> output_nodes_;
    Graph* graph_;
    std::unordered_map<std::string, AttrValue> attrs_;
};

/* 
   NodeDef is used to store the definition of a node.
   It has a name, an operation type, and a list of input names.
   It has a map of attribute names to attribute values.
*/
class NodeDef {
public:
    NodeDef() = default;

    // Setters
    void set_name(const std::string& name) { name_ = name; }
    void set_op(const std::string& op) { op_ = op; }
    void add_input(const std::string& input) { inputs_.push_back(input); }

    // Getters
    const std::string& name() const { return name_; }
    const std::string& op() const { return op_; }
    const std::vector<std::string>& inputs() const { return inputs_; }

    // Attribute handling
    std::unordered_map<std::string, AttrValue>& mutable_attr() {
        return attr_;
    }

    const std::unordered_map<std::string, AttrValue>& attr() const {
        return attr_;
    }

private:
    std::string name_;
    std::string op_;
    std::vector<std::string> inputs_;
    std::unordered_map<std::string, AttrValue> attr_;
};

/* 
   NodeBuilder is used to build a node in a graph.
   It has an operation name, a node name, and a list of attributes.
   It has a method to set attribute values.
   It has a method to finalize the node and add it to the graph.
*/
class NodeBuilder
{
public:

    NodeBuilder(const std::string& op_name, const std::string& node_name);
    ~NodeBuilder() {};

    NodeBuilder& Input(const std::vector<Output>& inputs);

    template <typename T>
    NodeBuilder& Attr(const std::string& name, const T& value) {
        SetAttrValue(attrs_[name], value);
        return *this;
    }

    Status Finalize(Graph* graph, Node** created_node) const;

private:
    std::string op_name_;
    std::string node_name_;
    std::unordered_map<std::string, AttrValue> attrs_;
    std::vector<Node> inputs_;
};

/* 
   GraphVersions is used to store the versions of a graph.
   It has a producer version, a minimum consumer version, and a list of bad consumers.
*/
class GraphVersions {
public:
    GraphVersions(int producer, int min_consumer, const std::vector<int>& bad_consumers)
        : producer_(producer), min_consumer_(min_consumer), bad_consumers_(bad_consumers) {}

    int producer() const { return producer_; }
    int min_consumer() const { return min_consumer_; }
    const std::vector<int>& bad_consumers() const { return bad_consumers_; }

private:
    int producer_;
    int min_consumer_;
    std::vector<int> bad_consumers_;
};

typedef std::unordered_map<std::string, std::unique_ptr<Node>> NodeMap;

/* 
   Graph is a collection of nodes and edges.
   It is used to represent a computation graph.
*/
class Graph
{
   public:
      Graph(const OpRegistry* op_registry) : op_registry_(op_registry), versions_(0, 0, {}) {};
      ~Graph() {};

      GraphVersions versions() const { return versions_; }

      const OpRegistry* op_registry() const { return op_registry_; }

      Node* GetNode(const std::string& name) const {
         auto it = nodes_.find(name);
         if (it == nodes_.end()) {
            return nullptr;
         }
         return it->second.get();
      }

      Status AddNode(const NodeDef& node_def, Node** created_node);
   
   private:
      GraphVersions versions_;
      const OpRegistry* op_registry_;
      NodeMap nodes_;
};

} // namespace simpletf