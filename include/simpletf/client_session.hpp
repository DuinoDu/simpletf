#pragma once

#include "simpletf/scope.hpp"
#include <string>

namespace simpletf {

class ClientSession
{
   ClientSession(const Scope& scope); 
   ClientSession(const Scope& scope, const std::string& target); 
   ~ClientSession();

   // bool Run(const std::vector<std::pair<Output, Tensor>>& inputs, std::vector<Tensor>* outputs) const;
};

}