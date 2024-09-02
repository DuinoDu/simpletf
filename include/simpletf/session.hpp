#pragma once

#include "simpletf/scope.hpp"
#include "simpletf/op_core.hpp"
#include "simpletf/tensor.hpp"
#include <string>
#include <memory>

namespace simpletf {

class Env;

struct SessionOptions
{
   std::string target;
   Env* env;
   SessionOptions(const std::string& target) : target(target), env(nullptr) {}
};


class Session
{
public:
   Session(const Scope& scope); 
   Session(const Scope& scope, const std::string& target); 
   Session(const Scope& scope, const SessionOptions& options); 
   ~Session() {}

   Status Run(const std::vector<Output>& inputs, std::vector<Tensor>* outputs) const;
   // Status Run(const std::vector<std::pair<Output, Tensor>>& inputs, std::vector<Tensor>* outputs) const;

private:
   std::shared_ptr<Graph> graph_;

   // bool Run(const std::vector<std::pair<Output, Tensor>>& inputs, std::vector<Tensor>* outputs) const;
};

}