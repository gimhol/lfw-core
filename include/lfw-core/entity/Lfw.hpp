#ifndef LFW_CORE_ENTITY_LFW_HPP
#define LFW_CORE_ENTITY_LFW_HPP

#include "lfw-core/utils/math/MT.hpp"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// LFW — 游戏核心上下文
/// 对应 TS 中 `export class LFW`
/// 该 class 是 little-fighter 引擎的顶层容器，持有：
///   - World（世界/舞台）
///   - Factory（实体工厂）
///   - DatMgr（数据管理器）
///   - helpers：fighters / weapons / entities / balls / uis
///   - UI 栈（UIStack[]）
///   - 玩家信息（players: Map<string, PlayerInfo>）
///   - 资源包（zips: IZip[]）
///   - 输入回调（IKeyboardCallback）
///   - MersenneTwister 随机数生成器（_mt）
///   - i18n 国际化（I18N）
/// 当前 C++ 移植为渐进式，逐步添加成员。
struct LFW
{
  /// 梅森旋转随机数生成器 — 对应 TS lfw._mt（私有，通过 get mt() 暴露）
  MersenneTwister mt;
};

LFW_NS_END

#endif
