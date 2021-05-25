#if !defined(VULCAD_DRAW_DXF_SECTION_HEADER)
#define VULCAD_DRAW_DXF_SECTION_HEADER

#include "section.cc"

class Header : public Section {
public:
  static void write(std::ofstream &file) {
    begin(file, "HEADER");
    add(file);
    end(file);
  }

private:
  static void add(std::ofstream &file) {
    file << "  9" << std::endl
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
         << "AcDbBlockEnd" << std::endl;
  }
};

#endif // VULCAD_DRAW_DXF_SECTION_HEADER
