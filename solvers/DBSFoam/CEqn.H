{   fvScalarMatrix CEqn//构造体积矢量场矩阵
    (
	//Inertial Terms
        fvm::ddt(eps, C)
      // + fvm::div(phi,CbyC0) 

	//Viscous Terms
      == fvm::laplacian(eps*D,C)
     //    -kmax*Mb*C/(C+ks)
  
  //    - (Mmax*(mum/Yxs+ms)/C0)*CbyC0*MbbyMmax/(ks/C0+CbyC0)

    );

    CEqn.solve();
}
