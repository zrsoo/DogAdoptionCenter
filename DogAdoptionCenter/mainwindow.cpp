#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QDialog>
#include <QMessageBox>
#include <QTableView>
#include <QAbstractItemView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QDialogButtonBox>
#include "Storage.h"
#include "Dog.h"
#include <QUrl>
#include "filedownloader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    this->setWindowTitle("Dog Adoption Center");

    // Admin or user mode prompt....
    QDialog* dialogMode = new QDialog(this);

    QVBoxLayout* vLay = new QVBoxLayout();
    QPushButton* btnAdmin = new QPushButton("&Admin");
    QPushButton* btnUser = new QPushButton("&User");

    btnAdmin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnUser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    vLay->addWidget(btnAdmin);
    vLay->addWidget(btnUser);

    dialogMode->setLayout(vLay);
    dialogMode->setMinimumSize(200, 200);
    dialogMode->setWindowTitle("Use mode prompt");

    QObject::connect(btnAdmin, SIGNAL(clicked()), dialogMode, SLOT(accept()));
    QObject::connect(btnUser, SIGNAL(clicked()), dialogMode, SLOT(reject()));
    QObject::connect(dialogMode, SIGNAL(finished(int)), this, SLOT(dialogModeIsFinished(int)));

    dialogMode->exec();

    delete vLay;
    ////////////////////////////////////


    if(!admin)
    {
        // HTML or CSV storage prompt....
        QDialog* dialogStorage = new QDialog(this);

        vLay = new QVBoxLayout();
        QPushButton* btnHTML = new QPushButton("&HTML");
        QPushButton* btnCSV = new QPushButton("&CSV");

        btnHTML->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnCSV->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        vLay->addWidget(btnHTML);
        vLay->addWidget(btnCSV);

        dialogStorage->setLayout(vLay);
        dialogStorage->setMinimumSize(200, 200);
        dialogStorage->setWindowTitle("Storage prompt");

        QObject::connect(btnHTML, SIGNAL(clicked()), dialogStorage, SLOT(accept()));
        QObject::connect(btnCSV, SIGNAL(clicked()), dialogStorage, SLOT(reject()));
        QObject::connect(dialogStorage, SIGNAL(finished(int)), this, SLOT(dialogStorageIsFinished(int)));

        dialogStorage->exec();
        ////////////////////////////////////
    }


    // Creating main menu layout...

    if(admin)
    {
        QGridLayout* gLay = new QGridLayout();
        QPushButton* btnAddDog = new QPushButton("&Add dog");
        QPushButton* btnRemoveDog = new QPushButton("&Remove dog");
        QPushButton* btnUpdateDog = new QPushButton("&Update dog");
        QPushButton* btnUndo = new QPushButton("Undo");
        QPushButton* btnRedo = new QPushButton("Redo");
        QPushButton* btnExit = new QPushButton("&Exit");

        btnAddDog->setFixedHeight(100);
        btnRemoveDog->setFixedHeight(100);
        btnUpdateDog->setFixedHeight(100);
        btnUndo->setFixedHeight(100);
        btnRedo->setFixedHeight(100);
        btnExit->setFixedHeight(100);

        btnAddDog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnRemoveDog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnUpdateDog->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnUndo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnRedo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btnExit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QObject::connect(btnAddDog, SIGNAL(clicked()), this, SLOT(addDogPrompt()));
        QObject::connect(btnRemoveDog, SIGNAL(clicked()), this, SLOT(removeDogPrompt()));
        QObject::connect(btnUpdateDog, SIGNAL(clicked()), this, SLOT(updateDogPrompt()));
        QObject::connect(btnUndo, SIGNAL(clicked()), this, SLOT(undo()));
        QObject::connect(btnRedo, SIGNAL(clicked()), this, SLOT(redo()));
        QObject::connect(btnExit, SIGNAL(clicked()), this, SLOT(exit()));

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Breed"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Photo link"));

        view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        view->setModel(model);
        view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        // Populating table model...
        populate_table_view(model);

        gLay->addWidget(view, 0, 0, 3, 3);
        gLay->addWidget(btnAddDog, 3, 0, 1, 1);
        gLay->addWidget(btnRemoveDog, 3, 1, 1, 1);
        gLay->addWidget(btnUpdateDog, 4, 0, 1, 1);
        gLay->addWidget(btnUndo, 4, 1, 1, 1);
        gLay->addWidget(btnRedo, 5, 0, 1, 1);
        gLay->addWidget(btnExit, 5, 1, 1, 1);

        QWidget* w = new QWidget();

        w->setLayout(gLay);
        this->setCentralWidget(w);
    }
    else if (user)
    {
        if(HTML)
            st = new HTMLStorage("Dogs.html");
        else
            st = new CSVStorage("Dogs.csv");

        QGridLayout* gLay = new QGridLayout();
        QPushButton* btnViewDogs = new QPushButton("&View dogs");
        QPushButton* btnFilter = new QPushButton("&FIlter dogs by breed and maximum age");
        QPushButton* btnExit = new QPushButton("&Exit");

        QObject::connect(btnViewDogs, SIGNAL(clicked()), this, SLOT(viewDogs()));
        QObject::connect(btnFilter, SIGNAL(clicked()), this, SLOT(filterDogs()));
        QObject::connect(btnExit, SIGNAL(clicked()), this, SLOT(exit()));

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Breed"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Photo link"));

        view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        view->setModel(model);
        view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        populate_table_view(model);

        adoptionModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        adoptionModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        adoptionModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Breed"));
        adoptionModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
        adoptionModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Photo link"));

        adoptionView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        adoptionView->setModel(adoptionModel);
        adoptionView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        adoptionView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        gLay->addWidget(view, 0, 0, 2, 2);
        gLay->addWidget(adoptionView, 0, 2, 2, 2);
        gLay->addWidget(btnViewDogs, 2, 0, 1, 4);
        gLay->addWidget(btnFilter, 3, 0, 1, 4);
        gLay->addWidget(btnExit, 4, 0, 1, 4);

        QWidget* w = new QWidget();
        w->setLayout(gLay);
        this->setCentralWidget(w);
    }

    this->show();
    /////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dialogModeIsFinished(int result)
{
    if(result == QDialog::Accepted)
    {
        admin = true;
        return;
    }

    user = true;
}

