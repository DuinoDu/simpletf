#pragma once

#include "simpletf/scope.hpp"
#include <string>
#include <vector>

namespace simpletf {

namespace ops {



class Const
{
private:
    /* data */
public:
    Const(const Scope& scope, const std::string& value);
    ~Const() {};
};


class StringJoin
{
private:
    /* data */
public:
    StringJoin(const Scope& scope, const std::vector<std::string>& inputs);
    ~StringJoin() {};
};

}
}