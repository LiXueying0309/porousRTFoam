{   fvScalarMatrix Cco3Eqn
    (
	//Inertial Terms
        fvm::ddt(eps, Cco3)
       + fvm::div(phi,Cco3) 

	//Viscous Terms
      == fvm::laplacian(eps*Dco3,Cco3)
         + MbbyMmax*Mmax*Ku*eps*(Curea/(Km+Curea))*(KNH4/(KNH4+CNH4))
         - Kp*eps*min(Cca,Cco3)
    );

    Cco3Eqn.solve();
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
