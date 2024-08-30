#pragma once
#include <vector>

namespace simpletf {

class OpRegistry;

class GraphVersions {
public:
    GraphVersions(int producer, int min_consumer, const std::vector<int>& bad_consumers)
        : producer_(producer), min_consumer_(min_consumer), bad_consumers_(bad_consumers) {}

    int producer() const { return producer_; }
    int min_consumer() const { return min_consumer_; }
    const std::vector<int>& bad_consumers() const { return bad_consumers_; }

private:
    int producer_;
    int min_consumer_;
    std::vector<int> bad_consumers_;
};

class Graph
{
   public:
      Graph(const OpRegistry* op_registry) : op_registry_(op_registry), versions_(0, 0, {}) {};
      ~Graph() {};

      GraphVersions versions() const { return versions_; }

      const OpRegistry* op_registry() const { return op_registry_; }
   
   private:
      GraphVersions versions_;
      const OpRegistry* op_registry_;
};

}