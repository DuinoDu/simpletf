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

void Scope::UpdateStatus(const Status& status)
{
    *status_ = status;
}

std::string Scope::GetUniqueNameForOp(const std::string& name) const
{
    std::string unique_name = name;
    int counter = 0;
    while (name_map_->count(unique_name)) {
        unique_name = name + "/" + std::to_string(counter++);
    }
    name_map_->insert({unique_name, nullptr});
    return unique_name;
}

Status Scope::DoShapeInference(Node* node)
{  
    if (node == nullptr) {
        return Status(StatusCode::kInvalidArgument, "Node is null");
    }
    const std::vector<Node*> inputs = node->inputs();
    if (inputs.empty()) {
        return Status(StatusCode::kInvalidArgument, "Node has not input");
    }

    ShapeRefiner* shape_refiner = this->shape_refiner_;
    if (shape_refiner == nullptr) {
        return Status(StatusCode::kInternal, "Shape refiner is null");
    }

    for (Node* input : inputs) {
        Status status = shape_refiner->AddNode(input);
        if (!status.ok()) {
            return status;
        }
    }



    return shape_refiner_->AddNode(node);
}

} // namespace simpletf