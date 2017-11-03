#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <fstream>
#include <Windows.h>
#include <QMessageBox>
#include <QDebug>
#include <QStringListModel>

bool createMessage(const char *title, const char *body);

enum Mod
{
    None = 0,
    Ctrl = 1,
    Alt = 2,
    Shift = 4,
    CtAl = 3,
    CtSh = 5,
    AlSh = 6,
    All = 7
};

#pragma pack(push, 1)
struct BinSC
{
    unsigned short key;
    char isPressed;
};

struct SCPath
{
    BinSC       bin;
    std::string path;
};

class Shortcut
{
public:
    Shortcut();
    void    addKey(const short& key);
    void    activateSC(const short& key);
    QStringListModel *getSCList(void);

private:
    short   _pressed;
    void    loadSC(void);
    void    saveSC(SCPath *sc);
    VOID    Exec(const std::string& path);
    LPCWSTR stringToPath(const std::string& path);
    std::list<SCPath *>   shortcuts[8];
};
