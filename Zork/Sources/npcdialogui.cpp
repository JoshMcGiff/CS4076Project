#include "npcdialogui.hpp"
#include "ui_npcdialogui.h"

NpcDialogUI::NpcDialogUI(const Game::Npc& npc, QWidget *parent) :
    QDialog(parent), ui(new Ui::NpcDialogUI), myNpc(npc), myResult(NpcDialogUIResult_No)
{
    ui->setupUi(this);
    this->npcImagePath = GetNpcImageStr(this->myNpc.GetNpcID());
    this->setWindowTitle(QString::fromStdString(myNpc.GetNpcName()));

    if (this->npcImagePath) {
        ui->dialogueBox->textCursor().insertText(QString::fromStdString(myNpc.GetNpcQuestion()));
        QPixmap pic(this->npcImagePath);
        ui->imageLabel->setPixmap(pic.scaled(ui->imageLabel->width(), ui->imageLabel->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->imageLabel->adjustSize();
    }
}

NpcDialogUI::~NpcDialogUI() {
    delete ui;
}

void NpcDialogUI::showEvent(QShowEvent*) {
    if (this->npcImagePath == nullptr) {
        this->close();
    }
}

const char* NpcDialogUI::GetNpcImageStr(NpcID id) {
    switch (id) {
    case NpcID::Nicki:
        return ":/new/Images/Images/npcNicki.png";
        break;
    
    case NpcID::Bandit:
        return ":/new/Images/Images/npcBandit.png";
        break;
    
    case NpcID::Twitter:
        return ":/new/Images/Images/npcTwitter.png";
        break;
    
    case NpcID::Gamer:
        return ":/new/Images/Images/npcGamer.png";
        break;
    
    case NpcID::Code:
        return ":/new/Images/Images/npcCode.png";
        break;
    
    default:
        return nullptr;
        break;
    }
}


void NpcDialogUI::on_buttonBox_clicked(QAbstractButton *button) {
    if (reinterpret_cast<QPushButton *>(button) == ui->buttonBox->button(QDialogButtonBox::Yes)) {
        ui->dialogueBox->clear();
        ui->dialogueBox->textCursor().insertText(QString::fromStdString(myNpc.GetNpcResponseCorrect()));
        ui->buttonBox->clear();
        ui->buttonBox->addButton(QDialogButtonBox::Close);
        this->myResult = NpcDialogUIResult_Yes;

    }

    else if (reinterpret_cast<QPushButton *>(button) == ui->buttonBox->button(QDialogButtonBox::No)) {
        ui->dialogueBox->clear();
        ui->dialogueBox->textCursor().insertText(QString::fromStdString(myNpc.GetNpcResponseIncorrect()));
        ui->buttonBox->clear();
        ui->buttonBox->addButton(QDialogButtonBox::Close);
        this->myResult = NpcDialogUIResult_No;
    }

    else if (reinterpret_cast<QPushButton *>(button) == ui->buttonBox->button(QDialogButtonBox::Close)) {
        this->done(this->myResult);
    }
}
