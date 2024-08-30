#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace simpletf {

class Node
{
public:
    Node(const std::string& name, const std::string& op_type, const std::vector<std::string>& input_names, const std::vector<std::string>& output_names);
    ~Node();

    const std::string& name() const;
    const std::string& op_type() const;
    const std::vector<std::string>& input_names() const;
    const std::vector<std::string>& output_names() const;

private:
    std::string name_;
    std::string op_type_;
    std::vector<std::string> input_names_;
    std::vector<std::string> output_names_;
};

} // namespace simpletf
