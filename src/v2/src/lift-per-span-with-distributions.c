#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <uxhw.h>

// All quantities are in SI units.

const double g = 9.81;
const double R = 287.05;         // Specific gas constant for dry air in (J/kg/K)
const double densityLiquid = 1000;  //  Liquid inside Pitot tube column 


void loadInputs(double* altitude, double* ambientTemperature, double* ambientPressure, double* chordLength, double* deltaColumnHeight)
{
    *altitude = 10.0;
    *ambientTemperature = 281.65;   // ISA 
    *ambientPressure = 88375.17;     // ISA
   
    *chordLength = UxHwDoubleUniformDist(0.095,0.15);
    *deltaColumnHeight = UxHwDoubleUniformDist(0.056,0.109);

}

double getDensity(double ambientTemperature, double ambientPressure)
{
    double density;
    density = ambientPressure / (R * ambientTemperature);
    printf("\n Density = %f", density);
    return density;
}

double getReynoldsNumber(double density, double velocity, double chordLength, double ambientTemperature)
{
    double dynamicViscosity;
    // mu(T) = mu_0 * (T_0 + S) / (T + S) * (T / T_0)^(3/2)
    double S = 110.00;
    double mu_0 = 1.789E-5;
    double T_0 = 273.15;
    dynamicViscosity = mu_0 * (T_0 + S) / (ambientTemperature + S) * pow((ambientTemperature / T_0),1.5);
    double ReyNum = density * velocity * chordLength / dynamicViscosity;
    printf("\n Dynamic viscosity = %f \n ReyNum = %f", dynamicViscosity, ReyNum);
    return ReyNum;
}

