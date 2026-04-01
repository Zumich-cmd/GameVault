#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector> // для зберігання списку ігор

// структура для зберігання даних нашої проги
struct Game {
    QString title;
    QString genre;
    QString platform;
    int hours;
    int totalAchievements;
    int openedAchievements;
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
    void onGameSelected(); // обробка вибору гри
    void onAddGameClicked(); // обробка натискання кнопки "Додати гру"

private:
    Ui::MainWindow *ui;

    QVector<Game> games; // наш масив ігор
    void updateGamesListUI(); // метод для оновлення списку на екрані
};

#endif // MAINWINDOW_H