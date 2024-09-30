/*
 * Copyright (C) 2024 Daniel Gómez(Less)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

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

    void setValue(const QString &key, const QVariant &value);
    QVariant getValue(const QString &key, const QVariant &defaultValue = QVariant()) const;
    void removeValue(const QString &key);
    bool contains(const QString &key) const;

    // Delete all settings
    void clear();

private:
    QSettings *settings;
};

#endif // SETTINGSMANAGER_H
