#ifndef _pqConvertPointsToBlocks_h
#define _pqConvertPointsToBlocks_h

#include "pqApplicationComponentsModule.h"
#include "pqPropertyGroupWidget.h"

class vtkSMPropertyGroup;
namespace Ui{
  class Form;
}

class PQAPPLICATIONCOMPONENTS_EXPORT pqConvertPointsToBlocks
  : public pqPropertyGroupWidget
{
  Q_OBJECT
  typedef pqPropertyGroupWidget Superclass;

public:
  /// constructor
  pqConvertPointsToBlocks(
    vtkSMProxy* proxy, vtkSMPropertyGroup* smgroup, QWidget* parent = 0);
  /// destructor
  ~pqConvertPointsToBlocks();

protected slots:
  virtual  void updateGui();	

private:
  Q_DISABLE_COPY(pqConvertPointsToBlocks)
  Ui::Form* ui;
};

#endif

