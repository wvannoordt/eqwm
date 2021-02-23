#ifndef HW2_VARHANDLER_H
#define HW2_VARHANDLER_H
#include <vector>
#include <map>
#include <string>
#include "Variable.h"
#include "Partition.h"
namespace hw2
{
    class VarHandler
    {
        public:
            VarHandler(void);
            ~VarHandler(void);
            bool HasVariable(std::string name);
            Variable* CreateVariable(std::string name, int dim, Partition* varPartition);
            Variable* GetVariable(std::string name);
        private:
            std::map<std::string, Variable*> variables;
    };
}

#endif