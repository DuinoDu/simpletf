#include "simpletf/simpletf.hpp"
#include "catch2/catch.hpp"
#include <string>

using namespace simpletf;
using namespace simpletf::ops;


TEST_CASE( "hello_world", "[basic]" ){

  auto scope = Scope::NewRootScope();

  {
    auto hello = Const(scope, std::string("hello"));
    Session session(scope);
    std::vector<Tensor> outputs;
    CHECK_OK(session.Run({hello}, &outputs));
    // REQUIRE(outputs.size() == 1);
    // REQUIRE(outputs[0].flat<std::string>() == "hello");
  }

  {
    auto hello = Const(scope, std::string("hello"));
    auto space = Const(scope, std::string(" "));
    auto world = Const(scope, std::string("world !"));
  
    // auto joinOp = StringJoin(scope, {hello, space, world});

    Session session(scope);
    // std::vector<Tensor> outputs;
    // TF_CHECK_OK(session.Run({joinOp}, &outputs));

    // REQUIRE(outputs[0].flat<std::string>() == "hello world !");
    // REQUIRE(outputs[0].DebugString() == "hello world !");

  }
}

TEST_CASE( "basic_opertion", "[basic]" ){
  REQUIRE(true);

  // auto scope = Scope::NewRootScope();
  // auto a = Const(scope, 2);
  // auto b = Const(scope, 3);
  // auto c = Add(scope, a, b);

  // Session session(scope);
  // std::vector<Tensor> outputs;
  // TF_CHECK_OK(session.Run({c}, &outputs));
  // REQUIRE(outputs[0].flat<int>() == 5);
}

TEST_CASE( "basic_tensor", "[tensor]" ){
  REQUIRE(true);

  auto scope = Scope::NewRootScope();

  // {
  //   auto a = Placeholder(scope, DT_INT32);
  //   auto b = Placeholder(scope, DT_INT32);
  //   auto c = Add(scope, a, b);

  //   Session session(scope);
  //   std::vector<Tensor> outputs;
  //   TF_CHECK_OK(session.Run({{{a, 2}, {b, 3}}}, {c}, &outputs));
  //   REQUIRE(outputs[0].flat<int>() == 5);
  // }

  // {
  //   auto aScalar = Input(2);
  //   REQUIRE(aScalar.tensor().shape().dims() == 0);

  //   auto aVector = Input({2, 3});
  //   REQUIRE(aVector.tensor().shape().dims() == 1);

  //   // A tensor of Rank 2 is called a matrix
  //   auto aMatrix = Input({{2, 3}, {6, 5}});
  //   REQUIRE(aMatrix.tensor().shape().dims() == 2);
  // }

  // {
  //   auto c1 = Const(scope, 10, {2, 2});

  //   // [1 1] * [41]
  //   //         [1]
  //   auto x = MatMul(scope, {{1, 1}}, {{41}, {1}});

  //   Session session(scope);
  //   std::vector<Tensor> outputs;

  //   auto status = session.Run({x}, &outputs);
  //   REQUIRE(status.ok());
  //   REQUIRE(outputs[0].flat<int>() == 42);

  //   auto y = Add(scope, {1, 2, 3, 4}, 10);
  //   status = session.Run({y}, &outputs);
  //   REQUIRE(status.ok());
  //   REQUIRE(outputs[0].flat<int>() == { 11, 12, 13, 14});
  // }

}

TEST_CASE( "basic_graph", "[graph]" ){
  REQUIRE(true);

  auto scope = Scope::NewRootScope();

  // auto a = Placeholder(scope.WithOpName("A"), DT_INT32);
  // auto b = Placeholder(scope.WithOpName("B"), DT_INT32);
  // auto add = Add(scope.WithOpName("Add"), a, b);

  // GraphDef graph;
  // scope.ToGraphDef(&graph);

  // // Or we can create graph from file
  // // ...

  // std::unique_ptr<Session> session(NewSession(SessionOptions()));
  // session->Create(graph);

  // auto inputA = Tensor(DT_INT32, TensorShape({}));
  // auto inputB = Tensor(DT_INT32, TensorShape({}));
  // inputA.scalar<int>()() = 2;
  // inputB.scalar<int>()() = 3;
  // std::vector<std::pair<string, Tensor>> inputs = {
  //   {"a", inputA},
  //   {"b", inputB}
  // };
  // std::vector<Tensor> outputs;
  // auto status = session.Run(inputs, {"Add"}, &outputs);
  // REQUIRE(status.ok());
  // REQUIRE(outputs.size() == 1);
  // REQUIRE(outputs[0].flat<int>() == 5);

}

TEST_CASE( "graph_registry", "[graph]" ){
  // 获取全局操作注册表实例
  OpRegistry* registry = OpRegistry::Global();
 
  // 注册操作
  registry->RegisterOp("Add");
  registry->RegisterOp("Multiply");
 
  // 查找操作
  auto op = registry->FindOp("Add");
  REQUIRE(op != nullptr);
  REQUIRE(op->name == "Add");
}
