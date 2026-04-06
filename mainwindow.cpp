#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "achievementsdialog.h"

// Для групування кнопок
#include <QButtonGroup>

// Для елементів списку
#include <QListWidgetItem>

// Конструктор головного вікна
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Ініціалізація UI
    ui->setupUi(this);

    // Назва вікна
    setWindowTitle("GameVault");

    // Перемикач sidebar (активна тільки одна кнопка)
    QButtonGroup *group = new QButtonGroup(this);

    // Додаємо кнопки у групу
    group->addButton(ui->libraryButton);
    group->addButton(ui->achievementsButton);
    group->addButton(ui->steamImportButton);
    group->addButton(ui->settingsButton);

    // Дозволяємо тільки одну активну кнопку
    group->setExclusive(true);

    // Встановлюємо активну кнопку за замовчуванням
    ui->libraryButton->setChecked(true);

    // Прибираємо текст у progress bar
    ui->progressBar->setTextVisible(false);

    // Очищення та заповнення фільтрів
    ui->genreComboBox->clear();
    ui->genreComboBox->addItems({"Жанр", "RPG", "Action", "Roguelike", "Metroidvania"});

    ui->statusComboBox->clear();
    ui->statusComboBox->addItems({"Статус", "Усі"});

    ui->platformComboBox->clear();
    ui->platformComboBox->addItems({"Платформа", "Steam"});

    // Встановлення кількості ігор
    ui->gamesCountLabel->setText("5 ігор");

    // Очищення списку ігор
    ui->gamesList->clear();

    // ===== ТЕСТОВІ ІГРИ =====

    QString item1 = QString("#%1    %2    %3    %4h    %5/%6")
                        .arg(1)
                        .arg("Elden Ring", -20)
                        .arg("RPG", -14)
                        .arg(145, 3)
                        .arg(39, 2)
                        .arg(50, 2);

    QString item2 = QString("#%1    %2    %3    %4h    %5/%6")
                        .arg(2)
                        .arg("Cyberpunk 2077", -20)
                        .arg("RPG", -14)
                        .arg(120, 3)
                        .arg(32, 2)
                        .arg(57, 2);

    QString item3 = QString("#%1    %2    %3    %4h    %5/%6")
                        .arg(3)
                        .arg("Hades", -20)
                        .arg("Roguelike", -14)
                        .arg(64, 3)
                        .arg(21, 2)
                        .arg(49, 2);

    QString item4 = QString("#%1    %2    %3    %4h    %5/%6")
                        .arg(4)
                        .arg("Hollow Knight", -20)
                        .arg("Metroidvania", -14)
                        .arg(71, 3)
                        .arg(47, 2)
                        .arg(63, 2);

    QString item5 = QString("#%1    %2    %3    %4h    %5/%6")
                        .arg(5)
                        .arg("Sekiro", -20)
                        .arg("Action", -14)
                        .arg(58, 3)
                        .arg(28, 2)
                        .arg(34, 2);

    // Додавання ігор у список
    ui->gamesList->addItem(item1);
    ui->gamesList->addItem(item2);
    ui->gamesList->addItem(item3);
    ui->gamesList->addItem(item4);
    ui->gamesList->addItem(item5);

    // Обробка кліку по списку
    connect(ui->gamesList, &QListWidget::itemClicked,
            this, &MainWindow::onGameSelected);

    // Вибір першої гри при запуску
    ui->gamesList->setCurrentRow(0);

    // Оновлення правої панелі
    onGameSelected();

    // Відкриття вікна досягнень
    connect(ui->viewAchievementsButton, &QPushButton::clicked,
            this, &MainWindow::openAchievementsDialog);
}

// Деструктор
MainWindow::~MainWindow()
{
    delete ui;
}

// Відкриття діалогу досягнень
void MainWindow::openAchievementsDialog()
{
    AchievementsDialog dialog(this);

    // Передаємо назву поточної гри
    dialog.setGameTitle(ui->gameNameLabel->text());

    dialog.exec();
}

