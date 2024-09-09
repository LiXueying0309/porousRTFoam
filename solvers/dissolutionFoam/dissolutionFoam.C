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

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "postProcess.H"
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createControl.H"
    #include "createTimeControls.H"
    #include "createRDeltaT.H"
    #include "initContinuityErrs.H"
    #include "createFields.H"

   

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;
       #include "CourantNo.H"
        volScalarField k0("k0", K0*(eps*eps*eps)/(max((1-eps)*(1-eps),SMALL)) );
        volScalarField M ("M",k0/muf); 
        volScalarField Drag ("Drag", 1/M);
        volScalarField av ("av",4*eps*(1-eps)*mag(fvc::grad(eps)));
        volScalarField Madot  ("Madot",av*r*C);          
        volScalarField D ("D", Da*eps);
        {  
            #include "UEqn.H"  
            while (piso.correct())
            {
             #include "pEqn.H"
            }
         }
        #include "CEqn.H"
        Madot = av*r*C;
        const scalar& deltaT = mesh.time().deltaTValue();
        const Time& t = mesh.time();
        mineral = mineral-a*(rhof/rhos)*mineral.oldTime()*beta*Madot*mesh.time().deltaTValue(); 
        eps = 1-mineral;
        
        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;

    };
     
    ; Info<< "End\n" << endl;

    return 0;
}
// ************************************************************************* //
