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

#include "SettingsManager.h"

SettingsManager::SettingsManager(const QString &appName, QObject *parent) 
    : QObject(parent), settings(new QSettings("SpyDroid", appName, this)) {
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
