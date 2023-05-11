#include <QtWidgets>

class LightWidget : public QWidget {
 Q_OBJECT
  Q_PROPERTY(bool on READ isOn WRITE setOn)
 public:
  explicit LightWidget(const QColor &color, QWidget *parent = nullptr)
      : QWidget(parent), m_color(color), m_on(false) {}

  bool isOn() const { return m_on; }
  void setOn(bool on) {
    if (on == m_on)
      return;
    m_on = on;
    // 触发重绘事件
    update();
  }

 public slots:
  void turnOff() { setOn(false); }
  void turnOn() { setOn(true); }

 protected:
  void paintEvent(QPaintEvent *) override {
    if (!m_on)
      return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_color);
    painter.drawEllipse(0, 0, width(), height());
  }

 private:
  QColor m_color;
  // 控制是否重绘 自身 widget
  bool m_on;
};

QState *createLightState(LightWidget *light, int duration, QState *parent = nullptr) {
  auto *lightState = new QState(parent);

  // 将 timer 内嵌到 状态机中
  auto *timer = new QTimer(lightState);
  timer->setInterval(duration);
  timer->setSingleShot(true);

  auto *timing = new QState(lightState);
  auto *done = new QFinalState(lightState);
  timing->addTransition(timer, SIGNAL(timeout()), done);

  QObject::connect(timing, SIGNAL(entered()), light, SLOT(turnOn()));
  QObject::connect(timing, SIGNAL(exited()), light, SLOT(turnOff()));

  QObject::connect(timing, SIGNAL(entered()), timer, SLOT(start()));

  lightState->setInitialState(timing);

  return lightState;
}

class TrafficLightWidget : public QWidget {
 public:
  explicit TrafficLightWidget(QWidget *parent = nullptr)
      : QWidget(parent) {
    auto *vbox = new QVBoxLayout(this);

    m_red = new LightWidget(Qt::red);
    vbox->addWidget(m_red);
    m_yellow = new LightWidget(Qt::yellow);
    vbox->addWidget(m_yellow);
    m_green = new LightWidget(Qt::green);
    vbox->addWidget(m_green);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    setPalette(pal);
    setAutoFillBackground(true);
  }

  LightWidget *redLight() const { return m_red; }
  LightWidget *yellowLight() const { return m_yellow; }
  LightWidget *greenLight() const { return m_green; }

 private:
  LightWidget *m_red;
  LightWidget *m_yellow;
  LightWidget *m_green;
};



class TrafficLight : public QWidget {
 public:
  explicit TrafficLight(QWidget *parent = nullptr)
      : QWidget(parent) {
    auto *vbox = new QVBoxLayout(this);
    auto *widget = new TrafficLightWidget();
    vbox->addWidget(widget);
    vbox->setMargin(0);

    auto *machine = new QStateMachine(this);

    QState *redGoingYellow = createLightState(widget->redLight(), 3000);
    redGoingYellow->setObjectName("redGoingYellow");

    QState *yellowGoingGreen = createLightState(widget->yellowLight(), 1000);
    yellowGoingGreen->setObjectName("yellowGoingGreen");

    QState *greenGoingYellow = createLightState(widget->greenLight(), 3000);
    greenGoingYellow->setObjectName("greenGoingYellow");

    QState *yellowGoingRed = createLightState(widget->yellowLight(), 1000);
    yellowGoingRed->setObjectName("yellowGoingRed");

    greenGoingYellow->addTransition(greenGoingYellow, SIGNAL(finished()), yellowGoingRed);
    yellowGoingRed->addTransition(yellowGoingRed, SIGNAL(finished()), redGoingYellow);
    redGoingYellow->addTransition(redGoingYellow, SIGNAL(finished()), yellowGoingGreen);
    yellowGoingGreen->addTransition(yellowGoingGreen, SIGNAL(finished()), greenGoingYellow);

    machine->addState(redGoingYellow);
    machine->addState(yellowGoingGreen);
    machine->addState(greenGoingYellow);
    machine->addState(yellowGoingRed);
    machine->setInitialState(redGoingYellow);
    machine->start();
  }
};

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  TrafficLight widget;
  widget.resize(110, 300);
  widget.show();

  return app.exec();
}