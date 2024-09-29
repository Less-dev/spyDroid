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

#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QClipboard>
#include <QModelIndex>
#include <QMouseEvent>
#include <QObject>
#include <QCursor>


class FileExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit FileExplorer(const QString &directoryPath = QDir::homePath(), QWidget *parent = nullptr);
    ~FileExplorer();
    void setRootPath(const QString &newPath);
    void onFileDoubleClicked(const QModelIndex &index);
    void addToRecentFiles(const QString &filePath);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QTreeView *treeView;
    QFileSystemModel *fileModel;
    QLabel *titleLabel;
    QVBoxLayout *layout;

    QMenu *contextMenu;
    QAction *createAction;
    QAction *renameAction;
    QAction *deleteAction;
    QAction *copyAction;
    QAction *pasteAction;

    QString copiedFilePath;
    QClipboard *clipboard;

    void setupContextMenu();
    void setupActions();
signals:
    void fileOpened(const QString &filePath);  // Señal que emitimos cuando se selecciona un archivo
private slots:
    void createFile();
    void renameFile();
    void deleteFile();
    void copyFile();
    void pasteFile();
};

#endif // FILEEXPLORER_H
