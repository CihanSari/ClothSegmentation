################################################################

# cihanlib pri

################################################################

CONFIG(debug, debug|release) {
    SUFFIX = d
 } else {
    SUFFIX =
 }
CIHANLIBPATH="../ClothSegmentation/CihanLib/distribute"

INCLUDEPATH += $${CIHANLIBPATH}/include
LIBS += -L"$${CIHANLIBPATH}/lib"
LIBS += -lCihanLibrary$${SUFFIX}
LIBS += -L"$${CIHANLIBPATH}/bin"

message("CihanLib at $${CIHANLIBPATH} loaded: $${SUFFIX}")
