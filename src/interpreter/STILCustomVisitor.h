//
// Created by Gonzalo Solera on 04/08/2017.
//

#ifndef STIL_INTERPRETER_STILCUSTOMVISITOR_H
#define STIL_INTERPRETER_STILCUSTOMVISITOR_H

#include <STILBaseVisitor.h>

using namespace std;
using namespace antlr4;
using namespace parser;

class STILCustomVisitor : public STILBaseVisitor {

private:

    virtual antlrcpp::Any visitTerminal(tree::TerminalNode* node) override;

    virtual antlrcpp::Any visitFloat_t(STILParser::Float_tContext* ctx) override;

    virtual antlrcpp::Any visitInt_t(STILParser::Int_tContext* ctx) override;

    virtual antlrcpp::Any visitNum(STILParser::NumContext* ctx) override;

    virtual antlrcpp::Any visitPeriod(STILParser::PeriodContext* ctx) override;

    virtual antlrcpp::Any visitTime_expr(STILParser::Time_exprContext* ctx) override;

    virtual antlrcpp::Any visitWfc_seq(STILParser::Wfc_seqContext* ctx) override;

    virtual antlrcpp::Any visitContext(STILParser::ContextContext* ctx) override;

    virtual antlrcpp::Any visitAssigs(STILParser::AssigsContext* ctx) override;

    virtual antlrcpp::Any visitAssig_expr(STILParser::Assig_exprContext* ctx) override;

    virtual antlrcpp::Any visitRepeat(STILParser::RepeatContext* ctx) override;

};


#endif //STIL_INTERPRETER_STILCUSTOMVISITOR_H
