Configuration file keywords
===========================

| \|p4cm l l p5.5cm\| **Keyword** & **Type** & **Units** &
  **Description**
| Maps\_Folder & System Path & N/A & Path to folder with land surface
  information
| Clim\_Maps\_Folder & System Path & N/A & Path to folder with Climate
  information
| Output\_Folder & System Path & N/A & Path to folder where outputs will
  be written
| MapTypes & option & N/A & Format of maps. In this version the format
  is *csf* (PCRaster).
| Species\_State \_Variable\_Input\_Method & option & N/A & Specifies
  the input format of the vegetation state variables. Options are
  *table* or *maps*
| Reinfiltration & option & N/A & Switch 1/0 to turn reinfiltration on
  (1) or off (0)
| Aerodyn\_resist\_opt & option & N/A & Switches between different
  aerodynamic resistance formulations. 0: Penman; 1: Thom and Oliver
  (1977)
| Soil\_resistance\_opt & option & N/A & Switches between different soil
  resistance formulations. 0: Passerat de Silans et al 1989; 1: Ivanov
  et al (2008)
| Simul\_start & Integer & Seconds & Time of simulation start. In the
  current version this value must be 0
| Simul\_end & Integer & Seconds & Time when simulation ends in seconds.
  Since the start time is always 0, this value indicates the total
  simulated time
| Simul\_tstep & Integer & Seconds & Size of the integration time step
| Clim\_input\_tstep & Integer & Seconds & Time step of climate forcing.
  Typically it is the same as *Simul\_tstep* but can be larger (i.e.
  climate inputs are daily but we are using an hourly integration time
  step). *Clim\_input\_tstep* cannot be smaller than *Simul\_tstep*
| Report\_interval & Integer & Seconds & Intervals between outputs.
  *Report\_interval* cannot be smaller than *Simul\_tstep* and typically
  it is equal to *Simul\_tstep*
| Snow\_rain\_temp\_threshold & scalar & :math:`^{\circ}C` & Air
  temperature threshold for snow/rain transition
| ClimateZones & Map file name & integers & Map identifying the climate
  zones
| Isohyet\_map & Map file name & - & This map allows to redistribute
  rainfall within a climate zone. It is a map with multiplication
  factors for rain in a given pixel. A map containing 1 over the domain
  has the effect of overriding this input (does not modify the
  precipitation input)
| Precipitation & Binary climate file & :math:`ms^{-1}` & Precipitation
  input
| AirTemperature & Binary climate file & :math:`^{\circ}C` & Average air
  temperature
| MaxAirTemp & Binary climate file & :math:`^{\circ}C` & Maximum air
  temperature
| MinAirTemp& Binary climate file & :math:`^{\circ}C` & Maximum air
  temperature
| RelativeHumidity& Binary climate file & :math:`kPakPa^{-1}` & Average
  air temperature
| WindSpeed& Binary climate file & :math:`ms^{-1}` & Wind speed
| IncomingLongWave& Binary climate file & :math:`Wm^{-2}` & Incoming
  long wave radiation
| IncomingShortWave& Binary climate file & :math:`Wm^{-2}` & Incoming
  solar radiation
| local\_drain\_direc & Map file name & - & D8 steepest descent ldd
| channel\_width & Map file name & :math:`m` & mask with width of
  channel network. Pixels with no channel must be 0 or nodata. Positive
  numbers indicate the width of the channel in the pixel
| channel\_gw\_transfer\_param & Map file name & :math:` m^{-1} ` &
  Coefficient controlling transfers of water from the subsurface system
  to the channel
| mannings\_n & Map file name & :math:` sm^{-1/3} ` & Manning’s n
  roughness coefficient for channel

| 
| Streamflow & Map file name & :math:` m^3s^{-1} `\ & Streamflow
| snow\_water\_equivalent & Map file name & :math:` m `\ & Snow water
  equivalent
