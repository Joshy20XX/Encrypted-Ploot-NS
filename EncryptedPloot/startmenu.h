#ifndef STARTMENU_H
#define STARTMENU_H

#include <QMainWindow>
#include <QFile>

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
    QString des_encrypt(QString &encoded_block, QStringList &roundkeylist, QStringList &roundkeylist_bin);
    QString des_decrypt(QString &encrypted_block, QStringList &roundkeylist, QStringList &roundkeylist_bin);
    QString bin_to_hex(QString &string);
    QString hex_to_bin(QString &string);
    QString dec_to_bin(int n);
    int bin_to_dec(QString &string);
    QString shift_bit_left(QString &string, int n);
    QString xor_add(QString &string1, QString &string2);
    QString permute(QString &key, QVector<int> &arr, int n);
    QString hex_to_char(QString &string);
    void keygen(QString& key, QStringList &roundkeylist, QStringList &roundkeylist_bin);
    void TDES(QFile &ploot_out_file);
};
#endif // STARTMENU_H
