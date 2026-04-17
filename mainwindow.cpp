#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addgamedialog.h"
#include "achievementsdialog.h"
#include "buttonhoveranimator.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QIcon>
#include <QTimer>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QProgressBar>
#include <QFontMetrics>
#include <QButtonGroup>
#include <QListWidgetItem>
#include <QApplication>
#include <QPainter>
#include <QPainterPath>
#include <QInputDialog>
#include <QMessageBox>

namespace {
QPixmap makeRoundedThumb(const QPixmap &source, const QSize &targetSize) {
    if (source.isNull()) return QPixmap();
    QPixmap scaled = source.scaled(targetSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    const int x = qMax(0, (scaled.width() - targetSize.width()) / 2);
    const int y = qMax(0, (scaled.height() - targetSize.height()) / 2);
    QPixmap canvas = scaled.copy(x, y, targetSize.width(), targetSize.height());
    QPixmap rounded(targetSize);
    rounded.fill(Qt::transparent);
    QPainter painter(&rounded);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path;
    path.addRoundedRect(rounded.rect(), 6, 6);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, canvas);
    return rounded;
}

QString defaultThumbPathForGame(const QString &title) {
    const QString basePath = QCoreApplication::applicationDirPath();
    if (title == "Elden Ring") return basePath + "/assets/achievements/icons/elden_ring/elden_lord.png";
    if (title == "Hades") return basePath + "/assets/achievements/icons/hades/death_dealer.png";
    if (title == "Hollow Knight") return basePath + "/assets/achievements/icons/hollow_knight/hollow_knight.png";
    if (title == "Cyberpunk 2077") return basePath + "/assets/achievements/icons/elden_ring/radahn.png";
    if (title == "Sekiro") return basePath + "/assets/achievements/icons/elden_ring/morgott.png";
    return QString();
}
QString defaultCoverPathForGame(const QString &title) { return defaultThumbPathForGame(title); }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkReplyFinished);

    this->setStyleSheet("");
    if (centralWidget()) centralWidget()->setStyleSheet("");
    ui->settingsFrame->setStyleSheet("");
    ui->detailsFrame->setStyleSheet("");
    ui->sidebarFrame->setStyleSheet("");
    if (ui->libraryColumnsFrame) ui->libraryColumnsFrame->setStyleSheet("");

    QList<QWidget*> settingsWidgets = ui->settingsFrame->findChildren<QWidget*>();
    for (QWidget* w : settingsWidgets) {
        if (w->metaObject()->className() == QString("QFrame") || w->metaObject()->className() == QString("QWidget")) {
            w->setStyleSheet("background: transparent; border: none;");
        }
    }

    darkStyleSheet =
        "QMainWindow, #centralwidget, QDialog, QMessageBox { background-color: #0b0f14; color: #e6e6e6; font-family: \"Segoe UI\"; }"
        "QWidget { font-family: \"Segoe UI\"; }"
        "QLabel { background: transparent; border: none; color: #e6e6e6; }"
        "#sidebarFrame, #detailsFrame, #settingsFrame { background-color: #11161d; border-radius: 14px; }"
        "#libraryColumnsFrame { background-color: #141a22; border-radius: 10px; }"
        "#sidebarFrame QPushButton { background: transparent; border: none; text-align: left; padding: 10px 12px; border-radius: 10px; color: #c9d1d9; font-size: 10pt; font-weight: bold; }"
        "#sidebarFrame QPushButton:hover { background-color: #1b2129; }"
        "#sidebarFrame QPushButton:checked { background-color: #d32f2f; color: white; }"
        "QLineEdit, QComboBox, QSpinBox { background-color: #141a22; border: 1px solid #2c3440; border-radius: 10px; padding: 6px; color: #e6e6e6; }"
        "QComboBox QAbstractItemView { background-color: #141a22; color: #e6e6e6; selection-background-color: #d32f2f; selection-color: white; border: 1px solid #2c3440; outline: none; }"
        "QPushButton { background-color: #1c222b; border: none; border-radius: 10px; padding: 6px 12px; color: white; font-weight: bold; }"
        "QPushButton:hover { background-color: #2a313d; }"
        "#addGameButton, #bottomAddGameButton, #libraryAddButton { color: white; }"
        "#viewAchievementsButton { background-color: #1c222b; color: white; }"
        "QListWidget { border: none; background: transparent; outline: none; }"
        "QListWidget::item { background-color: #141a22; border: 1px solid transparent; border-radius: 12px; color: #e6e6e6; margin: 6px 0px; }"
        "QListWidget::item:selected { border: 2px solid #ff3d3d; }"
        "QProgressBar { background-color: #2a313d; border: none; border-radius: 6px; color: white; } QProgressBar::chunk { background-color: #ff3d3d; border-radius: 6px; }"
        "QScrollBar:vertical { background: transparent; width: 8px; margin: 0px; border-radius: 4px; border: none; }"
        "QScrollBar::handle:vertical { background: #612222; min-height: 28px; border-radius: 4px; border: none; margin: 0px; }"
        "QScrollBar::handle:vertical:hover { background: #7a2b2b; }"
        "QScrollBar::handle:vertical:pressed { background: #8f3333; }"
        "QWidget#achCard { background-color: #141a22; border-radius: 10px; border: 1px solid transparent; }"
        "QLabel#achTitle { color: white; font-size: 11pt; font-weight: bold; }"
        "QLabel#achDesc { color: #9aa4b2; font-size: 9pt; }";

    lightStyleSheet =
        "QMainWindow, #centralwidget, QDialog, QMessageBox { background-color: #f3f4f6; color: #1f2937; font-family: \"Segoe UI\"; }"
        "QWidget { font-family: \"Segoe UI\"; }"
        "QLabel { background: transparent; border: none; color: #1f2937; }"
        "#sidebarFrame, #detailsFrame, #settingsFrame { background-color: #ffffff; border-radius: 14px; border: 1px solid #e5e7eb; }"
        "#libraryColumnsFrame { background-color: #e5e7eb; border-radius: 10px; }"
        "#sidebarFrame QPushButton { background: transparent; border: none; text-align: left; padding: 10px 12px; border-radius: 10px; color: #4b5563; font-size: 10pt; font-weight: bold; }"
        "#sidebarFrame QPushButton:hover { background-color: #f3f4f6; }"
        "#sidebarFrame QPushButton:checked { background-color: #d32f2f; color: white; }"
        "QLineEdit, QComboBox, QSpinBox { background-color: #ffffff; border: 1px solid #d1d5db; border-radius: 10px; padding: 6px; color: #1f2937; }"
        "QComboBox QAbstractItemView { background-color: #ffffff; color: #1f2937; selection-background-color: #d32f2f; selection-color: white; border: 1px solid #d1d5db; outline: none; }"
        "QPushButton { background-color: #e5e7eb; border: 1px solid #d1d5db; border-radius: 10px; padding: 6px 12px; color: #1f2937; font-weight: bold; }"
        "QPushButton:hover { background-color: #d1d5db; }"
        "#addGameButton, #bottomAddGameButton, #libraryAddButton { color: white; }"
        "#viewAchievementsButton { background-color: #374151; color: white; }"
        "QListWidget { border: none; background: transparent; outline: none; }"
        "QListWidget::item { background-color: #ffffff; border: 1px solid #e5e7eb; border-radius: 12px; color: #1f2937; margin: 6px 0px; }"
        "QListWidget::item:selected { border: 2px solid #d32f2f; }"
        "QProgressBar { background-color: #e5e7eb; border: none; border-radius: 6px; color: white; } QProgressBar::chunk { background-color: #d32f2f; border-radius: 6px; }"
        "QScrollBar:vertical { background: transparent; width: 8px; margin: 0px; border-radius: 4px; border: none; }"
        "QScrollBar::handle:vertical { background: #9ca3af; min-height: 28px; border-radius: 4px; border: none; margin: 0px; }"
        "QScrollBar::handle:vertical:hover { background: #6b7280; }"
        "QScrollBar::handle:vertical:pressed { background: #4b5563; }"
        "QWidget#achCard { background-color: #ffffff; border-radius: 10px; border: 1px solid #e5e7eb; }"
        "QLabel#achTitle { color: #1f2937; font-size: 11pt; font-weight: bold; }"
        "QLabel#achDesc { color: #6b7280; font-size: 9pt; }";

    setWindowTitle("GameVault");

    QButtonGroup *group = new QButtonGroup(this);
    ui->libraryButton->setCheckable(true);
    ui->achievementsButton->setCheckable(true);
    ui->steamImportButton->setCheckable(true);
    ui->settingsButton->setCheckable(true);
    group->addButton(ui->libraryButton);
    group->addButton(ui->achievementsButton);
    group->addButton(ui->steamImportButton);
    group->addButton(ui->settingsButton);
    group->setExclusive(true);
    ui->libraryButton->setChecked(true);

    ui->progressBar->setTextVisible(false);

    ui->genreComboBox->clear();
    ui->genreComboBox->addItems({"Жанр", "RPG", "Action", "Roguelike", "Metroidvania", "Steam Import"});
    ui->statusComboBox->clear();
    ui->statusComboBox->addItems({"Статус", "Усі"});
    ui->platformComboBox->clear();
    ui->platformComboBox->addItems({"Платформа", "Steam", "Epic Games", "Other"});
    ui->searchLineEdit->clear();

    ui->gamesList->clear();
    ui->gamesList->setWordWrap(true);
    ui->gamesList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gamesList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->gamesList->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->gamesList, &QListWidget::itemClicked, this, &MainWindow::onGameSelected);
    connect(ui->gamesList, &QListWidget::itemDoubleClicked, this, &MainWindow::onGameDoubleClicked);
    connect(ui->gamesList, &QListWidget::currentRowChanged, this, [this](int) { updateGameRowsSelection(); });

    connect(ui->addGameButton, &QPushButton::clicked, this, &MainWindow::onAddGameClicked);
    connect(ui->bottomAddGameButton, &QPushButton::clicked, this, &MainWindow::onAddGameClicked);
    connect(ui->viewAchievementsButton, &QPushButton::clicked, this, &MainWindow::openAchievementsDialog);
    connect(ui->libraryButton, &QPushButton::clicked, this, &MainWindow::showLibraryPage);
    connect(ui->achievementsButton, &QPushButton::clicked, this, &MainWindow::showAchievementsPage);
    connect(ui->steamImportButton, &QPushButton::clicked, this, &MainWindow::showSteamImportPage);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::showSettingsPage);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::filterGames);
    connect(ui->genreComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::filterGames);
    connect(ui->platformComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::filterGames);

    auto *themeGroup = new QButtonGroup(this);
    themeGroup->setExclusive(true);
    themeGroup->addButton(ui->themeDarkButton);
    themeGroup->addButton(ui->themeLightButton);

    auto *langGroup = new QButtonGroup(this);
    langGroup->setExclusive(true);
    langGroup->addButton(ui->langUkButton);
    langGroup->addButton(ui->langEnButton);

    connect(ui->themeDarkButton, &QPushButton::clicked, this, &MainWindow::applyDarkTheme);
    connect(ui->themeLightButton, &QPushButton::clicked, this, &MainWindow::applyLightTheme);
    connect(ui->langUkButton, &QPushButton::clicked, this, &MainWindow::applyUkrainianLanguage);
    connect(ui->langEnButton, &QPushButton::clicked, this, &MainWindow::applyEnglishLanguage);

    ui->libraryButton->setCursor(Qt::PointingHandCursor);
    ui->achievementsButton->setCursor(Qt::PointingHandCursor);
    ui->steamImportButton->setCursor(Qt::PointingHandCursor);
    ui->settingsButton->setCursor(Qt::PointingHandCursor);
    ui->addGameButton->setCursor(Qt::PointingHandCursor);
    ui->bottomAddGameButton->setCursor(Qt::PointingHandCursor);
    ui->viewAchievementsButton->setCursor(Qt::PointingHandCursor);
    ui->libraryAddButton->setCursor(Qt::PointingHandCursor);
    ui->addGameButton->setVisible(false);

    installHoverAnimation(ui->addGameButton, ButtonHoverPalette{QColor("#d32f2f"), QColor("#ff3d3d"), QColor("#b92a2a"), QColor(), QColor(), false}, this);
    installHoverAnimation(ui->bottomAddGameButton, ButtonHoverPalette{QColor("#942B2B"), QColor("#b33636"), QColor("#7a2323"), QColor(), QColor(), false}, this);
    installHoverAnimation(ui->viewAchievementsButton, ButtonHoverPalette{QColor("#1c222b"), QColor("#323b49"), QColor("#262d38"), QColor(), QColor(), false}, this);
    installHoverAnimation(ui->libraryAddButton, ButtonHoverPalette{QColor("#d32f2f"), QColor("#ff3d3d"), QColor("#b92a2a"), QColor(), QColor(), false}, this);
    connect(ui->libraryAddButton, &QPushButton::clicked, this, &MainWindow::onAddGameClicked);

    ui->recentAchievementsList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->recentAchievementsList->setFocusPolicy(Qt::NoFocus);
    ui->recentAchievementsList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->recentAchievementsList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    qApp->setStyleSheet(darkStyleSheet);

    // ФІКС: Примусово вмикаємо українську мову під час запуску,
    // щоб перебити російський текст (напр. "Поиск игры...") з Qt Designer
    ui->langUkButton->setChecked(true);
    applyUkrainianLanguage();

    loadGamesFromJson();
    filterGames();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onAddGameClicked()
{
    AddGameDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Game newGame;
        newGame.title = dialog.getTitle();
        newGame.genre = dialog.getGenre();
        newGame.platform = dialog.getPlatform();
        newGame.hours = dialog.getHours();
        newGame.totalAchievements = dialog.getTotalAchievements();
        newGame.openedAchievements = dialog.getOpenedAchievements();
        newGame.steamAppId = "";
        newGame.ownerSteamId = "";

        QString originalPoster = dialog.getPosterPath();
        QString savedPosterPath = originalPoster;
        if (!originalPoster.isEmpty() && !originalPoster.startsWith("assets/")) {
            QDir dir; if (!dir.exists("assets")) dir.mkpath("assets");
            QFileInfo fileInfo(originalPoster);
            savedPosterPath = "assets/" + fileInfo.fileName();
            if (!QFile::exists(savedPosterPath)) QFile::copy(originalPoster, savedPosterPath);
        }
        newGame.posterPath = savedPosterPath;

        games.append(newGame);
        saveGamesToJson();
        filterGames();
        ui->gamesList->setCurrentRow(ui->gamesList->count() - 1);
        onGameSelected();
    }
}

