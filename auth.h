#ifndef AUTH_H
#define AUTH_H

#include <QDialog>

namespace Ui {
class auth;
}

class auth : public QDialog
{
    Q_OBJECT

public:
    explicit auth(QWidget *parent = nullptr);
    ~auth();

private slots:
    void on_auth_Button_clicked();

    void on_reg_Button_clicked();

    void on_back_Button_clicked();
    void on_message_reg(QString msg);
    void on_message_auth(QString msg);

private:
    Ui::auth *ui;
    bool flag;

    void change_mode(int mode);
signals:
    void closed(QString login);
};

#endif // AUTH_H
