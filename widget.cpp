#include "widget.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPalette>
#include <QColor>
#include <QGroupBox>
#include <QScrollBar>
#include <QDate>
#include <QProgressBar>
#include <QSlider>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QListWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QFrame>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QPainter>
#include <QMouseEvent>
#include <QSettings>
#include <QCloseEvent>
#include <QPainterPath>
#include <QBuffer>
#include <QTime>
#include <QTimer>
#include <QInputDialog>

CatUI::CatUI(QWidget *parent)
    : QWidget(parent)
    , avatarLabel(nullptr)
    , changeAvatarBtn(nullptr)
    , usernameLabel(nullptr)
    , usernameEdit(nullptr)
    , editUsernameBtn(nullptr)
    , cycleLabel(nullptr)
    , totalLabel(nullptr)
    , cycleUpBtn(nullptr)
    , cycleDownBtn(nullptr)
    , totalUpBtn(nullptr)
    , totalDownBtn(nullptr)
    , currentCycle(0)
    , totalCycles(1332)
    , settings(nullptr)
{
    setWindowTitle("滑动界面 - 深色主题");
    resize(800, 600);
    setMinimumSize(750, 450);

    setupDarkTheme();

    // 初始化设置
    settings = new QSettings("MyCompany", "AAcat_UI", this);
    loadSettings();  // 加载保存的设置

    setStyleSheet(R"(
        QWidget {
            background-color: #1e1e1e;
            font-family: "Microsoft YaHei";
        }
        QLabel {
            color: #e0e0e0;
        }
        QLineEdit {
            background-color: #2d2d2d;
            color: #e0e0e0;
            border: 1px solid #ffaa66;
            border-radius: 3px;
            padding: 5px;
            font-size: 14px;
        }
        QLineEdit:focus {
            border: 2px solid #ffaa66;
        }
        QPushButton {
            background-color: #3a3a3a;
            color: #e0e0e0;
            border: 1px solid #555555;
            border-radius: 5px;
            padding: 5px 10px;
            font-size: 12px;
            font-weight: bold;
            min-width: 60px;
            margin: 2px;
        }
        QPushButton:hover {
            background-color: #4a4a4a;
            border: 1px solid #777777;
        }
        QPushButton:pressed {
            background-color: #2a2a2a;
        }
        QPushButton#leftPanelButton {
            background-color: #2c3e50;
            border: 1px solid #34495e;
            color: #ecf0f1;
            font-size: 14px;
            padding: 8px 15px;
        }
        QPushButton#leftPanelButton:hover {
            background-color: #34495e;
            border: 1px solid #3d566e;
        }
        QPushButton#leftPanelButton:pressed {
            background-color: #1e2b37;
        }
        QPushButton#leftSideButton {
            background-color: #ff8c42;
            color: #ffffff;
            border: 2px solid #ffaa66;
            border-radius: 6px;
            padding: 8px 12px;
            font-size: 13px;
            font-weight: bold;
            min-width: 100px;
            text-align: left;
            margin: 3px 0;
        }
        QPushButton#leftSideButton:hover {
            background-color: #ff6b1a;
            border: 2px solid #ffcc88;
        }
        QPushButton#leftSideButton:pressed {
            background-color: #e05a00;
            border: 2px solid #ffaa66;
        }
        QPushButton#changeAvatarBtn {
            background-color: #1e1e1e;
            color: white;
            border: none;
            border-radius: 5px;
            padding: 5px 10px;
            font-size: 12px;
            min-width: 80px;
            margin-top: 5px;
        }
        QPushButton#changeAvatarBtn:hover {
            background-color: #ffaa66;
        }
        QPushButton#editUsernameBtn {
            background-color: transparent;
            color: #ffaa66;
            border: 1px solid #ffaa66;
            border-radius: 3px;
            padding: 2px 5px;
            font-size: 10px;
            min-width: 10px;
        }
        QPushButton#editUsernameBtn:hover {
            background-color: #ffaa66;
            color: #1e1e1e;
        }
        QPushButton#cycleBtn {
            background-color: #2d2d2d;
            color: #ffaa66;
            border: 1px solid #ffaa66;
            border-radius: 3px;
            padding: 2px 8px;
            font-size: 12px;
            min-width: 12px;
        }
        QPushButton#cycleBtn:hover {
            background-color: #ffaa66;
            color: #1e1e1e;
        }
        QTextEdit {
            border: 1px solid #444444;
            border-radius: 5px;
            background-color: #2d2d2d;
            color: #e0e0e0;
            font-size: 14px;
            selection-background-color: #404040;
        }
        QCalendarWidget {
            background-color: #2d2d2d;
            color: #e0e0e0;
            border: 1px solid #444444;
            border-radius: 5px;
        }
        #avatarLabel {
            background-color: #3a3a3a;
            border: 3px solid #ffaa66;
            border-radius: 45px;
            min-width: 90px;
            min-height: 90px;
            max-width: 90px;
            max-height: 90px;
        }
        #avatarLabel:hover {
            border: 3px solid #ff9933;
            cursor: pointer;
        }
        #infoBox {
            background-color: #2d2d2d;
            border: 1px solid #444444;
            border-radius: 10px;
            padding: 10px;
            margin: 10px;
        }
        .cycle-box {
            background-color: #2d2d2d;
            border: 1px solid #ffaa66;
            border-radius: 5px;
            padding: 10px;
            margin: 5px 0;
        }
        .cycle-label {
            font-size: 14px;
            color: #ffaa66;
            font-weight: bold;
        }
        .cycle-value {
            font-size: 24px;
            color: #ffffff;
            font-weight: bold;
        }
        .total-value {
            font-size: 18px;
            color: #888888;
        }
        QScrollArea {
            border: none;
            background-color: #1e1e1e;
        }
        QScrollBar:vertical {
            background-color: #2d2d2d;
            width: 12px;
            border-radius: 6px;
        }
        QScrollBar::handle:vertical {
            background-color: #555555;
            border-radius: 6px;
            min-height: 20px;
        }
        .title-label {
            font-size: 16px;
            font-weight: bold;
            color: #ffaa66;
            margin-bottom: 10px;
        }
        QPushButton#sendBtn {
                background-color: #4a90e2;
                color: white;
                border: none;
                border-radius: 3px;
                padding: 5px 10px;
                font-size: 12px;
                min-width: 60px;
            }
            QPushButton#sendBtn:hover {
                background-color: #357abd;
            }
            QPushButton#sendBtn:pressed {
                background-color: #2a5f8a;
            }

            QPushButton#clearChatBtn {
                background-color: #e25a4a;
                color: white;
                border: none;
                border-radius: 3px;
                padding: 5px 10px;
                font-size: 12px;
                min-width: 60px;
            }
            QPushButton#clearChatBtn:hover {
                background-color: #bd4a3a;
            }
            QPushButton#clearChatBtn:pressed {
                background-color: #8a3a2a;
            }

            QLineEdit#chatInput {
                background-color: #2d2d2d;
                color: #e0e0e0;
                border: 1px solid #444444;
                border-radius: 3px;
                padding: 5px 10px;
                font-size: 13px;
            }
            QLineEdit#chatInput:focus {
                border: 2px solid #4a90e2;
            }
    )");

    // -------------------- 左侧固定面板 --------------------
    QWidget *leftPanel = new QWidget(this);
    leftPanel->setObjectName("infoBox");
    leftPanel->setFixedWidth(220);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setAlignment(Qt::AlignTop);
    leftLayout->setSpacing(10);

    // 头像（可点击更换）
    avatarLabel = new QLabel(leftPanel);
    avatarLabel->setObjectName("avatarLabel");
    avatarLabel->setAlignment(Qt::AlignCenter);
    if (settings->value("avatar").isNull()) {
        avatarLabel->setText("🐱");
        avatarLabel->setStyleSheet("font-size: 40px; background-color: #3a3a3a; color: #ffaa66;");
    }
    avatarLabel->setToolTip("点击更换头像");
    avatarLabel->setCursor(Qt::PointingHandCursor);
    avatarLabel->installEventFilter(this);

    // 更换头像按钮
    changeAvatarBtn = new QPushButton("更换头像", leftPanel);
    changeAvatarBtn->setObjectName("changeAvatarBtn");
    changeAvatarBtn->setCursor(Qt::PointingHandCursor);
    connect(changeAvatarBtn, &QPushButton::clicked, this, &CatUI::onAvatarClicked);

    // 用户名区域
    QHBoxLayout *usernameLayout = new QHBoxLayout();
    usernameLabel = new QLabel(settings->value("username", "用户 1").toString(), leftPanel);
    usernameLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #ffaa66;");
    usernameLabel->setCursor(Qt::PointingHandCursor);
    usernameLabel->installEventFilter(this);

    usernameEdit = new QLineEdit(leftPanel);
    usernameEdit->setText(settings->value("username", "用户 1").toString());
    usernameEdit->setVisible(false);
    usernameEdit->setMaxLength(20);
    connect(usernameEdit, &QLineEdit::editingFinished, this, &CatUI::onUsernameEditingFinished);

    editUsernameBtn = new QPushButton("✏️", leftPanel);
    editUsernameBtn->setObjectName("editUsernameBtn");
    editUsernameBtn->setCursor(Qt::PointingHandCursor);
    editUsernameBtn->setToolTip("编辑用户名");
    connect(editUsernameBtn, &QPushButton::clicked, this, &CatUI::onUsernameClicked);

    usernameLayout->addStretch();  // 左侧弹性空间
    usernameLayout->addStretch();  // 弹性空间
    usernameLayout->addStretch();  // 弹性空间
    usernameLayout->addStretch();  // 弹性空间
    usernameLayout->addStretch();  // 弹性空间
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameEdit);
    usernameLayout->addWidget(editUsernameBtn);
    usernameLayout->addStretch();  // 右侧弹性空间

    // 轮回计数区域
    QWidget *cycleWidget = new QWidget(leftPanel);
    cycleWidget->setProperty("class", "cycle-box");
    QVBoxLayout *cycleLayout = new QVBoxLayout(cycleWidget);

    QLabel *cycleTitle = new QLabel("轮回计数", cycleWidget);
    cycleTitle->setProperty("class", "cycle-label");

    // 已过轮回显示
    QHBoxLayout *currentCycleLayout = new QHBoxLayout();
    QLabel *currentCycleTitle = new QLabel("已过:", cycleWidget);
    currentCycleTitle->setProperty("class", "total-value");
    cycleLabel = new QLabel(QString::number(currentCycle), cycleWidget);
    cycleLabel->setProperty("class", "cycle-value");
    cycleLabel->setCursor(Qt::PointingHandCursor);
    cycleLabel->installEventFilter(this);
    cycleLabel->setAlignment(Qt::AlignCenter);

    cycleDownBtn = new QPushButton("-", cycleWidget);
    cycleDownBtn->setObjectName("cycleBtn");
    cycleDownBtn->setFixedSize(30, 30);
    connect(cycleDownBtn, &QPushButton::clicked, this, &CatUI::onCycleValueChanged);

    cycleUpBtn = new QPushButton("+", cycleWidget);
    cycleUpBtn->setObjectName("cycleBtn");
    cycleUpBtn->setFixedSize(30, 30);
    connect(cycleUpBtn, &QPushButton::clicked, this, &CatUI::onCycleValueChanged);

    usernameLayout->addStretch();
    currentCycleLayout->addWidget(currentCycleTitle);
    currentCycleLayout->addWidget(cycleLabel);
    currentCycleLayout->addWidget(cycleDownBtn);
    currentCycleLayout->addWidget(cycleUpBtn);
    currentCycleLayout->addStretch();
    usernameLayout->addStretch();

    // 总轮回显示
    QHBoxLayout *totalCycleLayout = new QHBoxLayout();
    QLabel *totalCycleTitle = new QLabel("总计:", cycleWidget);
    totalCycleTitle->setProperty("class", "total-value");
    totalLabel = new QLabel(QString::number(totalCycles), cycleWidget);
    totalLabel->setProperty("class", "cycle-value");
    totalLabel->setCursor(Qt::PointingHandCursor);
    totalLabel->installEventFilter(this);
    totalLabel->setAlignment(Qt::AlignCenter);

    totalDownBtn = new QPushButton("-", cycleWidget);
    totalDownBtn->setObjectName("cycleBtn");
    totalDownBtn->setFixedSize(30, 30);
    connect(totalDownBtn, &QPushButton::clicked, this, &CatUI::onTotalValueChanged);

    totalUpBtn = new QPushButton("+", cycleWidget);
    totalUpBtn->setObjectName("cycleBtn");
    totalUpBtn->setFixedSize(30, 30);
    connect(totalUpBtn, &QPushButton::clicked, this, &CatUI::onTotalValueChanged);

    usernameLayout->addStretch();  // 弹性空间
    totalCycleLayout->addWidget(totalCycleTitle);
    totalCycleLayout->addWidget(totalLabel);
    totalCycleLayout->addWidget(totalDownBtn);
    totalCycleLayout->addWidget(totalUpBtn);
    totalCycleLayout->addStretch();
    usernameLayout->addStretch();  // 弹性空间

    cycleLayout->addWidget(cycleTitle);
    cycleLayout->addLayout(currentCycleLayout);
    cycleLayout->addLayout(totalCycleLayout);

    // 左侧固定按钮
    QPushButton *btnHome = new QPushButton("🏠 首页", leftPanel);
    btnHome->setObjectName("leftPanelButton");
    QPushButton *btnProfile = new QPushButton("👤 个人资料", leftPanel);
    btnProfile->setObjectName("leftPanelButton");
    QPushButton *btnMessages = new QPushButton("💬 消息", leftPanel);
    btnMessages->setObjectName("leftPanelButton");
    QPushButton *btnSettings = new QPushButton("⚙️ 设置", leftPanel);
    btnSettings->setObjectName("leftPanelButton");
    QPushButton *btnHelp = new QPushButton("❓ 帮助", leftPanel);
    btnHelp->setObjectName("leftPanelButton");

    leftLayout->addWidget(avatarLabel, 0, Qt::AlignCenter);
    leftLayout->addWidget(changeAvatarBtn, 0, Qt::AlignCenter);
    leftLayout->addLayout(usernameLayout);
    leftLayout->addWidget(cycleWidget);
    leftLayout->addSpacing(20);
    leftLayout->addWidget(btnHome);
    leftLayout->addWidget(btnProfile);
    leftLayout->addWidget(btnMessages);
    leftLayout->addWidget(btnSettings);
    leftLayout->addWidget(btnHelp);
    leftLayout->addStretch();

    // -------------------- 右侧可滑动窗口 --------------------
    QScrollArea *rightScrollArea = new QScrollArea(this);
    rightScrollArea->setWidgetResizable(true);
    rightScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    rightScrollArea->setStyleSheet("QScrollArea { border: none; background-color: transparent; }");

    // 创建右侧内容容器
    QWidget *rightContent = new QWidget();
    rightContent->setStyleSheet("background-color: transparent;");

    // 右侧内容使用水平布局
    QHBoxLayout *rightContentLayout = new QHBoxLayout(rightContent);
    rightContentLayout->setContentsMargins(10, 10, 10, 10);
    rightContentLayout->setSpacing(15);

    // ========== 左侧列：功能按钮区域（缩小后的按钮）==========
    QWidget *leftButtonColumnWidget = new QWidget(rightContent);
    leftButtonColumnWidget->setObjectName("infoBox");
    leftButtonColumnWidget->setFixedWidth(150);
    QVBoxLayout *leftButtonColumnLayout = new QVBoxLayout(leftButtonColumnWidget);
    leftButtonColumnLayout->setAlignment(Qt::AlignTop);
    leftButtonColumnLayout->setSpacing(8);

    QLabel *buttonTitle = new QLabel("🔘 功能菜单", leftButtonColumnWidget);
    buttonTitle->setProperty("class", "title-label");
    buttonTitle->setStyleSheet("font-size: 14px; margin-bottom: 8px;");

    QPushButton *btnMode = new QPushButton("🔄 切换 model", leftButtonColumnWidget);
    btnMode->setObjectName("leftSideButton");
    btnMode->setToolTip("点击切换模式");

    QPushButton *btnTheme = new QPushButton("🎨 切换 theme", leftButtonColumnWidget);
    btnTheme->setObjectName("leftSideButton");
    btnTheme->setToolTip("点击切换主题");

    QPushButton *btnFunc = new QPushButton("⚡ 功能", leftButtonColumnWidget);
    btnFunc->setObjectName("leftSideButton");
    btnFunc->setToolTip("功能设置");

    QPushButton *btnInfo = new QPushButton("ℹ️ 相关信息", leftButtonColumnWidget);
    btnInfo->setObjectName("leftSideButton");
    btnInfo->setToolTip("查看相关信息");

    QPushButton *btnExtra = new QPushButton("📌 其他功能", leftButtonColumnWidget);
    btnExtra->setObjectName("leftSideButton");
    btnExtra->setToolTip("其他功能选项");

    leftButtonColumnLayout->addWidget(buttonTitle);
    leftButtonColumnLayout->addWidget(btnMode);
    leftButtonColumnLayout->addWidget(btnTheme);
    leftButtonColumnLayout->addWidget(btnFunc);
    leftButtonColumnLayout->addWidget(btnInfo);
    leftButtonColumnLayout->addWidget(btnExtra);
    leftButtonColumnLayout->addStretch();

    // ========== 右侧列：聊天框 + 下方小日历 + 大量附加组件 ==========
    QWidget *rightColumnWidget = new QWidget(rightContent);
    rightColumnWidget->setObjectName("infoBox");
    QVBoxLayout *rightColumnLayout = new QVBoxLayout(rightColumnWidget);
    rightColumnLayout->setSpacing(20);  // 增加间距让滑动效果更明显

    // 1. 聊天框区域（修改后的版本）
    QWidget *chatWidget = new QWidget(rightColumnWidget);
    QVBoxLayout *chatLayout = new QVBoxLayout(chatWidget);
    chatLayout->setContentsMargins(0, 0, 0, 0);
    chatLayout->setSpacing(10);

    QLabel *chatTitle = new QLabel("💬 聊天对话框", chatWidget);
    chatTitle->setProperty("class", "title-label");

    // 聊天显示区域
    chatDisplay = new QTextEdit(chatWidget);
    chatDisplay->setReadOnly(true);
    chatDisplay->setMinimumHeight(200);
    // 添加一些初始消息（带时间戳）
    chatDisplay->append(QString("%1 🐱: 你好，我是小猫").arg(getCurrentTime()));
    chatDisplay->append(QString("%1 你: 喵~ 今天有什么安排？").arg(getCurrentTime()));
    chatDisplay->append(QString("%1 🐱: 今天想去公园玩").arg(getCurrentTime()));
    chatDisplay->append(QString("%1 你: 好啊，几点出发？").arg(getCurrentTime()));
    chatDisplay->append(QString("%1 🐱: 下午3点怎么样？").arg(getCurrentTime()));
    chatDisplay->append(QString("%1 你: 好的，到时候见！").arg(getCurrentTime()));

    // 聊天输入区域（水平布局）
    QWidget *inputWidget = new QWidget(chatWidget);
    QHBoxLayout *inputLayout = new QHBoxLayout(inputWidget);
    inputLayout->setContentsMargins(0, 0, 0, 0);
    inputLayout->setSpacing(5);

    chatInput = new QLineEdit(inputWidget);
    chatInput->setPlaceholderText("输入消息...");
    chatInput->setMinimumHeight(30);
    connect(chatInput, &QLineEdit::returnPressed, this, &CatUI::sendMessage);  // 回车发送

    sendBtn = new QPushButton("发送", inputWidget);
    sendBtn->setObjectName("sendBtn");
    sendBtn->setCursor(Qt::PointingHandCursor);
    sendBtn->setMinimumWidth(60);
    connect(sendBtn, &QPushButton::clicked, this, &CatUI::sendMessage);

    clearChatBtn = new QPushButton("清空", inputWidget);
    clearChatBtn->setObjectName("clearChatBtn");
    clearChatBtn->setCursor(Qt::PointingHandCursor);
    clearChatBtn->setMinimumWidth(60);
    connect(clearChatBtn, &QPushButton::clicked, this, &CatUI::clearChat);

    inputLayout->addWidget(chatInput, 1);  // 输入框占满剩余空间
    inputLayout->addWidget(sendBtn);
    inputLayout->addWidget(clearChatBtn);

    chatLayout->addWidget(chatTitle);
    chatLayout->addWidget(chatDisplay);
    chatLayout->addWidget(inputWidget);

    // 2. 小日历区域
    QWidget *calendarWidget = new QWidget(rightColumnWidget);
    QVBoxLayout *calendarLayout = new QVBoxLayout(calendarWidget);
    calendarLayout->setContentsMargins(0, 0, 0, 0);
    calendarLayout->setSpacing(10);

    QLabel *calendarTitle = new QLabel("📅 小日历", calendarWidget);
    calendarTitle->setProperty("class", "title-label");

    QCalendarWidget *calendar = new QCalendarWidget(calendarWidget);
    calendar->setMinimumHeight(200);
    calendar->setGridVisible(true);
    calendar->setSelectedDate(QDate::currentDate());

    calendarLayout->addWidget(calendarTitle);
    calendarLayout->addWidget(calendar);

    // 3. 进度条区域
    QWidget *progressWidget = new QWidget(rightColumnWidget);
    QVBoxLayout *progressLayout = new QVBoxLayout(progressWidget);
    progressLayout->setContentsMargins(0, 0, 0, 0);
    progressLayout->setSpacing(10);

    QLabel *progressTitle = new QLabel("📊 任务进度", progressWidget);
    progressTitle->setProperty("class", "title-label");

    QProgressBar *progressBar1 = new QProgressBar(progressWidget);
    progressBar1->setValue(75);
    progressBar1->setFormat("项目A: %p%");
    progressBar1->setMinimumHeight(25);

    QProgressBar *progressBar2 = new QProgressBar(progressWidget);
    progressBar2->setValue(45);
    progressBar2->setFormat("项目B: %p%");
    progressBar2->setMinimumHeight(25);

    QProgressBar *progressBar3 = new QProgressBar(progressWidget);
    progressBar3->setValue(90);
    progressBar3->setFormat("项目C: %p%");
    progressBar3->setMinimumHeight(25);

    progressLayout->addWidget(progressTitle);
    progressLayout->addWidget(progressBar1);
    progressLayout->addWidget(progressBar2);
    progressLayout->addWidget(progressBar3);

    // 4. 滑块控制区域
    QWidget *sliderWidget = new QWidget(rightColumnWidget);
    QVBoxLayout *sliderLayout = new QVBoxLayout(sliderWidget);
    sliderLayout->setContentsMargins(0, 0, 0, 0);
    sliderLayout->setSpacing(15);

    QLabel *sliderTitle = new QLabel("🎚️ 控制面板", sliderWidget);
    sliderTitle->setProperty("class", "title-label");

    QLabel *volumeLabel = new QLabel("音量控制: 60%", sliderWidget);
    QSlider *volumeSlider = new QSlider(Qt::Horizontal, sliderWidget);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(60);
    volumeSlider->setMinimumHeight(30);

    QLabel *brightnessLabel = new QLabel("亮度控制: 80%", sliderWidget);
    QSlider *brightnessSlider = new QSlider(Qt::Horizontal, sliderWidget);
    brightnessSlider->setRange(0, 100);
    brightnessSlider->setValue(80);
    brightnessSlider->setMinimumHeight(30);

    sliderLayout->addWidget(sliderTitle);
    sliderLayout->addWidget(volumeLabel);
    sliderLayout->addWidget(volumeSlider);
    sliderLayout->addWidget(brightnessLabel);
    sliderLayout->addWidget(brightnessSlider);

    // 5. 复选框区域
    QWidget *checkWidget = new QWidget(rightColumnWidget);
    QVBoxLayout *checkLayout = new QVBoxLayout(checkWidget);
    checkLayout->setContentsMargins(0, 0, 0, 0);
    checkLayout->setSpacing(10);

    QLabel *checkTitle = new QLabel("✅ 选项设置", checkWidget);
    checkTitle->setProperty("class", "title-label");

    QCheckBox *check1 = new QCheckBox("启用通知", checkWidget);
    QCheckBox *check2 = new QCheckBox("自动保存", checkWidget);
    QCheckBox *check3 = new QCheckBox("深色模式", checkWidget);
    check3->setChecked(true);

    QRadioButton *radio1 = new QRadioButton("简单模式", checkWidget);
    QRadioButton *radio2 = new QRadioButton("高级模式", checkWidget);
    radio1->setChecked(true);

    checkLayout->addWidget(checkTitle);
    checkLayout->addWidget(check1);
    checkLayout->addWidget(check2);
    checkLayout->addWidget(check3);
    checkLayout->addWidget(radio1);
    checkLayout->addWidget(radio2);

    // 6. 下拉选择框区域
    QWidget *comboWidget = new QWidget(rightColumnWidget);
    QVBoxLayout *comboLayout = new QVBoxLayout(comboWidget);
    comboLayout->setContentsMargins(0, 0, 0, 0);
    comboLayout->setSpacing(10);

    QLabel *comboTitle = new QLabel("📋 选择菜单", comboWidget);
    comboTitle->setProperty("class", "title-label");

    QComboBox *combo1 = new QComboBox(comboWidget);
    combo1->addItem("选项 1");
    combo1->addItem("选项 2");
    combo1->addItem("选项 3");
    combo1->addItem("选项 4");

    QComboBox *combo2 = new QComboBox(comboWidget);
    combo2->addItem("分类 A");
    combo2->addItem("分类 B");
    combo2->addItem("分类 C");

    comboLayout->addWidget(comboTitle);
    comboLayout->addWidget(combo1);
    comboLayout->addWidget(combo2);

    // 7. 列表区域
    QWidget *listWidget = new QWidget(rightColumnWidget);
    QVBoxLayout *listLayout = new QVBoxLayout(listWidget);
    listLayout->setContentsMargins(0, 0, 0, 0);
    listLayout->setSpacing(10);

    QLabel *listTitle = new QLabel("📝 任务列表", listWidget);
    listTitle->setProperty("class", "title-label");

    QListWidget *list = new QListWidget(listWidget);
    list->addItem("完成项目报告");
    list->addItem("参加会议讨论");
    list->addItem("回复客户邮件");
    list->addItem("更新文档");
    list->addItem("代码审查");
    list->addItem("测试新功能");
    list->addItem("部署到服务器");
    list->setMinimumHeight(150);

    listLayout->addWidget(listTitle);
    listLayout->addWidget(list);

    // 8. 表格区域
    QWidget *tableWidget = new QWidget(rightColumnWidget);
    QVBoxLayout *tableLayout = new QVBoxLayout(tableWidget);
    tableLayout->setContentsMargins(0, 0, 0, 0);
    tableLayout->setSpacing(10);

    QLabel *tableTitle = new QLabel("📊 数据表格", tableWidget);
    tableTitle->setProperty("class", "title-label");

    QTableWidget *table = new QTableWidget(8, 3, tableWidget);  // 增加行数
    table->setHorizontalHeaderLabels(QStringList() << "姓名" << "年龄" << "城市");

    QStringList names = {"张三", "李四", "王五", "赵六", "钱七", "孙八", "周九", "吴十"};
    QStringList ages = {"25", "30", "28", "32", "27", "29", "31", "26"};
    QStringList cities = {"北京", "上海", "广州", "深圳", "杭州", "成都", "武汉", "西安"};

    for (int i = 0; i < 8; i++) {
        table->setItem(i, 0, new QTableWidgetItem(names[i]));
        table->setItem(i, 1, new QTableWidgetItem(ages[i]));
        table->setItem(i, 2, new QTableWidgetItem(cities[i]));
    }

    table->setMinimumHeight(200);
    table->horizontalHeader()->setStretchLastSection(true);

    tableLayout->addWidget(tableTitle);
    tableLayout->addWidget(table);

    // 将所有部分添加到右侧列
    rightColumnLayout->addWidget(chatWidget);
    rightColumnLayout->addWidget(calendarWidget);
    rightColumnLayout->addWidget(progressWidget);
    rightColumnLayout->addWidget(sliderWidget);
    rightColumnLayout->addWidget(checkWidget);
    rightColumnLayout->addWidget(comboWidget);
    rightColumnLayout->addWidget(listWidget);
    rightColumnLayout->addWidget(tableWidget);
    rightColumnLayout->addStretch();

    // 将左右两列添加到右侧内容的水平布局
    rightContentLayout->addWidget(leftButtonColumnWidget);
    rightContentLayout->addWidget(rightColumnWidget, 1);

    // 设置滚动区域的内容
    rightScrollArea->setWidget(rightContent);

    // -------------------- 主布局：左右并排 --------------------
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(rightScrollArea, 1);

    setLayout(mainLayout);

    // 加载保存的头像
    if (!settings->value("avatar").isNull()) {
        QPixmap pixmap;
        if (pixmap.loadFromData(settings->value("avatar").toByteArray())) {
            updateAvatar(pixmap);
        }
    }
}

