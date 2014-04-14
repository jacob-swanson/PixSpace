#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

class Configurator
{
public:
    // Get an instance of the Configurator
    static Configurator* instance();

    /**
     * @brief parseconfig reads in a config file with keys/values separated
     * by colons. Stores in a QHash as QString:QString
     */
    void parseconfig();

    /**
     * @brief createconfig makes a config file
     */
    void createconfig();

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
