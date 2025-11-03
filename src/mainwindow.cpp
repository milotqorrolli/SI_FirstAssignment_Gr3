#include "mainwindow.hpp"
#include "ui_mainwindow.h"

// Main window constructor: sets up UI and connects GUI signals to slots.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pdfEncryptor = nullptr;

    // Wire buttons to handler methods
    connect(ui->encryptButton, &QPushButton::clicked, this, &MainWindow::onEncryptClicked);
    connect(ui->decryptButton, &QPushButton::clicked, this, &MainWindow::onDecryptClicked);
    connect(ui->selectInputButton, &QPushButton::clicked, this, &MainWindow::onSelectInputFile);
    connect(ui->selectOutputButton, &QPushButton::clicked, this, &MainWindow::onSelectOutputFile);
}

// Destructor: free UI and any allocated PDFEncryptor instance.
MainWindow::~MainWindow()
{
    delete ui;
    if (pdfEncryptor)
    {
        delete pdfEncryptor;
    }
}

// Slot: invoked when the Encrypt button is clicked. Validates input, creates
// a PDFEncryptor with the entered key, and runs encryptPDF to write output.
void MainWindow::onEncryptClicked()
{
    QString key = ui->keyLineEdit->text();
    if (key.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please enter a key.");
        return;
    }
    if (inputFilePath.isEmpty() || outputFilePath.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please select input and output files.");
        return;
    }
    if (pdfEncryptor)
    {
        delete pdfEncryptor;
    }
    pdfEncryptor = new PDFEncryptor(key.toStdString());
    if (pdfEncryptor->encryptPDF(inputFilePath.toStdString(), outputFilePath.toStdString()))
    {
        QMessageBox::information(this, "Success", "PDF encrypted successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to encrypt PDF.");
    }
}

// Slot: invoked when the Decrypt button is clicked. Validates input, creates
// a PDFEncryptor and calls decryptPDF to restore the original PDF.
void MainWindow::onDecryptClicked()
{
    QString key = ui->keyLineEdit->text();
    if (key.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please enter a key.");
        return;
    }
    if (inputFilePath.isEmpty() || outputFilePath.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please select input and output files.");
        return;
    }
    if (pdfEncryptor)
    {
        delete pdfEncryptor;
    }
    pdfEncryptor = new PDFEncryptor(key.toStdString());
    if (pdfEncryptor->decryptPDF(inputFilePath.toStdString(), outputFilePath.toStdString()))
    {
        QMessageBox::information(this, "Success", "PDF decrypted successfully.");
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to decrypt PDF.");
    }
}

// Slot: open a file dialog to pick the input PDF and show path in UI.
void MainWindow::onSelectInputFile()
{
    inputFilePath = QFileDialog::getOpenFileName(this, "Select Input PDF", "", "PDF Files (*.pdf)");
    if (!inputFilePath.isEmpty())
    {
        ui->inputLineEdit->setText(inputFilePath);
    }
}

// Slot: open a save dialog to choose where to write the output PDF.
void MainWindow::onSelectOutputFile()
{
    outputFilePath = QFileDialog::getSaveFileName(this, "Select Output PDF", "", "PDF Files (*.pdf)");
    if (!outputFilePath.isEmpty())
    {
        ui->outputLineEdit->setText(outputFilePath);
    }
}