void MainWindow::dialogStorageIsFinished(int result)
{
    if(result == QDialog::Accepted)
    {
        HTML = true;
        return;
    }

    HTML = false;
}

void MainWindow::populate_table_view(QStandardItemModel* model)
{
    QList<QStandardItem*> items;

    s.readDogsTXT();

    for(auto d : s.getAllDogs())
    {
        items.append(new QStandardItem(QVariant(d.get_id()).toString()));
        items.append(new QStandardItem(d.get_name().c_str()));
        items.append(new QStandardItem(d.get_breed().c_str()));
        items.append(new QStandardItem(QVariant(d.get_age()).toString()));
        items.append(new QStandardItem(d.get_photoLink().c_str()));

        model->appendRow(items);
        items.clear();
    }

    model->removeRow(0);
}

void MainWindow::addDogPrompt()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);

    form.addRow(new QLabel("Add dog..."));

    QList<QString> labels;
    labels << "Name: ";
    labels << "Breed: ";
    labels << "Age: ";
    labels << "Photo Link: ";

    QList<QLineEdit* > fields;
    for(int i = 0; i < 4; ++i)
    {
        QLineEdit *lineEdit = new QLineEdit(&dialog);
        QString label = labels[i];
        form.addRow(label, lineEdit);

        fields << lineEdit;
    }

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    QList<QString> dogVars;

    if(dialog.exec() == QDialog::Accepted)
    {
        foreach(QLineEdit* lineEdit, fields)
            dogVars << lineEdit->text();

        this->s.addDogByVars(dogVars[0].toStdString(), dogVars[1].toStdString(), dogVars[2].toInt(), dogVars[3].toStdString());
        refresh_table();
    }
}

