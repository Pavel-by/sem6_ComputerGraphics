#include "config.h"

Config* Config::instance = new Config();

Config::Config(QObject *parent) : QObject(parent)
{

}

void Config::notify() {
    emit changed();
}
