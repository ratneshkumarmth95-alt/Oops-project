#pragma once
#include "Events.h"

class Rule {
public:
    virtual ~Rule() = default;
    // Returns match strength between 0.0 and 1.0
    virtual double evaluate(const SecurityEvent& event) const = 0;
};

class LoginRule : public Rule {
public:
    double evaluate(const SecurityEvent& event) const override {
        if (event.getEventType() == "LoginFailure") {
            return 0.9; // High confidence it's an attack if rule triggers
        }
        return 0.0;
    }
};

class PortScanRule : public Rule {
public:
    double evaluate(const SecurityEvent& event) const override {
        if (event.getEventType() == "PortScan") {
            return 0.7; 
        }
        return 0.0;
    }
};

class MalwareRule : public Rule {
public:
    double evaluate(const SecurityEvent& event) const override {
        if (event.getEventType() == "MalwareAlert") {
            return 1.0; 
        }
        return 0.0;
    }
};
