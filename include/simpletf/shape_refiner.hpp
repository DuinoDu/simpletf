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

private:
    GraphVersions versions_;
    const OpRegistry* op_registry_;
};

}   