void MainWindow::onGameDoubleClicked(QListWidgetItem *item)
{
    if (!item) return;
    int realIndex = item->data(Qt::UserRole).toInt();
    if (realIndex < 0 || realIndex >= games.size()) return;

    Game &game = games[realIndex];
    AddGameDialog dialog(this);
    dialog.setWindowTitle(ui->langUkButton->isChecked() ? "Редагувати гру" : "Edit Game");

    int displayTotal = qMax(0, game.totalAchievements);
    int displayOpened = qMax(0, game.openedAchievements);
    dialog.setGameData(game.title, game.genre, game.platform, game.hours,
                       displayTotal, displayOpened, game.posterPath);

    if (dialog.exec() == QDialog::Accepted) {
        game.title = dialog.getTitle();
        game.genre = dialog.getGenre();
        game.platform = dialog.getPlatform();
        game.hours = dialog.getHours();
        game.totalAchievements = dialog.getTotalAchievements();
        game.openedAchievements = dialog.getOpenedAchievements();

        QString originalPoster = dialog.getPosterPath();
        if (!originalPoster.isEmpty() && !originalPoster.startsWith("assets/")) {
            QDir dir; if (!dir.exists("assets")) dir.mkpath("assets");
            QFileInfo fileInfo(originalPoster);
            QString savedPosterPath = "assets/" + fileInfo.fileName();
            if (!QFile::exists(savedPosterPath)) QFile::copy(originalPoster, savedPosterPath);
            game.posterPath = savedPosterPath;
        }

        saveGamesToJson();
        filterGames();
        onGameSelected();
    }
}

