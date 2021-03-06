/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2017 OpenCFD Ltd.
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of trueArrhenius.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "makeTrueArrheniusTypes.H"

#include "trueArrhenius.H"

#include "BirdCarreau.H"
#include "Casson.H"
#include "CrossPowerLaw.H"
#include "HerschelBulkley.H"
#include "Newtonian.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeTrueArrheniusTypes(trueArrhenius, BirdCarreau);
makeTrueArrheniusTypes(trueArrhenius, Casson);
makeTrueArrheniusTypes(trueArrhenius, CrossPowerLaw);
makeTrueArrheniusTypes(trueArrhenius, HerschelBulkley);
makeTrueArrheniusTypes(trueArrhenius, Newtonian);


// ************************************************************************* //
