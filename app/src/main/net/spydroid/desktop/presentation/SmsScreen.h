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

#ifndef SMS_SCREEN_H
#define SMS_SCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QThread>
#include <QPaintEvent>
#include "../components/GoBack.h"
#include "../remote/domain/SmsRepository.h"
#include "../remote/models/SmsHandler.h"
#include <QScrollArea>

class SmsLoader : public QThread {
    Q_OBJECT
public:
    SmsLoader(const QString& alias, QObject* parent = nullptr)
        : QThread(parent), alias(alias) {}

    std::vector<SmsHandler> getResult() const { return smsList; }

protected:
    void run() override {
        SmsRepositoryImp smsRepository;
        smsList = smsRepository.getSms(alias.toStdString());
    }

private:
    QString alias;
    std::vector<SmsHandler> smsList;
};

class SmsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SmsScreen(QWidget *parent = nullptr);  // Constructor

    // Método para actualizar el alias y recargar los SMS
    void setAlias(const QString& alias);

signals:
    void goToDashBoard();  // Señal para navegar a la vista Home

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVBoxLayout* layout;
    QLabel* label;
    SmsRepository* smsRepository;
    std::vector<SmsHandler> smsHandler;
    QString deviceAlias;
    QScrollArea* scrollArea = nullptr;  // ScrollArea para las tarjetas
    QWidget* cardContainer = nullptr;   // Contenedor de las tarjetas
    QVBoxLayout* cardLayout = nullptr;  // Layout de las tarjetas

    void clearCards();  // Método para limpiar las tarjetas y resetear la vista
    // Método privado para recargar los SMS con el alias actualizado
    void loadSms();
};

#endif // SMS_SCREEN_H