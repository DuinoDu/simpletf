#include "simpletf/scope.hpp"
#include "simpletf/op_registry.hpp"
#include "simpletf/graph.hpp"
#include "simpletf/shape_refiner.hpp"

namespace simpletf {

Scope::Scope(Graph* graph, Status* status, NameMap* name_map, ShapeRefiner* shape_refiner)
    : graph_(graph), status_(status), name_map_(name_map), shape_refiner_(shape_refiner)
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
    return *status_;
}



}