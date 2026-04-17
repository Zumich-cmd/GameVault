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
    explicit AddGameDialog(QWidget *parent = nullptr);
    ~AddGameDialog();

    QString getTitle() const;
    QString getGenre() const;
    QString getPlatform() const;
    int getHours() const;
    int getTotalAchievements() const;
    int getOpenedAchievements() const;
    QString getPosterPath() const;

    // НОВИЙ МЕТОД: Завантаження даних гри у форму для редагування
    void setGameData(const QString& title, const QString& genre, const QString& platform,
                     int hours, int totalAchiev, int openedAchiev, const QString& posterPath);

private:
    Ui::AddGameDialog *ui;
};

#endif