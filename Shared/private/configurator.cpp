#include "configurator.h"
#include <QMutex>
#include <QFile>
#include <QHash>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QDebug>

Configurator* Configurator::m_Instance = 0;

Configurator* Configurator::instance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();

        if (!m_Instance)
            m_Instance = new Configurator;

        mutex.unlock();
    }

    return m_Instance;
}

Configurator::Configurator()
{
}

void Configurator::parseconfig()
{
    QString fileName = "config.dat";
    QFile file(fileName);
        QHash<QString, QString> config;

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox errorBox;
            errorBox.setText("Can't open config file " + fileName + " for reading.");
            errorBox.setInformativeText(qPrintable(file.errorString()));
            errorBox.exec();
        }
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList tokens = line.split(":");
            config.insert(tokens[0],tokens[1]);
        }

        //to test that values were stored in QHash properly
            QHashIterator<QString, QString> iter(config);
            while (iter.hasNext())
            {
                iter.next();
                qDebug() << iter.key() << iter.value();
            }

        file.close();

}

void Configurator::createconfig()
{
        QString fileName = "config.dat";
        QFile file(fileName);

        QHash<QString, QString> config;

        config.insert("hostname", "localhost");
        config.insert("port", "3306");
        config.insert("dbname", "pixspace");
        config.insert("username", "pixspace");
        config.insert("password", "pixspace");

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox errorBox;
            errorBox.setText("Can't open config file " + fileName + " for writing.");
            errorBox.setInformativeText(qPrintable(file.errorString()));
            errorBox.exec();
        }
        QTextStream out(&file);
        QHashIterator<QString, QString> iter(config);
        while (iter.hasNext())
        {
            iter.next();
            qDebug() << iter.key() << iter.value();
            out << iter.key() << ":" << iter.value() << endl;
        }
        file.flush();
        file.close();
}
