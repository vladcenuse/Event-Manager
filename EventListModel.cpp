#include "EventListModel.h"

MyModel::MyModel(QObject* parent) : QAbstractTableModel{ parent }
{
}

void MyModel::setEvents(const std::vector<Event>& events)
{
	beginResetModel();
	this->events = events;
	endResetModel();
}

int MyModel::rowCount(const QModelIndex& parent) const
{
	return this->events.size();
}

int MyModel::columnCount(const QModelIndex& parent) const
{
	return 8;

}

QVariant MyModel::data(const QModelIndex& index, int role) const
{
	if (role != Qt::DisplayRole && role != Qt::EditRole)
		return {};

	const Event& event = this->events[index.row()];

	switch (index.column())
	{
		case 0:
			return QString::fromStdString(event.getTitle());
		case 1:
			return QString::fromStdString(event.getDescription());
		case 2:
			return QString::fromStdString(std::to_string(event.getDate().day));
		case 3:
			return QString::fromStdString(std::to_string(event.getDate().day));

		case 4:
			return QString::fromStdString(std::to_string(event.getTime().hour));
		case 5:
			return QString::fromStdString(std::to_string(event.getTime().minute));
		case 6:
			return QString::fromStdString(std::to_string(event.getNumberOfPeople()));
		case 7:
			return QString::fromStdString(event.getLink());
		default:
			return QVariant{};

	}

}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return {};

	if (orientation == Qt::Horizontal)
	{
		switch (section)
		{
		case 0:
			return "Title";
		case 1:
			return "Description";
		case 2:
			return "Day";
		case 3:
			return "Month";
		case 4:
			return "Hour";
		case 5:
			return "Minute";
		case 6:
			return "Number of people";
		case 7:
			return "Link";
		default:
			return QVariant();
		}
	}
	else if (orientation == Qt::Vertical)
	{
		return section + 1;
	}

	return QVariant();
}


