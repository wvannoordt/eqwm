#ifndef HW2_WALL_MODEL_INPUT_INFO_H
#define HW2_WALL_MODEL_INPUT_INFO_H

namespace hw2
{
    enum ViscousLaw
    {
        constantViscosity,
        sutherlandsLaw
    };
    
    struct ConfigurationInfo
    {
        double gpuAllocationRatio = 0.0;
        int rayDim = 30;
        int maxIterations = 100;
        double wallSpacing = 1e-6;
        bool alwaysReinitialize = false;
        double timeStep = 1e-5;
        int solveSkip = 1;
        bool laminarOnSolveFail = false;
        bool loadBalance = false;
        double errorTolerance = 1e-7;
    };
    
    struct FluidInfo
    {
        double wallTemperature = 300.0;
        bool adiabaticWall = false;
        double fluidCp = 1005.0;
        double turbPradntl = 0.9;
        double fluidPrandtl = 0.72;
        double vanDriestAPlus = 17.0;
        double gasConstant = 287.0;
        bool isCompressible = true;
        double suthViscRef = 1.45151376745308e-06;
        double suthTRef = 110.4;
        ViscousLaw viscLaw = constantViscosity;
    };
    
    namespace MomentumEquation
    {
        enum MomentumEquation
        {
            linear,
            allmaras,
            equilibriumODE
        };
    }
    
    namespace TurbulenceEquation
    {
        enum TurbulenceEquation
        {
            vanDriest,
            SaODE
        };
    }
    
    namespace EnergyEquation
    {
        enum EnergyEquation
        {
            linear,
            equilibriumODE
        };
    }
    
    struct MomentumEquationInfo
    {    
        double underRelaxationFactor = 0.9;
        MomentumEquation::MomentumEquation equation = MomentumEquation::equilibriumODE;
    };
    
    struct TurbulenceEquationInfo
    {        
        double underRelaxationFactor = 0.9;
        TurbulenceEquation::TurbulenceEquation equation = TurbulenceEquation::vanDriest;
    };
    
    struct EnergyEquationInfo
    {
        double underRelaxationFactor = 0.9;
        EnergyEquation::EnergyEquation equation = EnergyEquation::equilibriumODE;
    };
    
    struct WallModelInputInfo
    {
        ConfigurationInfo configInfo;
        FluidInfo fluidInfo;
        MomentumEquationInfo momentumEquationInfo;
        TurbulenceEquationInfo turbulenceEquationInfo;
        EnergyEquationInfo energyEquationInfo;
    };
};

#endif