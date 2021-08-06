#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H

#include <QAbstractListModel>

struct Data {
    Data() {}
    Data( const int& value): value(value){}
    int value;
};

class MemoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole
    };

    explicit MemoryModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash<int, QByteArray> roleNames() const override;
public slots:
    void onMemoryClearButtonClicked(int row);
    void onMemoryStoreFunctionButtonClicked(int _data);
    void onMemoryAddButtonClicked(int row,int _data);
    void onMemorySubtractButtonClicked(int _row,int _data);
    void onClearAllMemoryButtonClicked();
    int modelCount();
private: //members
    QVector< Data > m_data;
};

#endif // MEMORYMODEL_H
