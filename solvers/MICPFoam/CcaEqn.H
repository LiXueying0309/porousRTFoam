{   fvScalarMatrix CcaEqn
    (
	//Inertial Terms
        fvm::ddt(eps, Cca)
       + fvm::div(phi,Cca) 

	//Viscous Terms
      == fvm::laplacian(eps*Dca,Cca)
         - Kp*eps*min(Cca,Cco3)
    );

    CcaEqn.solve();
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
