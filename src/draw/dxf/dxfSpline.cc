#if !defined(VULCAD_DRAW_DXF_DXFSPLINE)
#define VULCAD_DRAW_DXF_DXFSPLINE

#include "../shapes/spline.cc"
#include <fstream>

class DxfSpline {

public:
  static void write(std::ofstream &file, Spline &spline) {
    DxfSpline::writeTables(file);
    DxfSpline::writeSpline(file, spline);
    DxfSpline::writeObjects(file);
  }

private:
  static void writeObjects(std::ofstream &file) {
    file << "  0" << std::endl
         << "SECTION" << std::endl
         << "  2" << std::endl
         << "OBJECTS" << std::endl
         << "  0" << std::endl
         << "DICTIONARY" << std::endl
         << "  5" << std::endl
         << "200" << std::endl
         << "330" << std::endl
         << "1FF" << std::endl
         << "100" << std::endl
         << "AcDbDictionary" << std::endl
         << "281" << std::endl
         << "     1" << std::endl
         << "  0" << std::endl
         << "ACDBDETAILVIEWSTYLE" << std::endl
         << "  5" << std::endl
         << "21C" << std::endl
         << "330" << std::endl
         << "21B" << std::endl
         << "100" << std::endl
         << "AcDbModelDocViewStyle" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "  3" << std::endl
         << "Metric50" << std::endl
         << "290" << std::endl
         << "     0" << std::endl
         << "300" << std::endl
         << "Metric50" << std::endl
         << " 90" << std::endl
         << "        0" << std::endl
         << "100" << std::endl
         << "AcDbDetailViewStyle" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << " 71" << std::endl
         << "     0" << std::endl
         << " 90" << std::endl
         << "        3" << std::endl
         << " 71" << std::endl
         << "     1" << std::endl
         << "340" << std::endl
         << "11" << std::endl
         << " 62" << std::endl
         << "   256" << std::endl
         << " 40" << std::endl
         << "5.0" << std::endl
         << "340" << std::endl
         << "0" << std::endl
         << " 62" << std::endl
         << "   256" << std::endl
         << " 40" << std::endl
         << "5.0" << std::endl
         << "300" << std::endl
         << std::endl
         << " 40" << std::endl
         << "0.0" << std::endl
         << "280" << std::endl
         << "     1" << std::endl
         << " 71" << std::endl
         << "     2" << std::endl
         << "340" << std::endl
         << "16" << std::endl
         << " 90" << std::endl
         << "       25" << std::endl
         << " 62" << std::endl
         << "   256" << std::endl
         << " 71" << std::endl
         << "     3" << std::endl
         << "340" << std::endl
         << "11" << std::endl
         << " 62" << std::endl
         << "   256" << std::endl
         << " 40" << std::endl
         << "5.0" << std::endl
         << " 90" << std::endl
         << "        0" << std::endl
         << " 40" << std::endl
         << "15.0" << std::endl
         << " 90" << std::endl
         << "        1" << std::endl
         << "300" << std::endl
         << "%<\\AcVar ViewDetailId>% (%<\\AcVar ViewScale \\f \"%sn\">%)"
         << std::endl
         << " 71" << std::endl
         << "     4" << std::endl
         << "340" << std::endl
         << "16" << std::endl
         << " 90" << std::endl
         << "       25" << std::endl
         << " 62" << std::endl
         << "   256" << std::endl
         << "340" << std::endl
         << "16" << std::endl
         << " 90" << std::endl
         << "       25" << std::endl
         << " 62" << std::endl
         << "   256" << std::endl
         << "280" << std::endl
         << "     0" << std::endl
         << "  0" << std::endl
         << "LAYOUT" << std::endl
         << "  5" << std::endl
         << "D3" << std::endl
         << "330" << std::endl
         << "1A" << std::endl
         << "100" << std::endl
         << "AcDbPlotSettings" << std::endl
         << "  1" << std::endl
         << std::endl
         << "  2" << std::endl
         << "none" << std::endl
         << "  4" << std::endl
         << std::endl
         << "  6" << std::endl
         << std::endl
         << " 40" << std::endl
         << "0.0" << std::endl
         << " 41" << std::endl
         << "0.0" << std::endl
         << " 42" << std::endl
         << "0.0" << std::endl
         << " 43" << std::endl
         << "0.0" << std::endl
         << " 44" << std::endl
         << "0.0" << std::endl
         << " 45" << std::endl
         << "0.0" << std::endl
         << " 46" << std::endl
         << "0.0" << std::endl
         << " 47" << std::endl
         << "0.0" << std::endl
         << " 48" << std::endl
         << "0.0" << std::endl
         << " 49" << std::endl
         << "0.0" << std::endl
         << "140" << std::endl
         << "0.0" << std::endl
         << "141" << std::endl
         << "0.0" << std::endl
         << "142" << std::endl
         << "1.0" << std::endl
         << "143" << std::endl
         << "1.0" << std::endl
         << " 70" << std::endl
         << "   688" << std::endl
         << " 72" << std::endl
         << "     0" << std::endl
         << " 73" << std::endl
         << "     0" << std::endl
         << " 74" << std::endl
         << "     5" << std::endl
         << "  7" << std::endl
         << std::endl
         << " 75" << std::endl
         << "    16" << std::endl
         << "147" << std::endl
         << "1.0" << std::endl
         << " 76" << std::endl
         << "     0" << std::endl
         << " 77" << std::endl
         << "     2" << std::endl
         << " 78" << std::endl
         << "   300" << std::endl
         << "148" << std::endl
         << "0.0" << std::endl
         << "149" << std::endl
         << "0.0" << std::endl
         << "100" << std::endl
         << "AcDbLayout" << std::endl
         << "  1" << std::endl
         << "Layout1" << std::endl
         << " 70" << std::endl
         << "     1" << std::endl
         << " 71" << std::endl
         << "     1" << std::endl
         << " 10" << std::endl
         << "0.0" << std::endl
         << " 20" << std::endl
         << "0.0" << std::endl
         << " 11" << std::endl
         << "12.0" << std::endl
         << " 21" << std::endl
         << "9.0" << std::endl
         << " 12" << std::endl
         << "0.0" << std::endl
         << " 22" << std::endl
         << "0.0" << std::endl
         << " 32" << std::endl
         << "0.0" << std::endl
         << " 14" << std::endl
         << "0.0" << std::endl
         << " 24" << std::endl
         << "0.0" << std::endl
         << " 34" << std::endl
         << "0.0" << std::endl
         << " 15" << std::endl
         << "0.0" << std::endl
         << " 25" << std::endl
         << "0.0" << std::endl
         << " 35" << std::endl
         << "0.0" << std::endl
         << "146" << std::endl
         << "0.0" << std::endl
         << " 13" << std::endl
         << "0.0" << std::endl
         << " 23" << std::endl
         << "0.0" << std::endl
         << " 33" << std::endl
         << "0.0" << std::endl
         << " 16" << std::endl
         << "1.0" << std::endl
         << " 26" << std::endl
         << "0.0" << std::endl
         << " 36" << std::endl
         << "0.0" << std::endl
         << " 17" << std::endl
         << "0.0" << std::endl
         << " 27" << std::endl
         << "1.0" << std::endl
         << " 37" << std::endl
         << "0.0" << std::endl
         << " 76" << std::endl
         << "     0" << std::endl
         << "330" << std::endl
         << "D2" << std::endl
         << "  0" << std::endl
         << "LAYOUT" << std::endl
         << "  5" << std::endl
         << "D7" << std::endl
         << "330" << std::endl
         << "1A" << std::endl
         << "100" << std::endl
         << "AcDbPlotSettings" << std::endl
         << "  1" << std::endl
         << std::endl
         << "  4" << std::endl
         << std::endl
         << "  6" << std::endl
         << std::endl
         << " 40" << std::endl
         << "0.0" << std::endl
         << " 41" << std::endl
         << "0.0" << std::endl
         << " 42" << std::endl
         << "0.0" << std::endl
         << " 43" << std::endl
         << "0.0" << std::endl
         << " 44" << std::endl
         << "0.0" << std::endl
         << " 45" << std::endl
         << "0.0" << std::endl
         << " 46" << std::endl
         << "0.0" << std::endl
         << " 47" << std::endl
         << "0.0" << std::endl
         << " 48" << std::endl
         << "0.0" << std::endl
         << " 49" << std::endl
         << "0.0" << std::endl
         << "140" << std::endl
         << "0.0" << std::endl
         << "141" << std::endl
         << "0.0" << std::endl
         << "142" << std::endl
         << "1.0" << std::endl
         << "143" << std::endl
         << "1.0" << std::endl
         << " 70" << std::endl
         << "   688" << std::endl
         << " 72" << std::endl
         << "     0" << std::endl
         << " 73" << std::endl
         << "     0" << std::endl
         << " 74" << std::endl
         << "     5" << std::endl
         << "  7" << std::endl
         << std::endl
         << " 75" << std::endl
         << "    16" << std::endl
         << "147" << std::endl
         << "1.0" << std::endl
         << " 76" << std::endl
         << "     0" << std::endl
         << " 77" << std::endl
         << "     2" << std::endl
         << " 78" << std::endl
         << "   300" << std::endl
         << "148" << std::endl
         << "0.0" << std::endl
         << "149" << std::endl
         << "0.0" << std::endl
         << "100" << std::endl
         << "AcDbLayout" << std::endl
         << "  1" << std::endl
         << "Layout2" << std::endl
         << " 70" << std::endl
         << "     1" << std::endl
         << " 71" << std::endl
         << "     2" << std::endl
         << " 10" << std::endl
         << "0.0" << std::endl
         << " 20" << std::endl
         << "0.0" << std::endl
         << " 11" << std::endl
         << "12.0" << std::endl
         << " 21" << std::endl
         << "9.0" << std::endl
         << " 12" << std::endl
         << "0.0" << std::endl
         << " 22" << std::endl
         << "0.0" << std::endl
         << " 32" << std::endl
         << "0.0" << std::endl
         << " 14" << std::endl
         << "0.0" << std::endl
         << " 24" << std::endl
         << "0.0" << std::endl
         << " 34" << std::endl
         << "0.0" << std::endl
         << " 15" << std::endl
         << "0.0" << std::endl
         << " 25" << std::endl
         << "0.0" << std::endl
         << " 35" << std::endl
         << "0.0" << std::endl
         << "146" << std::endl
         << "0.0" << std::endl
         << " 13" << std::endl
         << "0.0" << std::endl
         << " 23" << std::endl
         << "0.0" << std::endl
         << " 33" << std::endl
         << "0.0" << std::endl
         << " 16" << std::endl
         << "1.0" << std::endl
         << " 26" << std::endl
         << "0.0" << std::endl
         << " 36" << std::endl
         << "0.0" << std::endl
         << " 17" << std::endl
         << "0.0" << std::endl
         << " 27" << std::endl
         << "1.0" << std::endl
         << " 37" << std::endl
         << "0.0" << std::endl
         << " 76" << std::endl
         << "     0" << std::endl
         << "330" << std::endl
         << "D6" << std::endl
         << "  0" << std::endl
         << "LAYOUT" << std::endl
         << "  5" << std::endl
         << "22" << std::endl
         << "330" << std::endl
         << "1A" << std::endl
         << "100" << std::endl
         << "AcDbPlotSettings" << std::endl
         << "  1" << std::endl
         << std::endl
         << "  2" << std::endl
         << "none_device" << std::endl
         << "  4" << std::endl
         << "ISO_A4_(210.00_x_297.00_MM)" << std::endl
         << "  6" << std::endl
         << std::endl
         << " 40" << std::endl
         << "7.5" << std::endl
         << " 41" << std::endl
         << "20.0" << std::endl
         << " 42" << std::endl
         << "7.5" << std::endl
         << " 43" << std::endl
         << "20.0" << std::endl
         << " 44" << std::endl
         << "210.0" << std::endl
         << " 45" << std::endl
         << "297.0" << std::endl
         << " 46" << std::endl
         << "11.54999923706054" << std::endl
         << " 47" << std::endl
         << "-13.65000009536743" << std::endl
         << " 48" << std::endl
         << "0.0" << std::endl
         << " 49" << std::endl
         << "0.0" << std::endl
         << "140" << std::endl
         << "0.0" << std::endl
         << "141" << std::endl
         << "0.0" << std::endl
         << "142" << std::endl
         << "1.0" << std::endl
         << "143" << std::endl
         << "8.704084754739808" << std::endl
         << " 70" << std::endl
         << " 11952" << std::endl
         << " 72" << std::endl
         << "     1" << std::endl
         << " 73" << std::endl
         << "     0" << std::endl
         << " 74" << std::endl
         << "     0" << std::endl
         << "  7" << std::endl
         << std::endl
         << " 75" << std::endl
         << "     0" << std::endl
         << "147" << std::endl
         << "0.1148885871608098" << std::endl
         << " 76" << std::endl
         << "     0" << std::endl
         << " 77" << std::endl
         << "     2" << std::endl
         << " 78" << std::endl
         << "   300" << std::endl
         << "148" << std::endl
         << "0.0" << std::endl
         << "149" << std::endl
         << "0.0" << std::endl
         << "100" << std::endl
         << "AcDbLayout" << std::endl
         << "  1" << std::endl
         << "Model" << std::endl
         << " 70" << std::endl
         << "     1" << std::endl
         << " 71" << std::endl
         << "     0" << std::endl
         << " 10" << std::endl
         << "0.0" << std::endl
         << " 20" << std::endl
         << "0.0" << std::endl
         << " 11" << std::endl
         << "12.0" << std::endl
         << " 21" << std::endl
         << "9.0" << std::endl
         << " 12" << std::endl
         << "0.0" << std::endl
         << " 22" << std::endl
         << "0.0" << std::endl
         << " 32" << std::endl
         << "0.0" << std::endl
         << " 14" << std::endl
         << "0.0" << std::endl
         << " 24" << std::endl
         << "0.0" << std::endl
         << " 34" << std::endl
         << "0.0" << std::endl
         << " 15" << std::endl
         << "0.0" << std::endl
         << " 25" << std::endl
         << "0.0" << std::endl
         << " 35" << std::endl
         << "0.0" << std::endl
         << "146" << std::endl
         << "0.0" << std::endl
         << " 13" << std::endl
         << "0.0" << std::endl
         << " 23" << std::endl
         << "0.0" << std::endl
         << " 33" << std::endl
         << "0.0" << std::endl
         << " 16" << std::endl
         << "1.0" << std::endl
         << " 26" << std::endl
         << "0.0" << std::endl
         << " 36" << std::endl
         << "0.0" << std::endl
         << " 17" << std::endl
         << "0.0" << std::endl
         << " 27" << std::endl
         << "1.0" << std::endl
         << " 37" << std::endl
         << "0.0" << std::endl
         << " 76" << std::endl
         << "     0" << std::endl
         << "330" << std::endl
         << "1F" << std::endl
         << "331" << std::endl
         << "EA" << std::endl
         << "1001" << std::endl
         << "ACAD_PSEXT" << std::endl
         << "1000" << std::endl
         << "None" << std::endl
         << "1000" << std::endl
         << "None" << std::endl
         << "1000" << std::endl
         << "Not applicable" << std::endl
         << "1000" << std::endl
         << "The layout will not be plotted unless a new plotter "
            "configuration "
            "name is selected."
         << std::endl
         << "1070" << std::endl
         << "     0" << std::endl
         << "  0" << std::endl
         << "ENDSEC" << std::endl
         << "  0" << std::endl
         << "SECTION" << std::endl
         << "  2" << std::endl
         << "ACDSDATA" << std::endl
         << " 70" << std::endl
         << "     2" << std::endl
         << " 71" << std::endl
         << "     8" << std::endl
         << "  0" << std::endl
         << "ACDSSCHEMA" << std::endl
         << " 90" << std::endl
         << "        0" << std::endl
         << "  1" << std::endl
         << "AcDb_Thumbnail_Schema" << std::endl
         << "  2" << std::endl
         << "AcDbDs::ID" << std::endl
         << "280" << std::endl
         << "    10" << std::endl
         << " 91" << std::endl
         << "        8" << std::endl
         << "  2" << std::endl
         << "Thumbnail_Data" << std::endl
         << "280" << std::endl
         << "    15" << std::endl
         << " 91" << std::endl
         << "        0" << std::endl
         << "101" << std::endl
         << "ACDSRECORD" << std::endl
         << " 95" << std::endl
         << "        0" << std::endl
         << " 90" << std::endl
         << "        1" << std::endl
         << "  2" << std::endl
         << "AcDbDs::TreatedAsObjectData" << std::endl
         << "280" << std::endl
         << "     1" << std::endl
         << "291" << std::endl
         << "     1" << std::endl
         << "101" << std::endl
         << "ACDSRECORD" << std::endl
         << " 95" << std::endl
         << "        0" << std::endl
         << " 90" << std::endl
         << "        2" << std::endl
         << "  2" << std::endl
         << "AcDbDs::Legacy" << std::endl
         << "280" << std::endl
         << "     1" << std::endl
         << "291" << std::endl
         << "     1" << std::endl
         << "101" << std::endl
         << "ACDSRECORD" << std::endl
         << "  1" << std::endl
         << "AcDbDs::ID" << std::endl
         << " 90" << std::endl
         << "        3" << std::endl
         << "  2" << std::endl
         << "AcDs:Indexable" << std::endl
         << "280" << std::endl
         << "     1" << std::endl
         << "291" << std::endl
         << "     1" << std::endl
         << "101" << std::endl
         << "ACDSRECORD" << std::endl
         << "  1" << std::endl
         << "AcDbDs::ID" << std::endl
         << " 90" << std::endl
         << "        4" << std::endl
         << "  2" << std::endl
         << "AcDbDs::HandleAttribute" << std::endl
         << "280" << std::endl
         << "     7" << std::endl
         << "282" << std::endl
         << "     1" << std::endl
         << "  0" << std::endl
         << "ACDSSCHEMA" << std::endl
         << " 90" << std::endl
         << "        1" << std::endl
         << "  1" << std::endl
         << "AcDbDs::TreatedAsObjectDataSchema" << std::endl
         << "  2" << std::endl
         << "AcDbDs::TreatedAsObjectData" << std::endl
         << "280" << std::endl
         << "     1" << std::endl
         << " 91" << std::endl
         << "        0" << std::endl
         << "  0" << std::endl
         << "ACDSSCHEMA" << std::endl
         << " 90" << std::endl
         << "        2" << std::endl
         << "  1" << std::endl
         << "AcDbDs::LegacySchema" << std::endl
         << "  2" << std::endl
         << "AcDbDs::Legacy" << std::endl
         << "280" << std::endl
         << "     1" << std::endl
         << " 91" << std::endl
         << "        0" << std::endl
         << "  0" << std::endl
         << "ACDSSCHEMA" << std::endl
         << " 90" << std::endl
         << "        3" << std::endl
         << "  1" << std::endl
         << "AcDbDs::IndexedPropertySchema" << std::endl
         << "  2" << std::endl
         << "AcDs:Indexable" << std::endl
         << "280" << std::endl
         << "     1" << std::endl
         << " 91" << std::endl
         << "        0" << std::endl
         << "  0" << std::endl
         << "ACDSSCHEMA" << std::endl
         << " 90" << std::endl
         << "        4" << std::endl
         << "  1" << std::endl
         << "AcDbDs::HandleAttributeSchema" << std::endl
         << "  2" << std::endl
         << "AcDbDs::HandleAttribute" << std::endl
         << "280" << std::endl
         << "     7" << std::endl
         << " 91" << std::endl
         << "        1" << std::endl
         << "284" << std::endl
         << "     1" << std::endl
         << "  0" << std::endl
         << "ACDSRECORD" << std::endl
         << " 90" << std::endl
         << "        0" << std::endl
         << "  2" << std::endl
         << "AcDbDs::ID" << std::endl
         << "280" << std::endl
         << "    10" << std::endl
         << "320" << std::endl
         << "22" << std::endl
         << "  2" << std::endl
         << "Thumbnail_Data" << std::endl
         << "280" << std::endl
         << "    15" << std::endl
         << " 94" << std::endl
         << "      896" << std::endl
         << "310" << std::endl
         << "89504E470D0A1A0A0000000D49484452000001000000009108030000001BE19"
            "60600"
            "000300504C5445212830FFFFFF2128300000000000000000000000000000000"
            "00000"
            "0000000000000000330000660000990000CC0000FF003300003333003366003"
            "39900"
            "33CC0033FF0066000066330066660066990066CC0066FF0099"
         << std::endl
         << "310" << std::endl
         << "000099330099660099990099CC0099FF00CC0000CC3300CC6600CC9900CCCC0"
            "0CCFF"
            "00FF0000FF3300FF6600FF9900FFCC00FFFF330000330033330066330099330"
            "0CC33"
            "00FF3333003333333333663333993333CC3333FF33660033663333666633669"
            "93366"
            "CC3366FF3399003399333399663399993399CC3399FF33CC00"
         << std::endl
         << "310" << std::endl
         << "33CC3333CC6633CC9933CCCC33CCFF33FF0033FF3333FF6633FF9933FFCC33F"
            "FFF66"
            "00006600336600666600996600CC6600FF6633006633336633666633996633C"
            "C6633"
            "FF6666006666336666666666996666CC6666FF6699006699336699666699996"
            "699CC"
            "6699FF66CC0066CC3366CC6666CC9966CCCC66CCFF66FF0066"
         << std::endl
         << "310" << std::endl
         << "FF3366FF6666FF9966FFCC66FFFF9900009900339900669900999900CC9900F"
            "F9933"
            "009933339933669933999933CC9933FF9966009966339966669966999966CC9"
            "966FF"
            "9999009999339999669999999999CC9999FF99CC0099CC3399CC6699CC9999C"
            "CCC99"
            "CCFF99FF0099FF3399FF6699FF9999FFCC99FFFFCC0000CC00"
         << std::endl
         << "310" << std::endl
         << "33CC0066CC0099CC00CCCC00FFCC3300CC3333CC3366CC3399CC33CCCC33FFC"
            "C6600"
            "CC6633CC6666CC6699CC66CCCC66FFCC9900CC9933CC9966CC9999CC99CCCC9"
            "9FFCC"
            "CC00CCCC33CCCC66CCCC99CCCCCCCCCCFFCCFF00CCFF33CCFF66CCFF99CCFFC"
            "CCCFF"
            "FFFF0000FF0033FF0066FF0099FF00CCFF00FFFF3300FF3333"
         << std::endl
         << "310" << std::endl
         << "FF3366FF3399FF33CCFF33FFFF6600FF6633FF6666FF6699FF66CCFF66FFFF9"
            "900FF"
            "9933FF9966FF9999FF99CCFF99FFFFCC00FFCC33FFCC66FFCC99FFCCCCFFCCF"
            "FFFFF"
            "00FFFF33FFFF66FFFF99FFFFCCFFFFFF0000000D0D0D1A1A1A2828283535354"
            "34343"
            "5050505D5D5D6B6B6B787878868686939393A1A1A1AEAEAEBB"
         << std::endl
         << "310" << std::endl
         << "BBBBC9C9C9D6D6D6E4E4E4F1F1F1FFFFFF00000000000000000000000000000"
            "00000"
            "000000000000000000000000002E4550F10000003B4944415478DAEDC131010"
            "00000"
            "C2A0F54F6D0B2FA000000000000000000000000000000000000000000000000"
            "00000"
            "00000000000000000000CE06919100016C9A5B1B0000000049"
         << std::endl
         << "310" << std::endl
         << "454E44AE426082" << std::endl
         << "  0" << std::endl
         << "ENDSEC" << std::endl;
  }

