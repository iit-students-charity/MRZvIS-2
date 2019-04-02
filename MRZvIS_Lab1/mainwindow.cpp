#include "mainwindow.h"


MainWindow::MainWindow(QPushButton& button) {
    const int WINDOW_WIDTH  = 1800,
              WINDOW_HEIGHT = 900,
              TEXTBOX_HEIGHT = 100;
    const QString WINDOW_TITLE = "PIPELINE";
    QLabel *aLabel = new QLabel("&A = "),
           *bLabel = new QLabel("&B = ");

    operand1Line = new QLineEdit();
    operand2Line = new QLineEdit();
    aLabel->setBuddy(operand1Line);
    bLabel->setBuddy(operand2Line);
    lines = new QHBoxLayout();
    lines->addWidget(aLabel);
    lines->addWidget(operand1Line);
    lines->addWidget(bLabel);
    lines->addWidget(operand2Line);

    table =  new QTableWidget();

    table->setRowCount(6);
    table->setColumnCount(8);

    textBox = new QTextEdit();
    textBox->setMaximumHeight(TEXTBOX_HEIGHT);

    buttonStart = &button;

    vertice = new QVBoxLayout;
    vertice->setMargin(5);
    vertice->setSpacing(20);

    vertice->addLayout(lines);
    vertice->addWidget(table);
    vertice->addWidget(&button);
    vertice->addWidget(textBox);

    widget.setLayout(vertice);
    widget.setWindowTitle("PIPELINE");
    widget.setMinimumWidth(WINDOW_WIDTH);
    widget.setMinimumHeight(WINDOW_HEIGHT);
    widget.show();
}

void MainWindow::printText(const QString &input) {
    textBox->insertPlainText(input);
}

QLineEdit* MainWindow::getOp1Line(){
    return operand1Line;
}

QLineEdit* MainWindow::getOp2Line(){
    return operand2Line;
}

QTableWidget* MainWindow::getTable(){
    return table;
}
