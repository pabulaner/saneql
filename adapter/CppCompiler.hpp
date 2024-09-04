#include <vector>
#include <string>

namespace adapter {

class CppWriter;

class CppCompiler {
    enum Flag : uint8_t {
        OptimizeSelects = 0x1,
        OptimizeScans = 0x2,
        OptimizeJoins = 0x4,
    };

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
    CppCompiler(unsigned count, char** files, bool addDefaultOutput = true);

    void addOutput(const std::string& name, uint8_t flags);

    void compile(const std::string& file) const;

private:
    void writeOutput(CppWriter& writer, const Output& output) const;
};

}