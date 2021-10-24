#pragma once

#include <memory>
#include "date.h"

enum Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum LogicalOperation {
    Or,
    And,
};

class Node
{
public:
    virtual bool Evaluate(const Date& input_date, const std::string input_event) const = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date& input_date, const std::string input_event) const override {
        return true;
    }
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison new_cmp, const Date& new_date)
        : cmp(new_cmp),
          date(new_date) {}
    bool Evaluate(const Date& input_date, const std::string input_event) const override {
        switch (cmp) {
        case Comparison::Less:
            return input_date < date;
        case Comparison::LessOrEqual:
            return input_date <= date;
        case Comparison::Greater:
            return input_date > date;
        case Comparison::GreaterOrEqual:
            return input_date >= date;
        case Comparison::Equal:
            return input_date == date;
        case Comparison::NotEqual:
            return input_date != date;
        default:
            break;
        }
        return false;
    }

    const Comparison cmp;
    const Date date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison new_cmp, const std::string& new_event)
        : cmp(new_cmp),
          event(new_event){}
    bool Evaluate(const Date& input_date, const std::string input_event) const override {
        switch (cmp) {
        case Comparison::Less:
            return input_event < event;
        case Comparison::LessOrEqual:
            return input_event <= event;
        case Comparison::Greater:
            return input_event > event;
        case Comparison::GreaterOrEqual:
            return input_event >= event;
        case Comparison::Equal:
            return input_event == event;
        case Comparison::NotEqual:
            return input_event != event;
        default:
            break;
        }
        return false;
    }

    const Comparison cmp;
    const std::string event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation new_lo, std::shared_ptr<Node> new_left, std::shared_ptr<Node> new_right)
        : lo(new_lo),
          left(new_left),
          right(new_right){}
    bool Evaluate(const Date& input_date, const std::string input_event) const override {
        switch (lo) {
        case LogicalOperation::Or:
            return left->Evaluate(input_date, input_event) || right->Evaluate(input_date, input_event);
        case LogicalOperation::And:
            return left->Evaluate(input_date, input_event) && right->Evaluate(input_date, input_event);
        default:
            break;
        }
        return false;
    }

    const LogicalOperation lo;
    const std::shared_ptr<Node> left;
    const std::shared_ptr<Node> right;
};

