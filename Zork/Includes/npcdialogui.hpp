#ifndef NPCDIALOGUI_HPP
#define NPCDIALOGUI_HPP

#include <QDialog>
#include <QAbstractButton>
#include "Npc.hpp"

namespace Ui {
class NpcDialogUI;
}

enum NpcDialogUIResult : int {
    NpcDialogUIResult_No = 0,
    NpcDialogUIResult_Yes = 1
};

class NpcDialogUI : public QDialog
{
    Q_OBJECT

public:
    explicit NpcDialogUI(const Game::Npc& npc, QWidget *parent = nullptr);
    ~NpcDialogUI();
protected:
    void showEvent(QShowEvent*) override;
private slots:
    void on_buttonBox_clicked(QAbstractButton* button);

private:
    const char* GetNpcImageStr(NpcID id);
    Ui::NpcDialogUI *ui;
    const char* npcImagePath;
    Game::Npc myNpc;
    int myResult;
};

#endif // NPCDIALOGUI_HPP
