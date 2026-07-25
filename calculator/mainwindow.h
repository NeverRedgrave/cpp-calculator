#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include "calculator.h"

enum class Operation {
    NO_OPERATION,
    MULTIPLICATION,
    DIVISION,
    SUBTRACTION,
    ADDITION,
    POWER,
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void OnDigitPressed();
    void OnDotPressed();
    void OnSignPressed();
    void OnBackspacePressed();
    void OnEqualPressed();
    void OnClearPressed();
    void OnMemoryPressed();
    void OnOperationPressed();

private:
    void SetupUi();
    void SetText(const QString& text);
    void AddText(const QString& suffix);
    void SetOperation(Operation op);
    QString OpToString(Operation op);
    QString RemoveTrailingZeroes(const QString &text);
    QString NormalizeNumber(const QString &text);
    QLabel* l_memory;
    QLabel* l_result;
    QLabel* l_formula;
    QString input_number_;
    double active_number_ = 0.0;
    Operation current_operation_ = Operation::NO_OPERATION;
    Calculator calculator_;
    double memory_value_ = 0.0;
    bool has_memory_ = false;
};

#endif 