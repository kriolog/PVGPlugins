/*
   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2. 

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


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

#ifndef _pqTetgen_h
#define _pqTetgen_h

#include "pqApplicationComponentsModule.h"
#include "pqPropertyGroupWidget.h"

class vtkSMPropertyGroup;
namespace Ui{
  class uiMenu;
}

class PQAPPLICATIONCOMPONENTS_EXPORT pqTetgen
  : public pqPropertyGroupWidget
{
  Q_OBJECT
  typedef pqPropertyGroupWidget Superclass;

public:
  /// constructor
  pqTetgen(vtkSMProxy* proxy, vtkSMPropertyGroup* smgroup, QWidget* parent = 0);
  /// destructor
  ~pqTetgen();

protected:
  Ui::uiMenu* ui;

  void addPropertyLinkInt(const char* name, vtkSMPropertyGroup* smgroup);
  void addPropertyLinkIntString(const char* name, vtkSMPropertyGroup* smgroup);
  void addPropertyLinkDouble(const char* name, vtkSMPropertyGroup* smgroup);
  void addPropertyLinkDoubleString(const char* name, vtkSMPropertyGroup* smgroup);
  void addPropertyLinkBool(const char* name, vtkSMPropertyGroup* smgroup);
  void addPropertyLinkSelector(const char* name, vtkSMPropertyGroup* smgroup);
  void addPropertyLinkArraySelector(const char* name, vtkSMPropertyGroup* smgroup);
  void missingPropertyMessage(const char* name);

protected slots:
  virtual void updateMenu();
  virtual void updateDoubleSpineBoxStep();
  virtual void updateDoubleSpineBoxStep2();
  virtual void updateMenu_WithRegions();
  virtual void updateMenu_WithPredefinedRegions();
  virtual void updateMenu_WithBoundingBox();
  virtual void showbbx1();
  virtual void showbbx2();
  virtual void updateWbbx1();
  virtual void updateWbbx2();

  virtual void showClean();
  virtual void updateToleranceIsAbsolute();

  virtual void onNumberOfTetrahedronChanged(const QString& n);

private:
  Q_DISABLE_COPY(pqTetgen)
};

#endif

