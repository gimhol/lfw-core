#include "lfw-core/state/ENTITY_STATES.h"
#include "lfw-core/state/States.h"
#include "lfw-core/state/State_Base.hpp"
#include "lfw-core/state/WeaponState_Base.h"
#include "lfw-core/state/CharacterState_Base.h"
#include "lfw-core/state/StateBase_Proxy.h"
#include "lfw-core/state/WeaponState_InTheSky.h"
#include "lfw-core/state/WeaponState_OnGround.h"
#include "lfw-core/state/WeaponState_OnHand.h"
#include "lfw-core/state/WeaponState_Throwing.h"
#include "lfw-core/state/State_WeaponBroken.h"
#include "lfw-core/state/CharacterState_Standing.h"
#include "lfw-core/state/CharacterState_Walking.h"
#include "lfw-core/state/CharacterState_Running.h"
#include "lfw-core/state/CharacterState_Jump.h"
#include "lfw-core/state/CharacterState_Dash.h"
#include "lfw-core/state/CharacterState_Falling.h"
#include "lfw-core/state/CharacterState_Frozen.h"
#include "lfw-core/state/CharacterState_Lying.h"
#include "lfw-core/state/CharacterState_Caught.h"
#include "lfw-core/state/CharacterState_Injured.h"
#include "lfw-core/state/CharacterState_Rowing.h"
#include "lfw-core/state/CharacterState_Drink.h"
#include "lfw-core/state/CharacterState_Burning.h"
#include "lfw-core/state/CharacterState_Teleport2NearestEnemy.h"
#include "lfw-core/state/CharacterState_Teleport2FarthestAlly.h"
#include "lfw-core/state/CharacterState_Transform2LouisEX.h"
#include "lfw-core/state/State_Burning.h"
#include "lfw-core/state/State_15.h"
#include "lfw-core/state/State_TransformTo8XXX.h"
#include "lfw-core/state/State_TransformToCatching.h"
#include "lfw-core/defines/StateType.hpp"

LFW_NS_BEGIN

States &entity_states()
{
  static States s;

  // 仅首次调用时初始化（懒加载单例）
  static bool _init = [&]() -> bool
  {
    // TransformTo_ 范围
    s.set_in_range(static_cast<int>(StateType::TransformToMin),
                   static_cast<int>(StateType::TransformToMax),
                   [](int k) -> State_Base *
                   { return new State_TransformTo8XXX(static_cast<StateType>(k)); });

    // Ball 系列
    s.set_all_of(
        {static_cast<int>(StateType::BallBase),
         static_cast<int>(StateType::Ball3005),
         static_cast<int>(StateType::Ball3006),
         static_cast<int>(StateType::BallDisappear),
         static_cast<int>(StateType::BallFlying),
         static_cast<int>(StateType::BallHit),
         static_cast<int>(StateType::BallHitting)},
        [](int k) -> State_Base *
        { return new StateBase_Proxy(static_cast<StateType>(k)); });

    // 逐一注册所有状态
    s.add({
        new State_WeaponBroken(StateType::WeaponBrokens),
        new State_TransformToCatching(StateType::TransformToCatchingBegin),
        new WeaponState_Base(StateType::WeaponRebounding),
        new WeaponState_InTheSky(StateType::WeaponInTheSky),
        new WeaponState_OnGround(StateType::WeaponOnGround),
        new WeaponState_OnHand(StateType::WeaponOnHand),
        new WeaponState_Throwing(StateType::WeaponThrowing),
        new WeaponState_InTheSky(StateType::HeavyWeaponInTheSky),
        new WeaponState_OnGround(StateType::HeavyWeaponOnGround),
        new WeaponState_OnHand(StateType::HeavyWeaponOnHand),
        new WeaponState_Throwing(StateType::HeavyWeaponJustOnGround),
        new State_Base(StateType::EntityBase),
        new WeaponState_Base(StateType::WeaponBase),
        new CharacterState_Base(StateType::CharacterBase),
        new CharacterState_Standing(StateType::Standing),
        new CharacterState_Walking(StateType::Walking),
        new CharacterState_Running(StateType::Running),
        new CharacterState_Jump(StateType::Jump),
        new CharacterState_Dash(StateType::Dash),
        new CharacterState_Falling(StateType::Falling),
        new State_Burning(StateType::Burning),
        new CharacterState_Frozen(StateType::Frozen),
        new CharacterState_Lying(StateType::Lying),
        new CharacterState_Caught(StateType::Caught),
        new CharacterState_Injured(StateType::Injured),
        new CharacterState_Injured(StateType::Tired),
        new CharacterState_Base(StateType::ZMoveable),
        new CharacterState_Teleport2NearestEnemy(StateType::TeleportToNearestEnemy),
        new CharacterState_Teleport2FarthestAlly(StateType::TeleportToFarthestAlly),
        new CharacterState_Transform2LouisEX(StateType::TurnIntoLouisEX),
        new CharacterState_Rowing(StateType::Rowing),
        new CharacterState_Drink(StateType::Drink),
        new State_15(StateType::Normal),
        new StateBase_Proxy(StateType::LandGoto94),
    });

    return true;
  }();

  (void)_init;
  return s;
}

LFW_NS_END
