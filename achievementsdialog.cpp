#include "achievementsdialog.h"
#include "ui_achievementsdialog.h"
#include "buttonhoveranimator.h"

#include <QFile>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <QUrl>
#include <QNetworkRequest>

AchievementsDialog::AchievementsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AchievementsDialog)
{
    ui->setupUi(this);
    setWindowTitle("Досягнення");

    // ФІКС БІЛОЇ ТЕМИ: Вбиваємо всі захардкоджені кольори з Qt Designer
    this->setStyleSheet("");
    QList<QWidget*> widgets = this->findChildren<QWidget*>();
    for(QWidget* w : widgets) {
        QString cName = w->metaObject()->className();
        if(cName == "QFrame" || cName == "QWidget") {
            w->setStyleSheet("background: transparent; border: none;");
        }
    }

    netManager = new QNetworkAccessManager(this);

    connect(ui->closeButton, &QPushButton::clicked, this, &QDialog::accept);
    ui->closeButton->setCursor(Qt::PointingHandCursor);
    installHoverAnimation(ui->closeButton, ButtonHoverPalette{QColor("#d32f2f"), QColor("#ff3d3d"), QColor("#b92a2a"), QColor(), QColor(), false}, this);

    ui->achievementsList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->achievementsList->setFocusPolicy(Qt::NoFocus);
    ui->achievementsList->setWordWrap(true);
    ui->achievementsList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->achievementsList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

AchievementsDialog::~AchievementsDialog() { delete ui; }

void AchievementsDialog::setGameTitle(const QString &title) { ui->gameTitleLabel->setText(title); }

void AchievementsDialog::loadAchievementsForGame(const QString &gameTitle, const QString &steamAppId, const QString &steamId)
{
    ui->achievementsList->clear();
    ui->gameTitleLabel->setText(gameTitle);

    if (!steamAppId.isEmpty() && !steamId.isEmpty()) {
        currentAppId = steamAppId;
        currentSteamId = steamId;
        steamAchievements.clear();

        ui->achievementsList->addItem("Завантаження даних зі Steam API...");

        QString apiKey = "7867BE5270C9793801AF225244020B03";
        QString url = QString("https://api.steampowered.com/ISteamUserStats/GetSchemaForGame/v2/?key=%1&appid=%2").arg(apiKey, steamAppId);
        QNetworkRequest req((QUrl(url)));
        QNetworkReply *reply = netManager->get(req);
        connect(reply, &QNetworkReply::finished, this, [this, reply]() { onSchemaFinished(reply); });
        return;
    }

    QString basePath = QCoreApplication::applicationDirPath();
    QString filePath;
    if (gameTitle == "Elden Ring") filePath = basePath + "/assets/achievements/elden_ring.json";
    else if (gameTitle == "Hades") filePath = basePath + "/assets/achievements/hades.json";
    else if (gameTitle == "Hollow Knight") filePath = basePath + "/assets/achievements/hollow_knight.json";
    else { ui->achievementsList->addItem("Немає локальних досягнень"); return; }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) { ui->achievementsList->addItem("Не вдалося відкрити файл"); return; }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) return;
    QJsonArray arr = doc.array();

    for (const auto &value : arr) {
        QJsonObject obj = value.toObject();
        QString title = obj["title"].toString();
        QString description = obj["description"].toString();
        QString iconPath = obj["icon"].toString();
        bool unlocked = obj["unlocked"].toBool();

        QWidget *cardWidget = new QWidget;
        cardWidget->setMinimumHeight(72);
        cardWidget->setObjectName("achCard"); // Замість хардкоду юзаємо CSS змінну

        QHBoxLayout *mainLayout = new QHBoxLayout(cardWidget);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        mainLayout->setSpacing(12);

        QLabel *iconLabel = new QLabel;
        iconLabel->setFixedSize(48, 48);
        iconLabel->setAlignment(Qt::AlignCenter);

        QPixmap pix(basePath + "/" + iconPath);
        if (!pix.isNull()) {
            iconLabel->setPixmap(pix.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            iconLabel->setText(unlocked ? "✔" : "✖");
            iconLabel->setStyleSheet(unlocked ? "color: #7ee787; font-size: 24px; font-weight: bold;" : "color: #ff7b72; font-size: 24px; font-weight: bold;");
        }

        QVBoxLayout *textLayout = new QVBoxLayout;
        textLayout->setSpacing(2);
        QLabel *titleLabel = new QLabel(title);
        titleLabel->setObjectName("achTitle");

        QLabel *descriptionLabel = new QLabel(description);
        descriptionLabel->setObjectName("achDesc");
        descriptionLabel->setWordWrap(true);

        textLayout->addWidget(titleLabel);
        textLayout->addWidget(descriptionLabel);
        QWidget *textContainer = new QWidget;
        textContainer->setLayout(textLayout);

        QLabel *statusLabel = new QLabel(unlocked ? "Відкрито" : "Зачинено");
        statusLabel->setAlignment(Qt::AlignCenter);
        statusLabel->setFixedSize(92, 40);
        if (unlocked) statusLabel->setStyleSheet("color: #7ee787; background-color: #132a1b; border-radius: 8px; font-weight: bold;");
        else statusLabel->setStyleSheet("color: #ff7b72; background-color: #2d1316; border-radius: 8px; font-weight: bold;");

        mainLayout->addWidget(iconLabel);
        mainLayout->addWidget(textContainer, 1);
        mainLayout->addWidget(statusLabel);

        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(0, 76));
        ui->achievementsList->addItem(item);
        ui->achievementsList->setItemWidget(item, cardWidget);
    }
}

