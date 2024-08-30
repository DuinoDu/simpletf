#include <mutex>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

#include "simpletf/base.h"

namespace simpletf {

struct OpDef {
    explicit OpDef(const std::string& name) : name(name) {}
    std::string name;
};

class OpRegistry {
public:
    static OpRegistry* Global() {
        static OpRegistry* global_registry = new OpRegistry();
        return global_registry;
    }

    void RegisterOp(const std::string& name) {
        std::lock_guard<std::mutex> lock(mu_);
        if (ops_.find(name) == ops_.end()) {
            ops_[name] = std::make_shared<OpDef>(name);
            LOG(INFO) << "Registered op: " << name;
        }
    }

    // 查找操作的方法
    std::shared_ptr<OpDef> FindOp(const std::string& name) {
        std::lock_guard<std::mutex> lock(mu_);
        auto it = ops_.find(name);
        if (it != ops_.end()) {
            return it->second;
        }
        return nullptr;
    }

private:
    // 私有构造函数，确保只能通过 Global() 获取实例
    OpRegistry() = default;

    // 禁用拷贝构造和赋值操作
    OpRegistry(const OpRegistry&) = delete;
    OpRegistry& operator=(const OpRegistry&) = delete;

    // 互斥锁保护操作注册表
    std::mutex mu_;
    // 存储操作定义的哈希表
    std::unordered_map<std::string, std::shared_ptr<OpDef>> ops_;
};

}   // namespace simpletf
