#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addgamedialog.h"
#include "achievementsdialog.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QCoreApplication>

#include <QButtonGroup>
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
    group->addButton(ui->libraryButton);
    group->addButton(ui->achievementsButton);
    group->addButton(ui->steamImportButton);
    group->addButton(ui->settingsButton);
    group->setExclusive(true);
    ui->libraryButton->setChecked(true);

    // Прибираємо текст у progress bar
    ui->progressBar->setTextVisible(false);

    // Очищення та заповнення фільтрів
    ui->genreComboBox->clear();
    ui->genreComboBox->addItems({"Жанр", "RPG", "Action", "Roguelike", "Metroidvania"});

    ui->statusComboBox->clear();
    ui->statusComboBox->addItems({"Статус", "Усі"});

    ui->platformComboBox->clear();
    ui->platformComboBox->addItems({"Платформа", "Steam", "Epic Games", "Other"});

    // Очищення списку ігор
    ui->gamesList->clear();

    // Підключення сигналів
    connect(ui->gamesList, &QListWidget::itemClicked,
            this, &MainWindow::onGameSelected);

    connect(ui->addGameButton, &QPushButton::clicked,
            this, &MainWindow::onAddGameClicked);

    connect(ui->bottomAddGameButton, &QPushButton::clicked,
            this, &MainWindow::onAddGameClicked);

    connect(ui->viewAchievementsButton, &QPushButton::clicked,
            this, &MainWindow::openAchievementsDialog);

    // Налаштування списку останніх досягнень
    ui->recentAchievementsList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->recentAchievementsList->setFocusPolicy(Qt::NoFocus);
    ui->recentAchievementsList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    // Тестові ігри
    games.push_back({"Elden Ring", "RPG", "Steam", 145, 50, 39});
    games.push_back({"Cyberpunk 2077", "RPG", "Steam", 120, 57, 32});
    games.push_back({"Hades", "Roguelike", "Steam", 64, 49, 21});
    games.push_back({"Hollow Knight", "Metroidvania", "Steam", 71, 63, 47});
    games.push_back({"Sekiro", "Action", "Steam", 58, 34, 28});

    // Оновлюємо список ігор
    updateGamesListUI();
}

// Деструктор
MainWindow::~MainWindow()
{
    delete ui;
}

// Відкриття діалогу додавання гри
void MainWindow::onAddGameClicked()
{
    AddGameDialog dialog(this);

    // Якщо користувач натиснув "Зберегти"
    if (dialog.exec() == QDialog::Accepted) {
        Game newGame;
        newGame.title = dialog.getTitle();
        newGame.genre = dialog.getGenre();
        newGame.platform = dialog.getPlatform();
        newGame.hours = dialog.getHours();
        newGame.totalAchievements = dialog.getTotalAchievements();
        newGame.openedAchievements = dialog.getOpenedAchievements();

        // Додаємо гру в масив
        games.append(newGame);

        // Оновлюємо список
        updateGamesListUI();

        // Виділяємо щойно додану гру
        ui->gamesList->setCurrentRow(games.size() - 1);
        onGameSelected();
    }
}

// Оновлення списку ігор у QListWidget
void MainWindow::updateGamesListUI()
{
    ui->gamesList->clear();

    for (int i = 0; i < games.size(); ++i) {
        const Game &g = games[i];

        QString itemText = QString("#%1    %2    %3    %4h    %5/%6")
                               .arg(i + 1)
                               .arg(g.title, -20)
                               .arg(g.genre, -14)
                               .arg(g.hours, 3)
                               .arg(g.openedAchievements, 2)
                               .arg(g.totalAchievements, 2);

        ui->gamesList->addItem(itemText);
    }

    // Оновлюємо лічильник ігор
    ui->gamesCountLabel->setText(QString::number(games.size()) + " ігор");

    // Якщо є ігри, вибираємо першу
    if (games.size() > 0 && ui->gamesList->currentRow() == -1) {
        ui->gamesList->setCurrentRow(0);
        onGameSelected();
    }
}

// Відкриття вікна досягнень
void MainWindow::openAchievementsDialog()
{
    AchievementsDialog dialog(this);

    // Передаємо назву поточної гри
    dialog.loadAchievementsForGame(ui->gameNameLabel->text());

    dialog.exec();
}

// Завантаження локальних досягнень у праву панель
void MainWindow::loadRecentAchievements(const QString &gameTitle)
{
    // Очищення списку
    ui->recentAchievementsList->clear();

    QString basePath = QCoreApplication::applicationDirPath();
    QString filePath;

    if (gameTitle == "Elden Ring") {
        filePath = basePath + "/assets/achievements/elden_ring.json";
    }
    else if (gameTitle == "Hades") {
        filePath = basePath + "/assets/achievements/hades.json";
    }
    else if (gameTitle == "Hollow Knight") {
        filePath = basePath + "/assets/achievements/hollow_knight.json";
    }
    else {
        ui->recentAchievementsList->addItem("Немає локальних досягнень");
        return;
    }

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        ui->recentAchievementsList->addItem("Помилка відкриття файлу");
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) {
        ui->recentAchievementsList->addItem("Помилка JSON");
        return;
    }

    QJsonArray arr = doc.array();
    int count = qMin(3, arr.size());

    for (int i = 0; i < count; i++) {
        QJsonObject obj = arr[i].toObject();

        QString title = obj["title"].toString();
        bool unlocked = obj["unlocked"].toBool();

        QString text = (unlocked ? "✔ " : "✖ ") + title;
        ui->recentAchievementsList->addItem(text);
    }
}

// Оновлення правої панелі при виборі гри
void MainWindow::onGameSelected()
{
    int index = ui->gamesList->currentRow();

    // Якщо нічого не вибрано
    if (index < 0 || index >= games.size())
        return;

    // Беремо гру з масиву
    const Game &game = games[index];

    // Оновлюємо праву панель
    ui->gameNameLabel->setText(game.title);
    ui->genreInfoLabel->setText("Жанр: " + game.genre);
    ui->hoursInfoLabel->setText("Ігрові години: " + QString::number(game.hours));
    ui->totalAchievementsInfoLabel->setText("Всього: " + QString::number(game.totalAchievements));
    ui->openedAchievementsInfoLabel->setText("Відкрито: " + QString::number(game.openedAchievements));
    ui->platformInfoLabel->setText("Платформа: " + game.platform);
    ui->coverLabel->setText(game.title.toUpper());

    // Рахуємо прогрес
    int progress = 0;
    if (game.totalAchievements > 0) {
        progress = (game.openedAchievements * 100) / game.totalAchievements;

        // Захист від неправильних значень
        if (progress > 100)
            progress = 100;
    }

    ui->progressBar->setValue(progress);
    ui->progressInfoLabel->setText(
        QString("(%1/%2)").arg(game.openedAchievements).arg(game.totalAchievements)
        );

    // Завантажуємо останні досягнення
    loadRecentAchievements(game.title);
}