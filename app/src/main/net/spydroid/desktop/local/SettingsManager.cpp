#include "SettingsManager.h"

SettingsManager::SettingsManager(const QString &appName, QObject *parent) 
    : QObject(parent), settings(new QSettings("SpyDroid", appName, this)) {
    // Constructor: inicializa QSettings con SpyDroid como organización y appName como la aplicación
}

void SettingsManager::setValue(const QString &key, const QVariant &value) {
    settings->setValue(key, value);
}

QVariant SettingsManager::getValue(const QString &key, const QVariant &defaultValue) const {
    return settings->value(key, defaultValue);
}

void SettingsManager::removeValue(const QString &key) {
    settings->remove(key);
}

bool SettingsManager::contains(const QString &key) const {
    return settings->contains(key);
}

void SettingsManager::clear() {
    settings->clear();
}
