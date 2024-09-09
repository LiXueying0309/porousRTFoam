    fvVectorMatrix UEqn
    (
	//Inertial Terms
        (1./eps)*(fvm::ddt(rhof, U) + fvm::div(rhoPhiByEps, U) )
	//Viscous Terms
      - (1./eps)*(fvm::laplacian(muf,U))
	//Implicit Darcy-Brinkman Drag Term
     + fvm::Sp(Drag,U) 
    );

    UEqn.relax();
 if (piso.momentumPredictor()) 
    {
        solve
        (
            UEqn
           == -fvc::grad(p)
        );
    }