void CatUI::setupDarkTheme()
{
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(30, 30, 30));
    darkPalette.setColor(QPalette::WindowText, QColor(224, 224, 224));
    darkPalette.setColor(QPalette::Base, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::Text, QColor(224, 224, 224));
    darkPalette.setColor(QPalette::Button, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::ButtonText, QColor(224, 224, 224));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, QColor(224, 224, 224));

    //qApp->setPalette(darkPalette);
}

void CatUI::loadSettings()
{
    currentCycle = settings->value("currentCycle", 0).toInt();
    totalCycles = settings->value("totalCycles", 1332).toInt();
}

void CatUI::saveSettings()
{
    settings->setValue("username", usernameLabel->text());
    settings->setValue("currentCycle", currentCycle);
    settings->setValue("totalCycles", totalCycles);

    // 头像已经在 updateAvatar 中保存了
}

void CatUI::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event->accept();
}

bool CatUI::eventFilter(QObject *obj, QEvent *event)
{
    // 头像点击
    if (obj == avatarLabel && event->type() == QEvent::MouseButtonPress) {
        onAvatarClicked();
        return true;
    }

    // 用户名点击
    if (obj == usernameLabel && event->type() == QEvent::MouseButtonPress) {
        onUsernameClicked();
        return true;
    }

    // 已过轮回数值双击编辑
    if (obj == cycleLabel && event->type() == QEvent::MouseButtonDblClick) {
        bool ok;
        int newCycle = QInputDialog::getInt(this,
                                            tr("修改已过轮回数"),
                                            tr("请输入新的已过轮回数 (0 - %1):").arg(totalCycles),
                                            currentCycle,  // 当前值
                                            0,             // 最小值
                                            totalCycles,   // 最大值（不能超过总轮回）
                                            1,             // 步长
                                            &ok);
        if (ok) {
            currentCycle = newCycle;
            cycleLabel->setText(QString::number(currentCycle));
            saveSettings();  // 保存设置
        }
        return true;
    }

    // 总轮回数值双击编辑
    if (obj == totalLabel && event->type() == QEvent::MouseButtonDblClick) {
        bool ok;
        int newTotal = QInputDialog::getInt(this,
                                            tr("修改总轮回数"),
                                            tr("请输入新的总轮回数 (最小 1):"),
                                            totalCycles,  // 当前值
                                            1,            // 最小值（不能小于1）
                                            1000000,      // 最大值（可以根据需要调整）
                                            1,            // 步长
                                            &ok);
        if (ok) {
            totalCycles = newTotal;
            totalLabel->setText(QString::number(totalCycles));

            // 如果当前轮回超过新的总轮回，自动调整
            if (currentCycle > totalCycles) {
                currentCycle = totalCycles;
                cycleLabel->setText(QString::number(currentCycle));
            }

            saveSettings();  // 保存设置
        }
        return true;
    }

    return QWidget::eventFilter(obj, event);
}

