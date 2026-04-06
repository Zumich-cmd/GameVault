#include "achievementsdialog.h"
#include "ui_achievementsdialog.h"

// Конструктор діалогу
AchievementsDialog::AchievementsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AchievementsDialog)
{
    // Ініціалізація UI
    ui->setupUi(this);

    // Заголовок вікна
    setWindowTitle("Досягнення");

    // Тестові досягнення
    ui->achievementsList->addItem("☑ Перемогти першого боса");
    ui->achievementsList->addItem("☑ Відкрити приховану локацію");
    ui->achievementsList->addItem("☐ Зібрати всі артефакти");
    ui->achievementsList->addItem("☐ Завершити гру на 100%");
    ui->achievementsList->addItem("☐ Отримати секретну кінцівку");

    // Закриття вікна
    connect(ui->closeButton, &QPushButton::clicked,
            this, &QDialog::accept);
}

// Деструктор
AchievementsDialog::~AchievementsDialog()
{
    delete ui;
}

// Встановлення назви гри
void AchievementsDialog::setGameTitle(const QString &title)
{
    ui->gameTitleLabel->setText(title);
}