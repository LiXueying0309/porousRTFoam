Info<< "Reading transportProperties\n" << endl;


IOdictionary transportProperties
(
    IOobject
    (
        "transportProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

dimensionedScalar muf
    (
        transportProperties.lookup("muf")
    );

dimensionedScalar rhof
    (
        transportProperties.lookup("rhof")
    );

dimensionedScalar D
    (
        transportProperties.lookup("D")
    );

dimensionedScalar Dca
    (
        transportProperties.lookup("Dca")
    );

dimensionedScalar Dco3
    (
        transportProperties.lookup("Dco3")
    );

dimensionedScalar a
    (
        transportProperties.lookup("a")
    );

dimensionedScalar b
    (
        transportProperties.lookup("b")
    );

dimensionedScalar c
    (
        transportProperties.lookup("c")
	);
    
dimensionedScalar MWCaCO3
    (
        transportProperties.lookup("MWCaCO3")
    );

dimensionedScalar Kp
    (
        transportProperties.lookup("Kp")
    );

dimensionedScalar rhoCaCO3
    (
        transportProperties.lookup("rhoCaCO3")
    );

Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh 
);

Info<< "Reading field GradP\n" << endl;
volVectorField GradP
(
    IOobject
    (
        "GradP",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    fvc::grad(p)
);

Info<< "Reading field Ccaco3\n" << endl;
volScalarField Ccaco3
(
    IOobject
    (
        "Ccaco3",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field Cca\n" << endl;
volScalarField Cca
(
    IOobject
    (
        "Cca",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field Cco3\n" << endl;
volScalarField Cco3
(
    IOobject
    (
        "Cco3",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field GradCco3\n" << endl;
volVectorField GradCco3
(
    IOobject
    (
        "GradCco3",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    fvc::grad(Cco3)
);

Info<< "Reading field Cna\n" << endl;
volScalarField Cna
(
    IOobject
    (
        "Cna",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field Ccl\n" << endl;
volScalarField Ccl
(
    IOobject
    (
        "Ccl",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading fluid velocity field 'U'\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading fluid fraction field eps\n" << endl;
volScalarField eps
(
    IOobject
    (
        "eps",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

// Defenition of Solid Indicator
volScalarField Solid
(
    IOobject
    (
        "Solid",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar ("Solid", dimensionSet(0,0,0,0,0,0,0), 0) 
);

#include "createPhi.H"

// Defining Mass Flux
surfaceScalarField rhofPhi
(
    IOobject
    (
        "rhofPhi",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
     rhof*phi
);

Info<< "Calculating averaged mass flux\n" << endl;
surfaceScalarField rhoPhiByEps
(
	IOobject
	(
        "rhoPhiByEps",
	runTime.timeName(),
	mesh,
	IOobject::READ_IF_PRESENT,
        IOobject::NO_WRITE
    ),
    rhofPhi*linearInterpolate(1/(eps+SMALL))
);

#include "readGravitationalAcceleration.H"
#include "readhRef.H"
#include "gh.H"

label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell
(
    p,
    piso.dict(),
    pRefCell,
    pRefValue
);

if (p.needReference())
{
    p += dimensionedScalar
    (
        "p",
        p.dimensions(),
        pRefValue - getRefCellValue(p, pRefCell)
    );
}

mesh.setFluxRequired(p.name());
// MULES Correction
tmp<surfaceScalarField> talphaPhiCorr0;

#include "createPorousMediaFields.H"
