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

dimensionedScalar rhos
    (
        transportProperties.lookup("rhos")
    );

dimensionedScalar Da
    (
        transportProperties.lookup("Da")
    );
dimensionedScalar r
    (
        transportProperties.lookup("r")
    );

dimensionedScalar beta
    (
        transportProperties.lookup("beta")
    );
dimensionedScalar a
    (
        transportProperties.lookup("a")
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

Info<< "Reading field C\n" << endl;
volScalarField C
(
    IOobject
    (
        "C",
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

Info<< "Reading fluid fraction field mineral\n" << endl;
volScalarField mineral
(
    IOobject
    (
        "mineral",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
   1-eps
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

Info<< "Reading fluid fraction field gradeps\n" << endl;
volVectorField gradeps
(
    IOobject
    (
        "gradeps",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    fvc::grad(eps)
);

Info<< "Reading fluid fraction field gradeps1\n" << endl;
volScalarField gradeps1
(
    IOobject
    (
        "gradeps1",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mag(fvc::grad(eps))
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
