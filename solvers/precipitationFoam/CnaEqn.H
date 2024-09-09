{   fvScalarMatrix CnaEqn
    (
	//Inertial Terms
        fvm::ddt(eps, Cna)
       + fvm::div(phi,Cna) 

	//Viscous Terms
      == fvm::laplacian(eps*Dco3,Cna)
      - 2*eps*Kp*min(Cca,Cco3)
    );
    CnaEqn.solve();
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
