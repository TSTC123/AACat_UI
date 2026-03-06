#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QEvent>
#include <QSettings>
#include <QTextEdit>

class QLabel;
class QPushButton;
class QLineEdit;

class CatUI : public QWidget
{
    Q_OBJECT

public:
    CatUI(QWidget *parent = nullptr);
    ~CatUI() = default;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void closeEvent(QCloseEvent *event) override;  // 窗口关闭时保存设置

private slots:
    void onAvatarClicked();                          // 头像点击事件
    void updateAvatar(const QPixmap &pixmap);        // 更新头像
    void onUsernameClicked();                        // 用户名点击事件
    void onUsernameEditingFinished();                 // 用户名编辑完成


    void onCycleValueChanged();                       // 轮回值改变
    void onTotalValueChanged();                       // 总轮回值改变

    void sendMessage();           // 新增：发送消息
    void clearChat();             // 新增：清空聊天
    QString getCurrentTime();     // 新增：获取当前时间

private:
    void setupDarkTheme();
    void loadSettings();                              // 加载保存的设置
    void saveSettings();                              // 保存设置

    QLabel *avatarLabel;                              // 头像标签
    QPushButton *changeAvatarBtn;                      // 更换头像按钮
    QLabel *usernameLabel;                             // 用户名标签
    QLineEdit *usernameEdit;                           // 用户名编辑框
    QPushButton *editUsernameBtn;                      // 编辑用户名按钮

    QLabel *cycleLabel;                                // 已过轮回标签
    QLabel *totalLabel;                                // 总轮回标签
    QPushButton *cycleUpBtn;                           // 轮回+1按钮
    QPushButton *cycleDownBtn;                          // 轮回-1按钮
    QPushButton *totalUpBtn;                            // 总轮回+1按钮
    QPushButton *totalDownBtn;                          // 总轮回-1按钮

    int currentCycle;                                   // 当前已过轮回
    int totalCycles;                                    // 总轮回数

    QTextEdit *chatDisplay;      // 改为成员变量
    QLineEdit *chatInput;         // 新增：聊天输入框
    QPushButton *sendBtn;         // 新增：发送按钮
    QPushButton *clearChatBtn;    // 新增：清空聊天按钮

    QSettings *settings;                                // 设置保存
};

#endif // WIDGET_H
