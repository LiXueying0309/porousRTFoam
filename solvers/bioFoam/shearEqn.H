{   fvScalarMatrix shearEqn
(
    volTensorField gradU(fvc::grad(U));
    volScalarField shearStress = muf * gradU.component(tensor::XY);

);

shearEqn.solve();
