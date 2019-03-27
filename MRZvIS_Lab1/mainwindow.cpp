#include "mainwindow.h"


MainWindow::MainWindow() {
    const int WINDOW_WIDTH  = 700,
              WINDOW_HEIGHT = 500;
    const string WINDOW_TITLE = "PIPELINE";

    textBox = new QTextEdit();

    buttonStart = new QPushButton("START");

    vertice = new QVBoxLayout;
    vertice->setMargin(5);
    vertice->setSpacing(20);

    vertice->addWidget(textBox);
    //vertice->addWidget(buttonStart);

    widget.setLayout(vertice);
    widget.setWindowTitle("PIPELINE");
    widget.setMinimumWidth(WINDOW_WIDTH);
    widget.setMinimumHeight(WINDOW_HEIGHT);
    widget.show();
}

void MainWindow::printText(const QString &input) {
    textBox->insertPlainText(input);
}
