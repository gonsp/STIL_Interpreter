#include <iostream>

#include "antlr4-runtime.h"
#include "parser/STILLexer.h"
#include "parser/STILParser.h"

using namespace parser;
using namespace antlr4;
using namespace std;

int main(int num_args, char* args[]) {

    if(num_args > 1) {
        freopen(args[1], "r", stdin);
    }

    ANTLRInputStream input(cin);
    STILLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    STILParser parser(&tokens);
    tree::ParseTree *tree = parser.expr();

    cout << tree->toStringTree(&parser) << endl;

    return 0;
}