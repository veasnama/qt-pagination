#include "circularbutton.h"
#include <QPainter>
CircularButton::CircularButton(QWidget *owner)
    : circleText{""}, m_toggle(false) {
  //  circleText = text;
}

bool CircularButton::getToggled() const { return m_toggle; }

void CircularButton::setToggled(bool toggled) { m_toggle = toggled; }

// void CircularButton::setCircleText(QString &text) { circleText = text; }

// QString CircularButton::getCircleText() const { return circleText; }

void CircularButton::paintEvent(QPaintEvent *event) {

  // Do not paint base implementation -> no styles are applied
  QColor background = isDown() ? QColor("grey") : QColor("lightgrey");
  //    QColor background = QColor("grey");
  int diameter = qMin(height(), width());
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, false);
  painter.translate(width() / 2, height() / 2);

  painter.setPen(QPen(QColor("black"), 2));
  painter.setBrush(QBrush(background));
  painter.drawEllipse(QRect(-diameter / 2, -diameter / 2, diameter, diameter));
}

void CircularButton::resizeEvent(QResizeEvent *event) {
  QPushButton::resizeEvent(event);
  int diameter = qMin(height(), width()) + 4;
  int xOff = (width() - diameter) / 2;
  int yOff = (height() - diameter) / 2;
  setMask(QRegion(xOff, yOff, diameter, diameter, QRegion::Ellipse));
}

QSize CircularButton::sizeHint() const { return QSize(50, 40); }
