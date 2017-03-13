#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QImage>
#include "cihandata.h"
#include <QDateTime>
#include "clothsegmentation.h"

using CihanLib::CData;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("ClothSegmentation");
    QCoreApplication::setApplicationVersion("00.01");
    QCoreApplication::setOrganizationName("cihansari");
    QCoreApplication::setOrganizationDomain("www.cihansari.com");

    QCommandLineParser parser;
    parser.setApplicationDescription("Detects faces then segment cloths. Writes the results into image metadata with OpenCV yaml format; yaml key mask. To access to binary mask use=> mask&1.");
    parser.addHelpOption();
    parser.addPositionalArgument("source", "Source file(s) or directory to look for images.");

    // An option with a value
    QString outputOptionDef = QString("%1%2").arg(a.applicationName(),a.applicationVersion());
    QCommandLineOption outputOption("o", QString("Output metadata key. Default: \"%1\"").arg(outputOptionDef)
                                    , "Option", outputOptionDef);
    parser.addOption(outputOption);

    // Process the actual command line arguments given by the user
    parser.process(a);

    const QStringList args = parser.positionalArguments();
    // source is args.at(0)

    if (args.isEmpty()) {
        parser.showHelp(-1);
    }
    const QString outputKey = parser.value(outputOption);

    const ClothSegmentation cs;
    foreach (const QString source, args) {
        QString errorString;
        if (!cs.work(source, outputKey, errorString)) {
            qDebug(errorString.toLatin1().constData());
        }
    }
    return 0;
}
