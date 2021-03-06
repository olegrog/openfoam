const volScalarField liquidFraction("liquidFraction", 1 - phase + SMALL);
const volScalarField& nu = laminarTransport.nu();

fvVectorMatrix UlEqn
(
    fvm::ddt(liquidFraction, Ul)
  + fvm::div(phi, Ul)
 ==
    fvm::laplacian(nu*liquidFraction, Ul)
  - nu*fvm::div(fvc::snGrad(phase)*mesh.magSf(), Ul)
  - fvm::Sp(aIF*nu*sqr(phase/interfaceWidth)*liquidFraction, Ul)
);

UlEqn.relax();

if (pimple.momentumPredictor())
{
    solve(UlEqn == -liquidFraction*fvc::grad(p));
}

U = liquidFraction*Ul;
