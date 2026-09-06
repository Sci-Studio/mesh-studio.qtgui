#include "AxisIndicator.hpp"

#include <QPainter>
#include <QPolygonF>
#include <QTransform>
#include <QVector2D>

AxisIndicator::AxisIndicator(QWidget* parent) : QWidget(parent) {
    // Keep extra padding so arrowheads/labels never clip while rotating.
    setFixedSize(88, 88);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
}

void AxisIndicator::setRotationDegrees(float rotationDegrees) {
    mRotationDegrees = rotationDegrees;
    update();
}

void AxisIndicator::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const QPointF origin(width() * 0.5, height() * 0.5);
    const qreal axisLength = 26.0;
    const QPointF xEnd(origin.x() + axisLength, origin.y());
    const QPointF yEnd(origin.x(), origin.y() - axisLength);

    QTransform rotation;
    rotation.translate(origin.x(), origin.y());
    rotation.rotate(-mRotationDegrees);
    rotation.translate(-origin.x(), -origin.y());

    const QPointF xTip = rotation.map(xEnd);
    const QPointF yTip = rotation.map(yEnd);

    QPen xPen(QColor("#e54033"));
    xPen.setWidthF(1.8);
    painter.setPen(xPen);
    painter.drawLine(origin, xTip);

    QPen yPen(QColor("#33c759"));
    yPen.setWidthF(1.8);
    painter.setPen(yPen);
    painter.drawLine(origin, yTip);

    const auto drawArrowHead = [&painter](const QPointF& base, const QPointF& tip, const QColor& color) {
        const QVector2D direction(tip - base);
        if (direction.length() < 1e-3f) {
            return;
        }
        const QVector2D n = direction.normalized();
        const QVector2D p(-n.y(), n.x());
        const QPointF a = tip;
        const QPointF b = tip - (n.toPointF() * 5.0) + (p.toPointF() * 3.0);
        const QPointF c = tip - (n.toPointF() * 5.0) - (p.toPointF() * 3.0);

        painter.setPen(Qt::NoPen);
        painter.setBrush(color);
        painter.drawPolygon(QPolygonF{a, b, c});
    };

    drawArrowHead(origin, xTip, QColor("#e54033"));
    drawArrowHead(origin, yTip, QColor("#33c759"));

    painter.setPen(QColor("#e54033"));
    painter.setFont(QFont("Inter", 10, QFont::DemiBold));
    painter.drawText(QRectF(xTip + QPointF(4.0, -6.0), QSizeF(12.0, 12.0)), "X");

    painter.setPen(QColor("#33c759"));
    painter.drawText(QRectF(yTip + QPointF(-7.0, -10.0), QSizeF(12.0, 12.0)), "Y");
}
