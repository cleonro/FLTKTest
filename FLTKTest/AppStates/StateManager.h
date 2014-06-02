#pragma once

#include <map>
#include <string>

#define STATEMNGR (StateManager::instance())

class BaseState
{
	friend class StateManager;
public:
	virtual void init(void* data = nullptr) = 0;
	virtual void clear() = 0;
	virtual void update(void* data = nullptr) = 0;
	virtual void render() = 0;
	virtual bool initialized() = 0;

protected:
	BaseState();
	virtual ~BaseState();
};

class StateManager
{
public:
	static StateManager& instance();

	void setActiveState(const std::string& stateName, void* initData = NULL);
	BaseState* activeState();

	void updateActiveState(void* data = nullptr);
	void renderActiveState();

protected:
	StateManager();
	~StateManager();

	void addStates();

private:
	std::map<std::string, BaseState*>	m_states;
	std::string							m_activeStateName;
	BaseState*							m_activeState;
};

