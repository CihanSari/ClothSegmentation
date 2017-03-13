
################################################################

# opencv pri

################################################################

CONFIG(debug, debug|release) {
    SUFFIX = d
 } else {
    SUFFIX =
 }

!win32 {
OPENCVBUILDPATH = /usr/local
LIBS *= -L/usr/local/lib
INCLUDEPATH *= /usr/local/include
OPENCVLIBSUFFIX =
OPENCVLIBPREFIX =
}
win32 {
OPENCVBUILDPATH = "D:/Projects/libs/opencv/2.4.11/build"
LIBS *= -L$${OPENCVBUILDPATH}/x64/vc10/lib
OPENCVLIBSUFFIX = 2411$${SUFFIX}
INCLUDEPATH *= "$${OPENCVBUILDPATH}/include"
LIBS *= -L"$${OPENCVBUILDPATH}/x64/vc10/bin"
message($${OPENCVLIBPREFIX}opencv_core$${OPENCVLIBSUFFIX})
}



LIBS *= \
-l$${OPENCVLIBPREFIX}opencv_core$${OPENCVLIBSUFFIX}\
-l$${OPENCVLIBPREFIX}opencv_imgproc$${OPENCVLIBSUFFIX}


message("OpenCV at $${OPENCVBUILDPATH} loaded $${OPENCVLIBSUFFIX}")
