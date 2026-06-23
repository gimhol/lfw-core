#ifndef LFW_CORE_DEFINES_WEAPONTYPE_HPP
#define LFW_CORE_DEFINES_WEAPONTYPE_HPP

#include <cstdint>

enum class WeaponType : uint8_t
{
  None = 0,
  Stick = 1,
  Heavy = 2,
  Knife = 3,
  Baseball = 4,
  Drink = 5
};

#endif // LFW_CORE_DEFINES_WEAPONTYPE_HPP
