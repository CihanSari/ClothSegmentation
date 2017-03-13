#ifndef CIHANDATA_H
#define CIHANDATA_H
#include <QFileInfoList>
#include <QDir>
#include <QFile>

namespace CihanLib {
class CData
{
public:
    explicit CData(QString filepath, QStringList filter = QStringList()):
        d(new CDataPrivate())
    {
        QFileInfo fileInfo(filepath);
        if (fileInfo.isDir())
            load(filepath, filter);
        else
            d->__fileList << fileInfo;
        d->__it = d->__fileList.begin();
    }
    static QList<CData> multiData(int argc, const char *argv[])
    {
        QList<CData> multiCData;
        for (int i=1; i<argc;++i) {
            multiCData << CData(argv[i]);
        }
        return multiCData;
    }
    CData():
        d(new CDataPrivate())
    {

    }
    CData(const CData& other):
        d(new CDataPrivate())
    {
        d->__fileList = other.d->__fileList;
        d->__it = other.d->__it;
    }
    ~CData()
    {
        delete d;
    }
    QFileInfoList files() const {
        return d->__fileList;
    }
    QFileInfoList operator () () const {
        return d->__fileList;
    }

    QFileInfo operator [] (int index) const {
        return d->__fileList.value(index);
    }
    QString path() const
    {
        if (!d->__fileList.isEmpty())
            return d->__fileList.first().path();
        else
            return QString();
    }

    template <typename type>
    const CData& operator >> (type& out) const {
        QFileInfo fileInfo;
        *this >> fileInfo;
        out = type(fileInfo);
        return *this;
    }

    const CData& operator >> (QFileInfo& fileInfo) const {
        if (!hasNext())
            d->__it = d->__fileList.begin();
        fileInfo = *d->__it;
        ++d->__it;
        return *this;
    }

    bool hasNext() const
    {
        return d->__it != d->__fileList.end();
    }


protected:
    void load(QFileInfo info, QStringList filter)
    {
        QDir dir(info.filePath());
        QFileInfoList subdirInfoList = dir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
        foreach (QFileInfo subdirInfo, subdirInfoList) {
            load(subdirInfo, filter);
        }
        d->__fileList << dir.entryInfoList(filter, QDir::Files);
    }
private:
    class CDataPrivate
    {
    public:
        QFileInfoList __fileList;
        QFileInfoList::const_iterator __it;
    }*d;
};
}
#endif // CIHANDATA_H
