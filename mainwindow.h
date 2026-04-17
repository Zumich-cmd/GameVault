#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTranslator>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

class QListWidgetItem;
class QPushButton;

struct Game {
    QString title;
    QString genre;
    QString platform;
    int hours;
    int totalAchievements;
    int openedAchievements;
    QString posterPath;
    QString steamAppId;   // ID гри в Steam
    QString ownerSteamId; // ID гравця
};

struct AchievementEntry {
    QString gameTitle;
    QString title;
    QString description;
    QString iconPath;
    bool unlocked;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onGameSelected();
    void onGameDoubleClicked(QListWidgetItem *item);
    void onAddGameClicked();
    void openAchievementsDialog();
    void showLibraryPage();
    void showAchievementsPage();
    void showSteamImportPage();
    void showSettingsPage();
    void applyDarkTheme();
    void applyLightTheme();
    void applyUkrainianLanguage();
    void applyEnglishLanguage();
    void filterGames();
    void onNetworkReplyFinished(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QString darkStyleSheet;
    QString lightStyleSheet;

    QVector<Game> games;
    QVector<AchievementEntry> allAchievements;
    bool isAchievementsPage = false;

    QNetworkAccessManager *networkManager;
    QString currentSteamId;
    QString currentSteamName;

    void updateGamesListUI();
    void loadRecentAchievements(const QString &gameTitle);
    void loadAllAchievementsFromJson();
    QString resolveAchievementIconPath(const QString &rawIconPath) const;
    void setActiveSidebarButton(QPushButton *activeButton);
    void updateGameRowsSelection();

    void saveGamesToJson();
    void loadGamesFromJson();
};

#endif // MAINWINDOW_H