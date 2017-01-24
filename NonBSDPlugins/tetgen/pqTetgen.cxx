//===================================================================================//
//				Mirarco Mining Innovation
//
// Filter:   Volumique Tetrahedralisation
// Class:    pqTetgen
// Author:   Nehmeh Bilal
// Director: Marie-Grabrielle Valet 
// Date:     July 2008
// contact: nehmebilal@gmail.com 
//====================================================================================//

#include "pqTetgen.h"
#include "ui_pqTetgen.h"

#include "pqSignalAdaptors.h"
#include "vtkSMPropertyGroup.h"
#include "vtkSMProxy.h"
#include "pqComboBoxDomain.h"

pqTetgen::pqTetgen(
  vtkSMProxy* smproxy, vtkSMPropertyGroup* smgroup, QWidget* parentObject)
  : Superclass(smproxy, smgroup, parentObject)
{
  ui = new Ui::uiMenu;
  ui->setupUi(this);

  this->setChangeAvailableAsChangeFinished(true);

  addPropertyLinkDouble("RadiusEdgeRatio", smgroup);
  addPropertyLinkDouble("MaxTetrahedronVolume", smgroup);
  addPropertyLinkSelector("tetgenCommand", smgroup);
  addPropertyLinkDouble("MaxTetrahedronVolumeInBox", smgroup);
  addPropertyLinkDouble("MaxTetrahedronVolumeInBox2", smgroup);
  addPropertyLinkBool("WithRegions", smgroup);
  addPropertyLinkBool("WithPredefinedRegions", smgroup);
  addPropertyLinkBool("WithBoundingBox", smgroup);

  addPropertyLinkBool("WithBBX1", smgroup);
  addPropertyLinkDouble("deltaX", smgroup);
  addPropertyLinkDouble("deltaY", smgroup);
  addPropertyLinkDouble("deltaZ", smgroup);

  addPropertyLinkBool("WithBBX2", smgroup);
  addPropertyLinkDouble("deltaX2", smgroup);
  addPropertyLinkDouble("deltaY2", smgroup);
  addPropertyLinkDouble("deltaZ2", smgroup);

// 		ui->wbbx1 = this->findChild<QDockWidget*>("wbbx1");
// 		ui->wbbx2 = this->findChild<QDockWidget*>("wbbx2");
//
// 		ui->pbbx1 = this->findChild<QPushButton*>("pbbx1");
// 		ui->pbbx2 = this->findChild<QPushButton*>("pbbx2");

  ui->wbbx1->close();
  ui->wbbx1->setShown(false);
  ui->wbbx2->close();
  ui->wbbx2->setShown(false);

// 		ui->pClean = this->findChild<QPushButton*>("pClean");
// 		ui->wClean = this->findChild<QDockWidget*>("wClean");
  ui->wClean->close();

  addPropertyLinkBool("ToleranceIsAbsolute", smgroup);
  addPropertyLinkDoubleString("AbsoluteTolerance", smgroup);
  addPropertyLinkDoubleString("Tolerance", smgroup);

  addPropertyLinkArraySelector("RegionArray", smgroup);

  addPropertyLinkIntString("numberOfTetrahedronInfo", smgroup);
  ui->numberOfTetrahedronInfo->setVisible(false);
//
// 		ui->numberOfTetrahedronLabel = this->findChild<QLabel*>("numberOfTetrahedronLabel");

  addPropertyLinkBool("PieceInvariant", smgroup);
  addPropertyLinkBool("PointMerging", smgroup);
  addPropertyLinkBool("ConvertLinesToPoints", smgroup);
  addPropertyLinkBool("ConvertPolysToLines", smgroup);
  addPropertyLinkBool("ConvertStripsToPolys", smgroup);

		QObject::connect(ui->numberOfTetrahedronInfo, SIGNAL(textChanged (const QString&)),
			this, SLOT(onNumberOfTetrahedronChanged(const QString&)),Qt::QueuedConnection);


	  QObject::connect(ui->tetgenCommand, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(updateMenu(void)));

		
/*
	  QObject::connect(ui->MaxTetrahedronVolume, SIGNAL(valueChanged(double)),
                   this, SLOT(updateDoubleSpineBoxStep(void)));

	  QObject::connect(ui->RadiusEdgeRatio, SIGNAL(valueChanged(double)),
                   this, SLOT(updateDoubleSpineBoxStep2(void)));
*/

		QObject::connect(ui->WithRegions, SIGNAL(stateChanged(int)),this, SLOT(updateMenu_WithRegions(void)));
		QObject::connect(ui->WithPredefinedRegions, SIGNAL(stateChanged(int)),this, SLOT(updateMenu_WithPredefinedRegions(void)));
		QObject::connect(ui->WithBoundingBox, SIGNAL(stateChanged(int)),this, SLOT(updateMenu_WithBoundingBox(void)));
		QObject::connect(ui->pbbx1, SIGNAL(clicked()),this, SLOT(showbbx1(void)));
		QObject::connect(ui->pbbx2, SIGNAL(clicked()),this, SLOT(showbbx2(void)));

		QObject::connect(ui->WithBBX1, SIGNAL(stateChanged(int)),this, SLOT(updateWbbx1(void)));
		QObject::connect(ui->WithBBX2, SIGNAL(stateChanged(int)),this, SLOT(updateWbbx2(void)));

		QObject::connect(ui->pClean, SIGNAL(clicked()),this, SLOT(showClean(void)));
		QObject::connect(ui->ToleranceIsAbsolute, SIGNAL(stateChanged(int)),this, SLOT(updateToleranceIsAbsolute(void)));
		
		ui->RadiusEdgeRatio->setDisabled(true);
		ui->MaxTetrahedronVolume->setDisabled(true);
		ui->WithRegions->setDisabled(true);
		ui->WithPredefinedRegions->setDisabled(true);
		ui->WithBoundingBox->setDisabled(true);
		ui->MaxTetrahedronVolumeInBox->setDisabled(true);
		ui->RegionArray->setDisabled(true);
		ui->pbbx1->setDisabled(true);
		ui->pbbx2->setDisabled(true);

		
		ui->deltaX->setDisabled(true);
		ui->deltaY->setDisabled(true);
		ui->deltaZ->setDisabled(true);

		ui->deltaX2->setDisabled(true);
		ui->deltaY2->setDisabled(true);
		ui->deltaZ2->setDisabled(true);

		ui->AbsoluteTolerance->setDisabled(true);
}

