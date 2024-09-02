#include "simpletf/ops.hpp"
#include "simpletf/tensor.hpp"
#include "simpletf/graph.hpp"

namespace simpletf {
namespace ops {

Output Const(Scope& scope, const Input::Initializer& val)
{
    if (!val.status.ok()) {
        scope.UpdateStatus(val.status);
        return Output();
    }
    Node* ret;
    Graph* g = scope.graph();
    const std::string unique_name = scope.GetUniqueNameForOp("Const");

    auto builder = NodeBuilder(unique_name, "Const")
                     .Attr("value", val.tensor)
                     .Attr("dtype", val.tensor.dtype());
    scope.UpdateBuilder(&builder);
    scope.UpdateStatus(builder.Finalize(g, &ret));
    if (!scope.status().ok()) return Output();

    scope.UpdateStatus(scope.DoShapeInference(ret));
    if (!scope.status().ok()) return Output();

    return Output(ret);
}

Output StringJoin(Scope& scope, const std::vector<Output>& inputs)
{
    Node* ret;
    Graph* g = scope.graph();
    const std::string unique_name = scope.GetUniqueNameForOp("StringJoin");

    auto builder = NodeBuilder(unique_name, "StringJoin")
                     .Input(inputs)
                     .Attr("separator", " ");
    scope.UpdateBuilder(&builder);
    scope.UpdateStatus(builder.Finalize(g, &ret));
    if (!scope.status().ok()) return Output();

    scope.UpdateStatus(scope.DoShapeInference(ret));
    if (!scope.status().ok()) return Output();

    return Output(ret);
}


}   // namespace ops
}   // namespace simpletf