| Soil\_moisture\_1 & Map file name & :math:` m^3m^{-3} `\ & Volumetric
  soil water content for topmost soil layer
| Soil\_moisture\_2 & Map file name & :math:` m^3m^{-3} `\ & Volumetric
  soil water content for layer 3
| Soil\_moisture\_3 & Map file name & :math:` m^3m^{-3} `\ & Volumetric
  soil water content of bottommost layer
| Soil\_temperature & Map file name & :math:` ^{\circ}C `\ & Soil
  temperature at boundary of thermal layer
| DEM & Map file name & :math:`m` & Digital elevation model
| Slope& Map file name & :math:`mm^{-1}` & Local terrain slope. Rise
  over run
| Horiz\_Hydraulic\_Conductivity & Map file name & :math:`ms^{-1}` &
  Effective soil hydraulic conductivity
| Vert\_Horz\_Anis\_ratio & Map file name & :math:`[-]` & Ratio of
  vertical to horizontal hydraulic conductivity
| Terrain\_Random\_Roughness & Map file name & :math:`m` & Local surface
  roughness
| Porosity & Map file name & - & Soil porosity
| Air\_entry\_pressure & Map file name & :math:`m` & Soil air entry
  pressure
| Brooks\_Corey\_lambda & Map file name & - & Pore size distribution
| Residual\_soil\_moisture & Map file name & :math:`m^{3}m^{-3}` &
  Minimum allowed volumetric soil water content
| Soil\_depth & Map file name & :math:`m` & Soil depth
| Depth\_soil\_layer\_1 & Map file name & :math:`m` & Depth of topmost
  soil layer
| Depth\_soil\_layer\_2 & Map file name & :math:`m` & Depth of second
  soil layer
| Veget\_water\_use\_param1 & Map file name & :math:`m` & Vegetation
  water use parameter as per Landsberg and Waring (1997)
| Veget\_water\_use\_param2 & Map file name & :math:`m` & Vegetation
  water use parameter as per Landsberg and Waring (1997)
| Fraction\_roots\_soil\_layer\_1 & Map file name & - & Fraction of
  roots in topmost soil layer. Sum of fraction of roots in soil layer 1
  and 2 must be less than 1
| Fraction\_roots\_soil\_layer\_2 & Map file name & - & Fraction of
  roots in second soil layer. Sum of fraction of roots in soil layer 1
  and 2 must be less than 1
| Albedo & Map file name & - & Surface albedo
| Surface\_emissivity & Map file name & - & Surface
  emissivity/absorptivity
| Dry\_Soil\_Heat\_Capacity & Map file name & :math:` Jm^{-3}K^{-1} ` &
  Heat capacity of soil solid particles
| Dry\_Soil\_Therm\_Cond & Map file name & :math:` Wm^{-1}K^{-1} ` &
  Thermal conductivity of soil solid particles
| Damping\_depth & Map file name & :math:` m ` & Depth of bottom of
  second soil thermal layer
| Temp\_at\_damp\_depth & Map file name & :math:` ^{\circ}C ` & Soil
  temperature at damping depth
| Snow\_Melt\_Coeff & Map file name & :math:` m^{\circ}C^{-1} ` &
  Snowmelt coefficient factor

| 
| ForestPatches & Map file name & integers & Map identifying forest
  categories (patches)
| Number\_of\_Species & Integer & - & Number of vegetation types
  included in the simulation
| Species\_Parameters & Parameter table & - & Table containing parameter
  information for each simulated vegetation type
| Species\_Proportion\_Table & Variable table & :math:` m^{2}m^{-2}  ` &
  Table with initial proportion of covered area (canopy cover) for each
  vegetation type with respect to cell area
| Species\_StemDensity\_Table & Variable table & :math:` trees m^{-2}  `
  & Table with initial tree density per cell for each vegetation type
