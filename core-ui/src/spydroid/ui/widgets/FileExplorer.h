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

class FileExplorer : public QWidget
{
    Q_OBJECT

public:
    explicit FileExplorer(const QString &directoryPath = QDir::homePath(), QWidget *parent = nullptr);
    ~FileExplorer();
    void setRootPath(const QString &newPath);
    void onFileDoubleClicked(const QModelIndex &index);
    void addToRecentFiles(const QString &filePath);

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
