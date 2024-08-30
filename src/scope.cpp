#include "simpletf/scope.hpp"
#include "simpletf/graph.hpp"

namespace simpletf {

Scope::Scope(/* args */)
{
}

Scope Scope::NewRootScope()
{
    Graph* graph = new Graph(OpRegistry::Global());
    ShapeRefiner* shape_refiner = new ShapeRefiner(graph->versions(), graph->op_registry());
    return Scope(graph, new Status(absl::OkStatus()), new NameMap(), shape_refiner);
}

Graph* Scope::graph()
{
    return graph_.get();
}

std::shared_ptr<Graph> Scope::graph_as_shared_ptr() const
{
    return graph_;
}

Status Scope::status() const
{
    return status_;
}



}