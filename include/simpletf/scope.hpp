#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "simpletf/base.h"

namespace simpletf {

class Node;
class Graph;

using NameMap = std::unordered_map<std::string, Node*>;

class Scope
{
public:
    Scope(/* args */);
    ~Scope() {};

    static Scope NewRootScope();

    Graph* graph();
    std::shared_ptr<Graph> graph_as_shared_ptr() const;

    Status status() const;

private:
    std::shared_ptr<Graph> graph_;

    Status status_;
};

}
