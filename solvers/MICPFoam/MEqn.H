{   fvScalarMatrix MEqn
    (
	//Inertial Terms
        fvm::ddt(MbbyMmax) 
      ==Db*CbyC0*fvm::laplacian(pow(MbbyMmax*ops/(1.0-MbbyMmax),4.),MbbyMmax) 
      + Mmax*(mum/Yxs+ms)*(Yxs/Mmax)*CbyC0*MbbyMmax/(ks/C0+CbyC0)-(Yxs/Mmax)*(ms*Mmax)*MbbyMmax
    );
    
 forAll(eps,celli) 
   {
  	if(eps[celli]>0.1) 
         {
           	if(MbbyMmax[celli]<1) 	   	
               	{MEqn.solve(); }
	}

	else
		{
		MbbyMmax[celli] = 0;
		}      
   }

   forAll(MbbyMmax,celli)
   {
       if(MbbyMmax[celli] >= 1)
        {Solid[celli] = 1;
         eps[celli] =0;
        }
        else
        {Solid[celli] = 0;
        eps[celli] = 1;

        }
   }
}


