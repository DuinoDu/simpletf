#pragma once

#include "simpletf/scope.hpp"
#include "simpletf/op_core.hpp"
#include <string>
#include <vector>

namespace simpletf {

namespace ops {

Output Const(const Scope& scope, const Input::Initializer& val);

// Output StringJoin(const Scope& scope, const std::vector<Output>& inputs);


} // namespace ops
} // namespace simpletf