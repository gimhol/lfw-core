#ifndef LFW_CORE_DEFINES_OID_HPP
#define LFW_CORE_DEFINES_OID_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// OID.ts — 内置对象 ID（枚举值 = LF2 内部编号）
#define ENUM_ITEMS(X)                                       \
  X(OID, Template, "0", "模板", = 0)                        \
  X(OID, Julian, "52", "Julian", = 52)                      \
  X(OID, Firzen, "51", "Firzen", = 51)                      \
  X(OID, LouisEX, "50", "LouisEX", = 50)                    \
  X(OID, Bat, "38", "Bat", = 38)                            \
  X(OID, Justin, "39", "Justin", = 39)                      \
  X(OID, Knight, "37", "Knight", = 37)                      \
  X(OID, Jan, "36", "Jan", = 36)                            \
  X(OID, Monk, "35", "Monk", = 35)                          \
  X(OID, Sorcerer, "34", "Sorcerer", = 34)                  \
  X(OID, Jack, "33", "Jack", = 33)                          \
  X(OID, Mark, "32", "Mark", = 32)                          \
  X(OID, Hunter, "31", "Hunter", = 31)                      \
  X(OID, Bandit, "30", "Bandit", = 30)                      \
  X(OID, Deep, "1", "Deep", = 1)                            \
  X(OID, John, "2", "John", = 2)                            \
  X(OID, Henry, "4", "Henry", = 4)                          \
  X(OID, Rudolf, "5", "Rudolf", = 5)                        \
  X(OID, Louis, "6", "Louis", = 6)                          \
  X(OID, Firen, "7", "Firen", = 7)                          \
  X(OID, Freeze, "8", "Freeze", = 8)                        \
  X(OID, Dennis, "9", "Dennis", = 9)                        \
  X(OID, Woody, "10", "Woody", = 10)                        \
  X(OID, Davis, "11", "Davis", = 11)                        \
  X(OID, Weapon0_Stick, "100", "棍", = 100)                 \
  X(OID, Weapon2_Hoe, "101", "锄头", = 101)                 \
  X(OID, Weapon4_Knife, "120", "刀", = 120)                 \
  X(OID, Weapon5_Baseball, "121", "棒球棍", = 121)          \
  X(OID, Weapon6_Milk, "122", "牛奶", = 122)                \
  X(OID, Weapon1_Stone, "150", "石头", = 150)               \
  X(OID, Weapon3_WoodenBox, "151", "木箱", = 151)           \
  X(OID, Weapon8_Beer, "123", "啤酒", = 123)                \
  X(OID, Weapon9_Boomerang, "124", "回旋镖", = 124)         \
  X(OID, Weapon10_LouisArmourA, "217", "Louis盔甲A", = 217) \
  X(OID, Weapon11_LouisArmourB, "218", "Louis盔甲B", = 218) \
  X(OID, Criminal, "300", "罪犯", = 300)                    \
  X(OID, JohnBall, "200", "John波", = 200)                  \
  X(OID, HenryArrow1, "201", "Henry箭1", = 201)             \
  X(OID, RudolfWeapon, "202", "Rudolf武器", = 202)          \
  X(OID, DeepBall, "203", "Deep波", = 203)                  \
  X(OID, HenryWind, "204", "Henry风", = 204)                \
  X(OID, DennisBall, "205", "Dennis波", = 205)              \
  X(OID, WoodyBall, "206", "Woody波", = 206)                \
  X(OID, DavisBall, "207", "Davis波", = 207)                \
  X(OID, HenryArrow2, "208", "Henry箭2", = 208)             \
  X(OID, FreezeBall, "209", "Freeze波", = 209)              \
  X(OID, FirenBall, "210", "Firen波", = 210)                \
  X(OID, FirenFlame, "211", "Firen火焰", = 211)             \
  X(OID, FreezeColumn, "212", "Freeze冰柱", = 212)          \
  X(OID, Weapon7_IceSword, "213", "冰剑", = 213)            \
  X(OID, JohnBiscuit, "214", "John饼干", = 214)             \
  X(OID, DennisChase, "215", "Dennis追击", = 215)           \
  X(OID, JackBall, "216", "Jack波", = 216)                  \
  X(OID, JanChaseh, "219", "Jan追H", = 219)                 \
  X(OID, JanChase, "220", "Jan追击", = 220)                 \
  X(OID, FirzenChasef, "221", "Firzen追F", = 221)           \
  X(OID, FirzenChasei, "222", "Firzen追I", = 222)           \
  X(OID, FirzenBall, "223", "Firzen波", = 223)              \
  X(OID, BatBall, "224", "Bat波", = 224)                    \
  X(OID, BatChase, "225", "Bat追击", = 225)                 \
  X(OID, JustinBall, "226", "Justin波", = 226)              \
  X(OID, JulianBall, "228", "Julian波", = 228)              \
  X(OID, JulianBall2, "229", "Julian波2", = 229)            \
  X(OID, Etc, "998", "杂项", = 998)                         \
  X(OID, BrokenWeapon, "999", "破碎武器", = 999)

enum class OID : uint16_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto OID_MIN = OID::Template;
constexpr auto OID_MAX = OID::BrokenWeapon;
GEN_ENUM_STR_MAP(OIDStringMap, ENUM_ITEMS, OID)
GEN_ENUM_NAME_MAP(OIDNameMap, ENUM_ITEMS, OID)
GEN_ENUM_DESC_MAP(OIDDescMap, ENUM_ITEMS, OID)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(oid_to_string, oid_from_string, OID, OIDStringMap)
DEFINE_ENUM_STR_CONVERTERS(oid_to_name, oid_from_name, OID, OIDNameMap)
DEFINE_ENUM_TO_STR(oid_to_desc, OID, OIDDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_OID_HPP
