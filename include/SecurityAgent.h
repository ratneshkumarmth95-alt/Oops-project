#pragma once
#include <memory>
#include <iostream>
#include <iomanip>
#include "Events.h"
#include "DecisionEngine.h"
#include "Actions.h"
#include "Logger.h"

class SecurityAgent {
private:
    DecisionEngine engine;
    std::vector<std::unique_ptr<Logger>> loggers;
    
    // State for the current processing cycle
    const SecurityEvent* currentEvent = nullptr;
    std::unique_ptr<Action> currentAction;
    double currentDCS = 0.0;
    std::string currentReason;

public:
    SecurityAgent() {
        // Initialize rules
        engine.addRule(std::make_unique<LoginRule>());
        engine.addRule(std::make_unique<PortScanRule>());
        engine.addRule(std::make_unique<MalwareRule>());
    }

    void addLogger(std::unique_ptr<Logger> logger) {
        loggers.push_back(std::move(logger));
    }

    void setStrategy(std::unique_ptr<DecisionStrategy> strategy) {
        engine.setStrategy(std::move(strategy));
    }

    // The OODA Loop
    void processEvent(const SecurityEvent& event) {
        observe(event);
        analyze();
        decide();
        execute();
        explain();
        
        // Log the results
        for (const auto& logger : loggers) {
            logger->log(*currentEvent, *currentAction, currentDCS, currentReason);
        }
    }

private:
    void observe(const SecurityEvent& event) {
        currentEvent = &event;
        std::cout << "\n--------------------------------------------------\n";
        std::cout << "[Agent] Observe: New event detected.\n";
        currentEvent->display();
    }

    void analyze() {
        std::cout << "[Agent] Analyze: Applying rules and gathering context...\n";
    }

    void decide() {
        std::cout << "[Agent] Decide: Using " << engine.getStrategyName() << "...\n";
        auto [action, dcs, reason] = engine.evaluate(*currentEvent);
        currentAction = std::move(action);
        currentDCS = dcs;
        currentReason = reason;
    }

    void execute() {
        std::cout << "[Agent] Execute: \n";
        if (currentAction) {
            currentAction->execute(*currentEvent);
        }
    }

    void explain() {
        std::cout << "\n[Agent] Explanation:\n";
        std::cout << "  Action:     " << currentAction->getName() << "\n";
        std::cout << "  DCS:        " << std::fixed << std::setprecision(2) << currentDCS << " (Decision Confidence Score)\n";
        std::cout << "  Factors:    " << currentReason << "\n";
        std::cout << "--------------------------------------------------\n";
    }
};