| Species\_LAI\_Table & Variable table & :math:` m^{2}m^{-2}  ` & Table
  with initial leaf area index for each vegetation type
| Species\_AGE\_Table & Variable table & :math:` years  ` & Table with
  initial average age each vegetation type
| Species\_BasalArea\_Table & Variable table & :math:` m^{2}  ` & Table
  with initial total basal area per vegetation type
| Species\_Height\_table & Variable table & :math:` m  ` & Table with
  initial effective height per vegetation type
| Species\_RootMass\_table & Variable table & :math:` gm^{-3}  ` & Table
  with initial root mass per volume of soil for each vegetation type
| Report\_Long\_Rad\_Down & switch & :math:`Wm^{-2}` & 1: Report map for
  this variable - 0: Switch off reporting for this variable. Root name
| Report\_Short\_Rad\_Down & switch & :math:`Wm^{-2}` & 1: Report map
  for this variable - 0: Switch off reporting for this variable. Root
  name
| Report\_Precip& switch & :math:`ms^{-1}` & 1: Report map for this
  variable - 0: Switch off reporting for this variable. Root name
| Report\_Rel\_Humidity& switch & :math:` Pa^{1}Pa^{-1} ` & 1: Report
  map for this variable - 0: Switch off reporting for this variable.
  Root name
| Report\_Wind\_Speed& switch & :math:` ms^{-1} ` & 1: Report map for
  this variable - 0: Switch off reporting for this variable. Root name
| Report\_AvgAir\_Temperature & switch & :math:` ^{\circ}C ` & 1: Report
  map for this variable - 0: Switch off reporting for this variable.
  Root name
| Report\_MinAir\_Temperature& switch & :math:` ^{\circ}C ` & 1: Report
  map for this variable - 0: Switch off reporting for this variable.
  Root name
| Report\_MaxAir\_Temperature& switch & :math:` ^{\circ}C ` & 1: Report
  map for this variable - 0: Switch off reporting for this variable.
  Root name
| Report\_SWE& switch & :math:` m ` & 1: Report map for this variable -
  0: Switch off reporting for this variable. Root name
| Report\_Infilt\_Cap & switch & :math:` ms^{-1} ` & 1: Report map for
  this variable - 0: Switch off reporting for this variable. Root name
| Report\_Infilt\_Cap & switch & :math:` ms^{-1} ` & 1: Report map for
  this variable - 0: Switch off reporting for this variable. Root name
| Report\_Streamflow & switch & :math:` m^{3}s^{-1} ` & 1: Report map
  for this variable - 0: Switch off reporting for this variable. Root
  name
| Report\_Soil\_Water\_Content\_Average & switch & :math:` m^{3}m^{-3} `
  & 1: Average volumetric water content for entire soil profile. Report
  map for this variable - 0: Switch off reporting for this variable.
  Root name
| Report\_Soil\_Water\_Content\_L1 & switch & :math:` m^{3}m^{-3} ` & 1:
  Volumetric water content for topmost soil layer. Report map for this
  variable - 0: Switch off reporting for this variable. Root name
| Report\_Soil\_Water\_Content\_L2 & switch & :math:` m^{3}m^{-3} ` & 1:
  Volumetric water content for second soil layer. Report map for this
  variable - 0: Switch off reporting for this variable. Root name
| Report\_Soil\_Water\_Content\_L3 & switch & :math:` m^{3}m^{-3} ` & 1:
  Volumetric water content for bottommost soil layer. Report map for
  this variable - 0: Switch off reporting for this variable. Root name
| Report\_Soil\_Sat\_Deficit & switch & :math:` m ` & Meters of water
  needed to saturate soil. 1: Report map for this variable - 0: Switch
  off reporting for this variable. Root name
| Report\_Soil\_ETP & switch & :math:` ms^{-1} ` & Soil evaporation. 1:
  Report map for this variable - 0: Switch off reporting for this
  variable. Root name
