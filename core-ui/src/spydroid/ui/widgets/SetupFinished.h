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

#ifndef SETUP_FINISHED_H
#define SETUP_FINISHED_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include <QPaintEvent>
#include "BottomBarInstaller.h"
#include "BannerHorizontal.h"
#include "CardWidgetInstaller.h"
#include <QString>

class SetupFinished : public QWidget
{
    Q_OBJECT

public:
    explicit SetupFinished(QWidget *parent = nullptr);
    void setStartDownload(bool start, const QString& pathResources);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event);

signals:
    void nextPage();
    void backPage();
    
private:
    QVBoxLayout* layout;
    BannerHorizontal* topBarInstaller;
    CardWidgetInstaller* details;
    QLabel* downloadDescriptor;
    QProgressBar* progressBar;
    BottomBarInstaller* bottomBarInstaller;
    bool startDownload;  
    void onStartCheckBoxStateChanged(int state);
    void goToNextPage();
    void goToBackPage();
};

#endif // SETUP_FINISHED_H
