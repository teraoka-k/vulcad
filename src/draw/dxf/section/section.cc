#if !defined(VULCAD_DRAW_DXF_SECTION_SECTION)
#define VULCAD_DRAW_DXF_SECTION_SECTION

#include <fstream>
#include <iostream>

class Section {
protected:
  static void begin(std::ofstream &file, std::string sectionType) {
    file << "  0" << std::endl
         << "SECTION" << std::endl
         << "  2" << std::endl
         << sectionType << std::endl;
  }
  static void end(std::ofstream &file) {
    file << "  0" << std::endl << "ENDSEC" << std::endl;
  }
};

#endif // VULCAD_DRAW_DXF_SECTION_SECTION
