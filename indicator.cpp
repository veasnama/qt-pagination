#include "indicator.h"
#include "circularbutton.h"
#include <QDebug>
#include <QGesture>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSignalMapper>
#include <QToolButton>

QIndicator::QIndicator(int pages, bool isArrow, QWidget *parent)
    : QMainWindow(parent), arrayOfIndicator{}, m_toggle(false),
      m_pages(pages), m_arrow{isArrow} {
  setVisible(false);
  QHBoxLayout *centralGrid = new QHBoxLayout;
  QWidget *central = new QWidget(this);
  arrayOfIndicator.reserve(m_pages);
  if (m_arrow) {
    QToolButton *arrowLeft = new QToolButton;
    arrowLeft->setIcon(QIcon::fromTheme(tr("arrow-left")));
    arrowLeft->setAutoRaise(true);
    centralGrid->addWidget(arrowLeft);
    connect(arrowLeft, &QAbstractButton::clicked, this,
            &QIndicator::handleLeftClicked);
  }
  for (int i = 0; i < m_pages; i++) {

    CircularButton *button = new CircularButton(this);
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    button->setText(tr("Button %1").arg(i));
    connect(button, &CircularButton::clicked, this,
            &QIndicator::onIndicatorClicked);
    arrayOfIndicator.push_back(button);
    centralGrid->addWidget(button);
    //    signalMapper->setMapping(button, list[i]);
  }

  if (m_arrow) {
    QToolButton *arrowRight = new QToolButton;
    arrowRight->setIcon(QIcon::fromTheme(tr("arrow-right")));
    arrowRight->setAutoRaise(true);
    centralGrid->addWidget(arrowRight);
    connect(arrowRight, &QToolButton::clicked, this,
            &QIndicator::handleRightClicked);
  }
  arrayOfIndicator.first()->setMaximumSize(50, 30);
  pre_index = 0;
  connect(this, &QIndicator::clicked, this, &QIndicator::onClicked);
  central->setLayout(centralGrid);
  setCentralWidget(central);
}

void QIndicator::onClicked(const QString &text) { qDebug() << text; }

void QIndicator::onIndicatorClicked() {
  auto *indicator = qobject_cast<CircularButton *>(sender());
  qInfo() << indexOf(indicator);
  m_currentIndex = arrayOfIndicator.indexOf(indicator);
  setCurrentIndex(m_currentIndex);
  if (pre_index == currentIndex()) {
    return;
  }
  if (pre_index == 0) {
    arrayOfIndicator[pre_index]->setMaximumSize(
        m_initSmScale.width() + m_incre, m_initSmScale.height() + m_incre);
    arrayOfIndicator[pre_index]->move(arrayOfIndicator[pre_index]->x(),
                                      arrayOfIndicator[pre_index]->y());
  }
  QPropertyAnimation *animation =
      new QPropertyAnimation(arrayOfIndicator[m_currentIndex], "geometry");
  animation->setDuration(m_animationSpeed);
  animation->setStartValue(QRect(QPoint(arrayOfIndicator[m_currentIndex]->x(),
                                        arrayOfIndicator[m_currentIndex]->y()),
                                 arrayOfIndicator[m_currentIndex]->size()));
  animation->setEndValue(
      QRect(QPoint(arrayOfIndicator[m_currentIndex]->x(),
                   arrayOfIndicator[m_currentIndex]->y()),
            QSize(arrayOfIndicator[m_currentIndex]->width() - decreValue(),
                  arrayOfIndicator[m_currentIndex]->height() - decreValue())));
  QPropertyAnimation *animation1 =
      new QPropertyAnimation(arrayOfIndicator[pre_index], "geometry");
  animation1->setDuration(m_animationSpeed);
  animation1->setStartValue(QRect(QPoint(arrayOfIndicator[pre_index]->x(),
                                         arrayOfIndicator[pre_index]->y()),
                                  arrayOfIndicator[pre_index]->size()));

  animation1->setEndValue(
      QRect(QPoint(arrayOfIndicator[pre_index]->x(),
                   arrayOfIndicator[pre_index]->y()),
            QSize(arrayOfIndicator[pre_index]->width() + m_incre,
                  arrayOfIndicator[pre_index]->height() + m_incre)));
  QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;

  animgroup->addAnimation(animation);
  animgroup->addAnimation(animation1);
  animgroup->start(QParallelAnimationGroup::DeletionPolicy::DeleteWhenStopped);
  pre_index = m_currentIndex;
  indicator->setToggled(toggle());
}

