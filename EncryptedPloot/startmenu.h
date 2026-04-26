#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class StartMenu;
}
QT_END_NAMESPACE

class StartMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu() override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_actionExit_triggered();

    void on_actionOpen_triggered();

private:
    Ui::StartMenu *ui;
    void des_encrypt(QString &encoded_block, QString &key);
    void des_decrypt(QString &encrypted_block, QString &key);
    QString bin_to_hex(QString string);
    QString hex_to_bin(QString string);
    QString dec_to_bin(int n);
    QString shift_bit_left(QString string, int n);
    QString xor_add(QString string1, QString string2);
    QString permute(QString &key, QVector<int> &arr, int n);
    QString char_to_hex(QString &encoded_block);
};
#endif // STARTMENU_H
