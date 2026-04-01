#include "addgamedialog.h"
#include "ui_addgamedialog.h"

// Для відображення повідомлень про помилки
#include <QMessageBox>

// Конструктор діалогу
AddGameDialog::AddGameDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddGameDialog)
{
    // Ініціалізація UI
    ui->setupUi(this);

    // Заповнення списку жанрів
    ui->genreComboBox->addItems({"RPG", "Action"});

    // Заповнення списку платформ
    ui->platformComboBox->addItems({"Steam", "Epic"});

    // Обробка кнопки "Скасувати" (закриття вікна)
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &QDialog::reject);

    // Обробка кнопки "Зберегти"
    connect(ui->saveGameButton, &QPushButton::clicked, this, [this]() {

        // Перевірка: чи введена назва гри
        if (ui->titleLineEdit->text().isEmpty()) {

            // Вивід попередження
            QMessageBox::warning(this, "Помилка", "Введіть назву гри");

            // Зупинка виконання
            return;
        }

        // Закриття діалогу з підтвердженням
        accept();
    });
}

// Деструктор (звільнення пам'яті)
AddGameDialog::~AddGameDialog()
{
    delete ui;
}

// ===== ГЕТЕРИ =====

// Отримання назви гри
QString AddGameDialog::getTitle() const {
    return ui->titleLineEdit->text();
}

// Отримання жанру
QString AddGameDialog::getGenre() const {
    return ui->genreComboBox->currentText();
}

// Отримання платформи
QString AddGameDialog::getPlatform() const {
    return ui->platformComboBox->currentText();
}

// Отримання кількості годин
int AddGameDialog::getHours() const {
    return ui->hoursSpinBox->value();
}

// Отримання загальної кількості досягнень
int AddGameDialog::getTotalAchievements() const {
    return ui->totalAchievementsSpinBox->value();
}

// Отримання відкритих досягнень
int AddGameDialog::getOpenedAchievements() const {
    return ui->openedAchievementsSpinBox->value();
}