// Обробка вибору гри
void MainWindow::onGameSelected()
{
    // Отримання вибраного елемента
    QListWidgetItem *item = ui->gamesList->currentItem();

    // Якщо нічого не вибрано — вихід
    if (!item) return;

    // Текст вибраного елемента
    QString text = item->text();

    // ===== Elden Ring =====
    if (text.contains("Elden Ring")) {

        ui->gameNameLabel->setText("Elden Ring");
        ui->genreInfoLabel->setText("Жанр: RPG");
        ui->hoursInfoLabel->setText("Ігрові години: 145");
        ui->totalAchievementsInfoLabel->setText("Всього: 50");
        ui->openedAchievementsInfoLabel->setText("Відкрито: 39");
        ui->platformInfoLabel->setText("Платформа: Steam");

        ui->progressBar->setValue(78);
        ui->progressInfoLabel->setText("(39/50)");
        ui->coverLabel->setText("ELDEN RING");

        ui->recentAchievementsList->clear();
        ui->recentAchievementsList->addItem("Kill the Dragon");
        ui->recentAchievementsList->addItem("Hidden Path");
        ui->recentAchievementsList->addItem("First Victory");
    }

    // ===== Cyberpunk =====
    if (text.contains("Cyberpunk")) {

        ui->gameNameLabel->setText("Cyberpunk 2077");
        ui->genreInfoLabel->setText("Жанр: RPG");
        ui->hoursInfoLabel->setText("Ігрові години: 120");
        ui->totalAchievementsInfoLabel->setText("Всього: 57");
        ui->openedAchievementsInfoLabel->setText("Відкрито: 32");
        ui->platformInfoLabel->setText("Платформа: Steam");

        ui->progressBar->setValue(56);
        ui->progressInfoLabel->setText("(32/57)");
        ui->coverLabel->setText("CYBERPUNK 2077");

        ui->recentAchievementsList->clear();
        ui->recentAchievementsList->addItem("The Fool");
        ui->recentAchievementsList->addItem("The Lovers");
        ui->recentAchievementsList->addItem("The Hermit");
    }

    // ===== Hades =====
    if (text.contains("Hades")) {

        ui->gameNameLabel->setText("Hades");
        ui->genreInfoLabel->setText("Жанр: Roguelike");
        ui->hoursInfoLabel->setText("Ігрові години: 64");
        ui->totalAchievementsInfoLabel->setText("Всього: 49");
        ui->openedAchievementsInfoLabel->setText("Відкрито: 21");
        ui->platformInfoLabel->setText("Платформа: Steam");

        ui->progressBar->setValue(43);
        ui->progressInfoLabel->setText("(21/49)");
        ui->coverLabel->setText("HADES");

        ui->recentAchievementsList->clear();
        ui->recentAchievementsList->addItem("Escape Attempt");
        ui->recentAchievementsList->addItem("The Bone Hydra");
        ui->recentAchievementsList->addItem("Friends Forever");
    }

    // ===== Hollow Knight =====
    if (text.contains("Hollow Knight")) {

        ui->gameNameLabel->setText("Hollow Knight");
        ui->genreInfoLabel->setText("Жанр: Metroidvania");
        ui->hoursInfoLabel->setText("Ігрові години: 71");
        ui->totalAchievementsInfoLabel->setText("Всього: 63");
        ui->openedAchievementsInfoLabel->setText("Відкрито: 47");
        ui->platformInfoLabel->setText("Платформа: Steam");

        ui->progressBar->setValue(74);
        ui->progressInfoLabel->setText("(47/63)");
        ui->coverLabel->setText("HOLLOW KNIGHT");

        ui->recentAchievementsList->clear();
        ui->recentAchievementsList->addItem("False Knight");
        ui->recentAchievementsList->addItem("Soul Master");
        ui->recentAchievementsList->addItem("Dream Nail");
    }

    // ===== Sekiro =====
    if (text.contains("Sekiro")) {

        ui->gameNameLabel->setText("Sekiro");
        ui->genreInfoLabel->setText("Жанр: Action");
        ui->hoursInfoLabel->setText("Ігрові години: 58");
        ui->totalAchievementsInfoLabel->setText("Всього: 34");
        ui->openedAchievementsInfoLabel->setText("Відкрито: 28");
        ui->platformInfoLabel->setText("Платформа: Steam");

        ui->progressBar->setValue(82);
        ui->progressInfoLabel->setText("(28/34)");
        ui->coverLabel->setText("SEKIRO");

        ui->recentAchievementsList->clear();
        ui->recentAchievementsList->addItem("Gyoubu Oniwa");
        ui->recentAchievementsList->addItem("Shinobi Prosthetic");
        ui->recentAchievementsList->addItem("Immortal Severance");
    }
    //Короче, бля, вроде бы красиво написал комментарии и надеюсь, ты здесь не заблудишься, 4 часа утра, я уже не особо что-то здесь понимаю, допишу, как только проснусь
}