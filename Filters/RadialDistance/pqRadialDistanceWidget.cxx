#include "pqRadialDistanceWidget.h"
//#include "pqNamedWidgets.h"
//#include "pqRadialDistanceWidget.h"
//#include "pqPropertyLinks.h"

//#include "pqHandleWidget.h"

#include <vtkSMDoubleVectorProperty.h>
#include <vtkSMIntVectorProperty.h>
#include <vtkSMProxyProperty.h>
#include <vtkSMNewWidgetRepresentationProxy.h>

#include <QLabel>
#include <QLineEdit>

pqRadialDistanceWidget::pqRadialDistanceWidget(pqProxy* pxy, QWidget* p) : pqAutoGeneratedObjectPanel(pxy, p)
{
		// We need to hide the QT objects that are used for Point Source
		QWidget* widget = this->findChild<QWidget*>("NumberOfPoints");
		widget->setVisible(false);
		widget = this->findChild<QWidget*>("label");
		widget->setVisible(false);
		widget = this->findChild<QWidget*>("label_2");
		widget->setVisible(false);
		widget = this->findChild<QWidget*>("Radius");
		widget->setVisible(false);

    this->linkServerManagerProperties();
  }

pqRadialDistanceWidget::~pqRadialDistanceWidget()
  {
  }

void pqRadialDistanceWidget::linkServerManagerProperties()
  {
  // parent class hooks up some of our widgets in the ui
  pqAutoGeneratedObjectPanel::linkServerManagerProperties();
	}