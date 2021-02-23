#ifndef HW2_PARTITION_H
#define HW2_PARTITION_H

namespace hw2
{
    struct Partition
    {
        int numNativePoints; // points passed by the external solver on this proc
        int numSolvePoints; //the total number of points to solve (after possible load-balancing)
    };
};

#endif