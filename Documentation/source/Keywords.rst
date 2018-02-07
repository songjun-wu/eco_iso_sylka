Configuration (main) file keywords
==================================

**PATH DEFINITION SECTION**

.. csv-table:: 
   :header: "Keyword", "Type", "Description"
   :widths: "auto"

    Maps\_Folder , System Path, Path to folder with land surface information 
    Clim\_Maps\_Folder , System Path , Path to folder with Climate information 
    Output\_Folder , System Path, Path to folder where outputs will be written 

**TRACKING SECTION**
    
.. csv-table::
   :header: "Keyword", "Type", "Description"
   :widths: 35, 5, 5, 55
    
    Tracking , option, Switch 1/0 to turn water tracking (isotopes and/or ages) on (1) or off (0)
    TrackingConfig , System Path, Location and name of the tracking configuration file.

.. csv-table:: **OPTIONS**
   :header: "Keyword", "Type", "Description"
   :widths: "auto"
    
    MapTypes, option, Format of maps. In this version the format is *csf* (PCRaster)
    Species\_State\_Variable\_Input\_Method, option, Specifies the input format of the vegetation state variables. Options are *table} or *maps}
    Vegetation\_dynamics , option, Switch 1/0 to turn vegetation allocation and growth component on (1) or off (0)
    Reinfiltration , option, Switch 1/0 to turn reinfiltration on (1) or off (0)
    Aerodyn\_resist\_opt , option, Switches between different aerodynamic resistance formulations. 0: Penman; 1: Thom and Oliver (1977) 
    Soil\_resistance\_opt , option, Switches between different soil resistance formulations. \n0: No resistance; \n1: Passerat de Silans et al (1989); \n2: Sellers et al., JGR (1992); \n3: Sakaguchi and Zeng, JGR (2009)

.. csv-table:: **TIME CONTROLS**
   :header: "Keyword", "Type", "Units", "Description"
   :widths: 35, 5, 5, 55

    Simul\_start, Integer, Seconds, Time of simulation start. In the current version this value must be 0 
    Simul\_end, Integer, Seconds, Time when simulation ends in seconds. This value indicates the total simulated time 
    Simul\_tstep , Integer , Seconds , Size of the integration time step 
    Clim\_input\_tstep , Integer , Seconds , Time step of climate forcing. Typically it is the same as *Simul\_tstep} but can be larger (i.e. climate inputs are daily but we are using an hourly integration time step). *Clim\_input\_tstep} cannot be smaller than *Simul\_tstep} 
    Report\_interval , Integer , Seconds , Intervals between time series outputs. *Report\_interval} cannot be smaller than *Simul\_tstep} and typically it is equal to *Simul\_tstep}
    ReportMap\_interval , Integer , Seconds , Intervals between maps outputs. *ReportMap\_interval} cannot be smaller than *Simul\_tstep}.
    
.. csv-table:: **Climate information** (maps and binary files must be placed in` `Clim\_Maps\_Folder``)
   :header: "Keyword", "Type", "Units", "Description"
   :widths: 35, 5, 5, 55
    
    Snow\_rain\_temp\_threshold , scalar , :math:`^{\circ}C`, Air temperature threshold for snow/rain transition
    ClimateZones ,  Map file name , integers , Map identifying the climate zones
    Isohyet\_map ,  Map file name , - , This map allows to redistribute rainfall within a climate zone. It is a map with multiplication factors for rain in a given pixel. A map containing 1 over the domain has the effect of overriding this  input (does not modify the precipitation input)
    Precipitation , Binary climate file , :math:`ms^{-1}`, Precipitation input 
    AirTemperature , Binary climate file , :math:`^{\circ}C`, Average air temperature
    MaxAirTemp , Binary climate file , :math:`^{\circ}C`, Maximum air temperature
    MinAirTemp, Binary climate file , :math:`^{\circ}C`, Maximum air temperature
    RelativeHumidity, Binary climate file , :math:`kPakPa^{-1}`, Average air temperature
    WindSpeed, Binary climate file , :math:`ms^{-1}`, Wind speed
    IncomingLongWave, Binary climate file , :math:`Wm^{-2}`, Incoming long wave radiation
    IncomingShortWave, Binary climate file , :math:`Wm^{-2}`, Incoming solar radiation

