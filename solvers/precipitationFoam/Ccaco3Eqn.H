{   
    scalar gradC_sat_value;
	scalar gaussianRandomValue;
	do {
		gaussianRandomValue = d(gen);
	} while (gaussianRandomValue < 0);

	scalar threshold = 0.8;
	scalar normalizedGaussianValue = 0.5 * (1.0 + std::erf(gaussianRandomValue/std::sqrt(2.0)));

	dimensionedScalar gradC_sat("gradC_sat",dimensionSet(0,-3,0,0,1,0,0),gradC_sat_value);

	volScalarField Rp = Kp*(Cca*Cco3/(Cca+Cco3))*eps*c*4*mag(-fvc::grad(eps));//MWCaCO3*

	Rp = pos(normalizedGaussianValue - threshold)*Rp;

	fvScalarMatrix Ccaco3Eqn
    (
	//Inertial Terms
		fvm::ddt(eps,Ccaco3) 
		==
		Rp    
	);

    Ccaco3Eqn.solve();

    forAll(Solid,celli) 
    {
      if(Solid[celli]==1) 
      
                { 
                Ccaco3[celli] =0;}
    }
  
   forAll(Ccaco3,celli) 
    {
      if(Ccaco3[celli]>0.3) 
      
                { Ccaco3[celli] = 0.3; 
                eps[celli] =0.0001;}
    }

 }
