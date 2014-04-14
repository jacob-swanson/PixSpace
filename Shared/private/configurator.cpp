#include "configurator.h"

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

QHash<QString, QString> Configurator::getConfig()
{
    QString fileName = "config.dat";
    QFile file(fileName);
    QHash<QString, QString> config;

    if (!file.open(QIODevice::ReadOnly))
    {
        /*QMessageBox errorBox;
        errorBox.setText("Can't open config file " + fileName + " for reading.");
        errorBox.setInformativeText(qPrintable(file.errorString()));
        errorBox.exec();*/

        // Not a fatal error, so using qDebug
        qDebug() << "Can't open config file " + fileName + " for reading.";

        return QHash<QString, QString>();
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

    return config;
}

void Configurator::updateConfig(QHash<QString, QString> newConfig)
{
    // writes server settings to file config.dat
    QString fileName = "config.dat";
    QFile file(fileName);

    QHash<QString, QString> oldConfig = this->getConfig();

    // Merge new and old config
    QHashIterator<QString, QString> iter(newConfig);
    while (iter.hasNext())
    {
        iter.next();
        oldConfig.insert(iter.key(), iter.value());
    }

    //can test this by manually making file config.dat read only
    //error message let's you know file is unavailable for editing
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Is a fatal error
        QMessageBox errorBox;
        errorBox.setText("Can't open config file " + fileName + " for writing.");
        errorBox.setInformativeText(qPrintable(file.errorString()));
        errorBox.exec();
    }
    else
    {
        //textstream is preferable to data stream for readability
        QTextStream out(&file);
        QHashIterator<QString, QString> outIter(oldConfig);
        while (outIter.hasNext())
        {
            outIter.next();
            //qdebug line following is for testing output.
            //qDebug() << iter.key() << iter.value();
            out << outIter.key() << ":" << outIter.value() << endl;
        }

        file.flush();
        file.close();
    }
}
