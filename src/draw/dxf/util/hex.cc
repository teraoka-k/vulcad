#if !defined(VULCAD_DRAW_UTIL_HEX)
#define VULCAD_DRAW_UTIL_HEX

#include <iomanip>
#include <string>

class Hex {
public:
  /**
   * convert integer to hex
   */
  static std::string from(int integer) {
    std::stringstream hex;
    hex << std::uppercase << std::hex << integer;
    return hex.str();
  }
};

#endif // VULCAD_DRAW_UTIL_HEX
