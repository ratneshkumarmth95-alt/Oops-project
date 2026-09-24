#pragma once
#include <string>
#include <iostream>
#include "Events.h"

class Action {
protected:
    std::string actionName;
public:
    Action(const std::string& name) : actionName(name) {}
    virtual ~Action() = default;
    virtual void execute(const SecurityEvent& event) const = 0;
    std::string getName() const { return actionName; }
};

class BlockIP : public Action {
public:
    BlockIP() : Action("Block IP") {}
    void execute(const SecurityEvent& event) const override {
        std::cout << ">>> ACTION EXECUTED: Firewall rule added to block IP " << event.getSourceIP() << " <<<\n";
    }
};

class NotifyAdmin : public Action {
public:
    NotifyAdmin() : Action("Notify Admin") {}
    void execute(const SecurityEvent& event) const override {
        std::cout << ">>> ACTION EXECUTED: Alert email sent to admin regarding IP " << event.getSourceIP() << " <<<\n";
    }
};

class QuarantineDevice : public Action {
public:
    QuarantineDevice() : Action("Quarantine Device") {}
    void execute(const SecurityEvent& event) const override {
        std::cout << ">>> ACTION EXECUTED: Device " << event.getSourceIP() << " isolated from network <<<\n";
    }
};

class Ignore : public Action {
public:
    Ignore() : Action("Ignore") {}
    void execute(const SecurityEvent& event) const override {
        std::cout << ">>> ACTION EXECUTED: No action taken for IP " << event.getSourceIP() << " <<<\n";
    }
};
