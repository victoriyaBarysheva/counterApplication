#include "mainwindow.h"

#include "counter.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(std::shared_ptr<CounterUseCase> counterUseCase,
                       std::shared_ptr<FrequencyUseCase> frequencyUseCase,
                       QWidget* parent) :
    QMainWindow(parent),
    m_counterUseCase(std::move(counterUseCase)),
    m_frequencyUseCase(std::move(frequencyUseCase))
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    m_tableWidget = new QTableWidget(this);
    m_tableWidget->setColumnCount(2);
    m_tableWidget->setHorizontalHeaderLabels(QStringList() << "ID"
                                                           << "Value");
    m_tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    m_frequencyLabel = new QLabel("Frequency: 0.0", this);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    m_addButton = new QPushButton("Add", this);
    m_removeButton = new QPushButton("Remove", this);
    m_saveButton = new QPushButton("Save", this);
    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_removeButton);
    buttonLayout->addWidget(m_saveButton);

    mainLayout->addWidget(m_tableWidget);
    mainLayout->addWidget(m_frequencyLabel);
    mainLayout->addLayout(buttonLayout);
    setCentralWidget(centralWidget);

    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(m_removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);
    connect(m_saveButton, &QPushButton::clicked, this, &MainWindow::onSaveClicked);

    m_tableUpdateTimer = new QTimer(this);
    connect(m_tableUpdateTimer, &QTimer::timeout, this, &MainWindow::updateTable);
    m_tableUpdateTimer->start(200);

    m_frequencyUpdateTimer = new QTimer(this);
    connect(m_frequencyUpdateTimer, &QTimer::timeout, this, &MainWindow::updateFrequency);
    m_frequencyUpdateTimer->start(1000);
}

void MainWindow::onAddClicked()
{
    m_counterUseCase->append();
}

void MainWindow::onRemoveClicked()
{
    int currentRow = m_tableWidget->currentRow();
    auto item = m_tableWidget->itemAt(0, currentRow);
    if (item)
    {
        m_counterUseCase->remove(item->text());
    }
}

void MainWindow::onSaveClicked()
{
    m_counterUseCase->save();
}

void MainWindow::updateTable()
{
    auto counters = m_counterUseCase->counters();

    m_tableWidget->setRowCount(counters.size());
    for (int i = 0; i < static_cast<int>(counters.size()); ++i)
    {
        QTableWidgetItem* idItem = m_tableWidget->item(i, 0);
        if (!idItem)
        {
            idItem = new QTableWidgetItem();
            m_tableWidget->setItem(i, 0, idItem);
        }
        auto id = counters[i].m_id;
        idItem->setText(id);

        QTableWidgetItem* valueItem = m_tableWidget->item(i, 1);
        if (!valueItem)
        {
            valueItem = new QTableWidgetItem();
            m_tableWidget->setItem(i, 1, valueItem);
        }
        valueItem->setText(QString::number(counters[i].m_value));
    }
}

void MainWindow::updateFrequency()
{
    auto _frequency = m_frequencyUseCase->frequency();
    m_frequencyLabel->setText(QString("Frequency: %1").arg(_frequency, 0, 'f', 2));
}