  static void writeSpline(std::ofstream &file, Spline &spline) {
    file << "  0" << std::endl
         << "SECTION" << std::endl
         << "  2" << std::endl
         << "ENTITIES" << std::endl
         << "  0" << std::endl
         << "SPLINE" << std::endl
         << "  5" << std::endl
         << "2A0" << std::endl
         << "330" << std::endl
         << "1F" << std::endl
         << "100" << std::endl
         << "AcDbEntity" << std::endl
         << "  8" << std::endl
         << "0" << std::endl
         << "100" << std::endl
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
    file << "  0" << std::endl << "ENDSEC" << std::endl;
  }

  static void writeTables(std::ofstream &file) {
    file << "  0" << std::endl
         << "SECTION" << std::endl
         << "  2" << std::endl
         << "HEADER" << std::endl
         << "  9" << std::endl
         << "$ACADVER" << std::endl
         << "  1" << std::endl
         << "AC1032" << std::endl
         << "  9" << std::endl
         << "$HANDSEED" << std::endl
         << "  5" << std::endl
         << "2A3" << std::endl
         << "  0" << std::endl
         << "ENDSEC" << std::endl
         << "  0" << std::endl
         << "SECTION" << std::endl
         << "  2" << std::endl
         << "TABLES" << std::endl
         << "  0" << std::endl
         << "TABLE" << std::endl
         << "  2" << std::endl
         << "VPORT" << std::endl
         << "  5" << std::endl
         << "8" << std::endl
         << "330" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTable" << std::endl
         << " 70" << std::endl
         << "     1" << std::endl
         << "  0" << std::endl
         << "VPORT" << std::endl
         << "  5" << std::endl
         << "EA" << std::endl
         << "330" << std::endl
         << "8" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbViewportTableRecord" << std::endl
         << "  2" << std::endl
         << "*Active" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << " 10" << std::endl
         << "0.0" << std::endl
         << " 20" << std::endl
         << "0.0" << std::endl
         << " 11" << std::endl
         << "1.0" << std::endl
         << " 21" << std::endl
         << "1.0" << std::endl
         << " 12" << std::endl
         << "2630.048781668382" << std::endl
         << " 22" << std::endl
         << "1777.370161854362" << std::endl
         << " 13" << std::endl
         << "0.0" << std::endl
         << " 23" << std::endl
         << "0.0" << std::endl
         << " 14" << std::endl
         << "10.0" << std::endl
         << " 24" << std::endl
         << "10.0" << std::endl
         << " 15" << std::endl
         << "10.0" << std::endl
         << " 25" << std::endl
         << "10.0" << std::endl
         << " 16" << std::endl
         << "0.0" << std::endl
         << " 26" << std::endl
         << "0.0" << std::endl
         << " 36" << std::endl
         << "1.0" << std::endl
         << " 17" << std::endl
         << "0.0" << std::endl
         << " 27" << std::endl
         << "0.0" << std::endl
         << " 37" << std::endl
         << "0.0" << std::endl
         << " 40" << std::endl
         << "2787.3330168711" << std::endl
         << " 41" << std::endl
         << "1.675847457627118" << std::endl
         << " 42" << std::endl
         << "50.0" << std::endl
         << " 43" << std::endl
         << "0.0" << std::endl
         << " 44" << std::endl
         << "0.0" << std::endl
         << " 50" << std::endl
         << "0.0" << std::endl
         << " 51" << std::endl
         << "0.0" << std::endl
         << " 71" << std::endl
         << "     0" << std::endl
         << " 72" << std::endl
         << "  1000" << std::endl
         << " 73" << std::endl
         << "     1" << std::endl
         << " 74" << std::endl
         << "     3" << std::endl
         << " 75" << std::endl
         << "     0" << std::endl
         << " 76" << std::endl
         << "     1" << std::endl
         << " 77" << std::endl
         << "     0" << std::endl
         << " 78" << std::endl
         << "     0" << std::endl
         << "281" << std::endl
         << "     0" << std::endl
         << " 65" << std::endl
         << "     1" << std::endl
         << "110" << std::endl
         << "0.0" << std::endl
         << "120" << std::endl
         << "0.0" << std::endl
         << "130" << std::endl
         << "0.0" << std::endl
         << "111" << std::endl
         << "1.0" << std::endl
         << "121" << std::endl
         << "0.0" << std::endl
         << "131" << std::endl
         << "0.0" << std::endl
         << "112" << std::endl
         << "0.0" << std::endl
         << "122" << std::endl
         << "1.0" << std::endl
         << "132" << std::endl
         << "0.0" << std::endl
         << " 79" << std::endl
         << "     0" << std::endl
         << "146" << std::endl
         << "0.0" << std::endl
         << "348" << std::endl
         << "F5" << std::endl
         << " 60" << std::endl
         << "     3" << std::endl
         << " 61" << std::endl
         << "     5" << std::endl
         << "292" << std::endl
         << "     1" << std::endl
         << "282" << std::endl
         << "     1" << std::endl
         << "141" << std::endl
         << "0.0" << std::endl
         << "142" << std::endl
         << "0.0" << std::endl
         << " 63" << std::endl
         << "   250" << std::endl
         << "421" << std::endl
         << "  3355443" << std::endl
         << "1001" << std::endl
         << "ACAD_NAV_VCDISPLAY" << std::endl
         << "1070" << std::endl
         << "     3" << std::endl
         << "  0" << std::endl
         << "ENDTAB" << std::endl
         << "  0" << std::endl
         << "TABLE" << std::endl
         << "  2" << std::endl
         << "LTYPE" << std::endl
         << "  5" << std::endl
         << "5" << std::endl
         << "330" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTable" << std::endl
         << " 70" << std::endl
         << "     1" << std::endl
         << "  0" << std::endl
         << "LTYPE" << std::endl
         << "  5" << std::endl
         << "14" << std::endl
         << "330" << std::endl
         << "5" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbLinetypeTableRecord" << std::endl
         << "  2" << std::endl
         << "ByBlock" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "  3" << std::endl
         << std::endl
         << " 72" << std::endl
         << "    65" << std::endl
         << " 73" << std::endl
         << "     0" << std::endl
         << " 40" << std::endl
         << "0.0" << std::endl
         << "  0" << std::endl
         << "LTYPE" << std::endl
         << "  5" << std::endl
         << "15" << std::endl
         << "330" << std::endl
         << "5" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbLinetypeTableRecord" << std::endl
         << "  2" << std::endl
         << "ByLayer" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "  3" << std::endl
         << std::endl
         << " 72" << std::endl
         << "    65" << std::endl
         << " 73" << std::endl
         << "     0" << std::endl
         << " 40" << std::endl
         << "0.0" << std::endl
         << "  0" << std::endl
         << "ENDTAB" << std::endl
         << "  0" << std::endl
         << "TABLE" << std::endl
         << "  2" << std::endl
         << "LAYER" << std::endl
         << "  5" << std::endl
         << "2" << std::endl
         << "330" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTable" << std::endl
         << " 70" << std::endl
         << "     1" << std::endl
         << "  0" << std::endl
         << "LAYER" << std::endl
         << "  5" << std::endl
         << "10" << std::endl
         << "330" << std::endl
         << "2" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbLayerTableRecord" << std::endl
         << "  2" << std::endl
         << "0" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << " 62" << std::endl
         << "     7" << std::endl
         << "  6" << std::endl
         << "Continuous" << std::endl
         << "370" << std::endl
         << "    -3" << std::endl
         << "390" << std::endl
         << "F" << std::endl
         << "347" << std::endl
         << "EE" << std::endl
         << "348" << std::endl
         << "0" << std::endl
         << "  0" << std::endl
         << "ENDTAB" << std::endl
         << "  0" << std::endl
         << "TABLE" << std::endl
         << "  2" << std::endl
         << "STYLE" << std::endl
         << "  5" << std::endl
         << "3" << std::endl
         << "330" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTable" << std::endl
         << " 70" << std::endl
         << "     2" << std::endl
         << "  0" << std::endl
         << "STYLE" << std::endl
         << "  5" << std::endl
         << "132" << std::endl
         << "330" << std::endl
         << "3" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbTextStyleTableRecord" << std::endl
         << "  2" << std::endl
         << "Annotative" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << " 40" << std::endl
         << "0.0" << std::endl
         << " 41" << std::endl
         << "1.0" << std::endl
         << " 50" << std::endl
         << "0.0" << std::endl
         << " 71" << std::endl
         << "     0" << std::endl
         << " 42" << std::endl
         << "2.5" << std::endl
         << "  3" << std::endl
         << "arial.ttf" << std::endl
         << "  4" << std::endl
         << std::endl
         << "1001" << std::endl
         << "AcadAnnotative" << std::endl
         << "1000" << std::endl
         << "AnnotativeData" << std::endl
         << "1002" << std::endl
         << "{" << std::endl
         << "1070" << std::endl
         << "     1" << std::endl
         << "1070" << std::endl
         << "     1" << std::endl
         << "1002" << std::endl
         << "}" << std::endl
         << "1001" << std::endl
         << "ACAD" << std::endl
         << "1000" << std::endl
         << "Arial" << std::endl
         << "1071" << std::endl
         << "       34" << std::endl
         << "  0" << std::endl
         << "ENDTAB" << std::endl
         << "  0" << std::endl
         << "TABLE" << std::endl
         << "  2" << std::endl
         << "VIEW" << std::endl
         << "  5" << std::endl
         << "6" << std::endl
         << "330" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTable" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "  0" << std::endl
         << "ENDTAB" << std::endl
         << "  0" << std::endl
         << "TABLE" << std::endl
         << "  2" << std::endl
         << "UCS" << std::endl
         << "  5" << std::endl
         << "7" << std::endl
         << "330" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTable" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "  0" << std::endl
         << "ENDTAB" << std::endl
         << "  0" << std::endl
         << "TABLE" << std::endl
         << "  2" << std::endl
         << "APPID" << std::endl
         << "  5" << std::endl
         << "9" << std::endl
         << "330" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTable" << std::endl
         << " 70" << std::endl
         << "     8" << std::endl
         << "  0" << std::endl
         << "APPID" << std::endl
         << "  5" << std::endl
         << "12" << std::endl
         << "330" << std::endl
         << "9" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbRegAppTableRecord" << std::endl
         << "  2" << std::endl
         << "ACAD" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "  0" << std::endl
         << "APPID" << std::endl
         << "  5" << std::endl
         << "9E" << std::endl
         << "330" << std::endl
         << "9" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbRegAppTableRecord" << std::endl
         << "  2" << std::endl
         << "ACAD_PSEXT" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "  0" << std::endl
         << "APPID" << std::endl
         << "  5" << std::endl
         << "134" << std::endl
         << "330" << std::endl
         << "9" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbRegAppTableRecord" << std::endl
         << "  2" << std::endl
         << "AcadAnnotative" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "  0" << std::endl
         << "APPID" << std::endl
         << "  5" << std::endl
         << "217" << std::endl
         << "330" << std::endl
         << "9" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbRegAppTableRecord" << std::endl
         << "  2" << std::endl
         << "ACAD_NAV_VCDISPLAY" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "  0" << std::endl
         << "ENDTAB" << std::endl
         << "  0" << std::endl
         << "TABLE" << std::endl
         << "  2" << std::endl
         << "DIMSTYLE" << std::endl
         << "  5" << std::endl
         << "A" << std::endl
         << "330" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTable" << std::endl
         << " 70" << std::endl
         << "     3" << std::endl
         << "100" << std::endl
         << "AcDbDimStyleTable" << std::endl
         << " 71" << std::endl
         << "     2" << std::endl
         << "340" << std::endl
         << "27" << std::endl
         << "340" << std::endl
         << "137" << std::endl
         << "  0" << std::endl
         << "DIMSTYLE" << std::endl
         << "105" << std::endl
         << "27" << std::endl
         << "330" << std::endl
         << "A" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbDimStyleTableRecord" << std::endl
         << "  2" << std::endl
         << "ISO-25" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << " 41" << std::endl
         << "2.5" << std::endl
         << " 42" << std::endl
         << "0.625" << std::endl
         << " 43" << std::endl
         << "3.75" << std::endl
         << " 44" << std::endl
         << "1.25" << std::endl
         << " 73" << std::endl
         << "     0" << std::endl
         << " 74" << std::endl
         << "     0" << std::endl
         << " 77" << std::endl
         << "     1" << std::endl
         << " 78" << std::endl
         << "     8" << std::endl
         << "140" << std::endl
         << "2.5" << std::endl
         << "141" << std::endl
         << "2.5" << std::endl
         << "143" << std::endl
         << "0.03937007874016" << std::endl
         << "147" << std::endl
         << "0.625" << std::endl
         << "171" << std::endl
         << "     3" << std::endl
         << "172" << std::endl
         << "     1" << std::endl
         << "271" << std::endl
         << "     2" << std::endl
         << "272" << std::endl
         << "     2" << std::endl
         << "274" << std::endl
         << "     3" << std::endl
         << "278" << std::endl
         << "    44" << std::endl
         << "283" << std::endl
         << "     0" << std::endl
         << "284" << std::endl
         << "     8" << std::endl
         << "340" << std::endl
         << "11" << std::endl
         << "  0" << std::endl
         << "ENDTAB" << std::endl
         << "  0" << std::endl
         << "TABLE" << std::endl
         << "  2" << std::endl
         << "BLOCK_RECORD" << std::endl
         << "  5" << std::endl
         << "1" << std::endl
         << "330" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTable" << std::endl
         << " 70" << std::endl
         << "     1" << std::endl
         << "  0" << std::endl
         << "BLOCK_RECORD" << std::endl
         << "  5" << std::endl
         << "1F" << std::endl
         << "330" << std::endl
         << "1" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbBlockTableRecord" << std::endl
         << "  2" << std::endl
         << "*Model_Space" << std::endl
         << "340" << std::endl
         << "22" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "280" << std::endl
         << "     1" << std::endl
         << "281" << std::endl
         << "     0" << std::endl
         << "  0" << std::endl
         << "BLOCK_RECORD" << std::endl
         << "  5" << std::endl
         << "D2" << std::endl
         << "330" << std::endl
         << "1" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbBlockTableRecord" << std::endl
         << "  2" << std::endl
         << "*Paper_Space" << std::endl
         << "340" << std::endl
         << "D3" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "280" << std::endl
         << "     1" << std::endl
         << "281" << std::endl
         << "     0" << std::endl
         << "  0" << std::endl
         << "BLOCK_RECORD" << std::endl
         << "  5" << std::endl
         << "D6" << std::endl
         << "330" << std::endl
         << "1" << std::endl
         << "100" << std::endl
         << "AcDbSymbolTableRecord" << std::endl
         << "100" << std::endl
         << "AcDbBlockTableRecord" << std::endl
         << "  2" << std::endl
         << "*Paper_Space0" << std::endl
         << "340" << std::endl
         << "D7" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << "280" << std::endl
         << "     1" << std::endl
         << "281" << std::endl
         << "     0" << std::endl
         << "  0" << std::endl
         << "ENDTAB" << std::endl
         << "  0" << std::endl
         << "ENDSEC" << std::endl
         << "  0" << std::endl
         << "SECTION" << std::endl
         << "  2" << std::endl
         << "BLOCKS" << std::endl
         << "  0" << std::endl
         << "BLOCK" << std::endl
         << "  5" << std::endl
         << "20" << std::endl
         << "330" << std::endl
         << "1F" << std::endl
         << "100" << std::endl
         << "AcDbEntity" << std::endl
         << "  8" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbBlockBegin" << std::endl
         << "  2" << std::endl
         << "*Model_Space" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << " 10" << std::endl
         << "0.0" << std::endl
         << " 20" << std::endl
         << "0.0" << std::endl
         << " 30" << std::endl
         << "0.0" << std::endl
         << "  3" << std::endl
         << "*Model_Space" << std::endl
         << "  1" << std::endl
         << std::endl
         << "  0" << std::endl
         << "ENDBLK" << std::endl
         << "  5" << std::endl
         << "21" << std::endl
         << "330" << std::endl
         << "1F" << std::endl
         << "100" << std::endl
         << "AcDbEntity" << std::endl
         << "  8" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbBlockEnd" << std::endl
         << "  0" << std::endl
         << "BLOCK" << std::endl
         << "  5" << std::endl
         << "D4" << std::endl
         << "330" << std::endl
         << "D2" << std::endl
         << "100" << std::endl
         << "AcDbEntity" << std::endl
         << " 67" << std::endl
         << "     1" << std::endl
         << "  8" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbBlockBegin" << std::endl
         << "  2" << std::endl
         << "*Paper_Space" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << " 10" << std::endl
         << "0.0" << std::endl
         << " 20" << std::endl
         << "0.0" << std::endl
         << " 30" << std::endl
         << "0.0" << std::endl
         << "  3" << std::endl
         << "*Paper_Space" << std::endl
         << "  1" << std::endl
         << std::endl
         << "  0" << std::endl
         << "ENDBLK" << std::endl
         << "  5" << std::endl
         << "D5" << std::endl
         << "330" << std::endl
         << "D2" << std::endl
         << "100" << std::endl
         << "AcDbEntity" << std::endl
         << " 67" << std::endl
         << "     1" << std::endl
         << "  8" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbBlockEnd" << std::endl
         << "  0" << std::endl
         << "BLOCK" << std::endl
         << "  5" << std::endl
         << "D8" << std::endl
         << "330" << std::endl
         << "D6" << std::endl
         << "100" << std::endl
         << "AcDbEntity" << std::endl
         << " 67" << std::endl
         << "     1" << std::endl
         << "  8" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbBlockBegin" << std::endl
         << "  2" << std::endl
         << "*Paper_Space0" << std::endl
         << " 70" << std::endl
         << "     0" << std::endl
         << " 10" << std::endl
         << "0.0" << std::endl
         << " 20" << std::endl
         << "0.0" << std::endl
         << " 30" << std::endl
         << "0.0" << std::endl
         << "  3" << std::endl
         << "*Paper_Space0" << std::endl
         << "  1" << std::endl
         << std::endl
         << "  0" << std::endl
         << "ENDBLK" << std::endl
         << "  5" << std::endl
         << "D9" << std::endl
         << "330" << std::endl
         << "D6" << std::endl
         << "100" << std::endl
         << "AcDbEntity" << std::endl
         << " 67" << std::endl
         << "     1" << std::endl
         << "  8" << std::endl
         << "0" << std::endl
         << "100" << std::endl
         << "AcDbBlockEnd" << std::endl
         << "  0" << std::endl
         << "ENDSEC" << std::endl;
  }
};

#endif // VULCAD_DRAW_DXF_DXFSPLINE