#ifndef TASK_SOLUTION_H
#define TASK_SOLUTION_H

#include <QDialog>

namespace Ui {
class Task_solution;
}

class Task_solution : public QDialog
{
    Q_OBJECT

public:
    explicit Task_solution(QWidget *parent = nullptr);
    ~Task_solution();

private slots:
    void on_send_Button_clicked();

    void on_back_Button_clicked();
    void on_message_task(QString msg);

private:
    Ui::Task_solution *ui;
    QStringList zapros;
    QString rightanswer;

public slots:
    void change_task(QString task);
signals:
    void back(QString answ);
};

#endif // TASK_SOLUTION_H
