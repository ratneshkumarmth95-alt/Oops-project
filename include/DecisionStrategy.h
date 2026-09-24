#pragma once
#include <memory>
#include "Actions.h"

class DecisionStrategy {
public:
    virtual ~DecisionStrategy() = default;
    virtual std::unique_ptr<Action> decide(double dcs) const = 0;
    virtual std::string getStrategyName() const = 0;
};

class BalancedStrategy : public DecisionStrategy {
public:
    std::string getStrategyName() const override { return "Balanced Strategy"; }
    std::unique_ptr<Action> decide(double dcs) const override {
        if (dcs >= 0.85) {
            return std::make_unique<BlockIP>();
        } else if (dcs >= 0.60) {
            return std::make_unique<NotifyAdmin>();
        } else {
            return std::make_unique<Ignore>();
        }
    }
};

class StrictStrategy : public DecisionStrategy {
public:
    std::string getStrategyName() const override { return "Strict Strategy"; }
    std::unique_ptr<Action> decide(double dcs) const override {
        if (dcs >= 0.60) {
            return std::make_unique<BlockIP>();
        } else if (dcs >= 0.40) {
            return std::make_unique<NotifyAdmin>();
        } else {
            return std::make_unique<Ignore>();
        }
    }
};

class RelaxedStrategy : public DecisionStrategy {
public:
    std::string getStrategyName() const override { return "Relaxed Strategy"; }
    std::unique_ptr<Action> decide(double dcs) const override {
        if (dcs >= 0.95) {
            return std::make_unique<BlockIP>();
        } else if (dcs >= 0.80) {
            return std::make_unique<NotifyAdmin>();
        } else {
            return std::make_unique<Ignore>();
        }
    }
};
