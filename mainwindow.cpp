#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addgamedialog.h" // Обов'язково підключаємо діалог

#include <QButtonGroup>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("GameVault");

    // перемикач sidebar (активна тільки одна кнопка)
    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(ui->libraryButton);
    group->addButton(ui->achievementsButton);
    group->addButton(ui->steamImportButton);
    group->addButton(ui->settingsButton);
    group->setExclusive(true);
    ui->libraryButton->setChecked(true);

    // удаляем текст у progress bar
    ui->progressBar->setTextVisible(false);

    // очищення та заповнення фільтрів
    ui->genreComboBox->clear();
    ui->genreComboBox->addItems({"Жанр", "RPG", "Action", "Roguelike", "Metroidvania"});

    ui->statusComboBox->clear();
    ui->statusComboBox->addItems({"Статус", "Усі"});

    ui->platformComboBox->clear();
    ui->platformComboBox->addItems({"Платформа", "Steam", "Epic Games", "Other"});

    // очищення списку ігор
    ui->gamesList->clear();

    // ПІДКЛЮЧЕННЯ СИГНАЛІВ (КНОПОК ТА СПИСКІВ
    connect(ui->gamesList, &QListWidget::itemClicked, this, &MainWindow::onGameSelected);
    connect(ui->addGameButton, &QPushButton::clicked, this, &MainWindow::onAddGameClicked);
    connect(ui->bottomAddGameButton, &QPushButton::clicked, this, &MainWindow::onAddGameClicked);

    // ДОДАЄМО 5 ТЕСТОВИХ ІГОР ОДНОГРУПНИКА У МАСИВ ===
    games.push_back({"Elden Ring", "RPG", "Steam", 145, 50, 39});
    games.push_back({"Cyberpunk 2077", "RPG", "Steam", 120, 57, 32});
    games.push_back({"Hades", "Roguelike", "Steam", 64, 49, 21});
    games.push_back({"Hollow Knight", "Metroidvania", "Steam", 71, 63, 47});
    games.push_back({"Sekiro", "Action", "Steam", 58, 34, 28});

    // оновлюємо UI списку ігор
    updateGamesListUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Функція відкриття діалогу та збереження гри
void MainWindow::onAddGameClicked()
{
    AddGameDialog dialog(this);

    // якщо користувач натиснув "Зберегти" в діалозі
    if (dialog.exec() == QDialog::Accepted) {
        Game newGame;
        newGame.title = dialog.getTitle();
        newGame.genre = dialog.getGenre();
        newGame.platform = dialog.getPlatform();
        newGame.hours = dialog.getHours();
        newGame.totalAchievements = dialog.getTotalAchievements();
        newGame.openedAchievements = dialog.getOpenedAchievements();

        // додаємо гру в масив
        games.append(newGame);

        // оновлюємо візуальний список
        updateGamesListUI();

        // виділяємо щойно додану гру і показуємо її деталі
        ui->gamesList->setCurrentRow(games.size() - 1);
        onGameSelected();
    }
}

// функція оновлення QListWidget на основі масиву
void MainWindow::updateGamesListUI()
{
    ui->gamesList->clear();

    for (int i = 0; i < games.size(); ++i) {
        const Game& g = games[i];

        // Форматуємо рядок (відступи для краси)
        QString itemText = QString("#%1    %2    %3    %4h    %5/%6")
                               .arg(i + 1)
                               .arg(g.title, -20)
                               .arg(g.genre, -14)
                               .arg(g.hours, 3)
                               .arg(g.openedAchievements, 2)
                               .arg(g.totalAchievements, 2);

        ui->gamesList->addItem(itemText);
    }

    ui->gamesCountLabel->setText(QString::number(games.size()) + " ігор");

    // якщо ігри є, вибираємо першу за замовчуванням
    if (games.size() > 0 && ui->gamesList->currentRow() == -1) {
        ui->gamesList->setCurrentRow(0);
        onGameSelected();
    }
}

// Функція оновлення правої панелі при виборі гри
void MainWindow::onGameSelected()
{
    int index = ui->gamesList->currentRow();

    // якщо нічого не вибрано — виходимо
    if (index < 0 || index >= games.size()) return;

    // беремо гру з масиву за її індексом
    const Game& game = games[index];

    // оновлюємо праву панель
    ui->gameNameLabel->setText(game.title);
    ui->genreInfoLabel->setText("Жанр: " + game.genre);
    ui->hoursInfoLabel->setText("Ігрові години: " + QString::number(game.hours));
    ui->totalAchievementsInfoLabel->setText("Всього: " + QString::number(game.totalAchievements));
    ui->openedAchievementsInfoLabel->setText("Відкрито: " + QString::number(game.openedAchievements));
    ui->platformInfoLabel->setText("Платформа: " + game.platform);
    ui->coverLabel->setText(game.title.toUpper());

    // рахуємо прогрес у відсотках для progressBar
    int progress = 0;
    if (game.totalAchievements > 0) {
        progress = (game.openedAchievements * 100) / game.totalAchievements;
        if (progress > 100) progress = 100; // Захист від введення типу "50 з 10"
    }

    ui->progressBar->setValue(progress);
    ui->progressInfoLabel->setText(QString("(%1/%2)").arg(game.openedAchievements).arg(game.totalAchievements));

    // оновлення списку досягнень (заглушки для краси)
    ui->recentAchievementsList->clear();
    if (game.openedAchievements > 0) {
        ui->recentAchievementsList->addItem("Перша кров");
        ui->recentAchievementsList->addItem("Майстер меча");
    } else {
        ui->recentAchievementsList->addItem("Немає відкритих досягнень...");
    }
}