void AchievementsDialog::onSchemaFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray achArray = doc.object()["game"].toObject()["availableGameStats"].toObject()["achievements"].toArray();

        for (int i = 0; i < achArray.size(); ++i) {
            QJsonObject obj = achArray[i].toObject();
            AchInfo info;
            info.displayName = obj["displayName"].toString();
            info.description = obj["description"].toString();
            steamAchievements[obj["name"].toString()] = info;
        }

        QString apiKey = "7867BE5270C9793801AF225244020B03";
        QString url = QString("https://api.steampowered.com/ISteamUserStats/GetPlayerAchievements/v0001/?appid=%1&key=%2&steamid=%3")
                          .arg(currentAppId, apiKey, currentSteamId);
        QNetworkRequest req((QUrl(url)));
        QNetworkReply *pReply = netManager->get(req);
        connect(pReply, &QNetworkReply::finished, this, [this, pReply]() { onPlayerStatsFinished(pReply); });
    } else {
        ui->achievementsList->clear();
        ui->achievementsList->addItem("Помилка Steam API. Можливо, ця гра не має системи досягнень.");
    }
    reply->deleteLater();
}

void AchievementsDialog::onPlayerStatsFinished(QNetworkReply *reply) {
    ui->achievementsList->clear();
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject playerstats = doc.object()["playerstats"].toObject();

        if(playerstats["success"].toBool()) {
            QJsonArray playerAch = playerstats["achievements"].toArray();
            for (int i = 0; i < playerAch.size(); ++i) {
                QJsonObject obj = playerAch[i].toObject();
                QString apiName = obj["apiname"].toString();
                if (steamAchievements.contains(apiName)) {
                    steamAchievements[apiName].unlocked = (obj["achieved"].toInt() == 1);
                }
            }
            renderSteamAchievements();
        } else {
            ui->achievementsList->addItem("Профіль Steam прихований або статистика недоступна.");
        }
    } else {
        ui->achievementsList->addItem("Помилка завантаження статистики гравця.");
    }
    reply->deleteLater();
}

void AchievementsDialog::renderSteamAchievements() {
    if (steamAchievements.isEmpty()) {
        ui->achievementsList->addItem("У цій грі немає досягнень.");
        return;
    }

    for (const AchInfo &info : steamAchievements) {
        QWidget *cardWidget = new QWidget;
        cardWidget->setMinimumHeight(72);
        cardWidget->setObjectName("achCard"); // Замість хардкоду юзаємо CSS змінну

        QHBoxLayout *mainLayout = new QHBoxLayout(cardWidget);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        mainLayout->setSpacing(12);

        QLabel *iconLabel = new QLabel;
        iconLabel->setFixedSize(48, 48);
        iconLabel->setAlignment(Qt::AlignCenter);
        iconLabel->setText(info.unlocked ? "✔" : "✖");
        iconLabel->setStyleSheet(info.unlocked ? "color: #7ee787; font-size: 26px; font-weight: bold;" : "color: #ff7b72; font-size: 26px; font-weight: bold;");

        QVBoxLayout *textLayout = new QVBoxLayout;
        textLayout->setSpacing(2);
        QLabel *titleLabel = new QLabel(info.displayName);
        titleLabel->setObjectName("achTitle");

        QLabel *descriptionLabel = new QLabel(info.description);
        descriptionLabel->setObjectName("achDesc");
        descriptionLabel->setWordWrap(true);

        textLayout->addWidget(titleLabel);
        textLayout->addWidget(descriptionLabel);
        QWidget *textContainer = new QWidget;
        textContainer->setLayout(textLayout);

        QLabel *statusLabel = new QLabel(info.unlocked ? "Відкрито" : "Зачинено");
        statusLabel->setAlignment(Qt::AlignCenter);
        statusLabel->setFixedSize(92, 40);
        if (info.unlocked) statusLabel->setStyleSheet("color: #7ee787; background-color: #132a1b; border-radius: 8px; font-weight: bold;");
        else statusLabel->setStyleSheet("color: #ff7b72; background-color: #2d1316; border-radius: 8px; font-weight: bold;");

        mainLayout->addWidget(iconLabel);
        mainLayout->addWidget(textContainer, 1);
        mainLayout->addWidget(statusLabel);

        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(0, 76));
        ui->achievementsList->addItem(item);
        ui->achievementsList->setItemWidget(item, cardWidget);
    }
}