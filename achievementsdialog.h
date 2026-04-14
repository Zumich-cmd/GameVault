#ifndef ACHIEVEMENTSDIALOG_H
#define ACHIEVEMENTSDIALOG_H

#include <QDialog>

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
    void loadAchievementsForGame(const QString &gameTitle);

private:
    Ui::AchievementsDialog *ui;
};

#endif // ACHIEVEMENTSDIALOG_H