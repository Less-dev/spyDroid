#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include <QString>

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    explicit SettingsManager(const QString &appName, QObject *parent = nullptr);

    // Métodos públicos para manejar configuraciones
    void setValue(const QString &key, const QVariant &value);
    QVariant getValue(const QString &key, const QVariant &defaultValue = QVariant()) const;
    void removeValue(const QString &key);
    bool contains(const QString &key) const;

    // Eliminar todas las configuraciones
    void clear();

private:
    QSettings *settings;
};

#endif // SETTINGSMANAGER_H
