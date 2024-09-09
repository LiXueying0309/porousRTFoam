volTensorField gradU(fvc::grad(U));
volScalarField shearStress = muf * gradU.component(tensor::XY);
volScalarField phi_det = pos(shearStress - tau_max) * (1 - exp(-C_det * (shearStress - tau_max) / tau_max));
volScalarField detachmentRate = phi_det * detachmentValue;
volScalarField attachmentRate = pos(U.component(0) - U_attach) * attachmentValue;

{
volScalarField conditionalAttachmentRate
        (
            IOobject
            (
                "conditionalAttachmentRate",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            mesh,
            dimensionedScalar("zero", dimensionSet(0, 0, -1, 0, 0), 0.0) // Initialize with 0
        );

        forAll(mesh.C(), celli) // Loop over all cells
        {
            if (mesh.C()[celli].x() < 0.05 && mesh.C()[celli].x() > -0.05) // Check x-coordinate of cell center, convert mm to meters
            {
                conditionalAttachmentRate[celli] = attachmentRate[celli];
            }
        }

fvScalarMatrix MEqn
(
    fvm::ddt(eps, MbbyMmax) 
    ==
    eps*fvm::laplacian(Db, MbbyMmax)
    + fvm::div(phi, MbbyMmax)
    + eps*(mum/Yxs + ms)*Yxs*CbyC0*MbbyMmax/(ks/C0 + CbyC0)
    - eps*Yxs*ms*MbbyMmax
    + eps*conditionalAttachmentRate
    - eps*detachmentRate
);

MEqn.solve();

    forAll(Solid,celli) 
    {
      if(Solid[celli]==1) 
      
                { //MbbyMmax[celli] = 1; 
                MbbyMmax[celli] =0;}
    }
  
   forAll(MbbyMmax,celli) 
    {
      if(MbbyMmax[celli]>0.3) 
      
                { MbbyMmax[celli] = 0.3; 
                eps[celli] =0.0001;}
      if(MbbyMmax[celli]<-0.0001) 
      
                { MbbyMmax[celli] = 0; 
                eps[celli] =1;}
    }
   }


