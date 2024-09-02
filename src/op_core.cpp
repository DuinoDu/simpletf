#include "simpletf/op_core.hpp"
#include "simpletf/base.h"

namespace simpletf {

Operation::Operation(Node* node) : node_(node), inputs_(GetInputs(node)) {}

Output Operation::input(int i) const
{
    CHECK(node_ != nullptr);
    CHECK(i >= 0 && i < num_inputs());
    return Output(inputs_[i].first, inputs_[i].second);
}

Output Operation::output(int i) const
{
    CHECK(node_ != nullptr);
    CHECK(i >= 0 && i < num_outputs());
    return Output(node_, i);
}

Operation::Inputs Operation::GetInputs(Node* node)
{
    Inputs inputs;
    if (node != nullptr) {
        for (const auto& input_name : node->input_names()) {
            inputs.push_back({node->graph()->GetNode(input_name), 0});
        }
    }
    return inputs;
}





} // namespace simpletf
