
//color("orangered")
//rotate([90,0,0])
//linear_extrude(height = 80, $fn = 100)
//import("base.dxf");

module rotor(){
    color("black")
    rotate([90,0,0])
    cylinder(h=80,r=30,center=true);
    color("gray")
    hull(){
        translate([0,40,0])
        rotate([90,0,0])
        cylinder(h=90,r=8,center=true);
        translate([-25,65,0])
        cylinder(h=22,r=25,center=true);
    }
} 

//rotor();

//iman
//color("gray")
//translate([0,-25,0])
//rotate([90,0,0])
//cylinder(h=45,r=3.4,center=true);


//pines

module pines(){
   color("gray")
   translate([-25,65,0])
   rotate([0,0,-10])
   translate([0,-20,22])
   cylinder(h=22,r=5,center=true);
   
   color("gray")
   translate([-25,65,0])
   rotate([0,0,120-10])
   translate([0,-20,22])
   cylinder(h=22,r=5,center=true);
   
   color("gray")
   translate([-25,65,0])
   rotate([0,0,240-10])
   translate([0,-20,22])
   cylinder(h=22,r=5,center=true);
}


//pines();


color("gray")
translate([-25,65,0])
translate([0,0,22])
cylinder(h=22,r=9,center=true);

origen2=[-25,65,22+11];

color("red")
translate(origen2)
sphere(r = 3);

//-----------------------------origen2:

color("orangered")
translate(origen2)
cylinder(h=225,r=25.4/2,center=false);

color("gray")
translate([0,35,225])
translate(origen2)
rotate([90,0,0])
cylinder(h=70,r=20,center=false);


origen3= origen2+[0,0,225];

color("red")
translate(origen3)
rotate([90,0,0])
cylinder(h=260*2,r=2,center=true);

//********************************
//pendulo:
module pendulo(){
translate([0,0,-225])
cylinder(h=225,r=5,center=false);
translate([0,0,-210])
cylinder(h=30,r=15,center=false);
}

origen4=origen3+[0,-260,0];


translate(origen4)
rotate([0,20,0])
pendulo();


