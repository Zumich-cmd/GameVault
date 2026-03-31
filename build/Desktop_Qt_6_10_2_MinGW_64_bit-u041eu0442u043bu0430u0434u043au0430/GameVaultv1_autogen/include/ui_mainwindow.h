/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *sidebarFrame;
    QVBoxLayout *verticalLayout_2;
    QLabel *logoLabel;
    QPushButton *libraryButton;
    QPushButton *achievementsButton;
    QPushButton *steamImportButton;
    QPushButton *settingsButton;
    QSpacerItem *verticalSpacer;
    QPushButton *bottomAddGameButton;
    QVBoxLayout *verticalLayout;
    QFrame *topBarFrame;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *sectionTitleLabel;
    QSpacerItem *horizontalSpacer;
    QComboBox *genreComboBox;
    QComboBox *statusComboBox;
    QComboBox *platformComboBox;
    QLineEdit *searchLineEdit;
    QPushButton *addGameButton;
    QLabel *gamesCountLabel;
    QListWidget *gamesList;
    QFrame *detailsFrame;
    QVBoxLayout *verticalLayout_4;
    QLabel *detailsHeaderLabel;
    QFrame *coverFrame;
    QVBoxLayout *verticalLayout_5;
    QLabel *coverLabel;
    QLabel *gameNameLabel;
    QLabel *genreInfoLabel;
    QLabel *hoursInfoLabel;
    QLabel *totalAchievementsInfoLabel;
    QLabel *openedAchievementsInfoLabel;
    QProgressBar *progressBar;
    QLabel *mutedLabel;
    QListWidget *recentAchievementsList;
    QLabel *platformInfoLabel;
    QPushButton *viewAchievementsButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1220, 720);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow, QWidget {\n"
"    background-color: #0d1117;\n"
"    color: #f2f2f2;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"#centralwidget {\n"
"    background-color: #0d1117;\n"
"}\n"
"\n"
"QFrame#sidebarFrame {\n"
"    background-color: #131720;\n"
"    border-radius: 14px;\n"
"}\n"
"\n"
"QFrame#detailsFrame {\n"
"    background-color: #131720;\n"
"    border-radius: 14px;\n"
"}\n"
"\n"
"QFrame#topBarFrame {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QLabel#logoLabel {\n"
"    font-size: 16pt;\n"
"    font-weight: 700;\n"
"    color: white;\n"
"}\n"
"\n"
"QLabel#sectionTitleLabel {\n"
"    font-size: 18pt;\n"
"    font-weight: 700;\n"
"    color: white;\n"
"}\n"
"\n"
"QLabel#gamesCountLabel {\n"
"    color: #7d8590;\n"
"    font-size: 9pt;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #1c212b;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #262c"
                        "36;\n"
"}\n"
"\n"
"QPushButton#libraryButton {\n"
"    background-color: #b3261e;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton#libraryButton:hover {\n"
"    background-color: #cf2f25;\n"
"}\n"
"\n"
"QPushButton#addGameButton {\n"
"    background-color: #c62828;\n"
"    font-weight: 700;\n"
"}\n"
"\n"
"QPushButton#addGameButton:hover {\n"
"    background-color: #e53935;\n"
"}\n"
"\n"
"QPushButton#viewAchievementsButton {\n"
"    background-color: #b3261e;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton#viewAchievementsButton:hover {\n"
"    background-color: #cf2f25;\n"
"}\n"
"\n"
"QLineEdit, QComboBox {\n"
"    background-color: #1a1f29;\n"
"    border: 1px solid #2c3440;\n"
"    border-radius: 8px;\n"
"    padding: 7px 8px;\n"
"    color: white;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 18px;\n"
"}\n"
"\n"
"QListWidget#gamesList {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    outline: none;\n"
"}\n"
"\n"
"QListWidget#gamesList::item {\n"
"  "
                        "  background-color: #171c25;\n"
"    border: 1px solid #171c25;\n"
"    border-radius: 12px;\n"
"    margin: 6px 0px;\n"
"    padding: 14px;\n"
"}\n"
"\n"
"QListWidget#gamesList::item:selected {\n"
"    border: 1px solid #c62828;\n"
"    background-color: #171c25;\n"
"}\n"
"\n"
"QListWidget#recentAchievementsList {\n"
"    background-color: #171c25;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"}\n"
"\n"
"QProgressBar {\n"
"    background-color: #2a313d;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    text-align: center;\n"
"    color: white;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background-color: #e53935;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QLabel#detailsHeaderLabel {\n"
"    font-size: 16pt;\n"
"    font-weight: 700;\n"
"}\n"
"\n"
"QLabel#gameNameLabel {\n"
"    font-size: 20pt;\n"
"    font-weight: 700;\n"
"}\n"
"\n"
"QLabel#mutedLabel, QLabel#genreInfoLabel, QLabel#hoursInfoLabel,\n"
"QLabel#totalAchievementsInfoLabel, QLabel#openedAchievementsInfoLabe"
                        "l,\n"
