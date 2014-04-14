#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H
#include <QMutex>
#include <QFile>
#include <QHash>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QDebug>

class Configurator
{
public:
    // Get an instance of the Configurator
    static Configurator* instance();

    /**
     * @brief getConfig Return config file
     * @return
     */
    QHash<QString, QString> getConfig();

    /**
     * @brief updateConfig Update config file
     * @param newConfig
     */
    void updateConfig(QHash<QString, QString> newConfig);


private:
    // Hide constructor
    Configurator();

    // Hide copy constructor
    Configurator(const Configurator&);

    // Hide assignment operator
    Configurator& operator=(const Configurator &);

    // Configurator instance
    static Configurator* m_Instance;
};

#endif // CONFIGURATOR_H
