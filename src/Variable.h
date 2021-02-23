#ifndef HW2_VARIABLE_H
#define HW2_VARIABLE_H
#include <string>
#include "Partition.h"
#include "DataBuffer.h"
namespace hw2
{
    class Variable
    {
        public:
            Variable(std::string name_in, int dim_in, Partition* varPartition);
            ~Variable(void);
            std::string GetName(void);
        private:
            std::string name;
            Partition* partition;
            int dim;
            DataBuffer<double> array;
    };
}

#endif