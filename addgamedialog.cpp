#include "addgamedialog.h"
#include "ui_addgamedialog.h"
#include "buttonhoveranimator.h"

// Для відображення повідомлень про помилки
#include <QMessageBox>

// Для вибору постера
#include <QFileDialog>

// Конструктор діалогу
AddGameDialog::AddGameDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddGameDialog)
{
    // Ініціалізація UI
    ui->setupUi(this);

    // Поле шляху до постера тільки для читання
    ui->posterPathLineEdit->setReadOnly(true);

    // Заповнення списку жанрів
    ui->genreComboBox->addItems({"RPG", "Action", "Roguelike", "Metroidvania"});

    // Заповнення списку платформ
    ui->platformComboBox->addItems({"Steam", "Epic", "Other"});

    // Обробка кнопки вибору постера
    connect(ui->choosePosterButton, &QPushButton::clicked, this, [this]() {
        QString fileName = QFileDialog::getOpenFileName(
            this,
            "Обрати постер",
            "",
            "Images (*.png *.jpg *.jpeg *.webp)"
            );

        if (!fileName.isEmpty()) {
            ui->posterPathLineEdit->setText(fileName);
        }
    });

    // Обробка кнопки "Скасувати"
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &QDialog::reject);

    // Обробка кнопки "Зберегти"
    connect(ui->saveGameButton, &QPushButton::clicked, this, [this]() {

        // Перевірка: чи введена назва гри
        if (ui->titleLineEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Помилка", "Введіть назву гри");
            return;
        }

        // Перевірка: відкритих досягнень не може бути більше за загальну кількість
        if (ui->openedAchievementsSpinBox->value() > ui->totalAchievementsSpinBox->value()) {
            QMessageBox::warning(this, "Помилка", "Відкритих досягнень не може бути більше, ніж загальна кількість");
            return;
        }

        // Закриття діалогу з підтвердженням
        accept();
    });

    // Ставимо курсор-указівник для інтерактивних кнопок
    ui->choosePosterButton->setCursor(Qt::PointingHandCursor);
    ui->saveGameButton->setCursor(Qt::PointingHandCursor);
    ui->cancelButton->setCursor(Qt::PointingHandCursor);

    // Додаємо плавну анімацію зміни кольору при наведенні
    installHoverAnimation(
        ui->choosePosterButton,
        ButtonHoverPalette{QColor("#21262d"), QColor("#30363d"), QColor("#1b2026"), QColor(), QColor(), false},
        this
        );
    installHoverAnimation(
        ui->saveGameButton,
        ButtonHoverPalette{QColor("#c62828"), QColor("#e53935"), QColor("#a22222"), QColor(), QColor(), false},
        this
        );
    installHoverAnimation(
        ui->cancelButton,
        ButtonHoverPalette{QColor("#21262d"), QColor("#30363d"), QColor("#1b2026"), QColor(), QColor(), false},
        this
        );
}

// Деструктор
AddGameDialog::~AddGameDialog()
{
    delete ui;
}

// ===== ГЕТЕРИ =====

// Отримання назви гри
QString AddGameDialog::getTitle() const
{
    return ui->titleLineEdit->text();
}

// Отримання жанру
QString AddGameDialog::getGenre() const
{
    return ui->genreComboBox->currentText();
}

// Отримання платформи
QString AddGameDialog::getPlatform() const
{
    return ui->platformComboBox->currentText();
}

// Отримання кількості годин
int AddGameDialog::getHours() const
{
    return ui->hoursSpinBox->value();
}

// Отримання загальної кількості досягнень
int AddGameDialog::getTotalAchievements() const
{
    return ui->totalAchievementsSpinBox->value();
}

// Отримання відкритих досягнень
int AddGameDialog::getOpenedAchievements() const
{
    return ui->openedAchievementsSpinBox->value();
}

// Отримання шляху до постера
QString AddGameDialog::getPosterPath() const
{
    return ui->posterPathLineEdit->text();
}