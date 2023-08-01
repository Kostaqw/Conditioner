#pragma once

#include "RoundedGraphics.h"
#include <QMap>
#include <QPixmap>
#include "StatusEnums.h"
#include <QMouseEvent>

typedef QMap<CondeiStatus, QPixmap> StatusMap;

class RoundedGraphicsStatus : public RoundedGraphics
{
    Q_OBJECT
public:
    RoundedGraphicsStatus(int width, int height, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    StatusMap m_statusMap;
    CondeiStatus m_powerStatus;
    CondeiStatus m_signalStatus;
    CondeiStatus m_tempStatus;
    CondeiStatus m_fanStatus;

    void CreateStatusMap();

signals:
    void PowerIconClicked(const CondeiStatus &status);
    void FanIconClicked(const CondeiStatus &status);
};

