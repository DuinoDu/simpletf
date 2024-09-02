#include "simpletf/session.hpp"

namespace simpletf {

Session::Session(const Scope& scope) : Session(scope, "") {}

Session::Session(const Scope& scope, const std::string& target)
    : Session(scope, SessionOptions(target)) {}

Session::Session(const Scope& scope, const SessionOptions& options)
{
    graph_ = scope.graph_as_shared_ptr();
}

Status Session::Run(const std::vector<Output>& inputs, std::vector<Tensor>* outputs) const
{
    return absl::OkStatus();
}


} // namespace simpletf