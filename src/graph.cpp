#include "simpletf/graph.hpp"
#include "simpletf/base.h"

namespace simpletf {

Status Graph::AddNode(const NodeDef& node_def, Node** created_node)
{
    if (nodes_.find(node_def.name()) != nodes_.end()) {
        return Status(StatusCode::kAlreadyExists, 
                      "Node '" + node_def.name() + "' already exists in the graph.");
    }

    std::unique_ptr<Node> node = std::make_unique<Node>(
        node_def.name(),
        node_def.op(),
        node_def.inputs(),
        std::vector<std::string>()
    );

    for (const auto& attr : node_def.attr()) {
        node->SetAttr(attr.first, attr.second);
    }
    node->SetGraph(this);

    // set input nodes
    for (const auto& input_name : node_def.inputs()) {
        auto input_node = nodes_.find(input_name);
        if (input_node == nodes_.end()) {
            input_node->second->AddOutputNode(node_def.name(), node.get());
        } else {
            return Status(StatusCode::kNotFound, 
                          "Input node '" + input_name + "' not found in the graph.");
        }
    }

    // add node to graph
    nodes_[node_def.name()] = std::move(node);
    if (created_node) { 
        *created_node = nodes_[node_def.name()].get();
    }
    return absl::OkStatus();
}

Node::Node(const std::string& name, const std::string& op_type, const std::vector<std::string>& input_names, const std::vector<std::string>& output_names)
    : name_(name), op_type_(op_type), input_names_(input_names), output_names_(output_names)
{
}

const std::string& Node::name() const
{
    return name_;
}

const std::string& Node::op_type() const
{
    return op_type_;
}

const std::vector<std::string>& Node::input_names() const
{
    return input_names_;
}

const std::vector<std::string>& Node::output_names() const
{
    return output_names_;
}

int Node::num_inputs() const
{
    return input_names_.size();
}

int Node::num_outputs() const
{
    return output_names_.size();
}

DataType Node::input_type(int i) const
{
    return DataType::Float;
}

DataType Node::output_type(int i) const
{
    return DataType::Float;
}

Graph* Node::graph() const
{
    return graph_;
}

void Node::SetAttr(const std::string& name, const AttrValue& value)
{
    attrs_.insert({name, value});
}

void Node::AddOutputNode(const std::string& output_name, Node* node)
{
    output_nodes_[output_name] = node;
}

template <>
void SetAttrValue<int>(AttrValue& attr_value, const int& value)
{
    attr_value.type_ = AttrValue::Type::Int;
    attr_value.int_value_ = value;
}

template <>
void SetAttrValue<float>(AttrValue& attr_value, const float& value)
{
    attr_value.type_ = AttrValue::Type::Float;
    attr_value.float_value_ = value;
}

template <>
void SetAttrValue<std::string>(AttrValue& attr_value, const std::string& value)
{
    attr_value.type_ = AttrValue::Type::String;
    attr_value.string_value_ = value;
}

template <>
void SetAttrValue<Tensor>(AttrValue& attr_value, const Tensor& value)
{
    attr_value.type_ = AttrValue::Type::Tensor;
    attr_value.tensor_value_ = value;
}

template <>
void SetAttrValue<bool>(AttrValue& attr_value, const bool& value)
{
    attr_value.type_ = AttrValue::Type::Bool;
    attr_value.bool_value_ = value;
}


NodeBuilder::NodeBuilder(const std::string& op_name, const std::string& node_name)
    : op_name_(op_name), node_name_(node_name) {}

template <typename T>
NodeBuilder& NodeBuilder::Attr(const std::string& name, const T& value)
{
    SetAttrValue(attrs_[name], value);
    return *this;
}

Status NodeBuilder::Finalize(Graph* graph, Node** created_node) const
{
    NodeDef node_def;
    node_def.set_name(node_name_);
    node_def.set_op(op_name_);
    for (const auto& attr : attrs_) {
        node_def.mutable_attr()[attr.first] = attr.second;
    }

    Status status = graph->AddNode(node_def, created_node);
    if (!status.ok()) {
        return status;
    }
    return absl::OkStatus();
}


} // namespace simpletf