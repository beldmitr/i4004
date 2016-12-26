#ifndef CPUMODEL_H
#define CPUMODEL_H

#include <QObject>
#include <QAbstractItemModel>

class CpuModel : public QAbstractItemModel
{
public:
    CpuModel();
    std::vector<int> cpuData;


    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex& parent) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex& child) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex& parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex& parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex& index, int role) const Q_DECL_OVERRIDE;
};

#endif // CPUMODEL_H
