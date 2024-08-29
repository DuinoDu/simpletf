#include "simpletf/scope.hpp"

namespace simpletf {

Scope::Scope(/* args */)
{
}

Scope::~Scope()
{
}

Scope Scope::NewRootScope()
{
    return Scope();
}
    
}