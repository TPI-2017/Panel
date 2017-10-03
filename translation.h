#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QTranslator>

using namespace std;

#define TRANSLATION_ES ":/es.qm"
#define TRANSLATION_EN ":/en.qm"

class Translation
{
    public:
        static void translateTo(const string lang = "");
    private:
        static void translate(const string l);
};

#endif // TRANSLATION_H
