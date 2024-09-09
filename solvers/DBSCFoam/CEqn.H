{   fvScalarMatrix CEqn
    (
	//Inertial Terms
        fvm::ddt(eps, C)
        + fvm::div(phi,C)
      == fvm::laplacian(eps*D,C)
    );

    CEqn.solve();
}
