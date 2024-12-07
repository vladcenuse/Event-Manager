#pragma once
#include <QAbstractTableModel>
#include "Event.h"
#include <vector>
class MyModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit MyModel(QObject* parent = nullptr);
	void setEvents(const std::vector<Event>& events);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
	std::vector<Event> events;


};

