#include "translation.h"
#include <QApplication>

QTranslator Translation::translator;

void Translation::translate(Language lang)
{
    switch (lang) {
    case English:
        translator.load(":/en.qm");
        break;
    case Spanish:
        translator.load(":/es.qm");
        break;
    }
    QApplication::instance()->installTranslator(&translator);
}

void Translation::translate()
{
    if (QLocale::system().name().toStdString() == "es_AR")
        translator.load(":/es.qm");
    QApplication::instance()->installTranslator(&translator);
}
