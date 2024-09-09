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

dimensionedScalar mum
    (
        transportProperties.lookup("mum")
    );

dimensionedScalar Yxs
    (
        transportProperties.lookup("Yxs")
    );


dimensionedScalar ms
    (
        transportProperties.lookup("ms")
    );

dimensionedScalar rhof
    (
        transportProperties.lookup("rhof")
    );

dimensionedScalar D
    (
        transportProperties.lookup("D")
    );

dimensionedScalar Mmax
    (
        transportProperties.lookup("Mmax")
    );
    
dimensionedScalar tau_max
    (
        transportProperties.lookup("tau_max")
    );
    
dimensionedScalar U_attach
    (
        transportProperties.lookup("U_attach")
    );
    
dimensionedScalar C_det
    (
        transportProperties.lookup("C_det")
    );
    
dimensionedScalar attachmentValue
    (
        transportProperties.lookup("attachmentValue")
    );
    
dimensionedScalar detachmentValue
    (
        transportProperties.lookup("detachmentValue")
    );

dimensionedScalar Db
    (
        transportProperties.lookup("Db")
    );

dimensionedScalar ks
    (
        transportProperties.lookup("ks")
    );
dimensionedScalar C0
    (
        transportProperties.lookup("C0")
    );
dimensionedScalar rhoMb
    (
        transportProperties.lookup("rhoMb")
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

Info<< "Reading field MbbyMmax\n" << endl;
volScalarField MbbyMmax
(
    IOobject
    (
        "MbbyMmax",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
Info<< "Reading fluid velocity field 'shear'\n" << endl;
volVectorField shear
(
    IOobject
    (
        "shear",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh
);
Info<< "Reading field CbyC0\n" << endl;
volScalarField CbyC0
(
    IOobject
    (
        "CbyC0",
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
tmp<surfaceScalarField> talphaPhiCorr0;

#include "createPorousMediaFields.H"