pqTetgen::~pqTetgen()
{
  delete ui;
}

void pqTetgen::addPropertyLinkInt(const char* name, vtkSMPropertyGroup* smgroup)
{
  if(vtkSMProperty* smproperty = smgroup->GetProperty(
    QString("Link%1").arg(name).toLatin1().data()))
  {
    this->addPropertyLink(this->findChild<QSpinBox*>(name),
      "value", SIGNAL(valueChanged(int)), smproperty);
  } else {
    missingPropertyMessage(name);
  }
}

void pqTetgen::addPropertyLinkDouble(const char* name, vtkSMPropertyGroup* smgroup)
{
  if(vtkSMProperty* smproperty = smgroup->GetProperty(
    QString("Link%1").arg(name).toLatin1().data()))
  {
    this->addPropertyLink(this->findChild<QDoubleSpinBox*>(name),
      "value", SIGNAL(valueChanged(double)), smproperty);
  } else {
    missingPropertyMessage(name);
  }
}

void pqTetgen::addPropertyLinkIntString(const char* name, vtkSMPropertyGroup* smgroup)
{
  QLineEdit* line_edit = this->findChild<QLineEdit*>(name);
  line_edit->setValidator(new QIntValidator(line_edit));
  if(vtkSMProperty* smproperty = smgroup->GetProperty(
    QString("Link%1").arg(name).toLatin1().data()))
  {
    this->addPropertyLink(line_edit,
      "text", SIGNAL(editingFinished()), smproperty);
  } else {
    missingPropertyMessage(name);
  }
}

