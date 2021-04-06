#include "QListStorageWidget.hpp"

namespace Ui {

QListStorageWidget::QListStorageWidget(QWidget* parent) 
    : QListWidget(parent)
{
    this->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
    this->setMaximumSize(this->maximumWidth(), 100);

}

void QListStorageWidget::addItem(const std::string& item) {
    this->QListWidget::addItem(QString::fromStdString(item)); //Call addItem function from base class, hence QListWidget:: needed
}

void QListStorageWidget::addItem(const QString& item) {
    this->QListWidget::addItem(item); //Call addItem function from base class, hence QListWidget:: needed
}

void QListStorageWidget::addItemWithStorage(const Game::Item& item) {
    QListStorageInfo info = {item, this->QListWidget::count()};
    this->QListWidget::addItem(QString::fromStdString(item.GetName()));
    storage.push_back(info);
}

void QListStorageWidget::removeItemByStorageIndex(const size_t index) {
    if (index >= storage.size()) {
        return;
    }

    this->QListWidget::takeItem(storage[index].row);
    storage.erase(storage.begin()+index);
}

void QListStorageWidget::removeItemWithStorage(const Game::Item& item) {
    for (size_t i = 0; i < storage.size(); i++) {
        if (item == storage[i].item) {
            removeItemByStorageIndex(i);
            break;
        }
    }
}

bool QListStorageWidget::getItemFromStorage(const int row, Game::Item& data, bool remove) {
    for (size_t i = 0; i < storage.size(); i++) {
        if (row == storage[i].row) {
            data = storage[i].item;
            if (remove) {
                removeItemByStorageIndex(i);
            }
            return true;
        }
    }

    return false;
}

bool QListStorageWidget::getItemFromStorage(const QListWidgetItem* item, Game::Item& data, bool remove) {
    int row = this->QListWidget::row(item);
    if (row < 0 || row >= this->QListWidget::count()) {
        return false;
    }
    return this->getItemFromStorage(row, data, remove);
}

void QListStorageWidget::clear() {
    this->QListWidget::clear();
    this->storage.clear();
}

}
