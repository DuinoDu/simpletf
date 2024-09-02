#include "simpletf/tensor.hpp"
#include "catch2/catch.hpp"

using namespace simpletf;


TEST_CASE( "tensor_creation", "[tensor]" ){
    Tensor t1({2, 3}, Tensor::DataType::Float);
    REQUIRE(t1.shape() == std::vector<int>({2, 3}));
    REQUIRE(t1.dtype() == Tensor::DataType::Float);

    Tensor t2({2, 3}, Tensor::DataType::Int);
    REQUIRE(t2.shape() == std::vector<int>({2, 3}));
    REQUIRE(t2.dtype() == Tensor::DataType::Int);

    Tensor t3({2, 3}, Tensor::DataType::String);
    REQUIRE(t3.shape() == std::vector<int>({2, 3}));
    REQUIRE(t3.dtype() == Tensor::DataType::String);

    Tensor t4({2, 3}, Tensor::DataType::Bool);
    REQUIRE(t4.shape() == std::vector<int>({2, 3}));
    REQUIRE(t4.dtype() == Tensor::DataType::Bool);

    Tensor t5({2, 3}, Tensor::DataType::Double);
    REQUIRE(t5.shape() == std::vector<int>({2, 3}));
    REQUIRE(t5.dtype() == Tensor::DataType::Double);

    Tensor t6({2, 3}, Tensor::DataType::Long);
    REQUIRE(t6.shape() == std::vector<int>({2, 3}));
    REQUIRE(t6.dtype() == Tensor::DataType::Long);
}

TEST_CASE( "tensor_access", "[tensor]" ){
    Tensor t1({2, 3}, Tensor::DataType::Float);
    t1.at<float>(0) = 1.0f;
    t1.at<float>(1) = 2.0f;
    t1.at<float>(2) = 3.0f;
    t1.at<float>(3) = 4.0f;
    t1.at<float>(4) = 5.0f;
    t1.at<float>(5) = 6.0f;
    t1.Print();
    REQUIRE(t1.at<float>(0) == 1.0f);
    REQUIRE(t1.at<float>(1) == 2.0f);
    REQUIRE(t1.at<float>(2) == 3.0f);
    REQUIRE(t1.at<float>(3) == 4.0f);
    REQUIRE(t1.at<float>(4) == 5.0f);
    REQUIRE(t1.at<float>(5) == 6.0f);

    Tensor t2({2, 3}, Tensor::DataType::String);
    t2.at<std::string>(0) = "hello";
    t2.at<std::string>(1) = "world";
    t2.at<std::string>(2) = "this";
    t2.at<std::string>(3) = "is";
    t2.at<std::string>(4) = "a";
    t2.at<std::string>(5) = "test";
    t2.Print();
    REQUIRE(t2.at<std::string>(0) == "hello");
    REQUIRE(t2.at<std::string>(1) == "world");
    REQUIRE(t2.at<std::string>(2) == "this");
    REQUIRE(t2.at<std::string>(3) == "is");
    REQUIRE(t2.at<std::string>(4) == "a");
    REQUIRE(t2.at<std::string>(5) == "test");

    Tensor t3;
    t3 = t2;
    REQUIRE(t3.at<std::string>(0) == "hello");

    Tensor t4 = t2;
    REQUIRE(t4.at<std::string>(0) == "hello");
 }