#include "indicator.h"
#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QIndicator indicator(6, true);
  indicator.setAnimationSpeed(300);
  indicator.setInitSmScaleSize(QSize(40, 30));
  indicator.setIncreValue(10);
  indicator.setDecreValue(10);
  indicator.setShowArrow(true);
  indicator.resize(400, 100);
  indicator.setVisible(true);
  return a.exec();
}
