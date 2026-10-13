#ifndef FILEMANAGERTAB_H
#define FILEMANAGERTAB_H

#include <QWidget>
#include "filetreemodel.h"
#include <string>
#include "filetabmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class filemanagertab;
}
QT_END_NAMESPACE


class filemanagertab : public QWidget
{
    Q_OBJECT

public:
    explicit filemanagertab(const std::string& initialPath, QWidget *parent = nullptr);
    ~filemanagertab();

private slots:
    void onTableDoubleClicked(const QModelIndex &index);
    void onTreeExpanded(const QModelIndex &index);

    void onTreeClicked(const QModelIndex &index);
    void onBackBtnClicked();

private:
    Ui::filemanagertab *ui;
    filetabmodel *tableModel;
    std::string currentpath;
    FileTreeModel *treeModel;

    void loadDirectory(const std::string& targetPath);



};

#endif // FILEMANAGERTAB_H
