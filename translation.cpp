#include "translation.h"
#include <QLocale>
#include <QApplication>
#include <QtDebug>

using namespace std;

static QTranslator translator;

void Translation::translateTo(const string lang)
{
    if (lang.empty())
    {
        string local = QLocale::system().name().toStdString();
        if (local == "en_US")
            Translation::translate(TRANSLATION_EN);
        else if (local == "es_AR")
            Translation::translate(TRANSLATION_ES);
    }
    else
    {
        Translation::translate(lang);
    }
    QApplication::instance()->installTranslator(&translator);
}

inline void Translation::translate(const string l){
    translator.load(QString::fromStdString(l));
}

