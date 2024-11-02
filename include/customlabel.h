#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

class Tank;
class PowerUp;

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(Tank* tank = nullptr, QWidget* parent = nullptr);
    explicit CustomLabel(PowerUp* powerUp = nullptr, QWidget* parent = nullptr);
    explicit CustomLabel(const QString& text, Tank* tank = nullptr, QWidget* parent = nullptr);


    void setTankReference(Tank *newTankReference);

    void setPowerUpReference(PowerUp *newPowerUpReference);

protected:
    void enterEvent(QEnterEvent *ev) override;
    void leaveEvent(QEvent *ev) override;
    Tank* tankReference = nullptr;
    PowerUp* powerUpReference = nullptr;

};

#endif // CUSTOMLABEL_H
