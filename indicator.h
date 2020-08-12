#ifndef INDICATOR_H
#define INDICATOR_H

#include <QGestureEvent>
#include <QMainWindow>
#include <QWidget>
class QSignalMapper;
class CircularButton;

class QIndicator : public QMainWindow {
  Q_OBJECT
  Q_PROPERTY(int animationSpeed READ animationSpeed WRITE setAnimationSpeed
                 NOTIFY animationSpeedChanged)
  Q_PROPERTY(QSize initSmScaleSize READ initSmScaleSize WRITE setInitSmScaleSize
                 NOTIFY initSmScaleSizeChanged)
  Q_PROPERTY(int increValue READ increValue WRITE setIncreValue NOTIFY
                 increValueChanged)
  Q_PROPERTY(int decreValue READ decreValue WRITE setDecreValue NOTIFY
                 decreValueChanged)
  Q_PROPERTY(int pages READ pages WRITE setPages NOTIFY pagesChanged)

  Q_PROPERTY(
      bool showArrow READ showArrow WRITE setShowArrow NOTIFY showArrowChanged)
  Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY
                 currentIndexChanged)
public:
  explicit QIndicator(int pages, bool isArrow = false,
                      QWidget *parent = nullptr);
  bool toggle() const;
  void setToggle(bool toggle);

  int animationSpeed() const;
  void setAnimationSpeed(int speed);
  QSize initSmScaleSize() const;
  void setInitSmScaleSize(const QSize size);
  int increValue() const;
  void setIncreValue(int value);
  int decreValue() const;
  void setDecreValue(int value);
  int pages() const;
  void setPages(int pages);
  bool showArrow() const;
  void setShowArrow(bool isEnable);
  int currentIndex() const;
  void setCurrentIndex(const auto index);
  QVector<CircularButton *> getArrayOfIndicator() const;
  int indexOf(CircularButton *);
signals:
  void clicked(const QString &text);
  void animationSpeedChanged(int speed);
  void initSmScaleSizeChanged(int size);
  void increValueChanged();
  void decreValueChanged();
  void pagesChanged();
  void showArrowChanged();
  void currentIndexChanged();
private slots:
  void onClicked(const QString &text);
  void onIndicatorClicked();
  void handleLeftClicked();
  void handleRightClicked();

private:
  void animationScaleSm();
  void animationSCaleBg();

  QVector<CircularButton *> arrayOfIndicator;
  int pre_index;
  bool m_toggle;
  int m_animationSpeed;
  int m_incre;
  int m_decre;
  int m_pages;
  int m_currentIndex;
  bool m_arrow;
  QSize m_initSmScale;
};

#endif // INDICATOR_H
