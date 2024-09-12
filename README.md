# porousRTFoam
porousRTFoam is an open-source software developed to simulate hydro-bio-geochemical processes in porous media using the well-known CFD platform OpenFOAM®. The software contains all OpenFOAM® functions, which makes it possible to solve the Darcy-Brinkman-Stokes equation together with other partial differential equations using the finite-volume method and support parallel computing. 
![figure2](https://github.com/porousRTFoam/figure2.png)


### 1. Organization of porousRTFoam
1. solvers: porousRTFoam is consist of dbsFoam, dbscFoam, dissolFoam, precipFoam, and bioFoam. 
![figure3](https://github.com/porousRTFoam/figure3.png)
2. cases: four kinds of test cases is shown in this release. The names of the folders are Flow_Solute_Transport, Reactive_Transport, Biofilm, and MICP.

### 2. Installation
All the solvers in porousRTFoam were been developed on OpenFOAM v7. Before installation, users should ensure OpenFOAM v7 is properly installed in the environment.
If the system has multi OpenFOAM versions, users should first source the environment to v7:
```source /the path where you install openfoam/openfoamv7/etc/bashrc```
Then enter each folders in solvers and run ```wmake``` to install the solvers.
Please note that additional libraries that are not included in the standard OpenFOAM user directory are required.

