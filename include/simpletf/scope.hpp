#pragma once

namespace simpletf {

class Scope
{
private:
    /* data */
public:
    Scope(/* args */);
    ~Scope();

    static Scope NewRootScope();
};

}