void QIndicator::handleRightClicked() {

  if (currentIndex() == arrayOfIndicator.length() - 1) {
    setCurrentIndex(arrayOfIndicator.length() - 1);
  }

  if (currentIndex() <= arrayOfIndicator.length()) {
    setCurrentIndex(currentIndex() + 1);
  }
  if (currentIndex() == arrayOfIndicator.length()) {
    setCurrentIndex(0);
  }
  if (pre_index == currentIndex()) {
    return;
  }
  if (pre_index == 0) {
    arrayOfIndicator[pre_index]->setMaximumSize(
        m_initSmScale.width() + m_incre, m_initSmScale.height() + m_incre);
    arrayOfIndicator[pre_index]->move(arrayOfIndicator[pre_index]->x(),
                                      arrayOfIndicator[pre_index]->y());
  }
  QPropertyAnimation *animation =
      new QPropertyAnimation(arrayOfIndicator[m_currentIndex], "geometry");
  animation->setDuration(m_animationSpeed);
  animation->setStartValue(QRect(QPoint(arrayOfIndicator[m_currentIndex]->x(),
                                        arrayOfIndicator[m_currentIndex]->y()),
                                 arrayOfIndicator[m_currentIndex]->size()));
  animation->setEndValue(
      QRect(QPoint(arrayOfIndicator[m_currentIndex]->x(),
                   arrayOfIndicator[m_currentIndex]->y()),
            QSize(arrayOfIndicator[m_currentIndex]->width() - decreValue(),
                  arrayOfIndicator[m_currentIndex]->height() - decreValue())));
  QPropertyAnimation *animation1 =
      new QPropertyAnimation(arrayOfIndicator[pre_index], "geometry");
  animation1->setDuration(m_animationSpeed);
  animation1->setStartValue(QRect(QPoint(arrayOfIndicator[pre_index]->x(),
                                         arrayOfIndicator[pre_index]->y()),
                                  arrayOfIndicator[pre_index]->size()));

  animation1->setEndValue(
      QRect(QPoint(arrayOfIndicator[pre_index]->x(),
                   arrayOfIndicator[pre_index]->y()),
            QSize(arrayOfIndicator[pre_index]->width() + m_incre,
                  arrayOfIndicator[pre_index]->height() + m_incre)));
  QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;

  animgroup->addAnimation(animation);
  animgroup->addAnimation(animation1);
  animgroup->start(QParallelAnimationGroup::DeletionPolicy::DeleteWhenStopped);

  if (pre_index == arrayOfIndicator.length() - 1) {
    pre_index = arrayOfIndicator.length() - 1;
  }
  if (pre_index <= arrayOfIndicator.length()) {
    pre_index++;
  }
  if (pre_index == arrayOfIndicator.length()) {
    pre_index = 0;
  }
}

