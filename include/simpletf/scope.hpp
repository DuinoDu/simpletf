#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "simpletf/base.h"

namespace simpletf {

class Node;
class Graph;
class ShapeRefiner;
class NodeBuilder;

using NameMap = std::unordered_map<std::string, Node*>;

class Scope
{
public:
    static Scope NewRootScope();

    Scope(Graph* graph, Status* status, NameMap* name_map, ShapeRefiner* shape_refiner);
    ~Scope() {};

    Graph* graph();

    std::shared_ptr<Graph> graph_as_shared_ptr() const;

    Status status() const;
    
    NameMap* name_map();

    ShapeRefiner* shape_refiner();

    void UpdateStatus(const Status& status);

    std::string GetUniqueNameForOp(const std::string& name) const;

    void UpdateBuilder(NodeBuilder* builder) {}

    /* 
    * Do shape inference for the node. It will update the node's output shapes.
    * @param node The node to do shape inference for.
    * @return The status of the shape inference.
    */
    Status DoShapeInference(Node* node);

private:
    std::shared_ptr<Graph> graph_;
    Status* status_;
    NameMap* name_map_;
    ShapeRefiner* shape_refiner_;
};

}
