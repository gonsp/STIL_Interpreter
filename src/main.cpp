#include <iostream>

#include "antlr4-runtime.h"
#include "parser/STILLexer.h"
#include "parser/STILParser.h"

using namespace parser;
using namespace antlr4;
using namespace std;

int main(int , const char **) {
    ANTLRInputStream input(u8"hello");
    STILLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
    for (auto token : tokens.getTokens()) {
        std::cout << token->toString() << std::endl;
    }

    STILParser parser(&tokens);
    tree::ParseTree *tree = parser.hello();

    std::cout << tree->toStringTree(&parser) << std::endl;

    return 0;
}