#ifndef LFW_CORE_DEFINES_OID_HPP
#define LFW_CORE_DEFINES_OID_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

/// OID.ts — 内置对象 ID
enum class OID : uint8_t
{
  Template,
  Julian,
  Firzen,
  LouisEX,
  Bat,
  Justin,
  Knight,
  Jan,
  Monk,
  Sorcerer,
  Jack,
  Mark,
  Hunter,
  Bandit,
  Deep,
  John,
  Henry,
  Rudolf,
  Louis,
  Firen,
  Freeze,
  Dennis,
  Woody,
  Davis,
  Weapon0_Stick,
  Weapon2_Hoe,
  Weapon4_Knife,
  Weapon5_Baseball,
  Weapon6_Milk,
  Weapon1_Stone,
  Weapon3_WoodenBox,
  Weapon8_Beer,
  Weapon9_Boomerang,
  Weapon10_LouisArmourA,
  Weapon11_LouisArmourB,
  Criminal,
  JohnBall,
  HenryArrow1,
  RudolfWeapon,
  DeepBall,
  HenryWind,
  DennisBall,
  WoodyBall,
  DavisBall,
  HenryArrow2,
  FreezeBall,
  FirenBall,
  FirenFlame,
  FreezeColumn,
  Weapon7_IceSword,
  JohnBiscuit,
  DennisChase,
  JackBall,
  JanChaseh,
  JanChase,
  FirzenChasef,
  FirzenChasei,
  FirzenBall,
  BatBall,
  BatChase,
  JustinBall,
  JulianBall,
  JulianBall2,
  Etc,
  BrokenWeapon,
};

inline std::string_view oid_to_string(OID v)
{
  switch (v)
  {
  case OID::Template:
    return "0";
  case OID::Julian:
    return "52";
  case OID::Firzen:
    return "51";
  case OID::LouisEX:
    return "50";
  case OID::Bat:
    return "38";
  case OID::Justin:
    return "39";
  case OID::Knight:
    return "37";
  case OID::Jan:
    return "36";
  case OID::Monk:
    return "35";
  case OID::Sorcerer:
    return "34";
  case OID::Jack:
    return "33";
  case OID::Mark:
    return "32";
  case OID::Hunter:
    return "31";
  case OID::Bandit:
    return "30";
  case OID::Deep:
    return "1";
  case OID::John:
    return "2";
  case OID::Henry:
    return "4";
  case OID::Rudolf:
    return "5";
  case OID::Louis:
    return "6";
  case OID::Firen:
    return "7";
  case OID::Freeze:
    return "8";
  case OID::Dennis:
    return "9";
  case OID::Woody:
    return "10";
  case OID::Davis:
    return "11";
  case OID::Weapon0_Stick:
    return "100";
  case OID::Weapon2_Hoe:
    return "101";
  case OID::Weapon4_Knife:
    return "120";
  case OID::Weapon5_Baseball:
    return "121";
  case OID::Weapon6_Milk:
    return "122";
  case OID::Weapon1_Stone:
    return "150";
  case OID::Weapon3_WoodenBox:
    return "151";
  case OID::Weapon8_Beer:
    return "123";
  case OID::Weapon9_Boomerang:
    return "124";
  case OID::Weapon10_LouisArmourA:
    return "217";
  case OID::Weapon11_LouisArmourB:
    return "218";
  case OID::Criminal:
    return "300";
  case OID::JohnBall:
    return "200";
  case OID::HenryArrow1:
    return "201";
  case OID::RudolfWeapon:
    return "202";
  case OID::DeepBall:
    return "203";
  case OID::HenryWind:
    return "204";
  case OID::DennisBall:
    return "205";
  case OID::WoodyBall:
    return "206";
  case OID::DavisBall:
    return "207";
  case OID::HenryArrow2:
    return "208";
  case OID::FreezeBall:
    return "209";
  case OID::FirenBall:
    return "210";
  case OID::FirenFlame:
    return "211";
  case OID::FreezeColumn:
    return "212";
  case OID::Weapon7_IceSword:
    return "213";
  case OID::JohnBiscuit:
    return "214";
  case OID::DennisChase:
    return "215";
  case OID::JackBall:
    return "216";
  case OID::JanChaseh:
    return "219";
  case OID::JanChase:
    return "220";
  case OID::FirzenChasef:
    return "221";
  case OID::FirzenChasei:
    return "222";
  case OID::FirzenBall:
    return "223";
  case OID::BatBall:
    return "224";
  case OID::BatChase:
    return "225";
  case OID::JustinBall:
    return "226";
  case OID::JulianBall:
    return "228";
  case OID::JulianBall2:
    return "229";
  case OID::Etc:
    return "998";
  case OID::BrokenWeapon:
    return "999";
  }
  return "";
}

inline std::optional<OID> oid_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, OID> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(OID::BrokenWeapon); ++i)
    {
      auto v = static_cast<OID>(i);
      r[oid_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_OID_HPP
