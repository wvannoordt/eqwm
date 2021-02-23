#include "WallModel.h"

namespace hw2
{
    WallModel::WallModel(int numPoints_in, MPI_Comm comm_in)
    {
        Builder(numPoints_in, comm_in);
    }
    
    WallModel::WallModel(int numPoints_in)
    {
        Builder(numPoints_in, MPI_COMM_WORLD);
    }
    
    Variable* WallModel::CreateVariable(std::string name, int dim)
    {
        return vars.CreateVariable(name, dim, &partition);
    }
    
    Variable* WallModel::operator [] (std::string name)
    {
        return this->GetVariable(name);
    }
    
    Variable* WallModel::GetVariable(std::string name)
    {
        return vars.GetVariable(name);
    }
    
    void WallModel::Builder(int numPoints_in, MPI_Comm comm_in)
    {
        partition.numNativePoints = numPoints_in;
        partition.numSolvePoints = numPoints_in;
        comm = comm_in;
    }
    
    WallModel::~WallModel(void)
    {
        
    }
}