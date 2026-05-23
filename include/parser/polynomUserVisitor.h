#pragma once

#include"antlr4-runtime.h"
#include"polynomBaseVisitor.h"
#include"monom.h"
#include"polynom.h"
#include<iostream>

class polynomUserVisitor :public polynomBaseVisitor {
    double k = 1;
    char x = 0, y = 0, z = 0;
    char q = 11;
public:

    Polynom* p = nullptr;

    void setPolynom(Polynom* polynom) { p = polynom; }

    std::any visitAddFirstMonom(polynomParser::AddFirstMonomContext* ctx) {
        if (!p) return {};
        visitChildren(ctx);
        if ((ctx->op != nullptr) && (ctx->op->getType() == polynomParser::SUB))k *= (-1);
        Monom m = Monom(k, x, y, z);
        k = 1;
        x = 0;
        y = 0;
        z = 0;
        q = 11;
        p->add(m);
        return m;
    }

    std::any visitAddMonom(polynomParser::AddMonomContext* ctx) {
        if (!p) return {};
        visitChildren(ctx);
        if (ctx->op->getType() == polynomParser::SUB)k *= (-1);
        Monom m = Monom(k, x, y, z);
        k = 1;
        x = 0;
        y = 0;
        z = 0;
        q = 11;
        p->add(m);
        return m;
    }

    std::any visitNewMonom(polynomParser::NewMonomContext* ctx) {
        visitChildren(ctx);
        if (!ctx->koef())k = 1;
        if (!ctx->varx())x = 0;
        if (!ctx->vary())y = 0;
        if (!ctx->varz())z = 0;
        return k;
    }

    std::any visitNewKoef(polynomParser::NewKoefContext* ctx) {
        visitChildren(ctx);
        k = std::stoi(ctx->KF()->getText());
        return k;
    }

    std::any visitNewX(polynomParser::NewXContext* ctx) {
        visitChildren(ctx);
        if (q != 11) {
            x = q;
        }
        else {
            x = 1;
        }
        q = 11;
        return x;
    }

    std::any visitNewY(polynomParser::NewYContext* ctx) {
        visitChildren(ctx);
        if (q != 11) {
            y = q;
        }
        else {
            y = 1;
        }
        q = 11;
        return y;
    }

    std::any visitNewZ(polynomParser::NewZContext* ctx) {
        visitChildren(ctx);
        if (q != 11) {
            z = q;
        }
        else {
            z = 1;
        }
        q = 11;
        return z;
    }

    std::any visitNewDeg(polynomParser::NewDegContext* ctx) {
        int t = std::stoi(ctx->DEG()->getText());
        if ((t < -5) || (t > 10))throw - 1;
        q = t;
        return q;
    }
};