"QLabel#platformInfoLabel {\n"
"    color: #a7b0bb;\n"
"}\n"
"\n"
"QFrame#coverFrame {\n"
"    background-color: #0f131a;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QLabel#coverLabel {\n"
"    font-size: 18pt;\n"
"    font-weight: 700;\n"
"    color: #e7d7a5;\n"
"    background-color: #0b0f14;\n"
"    border-radius: 8px;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background: #0d1117;\n"
"    width: 10px;\n"
"    margin: 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #2a313d;\n"
"    min-height: 24px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical,\n"
"QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(14);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(12, 12, 12, 12);
        sidebarFrame = new QFrame(centralwidget);
        sidebarFrame->setObjectName("sidebarFrame");
        sidebarFrame->setMinimumSize(QSize(160, 0));
        sidebarFrame->setMaximumSize(QSize(190, 16777215));
        verticalLayout_2 = new QVBoxLayout(sidebarFrame);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(12, 12, 12, 12);
        logoLabel = new QLabel(sidebarFrame);
        logoLabel->setObjectName("logoLabel");

        verticalLayout_2->addWidget(logoLabel);

        libraryButton = new QPushButton(sidebarFrame);
        libraryButton->setObjectName("libraryButton");

        verticalLayout_2->addWidget(libraryButton);

        achievementsButton = new QPushButton(sidebarFrame);
        achievementsButton->setObjectName("achievementsButton");

        verticalLayout_2->addWidget(achievementsButton);

        steamImportButton = new QPushButton(sidebarFrame);
        steamImportButton->setObjectName("steamImportButton");

        verticalLayout_2->addWidget(steamImportButton);

        settingsButton = new QPushButton(sidebarFrame);
        settingsButton->setObjectName("settingsButton");

        verticalLayout_2->addWidget(settingsButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        bottomAddGameButton = new QPushButton(sidebarFrame);
        bottomAddGameButton->setObjectName("bottomAddGameButton");

        verticalLayout_2->addWidget(bottomAddGameButton);


        horizontalLayout->addWidget(sidebarFrame);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        topBarFrame = new QFrame(centralwidget);
        topBarFrame->setObjectName("topBarFrame");
        verticalLayout_3 = new QVBoxLayout(topBarFrame);
        verticalLayout_3->setSpacing(8);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        sectionTitleLabel = new QLabel(topBarFrame);
        sectionTitleLabel->setObjectName("sectionTitleLabel");

        horizontalLayout_2->addWidget(sectionTitleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        genreComboBox = new QComboBox(topBarFrame);
        genreComboBox->addItem(QString());
        genreComboBox->setObjectName("genreComboBox");

        horizontalLayout_2->addWidget(genreComboBox);

        statusComboBox = new QComboBox(topBarFrame);
        statusComboBox->addItem(QString());
        statusComboBox->setObjectName("statusComboBox");

        horizontalLayout_2->addWidget(statusComboBox);

        platformComboBox = new QComboBox(topBarFrame);
        platformComboBox->addItem(QString());
        platformComboBox->setObjectName("platformComboBox");

        horizontalLayout_2->addWidget(platformComboBox);

        searchLineEdit = new QLineEdit(topBarFrame);
        searchLineEdit->setObjectName("searchLineEdit");

        horizontalLayout_2->addWidget(searchLineEdit);

        addGameButton = new QPushButton(topBarFrame);
        addGameButton->setObjectName("addGameButton");

        horizontalLayout_2->addWidget(addGameButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        gamesCountLabel = new QLabel(topBarFrame);
        gamesCountLabel->setObjectName("gamesCountLabel");

        verticalLayout_3->addWidget(gamesCountLabel);


        verticalLayout->addWidget(topBarFrame);

        gamesList = new QListWidget(centralwidget);
        gamesList->setObjectName("gamesList");

        verticalLayout->addWidget(gamesList);


        horizontalLayout->addLayout(verticalLayout);

        detailsFrame = new QFrame(centralwidget);
        detailsFrame->setObjectName("detailsFrame");
        detailsFrame->setMinimumSize(QSize(270, 0));
        detailsFrame->setMaximumSize(QSize(320, 16777215));
        verticalLayout_4 = new QVBoxLayout(detailsFrame);
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(12, 12, 12, 12);
        detailsHeaderLabel = new QLabel(detailsFrame);
        detailsHeaderLabel->setObjectName("detailsHeaderLabel");

        verticalLayout_4->addWidget(detailsHeaderLabel);

        coverFrame = new QFrame(detailsFrame);
        coverFrame->setObjectName("coverFrame");
        coverFrame->setMinimumSize(QSize(0, 140));
        coverFrame->setMaximumSize(QSize(16777215, 140));
        verticalLayout_5 = new QVBoxLayout(coverFrame);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        coverLabel = new QLabel(coverFrame);
        coverLabel->setObjectName("coverLabel");
        coverLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(coverLabel);


        verticalLayout_4->addWidget(coverFrame);

        gameNameLabel = new QLabel(detailsFrame);
        gameNameLabel->setObjectName("gameNameLabel");

        verticalLayout_4->addWidget(gameNameLabel);

        genreInfoLabel = new QLabel(detailsFrame);
        genreInfoLabel->setObjectName("genreInfoLabel");

        verticalLayout_4->addWidget(genreInfoLabel);

        hoursInfoLabel = new QLabel(detailsFrame);
        hoursInfoLabel->setObjectName("hoursInfoLabel");

        verticalLayout_4->addWidget(hoursInfoLabel);

        totalAchievementsInfoLabel = new QLabel(detailsFrame);
        totalAchievementsInfoLabel->setObjectName("totalAchievementsInfoLabel");

        verticalLayout_4->addWidget(totalAchievementsInfoLabel);

        openedAchievementsInfoLabel = new QLabel(detailsFrame);
        openedAchievementsInfoLabel->setObjectName("openedAchievementsInfoLabel");

        verticalLayout_4->addWidget(openedAchievementsInfoLabel);

        progressBar = new QProgressBar(detailsFrame);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(78);

        verticalLayout_4->addWidget(progressBar);

        mutedLabel = new QLabel(detailsFrame);
        mutedLabel->setObjectName("mutedLabel");

        verticalLayout_4->addWidget(mutedLabel);

        recentAchievementsList = new QListWidget(detailsFrame);
        recentAchievementsList->setObjectName("recentAchievementsList");

        verticalLayout_4->addWidget(recentAchievementsList);

        platformInfoLabel = new QLabel(detailsFrame);
        platformInfoLabel->setObjectName("platformInfoLabel");

        verticalLayout_4->addWidget(platformInfoLabel);

        viewAchievementsButton = new QPushButton(detailsFrame);
        viewAchievementsButton->setObjectName("viewAchievementsButton");

        verticalLayout_4->addWidget(viewAchievementsButton);


        horizontalLayout->addWidget(detailsFrame);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1220, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "GameVault", nullptr));
        logoLabel->setText(QCoreApplication::translate("MainWindow", "GameVault", nullptr));
        libraryButton->setText(QCoreApplication::translate("MainWindow", "\320\221\321\226\320\261\320\273\321\226\320\276\321\202\320\265\320\272\320\260", nullptr));
        achievementsButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\321\201\321\217\320\263\320\275\320\265\320\275\320\275\321\217", nullptr));
        steamImportButton->setText(QCoreApplication::translate("MainWindow", "Steam Import", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\273\320\260\321\210\321\202\321\203\320\262\320\260\320\275\320\275\321\217", nullptr));
        bottomAddGameButton->setText(QCoreApplication::translate("MainWindow", "+ \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\320\263\321\200\321\203", nullptr));
        sectionTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\321\217 \321\226\320\263\321\200\320\276\320\262\320\260 \320\261\321\226\320\261\320\273\321\226\320\276\321\202\320\265\320\272\320\260", nullptr));
        genreComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\226\320\260\320\275\321\200", nullptr));

        statusComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));

        platformComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\237\320\273\320\260\321\202\321\204\320\276\321\200\320\274\320\260", nullptr));

        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\270\320\263\321\200\321\213...", nullptr));
        addGameButton->setText(QCoreApplication::translate("MainWindow", "+ \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        gamesCountLabel->setText(QCoreApplication::translate("MainWindow", "0 \320\270\320\263\321\200", nullptr));
        detailsHeaderLabel->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\321\202\320\260\320\273\321\226 \320\263\321\200\320\270", nullptr));
        coverLabel->setText(QCoreApplication::translate("MainWindow", "ELDEN RING", nullptr));
        gameNameLabel->setText(QCoreApplication::translate("MainWindow", "Elden Ring", nullptr));
        genreInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\226\320\260\320\275\321\200: RPG", nullptr));
        hoursInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\230\320\263\321\200\320\276\320\262\321\213\320\265 \321\207\320\260\321\201\321\213: 145 hours", nullptr));
        totalAchievementsInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\320\265\320\263\320\276 \320\264\320\276\321\201\321\202\320\270\320\266\320\265\320\275\320\270\320\271: 50", nullptr));
        openedAchievementsInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\320\276: 39", nullptr));
        mutedLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\320\273\320\265\320\264\320\275\320\270\320\265 \320\264\320\276\321\201\321\202\320\270\320\266\320\265\320\275\320\270\321\217", nullptr));
        platformInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\260\321\202\321\204\320\276\321\200\320\274\320\260: Steam", nullptr));
        viewAchievementsButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\320\274\320\276\321\202\321\200\320\265\321\202\321\214 \320\264\320\276\321\201\321\202\320\270\320\266\320\265\320\275\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
