#include "Variable.h"
#include "hw2Screen.h"
namespace hw2
{
    Variable::Variable(std::string name_in, int dim_in, Partition* varPartition)
    {
        name = name_in;
        partition = varPartition;
        dim = dim_in;
        WriteLine(5, "Allocate variable \"" + name + "\"");
        array.SetSize(dim*partition->numSolvePoints);
    }
    
    double* Variable::Data(void)
    {
        return array.data;
    }
    
    void Variable::Fill(double val)
    {
        array.Fill(val);
    }
    
    std::string Variable::GetName(void)
    {
        return name;
    }
    
    Variable::~Variable(void)
    {
        
    }
}