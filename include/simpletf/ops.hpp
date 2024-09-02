#pragma once

#include <string>
#include <vector>
#include "simpletf/scope.hpp"
#include "simpletf/op_core.hpp"

namespace simpletf {
namespace ops {

Output Const(Scope& scope, const Input::Initializer& val);

Output StringJoin(Scope& scope, const std::vector<Output>& inputs);


} // namespace ops
} // namespace simpletf