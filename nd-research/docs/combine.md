# Create and Equilibrate a Box of Salt-Water and Nanoporous Graphene Sheets

1. Generate a salt-water box from a packmol file
    ```bash
    saltWaterBoxer -i box.pack
    ```

    \note check the seed!

2. Use NPGBuilder to create the graphene sheets
    ...

3. Ensure the box dimensions are the same for graphene and salt-water boxes
    ```bash
    modifyFiles -i graphene-combined.omd -o "$(grep Hmat graphene-combined.omd)" -n "$(grep Hmat box.omd)"
    ```

4. Combine the two simulation boxes
    ```bash
    omdCombined -u graphene-combined.omd -v box.omd -o saltWaterBox.omd
    ```

5. Replace `<MetaData>` section in the `.omd` file with the following:
    ```C++
    #include "graphene.inc"
    #include "/afs/crc.nd.edu/group/gezelter/cdrisko/.local/etc/includeFiles/molecNaCl.inc"
        
    component{
        type = "graphene";
        nMol = 2;
    }       
    
    component {
        type = "SPCE"; 
        nMol = 1510;
    }   
            
    component {     
        type = "Na+"; 
        nMol = 28;    
    }        
            
    component {     
        type = "Cl-"; 
        nMol = 28;        
    }        
            
    ensemble = NVT; 
    forceField = "ChargedSPF";
    forceFieldFileName = "ChargedSPF.frc";       
    electrostaticSummationMethod = "shifted_force";
    electrostaticScreeningMethod = "damped";     
    cutoffRadius = 12;        
    dampingAlpha = 0.18;      
    seed = 8675309; 
            
    targetTemp = 300;
    targetPressure = 1.0;     
    tauThermostat = 1e3;      
    tauBarostat = 1e4;        
            
    dt = 1.0;
    runTime = 1e6;  
    sampleTime = 10000;       
    statusTime = 1000;        
            
    statFileFormat = "TIME|TOTAL_ENERGY|POTENTIAL_ENERGY|KINETIC_ENERGY|TEMPERATURE|PRESSURE|VOLUME|CONSERVED_QUANTITY|PRESSURE_TENSOR";
            
    zconsTime = 1;  
    zconsTol = 0.01;

    zconstraint {   
        molIndex = 0; 
        kRatio = 0.5;
        zPos = -18.75;
    }

    zconstraint {
        molIndex = 1;
        kRatio = 0.5;
        zPos = 18.75;
    }
    ```

    \note check the seed!

6. Use some `openmd` tools to finalize the starting configurations

    ```bash
    omd2omd -i saltWaterBox.omd -o saltWaterBox-shifted.omd
    thermalizer -i saltWaterBox-shifted.omd -o warm.omd -t 300
    ```

7. Run openmd or submit to the CRC queue  (1 ns, NVT)
    ```bash
    groupSubmit -i warm.omd
    ```

8. ...
    ```bash
    energyArray=( $(grep Total\ Energy: warm.report) )
    energy=${energyArray[3]}
    thermalizer -i warm.eor -o equil.omd -e "$energy"

    modifyFiles -i equil.omd -o "ensemble = NVT;" -n "ensemble = NVE;"
    ```

9. Run openmd or submit to the CRC queue  (1 ns, NVE)
    ```bash
    groupSubmit -i equil.omd
    ```

10. ...
    ```bash
    npgCombiner -i equil.eor # optionally use -t with the highest value possible
    ```

11. Ensure the box dimensions are the same for npg sheets and equilibrated salt-water boxes
    ```bash
    modifyFiles -i p14x2-combined.omd -o "$(grep Hmat p14x2-combined.omd)" -n "$(grep Hmat equil_completed.omd)"
    modifyFiles -i p28-combined.omd -o "$(grep Hmat p28-combined.omd)" -n "$(grep Hmat equil_completed.omd)"
    ```

12. Combine the two simulation boxes
    ```bash
    omdCombined -u p14x2-combined.omd -v equil_completed.omd -o equil_p14x2.omd
    omdCombined -u p28-combined.omd -v equil_completed.omd -o equil_p28.omd
    ```

13. Replace `<MetaData>` section in the `.omd` file with the following:
    ```C++
    #include "/afs/crc.nd.edu/group/gezelter/cdrisko/.local/etc/includeFiles/npgBuilder/graphene.inc"
    #include "/afs/crc.nd.edu/group/gezelter/cdrisko/.local/etc/includeFiles/molecNaCl.inc"
        
    component{
        type = "graphene";
        nMol = 2;
    }       
    
    component {
        type = "SPCE"; 
        nMol = 1510;
    }   
            
    component {     
        type = "Na+"; 
        nMol = 28;    
    }        
            
    component {     
        type = "Cl-"; 
        nMol = 28;        
    }        
            
    ensemble = NVT; 
    forceField = "ChargedSPF";
    forceFieldFileName = "ChargedSPF.frc";       
    electrostaticSummationMethod = "shifted_force";
    electrostaticScreeningMethod = "damped";     
    cutoffRadius = 12;        
    dampingAlpha = 0.18;      
    seed = 8675309; 
            
    targetTemp = 300;
    targetPressure = 1.0;     
    tauThermostat = 1e3;      
    tauBarostat = 1e4;        
            
    dt = 1.0;
    runTime = 5e4;  
    sampleTime = 10000;       
    statusTime = 1000;        
            
    statFileFormat = "TIME|TOTAL_ENERGY|POTENTIAL_ENERGY|KINETIC_ENERGY|TEMPERATURE|PRESSURE|VOLUME|CONSERVED_QUANTITY|PRESSURE_TENSOR";
            
    zconsTime = 1;  
    zconsTol = 0.01;

    zconstraint {   
        molIndex = 0; 
        kRatio = 0.5;
        zPos = 18.75;
    }

    zconstraint {
        molIndex = 1;
        kRatio = 0.5;
        zPos = -18.75;
    }
    ```

    \note check the seed!
    \note check the molecule name!

14. ...
    ```bash
    thermalizer -i equil_p14x2.omd -o temp_p14x2.omd -t 300
    thermalizer -i equil_p28.omd -o temp_p28.omd -t 300
    ```

15. Run openmd or submit to the CRC queue (50 ps, NVT)
    ```bash
    groupSubmit -i temp_p14x2.omd
    groupSubmit -i temp_p28.omd
    ```
