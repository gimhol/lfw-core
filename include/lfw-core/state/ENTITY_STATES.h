#ifndef LFW_CORE_STATE_ENTITY_STATES_H
#define LFW_CORE_STATE_ENTITY_STATES_H

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

class States;

/// ENTITY_STATES — 全局实体状态注册表（对应 TS ENTITY_STATES）
States &entity_states();

LFW_NS_END

#endif