| Report\_Soil\_Net\_RadReport & switch & :math:` Wm^{-2} ` & Soil net
  radiation. 1: Report map for this variable - 0: Switch off reporting
  for this variable. Root name
| Report\_Soil\_LESoil & switch & :math:` Wm^{-2} ` & Latent heat for
  surface layer. 1: Report map for this variable - 0: Switch off
  reporting for this variable. Root name
| Report\_Sens\_Heat & switch & :math:` Wm^{-2} ` & Sensible heat for
  surface layer. 1: Report map for this variable - 0: Switch off
  reporting for this variable. Root name
| Report\_Grnd\_Heat & switch & :math:` Wm^{-2} ` & Ground heat. 1:
  Report map for this variable - 0: Switch off reporting for this
  variable. Root name
| Report\_Snow\_Heat& switch & :math:` Wm^{-2} ` & Turbulent heat
  exchange with snowpack. 1: Report map for this variable - 0: Switch
  off reporting for this variable. Root name
| Report\_Soil\_Temperature & switch & :math:` ^{\circ}C ` & Soil
  temperature at the bottom of first thermal layer. 1: Report map for
  this variable - 0: Switch off reporting for this variable. Root name
| Report\_Skin\_Temperature & switch & :math:` ^{\circ}C ` & Soil skin
  temperature. 1: Report map for this variable - 0: Switch off reporting
  for this variable. Root name
| Report\_Veget\_frac& switch & :math:` m^{2}m^{-2} ` & Fraction of cell
  covered by canopy of vegetation type *n*. 1: Report map for this
  variable - 0: Switch off reporting for this variable. Root name
| Report\_Stem\_Density & switch & :math:` stems m^{-2} ` & Density of
  individuals of vegetation type *n*. 1: Report map for this variable -
  0: Switch off reporting for this variable. Root name
| Report\_Leaf\_Area\_Index & switch & :math:`  m^{2}m^{-2} ` & Leaf
  area index of vegetation type *n*. 1: Report map for this variable -
  0: Switch off reporting for this variable. Root name
| Report\_Stand\_Age & switch & :math:` years ` & Age of stand of
  vegetation type *n*. 1: Report map for this variable - 0: Switch off
  reporting for this variable. Root name
| Report\_Canopy\_Conductance & switch & :math:` ms^{-1} ` & Canopy
  conductance for vegetation type *n*. 1: Report map for this variable -
  0: Switch off reporting for this variable. Root name
| Report\_GPP & switch & :math:` gCm^{-2} ` & Gross primary production
  for vegetation type *n* during the time step. 1: Report map for this
  variable - 0: Switch off reporting for this variable. Root name
| Report\_NPP & switch & :math:` gC^{-1}m^{-2} ` & Net primary
  production for vegetation type *n* during the time step. 1: Report map
  for this variable - 0: Switch off reporting for this variable. Root
  name
| Report\_Basal\_Area & switch & :math:` m^{2} ` & Total basal area of
  vegetation type *n*. 1: Report map for this variable - 0: Switch off
  reporting for this variable. Root name
| Report\_Tree\_Height & switch & :math:` m ` & Height of stand of
  vegetation type *n*. 1: Report map for this variable - 0: Switch off
  reporting for this variable. Root name
| Report\_Root\_Mass & switch & :math:` gm^{-3} ` & Root mass per volume
  of soil vegetation type *n*. 1: Report map for this variable - 0:
  Switch off reporting for this variable. Root name
| Report\_Canopy\_Temp& switch & :math:` ^{\circ}C ` & Canopy
  temperature of vegetation type *n*. 1: Report map for this variable -
  0: Switch off reporting for this variable. Root name
| Report\_Canopy\_NetR& switch & :math:` Wm^{-2} ` & Canopy temperature
  of vegetation type *n*. 1: Report map for this variable - 0: Switch
  off reporting for this variable. Root name
