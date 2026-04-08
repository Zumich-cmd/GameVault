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
    QFrame *libraryColumnsFrame;
    QHBoxLayout *libraryColumnsLayout;
    QLabel *sortGlyphLabel;
    QSpacerItem *columnsSpacer0;
    QLabel *columnsNameLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *columnsGenreLabel;
    QLabel *columnsHoursLabel;
    QSpacerItem *columnsSpacer1;
    QPushButton *libraryAddButton;
    QListWidget *gamesList;
    QFrame *settingsFrame;
    QVBoxLayout *settingsLayout;
    QLabel *settingsTitleLabel;
    QLabel *themeLabel;
    QHBoxLayout *themeButtonsLayout;
    QPushButton *themeDarkButton;
    QPushButton *themeLightButton;
    QLabel *languageLabel;
    QHBoxLayout *languageButtonsLayout;
    QPushButton *langUkButton;
    QPushButton *langEnButton;
    QSpacerItem *settingsSpacer;
    QFrame *detailsFrame;
    QVBoxLayout *detailsLayout;
    QLabel *detailsHeaderLabel;
    QFrame *coverFrame;
    QVBoxLayout *coverLayout;
    QLabel *coverLabel;
    QLabel *gameNameLabel;
    QLabel *genreInfoLabel;
    QLabel *hoursInfoLabel;
    QLabel *totalAchievementsInfoLabel;
    QLabel *openedAchievementsInfoLabel;
    QHBoxLayout *progressRowLayout;
    QProgressBar *progressBar;
    QLabel *progressInfoLabel;
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
"    background-color: #0b0f14;\n"
"    color: #e6e6e6;\n"
"}\n"
"\n"
"/* \320\221\320\260\320\267\320\276\320\262\321\213\320\271 \321\202\320\265\320\272\321\201\321\202 */\n"
"QLabel {\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"/* ===== SIDEBAR ===== */\n"
"#sidebarFrame {\n"
"    background-color: #11161d;\n"
"    border-radius: 14px;\n"
"}\n"
"\n"
"#sidebarFrame QPushButton {\n"
"    background: transparent;\n"
"    border: none;\n"
"    text-align: left;\n"
"    padding: 10px 12px;\n"
"    border-radius: 10px;\n"
"    color: #c9d1d9;\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"#sidebarFrame QPushButton:hover {\n"
"    background-color: #252d39;\n"
"}\n"
"\n"
"#sidebarFrame QPushButton:pressed {\n"
"    background-color: #1b222d;\n"
"}\n"
"\n"
"#sidebarFrame QPushButton:checked {\n"
"    background-color: #d32f2f;\n"
"    color: white;\n"
"}\n"
"\n"
"/* \320\235\320\270\320\266\320\275\321\217\321\217 \320\272\320\275\320\276\320\277\320\272\320\260 */\n"
""
                        "#sidebarFrame QPushButton#bottomAddGameButton {\n"
"    background-color: #942B2B;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"}\n"
"\n"
"#sidebarFrame QPushButton#bottomAddGameButton:hover {\n"
"    background-color: #b33636;\n"
"}\n"
"\n"
"#sidebarFrame QPushButton#bottomAddGameButton:pressed {\n"
"    background-color: #7a2323;\n"
"}\n"
"\n"
"/* ===== HEADER / FILTERS ===== */\n"
"QLineEdit, QComboBox {\n"
"    background-color: #141a22;\n"
"    border: 1px solid #2c3440;\n"
"    border-radius: 10px;\n"
"    padding: 6px;\n"
"    color: #e6e6e6;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 18px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: none;\n"
"    border: none;\n"
"}\n"
"\n"
"/* ===== BUTTONS ===== */\n"
"QPushButton {\n"
"    background-color: #1c222b;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    padding: 6px 12px;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-colo"
                        "r: #323b49;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #262d38;\n"
"}\n"
"\n"
"QPushButton#addGameButton {\n"
"    background-color: #d32f2f;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton#addGameButton:hover {\n"
"    background-color: #ff3d3d;\n"
"}\n"
"\n"
"QPushButton#viewAchievementsButton {\n"
"    background-color: #9f2727;\n"
"    border-radius: 10px;\n"
"    padding: 10px 14px;\n"
"    font-size: 11pt;\n"
"    font-weight: 800;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#viewAchievementsButton:hover {\n"
"    background-color: #c13333;\n"
"}\n"
"\n"
"QPushButton#viewAchievementsButton:pressed {\n"
"    background-color: #7e1f1f;\n"
"}\n"
"\n"
"/* ===== LISTS ===== */\n"
"QListWidget {\n"
"    border: none;\n"
"    background: transparent;\n"
"    outline: none;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    background-color: #141a22;\n"
"    border: 1px solid transparent;\n"
"    border-radius: 12px;\n"
"    padding: 10px 16px;\n"
"    margin: 6px 0px;"
                        "\n"
