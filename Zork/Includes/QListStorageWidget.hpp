#ifndef QLISTSTORAGEWIDGET_HPP
#define QLISTSTORAGEWIDGET_HPP

#include <QListWidget>
#include <string>
#include "Item.hpp"
#include "Zork.hpp"

namespace Ui {

class QListStorageWidget : public QListWidget
{
    Q_OBJECT
private:
    void removeItemByStorageIndex(const size_t index);

    struct QListStorageInfo {
        Game::Item item;
        int row;
    };

    std::vector<QListStorageInfo> storage;
public:
    QListStorageWidget(QWidget* parent = nullptr);

    void addItem(const std::string& item);
    void addItem(const QString& item);
    void addItemWithStorage(const Game::Item& item);
    void removeItemWithStorage(const Game::Item& item);

    bool getItemFromStorage(const int row, Game::Item& data, bool remove = false);
    bool getItemFromStorage(const QListWidgetItem* item, Game::Item& data, bool remove = false);

    void clear();
};

} //namespace Ui

#endif
