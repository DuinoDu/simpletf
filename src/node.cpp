#include "simpletf/node.hpp"

namespace simpletf {

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

} // namespace simpletf