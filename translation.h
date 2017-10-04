#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QLocale>
#include <QTranslator>

class Translation
{
public:
    enum Language {English, Spanish};
    static void translate(Language lang);
    static void translate();
private:
    static QTranslator translator;
};

#endif // TRANSLATION_H