void MainWindow::filterGames() { updateGamesListUI(); }

void MainWindow::updateGamesListUI()
{
    ui->gamesList->clear();

    QString searchText = ui->searchLineEdit->text().toLower();
    bool useGenreFilter = ui->genreComboBox->currentIndex() > 0;
    QString filterGenre = ui->genreComboBox->currentText();
    bool usePlatformFilter = ui->platformComboBox->currentIndex() > 0;
    QString filterPlatform = ui->platformComboBox->currentText();

    int displayCount = 0;

    for (int i = 0; i < games.size(); ++i) {
        const Game &g = games[i];

        if (!searchText.isEmpty() && !g.title.toLower().contains(searchText)) continue;
        if (useGenreFilter && g.genre != filterGenre) continue;
        if (usePlatformFilter && g.platform != filterPlatform) continue;

        displayCount++;
        int safeTotal = qMax(0, g.totalAchievements);
        int safeOpened = qMax(0, g.openedAchievements);
        const int progress = (safeTotal > 0) ? qBound(0, (safeOpened * 100) / safeTotal, 100) : 0;

        auto *item = new QListWidgetItem();
        item->setSizeHint(QSize(0, 64));
        item->setData(Qt::UserRole, i);
        ui->gamesList->addItem(item);

        auto *rowFrame = new QFrame;
        rowFrame->setObjectName("gameRowFrame");

        auto *rowLayout = new QHBoxLayout(rowFrame);
        rowLayout->setContentsMargins(12, 8, 12, 8);
        rowLayout->setSpacing(10);

        auto *indexLabel = new QLabel(QString("#%1").arg(displayCount));
        indexLabel->setFixedWidth(28);
        indexLabel->setStyleSheet("font-weight: 700; font-size: 10pt;");

        auto *thumbLabel = new QLabel;
        thumbLabel->setFixedSize(64, 36);
        thumbLabel->setAlignment(Qt::AlignCenter);
        thumbLabel->setStyleSheet("background-color: #0f1319; border-radius: 6px; color: #d7c58a; font-size: 7pt; font-weight: 700;");

        QPixmap thumbPixmap;
        if (!g.posterPath.isEmpty() && g.posterPath != "downloading" && QFile::exists(g.posterPath)) {
            thumbPixmap.load(g.posterPath);
        } else {
            thumbPixmap.load(defaultThumbPathForGame(g.title));
        }

        if (!thumbPixmap.isNull()) {
            thumbLabel->setText("");
            thumbLabel->setPixmap(makeRoundedThumb(thumbPixmap, thumbLabel->size()));
        } else {
            QString shortTitle = g.title.left(10).toUpper();
            thumbLabel->setText(shortTitle);
        }

        auto *titleLabel = new QLabel(g.title);
        titleLabel->setMinimumWidth(140);
        titleLabel->setStyleSheet("font-size: 10.5pt; font-weight: 700;");

        auto *genreLabel = new QLabel(g.genre);
        genreLabel->setMinimumWidth(92);
        genreLabel->setStyleSheet("font-size: 10pt; font-weight: 600; color: #7f8b9a;");

        auto *hoursLabel = new QLabel(QString("%1h").arg(g.hours));
        hoursLabel->setMinimumWidth(62);
        hoursLabel->setStyleSheet("font-size: 11pt; font-weight: 700;");

        auto *progressText = new QLabel(QString("%1%").arg(progress));
        progressText->setMinimumWidth(40);
        progressText->setStyleSheet("font-size: 10pt; font-weight: 700;");

        auto *rowProgress = new QProgressBar;
        rowProgress->setRange(0, 100);
        rowProgress->setValue(progress);
        rowProgress->setTextVisible(false);
        rowProgress->setFixedSize(118, 8);

        auto *fractionLabel = new QLabel(QString("%1/%2").arg(safeOpened).arg(safeTotal));
        fractionLabel->setMinimumWidth(48);
        fractionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        fractionLabel->setStyleSheet("font-size: 10pt; font-weight: 700;");

        rowLayout->addWidget(indexLabel);
        rowLayout->addWidget(thumbLabel);
        rowLayout->addWidget(titleLabel, 1);
        rowLayout->addWidget(genreLabel);
        rowLayout->addWidget(hoursLabel);
        rowLayout->addWidget(progressText);
        rowLayout->addWidget(rowProgress);
        rowLayout->addWidget(fractionLabel);

        ui->gamesList->setItemWidget(item, rowFrame);
    }

    QString gamesText = ui->langUkButton->isChecked() ? "ігор" : "games";
    ui->gamesCountLabel->setText(QString::number(displayCount) + " " + gamesText);

    if (displayCount > 0) {
        if (!isAchievementsPage) {
            ui->detailsFrame->setVisible(true);
        }
        if (ui->gamesList->currentRow() == -1 && !isAchievementsPage) {
            ui->gamesList->setCurrentRow(0);
            onGameSelected();
        }
    } else {
        ui->detailsFrame->setVisible(false);
    }
    updateGameRowsSelection();
}

