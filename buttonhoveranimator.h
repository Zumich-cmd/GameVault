#ifndef BUTTONHOVERANIMATOR_H
#define BUTTONHOVERANIMATOR_H

#include <QObject>
#include <QColor>

class QPushButton;
class QVariantAnimation;
class QEvent;

struct ButtonHoverPalette {
    QColor normal;
    QColor hover;
    QColor pressed;
    QColor checked;
    QColor checkedHover;
    bool useChecked = false;
};

class ButtonHoverAnimator : public QObject
{
    Q_OBJECT

public:
    ButtonHoverAnimator(QPushButton *button,
                        const ButtonHoverPalette &palette,
                        int durationMs = 140);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void animateTo(const QColor &target);
    void applyColor(const QColor &color);
    QColor resolveBaseColor() const;

private:
    QPushButton *m_button = nullptr;
    QVariantAnimation *m_anim = nullptr;
    ButtonHoverPalette m_palette;
    QColor m_current;
};

void installHoverAnimation(QPushButton *button,
                           const ButtonHoverPalette &palette,
                           QObject *parent,
                           int durationMs = 140);

#endif // BUTTONHOVERANIMATOR_H
