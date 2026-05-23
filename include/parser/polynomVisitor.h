
// Generated from polynom.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "polynomParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by polynomParser.
 */
class  polynomVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by polynomParser.
   */
    virtual std::any visitAddFirstMonom(polynomParser::AddFirstMonomContext *context) = 0;

    virtual std::any visitAddMonom(polynomParser::AddMonomContext *context) = 0;

    virtual std::any visitNewMonom(polynomParser::NewMonomContext *context) = 0;

    virtual std::any visitNewKoef(polynomParser::NewKoefContext *context) = 0;

    virtual std::any visitNewX(polynomParser::NewXContext *context) = 0;

    virtual std::any visitNewY(polynomParser::NewYContext *context) = 0;

    virtual std::any visitNewZ(polynomParser::NewZContext *context) = 0;

    virtual std::any visitNewDeg(polynomParser::NewDegContext *context) = 0;


};