double getCL(double ReynoldsNumber)
{  
    // Cl : Lift coefficient
    // Data obtained from: http://airfoiltools.com/airfoil/details?airfoil=naca23012-il#polars
    // Making use of a Lookup table for given airfoil; fixed Mach number and angle of attack (= zero degrees)
    // Estimation of lift coefficient by linear interpolation/extrapolation on non-uniform empirical data
    
    // ReyNum[] = {50000, 100000, 200000, 500000, 1000000};
    // Cl[] = {0.0256, 0.2908, 0.1833, 0.1175, 0.1241};
    
    
    double interpolatedCL, extrapolatedCL, interpolatedParaCL, interpolatedLinearCL, extrapolatedLinearCL, extrapolatedParaCL, a, c, x1, x2, y1, y2;
    
    if( ReynoldsNumber >= 50000 & ReynoldsNumber < 100000)
    {
        x1 = 50000;
        x2 = 100000;
        y1 = 0.0256;
        y2 = 0.2908;
        interpolatedLinearCL = y1 + (ReynoldsNumber - x1) * (y2 - y1)/(x2 - x1);
        a = (pow(y1,2) - pow(y2,2))/(4*(pow(x1,2) - pow(x2,2)));
        c = pow(y1,2) - (4*a*x1);
        interpolatedParaCL = sqrt(4*a*ReynoldsNumber + c); 
        if(interpolatedLinearCL > interpolatedParaCL)
        {
            interpolatedCL = UxHwDoubleUniformDist(interpolatedParaCL,interpolatedLinearCL);
            
        }

        else
        {
            interpolatedCL = UxHwDoubleUniformDist(interpolatedLinearCL,interpolatedParaCL);
        }
    }
    
    else if( ReynoldsNumber >= 100000 & ReynoldsNumber < 200000)
    {
        x1 = 100000;
        x2 = 200000;
        y1 = 0.2908;
        y2 = 0.1833;
        interpolatedLinearCL = y1 + (ReynoldsNumber - x1) * (y2 - y1)/(x2 - x1);
        a = (pow(y1,2) - pow(y2,2))/(4*(pow(x1,2) - pow(x2,2)));
        c = pow(y1,2) - (4*a*x1);
        interpolatedParaCL = sqrt(4*a*ReynoldsNumber + c); 
        if(interpolatedLinearCL > interpolatedParaCL)
        {
            interpolatedCL = UxHwDoubleUniformDist(interpolatedParaCL,interpolatedLinearCL);
        }

        else
        {
            interpolatedCL = UxHwDoubleUniformDist(interpolatedLinearCL,interpolatedParaCL);
        }
    }
    
    else if( ReynoldsNumber >= 200000 & ReynoldsNumber < 500000)
    {
        x1 = 200000;
        x2 = 500000;
        y1 = 0.1833;
        y2 = 0.1175;
        interpolatedLinearCL = y1 + (ReynoldsNumber - x1) * (y2 - y1)/(x2 - x1);
        a = (pow(y1,2) - pow(y2,2))/(4*(pow(x1,2) - pow(x2,2)));
        c = pow(y1,2) - (4*a*x1);
        interpolatedParaCL = sqrt(4*a*ReynoldsNumber + c); 
        if(interpolatedLinearCL > interpolatedParaCL)
        {
            interpolatedCL = UxHwDoubleUniformDist(interpolatedParaCL,interpolatedLinearCL);
        }

        else
        {
            interpolatedCL = UxHwDoubleUniformDist(interpolatedLinearCL,interpolatedParaCL);
        }
    }
    
    else if( ReynoldsNumber >= 500000 & ReynoldsNumber < 1000000)
    {
        x1 = 500000;
        x2 = 1000000;
        y1 = 0.1175;
        y2 = 0.1241;
        interpolatedLinearCL = y1 + (ReynoldsNumber - x1) * (y2 - y1)/(x2 - x1);
        a = (pow(y1,2) - pow(y2,2))/(4*(pow(x1,2) - pow(x2,2)));
        c = pow(y1,2) - (4*a*x1);
        interpolatedParaCL = sqrt(4*a*ReynoldsNumber + c); 
        if(interpolatedLinearCL > interpolatedParaCL)
        {
            interpolatedCL = UxHwDoubleUniformDist(interpolatedParaCL,interpolatedLinearCL);
        }

        else
        {
            interpolatedCL = UxHwDoubleUniformDist(interpolatedLinearCL,interpolatedParaCL);
        }
    }
    
    else if(ReynoldsNumber >= 1000000)
    {
        printf("\n Reynolds number = %f",ReynoldsNumber);
        
        x1 = 500000;
        x2 = 1000000;
        y1 = 0.1175;
        y2 = 0.1241;
        
        extrapolatedLinearCL = y2 + (ReynoldsNumber - x2) * (y2 - y1)/(x2 - x1);
        a = (pow(y1,2) - pow(y2,2))/(4*(pow(x1,2) - pow(x2,2)));
        c = pow(y1,2) - (4*a*x1);
        extrapolatedParaCL = sqrt(4*a*ReynoldsNumber + c); 
        if(extrapolatedLinearCL > extrapolatedParaCL)
        {
            extrapolatedCL = UxHwDoubleUniformDist(extrapolatedParaCL,extrapolatedLinearCL);
        }

        else
        {
            extrapolatedCL = UxHwDoubleUniformDist(extrapolatedLinearCL,extrapolatedParaCL);
        }
        printf("\nCl = %f", extrapolatedCL);
        return extrapolatedCL; 
    }

    else
    {
        x1 = 50000;
        x2 = 100000;
        y1 = 0.0256;
        y2 = 0.2908;
        extrapolatedLinearCL = y1 + (ReynoldsNumber - x1) * (y2 - y1)/(x2 - x1);
        a = (pow(y1,2) - pow(y2,2))/(4*(pow(x1,2) - pow(x2,2)));
        c = pow(y1,2) - (4*a*x1);
        extrapolatedParaCL = sqrt(4*a*ReynoldsNumber + c); 
        if(extrapolatedLinearCL > extrapolatedParaCL)
        {
            extrapolatedCL = UxHwDoubleUniformDist(extrapolatedParaCL,extrapolatedLinearCL);
        }

        else
        {
            extrapolatedCL = UxHwDoubleUniformDist(extrapolatedLinearCL,extrapolatedParaCL);
        }
        printf("\nCl = %f", extrapolatedCL);
        return extrapolatedCL;

    }
    printf("\nCl = %f", interpolatedCL); 
    return interpolatedCL;
}

double getVelocity(double deltaColumnHeight, double densityAir)
{
    double v;

    v = sqrt(2 * g * deltaColumnHeight * (densityLiquid/densityAir));
    printf("\n Velocity = %f", v);
    return v;
}


double getLift(double altitude, double ambientTemperature, double ambientPressure, double deltaColumnHeight, double chordLength)
{
    double densityAir, liftCoefficient, lift, reynoldsNumber, velocity;
    densityAir = getDensity(ambientTemperature,ambientPressure);
    velocity = getVelocity(deltaColumnHeight, densityAir);
    reynoldsNumber = getReynoldsNumber(densityAir, velocity, chordLength, ambientTemperature);
    liftCoefficient = getCL(reynoldsNumber);
    lift = 0.5 * liftCoefficient * densityAir * pow(velocity,2) * chordLength;
    return lift;
}

int main() 
{
    double altitude, ambientTemperature, ambientPressure, chordLength;
    double deltaColumnHeight, liftPerSpan;
    loadInputs(&altitude, &ambientTemperature, &ambientPressure, &chordLength, &deltaColumnHeight);
    printf("ambientTemp = %f \t ambientPressure = %f", ambientTemperature, ambientPressure);
    liftPerSpan = getLift(altitude, ambientTemperature, ambientPressure, deltaColumnHeight,chordLength);
    printf("\nLift per span = %.2f", liftPerSpan);
    return 0;
}
