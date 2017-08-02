#include "parser.hpp"

#include "antlr4-runtime.h"
#include "DMCQLLexer.h"
#include "DMCQLParser.h"
#include "DMCQLBaseListener.h"

namespace dmc12 {
namespace dmcql {

class BasicListener: public DMCQLBaseListener {
public: 
    void exitStart(DMCQLParser::StartContext *ctx) {
        std::cout << "done\n";
    }
};

void parse(std::istream &input) {
    antlr4::ANTLRInputStream antlr_input(input);
    DMCQLLexer lexer(&antlr_input);
    antlr4::CommonTokenStream tokens(&lexer);
    DMCQLParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.start();
    BasicListener listener;
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
}

}
}

#include <string>
#include <sstream>

int main(void) {
    std::string s = "0";
    std::stringstream ss(s);

    dmc12::dmcql::parse(ss);
    return 0;
}