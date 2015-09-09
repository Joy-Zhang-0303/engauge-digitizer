#include "Logger.h"
#include <qdebug.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "TutorialButton.h"
#include "TutorialDlg.h"
#include "TutorialStateAxisPoints.h"
#include "TutorialStateContext.h"

TutorialStateAxisPoints::TutorialStateAxisPoints (TutorialStateContext &context) : 
  TutorialStateAbstractBase (context)
{
}

void TutorialStateAxisPoints::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateAxisPoints::begin ()";

  m_title = createTitle ("Axis Points");
  m_background = createPixmapItem (":/engauge/img/panel_axis_points.png",
                                   QPoint (0, 30));
  m_text0 = createTextItem ("Axis points are first defined to\n"
                            "define the coordinates. Click on the\n"
                            "Axis Points button",
                            QPoint (320, 60));
  m_text1 = createTextItem ("Click on an axis or grid line with\n"
                            "known coordinates. An axis point\n"
                            "appears, with a dialog window for\n"
                            "entering the axis point's coordinates",
                            QPoint (300, 210));
  m_text2 = createTextItem ("Enter the two coordinates of the axis\n"
                            "point and then click Ok. Repeat steps\n"
                            "2 and 3 twice more until three axis\n"
                            "points are created",
                            QPoint (280, 320));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_previous = new TutorialButton ("Previous",
                                   context().tutorialDlg().scene());
  m_previous->setGeometry (QPoint (buttonMargin (),
                                   backgroundSize.height() - buttonMargin() - m_previous->size().height()));
  connect (m_previous, SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));

  m_next = new TutorialButton ("Next",
                               context().tutorialDlg().scene());
  m_next->setGeometry (QPoint (backgroundSize.width () - buttonMargin () - m_next->size ().width (),
                               backgroundSize.height () - buttonMargin () - m_next->size ().height ()));
  connect (m_next, SIGNAL (signalTriggered ()), this, SLOT (slotNext ()));
}

void TutorialStateAxisPoints::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateAxisPoints::end ()";

  context().tutorialDlg().scene().removeItem (m_title);
  context().tutorialDlg().scene().removeItem (m_background);
  context().tutorialDlg().scene().removeItem (m_text0);
  context().tutorialDlg().scene().removeItem (m_text1);
  context().tutorialDlg().scene().removeItem (m_text2);
  // TutorialButton removes itself from the scene

  delete m_title;
  delete m_background;
  delete m_text0;
  delete m_text1;
  delete m_text2;
  delete m_next;
  delete m_previous;

  m_title = 0;
  m_background = 0;
  m_text0 = 0;
  m_text1 = 0;
  m_text2 = 0;
  m_next = 0;
  m_previous = 0;
}

void TutorialStateAxisPoints::slotNext ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateAxisPoints::slotNextCurves";

  context().requestDelayedStateTransition (TUTORIAL_STATE_CURVE_TYPE);
}

void TutorialStateAxisPoints::slotPrevious ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateAxisPoints::slotPrevious";

  context().requestDelayedStateTransition (TUTORIAL_STATE_INTRODUCTION);
}