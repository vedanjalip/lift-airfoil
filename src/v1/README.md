## Parameter values

-	`ambientTemperature`: 281.65 K
-	`ambientPressure`   : 88375.17 Pa
-	`chordLength`       : 0.1
-	`deltaColumnHeight` : 0.1

The empirical data[^1] represented in ```lookup-table.md``` is used to estimate the value of lift coefficient based on the value of Reynolds number. The estimation is done using a combination of linear and parabolic interpolation. The mean of the resultant interpolated value is chosen to be the lift coefficient.

[^1]: http://airfoiltools.com/airfoil/details?airfoil=naca23012-il
