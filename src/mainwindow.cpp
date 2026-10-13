#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filemanagertab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("File Explorer");

    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);

    connect(ui->tabWidget , &QTabWidget::tabCloseRequested, [this](int index){
        QWidget *tab = ui->tabWidget->widget(index);
        ui->tabWidget->removeTab(index);
        delete tab;
    });

    filemanagertab *newtab = new filemanagertab("/");
    ui->tabWidget->addTab(newtab , "Root");
}

MainWindow::~MainWindow()
{
    delete ui;
}
