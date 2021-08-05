#include "memorymodel.h"

MemoryModel::MemoryModel(QObject *parent) : QAbstractListModel(parent)
{
    m_data << Data(1)
           <<Data(2)
          <<Data(3);
}

int MemoryModel::rowCount( const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_data.count();
}

QVariant MemoryModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
        return QVariant();

    const Data &data = m_data.at(index.row());
    if ( role == NameRole ){
        return data.value;
    }
    else
        return QVariant();
}

QHash<int, QByteArray> MemoryModel::roleNames() const
{
    static QHash<int, QByteArray> mapping {
        {NameRole, "name"}
    };
    return mapping;
}

void MemoryModel::duplicateData(int row)
{
    if (row < 0 || row >= m_data.count())
        return;

    const Data data = m_data[row];
    const int rowOfInsert = row + 1;

    beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
    m_data.insert(rowOfInsert, data);
    endInsertRows();
}

void MemoryModel::removeData(int row)
{
    if (row < 0 || row >= m_data.count())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
}

void MemoryModel::addNewData(int _data)
{
    const Data data = _data;
    const int rowOfInsert = m_data.count();
    beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
    m_data.insert(rowOfInsert, data);
    endInsertRows();
}

void MemoryModel::onMemoryAddButtonClicked(int _row, int _data)
{
    Data currentData = m_data[_row];
    currentData.value = currentData.value + Data(_data).value;
    beginRemoveRows(QModelIndex(), _row, _row);
    m_data.removeAt(_row);
    endRemoveRows();
    beginInsertRows(QModelIndex(), _row, _row);
    m_data.insert(_row, currentData);
    endInsertRows();
}

void MemoryModel::onMemorySubtractButtonClicked(int _row, int _data)
{
    Data currentData = m_data[_row];
    currentData.value = currentData.value - Data(_data).value;
    beginRemoveRows(QModelIndex(), _row, _row);
    m_data.removeAt(_row);
    endRemoveRows();
    beginInsertRows(QModelIndex(), _row, _row);
    m_data.insert(_row, currentData);
    endInsertRows();
}