void MainWindow::openAchievementsDialog() {
    int row = ui->gamesList->currentRow();
    if(row < 0) return;
    int realIndex = ui->gamesList->item(row)->data(Qt::UserRole).toInt();
    Game &g = games[realIndex];

    if (g.platform == "Steam" && g.steamAppId.isEmpty()) {
        QMessageBox::warning(this, ui->langUkButton->isChecked() ? "Увага" : "Warning",
                             ui->langUkButton->isChecked() ? "Пересинхронізуйте акаунт у вкладці Steam Import (відв'яжіть і прив'яжіть знову), щоб програма отримала ID цієї гри для ачивок!" : "Re-sync your Steam account in the Import tab to get the AppID for achievements.");
    }

    AchievementsDialog dialog(this);
    dialog.loadAchievementsForGame(g.title, g.steamAppId, g.ownerSteamId);
    dialog.exec();
}

void MainWindow::loadRecentAchievements(const QString &gameTitle) {
    ui->recentAchievementsList->clear();
    QString basePath = QCoreApplication::applicationDirPath();
    QString filePath;

    if (gameTitle == "Elden Ring") filePath = basePath + "/assets/achievements/elden_ring.json";
    else if (gameTitle == "Hades") filePath = basePath + "/assets/achievements/hades.json";
    else if (gameTitle == "Hollow Knight") filePath = basePath + "/assets/achievements/hollow_knight.json";
    else {
        ui->recentAchievementsList->addItem(ui->langUkButton->isChecked() ? "Немає локальних досягнень" : "No local achievements");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) { return; }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) return;
    QJsonArray arr = doc.array();
    int count = qMin(3, arr.size());

    for (int i = 0; i < count; i++) {
        QJsonObject obj = arr[i].toObject();
        QString title = obj["title"].toString("Без назви");
        const QString iconPath = resolveAchievementIconPath(obj["icon"].toString());
        bool unlocked = obj["unlocked"].toBool();

        QWidget *cardWidget = new QWidget;
        cardWidget->setStyleSheet("background: transparent;");
        QHBoxLayout *cardLayout = new QHBoxLayout(cardWidget);
        cardLayout->setContentsMargins(2, 4, 6, 4);
        cardLayout->setSpacing(8);

        QLabel *iconLabel = new QLabel;
        iconLabel->setFixedSize(44, 44);
        iconLabel->setAlignment(Qt::AlignCenter);
        iconLabel->setStyleSheet("background-color: #0f1319; border-radius: 7px;");
        QPixmap iconPix(iconPath);
        if (!iconPix.isNull()) iconLabel->setPixmap(makeRoundedThumb(iconPix, iconLabel->size()));
        else iconLabel->setText(unlocked ? "✔" : "✖");

        QVBoxLayout *textLayout = new QVBoxLayout;
        textLayout->setSpacing(0);
        textLayout->setContentsMargins(0, 0, 0, 0);

        QLabel *titleLabel = new QLabel(title);
        titleLabel->setStyleSheet("font-size: 12pt; font-weight: 700;");
        QLabel *dateLabel = new QLabel("27.03.2026");
        dateLabel->setStyleSheet("color: #7f8b9a; font-size: 10pt; font-weight: 600;");

        textLayout->addWidget(titleLabel);
        textLayout->addWidget(dateLabel);

        cardLayout->addWidget(iconLabel);
        cardLayout->addLayout(textLayout, 1);

        auto *item = new QListWidgetItem;
        item->setSizeHint(QSize(0, 58));
        ui->recentAchievementsList->addItem(item);
        ui->recentAchievementsList->setItemWidget(item, cardWidget);
    }
}

