#include "StateManager.h"


BaseState::BaseState()
{

}

BaseState::~BaseState()
{

}

StateManager::StateManager()
{
	addStates();
}


StateManager::~StateManager()
{

}

StateManager& StateManager::instance()
{
	static StateManager stMngr;
	return stMngr;
}

void StateManager::setActiveState(const std::string& stateName, void* initData)
{
	BaseState* oldState = m_states[m_activeStateName];
	m_activeStateName = stateName;
	BaseState* activeState = m_states[m_activeStateName];
	if(oldState != nullptr)
	{
		oldState->clear();
	}
	if(activeState != nullptr)
	{
		activeState->init(initData);
	}
}

void StateManager::addStates()
{

}