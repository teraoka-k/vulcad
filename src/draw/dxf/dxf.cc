#if !defined(VULCAD_DRAW_DXF_DXF)
#define VULCAD_DRAW_DXF_DXF

#include "../../types.cc"
#include "section/entity.cc"
#include "section/header.cc"
#include "section/object.cc"
#include <fstream>
#include <iostream>

const std::string OUT_DIR = "dxf/";

/**
 * save drawing as dxf file
 * look at dxf specification for detail
 * https://images.autodesk.com/adsk/files/autocad_2012_pdf_dxf-reference_enu.pdf
 */
class Dxf {
public:
  /**
   * following shapes are not supported
   * - bezier: skip drawing
   * - polyline: converto to spline
   * - polygone: convert to circle
   */
  static void write(std::string fileName, std::vector<Shape> shapes) {
    std::ofstream file(OUT_DIR + fileName + ".dxf");
    Header::write(file, shapes.size());
    Entity::write(file, shapes);
    Object::write(file);
    file << "  0" << std::endl << "EOF" << std::endl;
    file.close();
  }
};

#endif // VULCAD_DRAW_DXF_DXF