void MainWindow::onGameSelected() {
    QListWidgetItem *item = ui->gamesList->currentItem();
    if (!item) return;

    int realIndex = item->data(Qt::UserRole).toInt();
    if (realIndex < 0 || realIndex >= games.size()) return;

    Game &game = games[realIndex];

    if (isAchievementsPage) {
        if (game.platform == "Steam" && game.steamAppId.isEmpty()) {
            QMessageBox::warning(this, ui->langUkButton->isChecked() ? "Увага" : "Warning",
                                 ui->langUkButton->isChecked() ? "Пересинхронізуйте акаунт у вкладці Steam Import (відв'яжіть і прив'яжіть знову), щоб програма отримала ID цієї гри для ачивок!" : "Re-sync your Steam account in the Import tab to get the AppID for achievements.");
        }
        AchievementsDialog dialog(this);
        dialog.loadAchievementsForGame(game.title, game.steamAppId, game.ownerSteamId);
        dialog.exec();
        ui->gamesList->clearSelection();
        return;
    }

    if (game.platform == "Steam" && !game.steamAppId.isEmpty()) {
        if (game.posterPath.isEmpty()) {
            game.posterPath = "downloading";
            QString url = QString("https://steamcdn-a.akamaihd.net/steam/apps/%1/library_600x900.jpg").arg(game.steamAppId);
            QNetworkRequest req((QUrl(url)));
            req.setAttribute(QNetworkRequest::User, "FetchPoster");
            QNetworkReply *reply = networkManager->get(req);
            reply->setProperty("gameIndex", realIndex);
        }

        if (game.totalAchievements == 0 && !game.ownerSteamId.isEmpty()) {
            game.totalAchievements = -1;
            QString apiKey = "7867BE5270C9793801AF225244020B03";
            QString url = QString("https://api.steampowered.com/ISteamUserStats/GetPlayerAchievements/v0001/?appid=%1&key=%2&steamid=%3")
                              .arg(game.steamAppId, apiKey, game.ownerSteamId);
            QNetworkRequest req((QUrl(url)));
            req.setAttribute(QNetworkRequest::User, "FetchAchievements");
            QNetworkReply *reply = networkManager->get(req);
            reply->setProperty("gameIndex", realIndex);
        }
    }

    ui->gameNameLabel->setText(game.title);

    QString genreStr = ui->langUkButton->isChecked() ? "Жанр: " : "Genre: ";
    QString hoursStr = ui->langUkButton->isChecked() ? "Ігрові години: " : "Playtime: ";
    QString totalAchStr = ui->langUkButton->isChecked() ? "Усього досягнень: " : "Total achievements: ";
    QString openedStr = ui->langUkButton->isChecked() ? "Відкрито: " : "Unlocked: ";
    QString platformStr = ui->langUkButton->isChecked() ? "Платформа: " : "Platform: ";

    ui->genreInfoLabel->setText(genreStr + game.genre);
    ui->hoursInfoLabel->setText(hoursStr + QString::number(game.hours) + " h");

    int safeTotal = qMax(0, game.totalAchievements);
    int safeOpened = qMax(0, game.openedAchievements);

    ui->totalAchievementsInfoLabel->setText(totalAchStr + QString::number(safeTotal));

    const int percent = (safeTotal > 0) ? (safeOpened * 100) / safeTotal : 0;
    ui->openedAchievementsInfoLabel->setText(QString("%1 %2 (%3%)").arg(openedStr).arg(safeOpened).arg(percent));
    ui->platformInfoLabel->setText(platformStr + game.platform);

    QString coverPath = game.posterPath;
    if (coverPath == "downloading") {
        ui->coverLabel->setPixmap(QPixmap());
        ui->coverLabel->setText(ui->langUkButton->isChecked() ? "Завантаження..." : "Loading...");
    } else {
        if (coverPath.isEmpty() || !QFile::exists(coverPath)) coverPath = defaultCoverPathForGame(game.title);
        QPixmap cover(coverPath);

        if (!cover.isNull()) {
            const QSize targetSize = ui->coverLabel->size();
            const QSize sourceSize = cover.size();
            const double sourceRatio = static_cast<double>(sourceSize.width()) / sourceSize.height();
            const double targetRatio = static_cast<double>(targetSize.width()) / targetSize.height();
            QRect cropRect(0, 0, sourceSize.width(), sourceSize.height());

            if (sourceRatio > targetRatio) {
                const int cropWidth = static_cast<int>(sourceSize.height() * targetRatio);
                cropRect = QRect((sourceSize.width() - cropWidth) / 2, 0, cropWidth, sourceSize.height());
            } else if (sourceRatio < targetRatio) {
                const int cropHeight = static_cast<int>(sourceSize.width() / targetRatio);
                int y = static_cast<int>(sourceSize.height() * 0.10);
                if (y + cropHeight > sourceSize.height()) y = sourceSize.height() - cropHeight;
                cropRect = QRect(0, qMax(0, y), sourceSize.width(), cropHeight);
            }

            const QPixmap cropped = cover.copy(cropRect).scaled(targetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            QPixmap rounded(targetSize);
            rounded.fill(Qt::transparent);
            QPainter roundedPainter(&rounded);
            roundedPainter.setRenderHint(QPainter::Antialiasing, true);
            QPainterPath path;
            path.addRoundedRect(rounded.rect(), 12, 12);
            roundedPainter.setClipPath(path);
            roundedPainter.drawPixmap(0, 0, cropped);

            ui->coverLabel->setPixmap(rounded);
            ui->coverLabel->setText("");
        } else {
            ui->coverLabel->setPixmap(QPixmap());
            ui->coverLabel->setText(game.title.toUpper());
        }
    }

    ui->progressBar->setValue(qMin(100, percent));
    ui->progressInfoLabel->setText(QString("(%1/%2)").arg(safeOpened).arg(safeTotal));

    loadRecentAchievements(game.title);
}

QString MainWindow::resolveAchievementIconPath(const QString &rawIconPath) const {
    if (rawIconPath.isEmpty()) return QString();
    const QString basePath = QCoreApplication::applicationDirPath();
    if (QFile::exists(basePath + "/" + rawIconPath)) return basePath + "/" + rawIconPath;

    QFileInfo info(rawIconPath);
    QDir iconsDir(basePath + "/assets/achievements/icons/" + info.path().section('/', -1));
    if (!iconsDir.exists()) return QString();

    const QStringList candidates = iconsDir.entryList(QStringList() << "*.png" << "*.jpg" << "*.jpeg" << "*.webp", QDir::Files);
    for (const QString &candidate : candidates) {
        if (candidate.compare(info.fileName(), Qt::CaseInsensitive) == 0) return iconsDir.filePath(candidate);
        if (candidate.toLower().contains(info.completeBaseName().toLower())) return iconsDir.filePath(candidate);
    }
    return QString();
}

void MainWindow::showLibraryPage() {
    setActiveSidebarButton(ui->libraryButton);
    isAchievementsPage = false;
    ui->genreComboBox->setVisible(true);
    ui->statusComboBox->setVisible(true);
    ui->platformComboBox->setVisible(true);
    ui->searchLineEdit->setVisible(true);
    if (ui->libraryColumnsFrame) ui->libraryColumnsFrame->setVisible(true);
    ui->settingsFrame->setVisible(false);
    ui->gamesList->setVisible(true);
    ui->sectionTitleLabel->setText(ui->langUkButton->isChecked() ? "Моя ігрова бібліотека" : "My Game Library");
    updateGamesListUI();
}

void MainWindow::showAchievementsPage() {
    setActiveSidebarButton(ui->achievementsButton);
    isAchievementsPage = true;
    ui->genreComboBox->setVisible(false);
    ui->statusComboBox->setVisible(false);
    ui->platformComboBox->setVisible(false);
    ui->searchLineEdit->setVisible(false);

    if (ui->libraryColumnsFrame) ui->libraryColumnsFrame->setVisible(true);
    ui->detailsFrame->setVisible(false);
    ui->settingsFrame->setVisible(false);

    ui->sectionTitleLabel->setText(ui->langUkButton->isChecked() ? "Досягнення (Оберіть гру)" : "Achievements (Select Game)");

    updateGamesListUI();
}

void MainWindow::showSteamImportPage() {
    bool hasSteamGames = false;
    for (const Game& g : games) {
        if (g.platform == "Steam" && g.genre == "Steam Import") { hasSteamGames = true; break; }
    }

    if (hasSteamGames) {
        QString titleStr = ui->langUkButton->isChecked() ? "Steam Import" : "Steam Import";
        QString textStr = ui->langUkButton->isChecked() ? "Відв'язати акаунт та видалити ігри?" : "Unlink account and delete games?";
        if (QMessageBox::question(this, titleStr, textStr, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            for (int i = games.size() - 1; i >= 0; --i) {
                if (games[i].platform == "Steam" && games[i].genre == "Steam Import") games.removeAt(i);
            }
            saveGamesToJson();
            updateGamesListUI();
        }
        showLibraryPage();
        return;
    }

    setActiveSidebarButton(ui->steamImportButton);
    isAchievementsPage = true;
    ui->genreComboBox->setVisible(false);
    ui->statusComboBox->setVisible(false);
    ui->platformComboBox->setVisible(false);
    ui->searchLineEdit->setVisible(false);
    if (ui->libraryColumnsFrame) ui->libraryColumnsFrame->setVisible(false);
    ui->detailsFrame->setVisible(false);
    ui->settingsFrame->setVisible(false);
    ui->gamesList->clear();

    bool ok;
    QString titleStr = ui->langUkButton->isChecked() ? "Steam Import" : "Steam Import";
    QString textStr = ui->langUkButton->isChecked() ? "Введіть Steam ID (17 цифр):" : "Enter Steam ID (17 digits):";
    currentSteamId = QInputDialog::getText(this, titleStr, textStr, QLineEdit::Normal, "", &ok);

    if (ok && !currentSteamId.isEmpty()) {
        ui->gamesList->addItem(ui->langUkButton->isChecked() ? "Завантаження профілю Steam..." : "Loading Steam profile...");
        ui->gamesCountLabel->setText("Крок 1/2...");

        QString apiKey = "7867BE5270C9793801AF225244020B03";
        QString urlStr = QString("https://api.steampowered.com/ISteamUser/GetPlayerSummaries/v0002/?key=%1&steamids=%2").arg(apiKey, currentSteamId);

        QNetworkRequest req((QUrl(urlStr)));
        req.setAttribute(QNetworkRequest::User, "Profile");
        networkManager->get(req);
    } else {
        showLibraryPage();
    }
}

void MainWindow::onNetworkReplyFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        if (reply->request().attribute(QNetworkRequest::User).toString() == "FetchPoster") {
            int index = reply->property("gameIndex").toInt();
            if (index >= 0 && index < games.size()) games[index].posterPath = "";
        }
        reply->deleteLater();
        return;
    }

    QString reqType = reply->request().attribute(QNetworkRequest::User).toString();
    QByteArray response = reply->readAll();
    QString apiKey = "7867BE5270C9793801AF225244020B03";

    if (reqType == "Profile") {
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject responseObj = doc.object()["response"].toObject();
        QJsonArray players = responseObj["players"].toArray();
        if (players.isEmpty()) {
            QMessageBox::warning(this, ui->langUkButton->isChecked() ? "Помилка" : "Error",
                                 ui->langUkButton->isChecked() ? "Профіль не знайдено!" : "Profile not found!");
            showLibraryPage();
        } else {
            currentSteamName = players[0].toObject()["personaname"].toString();
            ui->gamesList->clear();
            QString loadText = ui->langUkButton->isChecked() ? "Знайдено профіль: %1. Завантаження ігор..." : "Profile found: %1. Loading games...";
            ui->gamesList->addItem(loadText.arg(currentSteamName));
            ui->gamesCountLabel->setText("Крок 2/2...");

            QString urlStr = QString("https://api.steampowered.com/IPlayerService/GetOwnedGames/v0001/?key=%1&steamid=%2&format=json&include_appinfo=1").arg(apiKey, currentSteamId);
            QNetworkRequest req((QUrl(urlStr)));
            req.setAttribute(QNetworkRequest::User, "Games");
            networkManager->get(req);
        }
    }
    else if (reqType == "Games") {
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject responseObj = doc.object()["response"].toObject();
        if (responseObj.contains("games")) {
            QJsonArray gamesArray = responseObj["games"].toArray();
            int addedCount = 0;

            for (int i = 0; i < gamesArray.size(); ++i) {
                QJsonObject gameObj = gamesArray[i].toObject();
                QString title = gameObj["name"].toString();

                bool exists = false;
                for (const Game& g : games) {
                    if (g.title == title) { exists = true; break; }
                }

                if (!exists) {
                    Game newGame;
                    newGame.title = title;
                    newGame.platform = "Steam";
                    newGame.genre = "Steam Import";
                    newGame.hours = gameObj["playtime_forever"].toInt() / 60;
                    newGame.totalAchievements = 0;
                    newGame.openedAchievements = 0;
                    newGame.posterPath = "";

                    newGame.steamAppId = QString::number(gameObj["appid"].toInt());
                    newGame.ownerSteamId = currentSteamId;

                    games.append(newGame);
                    addedCount++;
                }
            }
            saveGamesToJson();
            updateGamesListUI();

            QString msgBoxText = ui->langUkButton->isChecked() ? "Акаунт: %1\nSteam ID: %2\nІмпортовано ігор: %3" : "Account: %1\nSteam ID: %2\nGames imported: %3";
            QString msgBoxTitle = ui->langUkButton->isChecked() ? "Успіх" : "Success";
            QMessageBox::information(this, msgBoxTitle, msgBoxText.arg(currentSteamName, currentSteamId).arg(addedCount));
        } else {
            QString errTitle = ui->langUkButton->isChecked() ? "Помилка" : "Error";
            QString errText = ui->langUkButton->isChecked() ? "Ігор не знайдено або профіль прихований." : "No games found or profile is private.";
            QMessageBox::warning(this, errTitle, errText);
        }
        showLibraryPage();
    }
    else if (reqType == "FetchPoster") {
        int index = reply->property("gameIndex").toInt();
        if (index >= 0 && index < games.size()) {
            QDir dir; if (!dir.exists("assets")) dir.mkpath("assets");
            QString path = QString("assets/steam_%1.jpg").arg(games[index].steamAppId);
            QFile file(path);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(response);
                file.close();
                games[index].posterPath = path;
                saveGamesToJson();
                if (ui->gamesList->currentRow() == index) onGameSelected();
            }
        }
    }
    else if (reqType == "FetchAchievements") {
        int index = reply->property("gameIndex").toInt();
        if (index >= 0 && index < games.size()) {
            QJsonDocument doc = QJsonDocument::fromJson(response);
            QJsonObject playerstats = doc.object()["playerstats"].toObject();

            if (playerstats["success"].toBool()) {
                QJsonArray achArray = playerstats["achievements"].toArray();
                games[index].totalAchievements = achArray.size();
                int unlocked = 0;
                for (int i = 0; i < achArray.size(); ++i) {
                    if (achArray[i].toObject()["achieved"].toInt() == 1) unlocked++;
                }
                games[index].openedAchievements = unlocked;
                saveGamesToJson();
                updateGamesListUI();

                if (ui->gamesList->currentRow() == index) onGameSelected();
            } else {
                games[index].totalAchievements = -2;
                saveGamesToJson();
            }
        }
    }
    reply->deleteLater();
}

