#ifndef CIRCULARBUTTON_H
#define CIRCULARBUTTON_H

#include <QPushButton>

class CircularButton : public QPushButton {
  Q_OBJECT
  //  Q_PROPERTY(circleText WRITE setCircleText READ getCircleText);
  Q_PROPERTY(
      bool isToggle READ getToggled WRITE setToggled NOTIFY notify_toggled)

public:
  explicit CircularButton(QWidget *owner = Q_NULLPTR);
  //  void setCircleText(QString &text);

  //  QString getCircleText() const;
  // QWidget interface
  bool getToggled() const;
  void setToggled(bool toggled);

protected:
  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;

signals:
  void notify_toggled();

private:
  QString circleText;
  bool m_toggle;

  // QWidget interface
public:
  QSize sizeHint() const Q_DECL_OVERRIDE;
};

#endif // CIRCULARBUTTON_H
