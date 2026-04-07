#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class AddGameDialog;
}

class AddGameDialog : public QDialog
{
    Q_OBJECT

public:
    // Конструктор (створення вікна)
    explicit AddGameDialog(QWidget *parent = nullptr);

    // Деструктор (очищення пам'яті)
    ~AddGameDialog();

    // Отримати назву гри
    QString getTitle() const;

    // Отримати жанр гри
    QString getGenre() const;

    // Отримати платформу
    QString getPlatform() const;

    // Отримати кількість годин
    int getHours() const;

    // Отримати загальну кількість досягнень
    int getTotalAchievements() const;

    // Отримати відкриті досягнення
    int getOpenedAchievements() const;

    // Отримати постер
    QString getPosterPath() const;

private:
    // Вказівник на UI форму (елементи з Designer)
    Ui::AddGameDialog *ui;
};

#endif