void MainWindow::showSettingsPage() {
    setActiveSidebarButton(ui->settingsButton);
    isAchievementsPage = true;
    ui->genreComboBox->setVisible(false);
    ui->statusComboBox->setVisible(false);
    ui->platformComboBox->setVisible(false);
    ui->searchLineEdit->setVisible(false);
    if (ui->libraryColumnsFrame) ui->libraryColumnsFrame->setVisible(false);
    ui->detailsFrame->setVisible(false);
    ui->gamesList->setVisible(false);
    ui->settingsFrame->setVisible(true);
    ui->sectionTitleLabel->setText(ui->langUkButton->isChecked() ? "Налаштування" : "Settings");
}

void MainWindow::applyDarkTheme() { qApp->setStyleSheet(darkStyleSheet); }
void MainWindow::applyLightTheme() { qApp->setStyleSheet(lightStyleSheet); }

void MainWindow::applyUkrainianLanguage() {
    ui->libraryButton->setText("Бібліотека");
    ui->achievementsButton->setText("Досягнення");
    ui->settingsButton->setText("Налаштування");
    ui->sectionTitleLabel->setText(isAchievementsPage ? (ui->settingsFrame->isVisible() ? "Налаштування" : "Досягнення (Оберіть гру)") : "Моя ігрова бібліотека");
    ui->genreComboBox->setItemText(0, "Жанр");
    ui->statusComboBox->setItemText(0, "Статус");
    ui->platformComboBox->setItemText(0, "Платформа");
    ui->searchLineEdit->setPlaceholderText("Пошук гри...");
    ui->addGameButton->setText("+ Додати");
    ui->bottomAddGameButton->setText("+ Додати гру");
    ui->detailsHeaderLabel->setText("Деталі гри");
    ui->mutedLabel->setText("Останні досягнення");
    ui->themeDarkButton->setText("Темна");
    ui->themeLightButton->setText("Світла");
    ui->viewAchievementsButton->setText("Досягнення");
    filterGames();
}

