#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include "common.h"
#include "mytextbrowser.h"

#include <QWidget>
#include <QtWebSockets/QWebSocket>
#include <QSplitter>
#include <QTableWidgetItem>
#include <QKeyEvent>

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();
    void SetSendBtnEnabled(bool b);

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

public slots:
    void OnUploadFileSuccess(QString filePath);

private slots:
    void on_sendMsgPushButton_clicked();
    void OnWebSocketMsgReceived(const QString &msg);
    void OnItemDoubleClicked(QTableWidgetItem *item);
    void OnTabCloseRequested(int index);
    void OnCurrentChanged(int index);
    void OnUploadFilePushButtonClicked();

private:
    Ui::ChatWidget *ui;

    MyTextBrowser       *m_pTextBrowser;

    bool                m_bCtrlPressed;
    QVector<MsgInfo>    m_vecMsgInfos;
    QVector<UserInfo>   m_vecOnlineUsers;
    QString             m_strFileLink;
    QString             m_strContentTemplateWithLink;
    QString             m_strContentTemplateWithoutLink;
    QMap<QString, QString>  m_jMessages;

    bool                m_bIsMainWindow;
    QVector<QString>    m_vecUserIds;   //用于保存多窗口的userId

signals:
    void newMessageArrived();
    void uploadFile(QString filePath);
    void anchorClicked(const QUrl &url);
};

#endif // CHATWIDGET_H