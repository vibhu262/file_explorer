#ifndef FILETREEMODEL_H
#define FILETREEMODEL_H

#include <QAbstractItemModel>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>


struct TreeNode {
    std::string name;
    std::string absolutePath;

    TreeNode* parent = nullptr;
    std::vector<std::unique_ptr<TreeNode>> children;

    bool isScanned = false;
};

class FileTreeModel : public QAbstractItemModel{
    Q_OBJECT

public:
    explicit FileTreeModel(QObject *parent = nullptr);

    void setRootPath(const std::string& path);

    void fetchNodes(TreeNode* parentNode);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::unique_ptr<TreeNode> rootNode;
};

#endif // FILETREEMODEL_H
