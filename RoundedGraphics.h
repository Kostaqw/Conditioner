#pragma once
#include <QGraphicsView>

class RoundedGraphics : public QWidget {
public:
    RoundedGraphics(int width, int height, QWidget *parent = nullptr);
    RoundedGraphics(int width, int height, const QColor& color, QWidget *parent = nullptr);
    void SetText(QString text);
    void SetText(qreal value);
    void SetColor(QColor color);
    void SetColor(QColor color, QColor shadow);
    void SetHeader(QString header);

protected:
    void paintEvent(QPaintEvent *event) override;
    void drawShadow(QPainter* painter, const QRect& rect);

private:
    bool m_isHeader = false;

    int m_width;
    int m_height;

    QString m_text;
    QString m_header;

    QColor m_color;
    QColor m_shadowColor;

    void CreateShadow(QColor color);
};

