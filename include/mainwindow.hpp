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

// Main application window: provides a simple UI for selecting input/output
// PDF files and entering an encryption key. The class forwards requests to
// PDFEncryptor for actual encryption/decryption operations.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Create the window and set up the UI widgets.
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slot for handling Encrypt button click.
    void onEncryptClicked();
    // Slot for handling Decrypt button click.
    void onDecryptClicked();
    // Slot to open a file dialog and select the input PDF path.
    void onSelectInputFile();
    // Slot to open a save dialog and select the output PDF path.
    void onSelectOutputFile();

private:
    Ui::MainWindow *ui;
    PDFEncryptor *pdfEncryptor;

    // UI state
    QString inputFilePath;
    QString outputFilePath;
};

#endif
