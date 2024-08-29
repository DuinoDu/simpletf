#include "simpletf/scope.hpp"

namespace simpletf {

Scope::Scope(/* args */)
{
}

Scope Scope::NewRootScope()
{
    return Scope();
}

Graph* Scope::graph()
{
    return graph_.get();
}

std::shared_ptr<Graph> Scope::graph_as_shared_ptr() const
{
    return graph_;
}





}