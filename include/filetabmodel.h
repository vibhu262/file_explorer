#ifndef FILETABMODEL_H
#define FILETABMODEL_H

#include <QAbstractTableModel>
#include <vector>
#include <string>

struct FileRecord {
    std::string name;
    std::string absolutePath;
    bool isDir;
    uintmax_t size;
};

class filetabmodel: public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit filetabmodel(QObject *parent = nullptr);
    //push vector into qt view
    void setFiles(const std::vector<FileRecord>& newFiles);

    const FileRecord& getFile(int rowIndex) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section , Qt::Orientation orientation, int role= Qt::DisplayRole) const override;

private:
    std::vector<FileRecord> m_files;
};

#endif // FILETABMODEL_H