void MainWindow::applyEnglishLanguage() {
    ui->libraryButton->setText("Library");
    ui->achievementsButton->setText("Achievements");
    ui->settingsButton->setText("Settings");
    ui->sectionTitleLabel->setText(isAchievementsPage ? (ui->settingsFrame->isVisible() ? "Settings" : "Achievements (Select Game)") : "My Game Library");
    ui->genreComboBox->setItemText(0, "Genre");
    ui->statusComboBox->setItemText(0, "Status");
    ui->platformComboBox->setItemText(0, "Platform");
    ui->searchLineEdit->setPlaceholderText("Search games...");
    ui->addGameButton->setText("+ Add");
    ui->bottomAddGameButton->setText("+ Add Game");
    ui->detailsHeaderLabel->setText("Game Details");
    ui->mutedLabel->setText("Recent Achievements");
    ui->themeDarkButton->setText("Dark");
    ui->themeLightButton->setText("Light");
    ui->viewAchievementsButton->setText("Achievements");
    filterGames();
}

void MainWindow::setActiveSidebarButton(QPushButton *activeButton) {
    ui->libraryButton->setChecked(false);
    ui->achievementsButton->setChecked(false);
    ui->steamImportButton->setChecked(false);
    ui->settingsButton->setChecked(false);
    if (activeButton) activeButton->setChecked(true);
}

