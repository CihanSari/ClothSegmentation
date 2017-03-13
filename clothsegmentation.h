#ifndef CLOTHSEGMENTATION_H
#define CLOTHSEGMENTATION_H

#include <QString>
class GCApplication;
class ClothSegmentation
{
public:
    ClothSegmentation();
    bool work(const QString source, const QString metadataKey, QString &errorString) const;
};

#endif // CLOTHSEGMENTATION_H
