#include "sevensegmentpanel.h"

// TODO delete pointers
SevenSegmentPanel::SevenSegmentPanel(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    layout->setSizeConstraint(QLayout::SetMinimumSize);

    countBox = new QComboBox;
    layout->addWidget(countBox, 0, 0);

    QStringList items;
    items << "1" << "2" << "4" << "8";
    countBox->addItems(items);

    init(8);

    connect(countBox, SIGNAL(currentTextChanged(QString)), this, SLOT(spinnerChanged(QString)));

    countBox->setCurrentText("4");

    this->setWindowTitle("Seven segment panel");
    this->setWindowIcon(QIcon(":/Resources/icons/SevenSegment.png"));
}

SevenSegmentPanel::~SevenSegmentPanel()
{
    // delete here something
}

void SevenSegmentPanel::init(unsigned int countSegments)
{
    for (unsigned int i = 0; i < countSegments; i++)
    {

        SevenSegmentIO* sevenSegment = new SevenSegmentIO;
        sevenSegment->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        vectSevenSegment.push_back(sevenSegment);
        sevenSegment->hide();
        layout->addWidget(sevenSegment, 1, i);


        QMenu* menu = new QMenu;
        for (int j = 0; j < 8; j++)
        {
            ChooseIOWidget* chooser = new ChooseIOWidget;
            vectChooser.push_back(chooser);

            QWidgetAction* chooserAction = new QWidgetAction(this);
            chooserAction->setDefaultWidget(chooser);
            menu->addAction(chooserAction);
        }

        connect(sevenSegment, &SevenSegmentIO::clicked, [=](QMouseEvent* event) {
            menu->exec(event->globalPos());
        });
    }
}

void SevenSegmentPanel::spinnerChanged(QString value)
{
    for (unsigned int i = 0; i < vectSevenSegment.size(); i++)
    {
        SevenSegmentIO* segment = vectSevenSegment[i];
        segment->hide();
    }

    for (int i = 0; i < value.toInt(); i++)
    {
        SevenSegmentIO* segment = vectSevenSegment[i];
        segment->show();
    }

    emit changedSegmentCount();
}