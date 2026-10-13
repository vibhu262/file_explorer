#include "filetabmodel.h"

filetabmodel::filetabmodel(QObject *parent)
    :QAbstractTableModel(parent){}

void filetabmodel::setFiles(const std::vector<FileRecord>& newFiles){
    //informing qt of change in data
    beginResetModel();
    m_files = newFiles;
    endResetModel();
}

int filetabmodel::rowCount(const QModelIndex &parent) const{
    if(parent.isValid()) return 0;
    return m_files.size();
}
const FileRecord& filetabmodel::getFile(int rowIndex) const {
    // Returns the raw struct from your standard vector
    return m_files.at(rowIndex);
}

int filetabmodel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return 3; // Name, Size, Type
}

QVariant filetabmodel::data(const QModelIndex &index, int role) const{
    if(!index.isValid() || index.row() >= m_files.size()) return QVariant();

    if(role == Qt::DisplayRole){
        const FileRecord& file = m_files[index.row()];

        if(index.column() == 0) return QString::fromStdString(file.name);

        if(index.column() == 1){
            if(file.isDir) return QString("");
            return QString::number(file.size);
        }
        if(index.column() == 2){
            return file.isDir ? QString("Directory") : QString("File");
        }
    }
    return QVariant();
}

QVariant filetabmodel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) return QString("Name");
        if (section == 1) return QString("Size (Bytes)");
        if (section == 2) return QString("Type");
    }
    return QVariant();
}