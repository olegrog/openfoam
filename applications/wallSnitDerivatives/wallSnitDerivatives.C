/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2013 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
Application
    wallSnitDerivatives

Description
    Calculates some derivatives on the wall for all patches and the specific
    times.

\*---------------------------------------------------------------------------*/

#define NoConstructFromTmp
#include "fvCFD.H"
#include "wallFvPatch.H"
#undef NoConstructFromTmp

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void writeWallField(
    const std::string name,
    const GeometricField<Type, fvsPatchField, surfaceMesh>& field,
    const Foam::fvMesh& mesh,
    const Foam::Time& runTime
)
{
    dimensioned<Type> zeroField(
        "zeroField",
        field.dimensions(),
        pTraits<Type>::zero
    );
    GeometricField<Type, fvPatchField, volMesh> wallField(
        IOobject("wall" + name, runTime.timeName(), mesh),
        mesh,
        zeroField
    );
    forAll(wallField.boundaryFieldRef(), patchi) {
        wallField.boundaryFieldRef()[patchi] = field.boundaryField()[patchi];
    }
    wallField.write();
}

int main(int argc, char *argv[])
{
    timeSelector::addOptions();
    #include "addRegionOption.H"
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createNamedMesh.H"

    instantList timeDirs = timeSelector::select0(runTime, args);
    forAll(timeDirs, timeI)
    {
        runTime.setTime(timeDirs[timeI], timeI);
        Info<< "Time = " << runTime.timeName() << endl;
        mesh.readUpdate();
        #include "createFields.H"

        // calculate normal derivatives
        const surfaceScalarField DT0n = fvc::snGrad(T0);
        const surfaceScalarField DTn = fvc::snGrad(T);
        const surfaceVectorField DT = fvc::interpolate(fvc::grad(T));
        const surfaceVectorField DDT0n( 
            ( fvc::interpolate(fvc::grad(fvc::grad(T0))) & mesh.Sf() ) / mesh.magSf()
        );
        const surfaceVectorField DU1n = fvc::snGrad(U1);
        const surfaceVectorField DUn = fvc::snGrad(U);

        // calculate tangential component
        surfaceSymmTensorField tang = I - sqr(mesh.Sf() / mesh.magSf());
        const surfaceVectorField DDT0nt = DDT0n & tang;
        const surfaceVectorField DU1nt = DU1n & tang;
        const surfaceVectorField DTt = DT & tang;
        const surfaceVectorField DUnt = DUn & tang;

        writeWallField("GradT0n", DT0n, mesh, runTime);
        writeWallField("GradGradT0nt", DDT0nt, mesh, runTime);
        writeWallField("GradU1nt", DU1nt, mesh, runTime);

        writeWallField("GradTt", DTt, mesh, runTime);
        writeWallField("GradTn", DTn, mesh, runTime);
        writeWallField("GradUnt", DUnt, mesh, runTime);
    }

    Info<< "End" << endl;

    return 0;
}


// ************************************************************************* //
