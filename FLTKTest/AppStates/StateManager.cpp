#include "StateManager.h"
#include "GLSimpleState.h"

UIEvent::UIEvent(UIEventType type)
	: m_type(type)
{

}

UIEvent::~UIEvent()
{

}

bool& UIEvent::rbutton(int index)
{
	index = index % 3;
	return m_buttons[index];
}

int& UIEvent::rkey()
{
	return m_key;
}

int& UIEvent::rx()
{
	return m_x;
}

int& UIEvent::ry()
{
	return m_y;
}

BaseState::BaseState()
{

}

BaseState::~BaseState()
{

}

StateManager::StateManager() :
	m_activeState(nullptr)
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
	BaseState* oldState = m_activeState;
	m_activeStateName = stateName;
	m_activeState = m_states[m_activeStateName];
	if(oldState != nullptr)
	{
		oldState->clear();
	}
	if(m_activeState != nullptr)
	{
		m_activeState->init(initData);
	}
}

BaseState* StateManager::activeState()
{
	return m_activeState;
}

void StateManager::updateActiveState(void* data)
{
	if(m_activeState == nullptr)
	{
		return;
	}

	if(!m_activeState->initialized())
	{
		m_activeState->init();
	}
	m_activeState->update(data);
}

void StateManager::renderActiveState()
{
	if(m_activeState == nullptr)
	{
		return;
	}

	m_activeState->render();
}

void StateManager::addStates()
{
	m_states[GL_SIMPLE_STATE] = new GLSimpleState();

	m_activeStateName = GL_SIMPLE_STATE;
	
	m_activeState = m_states[m_activeStateName];
}

void StateManager::sendEvent(UIEvent* event)
{
	if(m_activeState == nullptr)
	{
		return;
	}

	m_activeState->event(event);
}