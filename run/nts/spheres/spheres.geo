r=2;
d=.5;

thick = 0;
fluid = 0.04; //0.04
bound = 0.005;//0.005

Point(1) = {0,0,0};
Point(2) = {r , 0, 0};
Point(3) = {-r, 0, 0};
Point(4) = {0 , r, 0};
Circle(1) = {2,1,4};
Circle(2) = {4,1,3};

Point(11) = {d,0,0};
Point(12) = {d+1 , 0, 0};
Point(13) = {d-1, 0, 0};
Point(14) = {d , 1, 0};
Circle(11) = {12,11,14};
Circle(12) = {14,11,13};

Line(3)    = {3,13};
Line(4)    = {2,12};

Field[1] = Attractor;
Field[1].EdgesList = {4};
Field[1].NNodesByEdge = 100;

Field[3] = Threshold;
Field[3].IField = 1;
Field[3].LcMin = bound;
Field[3].LcMax = fluid;
Field[3].DistMin = thick;
Field[3].DistMax = 6;

Field[10] = Min;
Field[10].FieldsList = {3};
Background Field = 10;

Line Loop(13) = {2, 3, -12, -11, -4, 1};
Plane Surface(14) = {13};

alpha=Pi/50;
Rotate {{1, 0, 0}, {0, 0, 0}, -alpha/2} {
  Surface{14};
}
Extrude {{1, 0, 0}, {0, 0, 0}, alpha} {
  Surface{14};
  Layers{1};
  Recombine;
}

Physical Volume("internal") = {1};
Physical Surface("front") = {36};
Physical Surface("back") = {14};
Physical Surface("outer") = {35, 24};
Physical Surface("inner") = {28, 31};