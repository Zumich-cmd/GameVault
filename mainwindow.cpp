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

namespace {

QPixmap makeRoundedThumb(const QPixmap &source, const QSize &targetSize)
{
    if (source.isNull()) {
        return QPixmap();
    }

    // Масштабуємо під розмір прев'ю з акуратним центральним crop
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

QString defaultThumbPathForGame(const QString &title)
{
    const QString basePath = QCoreApplication::applicationDirPath();

    if (title == "Elden Ring") {
        return basePath + "/assets/achievements/icons/elden_ring/elden_lord.png";
    }
    if (title == "Hades") {
        return basePath + "/assets/achievements/icons/hades/death_dealer.png";
    }
    if (title == "Hollow Knight") {
        return basePath + "/assets/achievements/icons/hollow_knight/hollow_knight.png";
    }
    if (title == "Cyberpunk 2077") {
        return basePath + "/assets/achievements/icons/elden_ring/radahn.png";
    }
    if (title == "Sekiro") {
        return basePath + "/assets/achievements/icons/elden_ring/morgott.png";
    }

    return QString();
}

QString defaultCoverPathForGame(const QString &title)
{
    const QString basePath = QCoreApplication::applicationDirPath();

    if (title == "Elden Ring") {
        return basePath + "/assets/achievements/icons/elden_ring/elden_lord.png";
    }
    if (title == "Hades") {
        return basePath + "/assets/achievements/icons/hades/death_dealer.png";
    }
    if (title == "Hollow Knight") {
        return basePath + "/assets/achievements/icons/hollow_knight/hollow_knight.png";
    }
    if (title == "Cyberpunk 2077") {
        return basePath + "/assets/achievements/icons/elden_ring/radahn.png";
    }
    if (title == "Sekiro") {
        return basePath + "/assets/achievements/icons/elden_ring/morgott.png";
    }

    return QString();
}

}

// Конструктор головного вікна
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Ініціалізація UI
    ui->setupUi(this);

    // Зберігаємо поточну (dark) тему зі стилів Designer
    darkStyleSheet = this->styleSheet();
    lightStyleSheet =
        "QMainWindow, QWidget {"
        "  background-color: #f5f7fb;"
        "  color: #11161d;"
        "  font-family: \"Segoe UI\";"
        "}"
        "#sidebarFrame { background-color: #ffffff; border-radius: 14px; }"
        "#detailsFrame { background-color: #ffffff; border-radius: 14px; }"
        "QLineEdit, QComboBox {"
        "  background-color: #ffffff;"
        "  border: 1px solid #d0d7e2;"
        "  border-radius: 10px;"
        "  padding: 6px;"
        "  color: #11161d;"
        "}"
        "QPushButton {"
        "  background-color: #e9eef6;"
        "  border: 1px solid #d0d7e2;"
        "  border-radius: 10px;"
        "  padding: 6px 12px;"
        "  color: #11161d;"
        "}"
        "QPushButton:hover { background-color: #dde6f3; }";

    // Назва вікна
    setWindowTitle("GameVault");

    // Перемикач sidebar (активна тільки одна кнопка)
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
    ui->gamesList->setWordWrap(true);
    ui->gamesList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gamesList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->gamesList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->gamesList->verticalScrollBar()->setSingleStep(10);

    // Підключення сигналів
    connect(ui->gamesList, &QListWidget::itemClicked,
            this, &MainWindow::onGameSelected);
    connect(ui->gamesList, &QListWidget::currentRowChanged,
            this, [this](int) { updateGameRowsSelection(); });

    connect(ui->addGameButton, &QPushButton::clicked,
            this, &MainWindow::onAddGameClicked);

    connect(ui->bottomAddGameButton, &QPushButton::clicked,
            this, &MainWindow::onAddGameClicked);

    connect(ui->viewAchievementsButton, &QPushButton::clicked,
            this, &MainWindow::openAchievementsDialog);
    connect(ui->libraryButton, &QPushButton::clicked,
            this, &MainWindow::showLibraryPage);
    connect(ui->achievementsButton, &QPushButton::clicked,
            this, &MainWindow::showAchievementsPage);
    connect(ui->steamImportButton, &QPushButton::clicked,
            this, &MainWindow::showSteamImportPage);
    connect(ui->settingsButton, &QPushButton::clicked,
            this, &MainWindow::showSettingsPage);

    // Налаштування груп кнопок на сторінці налаштувань
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

