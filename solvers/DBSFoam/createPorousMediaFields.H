//Permeability Models
Info<< "Reading intrinsic permeability field field K\n" << endl;
volScalarField K
(
    IOobject
    (
        "K",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
volScalarField k0("k0", K*(eps*eps*eps)/(max((1-eps)*(1-eps),SMALL)) ); //Uncomment for Kozeny-Carman
//volScalarField k0("k0", K); 
surfaceScalarField k0f("k0f",fvc::interpolate(k0,"k0"));


//Mobilities
volScalarField M ("M",k0/muf); 
//volScalarField L1 ("L",rho1*k0*kr1/mu1);	


//Drag Coefficient Calculation
//surfaceScalarField Dragf ("Dragf",1/Mf);
volScalarField Drag ("Drag", 1/M);
	

//Labeling the places that have porous media
forAll(eps,celli) 
{
	if(eps[celli]>0.99) 
	{	
	Solid[celli]=0; 
	}
	else
	{
	Solid[celli]=1; 
	}
}

forAll(mesh.boundary(), patchi) 
{
	forAll(Solid.boundaryField()[patchi],facei)
	{
		if(eps.boundaryField()[patchi][facei]>0.99) 
		{Solid.boundaryFieldRef()[patchi][facei]=0;}
		else
		{Solid.boundaryFieldRef()[patchi][facei]=1;}
	}
}

surfaceScalarField Solidf(fvc::interpolate(Solid));

//Eliminating intermediate values of Solid Indicator Function
forAll(Solidf,facei)
{
	if(Solidf[facei]<1) // if <1 ==0.  
	{	
	Solidf[facei]=0; 
	}
}


