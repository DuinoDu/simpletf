#pragma once

#include "simpletf/scope.hpp"
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
      Session() {};
      ~Session() {}
};

class ClientSession
{

public:
   ClientSession(const Scope& scope); 
   ClientSession(const Scope& scope, const std::string& target); 
   ClientSession(const Scope& scope, const SessionOptions& options); 
   ~ClientSession() {}

private:
   std::shared_ptr<Session> session_;
   std::shared_ptr<Graph> graph_;

   // bool Run(const std::vector<std::pair<Output, Tensor>>& inputs, std::vector<Tensor>* outputs) const;
};

}