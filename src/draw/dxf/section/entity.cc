#if !defined(VULCAD_DRAW_DXF_SECTION_ENTITY)
#define VULCAD_DRAW_DXF_SECTION_ENTITY

#include "../../../types.cc"
#include "../util/hex.cc"
#include "section.cc"

constexpr int LAYER = 0;

class Entity : public Section {
public:
  static void write(std::ofstream &file, std::vector<Shape> shapes) {
    begin(file, "ENTITIES");
    for (int i = 0; i < shapes.size(); i++) {
      auto &shape = shapes[i];
      if (std::holds_alternative<Point>(shape))
        Entity::addPoint(file, std::get<Point>(shape), i);
      else if (std::holds_alternative<Line>(shape))
        Entity::addLine(file, std::get<Line>(shape), i);
      else if (std::holds_alternative<Circle>(shape))
        Entity::addCircle(file, std::get<Circle>(shape), i);
      else if (std::holds_alternative<Bezier>(shape))
        Entity::addBezier(file, std::get<Bezier>(shape), i);
      else if (std::holds_alternative<Spline>(shape))
        Entity::addSpline(file, std::get<Spline>(shape), i);
    }
    end(file);
  }

private:
  static void addBezier(std::ofstream &file, Bezier &bezier, int index) {
    // not supported
  }

  static void addCircle(std::ofstream &file, Circle &circle, int index) {
    file << "  0" << std::endl << "CIRCLE" << std::endl;
    addCommonCodes(file, index);
    file << "100" << std::endl
         << "AcDbCircle" << std::endl
         << " 10" << std::endl
         << circle.origin.x << std::endl
         << " 20" << std::endl
         << circle.origin.y << std::endl
         << " 40" << std::endl
         << circle.radius << std::endl;
    ;
  }

  static void addLine(std::ofstream &file, Line &line, int index) {
    file << "  0" << std::endl << "LINE" << std::endl;
    addCommonCodes(file, index);
    file << "100" << std::endl
         << "AcDbLine" << std::endl
         << " 10" << std::endl
         << line.origin.x << std::endl
         << " 20" << std::endl
         << line.origin.y << std::endl
         << " 11" << std::endl
         << line.end.x << std::endl
         << " 21" << std::endl
         << line.end.y << std::endl;
    ;
  }

  static void addPoint(std::ofstream &file, Point &point, int index) {
    file << "  0" << std::endl << "POINT" << std::endl;
    addCommonCodes(file, index);
    file << "100" << std::endl
         << "AcDbPoint" << std::endl
         << " 10" << std::endl
         << point.x << std::endl
         << " 20" << std::endl
         << point.y << std::endl;
    ;
  }

  static void addSpline(std::ofstream &file, Spline &spline, int index) {
    file << "  0" << std::endl << "SPLINE" << std::endl;
    addCommonCodes(file, index);
    file << "100" << std::endl
         << "AcDbSpline" << std::endl
         << "210" << std::endl
         << "0" << std::endl
         << "220" << std::endl
         << "0" << std::endl
         << "230" << std::endl
         << "0" << std::endl
         << " 70" << std::endl
         << "  1064" << std::endl
         << " 71" << std::endl
         << "     3" << std::endl
         << " 74" << std::endl
         << spline.points.size() << std::endl;

    for (auto &p : spline.points) {
      file << " 11" << std::endl
           << p.x << std::endl
           << " 21" << std::endl
           << p.y << std::endl;
    }
  }

  static void addCommonCodes(std::ofstream &file, int index) {
    // starts from 2A0
    index += 16 * 16 * 2 + 16 * 10;
    file << "  5" << std::endl
         << Hex::from(index) << std::endl
         << "330" << std::endl
         << "1F" << std::endl
         << "100" << std::endl
         << "AcDbEntity" << std::endl
         << "  8" << std::endl
         << "0" << std::endl;
  }
};

#endif // VULCAD_DRAW_DXF_SECTION_ENTITY
