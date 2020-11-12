#ifndef AGENTLISTMODEL_H
#define AGENTLISTMODEL_H

#include <QModelIndex>
#include <QObject>
#include "city.h"
#include "agent.h"

class AgentsList : public QAbstractListModel
{
  Q_OBJECT
  QList<Agent> agents;
public:

};

#endif // AGENTLISTMODEL_H
