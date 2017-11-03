#include "shortcut.h"

Shortcut::Shortcut()
{
    loadSC();
    _pressed = 0;
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
    else
        createMessage("Error loading shortcuts", "Couln't open [shortcut.nrd].");

}

void Shortcut::saveSC(SCPath *sc)
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
        shortcuts[static_cast<short>(sc->bin.isPressed)].push_back(sc);
    }
    else
        createMessage("Error saving shortcuts", "Couln't open [shortcut.nrd].");
}

LPCWSTR Shortcut::stringToPath(const std::string& path)
{
    int len;
    int slength = (int)path.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, path.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r.c_str();
}

VOID Shortcut::Exec(const std::string& path)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(stringToPath(path), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        createMessage("Failed to start process", ("The path to this process is [" + path + "] maybe it is wrong.").c_str());
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void Shortcut::addKey(const short& key)
{
    _pressed += key;
}

void    Shortcut::activateSC(const short& key)
{
    for (auto tmp : shortcuts[_pressed])
    {
        if (tmp->bin.key == key)
        {
            Exec(tmp->path);
            return ;
        }
    }
}

QStringListModel *Shortcut::getSCList(void)
{
    QStringListModel *model = new QStringListModel();
    QStringList stringList;

    for (unsigned i=0; i<6; ++i)
    {
        for (auto it : shortcuts[i])
        {
            stringList.append(it->path.c_str());
        }
    }
    model->setStringList(stringList);
    return model;
}
