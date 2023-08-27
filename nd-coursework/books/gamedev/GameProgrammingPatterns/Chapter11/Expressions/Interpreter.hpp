// Copyright (c) 2014 by Robert Nystrom. All rights reserved.
//
// Name: Interpreter.hpp
// Author: crdrisko
// Date: 08/25/2023-15:40:31
// Description:

#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

class Expression
{
public:
    virtual ~Expression() {}
    virtual double evaluate() = 0;
};

class NumberExpression : public Expression
{
public:
    NumberExpression(double value) : value_(value) {}

    virtual double evaluate() { return value_; }

private:
    double value_;
};

class AdditionExpression : public Expression
{
public:
    AdditionExpression(Expression* left, Expression* right) : left_(left), right_(right) {}

    virtual double evaluate()
    {
        // Evaluate the operands
        double left  = left_->evaluate();
        double right = right_->evaluate();

        return left + right;
    }

private:
    Expression* left_;
    Expression* right_;
};

class MultiplicationExpression : public Expression
{
public:
    MultiplicationExpression(Expression* left, Expression* right) : left_(left), right_(right) {}

    virtual double evaluate()
    {
        // Evaluate the operands
        double left  = left_->evaluate();
        double right = right_->evaluate();

        return left * right;
    }

private:
    Expression* left_;
    Expression* right_;
};

#endif
