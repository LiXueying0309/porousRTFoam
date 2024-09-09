{   fvScalarMatrix CEqn
    (
	//Inertial Terms
        fvm::ddt(eps, C)
       + fvm::div(phi,C) 
	//Viscous Terms
      == fvm::laplacian(eps*D,C)
     - Madot
  );

    CEqn.solve();
}
