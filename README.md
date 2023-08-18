# airfoil-Lift

This project estimates the lift force per unit wingspan acting on an airfoil (NACA 23012 12%)[^1] using the Bernoulli principle.
![NACA 23012 12%](naca23012%20(1).gif) 

## Model
For this project, the Bernoulli principle had been used to determine the lift force. The principle states that the difference in the velocity of fluid flowing over the upper and lower surfaces of the airfoil generates a pressure difference between the two surfaces. As a result, the airfoil experiences lift.  

The lift force per unit wingspan (span) of the airfoil can be estimated using the following equation:

```
Lift per unit span = 0.5  * Cl * rho_air * v^2 * c
```
 rho_air     : density of air at chosen elevation above sea level <br>
      v      : True air speed  <br>
      Cl     : Lift coefficient  <br>
      c      : Length of the chord for chosen airfoil  <br>


where dynamic pressure = 0.5 * air_density * velocity^2; It is a measure of the force exerted by a fluid due to its motion on a surface per unit area. 
Wingspan is the length of the lateral extent of the airfoil.

## Parameters
The estimation of lift per unit wingspan requires the direct/indirect consideration of several factors such as,
1. **Lift coefficient (Cl)**: This is a dimensionless quantity which is representative of the aerodynamical parameters of the airfoil. It is generally estimated experimentally for specific airfoils in wind tunnels. In this project, non-uniform empirical data has been obtained[^2]. The values for lift coefficient chosen are for the above mentioned airfoil, for a fixed angle of attack (zero degrees), fixed Mach number and varying values of the Reynolds Number(Re).
2. **Chord length (c)**: It represents the horizontal length of the cross section of the airfoil. For this particular airfoil, the value is taken to be 0.1m taking into account the parameters chosen while obtaining the empirical data for the lift coefficient.
3. **Air density (rho_air)**: The density of air decreases with increase in elevation from sea level (altitude). Here, the air density is being computed using the corresponding values of ambient temperature and pressure for the chosen altitude obtained from the International Standard Atmosphere (ISA) data.
4. **Liquid column height change (deltaColumnHeight)**: This is the change in the level of top of the liquid in the column in the Pitot tube. The level of the liquid changes with changing TAS.
5. **Velocity (v)**: It refers to the relative velocity of the airfoil with respect to the wind speed. It is also known as true airspeed (TAS). TAS is measured using an instrument called Pitot tube. The change in the liquid column height inside the Pitot tube is used to measure the TAS.
   
```
                  (  2 * g * (deltaColumnHeight) * rho_liquid  )
      TAS = sqrt  [ -------------------------------------------]
                  (                   rho_air                  )
```
7. **Dynamic viscosity**: It is a quantitity used to characterise the resistance to flow of a fluid under an applied force. It is mathematically expressed as,

   ```
                            Shear stress
   Dynamic viscosity (mu) = -------------
                             Shear rate
   ```
   
   where shear stress is the force applied on the fluid per unit area and shear rate is the velocity gradient of fluid          perpendicular to the fluid flow direction. For the sake of simplicity, this velocity gradient has been considered to be a    constant value. However, the dependence of dynamic viscosity on ambient temperature has been taken into account since the    former depends strongly on temperature. The Sutherland model has been used to calculate dynamic viscosity.

   ```
                               mu_ref * (T_ref + S)
   Dynamic viscosity (mu) = -------------------------
                             (T + S) * (T/T_ref)^-1.5
   ```
   
   mu_ref : dynamic viscosity at the reference temperature (T_ref) <br>
   T_ref  : reference temperature (273.15 K) <br>
   S      : Sutherland constant determined experimentally for various gases
   
6. **Reynolds Number**: It is used to characterise the type of flow of a fluid over a surface. The value of Reynolds number may indicate if a flow regime is laminar or turbulent or a transition between the two. This gives information about the behaviour of streamlines in the flow. The empirical data obtained[^2] points to the variation of the lift coefficient for various values of Reynolds number. It is calculated as follows:
   ```
                        rho_air * TAS * c
   Reynolds number =  ---------------------
                               mu

   ```

## Conditions

Elevation of airfoil above sea level = 10 m    

Ambient Temperature (ISA)            = 281.65 K   

Ambient Pressure (ISA)               = 88375.17 N/m^-2

Liquid density in Pitot tube column  = 1000 kg*m^-3

Angle of attack                      = 0 degrees

## Repository structure
```
|-------README.md
|-------src
         |--------v1
         |        |-------lift-per-span.c
         |        |-------README.md
         |
         |--------v2
                  |-------lift-per-span-with-distributions.c
                  |-------README.md

```

## Parameter values
The inputs and their ranges are:
-	`ambientTemperature`: 281.65 K
-	`ambientPressure`   : 88375.17 Pa
-	`chordLength`       : 0.095 to 0.15
-	`deltaColumnHeight` : 0.056 to 0.109

The empirical data[^2] represented in ```lookup-table.md``` is used to estimate the value of lift coefficient based on the value of Reynolds number. The estimation is done using a combination of linear and parabolic interpolation. The resultant interpolated values are used to inject a uniform distribution for lift coefficient.

## Parameter values

-	`ambientTemperature`: 281.65 K
-	`ambientPressure`   : 88375.17 Pa
-	`chordLength`       : 0.1
-	`deltaColumnHeight` : 0.1

The empirical data[^2] represented in ```lookup-table.md``` is used to estimate the value of lift coefficient based on the value of Reynolds number. The estimation is done using a combination of linear and parabolic interpolation. The mean of the resultant interpolated value is chosen to be the lift coefficient.

## Outputs



[^1]: https://m-selig.ae.illinois.edu/ads/afplots/naca23012.gif
[^2]: http://airfoiltools.com/airfoil/details?airfoil=naca23012-il
