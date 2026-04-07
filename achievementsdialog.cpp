#include "achievementsdialog.h"
#include "ui_achievementsdialog.h"

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

// Конструктор
AchievementsDialog::AchievementsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AchievementsDialog)
{
    ui->setupUi(this);

    setWindowTitle("Досягнення");

    connect(ui->closeButton, &QPushButton::clicked,
            this, &QDialog::accept);

    ui->achievementsList->setSelectionMode(QAbstractItemView::NoSelection);
    ui->achievementsList->setFocusPolicy(Qt::NoFocus);
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

// 🔥 ГЛАВНАЯ ФУНКЦИЯ (её у тебя не было)
void AchievementsDialog::loadAchievementsForGame(const QString &gameTitle)
{
    ui->achievementsList->clear();
    ui->gameTitleLabel->setText(gameTitle);

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
        ui->achievementsList->addItem("Немає локальних досягнень");
        return;
    }

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        ui->achievementsList->addItem("Не вдалося відкрити файл");
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) {
        ui->achievementsList->addItem("Помилка JSON");
        return;
    }

    QJsonArray arr = doc.array();

    for (const auto &value : arr) {
        QJsonObject obj = value.toObject();

        QString title = obj["title"].toString();
        QString description = obj["description"].toString();
        QString iconPath = obj["icon"].toString();
        bool unlocked = obj["unlocked"].toBool();

        QWidget *cardWidget = new QWidget;
        cardWidget->setMinimumHeight(72);
        cardWidget->setStyleSheet("background-color: #141a22; border-radius: 10px;");

        QHBoxLayout *mainLayout = new QHBoxLayout(cardWidget);
        mainLayout->setContentsMargins(10, 10, 10, 10);
        mainLayout->setSpacing(12);

        QLabel *iconLabel = new QLabel;
        iconLabel->setFixedSize(48, 48);
        iconLabel->setAlignment(Qt::AlignCenter);

        QPixmap pix(iconPath);
        if (!pix.isNull()) {
            iconLabel->setPixmap(pix.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            iconLabel->setText("No Icon");
            iconLabel->setStyleSheet("color: #9aa4b2;");
        }

        QVBoxLayout *textLayout = new QVBoxLayout;
        textLayout->setSpacing(2);

        QLabel *titleLabel = new QLabel(title);
        titleLabel->setStyleSheet("font-weight: bold; color: white;");

        QLabel *descriptionLabel = new QLabel(description);
        descriptionLabel->setStyleSheet("color: #9aa4b2; font-size: 9pt;");

        textLayout->addWidget(titleLabel);
        textLayout->addWidget(descriptionLabel);

        QWidget *textContainer = new QWidget;
        textContainer->setLayout(textLayout);

        QLabel *statusLabel = new QLabel(unlocked ? "Відкрито" : "Не відкрито");
        statusLabel->setAlignment(Qt::AlignCenter);
        statusLabel->setFixedSize(92, 40);

        if (unlocked) {
            statusLabel->setStyleSheet(
                "color: #7ee787;"
                "background-color: #132a1b;"
                "border-radius: 8px;"
                );
        } else {
            statusLabel->setStyleSheet(
                "color: #ff7b72;"
                "background-color: #2d1316;"
                "border-radius: 8px;"
                );
        }

        mainLayout->addWidget(iconLabel);
        mainLayout->addWidget(textContainer, 1);
        mainLayout->addWidget(statusLabel);

        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(0, 76));

        ui->achievementsList->addItem(item);
        ui->achievementsList->setItemWidget(item, cardWidget);
    }
}