void QIndicator::handleLeftClicked() {

  if (pre_index > 0) { // OK
    pre_index--;
  }
  if (pre_index < 0) {
    pre_index = arrayOfIndicator.length() - 1;
  }
  if (pre_index == currentIndex()) {
    pre_index = arrayOfIndicator.length() - 1;
  }

  if (currentIndex() < 0) {
    setCurrentIndex(arrayOfIndicator.length() - 1);
  }

  if (currentIndex() == 0) {
    arrayOfIndicator[currentIndex()]->setMaximumSize(
        m_initSmScale.width() + m_incre, m_initSmScale.height() + m_incre);
  }

  QPropertyAnimation *animation =
      new QPropertyAnimation(arrayOfIndicator[currentIndex()], "geometry");
  animation->setDuration(m_animationSpeed);
  animation->setStartValue(QRect(QPoint(arrayOfIndicator[currentIndex()]->x(),
                                        arrayOfIndicator[currentIndex()]->y()),
                                 arrayOfIndicator[currentIndex()]->size()));
  animation->setEndValue(
      QRect(QPoint(arrayOfIndicator[currentIndex()]->x(),
                   arrayOfIndicator[currentIndex()]->y()),
            QSize(arrayOfIndicator[currentIndex()]->width() + increValue(),
                  arrayOfIndicator[currentIndex()]->height() + increValue())));
  QPropertyAnimation *animation1 =
      new QPropertyAnimation(arrayOfIndicator[pre_index], "geometry");
  animation1->setDuration(m_animationSpeed);
  animation1->setStartValue(QRect(QPoint(arrayOfIndicator[pre_index]->x(),
                                         arrayOfIndicator[pre_index]->y()),
                                  arrayOfIndicator[pre_index]->size()));

  animation1->setEndValue(
      QRect(QPoint(arrayOfIndicator[pre_index]->x(),
                   arrayOfIndicator[pre_index]->y()),
            QSize(arrayOfIndicator[pre_index]->width() - decreValue(),
                  arrayOfIndicator[pre_index]->height() - decreValue())));
  QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;

  animgroup->addAnimation(animation);
  animgroup->addAnimation(animation1);
  animgroup->start(QParallelAnimationGroup::DeletionPolicy::DeleteWhenStopped);

  if (pre_index == 0) {
    pre_index--;
  }
  if (currentIndex() > 0) {
    setCurrentIndex(currentIndex() - 1);
  }

  if (currentIndex() == 0 && pre_index < 0) {
    setCurrentIndex(0);
    return;
  }
  if (currentIndex() == 0) {
    setCurrentIndex(currentIndex() - 1);
  }
  if (currentIndex() < 0) {
    setCurrentIndex(arrayOfIndicator.length() - 1);
  }
}

void QIndicator::animationScaleSm() {
  QPropertyAnimation *animation =
      new QPropertyAnimation(arrayOfIndicator[m_currentIndex], "geometry");
  animation->setDuration(m_animationSpeed);
  animation->setStartValue(QRect(QPoint(arrayOfIndicator[m_currentIndex]->x(),
                                        arrayOfIndicator[m_currentIndex]->y()),
                                 arrayOfIndicator[m_currentIndex]->size()));
  animation->setEndValue(
      QRect(QPoint(arrayOfIndicator[m_currentIndex]->x(),
                   arrayOfIndicator[m_currentIndex]->y()),
            QSize(arrayOfIndicator[m_currentIndex]->width() - decreValue(),
                  arrayOfIndicator[m_currentIndex]->height() - decreValue())));
}

void QIndicator::animationSCaleBg() {

  QPropertyAnimation *animation1 =
      new QPropertyAnimation(arrayOfIndicator[pre_index], "geometry");
  animation1->setDuration(m_animationSpeed);
  animation1->setStartValue(QRect(QPoint(arrayOfIndicator[pre_index]->x(),
                                         arrayOfIndicator[pre_index]->y()),
                                  arrayOfIndicator[pre_index]->size()));

  animation1->setEndValue(
      QRect(QPoint(arrayOfIndicator[pre_index]->x(),
                   arrayOfIndicator[pre_index]->y()),
            QSize(arrayOfIndicator[pre_index]->width() + m_incre,
                  arrayOfIndicator[pre_index]->height() + m_incre)));
}

bool QIndicator::toggle() const { return m_toggle; }

void QIndicator::setToggle(bool toggle) { m_toggle = toggle; }

int QIndicator::animationSpeed() const { return m_animationSpeed; }

void QIndicator::setAnimationSpeed(int speed) { m_animationSpeed = speed; }

QSize QIndicator::initSmScaleSize() const { return m_initSmScale; }

void QIndicator::setInitSmScaleSize(const QSize size) { m_initSmScale = size; }

int QIndicator::increValue() const { return m_incre; }

void QIndicator::setIncreValue(int value) { m_incre = value; }

int QIndicator::decreValue() const { return m_decre; }

void QIndicator::setDecreValue(int value) { m_decre = value; }

int QIndicator::pages() const { return m_pages; }

void QIndicator::setPages(int pages) { m_pages = pages; }

bool QIndicator::showArrow() const { return m_arrow; }

void QIndicator::setShowArrow(bool isEnable) { m_arrow = isEnable; }

int QIndicator::currentIndex() const { return m_currentIndex; }

void QIndicator::setCurrentIndex(const auto index) { m_currentIndex = index; }

QVector<CircularButton *> QIndicator::getArrayOfIndicator() const {
  return arrayOfIndicator;
}

int QIndicator::indexOf(CircularButton *button) {
  return arrayOfIndicator.indexOf(button);
}
