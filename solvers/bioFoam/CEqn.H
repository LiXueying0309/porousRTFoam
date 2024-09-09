{   fvScalarMatrix CEqn
    (
	//Inertial Terms
        fvm::ddt(eps, CbyC0)
       + fvm::div(phi,CbyC0) 

	//Viscous Terms
      == fvm::laplacian(eps*D,CbyC0)
  
      - eps*Mmax/C0*(mum/Yxs+ms)*CbyC0*MbbyMmax/(ks/C0+CbyC0)

    );

    CEqn.solve();
}

    solve(UEqn==-fvc::grad(p));
  if (piso.momentumPredictor()) 
    {
        solve
        (
            UEqn
            ==
            fvc::reconstruct
            (
               
                  - fvc::snGrad(p) * mesh.magSf()
		
            )
           
        );
    }

