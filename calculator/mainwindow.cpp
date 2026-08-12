#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    SetupUi();
    SetText("0"); 
}

void MainWindow::SetupUi() {
    QWidget* central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    QVBoxLayout* main_layout = new QVBoxLayout(central_widget);

    l_memory = new QLabel("", this);
    l_formula = new QLabel("", this);
    l_result = new QLabel("0", this);

    l_memory->setObjectName("l_memory");
    l_formula->setObjectName("l_formula");
    l_result->setObjectName("l_result");

    l_memory->setAlignment(Qt::AlignLeft);
    l_formula->setAlignment(Qt::AlignRight);
    l_result->setAlignment(Qt::AlignRight);

    main_layout->addWidget(l_memory);
    main_layout->addWidget(l_formula);
    main_layout->addWidget(l_result);

    QGridLayout* grid_layout = new QGridLayout();

    QPushButton* btn_mc = new QPushButton("MC", this);
    QPushButton* btn_mr = new QPushButton("MR", this);
    QPushButton* btn_ms = new QPushButton("MS", this);
    QPushButton* btn_clear = new QPushButton("C", this);
    QPushButton* btn_backspace = new QPushButton("⌫", this);

    QPushButton* btn_pow = new QPushButton("xʸ", this);
    QPushButton* btn_sign = new QPushButton("±", this);
    QPushButton* btn_div = new QPushButton("÷", this);
    QPushButton* btn_mul = new QPushButton("×", this);
    QPushButton* btn_sub = new QPushButton("−", this);
    QPushButton* btn_add = new QPushButton("+", this);
    QPushButton* btn_equal = new QPushButton("=", this);
    QPushButton* btn_dot = new QPushButton(".", this);

    connect(btn_clear, &QPushButton::clicked, this, &MainWindow::OnClearPressed);
    connect(btn_backspace, &QPushButton::clicked, this, &MainWindow::OnBackspacePressed);
    connect(btn_sign, &QPushButton::clicked, this, &MainWindow::OnSignPressed);
    connect(btn_dot, &QPushButton::clicked, this, &MainWindow::OnDotPressed);
    connect(btn_equal, &QPushButton::clicked, this, &MainWindow::OnEqualPressed);

    connect(btn_mc, &QPushButton::clicked, this, &MainWindow::OnMemoryPressed);
    connect(btn_mr, &QPushButton::clicked, this, &MainWindow::OnMemoryPressed);
    connect(btn_ms, &QPushButton::clicked, this, &MainWindow::OnMemoryPressed);

    connect(btn_add, &QPushButton::clicked, this, &MainWindow::OnOperationPressed);
    connect(btn_sub, &QPushButton::clicked, this, &MainWindow::OnOperationPressed);
    connect(btn_mul, &QPushButton::clicked, this, &MainWindow::OnOperationPressed);
    connect(btn_div, &QPushButton::clicked, this, &MainWindow::OnOperationPressed);
    connect(btn_pow, &QPushButton::clicked, this, &MainWindow::OnOperationPressed);

    QList<QPushButton*> digits;
    for (int i = 0; i <= 9; ++i) {
        QPushButton* btn_digit = new QPushButton(QString::number(i), this);
        digits.append(btn_digit);
        connect(btn_digit, &QPushButton::clicked, this, &MainWindow::OnDigitPressed);
    }

    grid_layout->addWidget(btn_mc, 0, 0); 
    grid_layout->addWidget(btn_mr, 0, 1); 
    grid_layout->addWidget(btn_ms, 0, 2); 
    grid_layout->addWidget(btn_clear, 0, 3);

    grid_layout->addWidget(digits[7], 1, 0); 
    grid_layout->addWidget(digits[8], 1, 1); 
    grid_layout->addWidget(digits[9], 1, 2); 
    grid_layout->addWidget(btn_div, 1, 3);

    grid_layout->addWidget(digits[4], 2, 0); 
    grid_layout->addWidget(digits[5], 2, 1); 
    grid_layout->addWidget(digits[6], 2, 2); 
    grid_layout->addWidget(btn_mul, 2, 3);

    grid_layout->addWidget(digits[1], 3, 0); 
    grid_layout->addWidget(digits[2], 3, 1); 
    grid_layout->addWidget(digits[3], 3, 2); 
    grid_layout->addWidget(btn_sub, 3, 3);

    grid_layout->addWidget(btn_sign, 4, 0);   
    grid_layout->addWidget(digits[0], 4, 1); 
    grid_layout->addWidget(btn_dot, 4, 2); 
    grid_layout->addWidget(btn_add, 4, 3);

    grid_layout->addWidget(btn_pow, 5, 0);    
    grid_layout->addWidget(btn_backspace, 5, 1); 
    grid_layout->addWidget(btn_equal, 5, 2, 1, 2);

    main_layout->addLayout(grid_layout);
}

