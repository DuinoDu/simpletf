#pragma once

namespace simpletf {

class GraphVersions;
class OpRegistry;

class ShapeRefiner
{
public:
    ShapeRefiner(const GraphVersions& versions, const OpRegistry* op_registry)
     : versions_(versions), op_registry_(op_registry) {}
    ~ShapeRefiner(){};

    // Perform shape inference and runs 'node's shape function,
    // and storing its shape outputs in the node's output tensors.
    Status AddNode(const Node* node) {};

private:
    GraphVersions versions_;
    const OpRegistry* op_registry_;
};

}   