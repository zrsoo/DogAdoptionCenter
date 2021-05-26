#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Service.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QLabel>
#include "filedownloader.h"
#include "Storage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void populate_table_view(QStandardItemModel* model);
    void refresh_table();
    void refresh_adoption_table();

private slots:
    void dialogModeIsFinished(int);
    void dialogStorageIsFinished(int);

    void addDogPrompt();
    void removeDogPrompt();
    void updateDogPrompt();
    void undo();
    void redo();
    void exit();

    void viewDogs();
    void filterDogs();

    void loadImage();

    void adoptDog();
    void openAdoptionList();
    void nextDog();

private:
    Ui::MainWindow *ui;
    bool admin = false;
    bool user = false;

    bool HTML = false;

    Service s;

    QTableView* view = new QTableView();
    QStandardItemModel* model = new QStandardItemModel(1, 5, view);

    QTableView* adoptionView = new QTableView();
    QStandardItemModel* adoptionModel = new QStandardItemModel(1, 5, adoptionView);

    int ind = 0;
    QLabel* pic = new QLabel("LABEL");
    FileDownloader* m_pImgCtrl;
    QLabel* lblName = new QLabel("Name: ");
    QLabel* lblBreed = new QLabel("Breed: ");
    QLabel* lblAge = new QLabel("Age: ");

    Storage* st;
};
#endif // MAINWINDOW_H