void MainWindow::removeDogPrompt()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);

    form.addRow(new QLabel("Remove dog..."));

    QList<QString> labels;
    labels << "Id: ";

    QList<QLineEdit* > fields;
    for(int i = 0; i < 1; ++i)
    {
        QLineEdit *lineEdit = new QLineEdit(&dialog);
        QString label = labels[i];
        form.addRow(label, lineEdit);

        fields << lineEdit;
    }

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    QList<QString> dogVars;

    if(dialog.exec() == QDialog::Accepted)
    {
        foreach(QLineEdit* lineEdit, fields)
            dogVars << lineEdit->text();

        this->s.removeDogById(dogVars[0].toInt());
        refresh_table();
    }
}

void MainWindow::updateDogPrompt()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);

    form.addRow(new QLabel("Update dog..."));

    QList<QString> labels;
    labels << "Id: ";
    labels << "New Name: ";
    labels << "New Breed: ";
    labels << "New Age: ";
    labels << "New Photo Link: ";

    QList<QLineEdit* > fields;
    for(int i = 0; i < 5; ++i)
    {
        QLineEdit *lineEdit = new QLineEdit(&dialog);
        QString label = labels[i];
        form.addRow(label, lineEdit);

        fields << lineEdit;
    }

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    QList<QString> dogVars;

    if(dialog.exec() == QDialog::Accepted)
    {
        foreach(QLineEdit* lineEdit, fields)
            dogVars << lineEdit->text();

        this->s.updateDogById(dogVars[0].toInt(), dogVars[1].toStdString(), dogVars[2].toStdString(), dogVars[3].toInt(), dogVars[4].toStdString());
        refresh_table();
    }
}

void MainWindow::exit()
{
    this->close();
}

void MainWindow::refresh_table()
{
    QList<QStandardItem*> items;

    model->clear();

    for(auto d : s.getAllDogs())
    {
        items.append(new QStandardItem(QVariant(d.get_id()).toString()));
        items.append(new QStandardItem(d.get_name().c_str()));
        items.append(new QStandardItem(d.get_breed().c_str()));
        items.append(new QStandardItem(QVariant(d.get_age()).toString()));
        items.append(new QStandardItem(d.get_photoLink().c_str()));

        model->appendRow(items);
        items.clear();
    }
}

void MainWindow::viewDogs()
{
    QGridLayout* gLay = new QGridLayout();
    QPushButton* btnNext = new QPushButton("&Next");
    QPushButton* btnAdopt = new QPushButton("&Adopt");
    QPushButton* btnOpenAdoptionList = new QPushButton("&Open adoption list");

    QObject::connect(btnNext, SIGNAL(clicked()), this, SLOT(nextDog()));
    QObject::connect(btnAdopt, SIGNAL(clicked()), this, SLOT(adoptDog()));
    QObject::connect(btnOpenAdoptionList, SIGNAL(clicked()), this, SLOT(openAdoptionList()));

    pic->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    gLay->addWidget(pic, 0, 0, 3, 3);
    gLay->addWidget(lblName, 3, 0, 1, 3);
    gLay->addWidget(lblBreed, 4, 0, 1, 3);
    gLay->addWidget(lblAge, 5, 0, 1, 3);
    gLay->addWidget(btnNext, 6, 0, 1, 3);
    gLay->addWidget(btnAdopt, 7, 0, 1, 3);
    gLay->addWidget(btnOpenAdoptionList, 8, 0, 1, 3);

    std::vector<Dog> dogs = s.getAllDogs();

    lblName->setText(QVariant("Name: ").toString() + dogs[ind].get_name().c_str());
    lblBreed->setText(QVariant("Breed: ").toString() + dogs[ind].get_breed().c_str());
    lblAge->setText(QVariant("Age: ").toString() + QVariant(dogs[ind].get_age()).toString());

    QUrl imageUrl(dogs[ind].get_photoLink().c_str());
    //QUrl imageUrl("https://unsplash.com/photos/zuvvVpfsMJE");
    m_pImgCtrl = new FileDownloader(imageUrl, this);

    connect(m_pImgCtrl, SIGNAL(downloaded()), this, SLOT(loadImage()));

    QWidget* w = new QWidget();
    w->setMinimumSize(500, 700);
    w->setLayout(gLay);
    w->show();
}

