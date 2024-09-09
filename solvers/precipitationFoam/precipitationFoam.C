/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    hybridPorousInterFoam

Description
    Solver for two-phase flow in hybrid-scale porous media containing porous 
    and solid-free regions. 
    
    In porous regions fluid flow is governed by two-phase Darcy's law
     
    In solid-free regions flow is modeled through the volume of fluid
    phase-fraction based interface capturing approach.

    The momentum and other fluid properties are of the "mixture" and a single
    momentum equation is solved.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "CMULES.H"
#include "EulerDdtScheme.H"
#include "localEulerDdtScheme.H"
#include "CrankNicolsonDdtScheme.H"
#include "subCycle.H"
#include "localEulerDdtScheme.H"
#include "fvcSmooth.H"
#include "pisoControl.H"
#include "singlePhaseTransportModel.H"
#include <cmath>
#include <cstdlib>
#include <random>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Constants for nucleation theory
const scalar A = 1.0e10;  // Define the system-specific constant
const scalar B = 5.0e-20; // Define the nucleation barrier constant
const scalar k = 1.380649e-23;  // Boltzmann constant in J/K
const scalar T0 = 298.15;  // Absolute temperature in Kelvin (25°C)

int main(int argc, char *argv[])
{
    #include "postProcess.H"
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createControl.H"
    #include "createTimeControls.H"
    #include "createRDeltaT.H"
    #include "createFields.H"
    //#include "readTransportProperties.H"
    #include "initContinuityErrs.H"
 
    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> d(0,1);


    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        #include "CourantNo.H"
        volScalarField  mt ("mt",fvc::ddt(Ccaco3));
        {
            #include "UEqn.H"
            while (piso.correct())
            {
                #include "pEqn.H"
               
            }
             #include "CcaEqn.H"
			 #include "Cco3Eqn.H"
             #include "Ccaco3Eqn.H"
             #include "setDeltaT.H"
             runTime++;
             mt=fvc::ddt(Ccaco3);
             fvc::ddt(eps) = -a*(1./rhoCaCO3)*mt*eps.oldTime(); 
             #include "updateVariables.H"
		}

        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;

    };
     
    ; Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