void MainWindow::updateGameRowsSelection() {
    const int selectedRow = ui->gamesList->currentRow();
    for (int row = 0; row < ui->gamesList->count(); ++row) {
        QListWidgetItem *item = ui->gamesList->item(row);
        QWidget *widget = ui->gamesList->itemWidget(item);
        auto *frame = qobject_cast<QFrame *>(widget);
        if (!frame) continue;

        if (row == selectedRow) {
            frame->setStyleSheet("QFrame#gameRowFrame { border: 2px solid #d32f2f; border-radius: 12px; background: transparent; }");
        } else {
            frame->setStyleSheet("QFrame#gameRowFrame { border: 1px solid transparent; border-radius: 12px; background: transparent; }");
        }
    }
}

void MainWindow::saveGamesToJson() {
    QJsonArray jsonArray;
    for (const Game& game : games) {
        QJsonObject jsonObj;
        jsonObj["title"] = game.title;
        jsonObj["genre"] = game.genre;
        jsonObj["platform"] = game.platform;
        jsonObj["hours"] = game.hours;
        jsonObj["totalAchievements"] = game.totalAchievements;
        jsonObj["openedAchievements"] = game.openedAchievements;
        jsonObj["posterPath"] = game.posterPath;
        jsonObj["steamAppId"] = game.steamAppId;
        jsonObj["ownerSteamId"] = game.ownerSteamId;

        jsonArray.append(jsonObj);
    }
    QJsonDocument doc(jsonArray);
    QFile file("games.json");
    if (file.open(QIODevice::WriteOnly)) { file.write(doc.toJson()); file.close(); }
}

void MainWindow::loadGamesFromJson() {
    games.clear();
    QFile file("games.json");
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = doc.array();
    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject jsonObj = jsonArray[i].toObject();
        Game g;
        g.title = jsonObj["title"].toString();
        g.genre = jsonObj["genre"].toString();
        g.platform = jsonObj["platform"].toString();
        g.hours = jsonObj["hours"].toInt();
        g.totalAchievements = jsonObj["totalAchievements"].toInt();
        g.openedAchievements = jsonObj["openedAchievements"].toInt();
        g.posterPath = jsonObj["posterPath"].toString();
        g.steamAppId = jsonObj["steamAppId"].toString();
        g.ownerSteamId = jsonObj["ownerSteamId"].toString();

        games.append(g);
    }
}