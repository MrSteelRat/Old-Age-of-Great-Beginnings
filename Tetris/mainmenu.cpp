#include "mainmenu.h"
#include "ui_menupause.h"

MainMenu::MainMenu(QObject *parent)
    : QAbstractItemModel(parent)
{
    ui->setupUi(this);
}

// QVariant MainMenu::headerData(int section, Qt::Orientation orientation, int role) const
// {
//     // FIXME: Implement me!
// }

// QModelIndex MainMenu::index(int row, int column, const QModelIndex &parent) const
// {
//     // FIXME: Implement me!
// }

// QModelIndex MainMenu::parent(const QModelIndex &index) const
// {
//     // FIXME: Implement me!
// }

// int MainMenu::rowCount(const QModelIndex &parent) const
// {
//     if (!parent.isValid())
//         return 0;

//     // FIXME: Implement me!
// }

// int MainMenu::columnCount(const QModelIndex &parent) const
// {
//     if (!parent.isValid())
//         return 0;

//     // FIXME: Implement me!
// }

// QVariant MainMenu::data(const QModelIndex &index, int role) const
// {
//     if (!index.isValid())
//         return QVariant();

//     // FIXME: Implement me!
//     return QVariant();
// }
