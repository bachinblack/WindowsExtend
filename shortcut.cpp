#include "shortcut.h"
#include <QDebug>

Shortcut::Shortcut()
{
    loadSC();
}

void Shortcut::loadSC()
{
    std::ifstream   fs("shortcut.nrd");
    SCPath          *tmp = new SCPath;
    char            c;

    if (fs.is_open())
    {
        while (fs.get(c))
        {
            tmp->path = "";
            fs.read((char *)&tmp->bin, sizeof(tmp->bin));
            qDebug() << "------- new ----------";
            qDebug() << "combo is: " << (short)tmp->bin.isPressed;
            qDebug() << "key is: " << tmp->bin.key;
            while (fs.get(c) && c != '\0')
              tmp->path += c;
            shortcuts[static_cast<short>(tmp->bin.isPressed)].push_back(tmp);
            qDebug() << "path: [" << tmp->path.c_str() << "]";
        }
        fs.close();
    }
}

void Shortcut::saveSC(const SCPath *sc)
{
    std::ofstream fs;

    fs.open("shortcut.nrd", std::ios_base::app);
    if (fs.is_open())
    {
        fs.write("\0", 1);
        fs.write((char *)&sc->bin, sizeof(sc->bin));
        for(char c : sc->path)
            fs.write(&c, 1);
        fs.write("\0", 1);
        fs.close();
    }
}

void Shortcut::addKey(const short& key)
{
    _pressed += key;
}
