#include "simpletf/client_session.hpp"

namespace simpletf {

ClientSession::ClientSession(const Scope& scope) : ClientSession(scope, "") {}

ClientSession::ClientSession(const Scope& scope, const std::string& target)
    : ClientSession(scope, SessionOptions(target)) {}

ClientSession::ClientSession(const Scope& scope, const SessionOptions& options)
{
    session_ = std::shared_ptr<Session>(new Session());
    graph_ = scope.graph_as_shared_ptr();
}



}