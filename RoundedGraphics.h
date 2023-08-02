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
    void SetHeaderFont(QFont *headerFon);
    void SetTextFont(QFont *textFont);
    ~RoundedGraphics();
protected:
    void paintEvent(QPaintEvent *event) override;
    void drawShadow(QPainter* painter, const QRect& rect);

    bool m_isHeader = false;

    QColor m_color;
    QColor m_shadowColor;

    QString m_text;
    QString m_header;

    QFont m_headerFont;
    QFont m_textFont;

private:



    int m_width;
    int m_height;

    void CreateShadow(QColor color);


};

