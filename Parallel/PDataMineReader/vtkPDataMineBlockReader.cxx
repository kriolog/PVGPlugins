#include "vtkPDataMineBlockReader.h"
#include "vtkObjectFactory.h"
#include "vtkCellArray.h"

vtkCxxRevisionMacro(vtkPDataMineBlockReader, "$Revision: 0.4 $");
vtkStandardNewMacro(vtkPDataMineBlockReader);


// --------------------------------------
vtkPDataMineBlockReader::vtkPDataMineBlockReader()
  {
  }

// --------------------------------------
vtkPDataMineBlockReader::~vtkPDataMineBlockReader()
  {  
  }

// --------------------------------------
int vtkPDataMineBlockReader::CanReadFile( const char* fname )
{
	return this->CanRead(fname, blockmodel);	
}


// --------------------------------------
int vtkPDataMineBlockReader::ReadShrunks( int start, int end, vtkPolyData* out)
{	
	vtkDataMineBlockReader* reader;
	vtkAppendPolyData *append = vtkAppendPolyData::New();
	//read all of pieces assigned to this process
	for(int piec = start; piec < end; ++piec)
	{
		vtkPolyData *tmp;
		reader = vtkDataMineBlockReader::New();
		reader->SetFileName(this->PieceFileNames[piec]);
		reader->SetCellDataArraySelection(this->CellDataArraySelection);
		tmp = reader->GetOutput();
		if (tmp && tmp->GetDataObjectType() != VTK_POLY_DATA)
		{
			vtkWarningMacro("Expecting PolyData in file: " << this->PieceFileNames[piec]);
		}
		else
			{
				append->AddInput(tmp);
				cout<<this->PieceFileNames[piec]<<" added to append"<<endl; 
			}
		reader->Delete();
	}
	append->Update();
	out->CopyStructure(append->GetOutput());
	out->GetFieldData()->PassData(append->GetOutput()->GetFieldData());
	out->GetCellData()->PassData(append->GetOutput()->GetCellData());
	out->GetPointData()->PassData(append->GetOutput()->GetPointData());
	append->Delete();
	
	return 1;
}