void CatUI::onAvatarClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "选择头像图片",
                                                    QDir::homePath(),
                                                    "图片文件 (*.png *.jpg *.jpeg *.bmp *.gif);;所有文件 (*.*)");

    if (fileName.isEmpty()) {
        return;
    }

    QPixmap pixmap(fileName);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "错误", "无法加载图片文件！");
        return;
    }

    updateAvatar(pixmap);
}

void CatUI::updateAvatar(const QPixmap &pixmap)
{
    if (!avatarLabel) return;

    // 缩放图片
    QPixmap scaledPixmap = pixmap.scaled(90, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 创建圆形头像
    QPixmap roundedPixmap(90, 90);
    roundedPixmap.fill(Qt::transparent);

    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QPainterPath path;
    path.addEllipse(0, 0, 90, 90);
    painter.setClipPath(path);

    int x = (90 - scaledPixmap.width()) / 2;
    int y = (90 - scaledPixmap.height()) / 2;
    painter.drawPixmap(x, y, scaledPixmap);

    painter.end();

    avatarLabel->setPixmap(roundedPixmap);
    avatarLabel->setText("");

    // 保存头像到设置
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    roundedPixmap.save(&buffer, "PNG");
    settings->setValue("avatar", byteArray);
}

void CatUI::onUsernameClicked()
{
    usernameLabel->setVisible(false);
    usernameEdit->setVisible(true);
    usernameEdit->setFocus();
    usernameEdit->selectAll();
    editUsernameBtn->setVisible(false);
}

void CatUI::onUsernameEditingFinished()
{
    QString newUsername = usernameEdit->text().trimmed();
    if (newUsername.isEmpty()) {
        newUsername = "用户 1";
    }

    usernameLabel->setText(newUsername);
    usernameLabel->setVisible(true);
    usernameEdit->setVisible(false);
    editUsernameBtn->setVisible(true);

    saveSettings();  // 立即保存
}

void CatUI::onCycleValueChanged()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn == cycleUpBtn) {
        currentCycle++;
        if (currentCycle > totalCycles) {
            currentCycle = totalCycles;
        }
    } else if (btn == cycleDownBtn) {
        currentCycle--;
        if (currentCycle < 0) {
            currentCycle = 0;
        }
    }

    cycleLabel->setText(QString::number(currentCycle));
    saveSettings();  // 立即保存
}

