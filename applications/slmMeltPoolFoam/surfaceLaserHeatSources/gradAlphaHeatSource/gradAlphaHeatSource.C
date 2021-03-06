/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author(s)
     \\/     M anipulation  |
-------------------------------------------------------------------------------
                            | Copyright (C) 2021 Oleg Rogozin
-------------------------------------------------------------------------------
License
    This file is part of slmMeltPoolFoam.

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

#include "gradAlphaHeatSource.H"

#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeName(gradAlphaHeatSource);
    addToRunTimeSelectionTable(surfaceLaserHeatSource, gradAlphaHeatSource, mixtureAdvector);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::gradAlphaHeatSource::gradAlphaHeatSource
(
    const incompressibleGasMetalMixture& mixture,
    const isoAdvection& advector
)
:
    surfaceLaserHeatSource(typeName, mixture, advector),
    absorptionModelPtr_(absorptionModel::New(modelDict_.subDict("absorption")))
{}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::gradAlphaHeatSource::calcSource()
{
    const volScalarField& redistribution = mixture_.surfaceHeatSourceRedistribution();
    const volVectorField& gradAlphaM = mixture_.gradAlphaM();

    startTimer();
    source_ = redistribution*beam().I()*absorptionModelPtr_->A(gradAlphaM, *this);
    stopTimer();
}


// ************************************************************************* //
