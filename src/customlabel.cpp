#include "../include/customlabel.h"
#include "../include/tank.h"

#include <QGraphicsColorizeEffect>

CustomLabel::CustomLabel(Tank* tank, QWidget* parent)
    : QLabel(parent), tankReference(tank)
{
    setAlignment(Qt::AlignCenter);
}

CustomLabel::CustomLabel(PowerUp* powerUp, QWidget* parent)
    : QLabel(parent), powerUpReference(powerUp)
{
    setAlignment(Qt::AlignCenter);
}
CustomLabel::CustomLabel(const QString& text, Tank* tank, QWidget* parent)
    : QLabel(parent), tankReference(tank)
{
    setText(text);
    setAlignment(Qt::AlignCenter);
}

void CustomLabel::enterEvent(QEnterEvent *event)
{
    if (!tankReference) return;

    auto* colorEffect = new QGraphicsColorizeEffect();
    colorEffect->setColor(Qt::red);
    tankReference->setGraphicsEffect(colorEffect);
    QLabel::enterEvent(event);
}

void CustomLabel::leaveEvent(QEvent *event)
{
    if (!tankReference) return;
    tankReference->setGraphicsEffect(nullptr);
    QLabel::leaveEvent(event);
}

void CustomLabel::setPowerUpReference(PowerUp *newPowerUpReference)
{
    powerUpReference = newPowerUpReference;
}

void CustomLabel::setTankReference(Tank *newTankReference)
{
    tankReference = newTankReference;
}
