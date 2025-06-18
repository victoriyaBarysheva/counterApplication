#pragma once

#include "usecase/counter_usecase.h"
#include "usecase/frequency_usecase.h"

#include <QMainWindow>
#include <QPointer>

class QTableWidget;
class QLabel;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(std::shared_ptr<CounterUseCase> counterUseCase,
               std::shared_ptr<FrequencyUseCase> frequencyUseCase,
               QWidget* parent = nullptr);

private slots:
    void onAddClicked();
    void onRemoveClicked();
    void onSaveClicked();

    void updateTable();
    void updateFrequency();

private:
    // label
    QPointer<QLabel> m_frequencyLabel;

    // buttons
    QPointer<QPushButton> m_addButton;
    QPointer<QPushButton> m_removeButton;
    QPointer<QPushButton> m_saveButton;

    // table
    QPointer<QTableWidget> m_tableWidget;

    // timers
    QPointer<QTimer> m_tableUpdateTimer;
    QPointer<QTimer> m_frequencyUpdateTimer;

    // usecase
    std::shared_ptr<CounterUseCase> m_counterUseCase;
    std::shared_ptr<FrequencyUseCase> m_frequencyUseCase;
};
