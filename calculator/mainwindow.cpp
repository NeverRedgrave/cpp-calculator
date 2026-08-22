#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <unordered_map>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (ui->btn_sub) ui->btn_sub->setText("−");
    if (ui->btn_div) ui->btn_div->setText("÷");
    if (ui->btn_mul) ui->btn_mul->setText("×");
    if (ui->btn_pow) ui->btn_pow->setText("xʸ");

    if (ui->btn_plus_minus) ui->btn_plus_minus->setText("±");
    else {
        QPushButton* pm = this->findChild<QPushButton*>("btn_plus_minus");
        if (!pm) pm = this->findChild<QPushButton*>("tb_plus_minus");
        if (pm) pm->setText("±");
    }

    if (ui->btn_backspace) ui->btn_backspace->setText("⌫");
    else {
        QPushButton* bs = this->findChild<QPushButton*>("btn_backspace");
        if (!bs) bs = this->findChild<QPushButton*>("tb_backspace");
        if (bs) bs->setText("⌫");
    }

    for (auto* btn : this->findChildren<QPushButton*>()) {
        if (btn->text() == "-") btn->setText("−");
        else if (btn->text() == "/") btn->setText("÷");
        else if (btn->text() == "*") btn->setText("×");
        else if (btn->text() == "+-" || btn->text() == "+/-" || btn->text() == "+ / -") btn->setText("±");
        else if (btn->text() == "^") btn->setText("xʸ");
        else if (btn->text() == "Backspace" || btn->text() == "Delete" || btn->text() == "Clear") btn->setText("⌫");
    }

    connect(ui->btn_0, &QPushButton::clicked, [this]() { if (digit_cb_) digit_cb_(0); });
    connect(ui->btn_1, &QPushButton::clicked, [this]() { if (digit_cb_) digit_cb_(1); });
    connect(ui->btn_2, &QPushButton::clicked, [this]() { if (digit_cb_) digit_cb_(2); });
    connect(ui->btn_3, &QPushButton::clicked, [this]() { if (digit_cb_) digit_cb_(3); });
    connect(ui->btn_4, &QPushButton::clicked, [this]() { if (digit_cb_) digit_cb_(4); });
    connect(ui->btn_5, &QPushButton::clicked, [this]() { if (digit_cb_) digit_cb_(5); });
    connect(ui->btn_6, &QPushButton::clicked, [this]() { if (digit_cb_) digit_cb_(6); });
    connect(ui->btn_7, &QPushButton::clicked, [this]() { if (digit_cb_) digit_cb_(7); });
    connect(ui->btn_8, &QPushButton::clicked, [this]() { if (digit_cb_) digit_cb_(8); });
    connect(ui->btn_9, &QPushButton::clicked, [this]() { if (digit_cb_) digit_cb_(9); });

    connect(ui->btn_add, &QPushButton::clicked, [this]() { if (operation_cb_) operation_cb_(Operation::ADDITION); });
    connect(ui->btn_sub, &QPushButton::clicked, [this]() { if (operation_cb_) operation_cb_(Operation::SUBTRACTION); });
    connect(ui->btn_mul, &QPushButton::clicked, [this]() { if (operation_cb_) operation_cb_(Operation::MULTIPLICATION); });
    connect(ui->btn_div, &QPushButton::clicked, [this]() { if (operation_cb_) operation_cb_(Operation::DIVISION); });
    connect(ui->btn_pow, &QPushButton::clicked, [this]() { if (operation_cb_) operation_cb_(Operation::POWER); });

    connect(ui->btn_equals, &QPushButton::clicked, [this]() { if (control_cb_) control_cb_(ControlKey::EQUALS); });
    connect(ui->btn_clear, &QPushButton::clicked, [this]() { if (control_cb_) control_cb_(ControlKey::CLEAR); });
    connect(ui->btn_plus_minus, &QPushButton::clicked, [this]() { if (control_cb_) control_cb_(ControlKey::PLUS_MINUS); });
    connect(ui->btn_backspace, &QPushButton::clicked, [this]() { if (control_cb_) control_cb_(ControlKey::BACKSPACE); });
    connect(ui->tb_extra, &QPushButton::clicked, [this]() { if (control_cb_) control_cb_(ControlKey::EXTRA_KEY); });

    connect(ui->btn_ms, &QPushButton::clicked, [this]() { if (control_cb_) control_cb_(ControlKey::MEM_SAVE); });
    connect(ui->btn_ml, &QPushButton::clicked, [this]() { if (control_cb_) control_cb_(ControlKey::MEM_LOAD); });
    connect(ui->btn_mc, &QPushButton::clicked, [this]() { if (control_cb_) control_cb_(ControlKey::MEM_CLEAR); });
    connect(ui->cmb_controller, &QComboBox::currentIndexChanged, [this]() {
        if (!controller_cb_) {
            return;
        }
        static const std::unordered_map<std::string, ControllerType> type_mapping = {
            {"uint8_t",  ControllerType::UINT8_T},
            {"int",      ControllerType::INT},
            {"int64_t",  ControllerType::INT64_T},
            {"size_t",   ControllerType::SIZE_T},
            {"double",   ControllerType::DOUBLE},
            {"float",    ControllerType::FLOAT},
            {"Rational", ControllerType::RATIONAL}
        };

        std::string type_str = ui->cmb_controller->currentText().trimmed().toStdString();
        
        auto it = type_mapping.find(type_str);
        if (it != type_mapping.end()) {
            controller_cb_(it->second);
        } else {
            controller_cb_(ControllerType::DOUBLE); // Значение по умолчанию, если строка не распознана
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key.has_value()) {
        ui->tb_extra->show();
        ui->tb_extra->setText(QString::fromStdString(*key));
    } else {
        ui->tb_extra->hide();
    }
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb) {
    digit_cb_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
    operation_cb_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
    control_cb_ = cb;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb) {
    controller_cb_ = cb;
}
