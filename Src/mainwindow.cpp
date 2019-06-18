#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    CurrentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    //Get file name from the user
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);  //File stream for QT
    CurrentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) //If there is a problem
    {
        QMessageBox::warning(this, "Warning", "Cannot open the file: "+file.errorString());
    }
    //Get the text and print it in the screan
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text)) //If there is a problem
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: "+file.errorString());
    }
    CurrentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog qDialog(&printer, this);

    if(qDialog.exec() == QDialog::Rejected)
    {
         QMessageBox::warning(this, "Warning", "Cannot print the file");
         return;
    }
    ui->textEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}
