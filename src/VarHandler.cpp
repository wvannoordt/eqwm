#include "VarHandler.h"
#include "hw2Error.h"
namespace hw2
{
    VarHandler::VarHandler(void)
    {
        
    }
    
    bool VarHandler::HasVariable(std::string name)
    {
        return (variables.find(name) != variables.end());
    }
    
    Variable* VarHandler::CreateVariable(std::string name, int dim, Partition* varPartition)
    {
        Variable* v = new Variable(name, dim, varPartition);
        variables.insert({name, v});
        return v;
    }
    
    Variable* VarHandler::GetVariable(std::string name)
    {
        if (!this->HasVariable(name)) hw2Error("Attempted to access a non-existent variable \"" + name + "\"");
        return variables[name];
    }
    
    VarHandler::~VarHandler(void)
    {
        for (auto it:variables)
        {
            delete it.second;
        }
    }
}