| Report\_Canopy\_LE & switch & :math:` Wm^{-2} ` & Latent heat for
  canopy layer of vegetation type *n*. 1: Report map for this variable -
  0: Switch off reporting for this variable. Root name
| Report\_Canopy\_Sens\_Heat & switch & :math:` Wm^{-2} ` & Sensible
  heat for canopy layer of vegetation type *n*. 1: Report map for this
  variable - 0: Switch off reporting for this variable. Root name
| Report\_Canopy\_Water\_Stor & switch & :math:` m ` & Water storage in
  canopy layer of vegetation type *n*. 1: Report map for this variable -
  0: Switch off reporting for this variable. Root name
| Report\_Transpiration& switch & :math:` ms^{-1} ` & Transpiration from
  vegetation type *n*. 1: Report map for this variable - 0: Switch off
  reporting for this variable. Root name
| Ts\_OutletDischarge& switch & :math:` m^{3}s^{-1} ` & 1: Turns on
  reporting of discharge at cells with *ldd* value = 5 (outlets and
  sinks) - 0: Turns off report. File name
| TS\_mask & Map file name & nominal & Map identifying cells for which
  state variables will be reported. Map should be zero every=where
  expect for target cells. which are identified with integer IDs
  (:math:`\geq 1`). A maximum of 32 cells can be reported.
| Ts\_Long\_Rad\_Down & Time series table & :math:` Wm^{-2} ` & Time
  series of incoming long wave radiation to the surface layer for cells
  identified in . File name
| Ts\_Short\_Rad\_Down& Time series table & :math:` Wm^{-2} ` & Time
  series of incoming short wave radiation to the surface layer for cells
  identified in . File name
| Ts\_Precip& Time series table & :math:` ms^{-1} ` & Time series of
  atmospheric long wave radiation for cells identified in . File name
| Ts\_Rel\_Humidity & Time series table & :math:` PaPa^{-1} ` & Time
  series of relative humidity at the reference height for cells
  identified in . File name
| Ts\_Wind\_Speed & Time series table & :math:` ms^{-1} ` & Time series
  of wind speed at reference height for cells identified in . File name
| Ts\_AvgAir\_Temperature & Time series table & :math:` ^{\circ}C ` &
  Time series of average temperature at reference height for cells
  identified in . File name
| Ts\_MinAir\_Temperature & Time series table & :math:` ^{\circ}C ` &
  Time series of minimum temperature at reference height for cells
  identified in . File name
| Ts\_MaxAir\_Temperature & Time series table & :math:` ^{\circ}C ` &
  Time series of maximum temperature at reference height for cells
  identified in . File name
| Ts\_SWE& Time series table & :math:` m ` & Time series of soil water
  equivalent at cells identified in . File name
| Ts\_Infilt\_Cap & Time series table & :math:` ms^{-1} ` & Time series
  of infiltration capacity at cells identified in . File name
| Ts\_Streamflow & Time series table & :math:` m^{3}s^{-1} ` & Time
  series of streamflow at cells identified in . File name
| Ts\_Soil\_Water\_Content\_Average & Time series table &
  :math:` m^{3}m^{-3} ` & Times series of Average volumetric water
  content for entire soil profile at cells identified in . File name
| Ts\_Soil\_Water\_Content\_L1 & Time series table &
  :math:` m^{3}m^{-3} ` &Times series of Average volumetric water
  content for topsoil at cells identified in . File name
| Ts\_Soil\_Water\_Content\_L2 & Time series table &
  :math:` m^{3}m^{-3} ` &Times series of Average volumetric water
  content for second soil layer at cells identified in . File name
| Ts\_Soil\_Water\_Content\_L3 & Time series table &
  :math:` m^{3}m^{-3} ` &Times series of Average volumetric water
  content for bottommost soil layer at cells identified in . File name
| Ts\_Soil\_Sat\_Deficit& Time series table & :math:` m ` & Time series
  of soil water deficit defined as the water depth needed to saturate
  cells identified in . File name
