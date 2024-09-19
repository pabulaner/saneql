#pragma once
// -------------------------------------------------------------------------------------
#include <cassert>
#include <cstdint>
#include <cstring>
#include <limits>
#include <string>
// -------------------------------------------------------------------------------------
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;
using UInteger = u32;
using Integer = s32;
using Timestamp = s64;
using Interval = s64;
using Numeric = double;
static constexpr Integer minUInteger = std::numeric_limits<UInteger>::min();
static constexpr Integer minInteger = std::numeric_limits<Integer>::min();
// -------------------------------------------------------------------------------------
template <int maxLength>
struct Varchar {
   int16_t length;
   char data[maxLength] = {0};  // not '\0' terminated

   Varchar() : length(0) {}
   Varchar(char c) {
      assert(1 <= maxLength);
      length = 1;
      data[0] = c;
   }
   Varchar(const char* str)
   {
      int l = strlen(str);
      assert(l <= maxLength);
      length = l;
      memcpy(data, str, l);
   }
   Varchar(const std::string_view& view)
   {
      assert(view.size() <= maxLength);
      length = view.size();
      memcpy(data, view.data(), view.size());
   }
   template <int otherMaxLength>
   Varchar(const Varchar<otherMaxLength>& other)
   {
      assert(other.length <= maxLength);
      length = other.length;
      memcpy(data, other.data, length);
   }

   explicit operator Timestamp() const {
      if (length != sizeof("0000-00-00") - 1 || data[4] != '-' || data[7] != '-') {
         return 0;
      }

      std::string str(data, length);

      int year = std::stoi(str.substr(0, 4));
      int month = std::stoi(str.substr(5, 2));
      int day = std::stoi(str.substr(8, 2));

      unsigned a = (14 - month) / 12;
      unsigned y = year + 4800 - a;
      unsigned m = month + (12 * a) - 3;
      return day + ((153 * m + 2) / 5) + (365 * y) + (y / 4) - (y / 100) +
            (y / 400) - 32045;
   }

   void append(char x)
   {
      assert(length < maxLength);
      data[length++] = x;
   };

   std::string toString() const { return std::string(data, length); };

   template <int otherMaxLength>
   Varchar<maxLength + otherMaxLength> operator||(const Varchar<otherMaxLength>& other) const
   {
      Varchar<maxLength + otherMaxLength> tmp;
      tmp.length = length + other.length;
      memcpy(tmp.data, data, length);
      memcpy(tmp.data + length, other.data, other.length);
      return tmp;
   }

   bool operator==(const Varchar<maxLength>& other) const { return (length == other.length) && (memcmp(data, other.data, length) == 0); }

   bool operator!=(const Varchar<maxLength>& other) const { return !operator==(other); }

   bool operator<(const Varchar<maxLength>& other) const
   {
      int cmp = memcmp(data, other.data, (length < other.length) ? length : other.length);
      if (cmp)
         return cmp < 0;
      else
         return length < other.length;
   }

   template <int len>
   friend std::ostream& operator<<(std::ostream& os, const Varchar<len>& value);
};
// -------------------------------------------------------------------------------------
// Fold functions convert integers to a lexicographical comparable format
unsigned fold(u8* writer, const Integer& x)
{
   *reinterpret_cast<u32*>(writer) = __builtin_bswap32(x ^ (1ul << 31));
   return sizeof(x);
}
// -------------------------------------------------------------------------------------
unsigned fold(u8* writer, const Timestamp& x)
{
   *reinterpret_cast<u64*>(writer) = __builtin_bswap64(x ^ (1ull << 63));
   return sizeof(x);
}
// -------------------------------------------------------------------------------------
unsigned fold(u8* writer, const u64& x)
{
   *reinterpret_cast<u64*>(writer) = __builtin_bswap64(x);
   return sizeof(x);
}
// -------------------------------------------------------------------------------------
template <int len>
unsigned fold(u8* writer, const Varchar<len>& x)
{
   memcpy(writer, x.data, x.length);
   writer[x.length] = 0;
   return x.length + 1;
}
// -------------------------------------------------------------------------------------
unsigned unfold(const u8* input, Integer& x)
{
   x = __builtin_bswap32(*reinterpret_cast<const u32*>(input)) ^ (1ul << 31);
   return sizeof(x);
}
// -------------------------------------------------------------------------------------
unsigned unfold(const u8* input, Timestamp& x)
{
   x = __builtin_bswap64(*reinterpret_cast<const u64*>(input)) ^ (1ul << 63);
   return sizeof(x);
}
// -------------------------------------------------------------------------------------
unsigned unfold(const u8* input, u64& x)
{
   x = __builtin_bswap64(*reinterpret_cast<const u64*>(input));
   return sizeof(x);
}
// -------------------------------------------------------------------------------------
template <int len>
unsigned unfold(const u8* input, Varchar<len>& x)
{
   int l = strlen(reinterpret_cast<const char*>(input));
   assert(l <= len);
   memcpy(x.data, input, l);
   x.length = l;
   return l + 1;
}

template <int len>
std::ostream& operator<<(std::ostream& os, const Varchar<len>& value) {
   os << value.toString();
   return os;
}