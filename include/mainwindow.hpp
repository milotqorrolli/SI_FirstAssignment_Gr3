#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "pdf_encryptor.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onEncryptClicked();
    void onDecryptClicked();
    void onSelectInputFile();
    void onSelectOutputFile();

private:
    Ui::MainWindow *ui;
    PDFEncryptor *pdfEncryptor;

    QString inputFilePath;
    QString outputFilePath;
};

#endif