void MainWindow::filterDogs()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);

    form.addRow(new QLabel("Filter dogs..."));

    QList<QString> labels;
    labels << "Breed: ";
    labels << "Maximum age: ";

    QList<QLineEdit* > fields;
    for(int i = 0; i < 2; ++i)
    {
        QLineEdit *lineEdit = new QLineEdit(&dialog);
        QString label = labels[i];
        form.addRow(label, lineEdit);

        fields << lineEdit;
    }

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    QList<QString> dogVars;

    if(dialog.exec() == QDialog::Accepted)
    {
        foreach(QLineEdit* lineEdit, fields)
        {
            dogVars << lineEdit->text();
        }

        std::vector<Dog> dogs = s.filterDogsBreedAge(dogVars[0].toStdString(), dogVars[1].toInt());

        QGridLayout* gLay = new QGridLayout();
        QTableView* filteredView = new QTableView();
        QStandardItemModel* filteredModel = new QStandardItemModel();

        filteredModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        filteredModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
        filteredModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Breed"));
        filteredModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
        filteredModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Photo link"));

        filteredView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        filteredView->setModel(filteredModel);
        filteredView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        filteredView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        QList<QStandardItem*> items;

        for(auto d : dogs)
        {
            items.append(new QStandardItem(QVariant(d.get_id()).toString()));
            items.append(new QStandardItem(d.get_name().c_str()));
            items.append(new QStandardItem(d.get_breed().c_str()));
            items.append(new QStandardItem(QVariant(d.get_age()).toString()));
            items.append(new QStandardItem(d.get_photoLink().c_str()));

            filteredModel->appendRow(items);
            items.clear();
        }

        gLay->addWidget(filteredView);

        QWidget* w = new QWidget();
        w->setLayout(gLay);
        w->show();
    }
}

void MainWindow::loadImage()
{
    QPixmap pm;
    pm.loadFromData(m_pImgCtrl->downloadedData());
    pic->setPixmap(pm);
}

void MainWindow::adoptDog()
{
    std::vector<Dog> dogs = s.getAllDogs();
    s.addToAdoptionList(dogs[ind]);
    s.removeDogById(dogs[ind].get_id());

    refresh_adoption_table();
    refresh_table();

    if(s.getNrDogs() == 0)
        this->close();

    nextDog();
}

void MainWindow::openAdoptionList()
{
    st->write_to_file(s);
    st->open_file();
}

void MainWindow::nextDog()
{
    ind = (ind + 1) % s.getNrDogs();
    std::vector<Dog> dogs = s.getAllDogs();

    lblName->setText(QVariant("Name: ").toString() + dogs[ind].get_name().c_str());
    lblBreed->setText(QVariant("Breed: ").toString() + dogs[ind].get_breed().c_str());
    lblAge->setText(QVariant("Age: ").toString() + QVariant(dogs[ind].get_age()).toString());
}

void MainWindow::refresh_adoption_table()
{
    QList<QStandardItem*> items;

    adoptionModel->clear();

    for(auto d : s.getAdoptedDogs())
    {
        items.append(new QStandardItem(QVariant(d.get_id()).toString()));
        items.append(new QStandardItem(d.get_name().c_str()));
        items.append(new QStandardItem(d.get_breed().c_str()));
        items.append(new QStandardItem(QVariant(d.get_age()).toString()));
        items.append(new QStandardItem(d.get_photoLink().c_str()));

        adoptionModel->appendRow(items);
        items.clear();
    }
}

void MainWindow::undo()
{
    this->s.undo();
    refresh_table();
}

void MainWindow::redo()
{
    this->s.redo();
    refresh_table();
}