void CatUI::onTotalValueChanged()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn == totalUpBtn) {
        totalCycles++;
    } else if (btn == totalDownBtn) {
        totalCycles--;
        if (totalCycles < 1) {
            totalCycles = 1;
        }
    }

    totalLabel->setText(QString::number(totalCycles));

    // 如果当前轮回超过总轮回，自动调整
    if (currentCycle > totalCycles) {
        currentCycle = totalCycles;
        cycleLabel->setText(QString::number(currentCycle));
    }

    saveSettings();  // 立即保存
}

// 在文件末尾添加这些函数实现

QString CatUI::getCurrentTime()
{
    return QDateTime::currentDateTime().toString("[hh:mm:ss]");
}

void CatUI::sendMessage()
{
    QString message = chatInput->text().trimmed();
    if (message.isEmpty()) {
        return;  // 空消息不发送
    }

    // 添加用户消息到聊天框
    chatDisplay->append(QString("%1 你: %2").arg(getCurrentTime()).arg(message));

    // 清空输入框
    chatInput->clear();

    // 自动滚动到底部
    QScrollBar *scrollBar = chatDisplay->verticalScrollBar();
    if (scrollBar) {
        scrollBar->setValue(scrollBar->maximum());
    }

    // 可选：添加自动回复（模拟小猫回复）
    // 这里简单示例，可以扩展为更复杂的逻辑
    QString response;
    if (message.contains("喵") || message.contains("猫")) {
        response = "喵喵~";
    } else if (message.contains("你好") || message.contains("您好")) {
        response = "你好呀！";
    } else if (message.contains("？") || message.contains("?")) {
        response = "让我想想...";
    } else {
        response = "收到消息啦！";
    }

    // 延迟一点时间回复，更像真实聊天
    QTimer::singleShot(500, this, [this, response]() {
        chatDisplay->append(QString("%1 🐱: %2").arg(getCurrentTime()).arg(response));
        // 再次滚动到底部
        QScrollBar *scrollBar = chatDisplay->verticalScrollBar();
        if (scrollBar) {
            scrollBar->setValue(scrollBar->maximum());
        }
    });
}

void CatUI::clearChat()
{
    // 弹出确认对话框
    QMessageBox::StandardButton reply = QMessageBox::question(this, "清空聊天",
                                                              "确定要清空所有聊天记录吗？",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        chatDisplay->clear();
        // 添加一条系统消息
        chatDisplay->append(QString("%1 系统: 聊天记录已清空").arg(getCurrentTime()));
    }
}