"    color: #e6e6e6;\n"
"    font-family: \"Consolas\";\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-color: #141a22;\n"
"    border: 2px solid #ff3d3d;\n"
"    outline: none;\n"
"}\n"
"\n"
"QListWidget::item:hover {\n"
"    background-color: #171f29;\n"
"}\n"
"\n"
"/* \320\241\320\277\320\270\321\201\320\276\320\272 \320\276\321\201\321\202\320\260\320\275\320\275\321\226\321\205 \320\264\320\276\321\201\321\217\320\263\320\275\320\265\320\275\321\214 */\n"
"QListWidget#recentAchievementsList {\n"
"    background: transparent;\n"
"    border: none;\n"
"    padding-right: 12px;\n"
"    outline: none;\n"
"}\n"
"\n"
"QListWidget#recentAchievementsList::item {\n"
"    background: transparent;\n"
"    border: none;\n"
"    border-radius: 0px;\n"
"    padding: 0px;\n"
"    margin: 0px 0px 2px 0px;\n"
"    color: #e6e6e6;\n"
"    font-family: \"Segoe UI\";\n"
"}\n"
"\n"
"QListWidget#recentAchievementsList::item:selected {\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"QLis"
                        "tWidget#recentAchievementsList QScrollBar:vertical {\n"
"    background: #0f141c;\n"
"    width: 6px;\n"
"    margin: 6px 2px 6px 0px;\n"
"    border-radius: 3px;\n"
"}\n"
"\n"
"QListWidget#recentAchievementsList QScrollBar::handle:vertical {\n"
"    background: #344053;\n"
"    border-radius: 3px;\n"
"    min-height: 28px;\n"
"}\n"
"\n"
"QListWidget#recentAchievementsList QScrollBar::handle:vertical:hover {\n"
"    background: #46556b;\n"
"}\n"
"\n"
"QListWidget#recentAchievementsList QScrollBar::handle:vertical:pressed {\n"
"    background: #ff3d3d;\n"
"}\n"
"\n"
"QListWidget#recentAchievementsList QScrollBar::add-line:vertical,\n"
"QListWidget#recentAchievementsList QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"QListWidget#recentAchievementsList QScrollBar::add-page:vertical,\n"
"QListWidget#recentAchievementsList QScrollBar::sub-page:vertical {\n"
"    background: transparent;\n"
"}\n"
"\n"
"/* ===== DETAILS PANEL ===== */\n"
"#detailsFrame {\n"
"    background-color: #11161d;\n"
"   "
                        " border-radius: 14px;\n"
"}\n"
"\n"
"#detailsFrame QLabel {\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"#coverFrame {\n"
"    background: transparent;\n"
"}\n"
"\n"
"#coverLabel {\n"
"    background-color: #0a0f14;\n"
"    border-radius: 12px;\n"
"    padding: 0px;\n"
"    font-size: 18pt;\n"
"    font-weight: bold;\n"
"    color: #d7c58a;\n"
"}\n"
"\n"
"#gameNameLabel {\n"
"    font-size: 18pt;\n"
"    font-weight: bold;\n"
"    color: white;\n"
"}\n"
"\n"
"#genreInfoLabel {\n"
"    color: #7f8b9a;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"#hoursInfoLabel,\n"
"#totalAchievementsInfoLabel,\n"
"#openedAchievementsInfoLabel {\n"
"    color: #f2f4f8;\n"
"    font-size: 12px;\n"
"    font-weight: 700;\n"
"}\n"
"\n"
"#mutedLabel {\n"
"    color: #ffffff;\n"
"    font-size: 14px;\n"
"    font-weight: 800;\n"
"}\n"
"\n"
"#platformInfoLabel {\n"
"    color: #9aa4b2;\n"
"    font-size: 12px;\n"
"    font-weight: 700;\n"
"}\n"
"\n"
"/* ===== PROGRESS ===== */\n"
"QProgre"
                        "ssBar {\n"
