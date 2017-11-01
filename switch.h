#pragma once

#include <QtWidgets>

void setActive(const unsigned char& act, const bool isActive);

class Switch : public QAbstractButton {
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush)

public:
    Switch(QWidget* parent = nullptr);
    Switch(const QBrush& brush, QWidget* parent = nullptr);

    void setID(const unsigned char& nID);
    QSize sizeHint() const override;

    QBrush brush() const {
        return _brush;
    }
    void setBrush(const QBrush &brsh) {
        _brush = brsh;
    }

    int offset() const {
        return _x;
    }
    void setOffset(int o) {
        _x = o;
        update();
    }

protected:
    void paintEvent(QPaintEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void enterEvent(QEvent*) override;

private:
    unsigned char ID;
    int _height;
    qreal _opacity;
    bool _switch;
    int _x, _y, _margin;
    QBrush _thumb, _track, _brush;
    QPropertyAnimation *_anim = nullptr;
};