void pqTetgen::addPropertyLinkDoubleString(const char* name, vtkSMPropertyGroup* smgroup)
{
  QLineEdit* line_edit = this->findChild<QLineEdit*>(name);
  line_edit->setValidator(new QDoubleValidator(line_edit));
  if(vtkSMProperty* smproperty = smgroup->GetProperty(
    QString("Link%1").arg(name).toLatin1().data()))
  {
    this->addPropertyLink(line_edit,
      "text", SIGNAL(editingFinished()), smproperty);
  } else {
    missingPropertyMessage(name);
  }
}

void pqTetgen::addPropertyLinkBool(const char* name, vtkSMPropertyGroup* smgroup)
{
  if(vtkSMProperty* smproperty = smgroup->GetProperty(
    QString("Link%1").arg(name).toLatin1().data()))
  {
    this->addPropertyLink(this->findChild<QCheckBox*>(name),
      "checked", SIGNAL(toggled(bool)), smproperty);
  } else {
    missingPropertyMessage(name);
  }
}

void pqTetgen::addPropertyLinkSelector(const char* name, vtkSMPropertyGroup* smgroup)
{
  if(vtkSMProperty* smproperty = smgroup->GetProperty(
    QString("Link%1").arg(name).toLatin1().data()))
  {
    this->addPropertyLink(new pqSignalAdaptorComboBox(this->findChild<QComboBox*>(name)),
      "currentText", SIGNAL(currentTextChanged(QString)), smproperty);
  } else {
    missingPropertyMessage(name);
  }
}

void pqTetgen::addPropertyLinkArraySelector(const char* name, vtkSMPropertyGroup* smgroup)
{
  if(vtkSMProperty* smproperty = smgroup->GetProperty(
    QString("Link%1").arg(name).toLatin1().data()))
  {
    QComboBox* combo_box = this->findChild<QComboBox*>(name);
    new pqComboBoxDomain(combo_box, smproperty, "array_list");
    this->addPropertyLink(new pqSignalAdaptorComboBox(combo_box), "currentText",
      SIGNAL(currentTextChanged(QString)), smproperty);
  } else {
    missingPropertyMessage(name);
  }
}

void pqTetgen::missingPropertyMessage(const char* name)
{
    qCritical(QString("Missing required property for function '%1'.")
      .arg(name).toLatin1().data());
}