QString MainWindow::RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') return text.mid(i);
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString &text) {
    if (text.isEmpty() || text == "-") {
        return "0";
    }
    if (text.startsWith('.')) {
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

void MainWindow::SetText(const QString& text) {
    input_number_ = NormalizeNumber(text);
    active_number_ = input_number_.toDouble(); 
    l_result->setText(input_number_);
}

void MainWindow::AddText(const QString& suffix) {
    SetText(input_number_ + suffix);
}

QString MainWindow::OpToString(Operation op) {
    switch(op) {
        case Operation::NO_OPERATION:   return "";
        case Operation::MULTIPLICATION: return "×";
        case Operation::DIVISION:       return "÷";
        case Operation::SUBTRACTION:    return "−";
        case Operation::ADDITION:       return "+";
        case Operation::POWER:          return "^";
        default:                        return ""; 
    }
}

void MainWindow::OnDigitPressed() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    if (is_result_shown_) {
        l_formula->clear();
        input_number_ = "";
        is_result_shown_ = false;
    }

    AddText(button->text());
}

void MainWindow::OnDotPressed() {
    if (input_number_.contains('.')) return;
    AddText(".");
}

void MainWindow::OnSignPressed() {
    if (is_result_shown_) {
        l_formula->clear();
        is_result_shown_ = false;
    }

    if (input_number_.isEmpty() && active_number_ != 0) {
        input_number_ = QString::number(active_number_);
    }

    if (input_number_ == "0" || input_number_.isEmpty()) {
        return; 
    }

    if (input_number_.startsWith('-')) {
        input_number_ = input_number_.mid(1);
    } else {
        input_number_ = "-" + input_number_;
    }

    SetText(input_number_);
}

void MainWindow::OnBackspacePressed() {
    if (input_number_.isEmpty()) return;

    input_number_.chop(1);
    if (input_number_.isEmpty() || input_number_ == "-") {
        input_number_ = "0";
    }
    SetText(input_number_);
}

void MainWindow::OnOperationPressed() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    Operation op = Operation::NO_OPERATION;
    QString text = button->text();
    if (text == "+") op = Operation::ADDITION;
    else if (text == "−") op = Operation::SUBTRACTION;
    else if (text == "×") op = Operation::MULTIPLICATION;
    else if (text == "÷") op = Operation::DIVISION;
    else if (text == "xʸ") op = Operation::POWER;

    SetOperation(op);
}

void MainWindow::SetOperation(Operation op) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }
    
    current_operation_ = op;
    is_result_shown_ = false; 
    
    QString formula_text = QString("%1 %2")
                           .arg(calculator_.GetNumber())
                           .arg(OpToString(op));
    l_formula->setText(formula_text);
    
    input_number_ = ""; 
}

void MainWindow::OnEqualPressed() {
    if (current_operation_ == Operation::NO_OPERATION) return;

    l_formula->setText(QString("%1 %2 %3 =")
                       .arg(calculator_.GetNumber())
                       .arg(OpToString(current_operation_))
                       .arg(active_number_));

    switch (current_operation_) {
        case Operation::ADDITION:       calculator_.Add(active_number_); break;
        case Operation::SUBTRACTION:    calculator_.Sub(active_number_); break;
        case Operation::MULTIPLICATION: calculator_.Mul(active_number_); break;
        case Operation::DIVISION:       calculator_.Div(active_number_); break;
        case Operation::POWER:          calculator_.Pow(active_number_); break;
        default: break;
    }

    active_number_ = calculator_.GetNumber();
    l_result->setText(QString::number(active_number_));
    
    input_number_ = ""; 
    current_operation_ = Operation::NO_OPERATION;
    is_result_shown_ = true; 
}

void MainWindow::OnMemoryPressed() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString text = button->text();

    if (text == "MS") {
        memory_value_ = active_number_;
        has_memory_ = true;
        l_memory->setText("M");
    } 
    else if (text == "MR") {
        if (has_memory_) {
            active_number_ = memory_value_;
            l_result->setText(QString::number(active_number_));
            input_number_ = ""; 
            is_result_shown_ = true; 
        }
    } 
    else if (text == "MC") {
        memory_value_ = 0.0;
        has_memory_ = false;
        l_memory->clear();
    }
}

void MainWindow::OnClearPressed() {
    current_operation_ = Operation::NO_OPERATION;
    l_formula->clear();
    calculator_.Set(0.0);
    is_result_shown_ = false; 
    SetText("0");
}
