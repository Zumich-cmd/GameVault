#ifndef ACHIEVEMENTSDIALOG_H
#define ACHIEVEMENTSDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMap>

namespace Ui {
class AchievementsDialog;
}

class AchievementsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AchievementsDialog(QWidget *parent = nullptr);
    ~AchievementsDialog();

    void setGameTitle(const QString &title);

    // Новий метод, який приймає Steam ID
    void loadAchievementsForGame(const QString &gameTitle, const QString &steamAppId = "", const QString &steamId = "");

private slots:
    void onSchemaFinished(QNetworkReply *reply);
    void onPlayerStatsFinished(QNetworkReply *reply);

private:
    Ui::AchievementsDialog *ui;

    QNetworkAccessManager *netManager;
    QString currentAppId;
    QString currentSteamId;

    // Структура для зберігання інфи про ачивки зі Steam
    struct AchInfo {
        QString displayName;
        QString description;
        bool unlocked = false;
    };
    QMap<QString, AchInfo> steamAchievements;

    void renderSteamAchievements();
};

#endif // ACHIEVEMENTSDIALOG_H