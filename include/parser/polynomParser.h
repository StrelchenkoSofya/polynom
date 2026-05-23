
// Generated from polynom.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  polynomParser : public antlr4::Parser {
public:
  enum {
    KF = 1, X = 2, Y = 3, Z = 4, DEG = 5, DS = 6, WS = 7, ADD = 8, SUB = 9
  };

  enum {
    RulePolynom = 0, RuleMonom = 1, RuleKoef = 2, RuleVarx = 3, RuleVary = 4, 
    RuleVarz = 5, RuleDegree = 6
  };

  explicit polynomParser(antlr4::TokenStream *input);

  polynomParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~polynomParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class PolynomContext;
  class MonomContext;
  class KoefContext;
  class VarxContext;
  class VaryContext;
  class VarzContext;
  class DegreeContext; 

  class  PolynomContext : public antlr4::ParserRuleContext {
  public:
    PolynomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PolynomContext() = default;
    void copyFrom(PolynomContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AddFirstMonomContext : public PolynomContext {
  public:
    AddFirstMonomContext(PolynomContext *ctx);

    antlr4::Token *op = nullptr;
    MonomContext *monom();
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddMonomContext : public PolynomContext {
  public:
    AddMonomContext(PolynomContext *ctx);

    antlr4::Token *op = nullptr;
    PolynomContext *polynom();
    MonomContext *monom();
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PolynomContext* polynom();
  PolynomContext* polynom(int precedence);
  class  MonomContext : public antlr4::ParserRuleContext {
  public:
    MonomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MonomContext() = default;
    void copyFrom(MonomContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NewMonomContext : public MonomContext {
  public:
    NewMonomContext(MonomContext *ctx);

    KoefContext *koef();
    VarxContext *varx();
    VaryContext *vary();
    VarzContext *varz();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  MonomContext* monom();

  class  KoefContext : public antlr4::ParserRuleContext {
  public:
    KoefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    KoefContext() = default;
    void copyFrom(KoefContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NewKoefContext : public KoefContext {
  public:
    NewKoefContext(KoefContext *ctx);

    antlr4::tree::TerminalNode *KF();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  KoefContext* koef();

  class  VarxContext : public antlr4::ParserRuleContext {
  public:
    VarxContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    VarxContext() = default;
    void copyFrom(VarxContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NewXContext : public VarxContext {
  public:
    NewXContext(VarxContext *ctx);

    antlr4::tree::TerminalNode *X();
    DegreeContext *degree();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  VarxContext* varx();

  class  VaryContext : public antlr4::ParserRuleContext {
  public:
    VaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    VaryContext() = default;
    void copyFrom(VaryContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NewYContext : public VaryContext {
  public:
    NewYContext(VaryContext *ctx);

    antlr4::tree::TerminalNode *Y();
    DegreeContext *degree();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  VaryContext* vary();

  class  VarzContext : public antlr4::ParserRuleContext {
  public:
    VarzContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    VarzContext() = default;
    void copyFrom(VarzContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NewZContext : public VarzContext {
  public:
    NewZContext(VarzContext *ctx);

    antlr4::tree::TerminalNode *Z();
    DegreeContext *degree();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  VarzContext* varz();

  class  DegreeContext : public antlr4::ParserRuleContext {
  public:
    DegreeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    DegreeContext() = default;
    void copyFrom(DegreeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NewDegContext : public DegreeContext {
  public:
    NewDegContext(DegreeContext *ctx);

    antlr4::tree::TerminalNode *DS();
    antlr4::tree::TerminalNode *DEG();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  DegreeContext* degree();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool polynomSempred(PolynomContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

