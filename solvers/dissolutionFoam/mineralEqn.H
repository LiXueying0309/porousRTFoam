{
        fvScalarMatrix epssEqn
        (
        fvm::ddt(rhos,epss)  == -beta*Madot
        );

 epssEqn.solve();

eps.correctBoundaryConditions();
eps.min(0);
eps.max(1);
}
