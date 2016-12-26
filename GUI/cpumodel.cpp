#include "cpumodel.h"

CpuModel::CpuModel()
{
    for (int i = 0; i < 10; i++)
    {
        cpuData.push_back(i);
    }

}

QModelIndex CpuModel::index(int row, int column, const QModelIndex& parent) const
{

}

QModelIndex CpuModel::parent(const QModelIndex& child) const
{

}

int CpuModel::rowCount(const QModelIndex& parent) const
{

}

int CpuModel::columnCount(const QModelIndex& parent) const
{

}

QVariant CpuModel::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role = Qt::DisplayRole)
    {

    }
}
