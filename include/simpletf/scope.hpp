#pragma once
#include <memory>

namespace simpletf {

class Graph;

class Scope
{
public:
    Scope(/* args */);
    ~Scope() {};

    static Scope NewRootScope();

    Graph* graph();
    std::shared_ptr<Graph> graph_as_shared_ptr() const;

private:
    std::shared_ptr<Graph> graph_;
};

}
