#include "filemanagertab.h"
#include "ui_filemanagertab.h"

#include <filesystem>
#include <iostream>


namespace fs = std::filesystem;



filemanagertab::filemanagertab(const std::string& initialPath,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::filemanagertab),
    currentpath(initialPath)
{
    ui->setupUi(this);

    //set up data model for table
    tableModel = new filetabmodel(this);


    ui->tableView->setModel(tableModel);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->verticalHeader()->setDefaultSectionSize(24);

    connect(ui->tableView , &QTableView::doubleClicked, this, &filemanagertab::onTableDoubleClicked);

    treeModel = new FileTreeModel(this);
    ui->treeView->setModel(treeModel);
    ui->treeView->setHeaderHidden(true);

    treeModel->setRootPath(currentpath);

    connect(ui->treeView , &QTreeView::expanded , this , &filemanagertab::onTreeExpanded);
    connect(ui->treeView, &QTreeView::clicked, this, &filemanagertab::onTreeClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, &filemanagertab::onBackBtnClicked);

    loadDirectory(initialPath);
}

filemanagertab::~filemanagertab()
{
    delete ui;
}

void filemanagertab::loadDirectory(const std::string& targetPath){
    std::vector<FileRecord> loadedFiles;
    try{
        for(const auto& entry: fs::directory_iterator(targetPath)){
            FileRecord record;
            record.name = entry.path().filename().string();
            record.absolutePath = entry.path().string();
            record.isDir = entry.is_directory();

            if (!record.isDir) {
                std::error_code ec;
                record.size = fs::file_size(entry.path(), ec);
                if (ec) record.size = 0; // Handle error silently for now
            } else {
                record.size = 0;
            }

            loadedFiles.push_back(record);
        }
    }catch(const fs::filesystem_error& e){
        std::cerr << "Filesystem Error: " << e.what() << '\n';
        return;
    }
    tableModel->setFiles(loadedFiles);
}

void filemanagertab::onTableDoubleClicked(const QModelIndex &index) {
    // Fetch the raw C++ struct directly from our vector via the row index!
    const FileRecord& clickedFile = tableModel->getFile(index.row());

    if (clickedFile.isDir) {
        currentpath = clickedFile.absolutePath;
        loadDirectory(currentpath);
    } else {
        std::cout << "Cannot navigate into a file.\n";
    }
}

void filemanagertab::onTreeExpanded(const QModelIndex &index){
    TreeNode* clickedNode = static_cast<TreeNode*>(index.internalPointer());

    treeModel->layoutAboutToBeChanged();
    treeModel->fetchNodes(clickedNode);
    treeModel->layoutChanged();
}


void filemanagertab::onTreeClicked(const QModelIndex &index){
    TreeNode* clickedNode = static_cast<TreeNode*>(index.internalPointer());

    // 2. Update the tracker and tell the table to load it
    currentpath = clickedNode->absolutePath;
    loadDirectory(currentpath);
}

void filemanagertab::onBackBtnClicked(){
    fs::path current(currentpath);

    // Check if we are at the root (e.g., "C:\" or "/")
    if (current.has_parent_path() && current != current.parent_path()) {
        // Move up one directory level
        currentpath = current.parent_path().string();
        loadDirectory(currentpath);
    }
}