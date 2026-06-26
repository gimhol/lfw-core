#ifndef LFW_CORE_STATE_STATEBASE_PROXY_H
#define LFW_CORE_STATE_STATEBASE_PROXY_H
#include "lfw-core/state/State_Base.hpp"
#include "lfw-core/core.hpp"
LFW_NS_BEGIN
class StateBase_Proxy : public State_Base { public: using State_Base::State_Base; };
LFW_NS_END

#endif