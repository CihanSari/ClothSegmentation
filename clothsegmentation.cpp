#include "clothsegmentation.h"
#include "grabcutapplication.h"
#include "cihanlandmark.h"
#include <QImage>
#include "opencv2/opencv.hpp"
ClothSegmentation::ClothSegmentation()
{

}

bool ClothSegmentation::work(const QString source, const QString metadataKey, QString& errorString) const
{

    QImage qimage(source);

    if (qimage.isNull()) {
        errorString = QString("File could not be read as an image: %1").arg(source);
        return false;
    }

    qimage = qimage.convertToFormat(QImage::Format_ARGB32);
    cv::Mat cvImage(qimage.height(),qimage.width(),CV_8UC4,const_cast<uchar*>(qimage.bits()),
                    static_cast<size_t>(qimage.bytesPerLine()));

    if (cvImage.empty()) {
        errorString = QString("QImage to cv::Mat conversion failed! This is highly abnormal. File: %1").arg(source);
        return false;
    }
    CihanLib::CLandmark::setModelPath("models/");
    GCApplication gca(cvImage);
    if (gca.resetFromFace()) {
        qimage.setText(metadataKey, gca.toString().data());
        qimage.save(source);
        return true;
    } else {
        errorString = QString("Face detection / landmark extraction process failed: %1").arg(source);
        return false;
    }
}
