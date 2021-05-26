#include "MyModel.h"

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
   return this->rows;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return this->columns;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{

    return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        switch(section)
        {
        case 0:
            return QString("ID");
        case 1:
            return QString("Name");
        case 2:
            return QString("Breed");
        case 3:
            return QString("Age");
        case 4:
            return QString("Photo link");
        }

    return QVariant();
}
