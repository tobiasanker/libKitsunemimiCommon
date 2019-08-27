/**
 *  @file    statemachine.h
 *
 *  @author  Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright MIT License
 *
 *  @brief simple statemachine
 *
 *  @detail Its only a simple statemachine in the moment. Basically its only to change the state
 *          and check the current state.
 */

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>
#include <iostream>
#include <map>
#include <utility>

namespace Kitsune
{
namespace Common
{
struct State;

class Statemachine
{
public:
    Statemachine();
    ~Statemachine();

    // init
    bool createNewState(const std::string &stateName);
    bool setCurrentState(const std::string &stateName);
    bool addTransition(const std::string &stateName,
                       const std::string &key,
                       const std::string &nextStateName);

    // runtime
    bool goToNextState(const std::string &next);
    std::string getCurrentState() const;

private:
    std::map<std::string, State*> m_allStates;

    State* m_currentState = nullptr;
};

} // namespace Common
} // namespace Kitsune

#endif // STATEMACHINE_H