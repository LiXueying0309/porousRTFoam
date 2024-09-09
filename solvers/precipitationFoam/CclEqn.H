{   fvScalarMatrix CclEqn
    (
	//Inertial Terms
        fvm::ddt(eps, Ccl)
       + fvm::div(phi,Ccl) 

	//Viscous Terms
      == fvm::laplacian(eps*Dca,Ccl)  
      - 2*eps*Kp*min(Cca,Cco3)
    );
    CclEqn.solve();
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