| Ts\_Soil\_ETP& Time series table & :math:` ms^{-1} ` & Time series of
  soil evaporation at cells identified in . File name
| Ts\_Soil\_Net\_Rad& Time series table & :math:` Wm^{-2} ` & Time
  series of net radiation for surface layer at cells identified in .
  File name
| Ts\_Soil\_LE& Time series table & :math:` Wm^{-2} ` & Time series of
  latent heat for surface layer at cells identified in . File name
| Ts\_Sens\_Heat& Time series table & :math:` Wm^{-2} ` & Time series of
  sensible heat for surface layer at cells identified in . File name
| Ts\_Grnd\_Heat& Time series table & :math:` Wm^{-2} ` & Time series of
  ground heat at cells identified in . File name
| Ts\_Snow\_Heat& Time series table & :math:` Wm^{-2} ` & Time series of
  heat exchanges with snowpack at cells identified in . File name
| Ts\_Soil\_Temperature& Time series table & :math:` ^{\circ}C ` & Time
  series of soil temperature at cells identified in . File name
| Ts\_Skin\_Temperature& Time series table & :math:` ^{\circ}C ` & Time
  series of soil skin temperature at cells identified in . File name
| Ts\_Veget\_frac& Time series table & :math:` m^{2}m^{-2} ` & Time
  series of fractions occupied by vegetation type *n* at cells
  identified in . File name
| Ts\_Stem\_Density & Time series table & :math:` stems m^{-2} ` & Time
  series of stem density of vegetation type *n* at cells identified in .
  File name
| Ts\_Leaf\_Area\_Index& Time series table & :math:` m^{2}m^{-2} ` &
  Time series of leaf area index of vegetation type *n* at cells
  identified in . File name
| Ts\_Canopy\_Conductance& Time series table & :math:` ms^{-1} ` & Time
  series of canopy conductance of vegetation type *n* at cells
  identified in . File name
| Ts\_GPP & Time series table & :math:` gCm^{-2} ` & Time series of
  gross primary production of vegetation type *n* during the current
  time step at cells identified in . File name
| Ts\_NPP & Time series table & :math:` gCm^{-2} ` & Time series of net
  primary production of vegetation type *n* during the current time step
  at cells identified in . File name
| Ts\_Basal\_Area & Time series table & :math:` m^{-2} ` & Time series
  of total basal area of vegetation type *n* at cells identified in .
  File name
| Ts\_Tree\_Height & Time series table & :math:` m ` & Time series of
  effective tree height of vegetation type *n* at cells identified in .
  File name
| Ts\_Root\_Mass& Time series table & :math:` gm^{-3} ` & Time series of
  root density (mass per volume of soil) of vegetation type *n* at cells
  identified in . File name
| Ts\_Canopy\_Temp& Time series table & :math:` ^{\circ}C ` & Time
  series of canopy temperature of vegetation type *n* at cells
  identified in . File name
| Ts\_Canopy\_NetR& Time series table & :math:` Wm^{-2} ` & Time series
  of net radiation at canopy layer of vegetation type *n* at cells
  identified in . File name
| Ts\_Canopy\_LE& Time series table & :math:` Wm^{-2} ` & Time series of
  latent heat at canopy layer of vegetation type *n* at cells identified
  in . File name
| Ts\_Canopy\_Sens\_Heat & Time series table & :math:` Wm^{-2} ` & Time
  series of sensible heat at canopy layer of vegetation type *n* at
  cells identified in . File name
| Ts\_Canopy\_Water\_Stor & Time series table & :math:` m ` & Time
  series of water storage at canopy layer of vegetation type *n* at
  cells identified in . File name
| Ts\_Transpiration & Time series table & :math:` ms^{-1} ` & Time
  series of transpiration for canopy layer of vegetation type *n* at
  cells identified in . File name
