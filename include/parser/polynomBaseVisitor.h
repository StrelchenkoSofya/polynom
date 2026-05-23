
// Generated from polynom.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "polynomVisitor.h"


/**
 * This class provides an empty implementation of polynomVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  polynomBaseVisitor : public polynomVisitor {
public:

  virtual std::any visitAddFirstMonom(polynomParser::AddFirstMonomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddMonom(polynomParser::AddMonomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewMonom(polynomParser::NewMonomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewKoef(polynomParser::NewKoefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewX(polynomParser::NewXContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewY(polynomParser::NewYContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewZ(polynomParser::NewZContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNewDeg(polynomParser::NewDegContext *ctx) override {
    return visitChildren(ctx);
  }


};