"    background-color: #2a313d;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    text-align: center;\n"
"    color: white;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"    background-color: #ff3d3d;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"/* ===== SCROLLBAR ===== */\n"
"QScrollBar:vertical {\n"
"    background: transparent;\n"
"    width: 6px;\n"
"    margin: 8px 2px 8px 0px;\n"
"    border-radius: 3px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #2a313d;\n"
"    border-radius: 3px;\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #3a4352;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:pressed {\n"
"    background: #ff3d3d;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical,\n"
"QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical,\n"
"QScrollBar::sub-page:vertical {\n"
"    background: transparent;\n"
"}\n"
"\n"
"QListWidget#gamesList QScrollBar:vertical {\n"
"    background: #0f141c;\n"
""
                        "    width: 8px;\n"
"    margin: 6px 2px 6px 0px;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QListWidget#gamesList QScrollBar::handle:vertical {\n"
"    background: #3a4352;\n"
"    border-radius: 4px;\n"
"    min-height: 40px;\n"
"}\n"
"\n"
"QListWidget#gamesList QScrollBar::handle:vertical:hover {\n"
"    background: #4a5668;\n"
"}\n"
"\n"
"QListWidget#gamesList QScrollBar::handle:vertical:pressed {\n"
"    background: #ff3d3d;\n"
"}\n"
"\n"
"QListWidget#gamesList QScrollBar::add-line:vertical,\n"
"QListWidget#gamesList QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"QListWidget#gamesList QScrollBar::add-page:vertical,\n"
"QListWidget#gamesList QScrollBar::sub-page:vertical {\n"
"    background: transparent;\n"
"}\n"
"\n"
"QListWidget#gamesList QScrollBar:horizontal {\n"
"    height: 0px;\n"
"}\n"
"\n"
"QListWidget#gamesList::item:selected {\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"QListWidget#gamesList::item {\n"
"    padding: 0px;\n"
"    margin: 6px 0px;\n"
""
                        "    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"QListWidget#gamesList::item:hover {\n"
