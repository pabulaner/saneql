#include <string>

namespace adapter {

class Statement {
    public:
    virtual void write(std::string& result) = 0;
};

class Assign : public Statement {
    private:
    
};

class Return : public Statement {

};

class Lambda : public Statement {

};

} // namespace adapter