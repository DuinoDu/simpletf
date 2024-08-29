#include "simpletf/simpletf.hpp"
#include "catch2/catch.hpp"
#include <string>

using namespace simpletf;
using namespace simpletf::ops;

TEST_CASE( "add_one", "[adder]" ){
  REQUIRE(add_one(0) == 1);
  REQUIRE(add_one(123) == 124);
  REQUIRE(add_one(-1) == 0);
}

TEST_CASE( "hello_world", "[simple]" ){

  auto scope = Scope::NewRootScope();

  // auto hello = Const(scope, std::string("hello"));
  // auto space = Const(scope, std::string(" "));
  // auto world = Const(scope, std::string("world !"));
  
  // auto joinOp = StringJoin(scope, {hello, space, world});

  ClientSession session(scope);
  // std::vector<Tensor> outputs;
  // TF_CHECK_OK(session.Run({joinOp}, &outputs));

  // REQUIRE(outputs[0].flat<std::string>() == "hello world !");
  // REQUIRE(outputs[0].DebugString() == "hello world !");

}

TEST_CASE( "basic_opertion", "[simple]" ){
  REQUIRE(true);
}

TEST_CASE( "basic_tensor", "[simple]" ){
  REQUIRE(true);
}