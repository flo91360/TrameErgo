#ifndef INTERFACE2_2_H
#define INTERFACE2_2_H

#include <QDialog>
#include <QApplication>
#include <QFile>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>
#include <QtUiTools>

namespace Ui {
class Interface2_2;
}

class Interface2_2 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface2_2(QWidget *parent = nullptr);
    ~Interface2_2();

private slots:
    void on_checkBoxPsychomotricien_stateChanged(int arg1);

    void on_checkBoxOrthophoniste_stateChanged(int arg1);

    void on_checkBoxPsychologue_stateChanged(int arg1);

    void on_checkBoxOrthopiste_stateChanged(int arg1);

    void on_checkBoxNeuropsychologue_stateChanged(int arg1);

    void on_checkBoxKinesiterapeute_stateChanged(int arg1);

    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface2_2 *ui;
    QLabel *labelPsychomotricien = nullptr;
    QComboBox *comboBoxPsychomotricien  = nullptr;
    QLabel *labelOrthophoniste = nullptr;
    QComboBox *comboBoxOrthophoniste = nullptr;
    QLabel *labelOrthopiste = nullptr;
    QComboBox *comboBoxOrthopiste  = nullptr;
    QLabel *labelKinesiterapeute = nullptr;
    QComboBox *comboBoxKinesiterapeute = nullptr;
    QLabel *labelNeuropsychologue = nullptr;
    QComboBox *comboBoxNeuropsychologue  = nullptr;
    QLabel *labelPsychologue = nullptr;
    QComboBox *comboBoxPsychologue = nullptr;

    QString professionnels = "";
};

#endif // INTERFACE2_2_H
