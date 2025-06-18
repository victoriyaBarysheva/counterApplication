#include "presentation/mainwindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    auto data = std::make_shared<DataBase>("counters.db");
    data->initialize();

    auto counterQueryData = std::make_shared<CounterQueryData>(data);
    counterQueryData->initialize();

    auto counterData = std::make_shared<CounterData>(counterQueryData);
    auto counterUseCase = std::make_shared<CounterUseCase>(counterData);
    auto frequencyUseCase = std::make_shared<FrequencyUseCase>(counterData);

    QSharedPointer<MainWindow> view(new MainWindow(counterUseCase, frequencyUseCase));
    view->resize(600, 400);
    view->show();

    return app.exec();
}
