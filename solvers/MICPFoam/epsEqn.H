{       fvScalarMatrix epsEqn
        (
        fvm::ddt(eps)  ==  -1./rhoCaCO3*fvc::ddt(Ccaco3)-Mmax*(1./rhoMb)*fvc::ddt(MbbyMmax)
        );
epsEqn.relax();
 epsEqn.solve();

eps.correctBoundaryConditions();
eps.min(0);
eps.max(1);

forAll(eps,celli) 
{
	if(eps[celli]<0.5) 
	{	
	Solid[celli]=0; 
	}
	else
	{
	Solid[celli]=1; 
	}
}
}
