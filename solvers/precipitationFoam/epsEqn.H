{
        fvScalarMatrix epsEqn
        (
       fvm::ddt(eps)  ==  -a*(1./rhoCaCO3)*fvc::ddt(Ccaco3)*eps.oldTime()
        );

 epsEqn.solve();

eps.correctBoundaryConditions();
eps.min(0.00000001);
eps.max(1);
}

forAll(eps,celli) 
{
	if(eps[celli]>0.5) 
	{	
	Solid[celli]=0; 
	}
	else
	{
	Solid[celli]=1; 
	}
}
