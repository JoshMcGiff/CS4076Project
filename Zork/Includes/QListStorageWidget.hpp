#ifndef QLISTSTORAGEWIDGET_HPP
#define QLISTSTORAGEWIDGET_HPP

#include <QListWidget>
#include <string>
#include <vector>

namespace Ui {

/*  Custom QListWidget
    A templated class for allowing to store data alongside a QListWidget
    Requires type to implement operator== and a "std::string GetName()" method
*/

template <typename Type>
class QListStorageWidget : public QListWidget
{
private:
    struct QListStorageInfo {
        Type item;
        int row;
    };

    std::vector<QListStorageInfo> storage;


    inline void removeItemByStorageIndex(const size_t index) {
        if (index >= storage.size()) {
            return;
        }

        this->QListWidget::takeItem(storage[index].row);
        storage.erase(storage.begin()+index);
    }

public:
    QListStorageWidget(QWidget* parent = nullptr) : QListWidget(parent)
    {
        this->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        this->setMaximumSize(this->maximumWidth(), 100);
    }

    void addItem(const std::string& item)  {
        this->QListWidget::addItem(QString::fromStdString(item)); //Call addItem function from base class, hence QListWidget:: needed
    }

    void addItemWithStorage(const Type& item) {
        QListStorageInfo info = {item, this->QListWidget::count()};
        this->QListWidget::addItem(QString::fromStdString(item.GetName()));
        storage.push_back(info);
    }

    void removeItemWithStorage(const Type& item) {
        for (size_t i = 0; i < storage.size(); i++) {
            if (item == storage[i].item) {
                removeItemByStorageIndex(i);
                break;
            }
        }
    }

    bool getItemFromStorage(const int row, Type& data, bool remove = false) {
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

    bool getItemFromStorage(const QListWidgetItem* item, Type& data, bool remove = false) {
        int row = this->QListWidget::row(item);
        if (row < 0 || row >= this->QListWidget::count()) {
            return false;
        }
        return this->getItemFromStorage(row, data, remove);
    }

    void clear() {
        this->QListWidget::clear();
        this->storage.clear();
    }

};

} //namespace Ui

#endif
