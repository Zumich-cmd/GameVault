#include "buttonhoveranimator.h"

#include <QPushButton>
#include <QVariantAnimation>
#include <QEvent>

ButtonHoverAnimator::ButtonHoverAnimator(QPushButton *button,
                                         const ButtonHoverPalette &palette,
                                         int durationMs)
    : QObject(button)
    , m_button(button)
    , m_anim(new QVariantAnimation(this))
    , m_palette(palette)
    , m_current(palette.normal)
{
    m_anim->setDuration(durationMs);
    m_anim->setStartValue(m_palette.normal);
    m_anim->setEndValue(m_palette.normal);

    connect(m_anim, &QVariantAnimation::valueChanged, this, [this](const QVariant &value) {
        m_current = value.value<QColor>();
        applyColor(m_current);
    });

    connect(m_button, &QPushButton::toggled, this, [this](bool) {
        animateTo(resolveBaseColor());
    });

    m_button->installEventFilter(this);
    applyColor(resolveBaseColor());
}

bool ButtonHoverAnimator::eventFilter(QObject *watched, QEvent *event)
{
    if (watched != m_button) {
        return QObject::eventFilter(watched, event);
    }

    if (event->type() == QEvent::Enter) {
        if (m_palette.useChecked && m_button->isCheckable() && m_button->isChecked()) {
            animateTo(m_palette.checkedHover);
        } else {
            animateTo(m_palette.hover);
        }
    } else if (event->type() == QEvent::Leave) {
        animateTo(resolveBaseColor());
    } else if (event->type() == QEvent::MouseButtonPress) {
        animateTo(m_palette.pressed);
    } else if (event->type() == QEvent::MouseButtonRelease) {
        if (m_button->underMouse()) {
            if (m_palette.useChecked && m_button->isCheckable() && m_button->isChecked()) {
                animateTo(m_palette.checkedHover);
            } else {
                animateTo(m_palette.hover);
            }
        } else {
            animateTo(resolveBaseColor());
        }
    }

    return QObject::eventFilter(watched, event);
}

void ButtonHoverAnimator::animateTo(const QColor &target)
{
    if (!m_button) {
        return;
    }

    m_anim->stop();
    m_anim->setStartValue(m_current);
    m_anim->setEndValue(target);
    m_anim->start();
}

void ButtonHoverAnimator::applyColor(const QColor &color)
{
    if (!m_button) {
        return;
    }

    m_button->setStyleSheet(QString("background-color: %1;").arg(color.name(QColor::HexRgb)));
}

QColor ButtonHoverAnimator::resolveBaseColor() const
{
    if (m_palette.useChecked && m_button->isCheckable() && m_button->isChecked()) {
        return m_palette.checked;
    }
    return m_palette.normal;
}

void installHoverAnimation(QPushButton *button,
                           const ButtonHoverPalette &palette,
                           QObject *parent,
                           int durationMs)
{
    if (!button) {
        return;
    }

    auto *animator = new ButtonHoverAnimator(button, palette, durationMs);
    animator->setParent(parent);
}
