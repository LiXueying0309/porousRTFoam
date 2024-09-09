{   fvScalarMatrix CureaEqn
    (
	//Inertial Terms
        fvm::ddt(eps, Curea)
       + fvm::div(phi,Curea) 

	//Viscous Terms
      == fvm::laplacian(eps*Durea,Curea)
         -MbbyMmax*Mmax*Ku*eps*(Curea/(Km+Curea))*(KNH4/(KNH4+CNH4))
    );

    CureaEqn.solve();
    
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