"    background: transparent;\n"
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
        sidebarFrame->setMaximumSize(QSize(318, 16777215));
        verticalLayout_2 = new QVBoxLayout(sidebarFrame);
        verticalLayout_2->setSpacing(8);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(12, 12, 12, 12);
        logoLabel = new QLabel(sidebarFrame);
        logoLabel->setObjectName("logoLabel");
        QFont font;
        font.setFamilies({QString::fromUtf8("Jura")});
        font.setPointSize(18);
        font.setBold(false);
        logoLabel->setFont(font);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(logoLabel);

        libraryButton = new QPushButton(sidebarFrame);
        libraryButton->setObjectName("libraryButton");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(10);
        font1.setBold(true);
        libraryButton->setFont(font1);
        libraryButton->setCheckable(true);
        libraryButton->setChecked(true);
        libraryButton->setFlat(true);

        verticalLayout_2->addWidget(libraryButton);

        achievementsButton = new QPushButton(sidebarFrame);
        achievementsButton->setObjectName("achievementsButton");
        achievementsButton->setFont(font1);
        achievementsButton->setFlat(true);

        verticalLayout_2->addWidget(achievementsButton);

        steamImportButton = new QPushButton(sidebarFrame);
        steamImportButton->setObjectName("steamImportButton");
        steamImportButton->setFont(font1);
        steamImportButton->setFlat(true);

        verticalLayout_2->addWidget(steamImportButton);

        settingsButton = new QPushButton(sidebarFrame);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setMinimumSize(QSize(33, 0));
        settingsButton->setMaximumSize(QSize(16777215, 16777215));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(10);
        font2.setBold(false);
        settingsButton->setFont(font2);
        settingsButton->setFlat(true);

        verticalLayout_2->addWidget(settingsButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        bottomAddGameButton = new QPushButton(sidebarFrame);
        bottomAddGameButton->setObjectName("bottomAddGameButton");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Roboto")});
        font3.setPointSize(10);
        bottomAddGameButton->setFont(font3);
        bottomAddGameButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        bottomAddGameButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        bottomAddGameButton->setAutoFillBackground(false);
        bottomAddGameButton->setStyleSheet(QString::fromUtf8(""));
        bottomAddGameButton->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        bottomAddGameButton->setAutoDefault(false);
        bottomAddGameButton->setFlat(false);

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
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI")});
        font4.setPointSize(20);
        font4.setBold(true);
        sectionTitleLabel->setFont(font4);

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
        statusComboBox->setFrame(true);

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
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Segoe UI")});
        font5.setPointSize(12);
        font5.setWeight(QFont::Light);
        gamesCountLabel->setFont(font5);
        gamesCountLabel->setStyleSheet(QString::fromUtf8("color: #9D9D9D;"));

        verticalLayout_3->addWidget(gamesCountLabel);


        verticalLayout->addWidget(topBarFrame);

        libraryColumnsFrame = new QFrame(centralwidget);
        libraryColumnsFrame->setObjectName("libraryColumnsFrame");
        libraryColumnsFrame->setStyleSheet(QString::fromUtf8("#libraryColumnsFrame {\n"
"    background-color: #141a22;\n"
"    border-radius: 10px;\n"
"    border: 1px solid #1c2532;\n"
"}\n"
"\n"
"#libraryColumnsFrame QLabel {\n"
"    color: #f1f4f9;\n"
"    font-size: 11pt;\n"
"    font-weight: 700;\n"
"}\n"
"\n"
"#libraryAddButton {\n"
"    background-color: #d32f2f;\n"
"    border-radius: 9px;\n"
"    font-weight: 700;\n"
"    color: white;\n"
"    padding: 6px 14px;\n"
"}\n"
"\n"
"#libraryAddButton:hover {\n"
"    background-color: #ff3d3d;\n"
"}\n"
"\n"
"#libraryAddButton:pressed {\n"
"    background-color: #b92a2a;\n"
"}"));
        libraryColumnsLayout = new QHBoxLayout(libraryColumnsFrame);
        libraryColumnsLayout->setSpacing(12);
        libraryColumnsLayout->setObjectName("libraryColumnsLayout");
        libraryColumnsLayout->setContentsMargins(12, 8, 12, 8);
        sortGlyphLabel = new QLabel(libraryColumnsFrame);
        sortGlyphLabel->setObjectName("sortGlyphLabel");
        sortGlyphLabel->setMinimumSize(QSize(24, 0));

        libraryColumnsLayout->addWidget(sortGlyphLabel);

        columnsSpacer0 = new QSpacerItem(99, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        libraryColumnsLayout->addItem(columnsSpacer0);

        columnsNameLabel = new QLabel(libraryColumnsFrame);
        columnsNameLabel->setObjectName("columnsNameLabel");
        columnsNameLabel->setMinimumSize(QSize(130, 0));

        libraryColumnsLayout->addWidget(columnsNameLabel);

        horizontalSpacer_2 = new QSpacerItem(85, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        libraryColumnsLayout->addItem(horizontalSpacer_2);

        columnsGenreLabel = new QLabel(libraryColumnsFrame);
        columnsGenreLabel->setObjectName("columnsGenreLabel");
        columnsGenreLabel->setMinimumSize(QSize(92, 0));

        libraryColumnsLayout->addWidget(columnsGenreLabel);

        columnsHoursLabel = new QLabel(libraryColumnsFrame);
        columnsHoursLabel->setObjectName("columnsHoursLabel");
        columnsHoursLabel->setMinimumSize(QSize(124, 0));

        libraryColumnsLayout->addWidget(columnsHoursLabel);

        columnsSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        libraryColumnsLayout->addItem(columnsSpacer1);

        libraryAddButton = new QPushButton(libraryColumnsFrame);
        libraryAddButton->setObjectName("libraryAddButton");
        libraryAddButton->setMinimumSize(QSize(150, 34));

        libraryColumnsLayout->addWidget(libraryAddButton);


        verticalLayout->addWidget(libraryColumnsFrame);

        gamesList = new QListWidget(centralwidget);
        gamesList->setObjectName("gamesList");
        gamesList->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        gamesList->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        gamesList->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        verticalLayout->addWidget(gamesList);

        settingsFrame = new QFrame(centralwidget);
        settingsFrame->setObjectName("settingsFrame");
        settingsFrame->setVisible(false);
        settingsFrame->setStyleSheet(QString::fromUtf8("#settingsFrame {\n"
"    background-color: #11161d;\n"
"    border-radius: 14px;\n"
"}\n"
"\n"
"#settingsFrame QLabel#settingsTitleLabel {\n"
"    font-size: 18pt;\n"
"    font-weight: 800;\n"
"    color: white;\n"
"}\n"
"\n"
"#settingsFrame QLabel.sectionLabel {\n"
"    color: #9aa4b2;\n"
"    font-size: 11pt;\n"
"    font-weight: 700;\n"
"}\n"
"\n"
"#settingsFrame QPushButton.optionButton {\n"
"    background-color: #141a22;\n"
"    border: 1px solid #2c3440;\n"
"    border-radius: 10px;\n"
"    padding: 10px 12px;\n"
"    text-align: left;\n"
"    font-weight: 700;\n"
"}\n"
"\n"
"#settingsFrame QPushButton.optionButton:checked {\n"
"    border: 1px solid #d32f2f;\n"
"}"));
        settingsLayout = new QVBoxLayout(settingsFrame);
        settingsLayout->setSpacing(10);
        settingsLayout->setObjectName("settingsLayout");
        settingsLayout->setContentsMargins(14, 14, 14, 14);
        settingsTitleLabel = new QLabel(settingsFrame);
        settingsTitleLabel->setObjectName("settingsTitleLabel");

        settingsLayout->addWidget(settingsTitleLabel);

        themeLabel = new QLabel(settingsFrame);
        themeLabel->setObjectName("themeLabel");

        settingsLayout->addWidget(themeLabel);

        themeButtonsLayout = new QHBoxLayout();
        themeButtonsLayout->setSpacing(10);
        themeButtonsLayout->setObjectName("themeButtonsLayout");
        themeDarkButton = new QPushButton(settingsFrame);
        themeDarkButton->setObjectName("themeDarkButton");
        themeDarkButton->setCheckable(true);
        themeDarkButton->setChecked(true);

        themeButtonsLayout->addWidget(themeDarkButton);

        themeLightButton = new QPushButton(settingsFrame);
        themeLightButton->setObjectName("themeLightButton");
        themeLightButton->setCheckable(true);

        themeButtonsLayout->addWidget(themeLightButton);


        settingsLayout->addLayout(themeButtonsLayout);

        languageLabel = new QLabel(settingsFrame);
        languageLabel->setObjectName("languageLabel");

        settingsLayout->addWidget(languageLabel);

        languageButtonsLayout = new QHBoxLayout();
        languageButtonsLayout->setSpacing(10);
        languageButtonsLayout->setObjectName("languageButtonsLayout");
        langUkButton = new QPushButton(settingsFrame);
        langUkButton->setObjectName("langUkButton");
        langUkButton->setCheckable(true);
        langUkButton->setChecked(true);

        languageButtonsLayout->addWidget(langUkButton);

        langEnButton = new QPushButton(settingsFrame);
        langEnButton->setObjectName("langEnButton");
        langEnButton->setCheckable(true);

        languageButtonsLayout->addWidget(langEnButton);


        settingsLayout->addLayout(languageButtonsLayout);

        settingsSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        settingsLayout->addItem(settingsSpacer);


        verticalLayout->addWidget(settingsFrame);


        horizontalLayout->addLayout(verticalLayout);

        detailsFrame = new QFrame(centralwidget);
        detailsFrame->setObjectName("detailsFrame");
        detailsFrame->setMinimumSize(QSize(270, 0));
        detailsFrame->setMaximumSize(QSize(320, 16777215));
        detailsLayout = new QVBoxLayout(detailsFrame);
        detailsLayout->setSpacing(10);
        detailsLayout->setObjectName("detailsLayout");
        detailsLayout->setContentsMargins(12, 12, 12, 12);
        detailsHeaderLabel = new QLabel(detailsFrame);
        detailsHeaderLabel->setObjectName("detailsHeaderLabel");
        QFont font6;
        font6.setPointSize(16);
        font6.setBold(true);
        detailsHeaderLabel->setFont(font6);

        detailsLayout->addWidget(detailsHeaderLabel);

        coverFrame = new QFrame(detailsFrame);
        coverFrame->setObjectName("coverFrame");
        coverFrame->setMinimumSize(QSize(0, 140));
        coverFrame->setMaximumSize(QSize(16777215, 140));
        coverLayout = new QVBoxLayout(coverFrame);
        coverLayout->setObjectName("coverLayout");
        coverLayout->setContentsMargins(0, 0, 0, 0);
        coverLabel = new QLabel(coverFrame);
        coverLabel->setObjectName("coverLabel");
        coverLabel->setMinimumSize(QSize(240, 120));
        coverLabel->setMaximumSize(QSize(240, 120));
        coverLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        coverLayout->addWidget(coverLabel);


        detailsLayout->addWidget(coverFrame);

        gameNameLabel = new QLabel(detailsFrame);
        gameNameLabel->setObjectName("gameNameLabel");
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Roboto")});
        font7.setPointSize(18);
        font7.setBold(true);
        gameNameLabel->setFont(font7);

        detailsLayout->addWidget(gameNameLabel);

        genreInfoLabel = new QLabel(detailsFrame);
        genreInfoLabel->setObjectName("genreInfoLabel");
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Roboto")});
        font8.setWeight(QFont::DemiBold);
        genreInfoLabel->setFont(font8);

        detailsLayout->addWidget(genreInfoLabel);

        hoursInfoLabel = new QLabel(detailsFrame);
        hoursInfoLabel->setObjectName("hoursInfoLabel");
        QFont font9;
        font9.setFamilies({QString::fromUtf8("Roboto")});
        font9.setBold(true);
        hoursInfoLabel->setFont(font9);

        detailsLayout->addWidget(hoursInfoLabel);

        totalAchievementsInfoLabel = new QLabel(detailsFrame);
        totalAchievementsInfoLabel->setObjectName("totalAchievementsInfoLabel");
        totalAchievementsInfoLabel->setFont(font9);

        detailsLayout->addWidget(totalAchievementsInfoLabel);

        openedAchievementsInfoLabel = new QLabel(detailsFrame);
        openedAchievementsInfoLabel->setObjectName("openedAchievementsInfoLabel");
        openedAchievementsInfoLabel->setFont(font9);

        detailsLayout->addWidget(openedAchievementsInfoLabel);

        progressRowLayout = new QHBoxLayout();
        progressRowLayout->setObjectName("progressRowLayout");
        progressBar = new QProgressBar(detailsFrame);
        progressBar->setObjectName("progressBar");
        progressBar->setTextVisible(false);

        progressRowLayout->addWidget(progressBar);

        progressInfoLabel = new QLabel(detailsFrame);
        progressInfoLabel->setObjectName("progressInfoLabel");
        QFont font10;
        font10.setFamilies({QString::fromUtf8("Roboto")});
        progressInfoLabel->setFont(font10);

        progressRowLayout->addWidget(progressInfoLabel);


        detailsLayout->addLayout(progressRowLayout);

        mutedLabel = new QLabel(detailsFrame);
        mutedLabel->setObjectName("mutedLabel");
        QFont font11;
        font11.setFamilies({QString::fromUtf8("Roboto")});
        font11.setWeight(QFont::ExtraBold);
        mutedLabel->setFont(font11);

        detailsLayout->addWidget(mutedLabel);

        recentAchievementsList = new QListWidget(detailsFrame);
        recentAchievementsList->setObjectName("recentAchievementsList");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(recentAchievementsList->sizePolicy().hasHeightForWidth());
        recentAchievementsList->setSizePolicy(sizePolicy);
        recentAchievementsList->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        recentAchievementsList->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        detailsLayout->addWidget(recentAchievementsList);

        platformInfoLabel = new QLabel(detailsFrame);
        platformInfoLabel->setObjectName("platformInfoLabel");

        detailsLayout->addWidget(platformInfoLabel);

        viewAchievementsButton = new QPushButton(detailsFrame);
        viewAchievementsButton->setObjectName("viewAchievementsButton");
        viewAchievementsButton->setMinimumSize(QSize(0, 42));
        QFont font12;
        font12.setFamilies({QString::fromUtf8("Roboto")});
        font12.setPointSize(11);
        font12.setWeight(QFont::ExtraBold);
        viewAchievementsButton->setFont(font12);

        detailsLayout->addWidget(viewAchievementsButton);


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
        libraryButton->setText(QCoreApplication::translate("MainWindow", "\342\226\243 \320\221\321\226\320\261\320\273\321\226\320\276\321\202\320\265\320\272\320\260", nullptr));
        achievementsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\217\205 \320\224\320\276\321\201\321\217\320\263\320\275\320\265\320\275\320\275\321\217", nullptr));
        steamImportButton->setText(QCoreApplication::translate("MainWindow", "\342\230\201 Steam Import", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "\342\232\231 \320\235\320\260\320\273\320\260\321\210\321\202\321\203\320\262\320\260\320\275\320\275\321\217", nullptr));
        bottomAddGameButton->setText(QCoreApplication::translate("MainWindow", "+ \320\224\320\276\320\264\320\260\321\202\320\270 \320\263\321\200\321\203", nullptr));
        sectionTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\321\217 \321\226\320\263\321\200\320\276\320\262\320\260 \320\261\321\226\320\261\320\273\321\226\320\276\321\202\320\265\320\272\320\260", nullptr));
        genreComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\226\320\260\320\275\321\200", nullptr));

        statusComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));

        platformComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\237\320\273\320\260\321\202\321\204\320\276\321\200\320\274\320\260", nullptr));

        searchLineEdit->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\210\321\203\320\272...", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\270\320\263\321\200\321\213...", nullptr));
        addGameButton->setText(QCoreApplication::translate("MainWindow", "+ \320\224\320\276\320\264\320\260\321\202\320\270", nullptr));
        gamesCountLabel->setText(QCoreApplication::translate("MainWindow", "0 \320\270\320\263\321\200", nullptr));
        sortGlyphLabel->setText(QCoreApplication::translate("MainWindow", "\342\230\267", nullptr));
        columnsNameLabel->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260", nullptr));
        columnsGenreLabel->setText(QCoreApplication::translate("MainWindow", "\320\226\320\260\320\275\321\200", nullptr));
        columnsHoursLabel->setText(QCoreApplication::translate("MainWindow", "\320\206\320\263\321\200\320\276\320\262\321\226 \320\263\320\276\320\264\320\270\320\275\320\270", nullptr));
        libraryAddButton->setText(QCoreApplication::translate("MainWindow", "+ \320\224\320\276\320\264\320\260\321\202\320\270 \320\263\321\200\321\203", nullptr));
        settingsTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\273\320\260\321\210\321\202\321\203\320\262\320\260\320\275\320\275\321\217", nullptr));
        themeLabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\274\320\260", nullptr));
        themeLabel->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "sectionLabel", nullptr)));
        themeDarkButton->setText(QCoreApplication::translate("MainWindow", "Dark", nullptr));
        themeDarkButton->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "optionButton", nullptr)));
        themeLightButton->setText(QCoreApplication::translate("MainWindow", "Light", nullptr));
        themeLightButton->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "optionButton", nullptr)));
        languageLabel->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\320\262\320\260", nullptr));
        languageLabel->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "sectionLabel", nullptr)));
        langUkButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\272\321\200\320\260\321\227\320\275\321\201\321\214\320\272\320\260", nullptr));
        langUkButton->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "optionButton", nullptr)));
        langEnButton->setText(QCoreApplication::translate("MainWindow", "English", nullptr));
        langEnButton->setProperty("property", QVariant(QCoreApplication::translate("MainWindow", "optionButton", nullptr)));
        detailsHeaderLabel->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\321\202\320\260\320\273\321\226 \320\263\321\200\320\270", nullptr));
        coverLabel->setText(QCoreApplication::translate("MainWindow", "ELDEN RING", nullptr));
        gameNameLabel->setText(QCoreApplication::translate("MainWindow", "Elden Ring", nullptr));
        genreInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\226\320\260\320\275\321\200: RPG", nullptr));
        hoursInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\206\320\263\321\200\320\276\320\262\321\226 \320\263\320\276\320\264\320\270\320\275\320\270: 145 hours", nullptr));
        totalAchievementsInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\321\214\320\276\320\263\320\276 \320\264\320\276\321\201\321\217\320\263\320\275\320\265\320\275\321\214: 50", nullptr));
        openedAchievementsInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\222\321\226\320\264\320\272\321\200\320\270\321\202\320\276: 39  (85% Complete)", nullptr));
        progressInfoLabel->setText(QCoreApplication::translate("MainWindow", "(39/50)", nullptr));
        mutedLabel->setText(QCoreApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\320\275\320\275\321\226 \320\264\320\276\321\201\321\217\320\263\320\275\320\265\320\275\320\275\321\217", nullptr));
        platformInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\260\321\202\321\204\320\276\321\200\320\274\320\260: Steam", nullptr));
        viewAchievementsButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\270\320\262\320\270\321\202\320\270\321\201\321\214 \320\264\320\276\321\201\321\217\320\263\320\275\320\265\320\275\320\275\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