.. csv-table:: **Drainage network** (Files must be located in ``Maps_Folder``)
   :header: "Keyword", "Type", "Units", "Description"
   :widths: 35, 5, 5, 55

    local\_drain\_direc , Map file name , - , D8 steepest descent ldd 
    channel\_width , Map file name , :math:`m`, mask with width of channel network. Pixels with no channel must be 0 or nodata. Positive numbers indicate the width of the channel in the pixel 
    channel\_gw\_transfer\_param , Map file name ,` m^{-1}`, Coefficient controlling transfers of water from the subsurface system to the channel 
    mannings\_n , Map file name ,` sm^{-1/3}`, Manning's n roughness coefficient for channel 

.. csv-table:: **Initial conditions for soil states**  (Files must be located in ```Maps\_Folder``) 
   :header: "Keyword", "Type", "Units", "Description"
   :widths: 35, 5, 5, 55
      
   Streamflow , Map file name , :math:`m^3s^{-1}`, Streamflow
   snow\_water\_equivalent , Map file name , :math:`m`, Snow water equivalent
   Soil\_moisture\_1 , Map file name , :math:`m^3m^{-3}`, Volumetric soil water content for topmost soil layer
   Soil\_moisture\_2 , Map file name , :math:`m^3m^{-3}`, Volumetric soil water content for layer 3
   Soil\_moisture\_3 , Map file name , :math:`m^3m^{-3}`, Volumetric soil water content of bottommost layer
   Soil\_temperature , Map file name , :math:`^{\circ}C`, Soil temperature at boundary of thermal layer 

.. csv-table:: **Soil parameters** (Files must be located in ``Maps_Folder``)
   :header: "Keyword", "Type", "Units", "Description"
   :widths: 35, 5, 5, 55

   DEM ,  Map file name , :math:`m`, Digital elevation model
   Slope, Map file name , :math:`mm^{-1}`, Local terrain slope. Rise over run
   Horiz\_Hydraulic\_Conductivity , Map file name , :math:`ms^{-1}`, Effective soil hydraulic conductivity
   Vert\_Horz\_Anis\_ratio , Map file name , :math:`[-]`, Ratio of vertical to horizontal hydraulic conductivity
   Terrain\_Random\_Roughness , Map file name , :math:`m`, Local surface roughness 
   Porosity , Map file name , - , Soil porosity 
   Air\_entry\_pressure , Map file name , :math:`m`, Soil air entry pressure 
   Brooks\_Corey\_lambda , Map file name , - , Pore size distribution 
   Residual\_soil\_moisture , Map file name , :math:`m^{3}m^{-3}`, Minimum allowed volumetric soil water content 
   Soil\_depth , Map file name , :math:`m`, Soil depth 
   Depth\_soil\_layer\_1 , Map file name , :math:`m`, Depth of topmost soil layer 
   Depth\_soil\_layer\_2 , Map file name , :math:`m`, Depth of second soil layer 
   Veget\_water\_use\_param1 , Map file name , :math:`m`, Vegetation water use parameter as per Landsberg and Waring (1997) 
   Veget\_water\_use\_param2 , Map file name , :math:`m`, Vegetation water use parameter as per Landsberg and Waring (1997) 
..   Fraction\_roots\_soil\_layer\_1 , Map file name , - , Fraction of roots in topmost soil layer. Sum of fraction of roots in soil layer 1 and 2 must be less than 1 
..   Fraction\_roots\_soil\_layer\_2 , Map file name , - , Fraction of roots in second soil layer. Sum of fraction of roots in soil layer 1 and 2 must be less than 1
   Root\_profile\_coeff , Map file name , :math:`m^{-1}` , Coefficient for the exponentiall-decreasing root profile. 
   Albedo , Map file name , - , Surface albedo 
   Surface\_emissivity , Map file name , - , Surface emissivity/absorptivity 
   Dry\_Soil\_Heat\_Capacity , Map file name , :math:`Jm^{-3}K^{-1}`, Heat capacity of soil solid particles 
   Dry\_Soil\_Therm\_Cond , Map file name , :math:`Wm^{-1}K^{-1}`, Thermal conductivity of soil solid particles 
   Damping\_depth , Map file name , :math:`m`, Depth of bottom of second soil thermal layer 
   Temp\_at\_damp\_depth , Map file name , :math:`^{\circ}C`, Soil temperature at damping depth 
   Snow\_Melt\_Coeff , Map file name , :math:`m^{\circ}C^{-1}`, Snowmelt coefficient factor 
   Soil\_bedrock\_leakance , Map file name , - , Factor between 0 and 1 defining the vertical hydraulic conductivity at the soil-bedrock interface (in proportion of soil Kv) 
   
.. csv-table:: **Forest parameters** (Files must be located in ``Maps_Folder``) 
   :header: "Keyword", "Type", "Units", "Description"
   :widths: 35, 5, 5, 55

   ForestPatches ,  Map file name , integers , Map identifying forest categories (patches)
   Number\_of\_Species , Integer , -  , Number of vegetation types included in the simulation 
   Species\_Parameters , Parameter table , - , Table containing parameter information for each simulated vegetation type 
   
.. csv-table:: **Vegetation tables** (*needed only if* ``Species_State_Variable_Input_Method=tables``)
   :header: "Keyword", "Type", "Units", "Description"
   :widths: 35, 5, 5, 55
   
   Species\_Proportion\_Table , Variable table , `m^{2} m^{-2}` , Table with initial proportion of covered area (canopy cover) for each vegetation type with respect to cell area 
   Species\_StemDensity\_Table , Variable table , :math:`trees m^{-2}` , Table with initial tree density for each vegetation type 
   Species\_LAI\_Table , Variable table , :math:`m^{2} m^{-2}` , Table with initial leaf area index for each vegetation type 
   Species\_AGE\_Table , Variable table , :math:`years` , Table with initial average age each vegetation type 
   Species\_BasalArea\_Table , Variable table , :math:`m^{2}` , Table with initial total basal area per vegetation type 
   Species\_Height\_table , Variable table , :math:`m` , Table with initial effective height per vegetation type 
   Species\_RootMass\_table , Variable table , :math:`g m^{-3}` , Table with initial root mass per volume of soil for each vegetation type 
   
**Map report switches**

Written outputs files are csf maps.

.. csv-table::
   :header: "Keyword", "Units", "Description", "File root"
   :widths: "auto"
   
   Report\_Long\_Rad\_Down, :math:`W m^{-2}`, Downwelling long wave (infrared) radiation at the top of the canopy (climate input), LDown
   Report\_Short\_Rad\_Down , :math:`W m^{-2}`, Incoming shortwave (visible) radiation at the top of canopy (climate input), Sdown 
   Report\_Precip , :math:`m s^{-1}`, Precipitation (climate input), Pp
   Report\_Rel\_Humidity , :math:`Pa^{1} Pa^{-1}`, Relative humidity in the atmosphere (climate input), RH  
   Report\_Wind\_Speed , :math:`m s^{-1}`, Horizontal wind speed (climate input), WndSp 
   Report\_AvgAir\_Temperature , :math:`^{\circ}C`, Average air temperature (climate input), Tp  
   Report\_MinAir\_Temperature , :math:`^{\circ}C`, Minimum air temperature (climate input), TpMin
   Report\_MaxAir\_Temperature , :math:`^{\circ}C`, Maximum air temperature (climate input), TpMax
   Report\_SWE , :math:`m` , Snow water equivalent, SWE
   Report\_Infilt\_Cap , :math:`m s^{-1}`, Infiltration capacity, IfCap
   Report\_Streamflow  , :math:`m^{3}s^{-1}`, Channel discharge, Q  
   Report\_Soil\_Water\_Content\_Average , :math:`m^{3}m^{-3}`, Average volumetric water content for entire soil profile, SWCav
   Report\_Soil\_Water\_Content\_Up  , :math:`m^{3}m^{-3}`, Average volumetric water content for the two upper soil layers, SWCup
   Report\_Soil\_Water\_Content\_L1  , :math:`m^{3}m^{-3}`, Volumetric water content for topmost soil layer, SWC1
   Report\_Soil\_Water\_Content\_L2  , :math:`m^{3}m^{-3}`, SWC2, 1: Volumetric water content for second soil layer, SWC2
   Report\_Soil\_Water\_Content\_L3  , :math:`m^{3}m^{-3}`, SWC3, 1: Volumetric water content for bottommost soil layer, SWC3
   Report\_WaterTableDepth  , :math:`m` Depth the equivalent water table using the average soil moisture, WTD
   Report\_Soil\_Sat\_Deficit  , :math:`m`, Meters of water needed to saturate soil. SatDef
   Report\_Ground\_Water  , :math:`m`, Meters of water above field capacity in the third hydrologic layer, GW
   Report\_Soil\_Net\_Rad  , :math:`Wm^{-2}`, Soil net radiation integrated over the grid cell, NRs 
   Report\_Soil\_LE  , :math:`Wm^{-2}`, Latent heat for surface layer. LEs
   Report\_Sens\_Heat  , :math:`Wm^{-2}`, Sensible heat for surface layer, SensH
   Report\_Grnd\_Heat  , :math:`Wm^{-2}`, Ground heat, GrndH  
   Report\_Snow\_Heat , :math:`Wm^{-2}`, Turbulent heat exchange with snowpack, SnowH 
   Report\_Soil\_Temperature , :math:`^{\circ}C`, Soil temperature at the bottom of first thermal layer, Ts
   Report\_Skin\_Temperature  , :math:`^{\circ}C`, Soil skin temperature, Tskin
   Report\_Total\_ET  , :math:`m s^{-1}`, Total evapotranspiration, Evap
   Report\_Transpiration\_sum , :math:`m s^{-1}`, Transpiration integrated over the grid cell using vegetation fractions, EvapT 
   Report\_Einterception\_sum , :math:`m s^{-1}`, Evaporation of intercepted water, integrated over the grid cell using vegetation fractions, EvapI
   Report\_Esoil\_sum , :math:`m s^{-1}`, Soil evaporation integrated over the grid cell using vegetation (here corresponding to sub-canopy) fractions, EvapS	  
   Report\_Net\_Rad\_sum  , :math:`Wm^{-2}`, Top-of-canopy net radiation integrated over the grid cell, NRtot
   Report\_Veget\_frac , :math:`m^{2} m^{-2}`, Fraction of cell covered by canopy of vegetation type *n*, p\_*n* 
   Report\_Stem\_Density  , :math:`stems m^{-2}`, Density of individuals of vegetation type *n*, ntr\_*n* 
   Report\_Leaf\_Area\_Index   , :math:`m^{2} m^{-2}`, Leaf area index of vegetation type *n*, lai\_*n* 
   Report\_Stand\_Age   , :math:`years`, Age of stand of vegetation type *n*, age\_*n* 
   Report\_Canopy\_Conductance  , :math:`m s^{-1}`, Canopy conductance for vegetation type *n*, gc\_*n* 
   Report\_GPP  , :math:`gC m^{-2}`, Gross primary production for vegetation type *n* during the time step. gpp\_*n* 
   Report\_NPP  , :math:`gC^{-1} m^{-2}`, Net primary production for vegetation type *n* during the time step. npp\_*n* 
   Report\_Basal\_Area  , :math:`m^{2}`, Total basal area of vegetation type *n*, bas\_*n* 
   Report\_Tree\_Height  , :math:`m`, Height of stand of vegetation type *n*, hgt\_*n* 
   Report\_Root\_Mass  , :math:`g m^{-3}`, Root mass per volume of soil vegetation type *n*, root\_*n* 
   Report\_Canopy\_Temp , :math:`^{\circ}C`, Canopy temperature of vegetation type *n*, Tc\_*n* 
   Report\_Canopy\_NetR , :math:`W m^{-2}`, Net radiation above the vegetation type *n*, NRc\_*n* 
   Report\_Canopy\_LE\_E  , :math:`W m^{-2}`, Latent heat for evaporation of canopy interception for vegetation type *n*, LEEi\_*n*
   Report\_Canopy\_LE\_T  , :math:`W m^{-2}`, Latent heat for transpiration for vegetation type *n*, LETr\_*n* 
   Report\_Canopy\_Sens\_Heat  , :math:`W m^{-2}`, Sensible heat for canopy layer of vegetation type *n*, Hc\_*n* 
   Report\_Canopy\_Water\_Stor  , :math:`m`, Water storage in canopy layer of vegetation type *n*, Cs\_*n* 
   Report\_species\_ET , :math:`ms^{-1}`, Evapotranspiration within the vegetation type *n*, ETc\_*n*
   Report\_Transpiration , :math:`ms^{-1}`, Transpiration from vegetation type *n*, Trp\_*n*
   Report\_Einterception , :math:`ms^{-1}`, Evaporation of intercepted water for the vegetation type *n*, Ei\_*n*
   Report\_Esoil , :math:`ms^{-1}`, Soil evaporation under the vegetation type *n*, Es\_*n*
   Report\_GW\_to\_Channnel  , :math:`m`,  Quantity of groundwater seeping in stream water, GWChn
   Report\_Surface\_to\_Channel  , :math:`m`, Quantity of surface runoff contributing to stream water, SrfChn
   Report\_Infiltration  , :math:`m`, Meters of water (re)infiltrated water in the first hydrological layer, Inf
   Report\_Return\_Flow\_Surface , :math:`m`, Meters of water exfiltrated from the first hydrological layer, RSrf
   Report\_Overland\_Inflow  , :math:`m`,  Surface run-on (excluding channel inflow), LSrfi
   Report\_Stream\_Inflow  , :math:`m`, Incoming stream water, LChni
   Report\_Groundwater\_Inflow  , :math:`m`, Lateral groundwater inflow, LGWi
   Report\_Overland\_Outflow  , :math:`m`, Surface run-off (excluding channel outflow), LSrfo
   Report\_Groundwater\_Outflow  , :math:`m`, Lateral groundwater outflow, LGWo
   Report\_GW\_to\_Channnel\_acc , :math:`m`, Cumulated quantity of groundwater seeping in stream water, GWChnA
   Report\_Surface\_to\_Channel\_acc  , :math:`m`, Cumulated quantity of surface runoff contributing to stream water, SrfChnA
   Report\_Infiltration\_acc  , :math:`m`, Cumulated meters of water (re)infiltrated water in the first hydrological layer, InfA
   Report\_Return\_Flow\_Surface\_acc, :math:`m`, Cumulated meters of water exfiltrated from the first hydrological layer, RSrfA
   Report\_Overland\_Inflow\_acc  , :math:`m`, Cumulated surface run-on (excluding channel inflow), LSrfiA
   Report\_Stream\_Inflow\_acc  , :math:`m`, Cumulated lncoming stream water, LChniA
   Report\_Groundwater\_Inflow\_acc  , :math:`m`, Cumulated lateral groundwater inflow, LGWiA
   Report\_Overland\_Outflow\_acc  , :math:`m`, Cumulated surface run-off (excluding channel outflow), LSrfoA
   Report\_Groundwater\_Outflow\_acc  , :math:`m`, Cumulated lateral groundwater outflow, LGWo

**Map mask for time series locations**

.. csv-table::
   :header: "Keyword", "Type", "Description"
   :widths: "auto"
  *TS\_mask* , Map file name , Map identifying cells for which state variables will be reported. Map should be zero every=where expect for target cells. which are identified with integer IDs (`\geq 1`). A maximum of 32 cells can be reported.    
   
**Time series report switches**

Written outputs file are time series tables, at cells identified in *TS\_mask.

.. csv-table:: 
   :header: "Keyword", "Units", "Description", "File name"
   :widths: "auto
   
   Ts\_OutletDischarge , :math:`m^{3} s^{-1}`, Time series discharge at cells with *ldd* value = 5 (outlets and sinks), OutletDisch.tab 
   Ts\_Long\_Rad\_Down ,  :math:`W m^{-2}`, Time series of incoming long wave radiation to the surface layer, Ldown.tab 
   Ts\_Short\_Rad\_Down,  :math:`W m^{-2}`, Time series of incoming short wave radiation to the surface layer, Sdown.tab 
   Ts\_Precip,  :math:`ms^{-1}`, Time series of atmospheric long wave radiation, Precip.tab 
   Ts\_Rel\_Humidity ,  :math:`Pa Pa^{-1}`, Time series of relative humidity at the reference height, RelHumid.tab 
   Ts\_Wind\_Speed ,  :math:`m s^{-1}`, Time series of wind speed at reference height, WindSpeed.tab 
   Ts\_AvgAir\_Temperature ,  :math:`^{\circ}C`, Time series of average temperature at reference height, AvgTemp.tab 
   Ts\_MinAir\_Temperature ,  :math:`^{\circ}C`, Time series of minimum temperature at reference height, MinTemp.tab 
   Ts\_MaxAir\_Temperature  ,  :math:`^{\circ}C`, Time series of maximum temperature at reference height, MaxTemp.tab 
   Ts\_SWE,  :math:`m`, Time series of soil water equivalent, SWE.tab 
   Ts\_Infilt\_Cap ,  :math:`m s^{-1}`, Time series of infiltration capacity, InfiltCap.tab 
   Ts\_Streamflow ,  :math:`m^{3} s^{-1}`,  Time series of streamflow, Streamflow.tab  
   Ts\_Ponding ,  :math:`m`, Times series of surface water height, Ponding.tab  
   Ts\_Soil\_Water\_Content\_Average ,  :math:`m^{3}m^{-3}`, Times series of average volumetric water content for entire soil profile, SoilMoistureAv.tab  
   Ts\_Soil\_Water\_Content\_Up ,  :math:`m^{3} m^{-3}`, Times series of average volumetric water content over the two upper soil layers, SoilMoistureUp.tab  
   Ts\_Soil\_Water\_Content\_L1 ,  :math:`m^{3} m^{-3}`,Times series of volumetric water content for topsoil, SoilMoistureL1.tab  
   Ts\_Soil\_Water\_Content\_L2 ,  :math:`m^{3} m^{-3}`,Times series of volumetric water content for second soil layer, SoilMoistureL2.tab  
   Ts\_Soil\_Water\_Content\_L3 ,  :math:`m^{3} m^{-3}`,Times series of volumetric water content for bottommost soil layer, SoilMoistureL3.tab  
   Ts\_WaterTableDepth  , :math:`m` Depth the equivalent water table using the average soil moisture, WaterTableDepth.tab
   Ts\_Soil\_Sat\_Deficit,  :math:`m`, Time series of soil water deficit defined as the water depth needed to saturate the cells identified in *TS\_mask*, SoilSatDef.tab 
   Ts\_Ground\_Water  , :math:`m`, Meters of water above field capacity in the third hydrologic layer, GroundWater.tab
   Ts\_Soil\_Net\_Rad,  :math:`W m^{-2}`, Time series of net radiation for surface layer, NetRadS.tab 
   Ts\_Soil\_LE,  :math:`W m^{-2}`, Time series of latent heat for surface layer, LatHeat.tab 
   Ts\_Sens\_Heat,  :math:`W m^{-2}`, Time series of sensible heat for surface layer, SensHeat.tab 
   Ts\_Grnd\_Heat,  :math:`W m^{-2}`, Time series of ground heat, GrndHeat.tab 
   Ts\_Snow\_Heat,  :math:`W m^{-2}`, Time series of heat exchanges with snowpack, SnowHeat.tab 
   Ts\_Soil\_Temperature,  :math:`^{\circ}C`, Time series of soil temperature, SoilTemp.tab 
   Ts\_Skin\_Temperature,  :math:`^{\circ}C`, Time series of soil skin temperature, SkinTemp.tab 
   Ts\_Total\_ET  , :math:`m s^{-1}`, Total evapotranspiration, Evap.tab
   Ts\_Transpiration\_sum , :math:`m s^{-1}`, Transpiration integrated over the grid cell using vegetation fractions, EvapT.tab 
   Ts\_Einterception\_sum , :math:`m s^{-1}`, Evaporation of intercepted water, integrated over the grid cell using vegetation fractions, EvapI.tab
   Ts\_Esoil\_sum , :math:`m s^{-1}`, Soil evaporation integrated over the grid cell using vegetation (here corresponding to sub-canopy) fractions, EvapS.tab
   Ts\_Net\_Rad\_sum  , :math:`Wm^{-2}`, Top-of-canopy net radiation integrated over the grid cell, NetRadtot.tab
   Ts\_Veget\_frac,  :math:`m^{2} m^{-2}`, Time series of fractions occupied by vegetation type *n*, p\_*n*.tab 
   Ts\_Stem\_Density ,  :math:`stems m^{-2}`, Time series of stem density of vegetation type *n*, num\_of\_trees\_*n*.tab 
   Ts\_Leaf\_Area\_Index,  :math:`m^{2} m^{-2}`, Time series of leaf area index of vegetation type *n*, lai\_*n*.tab 
   Ts\_Canopy\_Conductance,  :math:`m s^{-1}`, Time series of canopy conductance of vegetation type *n*, CanopyConduct\_*n*.tab 
   Ts\_GPP ,  :math:`gC m^{-2}`, Time series of gross primary production of vegetation type *n* during the current time step, GPP\_*n*.tab
   Ts\_NPP ,  :math:`gC m^{-2}`, Time series of net primary production of vegetation type *n* during the current time step, NPP\_*n*.tab
   Ts\_Basal\_Area ,  :math:`m^{-2}`, Time series of total basal area of vegetation type *n*, BasalArea\_*n*.tab
   Ts\_Tree\_Height ,  :math:`m`, Time series of effective tree height of vegetation type *n*, TreeHeight\_*n*.tab
   Ts\_Root\_Mass,  :math:`g m^{-3}`, Time series of root density (mass per volume of soil) of vegetation type *n*, RootMass\_*n*.tab
   Ts\_Canopy\_Temp,  :math:`^{\circ}C`, Time series of canopy temperature of vegetation type *n*, CanopyTemp\_*n*.tab
   Ts\_Canopy\_NetR,  :math:`W m^{-2}`, Time series of net radiation at canopy layer of vegetation type *n*, NetRadC\_*n*.tab
   Ts\_Canopy\_LE\_E,  :math:`W m^{-2}`, Time series of latent heat for evaporation of canopy interception for vegetation type *n*, CanopyLatHeatEi\_*n*.tab
   Ts\_Canopy\_LE\_T,  :math:`W m^{-2}`, Time series of latent heat for transpiration for vegetation type *n*, CanopyLatHeatTr\_*n*.tab
   Ts\_Canopy\_Sens\_Heat ,  :math:`W m^{-2}`, Time series of sensible heat at canopy layer of vegetation type *n*, CanopySensHeat\_*n*.tab
   Ts\_Canopy\_Water\_Stor ,  :math:`m`, Time series of water storage at canopy layer of vegetation type *n*, CanopyWaterStor\_*n*.tab
   Ts\_species\_ET , :math:`m s^{-1}`, Evapotranspiration within the vegetation type *n*, ETc\_*n*
   Ts\_Transpiration ,  :math:`m s^{-1}`, Time series of transpiration for canopy layer of vegetation type *n*, EvapT\_*n*.tab
   Ts\_Einterception , :math:`m s^{-1}`, Evaporation of intercepted water for the vegetation type *n*, EvapI\_*n*
   Ts\_Esoil , :math:`m s^{-1}`, Soil evaporation under the vegetation type *n*, EvapS\_*n*
   Ts\_GW\_to\_Channnel  , :math:`m`,  Quantity of groundwater seeping in stream water, GWtoChn.tab
   Ts\_Surface\_to\_Channel  , :math:`m`, Quantity of surface runoff contributing to stream water, SrftoChn.tab
   Ts\_Infiltration  , :math:`m`, Meters of water (re)infiltrated water in the first hydrological layer, Infilt.tab
   Ts\_Return\_Flow\_Surface , :math:`m`, Meters of water exfiltrated from the first hydrological layer, ReturnSrf.tab
   Ts\_Overland\_Inflow  , :math:`m`,  Surface run-on (excluding channel inflow), SrfLatI.tab
   Ts\_Stream\_Inflow  , :math:`m`, Incoming stream water, ChnLatI.tab
   Ts\_Groundwater\_Inflow  , :math:`m`, Lateral groundwater inflow, GWLatI.tab
   Ts\_Overland\_Outflow  , :math:`m`, Surface run-off (excluding channel outflow), SrfLatO.tab
   Ts\_Groundwater\_Outflow  , :math:`m`, Lateral groundwater outflow, LGWo
   Ts\_GW\_to\_Channnel\_acc , :math:`m`, Cumulated quantity of groundwater seeping in stream water, GWtoChnAcc.tab
   Ts\_Surface\_to\_Channel\_acc  , :math:`m`, Cumulated quantity of surface runoff contributing to stream water, SrftoChnAcc.tab
   Ts\_Infiltration\_acc, :math:`m`, Cumulated meters of water (re)infiltrated water in the first hydrological layer, InfiltAcc.tab
   Ts\_Return\_Flow\_Surface\_acc, :math:`m`, Cumulated meters of water exfiltrated from the first hydrological layer, ReturnSrfAcc.tab
   Ts\_Overland\_Inflow\_acc  , :math:`m`, Cumulated surface run-on (excluding channel inflow), SrfLatIAcc.tab
   Ts\_Stream\_Inflow\_acc  , :math:`m`, Cumulated incoming stream water, ChnLatIAcc.tab
   Ts\_Groundwater\_Inflow\_acc  , :math:`m`, Cumulated lateral groundwater inflow, GWLatIAcc.tab
   Ts\_Overland\_Outflow\_acc  , :math:`m`, Cumulated surface run-off (excluding channel outflow), SrfLatOAcc.tab
   Ts\_Groundwater\_Outflow\_acc  , :math:`m`, Cumulated lateral groundwater outflow, GWLatOAcc.tab
