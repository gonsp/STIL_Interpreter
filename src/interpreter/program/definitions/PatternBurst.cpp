//
// Created by Gonzalo Solera on 04/08/2017.
//

#include "PatternBurst.h"

PatternBurst::PatternBurst(string id, STILParser::Pattern_listContext* ast, PatternContext& context) : Identifiable(id) {
    this->ast = ast;
    this->context = context;
}