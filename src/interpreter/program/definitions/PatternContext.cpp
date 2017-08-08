//
// Created by Gonzalo Solera on 07/08/2017.
//

#include "PatternBurst.h"
#include "PatternContext.h"

PatternBurst::PatternBurst(string id, STILParser::Pattern_listContext* ast, PatternBurst::PatternContext& context) : Identifiable(id) {
    this->ast = ast;
    this->context = context;
}