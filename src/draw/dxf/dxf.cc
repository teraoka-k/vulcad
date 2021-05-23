#if !defined(VULCAD_DRAW_DXF_DXF)
#define VULCAD_DRAW_DXF_DXF

#include "../shapes/bezier.cc"
#include "../shapes/circle.cc"
#include "../shapes/line.cc"
#include "../shapes/point.cc"
#include "../shapes/spline.cc"
#include "dxfSpline.cc"
#include <fstream>
#include <iostream>
#include <variant>

constexpr int LAYER = 1;
const std::string OUT_DIR = "dxf/";

/**
 * convert object to dxf file
 * look at dxf specification for detail
 * https://images.autodesk.com/adsk/files/autocad_2012_pdf_dxf-reference_enu.pdf
 */
class Dxf {

public:
  static void write(std::string fileName,
                    std::variant<Point, Line, Circle, Bezier, Spline> shape) {
    std::ofstream file(OUT_DIR + fileName + ".dxf");
    if (std::holds_alternative<Point>(shape))
      Dxf::writePoint(file, std::get<Point>(shape));
    else if (std::holds_alternative<Line>(shape))
      Dxf::writeLine(file, std::get<Line>(shape));
    else if (std::holds_alternative<Circle>(shape))
      Dxf::writeCircle(file, std::get<Circle>(shape));
    else if (std::holds_alternative<Bezier>(shape))
      Dxf::writeBezier(file, std::get<Bezier>(shape));
    else if (std::holds_alternative<Spline>(shape))
      DxfSpline::write(file, std::get<Spline>(shape));

    file << "  0" << std::endl << "EOF" << std::endl;
    file.close();
  }

private:
  static void writeBezier(std::ofstream &file, Bezier &bezier) {
    file << "bezier";
  }

  static void writeCircle(std::ofstream &file, Circle &circle) {
    file << 0 << std::endl
         << "SECTION" << std::endl
         << 2 << std::endl
         << "ENTITIES" << std::endl
         << 0 << std::endl
         << "CIRCLE" << std::endl
         << 8 << std::endl
         << LAYER << std::endl
         << 10 << std::endl
         << circle.origin.x << std::endl
         << 20 << std::endl
         << circle.origin.y << std::endl
         << 40 << std::endl
         << circle.radius << std::endl
         << 0 << std::endl
         << "ENDSEC" << std::endl;
    ;
  }

  static void writeLine(std::ofstream &file, Line &line) {
    file << 0 << std::endl
         << "SECTION" << std::endl
         << 2 << std::endl
         << "ENTITIES" << std::endl
         << 0 << std::endl
         << "LINE" << std::endl
         << 8 << std::endl
         << LAYER << std::endl
         << 10 << std::endl
         << line.origin.x << std::endl
         << 20 << std::endl
         << line.origin.y << std::endl
         << 11 << std::endl
         << line.end.x << std::endl
         << 21 << std::endl
         << line.end.y << std::endl
         << 0 << std::endl
         << "ENDSEC" << std::endl;
    ;
  }

  static void writePoint(std::ofstream &file, Point &point) {
    file << 0 << std::endl
         << "SECTION" << std::endl
         << 2 << std::endl
         << "ENTITIES" << std::endl
         << 0 << std::endl
         << "POINT" << std::endl
         << 8 << std::endl
         << LAYER << std::endl
         << 10 << std::endl
         << point.x << std::endl
         << 20 << std::endl
         << point.y << std::endl
         << 0 << std::endl
         << "ENDSEC" << std::endl;
    ;
  }

  static void writeTable(std::ofstream &file) {
    file << 0 << std::endl
         << "SECTION" << std::endl
         << 2 << std::endl
         << "TABLES" << std::endl
         << 0 << std::endl
         << "TABLE" << std::endl
         << 2 << std::endl
         << "LAYER" << std::endl
         << 70 << std::endl
         << 6 << std::endl
         << 0 << std::endl
         << "LAYER" << std::endl
         << 2 << std::endl
         << LAYER << std::endl
         << 70 << std::endl
         << 64 << std::endl
         << 62 << std::endl
         << 7 << std::endl
         << 6 << std::endl
         << "CONTINUOUS" << std::endl
         << 0 << std::endl
         << "ENDTAB" << std::endl
         << 0 << std::endl
         << "ENDSEC" << std::endl
         << std::endl;
  }
};

#endif // VULCAD_DRAW_DXF_DXF