void pqTetgen::updateMenu()
{
	switch(ui->tetgenCommand->currentIndex())
	{
	case 1:
	case 2:
		ui->WithRegions->setDisabled(false);
		ui->WithPredefinedRegions->setDisabled(false);
		ui->WithBoundingBox->setDisabled(false);
		ui->RadiusEdgeRatio->setDisabled(true);
		ui->MaxTetrahedronVolume->setDisabled(true);
		ui->MaxTetrahedronVolumeInBox->setDisabled(true);
		ui->MaxTetrahedronVolumeInBox2->setDisabled(true);

		if(!(ui->WithBoundingBox->isChecked()))
		{
			ui->pbbx1->setDisabled(true);
			ui->pbbx2->setDisabled(true);
		}
		break;

	case 3:
		ui->RadiusEdgeRatio->setDisabled(false);
		ui->RadiusEdgeRatio->setFocus();
		ui->RadiusEdgeRatio->selectAll();
		ui->MaxTetrahedronVolume->setDisabled(true);
		ui->WithRegions->setDisabled(false);
		ui->WithPredefinedRegions->setDisabled(false);
		ui->WithBoundingBox->setDisabled(false);
		ui->MaxTetrahedronVolumeInBox->setDisabled(true);
		ui->MaxTetrahedronVolumeInBox2->setDisabled(true);

		if(!(ui->WithBoundingBox->isChecked()))
		{
			ui->pbbx1->setDisabled(true);
			ui->pbbx2->setDisabled(true);
		}

		break;

	case 4:
		ui->MaxTetrahedronVolume->setDisabled(false);
		ui->MaxTetrahedronVolume->setFocus();
		ui->MaxTetrahedronVolume->selectAll();
		ui->RadiusEdgeRatio->setDisabled(true);
		ui->WithRegions->setDisabled(false);
		ui->WithPredefinedRegions->setDisabled(false);
		ui->WithBoundingBox->setDisabled(false);

		if(!(ui->WithBoundingBox->isChecked()))
		{
			ui->pbbx1->setDisabled(true);
			ui->pbbx2->setDisabled(true);
			ui->MaxTetrahedronVolumeInBox->setDisabled(true);
			ui->MaxTetrahedronVolumeInBox2->setDisabled(true);
		}
		if((ui->WithBoundingBox->isChecked()) && (ui->WithPredefinedRegions->isChecked()))
		{
			if(ui->WithBBX1->isChecked())
				ui->MaxTetrahedronVolumeInBox->setDisabled(false);
			if(ui->WithBBX2->isChecked())
				ui->MaxTetrahedronVolumeInBox2->setDisabled(false);
		}
		break;

	case 5:
		ui->MaxTetrahedronVolume->setDisabled(false);
		ui->RadiusEdgeRatio->setDisabled(false);
		ui->RadiusEdgeRatio->setFocus();
		ui->RadiusEdgeRatio->selectAll();
		ui->WithRegions->setDisabled(false);
		ui->WithPredefinedRegions->setDisabled(false);
		ui->WithBoundingBox->setDisabled(false);

		if(!(ui->WithBoundingBox->isChecked()))
		{
			ui->pbbx1->setDisabled(true);
			ui->pbbx2->setDisabled(true);
			ui->MaxTetrahedronVolumeInBox->setDisabled(true);
			ui->MaxTetrahedronVolumeInBox2->setDisabled(true);
		}
		if((ui->WithBoundingBox->isChecked()) && (ui->WithPredefinedRegions->isChecked()))
		{
			if(ui->WithBBX1->isChecked())
				ui->MaxTetrahedronVolumeInBox->setDisabled(false);
			if(ui->WithBBX2->isChecked())
				ui->MaxTetrahedronVolumeInBox2->setDisabled(false);
		}
		break;

	default:
		ui->RadiusEdgeRatio->setDisabled(true);
		ui->MaxTetrahedronVolume->setDisabled(true);
		ui->WithRegions->setDisabled(true);
		ui->WithPredefinedRegions->setDisabled(true);
		ui->WithBoundingBox->setDisabled(true);
		ui->pbbx1->setDisabled(true);
		ui->pbbx2->setDisabled(true);
		ui->MaxTetrahedronVolumeInBox->setDisabled(true);
		ui->MaxTetrahedronVolumeInBox2->setDisabled(true);

		ui->WithRegions->setChecked(false);
		ui->WithPredefinedRegions->setChecked(false);
		ui->WithBoundingBox->setChecked(false);
		
	}



}

void pqTetgen::updateDoubleSpineBoxStep()
{
	if(ui->MaxTetrahedronVolume->value() < 6.0)
	{
		ui->MaxTetrahedronVolume ->setSingleStep(1.0);
		if(ui->MaxTetrahedronVolume->value() < 2.0)
		{
			ui->MaxTetrahedronVolume ->setSingleStep(0.1);
			if(ui->MaxTetrahedronVolume->value() < 0.2)
			{
				ui->MaxTetrahedronVolume ->setSingleStep(0.01);
			}
		}

	}	
	else
		ui->MaxTetrahedronVolume -> setSingleStep(5);
}


void pqTetgen::updateDoubleSpineBoxStep2()
{
	if(ui->RadiusEdgeRatio->value() < 1.1)
	{
		ui->RadiusEdgeRatio->setSingleStep(0.01);
	}
	else
		ui->RadiusEdgeRatio->setSingleStep(0.1);

}

void pqTetgen::updateMenu_WithBoundingBox()
{
	if((ui->WithBoundingBox->isChecked()))
	{
		ui->pbbx1->setDisabled(false);
		ui->pbbx2->setDisabled(false);

		if(ui->WithPredefinedRegions->isChecked() && (ui->tetgenCommand->currentIndex() > 3))
		{
			if(ui->WithBBX1->isChecked())
				ui->MaxTetrahedronVolumeInBox->setDisabled(false);
			if(ui->WithBBX2->isChecked())
				ui->MaxTetrahedronVolumeInBox2->setDisabled(false);
		}

		else
		{
			ui->MaxTetrahedronVolumeInBox->setDisabled(true);
			ui->MaxTetrahedronVolumeInBox2->setDisabled(true);
		}
	}
	else
	{
		ui->pbbx1->setDisabled(true);
		ui->pbbx2->setDisabled(true);
		ui->WithBBX1->setChecked(false);
		ui->WithBBX2->setChecked(false);
	}	
}

