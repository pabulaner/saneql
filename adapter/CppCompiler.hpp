#include <vector>
#include <string>

namespace adapter {

class CppWriter;

class CppCompiler {
public:
    enum Flag : uint8_t {
        None = 0x0,
        OptimizeSelects = 0x1,
        OptimizeScans = 0x2,
        OptimizeJoins = 0x4,
    };

private:
    struct Input {
        std::string name;
        std::string content;
    };

    struct Output {
        std::string name;
        uint8_t flags;
    };

    std::vector<Input> inputs;

    std::vector<Output> outputs;

public:
    CppCompiler(unsigned count, char** files, bool addDefaultOutput = false);

    void addOutput(const std::string& name, uint8_t flags);

    void compile(const std::string& file) const;

private:
    void writeOutput(CppWriter& writer, const Output& output) const;
};

}