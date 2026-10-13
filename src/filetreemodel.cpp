#include "filetreemodel.h"
#include <iostream>

namespace fs = std::filesystem;



FileTreeModel::FileTreeModel(QObject *parent) :QAbstractItemModel(parent) {}

void FileTreeModel::setRootPath(const std::string &path){
    beginResetModel();
    rootNode = std::make_unique<TreeNode>();
    rootNode->name = "Root";
    rootNode->absolutePath = path;
    rootNode->isScanned = false;

    fetchNodes(rootNode.get());
    endResetModel();
}


void FileTreeModel::fetchNodes(TreeNode* parentNode){
    if(parentNode->isScanned) return;

    try{
        for(const auto& entry: fs::directory_iterator(parentNode->absolutePath)){
            if(entry.is_directory()){
                auto child = std::make_unique<TreeNode>();
                child->name = entry.path().filename().string();
                child->absolutePath = entry.path().string();
                child->parent = parentNode;
                child->isScanned = false;

                parentNode->children.push_back(std::move(child));

            }
        }
    }catch(const fs::filesystem_error& e){

    }
    parentNode->isScanned = true;

    if(parentNode->children.empty()){

    }
}

QModelIndex FileTreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent)) return QModelIndex();

    TreeNode* parentNode = parent.isValid() ?
                               static_cast<TreeNode*>(parent.internalPointer()) : rootNode.get();

    if (row < parentNode->children.size()) {
        TreeNode* childNode = parentNode->children[row].get();
        return createIndex(row, column, childNode); // Embed pointer here!
    }
    return QModelIndex();
}
QModelIndex FileTreeModel::parent(const QModelIndex &index) const {
    if(!index.isValid()) return QModelIndex();

    TreeNode* childNode = static_cast<TreeNode*>(index.internalPointer());
    TreeNode* parentNode = childNode->parent;

    if(parentNode == rootNode.get() || parentNode == nullptr){
        return QModelIndex();
    }

    TreeNode* grandParent = parentNode->parent;
    int row=0;
    for(size_t i = 0 ; i < grandParent->children.size() ; i++){
        if(grandParent->children[i].get() == parentNode){
            row = i;
            break;
        }
    }
    return createIndex(row, 0 , parentNode);
}


int FileTreeModel::rowCount(const QModelIndex &parent) const{
    if(parent.column() > 0) return 0;
    TreeNode* parentNode = parent.isValid() ?
                               static_cast<TreeNode*>(parent.internalPointer()) : rootNode.get();
    return parentNode->children.size();
}

int FileTreeModel::columnCount(const QModelIndex &parent) const {
    return 1; // Only showing folder name in the tree
}

QVariant FileTreeModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid()) return QVariant();

    if(role == Qt::DisplayRole){
        TreeNode* node = static_cast<TreeNode*>(index.internalPointer());
        return QString::fromStdString(node->name);
    }
    return QVariant();
}


bool FileTreeModel::hasChildren(const QModelIndex &parent) const {
    if(!parent.isValid()) return true;

    TreeNode* node = static_cast<TreeNode*>(parent.internalPointer());

    if(!node->isScanned){
        return true;
    }

    return !node->children.empty();
}
