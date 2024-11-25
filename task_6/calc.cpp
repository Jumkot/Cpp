#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class Expression {
protected:
    std::vector<std::shared_ptr<Expression>> operands;

public:
    virtual double eval() const = 0;
    void add_operand(std::shared_ptr<Expression> operand)
    {
        operands.push_back(operand);
    }
};

class Number : public Expression {
    double number_;

public:
    explicit Number(double number_) : number_(number_)
    {
    }
    double eval() const override
    {
        return number_;
    }
};

class Add : public Expression {
public:
    double eval() const override
    {
        double result = 0.0;
        for (const auto& operand : operands) {
            result += operand->eval();
        }
        return result;
    }
};

class Sub : public Expression {
public:
    double eval() const override
    {
        if (operands.empty()) {
            return 0.0;
        }
        double result = operands[0]->eval();
        for (size_t i = 1; i < operands.size(); ++i) {
            result -= operands[i]->eval();
        }
        return result;
    }
};

class Mul : public Expression {
public:
    double eval() const override
    {
        double result = 1.0;
        for (const auto& operand : operands) {
            result *= operand->eval();
        }
        return result;
    }
};

class Div : public Expression {
public:
    double eval() const override
    {
        if (operands.empty()) {
            return 0.0;
        }
        double result = operands[0]->eval();
        for (size_t i = 1; i < operands.size(); ++i) {
            const double divisor = operands[i]->eval();
            if (divisor == 0.0) {
                return std::numeric_limits<double>::quiet_NaN();
            }
            result /= divisor;
        }
        return result;
    }
};

class Invalid : public Expression {
public:
    double eval() const override
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
};

std::shared_ptr<Expression> parse_expression(std::istream& input)
{
    std::vector<std::shared_ptr<Expression>> expressions;
    std::vector<size_t> fold_indices;

    char c;
    while (input >> c) {
        if (c == '(') {
            std::string op;
            if (!(input >> op))
            {
                return std::make_shared<Invalid>();
            }

            std::shared_ptr<Expression> expr;
            if (op == "+") {
                expr = std::make_shared<Add>();
            } else if (op == "-") {
                expr = std::make_shared<Sub>();
            } else if (op == "*") {
                expr = std::make_shared<Mul>();
            } else if (op == "/") {
                expr = std::make_shared<Div>();
            } else {
                return std::make_shared<Invalid>();
            }

            expressions.push_back(expr);
            fold_indices.push_back(expressions.size() - 1);
        } else if (c == ')') {
            if (fold_indices.empty()) {
                return std::make_shared<Invalid>();
            }

            const size_t start = fold_indices.back();
            fold_indices.pop_back();

            auto parent = expressions[start];
            for (size_t i = start + 1; i < expressions.size(); ++i) {
                parent->add_operand(expressions[i]);
            }
            expressions.resize(start + 1);
        } else if (std::isdigit(c) || c == '-' || c == '.') {
            input.putback(c);
            double value;
            if (!(input >> value)) {
                return std::make_shared<Invalid>();
            }
            expressions.push_back(std::make_shared<Number>(value));
        } else {
            return std::make_shared<Invalid>();
        }
    }

    if (expressions.size() == 1) {
        return expressions[0];
    }
    return std::make_shared<Invalid>();
}

int main()
{
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream input(line);
        auto expression = parse_expression(input);
        std::cout << std::fixed << std::setprecision(4) << expression->eval()
                  << "\n";
    }
    return 0;
}