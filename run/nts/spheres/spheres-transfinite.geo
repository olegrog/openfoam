R = 2;
d = .5;
theta = Pi/50;

fine = 0.05;
alpha = 5;

phi = Asin(d/R);
N = 5 / fine;       // circular mesh
M = N;              // radial mesh
inner = Exp(-Log(1-d*d) / N / 2);
L = Round(-(Log(1+Exp(-2*N*Log(inner))) - Log(2)) / Log(inner));
circular = Exp(Log((Pi/2 + phi) / (Pi/2 - phi)) / L * 1.2);
radial = 1/(3*alpha-2);

Point(1) = {0, 0, 0};
Point(2) = {R, 0, 0};
Point(3) = {-R, 0, 0};
Point(4) = {d, R*Cos(phi), 0};
Circle(1) = {2, 1, 4};
Circle(11) = {4, 1, 3};

Point(11) = {d, 0, 0};
Point(12) = {d+1, 0, 0};
Point(13) = {d-1, 0, 0};
Point(14) = {d, 1, 0};
Circle(2) = {12, 11, 14};
Circle(22) = {14, 11, 13};

Line(3) = {3, 13};
Line(4) = {2, 12};

Line Loop(13) = {3, -2, -22, -4, 1, 11};
Plane Surface(14) = {13};

Transfinite Line {22} = L + 1 Using Progression inner;
Transfinite Line {2} = 2*N-L + 1 Using Progression inner;
Transfinite Line {11} = L + 1 Using Progression circular;
Transfinite Line {1} = 2*N-L + 1 Using Progression circular;
Transfinite Line {-3, -4} = M + 1 Using Bump radial;
Transfinite Surface {14} = {3, 13, 12, 2};
Recombine Surface{14};

Rotate {{1, 0, 0}, {0, 0, 0}, -theta/2} {
  Surface{14};
}
Extrude {{1, 0, 0}, {0, 0, 0}, theta} {
  Surface{14};
  Layers{1};
  Recombine;
}

Physical Volume("internal") = {1};
Physical Surface("front") = {44};
Physical Surface("back") = {14};
Physical Surface("outer") = {40, 43};
Physical Surface("inner") = {33, 36};
