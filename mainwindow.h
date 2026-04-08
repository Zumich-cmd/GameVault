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

class QPushButton;

// Структура для зберігання даних гри
struct Game {
    QString title;
    QString genre;
    QString platform;
    int hours;
    int totalAchievements;
    int openedAchievements;
    QString posterPath;
};

// Структура для зберігання даних досягнення
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

    // Новий слот для пошуку та фільтрів
    void filterGames();

private:
    Ui::MainWindow *ui;
    QTranslator appTranslator;
    QString darkStyleSheet;
    QString lightStyleSheet;

    // Масив ігор
    QVector<Game> games;
    QVector<AchievementEntry> allAchievements;

    bool isAchievementsPage = false;

    void updateGamesListUI();
    void loadRecentAchievements(const QString &gameTitle);
    void loadAllAchievementsFromJson();
    QString resolveAchievementIconPath(const QString &rawIconPath) const;
    void setActiveSidebarButton(QPushButton *activeButton);
    void updateGameRowsSelection();

    // Нові методи для роботи з JSON
    void saveGamesToJson();
    void loadGamesFromJson();
};

#endif // MAINWINDOW_H