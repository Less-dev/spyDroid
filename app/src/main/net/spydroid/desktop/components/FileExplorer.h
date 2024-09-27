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

class FileExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit FileExplorer(const QString &directoryPath = QDir::homePath(), QWidget *parent = nullptr);
    ~FileExplorer();

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

private slots:
    void createFile();
    void renameFile();
    void deleteFile();
    void copyFile();
    void pasteFile();
};

#endif // FILEEXPLORER_H
