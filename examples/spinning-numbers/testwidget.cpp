#include "testwidget.h"

TestWidget::TestWidget(QMainWindow* Parent, const QPoint& Position, const QSize& Size)
    : QSFMLWidget(Parent, Position, Size, 0)
{
    TextColorR = 63;
    TextColorG = 165;

    colorModR = 1;
    colorModG = 1;

    counter = 0;
}

TestWidget::~TestWidget()
{
    if(initialized)
        free(fontDat);
}

void TestWidget::OnInit()
{
    bitFont.loadFromStream(fontStream("://BitFont.ttf"));

    bitText.setFont(bitFont);
    bitText.setCharacterSize(280);
    bitText.setPosition(qsf::QVector2f(200, 140));

    bitText.setString("0");
    bitText.setOrigin(bitText.getLocalBounds().width / 2.f, bitText.getLocalBounds().height / 2.f + 40.f);
}

void TestWidget::OnUpdate()
{
    setSize(qsf::QVector2u(((QWidget*) parent())->size()));

    clear({0, 0, 0});

    float seconds = frameTime.asSeconds();

    TextColorR += seconds * 27.f * colorModR;
    TextColorG += seconds * 31.f * colorModG;

    if(TextColorR > 250)
        colorModR = -1;
    else if(TextColorR < 5)
        colorModR = 1;

    if(TextColorG > 250)
        colorModG = -1;
    else if(TextColorG < 5)
        colorModG = 1;

    bitText.rotate(180);
    if(bitText.getRotation() + seconds * 80.f > 360)
        counter++;
    bitText.rotate(180);

    bitText.rotate(seconds * 80.f);
    bitText.setColor({sf::Uint8(TextColorR),
                      sf::Uint8(TextColorG),
                      sf::Uint8(255 - TextColorG)});

    float scale = (bitText.getRotation() <= 180 ? bitText.getRotation() : 180.f - (bitText.getRotation() - 180.f)) / 180;
    bitText.setScale(1.f - scale, 1.f - scale);

    bitText.setString(qsf::String::number(counter));
    bitText.setOrigin(bitText.getLocalBounds().width / 2.f, bitText.getLocalBounds().height / 2.f + 100.f);

    draw(bitText);
}
