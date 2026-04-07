#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTranslator>

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
    // Обробка вибору гри
    void onGameSelected();

    // Обробка натискання кнопки "Додати гру"
    void onAddGameClicked();

    // Відкриття вікна досягнень
    void openAchievementsDialog();

    // Перемикання на екран бібліотеки
    void showLibraryPage();

    // Перемикання на екран усіх досягнень
    void showAchievementsPage();

    // Перемикання на екран Steam Import
    void showSteamImportPage();

    // Перемикання на екран налаштувань
    void showSettingsPage();

    // Зміна теми
    void applyDarkTheme();
    void applyLightTheme();

    // Зміна мови
    void applyUkrainianLanguage();
    void applyEnglishLanguage();

private:
    Ui::MainWindow *ui;
    QTranslator appTranslator;
    QString darkStyleSheet;
    QString lightStyleSheet;

    // Масив ігор
    QVector<Game> games;
    QVector<AchievementEntry> allAchievements;

    // Поточний екран у центральній частині
    bool isAchievementsPage = false;

    // Оновлення списку ігор на екрані
    void updateGamesListUI();

    // Завантаження локальних досягнень у праву панель
    void loadRecentAchievements(const QString &gameTitle);

    // Завантаження всіх досягнень з локальних JSON
    void loadAllAchievementsFromJson();

    // Пошук валідного шляху до іконки досягнення
    QString resolveAchievementIconPath(const QString &rawIconPath) const;

    // Оновлення активної кнопки в sidebar
    void setActiveSidebarButton(QPushButton *activeButton);

    // Оновлення візуального стану рядків у списку ігор
    void updateGameRowsSelection();

};

#endif // MAINWINDOW_H