#!/usr/bin/env gnuplot -persist

set term qt 0 position 200, 200

set multiplot layout 2, 2
set key autotitle columnhead
set xlabel "Temperature (K)"

DT = 273.15
TS = 1698.25
TA = 1714.23
TL = 1726.78
C = 0.03; Cr = 0.17; Mo = 2.5; Ni = 0.12

rhoF_(T, C, Cr, Mo, Ni) = 7875.96 - 0.2970*T - 5.62e-5*T**2 \
    + (-206.35 + 0.00778*T + 1.472e-6*T**2)*C \
    + (-8.58 + 1.229e-3*T + 0.852e-7*T**2 + 0.018367*Cr)*Cr \
    + 30.78*Mo \
    + (-0.22 - 0.470e-3*T - 1.855e-7*T**2 + 0.104608*Ni)*Ni
rhoA_(T, C, Cr, Mo, Ni) = 8099.79 - 0.5060*T \
    + (-118.26 + 0.00739*T)*C \
    + (-7.59 + 3.422e-3*T - 5.388e-7*T**2 - 0.014271*Cr)*Cr \
    + 12.45*Mo \
    + (1.54 + 2.267e-3*T - 11.26e-7*T**2 + 0.062642*Ni)*Ni
rhoL_(T, C, Cr, Mo, Ni) = 8319.49 - 0.835*T \
    + (-83.19 + 0.00835*T)*C \
    + (-14.77 + 0.00535*T)*Cr \
    + (10.21 + 0.00835*T)*Mo \
    + (12.72 - 0.00325*T)*Ni

rhoF(T) = rhoF_(T, C, Cr, Mo, Ni)
rhoA(T) = rhoA_(T, C, Cr, Mo, Ni)
rhoL(T) = rhoL_(T, C, Cr, Mo, Ni)

print "rhoF = ", rhoF(TL)
print "rhoA = ", rhoA(TL)
print "rhoL = ", rhoL(TL)

fcc(T, y) = T > TA ? 1/0 : y

array solute[4] = ['C', 'Cr', 'Mo', 'Ni']
array equilL[4] = [0.0003, 0.17, 0.025, 0.12]
array slopeL[4] = [-63802.7453, 6271.864068, 7877.22822, -862.1874141]
array equilS[4] = [3.27e-5, 0.174707, 0.02881, 0.0913553]
array slopeS[4] = [-674731.1828, 5764.813964, 6990.47513, -1225.861277]

do for [i=1:4] {
    j = i+2
    titleL = sprintf('Liquidus slope %.3g K/wt%', slopeL[i]/100)
    titleS = sprintf('Solidus slope %.3g K/wt%', slopeS[i]/100)
    plot 'liquid.txt' u ($1+DT):j w l, \
        'ferrite.txt' u ($1+DT):j w l, \
        equilL[i] + (x-TL)/slopeL[i] w l dt 2 lc 1 title titleL, \
        equilS[i] + (x-TL)/slopeS[i] w l dt 2 lc 2 title titleS, \
        'austenite.txt' u ($1+DT):(fcc($1+DT,column(j))) w l, \
        '< paste ferrite.txt austenite.txt phases.txt' \
            u ($1+DT):(column(j)*$15/($15+$16) + column(j+6)*$16/($15+$16)) w l dt 4 lc 4 \
            title solute[i]."(bcc+fcc)"
}

unset multiplot

set term qt 1 position 900, 200

plot for [i=2:4] 'phases.txt' u ($1+DT):i w l
