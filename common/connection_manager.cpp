#include <QObject>
#include <QList>

#include "connection_manager.h"

ConnectionManager::ConnectionManager(const QList<QObject *> &inputs, const QList<QObject *> &strategies)
{
    for (const auto &strategy : strategies) {
        if (strategy != NULL) {
            for (const auto &input : inputs) {
                if (input != NULL) {
                    auto c = QObject::connect(input, SIGNAL(newMarketData(QString,uint,double,int,double,int,double,int)),
                                              strategy, SLOT(onMarketData(QString,uint,double,int,double,int,double,int)));
                    if (c) {
                        connections << c;
                    }
                }
            }
        }
    }
}

ConnectionManager::~ConnectionManager()
{
    for (const auto &connection : connections) {
        QObject::disconnect(connection);
    }
}
