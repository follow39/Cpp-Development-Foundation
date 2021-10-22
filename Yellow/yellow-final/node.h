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
    Node();
    virtual bool Evaluate(const Date& date, const std::string str) const;
};

class EmptyNode : public Node {

};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(Comparison cmp, const Date& date);
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(Comparison cmp, const std::string& event);
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(LogicalOperation cmp, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
};