void pqTetgen::updateMenu_WithRegions()
{
	if(ui->WithRegions->isChecked())
		ui->WithPredefinedRegions->setChecked(false);
}

void pqTetgen::updateMenu_WithPredefinedRegions()
{
	if(ui->WithPredefinedRegions->isChecked())
	{
		ui->RegionArray->setDisabled(false);
		ui->WithRegions->setChecked(false);
		if(ui->WithBoundingBox->isChecked()&& (ui->tetgenCommand->currentIndex() > 3))
		{
			if(ui->WithBBX1->isChecked())
				ui->MaxTetrahedronVolumeInBox->setDisabled(false);
			if(ui->WithBBX2->isChecked())
				ui->MaxTetrahedronVolumeInBox2->setDisabled(false);
		}
	}
	else
	{
		ui->RegionArray->setDisabled(true);
		if(ui->WithBoundingBox->isChecked())
		{
			ui->MaxTetrahedronVolumeInBox->setDisabled(true);
			ui->MaxTetrahedronVolumeInBox2->setDisabled(true);
		}
	}
}

void pqTetgen::showbbx1()
{
	ui->wbbx1->setFloating(true);
	//ui->wbbx1->showMaximized();
	ui->wbbx1->setShown(true);
	ui->wbbx1->setWindowTitle("Bounding Box 1");
}


void pqTetgen::showbbx2()
{
	ui->wbbx2->setFloating(true);
	ui->wbbx2->setShown(true);
	ui->wbbx2->setWindowTitle("Bounding Box 2");
}



void pqTetgen::updateWbbx1()
{
	if(ui->WithBBX1->isChecked())
	{
		ui->deltaX->setDisabled(false);
		ui->deltaY->setDisabled(false);
		ui->deltaZ->setDisabled(false);

		if(ui->WithPredefinedRegions->isChecked() && (ui->tetgenCommand->currentIndex() > 3))
		{
			ui->MaxTetrahedronVolumeInBox->setDisabled(false);
		}
	}

	else
	{
		ui->deltaX->setDisabled(true);
		ui->deltaY->setDisabled(true);
		ui->deltaZ->setDisabled(true);

		ui->MaxTetrahedronVolumeInBox->setDisabled(true);

	}
}


void pqTetgen::updateWbbx2()
{
	if(ui->WithBBX2->isChecked())
	{
		ui->deltaX2->setDisabled(false);
		ui->deltaY2->setDisabled(false);
		ui->deltaZ2->setDisabled(false);

		if(ui->WithPredefinedRegions->isChecked() && (ui->tetgenCommand->currentIndex() > 3))
		{
			ui->MaxTetrahedronVolumeInBox2->setDisabled(false);
		}
	}

	else
	{
		ui->deltaX2->setDisabled(true);
		ui->deltaY2->setDisabled(true);
		ui->deltaZ2->setDisabled(true);

		ui->MaxTetrahedronVolumeInBox2->setDisabled(true);

	}
}




void pqTetgen::showClean()
{
	ui->wClean->setFloating(true);
	ui->wClean->setShown(true);
	ui->wClean->setWindowTitle("Clean Filter");
}



void pqTetgen::updateToleranceIsAbsolute()
{
	if(ui->ToleranceIsAbsolute->isChecked())
	{
		ui->AbsoluteTolerance->setDisabled(false);
		ui->Tolerance->setDisabled(true);
	}
	else
	{
		ui->AbsoluteTolerance->setDisabled(true);
		ui->Tolerance->setDisabled(false);
	}
}



void pqTetgen::onNumberOfTetrahedronChanged(const QString& n)
{
	ui->numberOfTetrahedronLabel->setText(n);
}