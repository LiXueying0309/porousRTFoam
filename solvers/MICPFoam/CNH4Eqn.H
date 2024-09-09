{   fvScalarMatrix CNH4Eqn
    (
	//Inertial Terms
        fvm::ddt(eps, CNH4)
       + fvm::div(phi,CNH4) 

	//Viscous Terms
      == fvm::laplacian(eps*DNH4,CNH4)
         + 2*MbbyMmax*Mmax*Ku*eps*(Curea/(Km+Curea))*(KNH4/(KNH4+CNH4))
    );

    CNH4Eqn.solve();
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
