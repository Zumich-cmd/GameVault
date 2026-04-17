#include "addgamedialog.h"
#include "ui_addgamedialog.h"
#include "buttonhoveranimator.h"
#include <QMessageBox>
#include <QFileDialog>

AddGameDialog::AddGameDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddGameDialog)
{
    ui->setupUi(this);

    // ФІКС БІЛОЇ ТЕМИ: Вбиваємо всі захардкоджені кольори з Qt Designer
    this->setStyleSheet("");
    QList<QWidget*> widgets = this->findChildren<QWidget*>();
    for(QWidget* w : widgets) {
        QString cName = w->metaObject()->className();
        if(cName == "QFrame" || cName == "QWidget") {
            w->setStyleSheet("background: transparent; border: none;");
        }
    }

    ui->posterPathLineEdit->setReadOnly(true);

    ui->genreComboBox->clear();
    ui->genreComboBox->addItems({"RPG", "Action", "Roguelike", "Metroidvania", "Steam Import"});

    ui->platformComboBox->clear();
    ui->platformComboBox->addItems({"Steam", "Epic Games", "Other"});

    connect(ui->choosePosterButton, &QPushButton::clicked, this, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, "Обрати постер", "", "Images (*.png *.jpg *.jpeg *.webp)");
        if (!fileName.isEmpty()) ui->posterPathLineEdit->setText(fileName);
    });

    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    connect(ui->saveGameButton, &QPushButton::clicked, this, [this]() {
        if (ui->titleLineEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Помилка", "Введіть назву гри");
            return;
        }
        if (ui->openedAchievementsSpinBox->value() > ui->totalAchievementsSpinBox->value()) {
            QMessageBox::warning(this, "Помилка", "Відкритих досягнень не може бути більше, ніж загальна кількість");
            return;
        }
        accept();
    });

    ui->choosePosterButton->setCursor(Qt::PointingHandCursor);
    ui->saveGameButton->setCursor(Qt::PointingHandCursor);
    ui->cancelButton->setCursor(Qt::PointingHandCursor);

    installHoverAnimation(ui->choosePosterButton, ButtonHoverPalette{QColor("#21262d"), QColor("#30363d"), QColor("#1b2026"), QColor(), QColor(), false}, this);
    installHoverAnimation(ui->saveGameButton, ButtonHoverPalette{QColor("#c62828"), QColor("#e53935"), QColor("#a22222"), QColor(), QColor(), false}, this);
    installHoverAnimation(ui->cancelButton, ButtonHoverPalette{QColor("#21262d"), QColor("#30363d"), QColor("#1b2026"), QColor(), QColor(), false}, this);
}

AddGameDialog::~AddGameDialog() { delete ui; }

void AddGameDialog::setGameData(const QString& title, const QString& genre, const QString& platform,
                                int hours, int totalAchiev, int openedAchiev, const QString& posterPath)
{
    ui->titleLineEdit->setText(title);
    ui->genreComboBox->setCurrentText(genre);
    ui->platformComboBox->setCurrentText(platform);
    ui->hoursSpinBox->setValue(hours);
    ui->totalAchievementsSpinBox->setValue(totalAchiev);
    ui->openedAchievementsSpinBox->setValue(openedAchiev);
    ui->posterPathLineEdit->setText(posterPath);
}

QString AddGameDialog::getTitle() const { return ui->titleLineEdit->text(); }
QString AddGameDialog::getGenre() const { return ui->genreComboBox->currentText(); }
QString AddGameDialog::getPlatform() const { return ui->platformComboBox->currentText(); }
int AddGameDialog::getHours() const { return ui->hoursSpinBox->value(); }
int AddGameDialog::getTotalAchievements() const { return ui->totalAchievementsSpinBox->value(); }
int AddGameDialog::getOpenedAchievements() const { return ui->openedAchievementsSpinBox->value(); }
QString AddGameDialog::getPosterPath() const { return ui->posterPathLineEdit->text(); }