    // Ставимо курсор-указівник для інтерактивних кнопок
    ui->libraryButton->setCursor(Qt::PointingHandCursor);
    ui->achievementsButton->setCursor(Qt::PointingHandCursor);
    ui->steamImportButton->setCursor(Qt::PointingHandCursor);
    ui->settingsButton->setCursor(Qt::PointingHandCursor);
    ui->addGameButton->setCursor(Qt::PointingHandCursor);
    ui->bottomAddGameButton->setCursor(Qt::PointingHandCursor);
    ui->viewAchievementsButton->setCursor(Qt::PointingHandCursor);
    ui->libraryAddButton->setCursor(Qt::PointingHandCursor);
    ui->addGameButton->setVisible(false);

    // Додаємо плавну анімацію зміни кольору при наведенні
    installHoverAnimation(
        ui->libraryButton,
        ButtonHoverPalette{QColor("#11161d"), QColor("#252d39"), QColor("#1b222d"), QColor("#d32f2f"), QColor("#ff3d3d"), true},
        this
        );
    installHoverAnimation(
        ui->achievementsButton,
        ButtonHoverPalette{QColor("#11161d"), QColor("#252d39"), QColor("#1b222d"), QColor("#d32f2f"), QColor("#ff3d3d"), true},
        this
        );
    installHoverAnimation(
        ui->steamImportButton,
        ButtonHoverPalette{QColor("#11161d"), QColor("#252d39"), QColor("#1b222d"), QColor("#d32f2f"), QColor("#ff3d3d"), true},
        this
        );
    installHoverAnimation(
        ui->settingsButton,
        ButtonHoverPalette{QColor("#11161d"), QColor("#252d39"), QColor("#1b222d"), QColor("#d32f2f"), QColor("#ff3d3d"), true},
        this
        );
    installHoverAnimation(
        ui->addGameButton,
        ButtonHoverPalette{QColor("#d32f2f"), QColor("#ff3d3d"), QColor("#b92a2a"), QColor(), QColor(), false},
        this
        );
    installHoverAnimation(
        ui->bottomAddGameButton,
        ButtonHoverPalette{QColor("#942B2B"), QColor("#b33636"), QColor("#7a2323"), QColor(), QColor(), false},
        this
        );
    installHoverAnimation(
        ui->viewAchievementsButton,
        ButtonHoverPalette{QColor("#1c222b"), QColor("#323b49"), QColor("#262d38"), QColor(), QColor(), false},
        this
        );
    installHoverAnimation(
        ui->libraryAddButton,
        ButtonHoverPalette{QColor("#d32f2f"), QColor("#ff3d3d"), QColor("#b92a2a"), QColor(), QColor(), false},
        this
        );
    connect(ui->libraryAddButton, &QPushButton::clicked, this, &MainWindow::onAddGameClicked);

    // Налаштування списку останніх досягнень
    ui->recentAchievementsList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->recentAchievementsList->setFocusPolicy(Qt::NoFocus);
    ui->recentAchievementsList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->recentAchievementsList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->recentAchievementsList->setWordWrap(true);
    ui->recentAchievementsList->setTextElideMode(Qt::ElideRight);
    // Стилізуємо scrollbar під заданий дизайн
    ui->recentAchievementsList->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical {"
        "  background: #232E33;"
        "  width: 8px;"
        "  margin: 0px;"
        "  border-radius: 4px;"
        "  border: none;"
        "}"
        "QScrollBar::groove:vertical {"
        "  background: transparent;"
        "  border-radius: 4px;"
        "  margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "  background: #612222;"
        "  min-height: 28px;"
        "  border-radius: 4px;"
        "  border: none;"
        "  margin: 0px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "  background: #7a2b2b;"
        "}"
        "QScrollBar::handle:vertical:pressed {"
        "  background: #8f3333;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "  background: transparent;"
        "  border: none;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "  height: 0px;"
        "  width: 0px;"
        "  margin: 0px;"
        "  padding: 0px;"
        "  background: transparent;"
        "  border: none;"
        "}"
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
        "  background: transparent;"
        "  height: 0px;"
        "}"
        );

    // Тестові ігри
    games.push_back({"Elden Ring", "RPG", "Steam", 145, 50, 39, ""});
    games.push_back({"Cyberpunk 2077", "RPG", "Steam", 120, 57, 32, ""});
    games.push_back({"Hades", "Roguelike", "Steam", 64, 49, 21, ""});
    games.push_back({"Hollow Knight", "Metroidvania", "Steam", 71, 63, 47, ""});
    games.push_back({"Sekiro", "Action", "Steam", 58, 34, 28, ""});

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
        newGame.posterPath = dialog.getPosterPath();

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
    if (isAchievementsPage) {
        return;
    }

