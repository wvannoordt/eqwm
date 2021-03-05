#include "hw2.h"
int main(void)
{
    // hw2::UserInput input;
    int numPoints = 10;
    hw2::globalSettings.debugLevel = 5;
    hw2::WallModelInputInfo info;
    hw2::WallModel model(numPoints, info);
    
    model["u_f"]->Fill(0.0);
    double* u_F = model["u_f"]->Data();
    // Array u = model["u"];
    // u[i] = ui
    // SolveResult result = model.Solve();
    // Array tau = model["tau"];
    // taui = tau[i]
}