#include "mainwindow.h"


MainWindow::MainWindow() {

    textBox = new QTextEdit();

    buttonStart = new QPushButton("START");

    vertice = new QVBoxLayout;
    vertice->setMargin(5);
    vertice->setSpacing(20);

    vertice->addWidget(textBox);
    vertice->addWidget(buttonStart);

    widget.setLayout(vertice);
    widget.setWindowTitle("PIPELINE");
    widget.setMinimumWidth(500);
    widget.setMinimumHeight(200);
    widget.show();
}

void MainWindow::printText(const QString &input) {

    textBox->insertPlainText(input);
}
