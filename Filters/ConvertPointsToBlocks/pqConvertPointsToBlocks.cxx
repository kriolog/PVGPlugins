#include "pqConvertPointsToBlocks.h"
#include "ui_pqConvertPointsToBlocks.h"

#include "pqSignalAdaptors.h"
#include "vtkSMPropertyGroup.h"
#include "vtkSMProxy.h"
#include "pqComboBoxDomain.h"

pqConvertPointsToBlocks::pqConvertPointsToBlocks(
  vtkSMProxy* smproxy, vtkSMPropertyGroup* smgroup, QWidget* parentObject)
  : Superclass(smproxy, smgroup, parentObject)
{
  ui = new Ui::Form;
  ui->setupUi(this);

  vtkSMProperty* smproperty;
  this->setChangeAvailableAsChangeFinished(true);


  if(smproperty = smgroup->GetProperty("LinkXEntry")) {
    this->addPropertyLink(new pqSignalAdaptorComboBox(ui->XEntry), "currentText",
      SIGNAL(currentTextChanged(QString)), smproperty);
  } else {
    qCritical("Missing required property for function 'XEntry'.");
  }

  if(smproperty = smgroup->GetProperty("LinkYEntry")) {
    this->addPropertyLink(new pqSignalAdaptorComboBox(ui->YEntry),
      "currentText", SIGNAL(currentTextChanged(QString)), smproperty);
  } else {
    qCritical("Missing required property for function 'YEntry'.");
  }

  if(smproperty = smgroup->GetProperty("LinkZEntry")) {
    this->addPropertyLink(new pqSignalAdaptorComboBox(ui->ZEntry),
      "currentText", SIGNAL(currentTextChanged(QString)), smproperty);
  } else {
    qCritical("Missing required property for function 'ZEntry'.");
  }

  QObject::connect(ui->XEntry, SIGNAL(currentIndexChanged(int)), this, SLOT(updateGui(void)));
  QObject::connect(ui->YEntry, SIGNAL(currentIndexChanged(int)), this, SLOT(updateGui(void)));
  QObject::connect(ui->ZEntry, SIGNAL(currentIndexChanged(int)), this, SLOT(updateGui(void)));


  if(smproperty = smgroup->GetProperty("LinkSizeCX")) {
    this->addPropertyLink(ui->SizeCX, "value", SIGNAL(valueChanged(double)), smproperty);
  } else {
    qCritical("Missing required property for function 'SizeCX'.");
  }

  if(smproperty = smgroup->GetProperty("LinkSizeCY")) {
    this->addPropertyLink(ui->SizeCY, "value", SIGNAL(valueChanged(double)), smproperty);
  } else {
    qCritical("Missing required property for function 'SizeCY'.");
  }

  if(smproperty = smgroup->GetProperty("LinkSizeCZ")) {
    this->addPropertyLink(ui->SizeCZ, "value", SIGNAL(valueChanged(double)), smproperty);
  } else {
    qCritical("Missing required property for function 'SizeCZ'.");
  }


  if(smproperty = smgroup->GetProperty("LinkXINC")) {
    new pqComboBoxDomain(ui->XINC, smproperty, "array_list");
    this->addPropertyLink(new pqSignalAdaptorComboBox(ui->XINC), "currentText",
      SIGNAL(currentTextChanged(QString)), smproperty);
  } else {
    qCritical("Missing required property for function 'XINC'.");
  }

  if(smproperty = smgroup->GetProperty("LinkYINC")) {
    new pqComboBoxDomain(ui->YINC, smproperty, "array_list");
    this->addPropertyLink(new pqSignalAdaptorComboBox(ui->YINC), "currentText",
      SIGNAL(currentTextChanged(QString)), smproperty);
  } else {
    qCritical("Missing required property for function 'YINC'.");
  }

  if(smproperty = smgroup->GetProperty("LinkZINC")) {
    new pqComboBoxDomain(ui->ZINC, smproperty, "array_list");
    this->addPropertyLink(new pqSignalAdaptorComboBox(ui->ZINC), "currentText",
      SIGNAL(currentTextChanged(QString)), smproperty);
  } else {
    qCritical("Missing required property for function 'ZINC'.");
  }


  this->updateGui();
}

pqConvertPointsToBlocks::~pqConvertPointsToBlocks()
{
  delete ui;
}

void pqConvertPointsToBlocks::updateGui()
{
  if(ui->XEntry->currentIndex() == 1) {
    ui->XINC->setEnabled(true);
    ui->SizeCX->setEnabled(false);
  } else {
    ui->XINC->setEnabled(false);
    ui->SizeCX->setEnabled(true);
  }

  if(ui->YEntry->currentIndex() == 1) {
    ui->YINC->setEnabled(true);
    ui->SizeCY->setEnabled(false);
  } else {
    ui->YINC->setEnabled(false);
    ui->SizeCY->setEnabled(true);
  }

  if(ui->ZEntry->currentIndex() == 1) {
    ui->ZINC->setEnabled(true);
    ui->SizeCZ->setEnabled(false);
  } else {
    ui->ZINC->setEnabled(false);
    ui->SizeCZ->setEnabled(true);
  }
}

