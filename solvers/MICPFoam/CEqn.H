{   fvScalarMatrix CEqn
    (
	//Inertial Terms
        fvm::ddt(eps, CbyC0)
       + fvm::div(phi,CbyC0) 

	//Viscous Terms
      == fvm::laplacian(eps*D,CbyC0)
  
      - (Mmax*(mum/Yxs+ms)/C0)*CbyC0*MbbyMmax/(ks/C0+CbyC0)

    );

    CEqn.solve();
}