    ui->gamesList->clear();

    for (int i = 0; i < games.size(); ++i) {
        const Game &g = games[i];
        const int progress = (g.totalAchievements > 0)
                                 ? qBound(0, (g.openedAchievements * 100) / g.totalAchievements, 100)
                                 : 0;

        auto *item = new QListWidgetItem();
        item->setSizeHint(QSize(0, 64));
        item->setData(Qt::UserRole, i);
        ui->gamesList->addItem(item);

        auto *rowFrame = new QFrame;
        rowFrame->setObjectName("gameRowFrame");
        rowFrame->setStyleSheet(
            "QFrame#gameRowFrame {"
            "background-color: #141a22;"
            "border: 1px solid transparent;"
            "border-radius: 12px;"
            "}"
            );

        auto *rowLayout = new QHBoxLayout(rowFrame);
        rowLayout->setContentsMargins(12, 8, 12, 8);
        rowLayout->setSpacing(10);

        auto *indexLabel = new QLabel(QString("#%1").arg(i + 1));
        indexLabel->setFixedWidth(28);
        indexLabel->setStyleSheet("color: #f5f7fa; font-weight: 700; font-size: 10pt;");

        auto *thumbLabel = new QLabel;
        thumbLabel->setFixedSize(64, 36);
        thumbLabel->setAlignment(Qt::AlignCenter);
        thumbLabel->setStyleSheet("background-color: #0f1319; border-radius: 6px; color: #d7c58a; font-size: 7pt; font-weight: 700;");

        QPixmap thumbPixmap;
        if (!g.posterPath.isEmpty()) {
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
        titleLabel->setStyleSheet("color: #ffffff; font-size: 10.5pt; font-weight: 700;");

        auto *genreLabel = new QLabel(g.genre);
        genreLabel->setMinimumWidth(92);
        genreLabel->setStyleSheet("color: #f0f3f8; font-size: 10pt; font-weight: 600;");

        auto *hoursLabel = new QLabel(QString("%1h").arg(g.hours));
        hoursLabel->setMinimumWidth(62);
        hoursLabel->setStyleSheet("color: #f0f3f8; font-size: 11pt; font-weight: 700;");

        auto *progressText = new QLabel(QString("%1%").arg(progress));
        progressText->setMinimumWidth(40);
        progressText->setStyleSheet("color: #f0f3f8; font-size: 10pt; font-weight: 700;");

        auto *rowProgress = new QProgressBar;
        rowProgress->setRange(0, 100);
        rowProgress->setValue(progress);
        rowProgress->setTextVisible(false);
        rowProgress->setFixedSize(118, 8);
        rowProgress->setStyleSheet(
            "QProgressBar {"
            "background-color: #38404b;"
            "border: none;"
            "border-radius: 4px;"
            "}"
            "QProgressBar::chunk {"
            "background-color: #d32f2f;"
            "border-radius: 4px;"
            "}"
            );

        auto *fractionLabel = new QLabel(QString("%1/%2").arg(g.openedAchievements).arg(g.totalAchievements));
        fractionLabel->setMinimumWidth(48);
        fractionLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        fractionLabel->setStyleSheet("color: #f0f3f8; font-size: 10pt; font-weight: 700;");

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

    // Оновлюємо лічильник ігор
    ui->gamesCountLabel->setText(QString::number(games.size()) + " ігор");

    // Якщо є ігри, вибираємо першу
    if (games.size() > 0 && ui->gamesList->currentRow() == -1) {
        ui->gamesList->setCurrentRow(0);
        onGameSelected();
    }

    updateGameRowsSelection();
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
        const QString iconPath = resolveAchievementIconPath(obj["icon"].toString());
        bool unlocked = obj["unlocked"].toBool();
        if (title.isEmpty()) {
            title = "Без назви";
        }

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
        if (!iconPix.isNull()) {
            iconLabel->setPixmap(makeRoundedThumb(iconPix, iconLabel->size()));
        } else {
            iconLabel->setText(unlocked ? "✔" : "✖");
            iconLabel->setStyleSheet("background-color: #0f1319; border-radius: 7px; color: #b7c2d1; font-weight: 700;");
        }

        QVBoxLayout *textLayout = new QVBoxLayout;
        textLayout->setSpacing(0);
        textLayout->setContentsMargins(0, 0, 0, 0);

        QLabel *titleLabel = new QLabel(title);
        titleLabel->setStyleSheet("color: #ffffff; font-size: 12pt; font-weight: 700;");
        titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        titleLabel->setTextInteractionFlags(Qt::NoTextInteraction);
        titleLabel->setWordWrap(false);
        titleLabel->setToolTip(title);

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

// Оновлення правої панелі при виборі гри
void MainWindow::onGameSelected()
{
    if (isAchievementsPage) {
        return;
    }

    int index = ui->gamesList->currentRow();

    // Якщо нічого не вибрано
    if (index < 0 || index >= games.size())
        return;

    // Беремо гру з масиву
    const Game &game = games[index];

    // Оновлюємо праву панель
    ui->gameNameLabel->setText(game.title);
    ui->genreInfoLabel->setText("Жанр: " + game.genre);
    ui->hoursInfoLabel->setText("Ігрові години: " + QString::number(game.hours) + " hours");
    ui->totalAchievementsInfoLabel->setText("Усього досягнень: " + QString::number(game.totalAchievements));
    const int percent = (game.totalAchievements > 0) ? (game.openedAchievements * 100) / game.totalAchievements : 0;
    ui->openedAchievementsInfoLabel->setText(
        QString("Відкрито: %1  (%2% Complete)").arg(game.openedAchievements).arg(percent)
        );
    ui->platformInfoLabel->setText("Платформа: " + game.platform);
    {
        QString coverPath = game.posterPath;
        if (coverPath.isEmpty()) {
            coverPath = defaultCoverPathForGame(game.title);
        }

        QPixmap cover(coverPath);

        if (!cover.isNull()) {
            const QSize targetSize = ui->coverLabel->size();

            // Розраховуємо розмір обрізки під формат блоку постера
            const QSize sourceSize = cover.size();
            const double sourceRatio = static_cast<double>(sourceSize.width()) / sourceSize.height();
            const double targetRatio = static_cast<double>(targetSize.width()) / targetSize.height();

            QRect cropRect(0, 0, sourceSize.width(), sourceSize.height());

            // Якщо зображення надто широке — ріжемо по боках (по центру)
            if (sourceRatio > targetRatio) {
                const int cropWidth = static_cast<int>(sourceSize.height() * targetRatio);
                const int x = (sourceSize.width() - cropWidth) / 2;
                cropRect = QRect(x, 0, cropWidth, sourceSize.height());
            }
            // Якщо зображення вертикальне — ріжемо по висоті з пріоритетом верхньої частини
            else if (sourceRatio < targetRatio) {
                const int cropHeight = static_cast<int>(sourceSize.width() / targetRatio);
                int y = static_cast<int>(sourceSize.height() * 0.10); // зміщення вгору як у постерах з логотипом зверху
                if (y + cropHeight > sourceSize.height()) {
                    y = sourceSize.height() - cropHeight;
                }
                if (y < 0) {
                    y = 0;
                }
                cropRect = QRect(0, y, sourceSize.width(), cropHeight);
            }

            const QPixmap cropped = cover.copy(cropRect).scaled(
                targetSize,
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation
                );

            // QLabel не кліпить pixmap по border-radius через stylesheet,
            // тому застосовуємо скруглення безпосередньо до зображення.
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
    ui->viewAchievementsButton->setText("Подивитись досягнення");

    // Завантажуємо останні досягнення
    loadRecentAchievements(game.title);
}

// Завантаження всіх досягнень з локальних JSON
void MainWindow::loadAllAchievementsFromJson()
{
    allAchievements.clear();

    QString basePath = QCoreApplication::applicationDirPath() + "/assets/achievements";
    QDir dir(basePath);

    if (!dir.exists()) {
        return;
    }

    const QStringList files = dir.entryList(QStringList() << "*.json", QDir::Files);

    for (const QString &fileName : files) {
        QFile file(dir.filePath(fileName));
        if (!file.open(QIODevice::ReadOnly)) {
            continue;
        }

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        if (!doc.isArray()) {
            continue;
        }

        QString gameTitle = fileName;
        gameTitle.chop(5); // прибираємо .json
        gameTitle.replace("_", " ");

        if (!gameTitle.isEmpty()) {
            gameTitle[0] = gameTitle[0].toUpper();
        }

        QJsonArray arr = doc.array();
        for (const auto &value : arr) {
            const QJsonObject obj = value.toObject();

            AchievementEntry entry;
            entry.gameTitle = gameTitle;
            entry.title = obj["title"].toString("Без назви");
            entry.description = obj["description"].toString("Без опису");
            entry.iconPath = resolveAchievementIconPath(obj["icon"].toString());
            entry.unlocked = obj["unlocked"].toBool(false);
            allAchievements.push_back(entry);
        }
    }
}

// Пошук валідного шляху до іконки досягнення
QString MainWindow::resolveAchievementIconPath(const QString &rawIconPath) const
{
    if (rawIconPath.isEmpty()) {
        return QString();
    }

    const QString basePath = QCoreApplication::applicationDirPath();
    const QString directPath = basePath + "/" + rawIconPath;
    if (QFile::exists(directPath)) {
        return directPath;
    }

    QFileInfo info(rawIconPath);
    const QString fileName = info.fileName();
    const QString stem = info.completeBaseName().toLower();
    const QString parentDir = info.path().section('/', -1);
    const QString iconsDirPath = basePath + "/assets/achievements/icons/" + parentDir;
    QDir iconsDir(iconsDirPath);

    if (!iconsDir.exists()) {
        return QString();
    }

    // Якщо ім'я не збігається, підбираємо найближчий файл за частиною назви
    const QStringList candidates = iconsDir.entryList(QStringList() << "*.png" << "*.jpg" << "*.jpeg" << "*.webp", QDir::Files);
    for (const QString &candidate : candidates) {
        if (candidate.compare(fileName, Qt::CaseInsensitive) == 0) {
            return iconsDir.filePath(candidate);
        }
    }
    for (const QString &candidate : candidates) {
        if (candidate.toLower().contains(stem)) {
            return iconsDir.filePath(candidate);
        }
    }

    return QString();
}

// Перемикання на екран бібліотеки
void MainWindow::showLibraryPage()
{
    setActiveSidebarButton(ui->libraryButton);
    isAchievementsPage = false;

    ui->genreComboBox->setVisible(true);
    ui->statusComboBox->setVisible(true);
    ui->platformComboBox->setVisible(true);
    ui->searchLineEdit->setVisible(true);
    ui->addGameButton->setVisible(false);
    if (ui->libraryColumnsFrame) {
        ui->libraryColumnsFrame->setVisible(true);
    }
    ui->detailsFrame->setVisible(true);
    ui->settingsFrame->setVisible(false);

    ui->sectionTitleLabel->setText("Моя ігрова бібліотека");
    ui->gamesList->setVisible(true);
    updateGamesListUI();
}

// Перемикання на екран усіх досягнень
void MainWindow::showAchievementsPage()
{
    setActiveSidebarButton(ui->achievementsButton);
    isAchievementsPage = true;

    ui->genreComboBox->setVisible(false);
    ui->statusComboBox->setVisible(false);
    ui->platformComboBox->setVisible(false);
    ui->searchLineEdit->setVisible(false);
    ui->addGameButton->setVisible(false);
    if (ui->libraryColumnsFrame) {
        ui->libraryColumnsFrame->setVisible(false);
    }
    ui->detailsFrame->setVisible(false);
    ui->settingsFrame->setVisible(false);

    ui->sectionTitleLabel->setText("Усі досягнення");
    ui->gamesList->clear();
    ui->gamesList->addItem("Завантаження досягнень...");
    ui->gamesCountLabel->setText("...");

    // Відкладаємо важку побудову списку, щоб UI встиг перемалювати активну кнопку
    QTimer::singleShot(0, this, [this]() {
        if (!isAchievementsPage) {
            return;
        }

        loadAllAchievementsFromJson();

        ui->sectionTitleLabel->setText("Усі досягнення");
        ui->gamesList->clear();
        ui->gamesList->setIconSize(QSize(40, 40));

        for (const AchievementEntry &entry : allAchievements) {
            const QString mark = entry.unlocked ? "✔" : "✖";
            const QString itemText = QString("%1 [%2]\n%3\n%4")
                                         .arg(mark)
                                         .arg(entry.gameTitle)
                                         .arg(entry.title)
                                         .arg(entry.description);

            auto *item = new QListWidgetItem(itemText);
            item->setSizeHint(QSize(0, 68));

            if (!entry.iconPath.isEmpty()) {
                QPixmap iconPix(entry.iconPath);
                if (!iconPix.isNull()) {
                    item->setIcon(QIcon(iconPix.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
                }
            }

            ui->gamesList->addItem(item);
        }

        ui->gamesCountLabel->setText(QString::number(allAchievements.size()) + " досягнень");
    });
}

// Перемикання на екран Steam Import
void MainWindow::showSteamImportPage()
{
    setActiveSidebarButton(ui->steamImportButton);
    isAchievementsPage = true;

    ui->genreComboBox->setVisible(false);
    ui->statusComboBox->setVisible(false);
    ui->platformComboBox->setVisible(false);
    ui->searchLineEdit->setVisible(false);
    ui->addGameButton->setVisible(false);
    if (ui->libraryColumnsFrame) {
        ui->libraryColumnsFrame->setVisible(false);
    }
    ui->detailsFrame->setVisible(false);
    ui->settingsFrame->setVisible(false);

    ui->sectionTitleLabel->setText("Steam Import");
    ui->gamesList->clear();
    ui->gamesList->addItem("Імпорт зі Steam буде додано пізніше");
    ui->gamesCountLabel->setText("1 запис");
}

// Перемикання на екран налаштувань
void MainWindow::showSettingsPage()
{
    setActiveSidebarButton(ui->settingsButton);
    isAchievementsPage = true;

    ui->genreComboBox->setVisible(false);
    ui->statusComboBox->setVisible(false);
    ui->platformComboBox->setVisible(false);
    ui->searchLineEdit->setVisible(false);
    ui->addGameButton->setVisible(false);
    if (ui->libraryColumnsFrame) {
        ui->libraryColumnsFrame->setVisible(false);
    }
    ui->detailsFrame->setVisible(false);
    ui->gamesList->setVisible(false);
    ui->settingsFrame->setVisible(true);

    ui->sectionTitleLabel->setText("Налаштування");
}

void MainWindow::applyDarkTheme()
{
    qApp->setStyleSheet(darkStyleSheet);
}

void MainWindow::applyLightTheme()
{
    qApp->setStyleSheet(lightStyleSheet);
}

void MainWindow::applyUkrainianLanguage()
{
    qApp->removeTranslator(&appTranslator);
    const QString baseName = "GameVaultv1_uk_UA";
    const QString basePath = QCoreApplication::applicationDirPath();
    if (appTranslator.load(baseName, basePath)) {
        qApp->installTranslator(&appTranslator);
    }
    ui->retranslateUi(this);
}

void MainWindow::applyEnglishLanguage()
{
    // Англійська — базова мова без перекладача
    qApp->removeTranslator(&appTranslator);
    ui->retranslateUi(this);
}

// Оновлення активної кнопки в sidebar
void MainWindow::setActiveSidebarButton(QPushButton *activeButton)
{
    ui->libraryButton->setChecked(false);
    ui->achievementsButton->setChecked(false);
    ui->steamImportButton->setChecked(false);
    ui->settingsButton->setChecked(false);

    if (activeButton) {
        activeButton->setChecked(true);
    }

    // Одразу синхронізуємо фоновий колір, щоб не було "залипання" до hover-події
    auto applySidebarColor = [activeButton](QPushButton *button) {
        if (button == activeButton) {
            button->setStyleSheet("background-color: #d32f2f;");
        } else {
            button->setStyleSheet("background-color: #11161d;");
        }
    };

    applySidebarColor(ui->libraryButton);
    applySidebarColor(ui->achievementsButton);
    applySidebarColor(ui->steamImportButton);
    applySidebarColor(ui->settingsButton);
}

// Оновлення візуального стану рядків у списку ігор
void MainWindow::updateGameRowsSelection()
{
    if (isAchievementsPage) {
        return;
    }

    const int selectedRow = ui->gamesList->currentRow();
    for (int row = 0; row < ui->gamesList->count(); ++row) {
        QListWidgetItem *item = ui->gamesList->item(row);
        QWidget *widget = ui->gamesList->itemWidget(item);
        auto *frame = qobject_cast<QFrame *>(widget);
        if (!frame) {
            continue;
        }

        if (row == selectedRow) {
            frame->setStyleSheet(
                "QFrame#gameRowFrame {"
                "background-color: #141a22;"
                "border: 1px solid #d32f2f;"
                "border-radius: 12px;"
                "}"
                );
        } else {
            frame->setStyleSheet(
                "QFrame#gameRowFrame {"
                "background-color: #141a22;"
                "border: 1px solid transparent;"
                "border-radius: 12px;"
                "}"
                );
        }
    }
}