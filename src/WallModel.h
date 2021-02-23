#ifndef HW2_WALL_MODEL_H
#define HW2_WALL_MODEL_H
#include "hw2Mpi.h"
#include "Partition.h"
#include "VarHandler.h"
namespace hw2
{
    class WallModel
    {
        public:
            WallModel(int numPoints_in, MPI_Comm comm_in);
            WallModel(int numPoints_in);
            ~WallModel(void);
            Variable* CreateVariable(std::string name, int dim = 1);
            Variable* GetVariable(std::string name);
            Variable* operator [] (std::string name);
        private:
            void Builder(int numPoints_in, MPI_Comm comm_in);
            Partition partition;
            MPI_Comm comm;
            VarHandler vars;
    };
}

#endif